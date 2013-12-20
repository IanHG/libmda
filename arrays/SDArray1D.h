#ifndef SDARRAY1D_H
#define SDARRAY1D_H

#include<iostream>
#include<assert.h>

#include"../interface.h"
#include"../IMDA.h"
#include"../functions.h"
//#include"../expr/expression.h"
//#include"../expr/char_expression.h"
#include "../expr/interface.h"
#include"../utility/index_check.h"
#include"../utility/sequence.h"
#include"../utility/require.h"
#include"Mda.h"
#include"Mda_ref.h"
#include"Mda_slice.h"
#include"slice.h"

namespace midas
{
namespace mmv
{

template<typename T, typename Allocator, typename index_check_policy> 
class SDArray1D;

}
}

namespace testing_traits
{
template<class A>
struct traits;

template<typename T, typename Allocator, typename index_check_policy>
struct traits< ::midas::mmv::SDArray1D<T, Allocator, index_check_policy> >
{
   typedef T                                     value_type;
   typedef size_t                                size_type;
   typedef ::midas::mmv::SDArray1D<T,Allocator,index_check_policy>    type;
   static const int order = 1;
};

} // namespace testing_traits 

namespace midas
{
namespace mmv
{


template<typename T, 
         typename Allocator = std::allocator<T>,
         typename index_check_policy = libmda::utility::index_nocheck
>
class SDArray1D:
   public libmda::expression_interface<SDArray1D<T,Allocator,index_check_policy>,
                                       ::testing_traits::traits<SDArray1D<T,Allocator,index_check_policy> > >
{
   public:
      //typedef libmda::IMDAInterface<SDArray1D<T,Allocator> > imda_interface;
      //typedef libmda::iexpression<SDArray1D<T,Allocator> > imda_interface;
      //typedef libmda::char_expr::ichar_expression<SDArray1D<T,Allocator,index_check_policy> > imda_interface;
      typedef libmda::expression_interface<SDArray1D<T,Allocator,index_check_policy>, ::testing_traits::traits<SDArray1D<T,Allocator,index_check_policy> > > imda_interface;
      using imda_interface::operator=;
      using imda_interface::operator();
    
      typedef testing_traits::traits<SDArray1D<T, Allocator,index_check_policy> > traits_type;
      //typedef ::midas::mmv::traits<SDArray1D<T, Allocator,index_check_policy> > traits_type;
      typedef typename traits_type::value_type value_type;
      typedef typename traits_type::size_type  size_type;
      typedef typename traits_type::type       type;
      static const int order = traits_type::order;
   
   private:
      T*  mptData1D;
      size_t msSize;
   
   private:
      void AllocateArray1D();
      void DeallocateArray1D();
      //SDArray1D<T,Allocator>& operator=(const SDArray1D<T,Allocator>&);

   private: // to prevent use

   public:
      SDArray1D();
      SDArray1D(size_t asSize);
      SDArray1D(const SDArray1D<T,Allocator,index_check_policy>&);
      /* construction from libmda expression */
      template<class A> //, libmda::Require_order<A,1> = 0 >
      SDArray1D(const libmda::expr::expression_base<A>& inp):
         mptData1D(NULL), msSize(inp.size())
      {
         AllocateArray1D();
         for(size_type i = 0; i<size(); ++i)
            mptData1D[i] = inp.at(i);
            //at(i) = inp.at(i);
      }
      
      ~SDArray1D();
      
      SDArray1D& operator=(const SDArray1D& a_other)
      { return imda_interface::operator=(a_other); }

      /**
       * use as 1D structure
       **/
      T&       operator[](const size_t asSize)       { return mptData1D[asSize]; }
      T const& operator[](const size_t asSize) const { return mptData1D[asSize]; }
      
      T&        operator()(const size_t asSize)       
      { return at(asSize); }
      T const&  operator()(const size_t asSize) const 
      { return at(asSize); }
      
      T* get() const { return mptData1D; }
      /**
       * get sizes
       **/
      size_t Nsize()   const { return msSize; }
      size_type Size() const { return msSize; }
      
      //template<class I, libmda::iEnable_if<libmda::Requesting_elem<1,size_type,I>()> = 0>
      T&        at(const size_t asSize)       
      { 
         index_check_policy::apply(asSize,msSize);
         return mptData1D[asSize]; 
      }
      
      //template<class I, libmda::iEnable_if<libmda::Requesting_elem<1,size_type,I>()> = 0>
      T const&  at(const size_t asSize) const 
      { 
         index_check_policy::apply(asSize,msSize);
         return mptData1D[asSize]; 
      }

      size_type size() const { return msSize; }
      
      template<int N, libmda::iEnable_if<N==0> = 0> size_type extent() const { return msSize; }
      
      /**
       * copy
       **/
      /*template<typename Expr>
      inline void Copy(const midas::mmv::Expression<Expr>&);*/
      inline void Copy(const SDArray1D&);

      /**
       * Iterator setup
       **/
      class iterator
      {
         private:
            T* mptPtr;
         public:
            iterator(SDArray1D& aArr, size_t aOff): mptPtr(aArr.mptData1D+aOff) { };
            int& operator*() { return *mptPtr; }
            iterator& operator++() { ++mptPtr; return *this; }
            bool operator==(const iterator& aIter) { return mptPtr==aIter.mptPtr; }
            bool operator!=(const iterator& aIter) { return mptPtr!=aIter.mptPtr; }
      };
      friend class iterator;
      
      iterator begin() { return iterator(*this,0); }
      iterator end()   { return iterator(*this,msSize); }

      void DoOutput(std::ostream&) const;
      
      
      template<int N=1, typename... Ts>
      ::libmda::arrays::mda_impl::Mda_ref<N,value_type,size_type> 
      sub_array(Ts&&... ts)
      { 
         return ::libmda::arrays::mda_impl::Mda_ref<N,value_type,size_type>
            { mptData1D, size_type(std::forward<Ts>(ts))...};
      };
}; 

template<typename T, typename Allocator, typename index_check_policy>
void SDArray1D<T,Allocator,index_check_policy>::AllocateArray1D()
{
   mptData1D = typename Allocator::template rebind<T>::other().allocate(msSize);
}

template<typename T, typename Allocator, typename index_check_policy>
void SDArray1D<T,Allocator,index_check_policy>::DeallocateArray1D()
{
   if(mptData1D)
   {
      typename Allocator::template rebind<T>::other().deallocate(mptData1D, msSize);
      mptData1D = NULL;
   }
}

template<typename T, typename Allocator, typename index_check_policy>
SDArray1D<T,Allocator,index_check_policy>::SDArray1D(): 
   mptData1D(NULL), 
   msSize(0)
{ }

template<typename T, typename Allocator, typename index_check_policy>
SDArray1D<T,Allocator,index_check_policy>::SDArray1D(size_t asSize):
   mptData1D(NULL), 
   msSize(asSize)
{
   AllocateArray1D();
}

template<typename T, typename Allocator, typename index_check_policy>
SDArray1D<T,Allocator,index_check_policy>::SDArray1D(const SDArray1D<T,Allocator,index_check_policy>& aOtherArray):
   mptData1D(NULL),
   msSize(aOtherArray.msSize)
{
   //std::cout << " using copy constructor " << std::endl;
   AllocateArray1D();
   this->Copy(aOtherArray);
}

template<typename T, typename Allocator, typename index_check_policy>
SDArray1D<T,Allocator,index_check_policy>::~SDArray1D()
{
   DeallocateArray1D();
}

//template<typename T, typename Allocator> template<typename Expr>
//inline void SDArray1D<T,Allocator>::Copy(const midas::mmv::Expression<Expr>& aOtherArray)
template<typename T, typename Allocator, typename index_check_policy> 
inline void SDArray1D<T,Allocator,index_check_policy>::Copy(const SDArray1D<T,Allocator,index_check_policy>& aOtherArray)
{
   //cout << " using Copy() " << endl;
   assert(msSize == aOtherArray.Size());
   for(size_t index=0; index<msSize; ++index)
      mptData1D[index] = aOtherArray(index);
}

template<typename T, typename Allocator, typename index_check_policy>
void SDArray1D<T,Allocator,index_check_policy>::DoOutput(std::ostream& aOstream) const
{
   for(size_t size=0; size<msSize; ++size)
      aOstream << " " << mptData1D[size];
   //aOstream << "\n";
}

//template<typename T, typename Allocator, typename index_check_policy>
//inline std::ostream& operator<<(std::ostream& aOstream, const SDArray1D<T,Allocator,index_check_policy>& aArray)
//{
//   aArray.DoOutput(aOstream);
//   return aOstream;
//}


template<typename T, typename Allocator, typename index_check_policy>
T dot(const SDArray1D<T,Allocator,index_check_policy>& arg1, 
      const SDArray1D<T,Allocator,index_check_policy>& arg2)
{
   assert(arg1.size() == arg2.size());
   T dot = 0;
   for(size_t i = 0; i<arg1.size(); ++i)
      dot += arg1(i)*arg2(i);
   return dot;
}

template<typename T, typename Allocator, typename index_check_policy>
T norm(const SDArray1D<T,Allocator,index_check_policy>& arg)
{
   return sqrt(dot(arg,arg));
}

}
}

#endif /* SDARRAY1D_H */
