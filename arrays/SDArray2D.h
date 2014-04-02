#ifndef SDARRAY2D_H
#define SDARRAY2D_H

#include<iostream>
#include"../interface.h"
#include"../expr/char_expression.h"
#include"../expr/expression.h"
#include"../util/index_check.h"
using libmda::util::index_nocheck;
#include"../expr/interface.h"
#include"Mda_ref.h"

//#include "debug_check.h"

static int number = 0;

namespace midas
{

namespace mmv
{

template<typename T, 
   typename Allocator = std::allocator<T>,
   typename index_check_policy = index_nocheck
   >
class SDArray2D: 
   public libmda::expression_interface<SDArray2D<T,Allocator,index_check_policy> > 
{
   public:
      typedef libmda::expression_interface<SDArray2D<T,Allocator,index_check_policy> > imda_interface;
      typedef traits<SDArray2D<T,Allocator,index_check_policy> >  traits_type;
      typedef typename traits_type::value_type value_type;
      typedef typename traits_type::size_type  size_type;
      static const int order = traits_type::order;
      
      using imda_interface::operator=;
      //using imda_expr_interface::operator=;
      using imda_interface::operator();

   private:
      T*  mptData1D;
      T** mptData2D;
      size_t msRows;
      size_t msCols;
      size_t msSize;
      int    mNumber;
   
   private:
      void AllocateArray2D();
      void DeallocateArray2D();

   private: // to prevent use

   public:
      double pub_var;
      SDArray2D();
      SDArray2D(size_t asRows, size_t asCols);
      SDArray2D(const SDArray2D&);
      ~SDArray2D();

      SDArray2D& operator=(const SDArray2D& a_other)
      { return imda_interface::operator=(a_other); }
      
      void Copy(const SDArray2D& a_other)
      { 
         for(size_type i=0; i<msRows; ++i) 
            for(size_type j=0; j<msCols; ++j) 
               mptData2D[i][j] = a_other(i,j); 
      }

      /**
       * use as 2D structure
       **/
      T*       operator[](size_t asRows)       
      { 
         return mptData2D[asRows]; 
      }
      T const* operator[](size_t asRows) const 
      { 
         return mptData2D[asRows]; 
      }

      T& operator()(size_t asRows, size_t asCols)
      { 
         return at(asRows,asCols); 
      }
      T const& operator()(size_t asRows, size_t asCols) const 
      { 
         return at(asRows,asCols); 
      }
      
      /**
       * use as 1D structure
       **/
      //T& operator()(size_t asSize)       { return mptData1D[asSize]; }
      //T  operator()(size_t asSize) const { return mptData1D[asSize]; }
      
      /*template<char index1, char index2>
      CharExpression<SDArray2D<T,Allocator>, CIndex<index1>, CIndex<index2> > 
      operator()(const CIndex<index1>, const CIndex<index2>)
      { return CharExpression<SDArray2D<T,Allocator>, CIndex<index1>, CIndex<index2> >(); }*/
         
      T* get() const { return mptData1D; }
      /**
       * get sizes
       **/
      size_t Ncols() const { return msCols; }
      size_t Nrows() const { return msRows; }
      size_t Size()  const { return msSize; }
      
      size_t size()  const { return msSize; }

      //const T& vec_at(const size_t i) const { };
      //      T& vec_at(const size_t i) { };
      
      const T& vec_at(const size_t i) const { return mptData1D[i]; }
            T& vec_at(const size_t i)       { return mptData1D[i]; }

      T& at(size_t asRows, size_t asCols)
      { 
         //cout << " accessing array " << mNumber << " which is " << msRows << "x" << msCols << " array " << endl;
         index_check_policy::apply(asRows,msRows);
         index_check_policy::apply(asCols,msCols);
         return mptData2D[asRows][asCols]; 
      }
      T const& at(size_t asRows, size_t asCols) const 
      { 
         //cout << " accessing array " << mNumber << " which is " << msRows << "x" << msCols << " array " << endl;
         index_check_policy::apply(asRows,msRows);
         index_check_policy::apply(asCols,msCols);
         return mptData2D[asRows][asCols]; 
      }
      
      template<int N, libmda::iEnable_if<N==0> = 0> size_t extent() const { return msRows; }
      template<int N, libmda::iEnable_if<N==1> = 0> size_t extent() const { return msCols; }

      void resize(size_t row, size_t col)
      {
         DeallocateArray2D();
         msRows = row;
         msCols = col;
         msSize = msRows*msCols;
         AllocateArray2D();
      }

      class iterator
      {
         private:
            T* mptPtr;
         public:
            iterator(SDArray2D& aArr, size_t aOff): mptPtr(aArr.mptData1D+aOff) { };
            int& operator*() { return *mptPtr; }
            iterator& operator++() { ++mptPtr; return *this; }
            bool operator==(const iterator& aIter) { return mptPtr==aIter.mptPtr; }
            bool operator!=(const iterator& aIter) { return mptPtr!=aIter.mptPtr; }
      };
      friend class iterator;
      
      iterator begin() { return iterator(*this,0); }
      iterator end()   { return iterator(*this,msSize); }

      void DoOutput(std::ostream&) const;
      
      template<int N=2, typename... Ts>
      ::libmda::arrays::Mda_ref<N,value_type,size_type> 
      sub_array(Ts&&... ts)
      { 
         return ::libmda::arrays::Mda_ref<N,value_type,size_type>
            { mptData1D, size_type(std::forward<Ts>(ts))...};
      };
};

template<typename T, typename Allocator, typename index_check_policy>
void SDArray2D<T,Allocator,index_check_policy>::AllocateArray2D()
{
   mptData1D = typename Allocator::template rebind<T>::other().allocate(msSize);
   mptData2D = typename Allocator::template rebind<T*>::other().allocate(msRows);
   T* ptData = mptData1D;
   for(size_t row=0; row<msRows; ++row)
   {
      mptData2D[row] = ptData;
      ptData+=msCols;
   }
}

template<typename T, typename Allocator, typename index_check_policy>
void SDArray2D<T,Allocator,index_check_policy>::DeallocateArray2D()
{
   if(mptData1D)
   {
      typename Allocator::template rebind<T>::other().deallocate(mptData1D, msSize);
      mptData1D = NULL;
   }
   
   if(mptData2D)
   {
      typename Allocator::template rebind<T*>::other().deallocate(mptData2D, msRows);
      mptData2D = NULL;
   }
}

template<typename T, typename Allocator, typename index_check_policy>
SDArray2D<T,Allocator,index_check_policy>::SDArray2D(): 
   mptData1D(NULL), 
   mptData2D(NULL), 
   msRows(0), 
   msCols(0), 
   msSize(0)
{
   //cout << " 2D array default constructor " << endl;
}

template<typename T, typename Allocator, typename index_check_policy>
SDArray2D<T,Allocator,index_check_policy>::SDArray2D(size_t asRows, size_t asCols):
   mptData1D(NULL), 
   mptData2D(NULL), 
   msRows(asRows), 
   msCols(asCols), 
   msSize(asRows*asCols),
   mNumber(number++)
{
   //cout << " 2D array size constructor " << endl;
   AllocateArray2D();
}

template<typename T, typename Allocator, typename index_check_policy>
SDArray2D<T,Allocator,index_check_policy>::SDArray2D(const SDArray2D<T,Allocator,index_check_policy>& aOtherArray):
   mptData1D(NULL),
   mptData2D(NULL),
   msRows(aOtherArray.msRows),
   msCols(aOtherArray.msCols),
   msSize(aOtherArray.msSize)
{
   //cout << " 2D array copy constructor " << endl;
   AllocateArray2D();
   this->Copy(aOtherArray);
}

template<typename T, typename Allocator, typename index_check_policy>
SDArray2D<T,Allocator,index_check_policy>::~SDArray2D()
{
   DeallocateArray2D();
}

template<typename T, typename Allocator, typename index_check_policy>
void SDArray2D<T,Allocator,index_check_policy>::DoOutput(std::ostream& aOstream) const
{
   for(size_t row=0; row<msRows; ++row)
   {
      for(size_t col=0; col<msCols; ++col)
         aOstream << " " << mptData2D[row][col];
      aOstream << "\n";
   }
}

template<typename T, typename Allocator, typename index_check_policy>
inline std::ostream& operator<<(std::ostream& aOstream, const SDArray2D<T,Allocator,index_check_policy>& aArray)
{
   aArray.DoOutput(aOstream);
   return aOstream;
}


}
}

template<typename T, typename Allocator, typename index_check_policy>
struct traits<midas::mmv::SDArray2D<T, Allocator, index_check_policy> >
{
   typedef T                                   value_type;
   typedef size_t                              size_type;
   typedef midas::mmv::SDArray2D<T,Allocator,index_check_policy>  type;
   static const int order = 2;
};

namespace libmda
{

template<typename T, typename Allocator, typename index_check_policy>
struct operator_traits<midas::mmv::SDArray2D<T,Allocator,index_check_policy> >:
   default_operator_traits
{ 
   template<class L, class R>
   using oper_add = expr::op_add<L,R>;
};

} // namespace libmda

#endif /* SDARRAY2D_H */
