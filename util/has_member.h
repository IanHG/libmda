#ifndef LIBMDA_HAS_MEMBER_H
#define LIBMDA_HAS_MEMBER_H

#include<type_traits>
#include"../expr/take_out_types.h"
#include"../basic_using.h"

namespace libmda
{

struct IMDABase;

/****************************/
// struct to check for public type in class
/****************************/
#define LIBMDA_CREATE_HAS_MEMBER_TYPE(NAME,TYPE) \
template<class A> \
struct NAME \
{ \
   template<class B> static std::true_type  test(typename B::TYPE*) { return std::true_type();  } \
   template<class B> static std::false_type test(...)               { return std::false_type(); } \
   typedef decltype(test<A>(0)) type; \
   static const bool value = type::value; \
};

namespace util{ // namespace util
LIBMDA_CREATE_HAS_MEMBER_TYPE(has_value_type, value_type)
LIBMDA_CREATE_HAS_MEMBER_TYPE(has_size_type, size_type)
} // namespace util
#undef LIBMDA_CREATE_HAS_MEMBER_TYPE


/****************************/
// struct to check for public variable in class
/****************************/
#define LIBMDA_CREATE_HAS_MEMBER_VARIABLE(NAME,VAR) \
template<class A> \
struct NAME \
{ \
   template<class B> static std::true_type  test( decltype(B::VAR)* ) { return std::true_type();  } \
   template<class B> static std::false_type test(...)                 { return std::false_type(); } \
   typedef decltype(test<A>(0)) type; \
   static const bool value = type::value; \
}; 

namespace util{ // namespace util
LIBMDA_CREATE_HAS_MEMBER_VARIABLE(has_order, order)
} // namespace util
#undef LIBMDA_CREATE_HAS_MEMBER_VARIABLE

/****************************/
// struct to check for public function in class
// 
// function signature must be provided separately
// through a using statement e.g:
// 
// template<class B> sig = double&(B::*)(const int);
//
// which will search for a function which takes a const int and 
// returns a reference to double
/****************************/
#define LIBMDA_CREATE_HAS_MEMBER_FUNCTION(NAME,FUNC) \
template<class A, template<class> class sig> \
struct NAME \
{ \
   /* true test */ \
   template<typename B> \
   static std::true_type \
   test(decltype(static_cast<sig<B> >(&B::FUNC))) \
   { return std::true_type(); } \
  \
   /* false test */ \
   template<typename B> \
   static std::false_type test(...) { return std::false_type(); } \
  \
   typedef decltype(test<A>(0)) type; \
   static const bool value = type::value; \
};

namespace util{ // namespace util
LIBMDA_CREATE_HAS_MEMBER_FUNCTION(basic_has_vec_at,vec_at)
LIBMDA_CREATE_HAS_MEMBER_FUNCTION(basic_has_apply_vec,apply_vec)

LIBMDA_CREATE_HAS_MEMBER_FUNCTION(basic_has_size,size)
} // namespace util
#undef LIBMDA_CREATE_HAS_MEMBER_FUNCTION

namespace util{ // namespace util
template<class A, typename size_type> struct has_size
{
   template<class B> using sig = size_type(B::*)() const;
   static const bool value = basic_has_size<A,sig>::value;
};
   
   
template<class A>
struct has_assignable_vec_at
{  typedef typename A::value_type value_type;
   typedef typename A::size_type  size_type;
   template<class B> using sig1 = value_type&(B::*)(const size_type);
   static const bool value = 
      basic_has_vec_at<A,sig1>::value;
};

template<class A>
struct has_nonassignable_vec_at
{  
   typedef typename A::value_type value_type;
   typedef typename A::size_type  size_type;
   template<class B> using sig1 = value_type(B::*)(const size_type)const;
   template<class B> using sig2 = const value_type&(B::*)(const size_type)const;
   static const bool value = 
      basic_has_vec_at<A,sig1>::value ||
      basic_has_vec_at<A,sig2>::value;
};

template<class A>
struct has_vec_at_indirection
{ static const bool value = (has_assignable_vec_at<A>::value || has_nonassignable_vec_at<A>::value); };


template<class A>
struct has_vec_at // USE IS BASE OF IMDABase TO DETERMINE IF WE ARE AN LIBMDA EXPRESSION/MATRIX
{ static const bool value = std::is_base_of<libmda::IMDABase,A>::value ? (has_vec_at_indirection<A>::value) : false; };

template<>
struct has_vec_at<double> 
{ static const bool value = true; };

template<class...>
struct has_apply_vec;

template<class A, class L, class R>
struct has_apply_vec<A,L,R> // for binary oper
{
   typedef typename expr::take_out_types<L,R>::value_type value_type;
   typedef typename expr::take_out_types<L,R>::size_type  size_type;
   template<class B> using sig = value_type(B::*)(const L&, const R&, const size_type);
   static const bool value = basic_has_apply_vec<A,sig>::value;
};

template<class A, class B>
struct has_apply_vec<A,B> // for unary oper
{
   typedef typename B::value_type value_type;
   typedef typename B::size_type  size_type;
   template<class C> using sig = value_type(C::*)(const B&, const size_type);
   static const bool value = basic_has_apply_vec<A,sig>::value;
};

} // namespace util
} // namespace libmda

#endif /* LIBMDA_HAS_MEMBER_FUNCTION_H */
