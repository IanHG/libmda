#ifndef LIBMDA_META_STRING_H
#define LIBMDA_META_STRING_H

#include<iostream>
#include<string>
#include"../metaprog/if.h"
using libmda::metaprog::if_;

namespace libmda
{
namespace utility
{

template<char... s>
struct meta_string
{ 
   static constexpr const char* to_char()
   { return std::string{s...}.c_str(); }
};

template<char... s>
std::ostream& operator<<(std::ostream& a_ostream, const meta_string<s...>& ms)
{ 
   a_ostream << std::string{s...}.c_str(); 
   return a_ostream; 
}

/**
 * catenate meta string
 **/
template<class L, class R>
struct catenate;
template<char... s, char... ss>
struct catenate<meta_string<s...>, meta_string<ss...> >
{
   typedef meta_string<s...,ss...> type;
};

// catenate with operator + as constexpr
template<char...s,char... ss>
meta_string<s...,ss...> 
operator+(const meta_string<s...>&, const meta_string<ss...>&)
{ return meta_string<s...,ss...>(); }

template<char... s>
constexpr meta_string<s...> operator"" _ms()
{ return meta_string<s...>(); }

/* make meta string from integer */
// first some helpers
template<bool, int e, char... s>
struct int_to_string_
{
   typedef typename int_to_string_< e>=10 , e/10 , s..., '0'+e%10 >::type type;
};

template<int e, char... s>
struct int_to_string_<false,e,s...>
{
   typedef meta_string<s...> type;
};

template<int e>
struct int_to_string
{
   typedef typename if_< e>=0, // check for positive/negative
      typename int_to_string_< e>=10 , e/10, '0'+e%10>::type,     // positive
      typename int_to_string_< -e>=10,-e/10, '-', '0'-e%10>::type // negative append '-'
      >::type type;
};

} // namespace utility
} // namespace libmda

#endif /* LIBMDA_META_STRING_H */
