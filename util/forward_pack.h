#ifndef LIBMDA_FORWARD_PACK_H_INCLUDED
#define LIBMDA_FORWARD_PACK_H_INCLUDED

// Disclamer:
//    Heavily inspired by Andy Prowls answer to this question on Stack Overflow with some additions
//    http://stackoverflow.com/questions/14261183/how-to-make-generic-computations-over-heterogeneous-argument-packs-of-a-variadic
//

#include"../meta/index_list.h"
#include"nth_value_of.h"

namespace libmda
{
namespace util
{

//
// The functor provided in the first argument is given in input the
// arguments in whose index is contained in the index list specified
// as the second argument.
//
//template<typename F, unsigned... Is, typename... Ts>
//void forward_subpack(F&& f, index_list<Is...> const& i, Ts&&... args)
//{
//   f((util::nth_value_of<Is>(std::forward<Ts>(args)...))...);
//}

/* modified version useable with functions with return types also */
template<typename F, unsigned... Is, typename... Ts>
auto forward_subpack(F&& f, meta::index_list<Is...> const& i, Ts&&... args)->
   decltype(f((util::nth_value_of<Is>(std::forward<Ts>(args)...))...))
{
   return f((util::nth_value_of<Is>(std::forward<Ts>(args)...))...);
}

//
// The functor provided in the first argument is given in input all the
// arguments in the pack.
//
//template<typename F, typename... Ts>
//void forward_pack(F&& f, Ts&&... args)
//{
//   f(std::forward<Ts>(args)...);
//}

/* modified version useable with functions with return types also */
template<typename F, typename... Ts>
auto forward_pack(F&& f, Ts&&... args) ->
   decltype(f(std::forward<Ts>(args)...))
{
   f(std::forward<Ts>(args)...);
}

//
// functor is given as input all arguments that satisfies predicate Pred
//
template<class F, class Pred, typename... Ts, class Index = meta::index_list_if<Pred,Ts...> >
auto forward_pack_if(F&& f, Pred const& p, Ts&&... args)
   -> decltype(forward_subpack(std::forward<F>(f), Index(), std::forward<Ts>(args)...))
{
   return forward_subpack(std::forward<F>(f), Index(), std::forward<Ts>(args)...);
}

} // namespace util
} // namespace libmda
 
#endif /* LIBMDA_FORWARD_PACK_H_INCLUDED */
