#ifndef LIBMDA_METAPROG_IF_H_INCLUDED
#define LIBMDA_METAPROG_IF_H_INCLUDED

namespace libmda
{
namespace meta
{
namespace detail
{
//
// if implementation
//
template<bool TEST, typename T1, typename T2> 
struct if_impl
{ 
   using type = T1; 
};

// 
template<typename T1, typename T2> 
struct if_impl<false,T1,T2>
{ 
   using type = T2; 
};

} // namespace detail

//
// if to switch between two types
//
template<bool TEST, typename T1, typename T2> 
struct if_: detail::if_impl<TEST,T1,T2> 
{ 
};

//
// eval_if... same as if_ interface through If
//
template<bool TEST, typename T1, typename T2>
struct eval_if: if_<TEST,T1,T2>::type
{ 
};

//
// if interface
//
template<bool TEST, typename T1, typename T2>
using If = typename if_<TEST,T1,T2>::type;

} // namespace meta

// remove this at some poiint !!
using meta::If;

} // namespace libmda

#endif /* LIBMDA_METAPROG_IF_H_INCLUDED */
