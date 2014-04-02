#ifndef LIBMDA_IMDA_BASIC_H_INCLUDED
#define LIBMDA_IMDA_BASIC_H_INCLUDED

// libmda headers
#include"../meta/std_wrappers.h"
#include"../util/Requesting.h"
#include"../util/enforce.h"
#include"../basic_using.h"

namespace libmda
{

namespace imda
{

//
// empty struct base struct
//
struct base
{ 
};


//
// mixin that provides the self() function to use in other mixins
//
template<class A, class trait>
struct selfish: trait
{
   //
   // self()
   //
   A& self()
   { 
      return static_cast<A&>(*this); 
   }

   //
   // self() const
   //
   A const& self() const
   { 
      return static_cast<A const&>(*this); 
   }
};


//
// mixin that provides basic typedefs and the two basic functions
// size()  : which returns total size of mda
// extent<N>(): which returns number of elements in dimension N
//
template<class A>
struct dimension: A
{
   //
   // size
   //
   template<class B = A>
   auto size() const 
      -> decltype(std::declval<B>().self().size()) 
   { 
      return this->self().size(); 
   }
   
   //
   // extent
   // 
   template<int N
          , class B = A
          , util::Enforce_order_bound<A,N> = 0
          >
   auto extent() const 
      -> decltype(std::declval<B>().self().template extent<N>())
   { 
      return this->self().template extent<N>(); 
   }
};

} // namespace imda
} // namespace libmda

#endif /* LIBMDA_IMDA_BASIC_H_INCLUDED */
