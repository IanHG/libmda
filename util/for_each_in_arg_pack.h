#ifndef LIB_FORWARD_H_INCLUDED
#define LIB_FORWARD_H_INCLUDED

// Disclamer: 
// All credit goes to Andy Prowl for his answer to this question at Stack Overflow (with very few additions)
// http://stackoverflow.com/questions/14261183/how-to-make-generic-computations-over-heterogeneous-argument-packs-of-a-variadic
//

//#include "homogeneous.h"
#include <type_traits>
#include <utility>
#include "../meta/index_list.h"
#include "../meta/nth_type_of.h"
#include "../util/nth_value_of.h"

namespace libmda
{
namespace util
{

//===============================================================================
// CLASSES AND FUNCTIONS FOR REALIZING LOOPS ON ARGUMENT PACKS

// Implementation inspired by @jogojapan's answer to this question:
// http://stackoverflow.com/questions/14089637/return-several-arguments-for-another-function-by-a-single-function

// Collects internal details for implementing functor invocation
namespace detail
{
// Functor invocation is realized through variadic inheritance.
// The constructor of each base class invokes an input functor.
// An functor invoker for an argument pack has one base class
// for each argument in the pack

// Realizes the invocation of the functor for one parameter
template<unsigned I, typename T>
struct invoker_base
{
  template<typename F, typename U>
  invoker_base(F&& f, U&& u) { f(u); }
};

// Necessary because a class cannot inherit the same class twice
template<unsigned I, typename T>
struct indexed_type
{
   static const unsigned int index = I;
   using type = T;
};

// The functor invoker: inherits from a list of base classes.
// The constructor of each of these classes invokes the input
// functor with one of the arguments in the pack.
template<typename... Ts>
struct invoker : public invoker_base<Ts::index, typename Ts::type>...
{
   template<typename F, typename... Us>
   invoker(F&& f, Us&&... args):
   invoker_base<Ts::index, typename Ts::type>(std::forward<F>(f), std::forward<Us>(args))...
   {
   }
};

} // namespace detail

//
// The functor provided in the first argument is invoked for each
// argument in the pack whose index is contained in the index list
// specified in the second argument
//
template<typename F, unsigned... Is, typename... Ts>
void for_each_in_arg_pack_subset(F&& f, meta::index_list<Is...> const& i, Ts&&... args)
{
//
// Constructors of invoker's sub-objects will invoke the functor.
// Note that argument types must be paired with numbers because the
// implementation is based on inheritance, and one class cannot
// inherit the same base class twice.
//
detail::invoker<detail::indexed_type<Is, meta::Nth_type_of<Is, Ts...> >...> invoker(
              f,
              (util::nth_value_of<Is>(std::forward<Ts>(args)...))...
              );
}

//
// The functor provided in the first argument is invoked for each
// argument in the pack
//
template<typename F, typename... Ts>
void for_each_in_arg_pack(F&& f, Ts&&... args)
{
   for_each_in_arg_pack_subset(f, meta::index_range<0, sizeof...(Ts)>(), std::forward<Ts>(args)...);
}

//
// apply functor on each argument in pack that satisfies a predicate
//
template<class F, class Pred, typename... Ts,
   class Index = meta::index_list_if<Pred,Ts...> >
void for_each_in_arg_pack_if(F&& f, Pred const& p, Ts&&... args)
{
   for_each_in_arg_pack_subset(f, Index(), std::forward<Ts>(args)...);
}


} // namespace util
} // namespace libmda

#endif /* LIB_FORWARD_H_INCLUDED */
