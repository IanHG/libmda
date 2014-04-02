#ifndef LIBMDA_META_STRING_H_INCLUDED
#define LIBMDA_META_STRING_H_INCLUDED

#include<iostream>
#include<string>
#include"../meta/if.h"
#include"../util/print_variadic.h"

namespace libmda
{
namespace util
{

//
// meta string class
//
template<char... Cs>
struct meta_string
{ 
   //static constexpr const char* to_char()
   //{ 
   //   return std::string{Cs...}.c_str(); 
   //}
};

//
// print a meta string
//
template<char... Cs>
std::ostream& operator<<(std::ostream& a_ostream, const meta_string<Cs...>& ms)
{ 
   print_variadic(a_ostream,"",Cs...);
   return a_ostream; 
}

//
// catenate meta string
//
template<class L, class R>
struct catenate;

template<char... Cs1, char... Cs2>
struct catenate<meta_string<Cs1...>, meta_string<Cs2...> >
{
   using type = meta_string<Cs1...,Cs2...>;
};

template<class L, class R>
using Catenate = typename catenate<L,R>::type;

//
// catenate with operator + as constexpr
//
template<char... Cs1
       , char... Cs2
       >
constexpr meta_string<Cs1..., Cs2...> operator+(const meta_string<Cs1...>&, const meta_string<Cs2...>&)
{ 
   return meta_string<Cs1...,Cs2...>(); 
}

//
// meta string literal (not tested)
//
template<char... Cs>
constexpr meta_string<Cs...> operator"" _ms()
{ 
   return meta_string<Cs...>(); 
}

//
// convert integer to meta string
//
namespace detail
{
//
// first some helpers
//
template<bool, int I, char... Cs>
struct int_to_meta_string_impl
{
   using type = typename int_to_meta_string_impl< I>=10 , I/10 , '0'+I%10, Cs... >::type;
};

template<int I, char... s>
struct int_to_meta_string_impl<false,I,s...>
{
   using type = meta_string<s...>;
};

} // namespace detail

template<int I>
struct int_to_meta_string
{
   using type = If< (I>=0)
                  , typename detail::int_to_meta_string_impl< I>=10, (I-I%10)/10, '0'+I%10>::type
                  , Catenate<meta_string<'-'>,typename detail::int_to_meta_string_impl<-I>=10,-(I+I%10)/10, '0'-I%10>::type> 
                  >;
};

//
// interface for converting integer to metastring
//
template<int I>
using Int_to_meta_string = typename int_to_meta_string<I>::type;

} // namespace util
} // namespace libmda

#endif /* LIBMDA_META_STRING_H_INCLUDED */
