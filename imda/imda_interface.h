#ifndef LIBMDA_IMDA_INTERFACE_H_INCLUDED
#define LIBMDA_IMDA_INTERFACE_H_INCLUDED

#include"imda_basic.h"
#include"imda_access.h"
#include"imda_assign.h"
#include"imda_assign_scalar.h"
#include"imda_ostream_output.h"
#include"../util/index_check.h"
//#include"../util/enforce.h"

namespace libmda
{
namespace imda
{

//   
// mixin that promises basic mda functionality:
//    self, size, dim, and reference access at
//
template<class A
       , class trait
       , bool ref_access = Ref_access()
       >
struct ibasic: 
   access_combined<
   access         <ref_access,
   dimension      <
   selfish        <
   A, trait
   > > > >,
   base
{ 
};

//   
// mixin that promises basic mda functionality
// with assignment operators
//
template<class A
       , class trait
       , bool ref_access = Ref_access()
       >
struct iextended:
   elem_assign    <util::index_nocheck,
   elem_assign_div<util::index_nocheck,
   elem_assign_mul<util::index_nocheck,
   elem_assign_sub<util::index_nocheck,
   elem_assign_add<util::index_nocheck,
   ibasic         <
   A, trait, ref_access
   > > > > > >
{
   template<class T
          , class C = A
          >
   auto operator=(const T& t)
      //-> decltype(std::declval<C>().self().assign(std::forward<T>(t)))
      -> decltype(std::declval<C>().self().assign(t))
   {
      //return this->self().assign(std::forward<T>(t));
      return this->self().assign(t);
   }
};

//
// mixin providing basic functionailities, assignment, AND scalar assignment
//
//
template<class A
       , class trait
       , bool ref_access = Ref_access()
       >
struct iextended_scalar:
   elem_assign_scalar    <
   elem_assign_add_scalar<
   elem_assign_sub_scalar<
   elem_assign_mul_scalar<
   elem_assign_div_scalar<
   iextended<
   A, trait, ref_access
   > > > > > >
{
   using iextended<A, trait, ref_access>::operator=;

   template<class T
          , class C = A
          >
   auto operator=(const T& t)
      //-> decltype(std::declval<C>().self().assign_scalar(std::forward<T>(t)))
      -> decltype(std::declval<C>().self().assign_scalar(t))
   {
      //return this->self().assign_scalar(std::forward<T>(t));
      return this->self().assign_scalar(t);
   }
};

} // namespace imda
} // namespace libmda

#endif /* LIBMDA_IMDA_INTERFACE_H_INCLUDED */
