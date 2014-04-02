#ifndef LIBMDA_MY_TUPLE_H_INCLUDED
#define LIBMDA_MY_TUPLE_H_INCLUDED

#include "../meta/id.h"
#include "../meta/tuple.h"

#include "print_variadic.h"
#include "type_info.h"

namespace libmda
{
namespace util
{

//
// my tuple implementation
//
template<size_t Idx, class T>
struct my_tuple_elem
{
   using This_ = my_tuple_elem<Idx,T>;
   using Head_ = T;
   
   static constexpr Head_& head_(This_& t) noexcept { return t._t; }
   static constexpr const Head_& head_(const This_& t) noexcept { return t._t; }

   //explicit constexpr my_tuple_elem(const T& t): _t(t)
   //{
   //}

   template<class TT>
   explicit constexpr my_tuple_elem(TT&& t): _t(std::forward<TT>(t))
   {
   }
   
   private:
      T _t;
};


template<size_t Idx, class T, class... Ts>
struct my_tuple_impl: public my_tuple_impl<Idx+1,Ts...>
                    , private my_tuple_elem<Idx,T>
{
   using This_ = my_tuple_impl<Idx,T,Ts...>;
   using Next_ = my_tuple_impl<Idx+1,Ts...>;
   using Elem_ = my_tuple_elem<Idx,T>;
   using Head_ = typename Elem_::Head_;

   static constexpr Next_& next_(This_& t) noexcept { return t; }
   static constexpr const Next_& next_(const This_& t) noexcept { return t; }
   static constexpr Elem_& elem_(This_& t) noexcept { return t; }
   static constexpr const Elem_& elem_(const This_& t) noexcept { return t; }
   static constexpr Head_& head_(This_& t) noexcept { return Elem_::head_(t); }
   static constexpr const Head_& head_(const This_& t) noexcept { return Elem_::head_(t); }

   //constexpr my_tuple_impl(const my_tuple_impl&) = default;

   template<class TT
          , class... TTs
          , meta::iEnable_if<sizeof...(TTs) == sizeof...(Ts)> = 0
          >
   explicit constexpr my_tuple_impl(TT&& t, TTs&&... ts): 
        Elem_(std::forward<TT>(t))
      , Next_(std::forward<TTs>(ts)...)
   {
   }
};

template<size_t Idx, class T>
struct my_tuple_impl<Idx,T>: private my_tuple_elem<Idx,T>
{
   using This_ = my_tuple_impl<Idx,T>;
   using Elem_ = my_tuple_elem<Idx,T>;
   using Head_ = typename Elem_::Head_;

   static constexpr Elem_& elem_(This_& t) noexcept { return t; }
   static constexpr const Elem_& elem_(const This_& t) noexcept { return t; }
   static constexpr Head_& head_(This_& t) noexcept { return Elem_::head_(t); }
   static constexpr const Head_& head_(const This_& t) noexcept { return Elem_::head_(t); }

   //constexpr my_tuple_impl(const my_tuple_impl&) = default;
   
   template<class TT>
   explicit constexpr my_tuple_impl(TT&& t): 
      Elem_(std::forward<TT>(t))
   {
   }
};

///////
//
// my tuple interface
//
///////
template<class... Ts>
struct my_tuple: my_tuple_impl<0,Ts...>, libmda::meta::tuple<Ts...>
{
   using This_ = my_tuple<Ts...>;
   using Impl_ = my_tuple_impl<0,Ts...>;

   //constexpr my_tuple(const my_tuple&) = default;
  
   template<class... TTs
          , meta::iEnable_if<sizeof...(TTs) == sizeof...(Ts)> = 0
          >
   explicit constexpr my_tuple(TTs&&... ts): 
        Impl_(std::forward<TTs>(ts)...)
   {
   }
};

template<class... Ts>
my_tuple<Ts...> make_my_tuple(Ts&&... ts)
{
   //std::cout << " IN MAKE TUPLE " << std::endl;
   //print_variadic(std::cout,"\n",typeof(ts)...);
   //std::cout << std::endl;
   return my_tuple<Ts...>(std::forward<Ts>(ts)...);
}

//
// my tuple size
//
template<class Tuple>
struct my_tuple_size;
template<class... Ts>
struct my_tuple_size<my_tuple<Ts...> >:
   std::integral_constant<std::size_t,sizeof...(Ts)>
{
};

//
// my tuple element implementation
//
namespace detail
{

template<size_t I, class Tuple>
struct my_tuple_element_impl;

template<size_t I, class T, class... Ts>
struct my_tuple_element_impl<I,my_tuple<T,Ts...> >:
   my_tuple_element_impl<I-1,my_tuple<Ts...> >
{
};

template<class T, class... Ts>
struct my_tuple_element_impl<0,my_tuple<T,Ts...> >:
   meta::detail::id<T>
{
};

template<size_t I, class Tuple>
struct my_tuple_element_impl<I,const Tuple>:
   meta::detail::id<const typename my_tuple_element_impl<I,Tuple>::type>
{
}; 

} /* namespace detail */ 

template<size_t I, class Tuple>
using my_tuple_element = typename detail::my_tuple_element_impl<I,Tuple>::type;


//
// get implementation
//
namespace detail
{

template<size_t I, class T, class... Ts>
constexpr  
typename std::add_lvalue_reference<T>::type
get_helper(my_tuple_impl<I,T,Ts...>& t) noexcept
{
   return my_tuple_impl<I,T,Ts...>::head_(t);
}

template<size_t I, class T, class... Ts>
constexpr
typename std::add_lvalue_reference<typename std::add_const<typename std::decay<T>::type>::type>::type
get_helper(const my_tuple_impl<I,T,Ts...>& t) noexcept
{
   return my_tuple_impl<I,T,Ts...>::head_(t);
}

} /* namespace detail */

template<size_t I, class... Ts>
constexpr 
typename std::add_lvalue_reference<my_tuple_element<I,my_tuple<Ts...> > >::type
get(my_tuple<Ts...>& t) noexcept
{
   return detail::get_helper<I>(t);
}

template<size_t I, class... Ts>
constexpr 
typename std::add_lvalue_reference<typename std::add_const<typename std::decay<my_tuple_element<I,my_tuple<Ts...> > >::type >::type>::type
get(const my_tuple<Ts...>& t) noexcept
{
   return detail::get_helper<I>(t);
}

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_MY_TUPLE_H_INCLUDED */
