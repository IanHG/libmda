#ifndef LIBMDA_MULTIDIMARRAY_H
#define LIBMDA_MULTIDIMARRAY_H

#include<algorithm>
#include<iostream>

#include "../util/TPN.h"
#include "../meta/check_type_.h"
#include "../meta/std_wrappers.h"

#include "../interface.h"
#include "../expr/char_expression.h"
#include "../expr/interface.h"

#include "../util/Requesting.h"
#include "scalar.h"

namespace libmda
{
 
template<typename T, int D, typename... U> 
struct parantesesImpl;   // Forward declarations - may avoid these if call below include instead of in class - maybe better?
template<int D, typename... U> 
struct to1DIndex;    // May make it a private member function using a compile loop to access parameter pack entries with an outside op::apply for the loop
template<typename T, int i> 
struct deallocate;

template<typename T, int D> 
class MDA: 
   public libmda::expression_interface<MDA<T,D>,traits<MDA<T,D> > >
{
public:
   //typedef libmda::char_expr::ichar_expression<MDA<T,D> > imda_interface;
   typedef libmda::expression_interface<MDA<T,D>,traits<MDA<T,D> > > imda_interface;
   using imda_interface::operator=;

private:
	int _n[D];	       // Size of extents
	int _intervals[D]; // Intervals needed to convert to 1D index - make const (may use _intervals(setIntervals()) with setIntervals() returning _intervals - other options?)
                      // Max value of int serious issue for 1D index 14^4 is too much! - Same issue in pointer to pointer when allocate! - Just need to use larger int in the class - may use it less in pointer to pointer
	int _size;

   util::TPN<T,D> _m; // T with D stars
	T* _data;          // To access data as 1D array

	void allocate();
	void setIntervals() 
   { 
      _size = 1; 
      for(int i=D-1;i>=0;i--) 
      { 
         _intervals[i] = _size; 
         _size*=_n[i]; 
      }
   } // size non-optimal name
	
   // private copy c-tor for now
public:
   MDA(const MDA& other): _m(nullptr), _data(nullptr) // Copy constructor
   {
      for(int i=0; i<D; ++i)
         _n[i] = other._n[i];
      setIntervals();
      allocate();
      for(int i=0; i<D; ++i)
         _data[i] = other._data[i];
   }
   template<typename... U, 
            iEnable_if<meta::check_type_and_size_<D,int,meta::Remove_reference<U>...>::value> = 0
   > 
   MDA(U&&... u): _n{ static_cast<int>(std::forward<U>(u))... }, _m(NULL)  // c-tor from ints
   { setIntervals(); allocate(); }
	~MDA() { if(_m) {deallocate<T,D>::apply(_m); _m = NULL;} }
   
   MDA& operator=(const MDA& a_other) 
   { return imda_interface::operator=(a_other); }     // Copy assignment

    // Access by [] works trivially - delete
	util::TPN<T,D-1> operator[](int i) { return _m[i]; }
	const util::TPN<T,D-1> operator[](int i) const { return _m[i]; }
	 
   /* ----- libmda interface ----- */
    // implementation of at(...) function
    template<typename... ints, 
             iEnable_if<meta::check_type_and_size_<D,int,ints...>::value> = 0>
             //iEnable_if<util::detail::requesting_elem<D,int,ints...>::value> = 0>
             //util::Requesting_elem<D,int, ints...> = 0>
    T& at(const ints... i) 
    { return parantesesImpl<T,D,ints...>::apply(_m, i...); }
    
    template<typename... ints, 
             iEnable_if<meta::check_type_and_size_<D,int,ints...>::value> = 0>
             //iEnable_if<util::detail::requesting_elem<D,int,ints...>::value> = 0>
             //util::Requesting_elem<D,int, ints...> = 0>
    T const& at(const ints... i) const
    { return parantesesImpl<T,D,ints...>::apply(_m, i...); }
    
    // Access by calculating 1D array entry
    //template<typename... ints, iEnable_if<meta::check_type_and_size_<D,int,ints...>::value> = 0> 
    //T& att(ints... i) { return _data[to1DIndex<D,ints...>::apply(_intervals,i...)]; }
    //template<typename... ints, iEnable_if<meta::check_type_and_size_<D,int,ints...>::value> = 0> 
    //const T& att(ints... i) const { return _data[to1DIndex<D,ints...>::apply(_intervals,i...)]; }

    int size() const
    {
      int size=1;
      for(int i=0; i<D; ++i)
         size*=_n[i];
      return size;
    }

    template<int N, iEnable_if<N<D> = 0> int extent() const { return _n[N]; }
    /* ----- libmda interface end ----- */
	
   //friend void swap(MDA<T,D>& mda1, MDA<T,D>&& mda2)
   //{
   //   std::swap(mda1._m,mda2._m); std::swap(mda1._data,mda2._data);
   //  for(int i=0; i<D; ++i) { mda1._n[i] = mda2._n[i]; mda1._intervals[i] = mda2._intervals[i]; }
   //}
   // Access by () less trivial but nicer in main
    template<typename... ints, 
             typename std::enable_if<meta::check_type_and_size_<D,int,ints...>::value, int>::type = 0>
             //iEnable_if<util::detail::requesting_elem<D,int,ints...>::value> = 0>
             //util::Requesting_elem<D,int, ints...> = 0>
    T&       operator()(const ints... i)   //    { return at(i...); }
    { return parantesesImpl<T,D,ints...>::apply(_m, i...); }
    
    template<typename... ints,
             typename std::enable_if<meta::check_type_and_size_<D,int,ints...>::value, int>::type = 0>
             //iEnable_if<util::detail::requesting_elem<D,int,ints...>::value> = 0>
             //util::Requesting_elem<D,int, ints...> = 0>
    T const& operator()(const ints... i) const //{ return at(i...); }
    { return parantesesImpl<T,D,ints...>::apply(_m, i...); }
    
    template<typename... ints,
             iEnable_if<util::detail::requesting_slice<D,ints...>::value> = 0>
             //util::Requesting_slice<D,ints...> = 0>
    libmda::char_expr::mda_char_expression<MDA<T,D>, ints...>
    operator()(const ints... i) // -> decltype(imda_interface::operator()(i...))
    { return imda_interface::c_expr(i...); } 
    //{ return imda_interface::operator()(i...); } //written expicitly to comply with
                                                 //clang and gcc(!) compiler
    
    // Access as 1D array - delete or protect
    T& vec_at(int i) { return _data[i]; }
    const T& vec_at(int i) const { return _data[i]; }
    

    void output()
    {
      int size=1;
      for(int i=0; i<D; ++i)
         size*=_n[i];

      for(int i=0; i<size; ++i)
         std::cout << _data[i] << " ";
      std::cout << std::endl;
    }
};

//
// specialization for 0-dimensional (number)
//
template<class T>
class MDA<T,0>: public arrays::scalar<T,int>
{
};

} // namespace libmda

template<typename T, int D>
struct traits<libmda::MDA<T,D> >
{
   typedef T        value_type;
   typedef int      size_type;
   typedef libmda::MDA<T,D> type;
   static const int order = D;
};

#include "MultiDimArrayImpl.h"

#endif /* LIBMDA_MULTIDIMARRAY_H */
