#ifndef METAPROG_IF_H
#define METAPROG_IF_H

namespace libmda
{
namespace metaprog
{

// if implementation
template<bool TEST, typename T1, typename T2> struct if_impl
{ typedef T1 type; };
template<typename T1, typename T2> struct if_impl<false,T1,T2>
{ typedef T2 type; };
// if to switch between two types
template<bool TEST, typename T1, typename T2> struct if_: if_impl<TEST,T1,T2> { };

// eval_if... same as if_ interface through If
template<bool TEST, typename T1, typename T2>
struct eval_if: if_<TEST,T1,T2>::type
{ };

} // namespace metaprog

// if interface
template<bool TEST, typename T1, typename T2>
using If = typename metaprog::if_<TEST,T1,T2>::type;

} // namespace libmda

#endif /* METAPROG_IF_H */
