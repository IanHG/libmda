#ifndef LIBMDA_IMDA_H
#define LIBMDA_IMDA_H

#include<iostream>
#include<typeinfo>
#include<math.h>
#include"meta/check_type_.h"
#include"meta/std_wrappers.h"
#include"util/for_loop_expand.h"
#include"util/has_member.h"
#include"util/Requesting.h"
#include"basic_using.h"

template<class A>
struct traits;

namespace libmda
{
/**
*
* empty struct base struct
*
***/
struct IMDABase 
{ 
};

////
// mixin that provides the self() function to use in other mixins
//
///
template<class A, class trait>
struct IMDASelf: trait
{
   //using base_type  = trait;
   //using type       = Type<trait>;
   //using value_type = Value_type<trait>;
   //using size_type  = Size_type<trait>;
   ////static const int order = Order<trait>();
   //static const int order = trait::order;
   
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

   //protected:
   //   IMDASelf() = default;
   //   IMDASelf& operator=(const IMDASelf&) = default;
};

// mixin that provides basic typedefs and the two basic functions
// size()  : which returns total size of mda
// extent<N>(): which returns number of elements in dimension N
template<class A>
struct IMDADim: A
{
   //using base_type  = A;
   //using type       = Type<A>;
   //using value_type = Value_type<A>;
   //using size_type  = Size_type<A>;
   ////static const int order = Order<A>();
   static const int order = A::order;

   //size_type size() const { return this->self().size(); }
   //
   //template<int N, meta::iEnable_if<(N<order)> = 0 >
   //size_type extent() const { return this->self().template extent<N>(); }
   
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
          , meta::iEnable_if<(N<order)> = 0  // <- this could be removed to get rid of dependence on order
          >
   auto extent() const 
      -> decltype(std::declval<B>().self().template extent<N>())
   { 
      return this->self().template extent<N>(); 
   }
};

// mixin that provides access to elements via the at function
// at(i1,...,in): return element at with index i1,...,in
// RefAccess: switches between access by refence and access by value
#define LIBMDA_REFACCESS true
#define LIBMDA_VALUEACCESS false
constexpr bool Ref_access()   { return LIBMDA_REFACCESS;  }
constexpr bool Value_access() { return LIBMDA_VALUEACCESS; }

template<bool RefAccess, class A>
struct IMDAAccess;

template<class A>
struct IMDAAccess<LIBMDA_REFACCESS,A>: A
{
   typedef A base_type;
   typedef Type<A>       type;
   typedef Value_type<A> value_type;
   typedef Size_type<A>  size_type;
   static const int order = A::order;
   
   //
   // ref at
   //
   template<class... Is
          , class B = A
          , util::Requesting_elem<order,size_type,Is...> = 0
          >
   auto at(const Is... is)
      -> decltype(std::declval<B>().self().at(is...))
   { 
      return this->self().at(is...); 
   }

   //
   // ref at const
   //
   template<class... Is
          , class B = A
          , util::Requesting_elem<order,size_type,Is...> = 0
          >
   auto at(const Is... is) const
      -> decltype(std::declval<const B>().self().at(is...))
   { 
      return this->self().at(is...); 
   }
};

template<class A>
struct IMDAAccess<LIBMDA_VALUEACCESS,A>: A
{
   typedef A base_type;
   typedef Value_type<A> value_type;
   typedef Size_type<A>  size_type;
   static const int order = A::order;
   
   //
   // at const
   //
   template<class... Is
          , class B = A
          , util::Requesting_elem<order,size_type,Is...> = 0
          >
   auto at(const Is... is) const 
      -> decltype(std::declval<const B>().self().at(is...))
   { 
      return this->self().at(is...); 
   }
};

// mixin that combines ref-access and non-refaccess
template<class A>
struct IMDAAccessComb: A { };

// mixin that promises self, size, dim, and at
template<class A>
struct IMDABasic: A { };

// mixin that provides access in vectorized form if available
// for speeding up sequntial access operations
// NB: not fully implemented/tested!
template<bool Ref, class A>
struct IMDAVecAccess;

template<class A>
struct IMDAVecAccess<LIBMDA_REFACCESS,A>: A
{
   typedef A base_type;
   typedef Value_type<A> value_type;
   typedef Size_type<A>  size_type;
   static const int order = A::order;
   value_type const& vec_at(const size_type i) const { return this->self().vec_at(i); }
   value_type&       vec_at(const size_type i)       { return this->self().vec_at(i); }
};

template<class A>
struct IMDAVecAccess<LIBMDA_VALUEACCESS,A>: A
{
   typedef A base_type;
   typedef Value_type<A> value_type;
   typedef Size_type<A>  size_type;
   static const int order = A::order;
   value_type vec_at(const size_type i) const { return this->self().vec_at(i); }
};

template<class A>
struct IMDAVecAccessComb: A { };
// vec access end

// make structs with operators:
// =, +=, -=, *=, /=
// for element by element operations
// these are used by assign mixins
#define LIBMDA_CREATE_EQUALOPER(NAME,OP) \
struct NAME \
{ \
   template<typename V, typename U, typename... ints> \
   static void apply(V& v, const U& u, const ints... i) \
   { v.at(i...) OP u.at(i...); } \
  \
   /*template<typename V, typename U, class meta::Enable_if<util::has_vec_at<V>::value && util::has_vec_at<U>::value> > */\
   /*static void apply_vec(V& v, const U& u, const typename V::size_type i) */\
   /*{ v.vec_at(i) OP u.vec_at(i); }*/ \
};

LIBMDA_CREATE_EQUALOPER(op_equal,=)
LIBMDA_CREATE_EQUALOPER(op_plus_equal,+=)
LIBMDA_CREATE_EQUALOPER(op_sub_equal,-=)
LIBMDA_CREATE_EQUALOPER(op_mult_equal,*=)
LIBMDA_CREATE_EQUALOPER(op_div_equal,/=)
#undef LIBMDA_CREATE_EQUALOPER

struct equal_functor
{
   template<class V, class U, class... ints>
   void operator()(V&& v, U&& u, ints... i) const
   { v.at(i...) = u.at(i...); }
};

// mixin that provides =, +=, -= operator overloads
template<class dims_check, class A>
struct IMDAElemAssign: A
{
   using base_type = A;
   using type      = Type<A>;
   using size_type = Size_type<A>;

   // does below function work/get called???!??? (ian: I think maybe not)
   type& operator=(const type& v) 
   {
      // CHECK FOR SELF ASSIGNMENT?? :O
      if(this!=&v)
      {
         dims_check::apply(*this,v);
         util::for_loop_expand<op_equal>::apply((*this),v);
      }
      return this->self();
   }
   template<typename B>
      //meta::iEnable_if<!(util::has_vec_at<A>::value && util::has_vec_at<B>::value)> = 0 >
   type& operator=(const IMDAAccessComb<B>& v)
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
   template<typename B>
   type& operator+=(const IMDAAccessComb<B>& v)
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_plus_equal>::apply((*this),v);
      return this->self();
   }
   template<typename B>
   type& operator-=(const IMDAAccessComb<B>& v)
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_sub_equal>::apply((*this),v);
      return this->self();
   }
};

//
// mixin that provides *=,/= operator overloads
//
template<class dims_check, class A>
struct IMDAElemAssignMult: A
{
   using base_type = A;
   using type      = Type<A>;
   using size_type = Size_type<A>;
   using A::operator=;

   template<class B>
   type& operator*=(const IMDAAccessComb<B>& v)
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_mult_equal>::apply((*this),v);
      return this->self();
   }
   template<class B>
   type& operator/=(const IMDAAccessComb<B>& v)
   {
      dims_check::apply(*this,v);
      util::for_loop_expand<op_div_equal>::apply((*this),v);
      return this->self();
   }
};

} // namespace libmda

#endif /* LIBMDA_IMDA_H */
