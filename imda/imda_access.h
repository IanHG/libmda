#ifndef LIBMDA_IMDA_ACCESS_H_INCLUDED
#define LIBMDA_IMDA_ACCESS_H_INCLUDED

#include "../basic_using.h"

namespace libmda
{

namespace imda
{

//
// functions for denoting access by reference and access by value
//
constexpr bool Ref_access()   
{ 
   return true;  
}

constexpr bool Value_access() 
{ 
   return false; 
}

//
// mixin that provides access to elements via the at function
// at(i1,...,in): return element at with index i1,...,in
// RefAccess: switches between access by refence and access by value
//
template<bool RefAccess, class A>
struct access;

//
// access by reference
//
template<class A>
struct access<Ref_access(),A>: A
{
   //
   // ref at
   //
   template<class... Is
          , class B = A
          //, util::Requesting_elem<order,size_type,Is...> = 0
          >
   auto at(Is... is)
      -> decltype(std::declval<B>().self().at(is...))
   { 
      return this->self().at(is...); 
   }

   //
   // ref at const
   //
   template<class... Is
          , class B = A
          //, util::Requesting_elem<order,size_type,Is...> = 0
          >
   auto at(Is... is) const
      -> decltype(std::declval<const B>().self().at(is...))
   { 
      return this->self().at(is...); 
   }
};

//
// access by value
//
template<class A>
struct access<Value_access(),A>: A
{
   //
   // at const
   //
   template<class... Is
          , class B = A
          //, util::Requesting_elem<order,size_type,Is...> = 0
          >
   auto at(Is... is) const 
      -> decltype(std::declval<const B>().self().at(is...))
   { 
      return this->self().at(is...); 
   }
};

//
// mixin that combines ref-access and non-refaccess
//
template<class A>
struct access_combined: A 
{
};

//
// mixin that provides access in vectorized form if available
// for speeding up sequntial access operations
// NB: not fully implemented/tested!
//
template<bool Ref, class A>
struct vec_access;

//
// vector access by reference
//
template<class A>
struct vec_access<Ref_access(),A>: A
{
   //
   // vec_at 
   //
   template<class I
          , class B = A
          >
   auto vec_at(I i) 
      -> decltype(std::declval<B>().self().vec_at(i))
   { 
      return this->self().vec_at(i); 
   }
   
   //
   // vec_at const
   //
   template<class I
          , class B = A
          >
   auto vec_at(I i) const 
      -> decltype(std::declval<const B>().self().vec_at(i))
   { 
      return this->self().vec_at(i); 
   }
};

//
// vector access by value
//
template<class A>
struct vec_access<Value_access(),A>: A
{
   //
   // vec_At const
   //
   template<class I
          , class B = A
          >
   auto vec_at(I i) const 
      -> decltype(std::declval<const B>().self().vec_at(i))
   { 
      return this->self().vec_at(i); 
   }
};

//
// vector access combined
//
template<class A>
struct vec_access_combined: A 
{ 
};

} // namespace imda
} // namespace libmda

#endif /* LIBMDA_IMDA_ACCESS_H_INCLUDED */
