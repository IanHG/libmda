#ifndef LIBMDA_IMDA_ASSIGN_H_INCLUDED
#define LIBMDA_IMDA_ASSIGN_H_INCLUDED

#include "imda_access.h"
#include "imda_operators.h"
#include "../util/for_loop_expand.h"

namespace libmda
{

namespace imda
{

//
// mixin that provides = operator overloads
//
template<class dims_check, class A>
struct elem_assign: A
{
   //
   // operator=
   //
   // does below function work/get called???!??? (ian: I think maybe not)
   //template<class C = A>
   //auto operator=(const type& v)
   //   -> decltype(std::declval<C>().self())
   //{
   //   // CHECK FOR SELF ASSIGNMENT?? :O
   //   if(this!=&v)
   //   {
   //      dims_check::apply(*this,v);
   //      util::for_loop_expand<op_equal>::apply((*this),v);
   //   }
   //   return this->self();
   //}
   
   //
   // operator=
   //
   template<class B
          , class C = A
          >
   auto operator=(const access_combined<B>& v)
      -> decltype(std::declval<C>().self())
   {
      dims_check::apply(*this,v);
      //util::for_loop_expand<op_equal>::apply((*this),v);
      util::for_each_elem(equal_functor(),(*this),v);
      return this->self();
   }
   //template<typename B, 
   //   meta::iEnable_if<(util::has_vec_at<A>::value && util::has_vec_at<B>::value)> = 0 >
   //type& operator=(const IMDAVecAccessComb<B>& v)
   //{
   //   //cout << " using VEC ASSIGNER " << endl;
   //   dims_check::apply(*this,v);
   //   for(size_type i = 0; i < this->self().size(); ++i)
   //      this->self().vec_at(i) = v.vec_at(i);
   //   return this->self();
   //}
};

//
// mixin that provides += operator overloads
//
template<class dims_check, class A>
struct elem_assign_add: A
{
   template<class B
          , class C = A
          >
   auto operator+=(const access_combined<B>& v)
      -> decltype(std::declval<C>().self())
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_plus_equal>::apply((*this),v);
      return this->self();
   }
};

//
// mixin that provides -= operator overloads
//
template<class dims_check, class A>
struct elem_assign_sub: A
{
   template<class B
          , class C = A
          >
   auto operator-=(const access_combined<B>& v)
      -> decltype(std::declval<C>().self())
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_sub_equal>::apply((*this),v);
      return this->self();
   }
};

//
// mixin that provides *= operator overload
//
template<class dims_check, class A>
struct elem_assign_mul: A
{
   template<class B
          , class C = A
          >
   auto operator*=(const access_combined<B>& v)
      -> decltype(std::declval<C>().self())
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_mult_equal>::apply((*this),v);
      return this->self();
   }
};
   
//
// mixin that provides /= operator overload
//
template<class dims_check, class A>
struct elem_assign_div: A
{
   template<class B
          , class C = A
          >
   auto operator/=(const access_combined<B>& v)
      -> decltype(std::declval<C>().self())
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_div_equal>::apply((*this),v);
      return this->self();
   }
};

} // namespace imda
} // namespace libmda

#endif /* LIBMDA_IMDA_ASSIGN_H_INCLUDED */
