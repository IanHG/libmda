#ifndef LIBMDA_CHAREXPRESSION_H
#define LIBMDA_CHAREXPRESSION_H

#include<iostream>

#include"../IMDA.h"
#include"../basic_using.h"
#include"../metaprog/check_type_.h"
#include"../metaprog/nth_type_of.h"
#include"../metaprog/std_wrappers.h"
#include"../metaprog/tuple.h"
#include"../metaprog/unique.h"
#include"../utility/for_loop_expand.h"
#include"../utility/get_argument_n.h"
#include"find_positions.h"
#include"cindex.h"
#include"check_cindicies.h"

namespace libmda
{
namespace char_expr
{

template<class A>
using Index_tuple = typename A::index_tuple;

template<class A>
struct traits;

template<class A>
struct char_expr_traits
{
   using traits_type = traits<A>;
   using value_type  = Value_type<traits_type>; 
   using size_type   = Size_type<traits_type>;
   using type        = A;
   using index_tuple = metaprog::tuple<>;
   static const int order = traits_type::order;
};

template<class A, class trait>
struct char_expression_base:
   libmda::IMDADim<
   libmda::IMDASelf<
   A, trait
   > >
{ 
   using char_expr_traits_type = char_expr_traits<A>;
   using index_tuple = Index_tuple<char_expr_traits_type>;
};

/**
 * Access to char expressions... these are different from ordinary access
 **/
template<bool RefAccess, class A>
struct char_expression_access;

template<class A>
struct char_expression_access<Ref_access(),A>: A
{
   using base_type  = A;
   using value_type = Value_type<A>;
   using size_type  = Size_type<A>;
   static const int order = Order<A>();

   template<typename... ints, 
            //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
            //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
            utility::Requesting_elem<order,size_type, ints...> = 0>
   value_type& at(const ints ...i) { return this->self().at(i...); }

   template<typename... ints, 
            //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
            //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
            utility::Requesting_elem<order,size_type, ints...> = 0>
   value_type const& at(const ints ...i) const { return this->self().at(i...); }  
};

template<class A>
struct char_expression_access<Value_access(),A>: A
{
   using base_type  = A;
   using value_type = Value_type<A>;
   using size_type  = Size_type<A>;
   static const int order = Order<A>();

   template<typename... ints, 
            //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
            //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
            utility::Requesting_elem<order,size_type, ints...> = 0>
   value_type at(const ints ...i) const { return this->self().at(i...); }  
};

template<class A>
struct char_expression_access_comb: A
{ using base_type = A; };

/*******************************/
// forward declaration of some operators to use in assignment
/*******************************/
template<typename L, typename R>
struct op_equal;
template<typename L, typename R>
struct op_plus_equal;
template<typename L, typename R>
struct op_sub_equal;

template<class A>
struct char_expression_assign: A  // builds on char_expression_access <true>
{
   typedef A base_type;
   typedef typename A::type      type;
   typedef typename A::size_type size_type;

   type& operator=(const type& other)
   {
      using oper_type = op_equal<type,type>;
      utility::for_loop_expand<oper_type>::apply((*this),other);
      return this->self();
   }
   template<class B>
   type& operator=(const char_expression_access_comb<B>& other)
   {
      using oper_type = op_equal<type,B>;
      static_assert(oper_type::is_valid, "operation= not valid");
      utility::for_loop_expand<oper_type>::apply((*this),other);
      return this->self();
   }
   template<class B>
   type& operator+=(const char_expression_access_comb<B>& other)
   {
      using oper_type = op_plus_equal<type,B>;
      static_assert(oper_type::is_valid, "operation+= not valid");
      utility::for_loop_expand<oper_type>::apply((*this),other);
      return this->self();
   }
   template<class B>
   type& operator-=(const char_expression_access_comb<B>& other)
   {
      using oper_type = op_sub_equal<type,B>;
      static_assert(oper_type::is_valid, "operation-= not valid");
      utility::for_loop_expand<oper_type>::apply((*this),other);
      return this->self();
   }
};


/*******************************/
// class defining a character expression
/*******************************/
template<class A>
struct char_expression: A
{ using base_type = A; };

template<class A, typename... cIndicies>
class mda_char_expression:
   public char_expression_assign<
          char_expression<
          char_expression_access_comb<
          char_expression_access<Ref_access(),
          char_expression_base<
          mda_char_expression<A, cIndicies...>, traits<mda_char_expression<A,cIndicies...> >
          > > > > >
{
   private:
      typedef A expr_type;
   
   private:
      //ichar_expression<expr_type>& m_object;
      expr_type& m_object;

   public:
   typedef char_expression_assign<
           char_expression<
           char_expression_access_comb<
           char_expression_access<Ref_access(),
           char_expression_base<
           mda_char_expression<A, cIndicies...>, traits<mda_char_expression<A,cIndicies...> >
           > > > > > interface_type;
      using interface_type::operator=;
      typedef libmda::metaprog::tuple<cIndicies...>   index_tuple;
      /*typedef typename traits<typename A::type>::value_type value_type;
      typedef typename traits<typename A::type>::size_type  size_type;
      typedef typename traits<typename A::type>::type       type;
      enum{ order = traits<typename A::type>::order };*/
      
      using value_type = Value_type<A>;
      using size_type  = Size_type<A>;
      using type       = Type<A>;
      static const int order = Order<A>();
      
      // constructor
      mda_char_expression(expr_type& a_object): m_object(a_object) { };
      
      // assignment operator
      mda_char_expression& operator=(const mda_char_expression& a_other)
      { return interface_type::operator=(a_other); }
      
      // const and non-const at()
      template<typename... ints,
               //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
               //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               utility::Requesting_elem<order,size_type, ints...> = 0>
      value_type const& at(const ints... i) const { return m_object.at(i...); }
      template<typename... ints,
               //typename std::enable_if<metaprog::check_type_and_size_<order,size_type,ints...>::value, int>::type = 0>
               //iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               utility::Requesting_elem<order,size_type, ints...> = 0>
      value_type&       at(const ints... i)       { return m_object.at(i...); }
      
      // size()
      size_type size() const { return m_object.size(); }
      
      // extent()
      template<int N>
      size_type extent()  const { return m_object.template extent<N>(); }
};


/******************************/
// struct with interface function
/******************************/
template<class A>
struct char_expression_interface: A
{  
   /* non-const version */
   template<class... cints, 
            iEnable_if<utility::detail::requesting_slice<Order<A>(),cints...>::value> = 0>
            //utility::Requesting_slice<Order<A>(),cints...> = 0>
   mda_char_expression<Type<A>, cints...> c_expr(const cints... ci)
   { 
      typedef mda_char_expression<Type<A>, cints...> Charexpr_type;
      return Charexpr_type(this->self());
   }
   
   /* const version */
   template<class... cints, 
            iEnable_if<utility::detail::requesting_slice<Order<A>(),cints...>::value> = 0>
            //utility::Requesting_slice<Order<A>(),cints...> = 0>
   mda_char_expression<const Type<A>, cints...> c_expr(const cints... ci) const
   { 
      typedef mda_char_expression<const Type<A>, cints...> Charexpr_type;
      return Charexpr_type(this->self());
   }

   /* non-const version */
   template<class... cints, 
            iEnable_if<utility::detail::requesting_slice<Order<A>(),cints...>::value> = 0>
            //utility::Requesting_slice<Order<A>(),cints...> = 0>
   mda_char_expression<Type<A>, cints...> operator()(const cints... ci)
   { 
      typedef mda_char_expression<Type<A>, cints...> Charexpr_type;
      return Charexpr_type(this->self());
   }
   
   /* const version */
   template<class... cints, 
            iEnable_if<utility::detail::requesting_slice<Order<A>(),cints...>::value> = 0>
            //utility::Requesting_slice<Order<A>(),cints...> = 0>
   mda_char_expression<const Type<A>, cints...> operator()(const cints... ci) const
   { 
      typedef mda_char_expression<const Type<A>, cints...> Charexpr_type;
      return Charexpr_type(this->self());
   }

};

//template<class A, class trait>
//struct ichar_expression:
//   char_expression_interface<
//   libmda::IMDAAccessComb<
//   libmda::IMDAAccess<Ref_access(),
//   libmda::IMDADim<
//   libmda::IMDASelf<
//   A, trait
//   > > > > >
//{  
//   typedef char_expression_interface<
//           libmda::IMDAAccessComb<
//           libmda::IMDAAccess<Ref_access(),
//           libmda::IMDADim<
//           libmda::IMDASelf<
//           A, trait
//           > > > > > imda_interface;
//   
//   template<typename... cints, 
//            utility::Requesting_slice<Order<A>(),cints...> = 0>
//   mda_char_expression<Type<imda_interface>, cints...>
//   operator()(const cints... ci) { return imda_interface::c_expr(ci...); }
//   
//   template<typename... cints, 
//            utility::Requesting_slice<Order<A>(),cints...> = 0>
//   mda_char_expression<const Type<imda_interface>, cints...>
//   operator()(const cints... ci) const { return imda_interface::c_expr(ci...); }
//   
//   //template<class... cints, metaprog::iEnable_if<check_cindicies_<cints...>::value> = 0>
//   //mda_char_expression<Type<imda_interface>, cints...>
//   //operator()(const cints... ci) const
//   //{ return imda_interface::c_expr(ci...); }
//};

/****************************************/
// char permutation struct + helpers
/****************************************/
template<class B, class E, size_t N>
struct is_permutation_help_impl
{
   static const bool value = (deref<B>::value < N) && (deref<B>::value >= 0)
      && is_permutation_help_impl<next<B>,E,N>::value;
};
template<class E, size_t N>
struct is_permutation_help_impl<E,E,N>
{
   static const bool value = true;
};

template<class T>
struct is_permutation_help: is_permutation_help_impl<begin<T>, end<T>, T::Size()>
{ };

template<class T>
struct is_permutation_
{
   static const bool value = metaprog::All_unique<T>() && is_permutation_help<T>::value;
};

template<class T> struct tuple_overlap
{
   template<class U> struct apply
   {
      static const bool value = (metaprog::Find_pos<T,U>() != T::Size());
   };
};

template<class l_index_tuple, class r_index_tuple>
struct permutation_
{
   // assert that indicies are unique at this point (else there is an error!)
   static_assert(metaprog::All_unique<l_index_tuple>(),"permutation_: left  indicies not unique");
   static_assert(metaprog::All_unique<r_index_tuple>(),"permutation_: right indicies not unique");

   /********************************/
   // addition/subtration functions
   //
   /********************************/
   // find how r_indicies are a permution of l_indicies (used for addition and subtraction!)
   using permutation_tuple = metaprog::find_positions<l_index_tuple,r_index_tuple>;
   // see if addition/subtraction is valid (r_index_tuple is a permutation of l_index_tuple)
   static const bool is_permutation = (l_index_tuple::size == r_index_tuple::size)
      && is_permutation_<permutation_tuple>::value;
   

   /********************************/
   // contraction(multiplication) functions
   //
   /********************************/
   private:
   // find overlap between left and right indicies (which indicies to contract)
   using partition_l = metaprog::partition<l_index_tuple,tuple_overlap<r_index_tuple> >;
   using partition_r = metaprog::partition<r_index_tuple,tuple_overlap<l_index_tuple> >;
   
   public:
   // create tuple of indicies to contract
   using contract_tuple = typename partition_l::t; // same as partition_r::t (maybe different permutation)

   // create tuple of indicies for result of contraction 
   // (all indicies that do not overlap between left and right indicies)
   using index_tuple = metaprog::catenate<typename partition_l::f, typename partition_r::f>;

   // create a tuple of result and contraction indicies
   // index_tuple first and then contract_tuple
   using full_contraction_tuple = metaprog::catenate<index_tuple,contract_tuple>;

   // find permutation of contraction indicies 
   using contract_index_perm = metaprog::find_positions<l_index_tuple,contract_tuple>;
   //using contract_index_perm = libmda::metaprog::find_positions<full_contraction_tuple,contract_tuple>;

   // find permutation of left indicies in full index tuple
   using l_index_perm = metaprog::find_positions<full_contraction_tuple,l_index_tuple>;
   
   // find permutation of right indicies in full index tuple
   using r_index_perm = metaprog::find_positions<full_contraction_tuple,r_index_tuple>;

   // DEBUG: functions for printing out some types
   //static void print_types(contract_index_perm=contract_index_perm(),
   //                        l_index_perm=l_index_perm(),
   //                        r_index_perm=r_index_perm())
   //static void print_types(l_index_tuple=l_index_tuple(),
   //                        r_index_tuple=r_index_tuple(),
   //                        index_tuple=index_tuple(),
   //                        contract_tuple=contract_tuple())
   //static void print_types(contract_index_perm=contract_index_perm(),
   //                        l_index_perm=l_index_perm(),
   //                        r_index_perm=r_index_perm())
   //{ cout << __PRETTY_FUNCTION__ << endl; }
};

/****************************************/
// char binary expression
//
/****************************************/
template<typename L, typename R, template<class,class> class Op>
class binary_char_expression:
   public char_expression<
          char_expression_access_comb<
          char_expression_access<Value_access(),
          char_expression_base<
          binary_char_expression<L, R, Op>, traits<binary_char_expression<L,R,Op> >
          > > > >
{
   private:
      const char_expression<L>& m_lhs;
      const char_expression<R>& m_rhs;

   public:
      //using l_index_tuple = Index_tuple<L>;
      //using r_index_tuple = Index_tuple<R>;
      //using oper_type     = Op<l_index_tuple,r_index_tuple>;
      using oper_type     = Op<L,R>;
      using index_tuple   = Index_tuple<oper_type>;
      static_assert(oper_type::is_valid, "operation not valid");
      
      using value_type = Value_type<L>;
      using size_type  = Size_type<L>;
      
      static const int order = oper_type::order;
      
      // constructor
      binary_char_expression(const char_expression<L>& a_lhs,
                             const char_expression<R>& a_rhs):
      m_lhs(a_lhs), m_rhs(a_rhs) { };
      
      // at()
      template<typename... ints
             , utility::Requesting_elem<order,size_type, ints...> = 0
             >
      value_type at(const ints... i) const { return oper_type::apply(m_lhs,m_rhs,i...); }
      
      // size()
      size_type size() const { return oper_type::size(m_lhs,m_rhs); }
      
      // extent()
      template<int N>
      size_type extent()  const { return oper_type::template extent<N>(m_lhs,m_rhs); }
};

/* ----- forward permutation ----- */
template<int pos, typename... ints>
inline metaprog::Nth_type_of<pos,ints...> forward_permutation(const ints... i)
{ return utility::get_argument_n<pos>::get(i...); }
/* ----- forward permutation end ----- */

/****************************************/
// definition of op_equal, op_plus_equal, op_sub_equal
//
/****************************************/
#define LIBMDA_CREATE_CHAR_ASSIGNOPERATOR(NAME,OP) \
template<class L, class R> \
struct NAME \
{ \
   using l_index_tuple = Index_tuple<L>; \
   using r_index_tuple = Index_tuple<R>; \
   using permutation   = permutation_<l_index_tuple,r_index_tuple>; \
   using index_tuple   = l_index_tuple; \
   static const int  order  = index_tuple::size; \
   static const bool is_valid = permutation::is_permutation; \
   \
   template<typename LH, typename RH, typename... Indicies> \
   /* template<typename... ints> */ \
   static void apply(LH& a_lhs, const RH& a_rhs, const Indicies... i) \
   { apply_help<typename permutation::permutation_tuple>::apply(a_lhs, a_rhs,i...); } \
   \
   /*template<int N, typename LH, typename RH>*/ \
   /*static typename LH::size_type extent(const LH& a_lhs, const RH& a_rhs)*/ \
   /*{ return a_lhs.template extent<N>(); } */ \
   \
   private: \
      template<typename Tuple> \
      struct apply_help; \
      template<typename ...Perm> \
      struct apply_help<libmda::metaprog::tuple<Perm...> > \
      { \
         template<typename LH, typename RH, typename... ints> \
         static void apply(LH& a_lhs, const RH& a_rhs, const ints... i) \
         { a_lhs.at(i...) OP a_rhs.at(forward_permutation<Perm::value>(i...)...); } \
      }; \
};

LIBMDA_CREATE_CHAR_ASSIGNOPERATOR(op_equal,=)
LIBMDA_CREATE_CHAR_ASSIGNOPERATOR(op_plus_equal,+=)
LIBMDA_CREATE_CHAR_ASSIGNOPERATOR(op_sub_equal,-=)
#undef LIBMDA_CREATE_CHAR_ASSIGNOPERATOR


/****************************************/
// definition of op_add, op_sub, and op_mult
//
/****************************************/
template<typename L, typename R>
struct op_add
{
   using l_index_tuple = Index_tuple<L>;
   using r_index_tuple = Index_tuple<R>;
   typedef permutation_<l_index_tuple,r_index_tuple> permutation;
   typedef l_index_tuple index_tuple;
   static const int order = index_tuple::size;

   enum{ is_valid = permutation::is_permutation };
   
   template<typename LH, typename RH, typename... Indicies>
   static typename LH::value_type 
   apply(const LH& a_lhs, const RH& a_rhs, const Indicies ...indicies)
   { 
      return apply_help<typename permutation::permutation_tuple>::
         apply(a_lhs, a_rhs,indicies...); 
   }

   template<typename Tuple>
   struct apply_help;
   template<typename ...Perm>
   struct apply_help<libmda::metaprog::tuple<Perm...> >
   {
      template<typename LH, typename RH, typename... Indicies>
      static typename LH::value_type 
      apply(const LH& a_lhs, const RH& a_rhs, const Indicies ...indicies)
      {
         //return a_lhs.at(indicies...) + a_rhs.at(forward_permutation<Perm::pos::value>(indicies...)...);
         return a_lhs.at(indicies...) + a_rhs.at(forward_permutation<Perm::value>(indicies...)...);
      }
   };
   template<int N, typename LH, typename RH>
   static typename LH::size_type extent(const LH& a_lhs, const RH& a_rhs)
   { return a_lhs.template extent<N>(); }
};

template<typename L, typename R>
struct op_sub
{
   using l_index_tuple = Index_tuple<L>;
   using r_index_tuple = Index_tuple<R>;
   typedef permutation_<l_index_tuple,r_index_tuple> permutation;
   typedef l_index_tuple index_tuple;
   static const int order = index_tuple::size;

   enum{ is_valid = permutation::is_permutation };
   
   template<typename LH, typename RH, typename... Indicies>
   static typename LH::value_type 
   apply(LH& a_lhs, const RH& a_rhs, const Indicies ...indicies)
   { 
      return apply_help<typename permutation::permutation_tuple>::
         apply(a_lhs, a_rhs,indicies...); 
   }

   template<typename Tuple>
   struct apply_help;
   template<typename ...Perm>
   struct apply_help<libmda::metaprog::tuple<Perm...> >
   {
      template<typename LH, typename RH, typename... Indicies>
      static typename LH::value_type 
      apply(LH& a_lhs, const RH& a_rhs, const Indicies ...indicies)
      {
         //return a_lhs.at(indicies...) - a_rhs.at(forward_permutation<Perm::pos::value>(indicies...)...);
         return a_lhs.at(indicies...) - a_rhs.at(forward_permutation<Perm::value>(indicies...)...);
      }
   };
   template<int N, typename LH, typename RH>
   static typename LH::size_type extent(const LH& a_lhs, const RH& a_rhs)
   { return a_lhs.template extent<N>(); }
};

template<typename L, typename R>
struct op_mult
{
   using l_index_tuple = Index_tuple<L>;
   using r_index_tuple = Index_tuple<R>;
   typedef permutation_<l_index_tuple,r_index_tuple> permutation;
   typedef typename permutation::index_tuple index_tuple;
   static const int order = index_tuple::size;

   enum{ is_valid = true };
   
   static void print_types()
   { 
      permutation::print_types();
      std::cout << __PRETTY_FUNCTION__ << std::endl; 
   }
   
   template<class tuple1, class tuple2>
   struct apply_help;
   template<typename... perm1, typename... perm2>
   struct apply_help<libmda::metaprog::tuple<perm1...>,
                     libmda::metaprog::tuple<perm2...>
          >
   {
      template<typename LH, typename RH, typename... Indicies>
      static void 
      apply(const LH& a_lhs, const RH& a_rhs,
            typename LH::value_type& contract_elem, 
            const Indicies ...indicies)
      {
         contract_elem += a_lhs.at(forward_permutation<perm1::value>(indicies...)...)
            *a_rhs.at(forward_permutation<perm2::value>(indicies...)...);
      }
   };
   
   template<typename LH, typename RH, typename... Indicies>
   static typename LH::value_type 
   apply(LH& a_lhs, const RH& a_rhs, const Indicies ...indicies)
   { 
      typename LH::value_type contract_elem=0;
      utility::for_loop_expand_dim<apply_help<typename permutation::l_index_perm,
                                     typename permutation::r_index_perm
                                  >,
                                  typename permutation::contract_index_perm
      >::apply(a_lhs,a_rhs,contract_elem,indicies...);
      return contract_elem;
   }
   
   template<int N, typename LH, typename RH>
   static typename LH::size_type extent(const LH& a_lhs, const RH& a_rhs)
   {
      typedef typename libmda::metaprog::at<index_tuple,N>::type char_index;
      return (libmda::utility::get_argument_n<
                                 (metaprog::pos<metaprog::find<r_index_tuple,char_index> >::value!=r_index_tuple::Size())
                               >::get(a_lhs,a_rhs)).template extent<
                               If<(metaprog::pos<metaprog::find<r_index_tuple,char_index> >::value!=r_index_tuple::Size()),
                                 typename libmda::metaprog::find<r_index_tuple,char_index>::pos,
                                 typename libmda::metaprog::find<l_index_tuple,char_index>::pos
                               >::value //if_ end
                               >(); // dim end
   }
};


/****************************************/
// character expression traits
//
/****************************************/
template<typename A, typename... cIndicies>
struct char_expr_traits<mda_char_expression<A,cIndicies...> >
{
   typedef traits<mda_char_expression<A,cIndicies...> > traits_type;
   typedef typename traits_type::value_type        value_type;
   typedef typename traits_type::size_type         size_type;
   typedef typename traits_type::type              type;
   static const int order = traits_type::order;
   typedef typename libmda::metaprog::tuple<cIndicies...> index_tuple;
};

template<typename L, typename R, template<class,class> class Op>
struct char_expr_traits<binary_char_expression<L,R,Op> >
{
   typedef traits<binary_char_expression<L,R,Op> > traits_type;
   typedef typename traits_type::value_type        value_type;
   typedef typename traits_type::size_type         size_type;
   typedef typename traits_type::type              type;
   static const int order = traits_type::order;
   typedef typename Op<L,R>::index_tuple index_tuple; // NB.. not pretty, but it works...
};

} // namespace char_expr

/****************************************/
// operator overloading
//
/****************************************/
template<typename L, typename R>
char_expr::binary_char_expression<L, R, char_expr::op_add> 
operator+ (const char_expr::char_expression<L>& a_lhs, 
           const char_expr::char_expression<R>& a_rhs)
{
   typedef char_expr::binary_char_expression<L, R, char_expr::op_add> expr_type;
   return expr_type( a_lhs, a_rhs );
}

template<typename L, typename R>
char_expr::binary_char_expression<L, R, char_expr::op_sub> 
operator- (const char_expr::char_expression<L>& a_lhs, 
           const char_expr::char_expression<R>& a_rhs)
{
   typedef char_expr::binary_char_expression<L, R, char_expr::op_sub> expr_type;
   return expr_type( a_lhs, a_rhs );
}

template<typename L, typename R>
char_expr::binary_char_expression<L, R, char_expr::op_mult> 
operator* (const char_expr::char_expression<L>& a_lhs, 
           const char_expr::char_expression<R>& a_rhs)
{
   typedef char_expr::binary_char_expression<L, R, char_expr::op_mult> expr_type;
   return expr_type( a_lhs, a_rhs );
}

/****************************************/
// more traits
//
/****************************************/
namespace char_expr
{

template<class A, typename... cIndicies>
struct traits<char_expr::mda_char_expression<A,cIndicies...> >
{
   //typedef typename traits<typename A::type>::value_type value_type;
   //typedef typename traits<typename A::type>::size_type  size_type;
   typedef typename A::value_type value_type;
   typedef typename A::size_type  size_type;
   typedef typename char_expr::mda_char_expression<A,cIndicies...> type;
   static const int order = A::order;
};

template<typename L, typename R, template<class,class> class Op>
struct traits<char_expr::binary_char_expression<L,R,Op> >
{
   //typedef typename traits<typename L::type>::value_type value_type;
   //typedef typename traits<typename L::type>::size_type  size_type;
   // NB NB NB NB BELOW SHOULD BE TAKEN FROM SOME HELPER STRUCT LOOK AT EXPRESSIONS FOR IDEA!
   typedef typename L::value_type value_type;
   typedef typename L::size_type  size_type;
   typedef typename char_expr::binary_char_expression<L,R,Op> type;
   static const int order = Op<L,R>::order;
};

} // namespace char_expr
} // namespace libmda

#endif /* LIBMDA_CHAREXPRESSION_H */
