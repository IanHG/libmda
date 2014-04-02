#ifndef LIBMDA_METAPROG_STD_WRAPPER_H
#define LIBMDA_METAPROG_STD_WRAPPER_H

#include <type_traits>

namespace libmda
{
namespace meta
{
namespace stdwrap
{
/***************
 *
 * Functions
 *
 ***************/
///////
// Is_same()
//
///////
template<class T, class U>
constexpr bool Is_same() 
{ return std::is_same<T,U>::value; }
static_assert( Is_same<double,double>(),"Is_same<>(): something wrong!");
static_assert(!Is_same<double,int   >(),"Is_same<>(): something wrong!");

/******************
 *
 * Non-functions
 *
 ******************/
///////
// Enable_if
//
///////
template<bool B, class T=void>
using Enable_if = typename std::enable_if<B,T>::type;

template<bool B>
using iEnable_if = typename std::enable_if<B,int>::type;

///////
// remove/ add refenrence
//
///////
template<class T>
using Remove_reference = typename std::remove_reference<T>::type;
static_assert(Is_same<double,Remove_reference<double&> >(), "Remove_reference: something wrong");

template<class T>
using Add_lvalue_reference = typename std::add_lvalue_reference<T>::type;
static_assert(Is_same<double&, Add_lvalue_reference<double> >(), "Add_lvalue_reference: something wrong");

template<class T>
using Add_rvalue_reference = typename std::add_rvalue_reference<T>::type;
static_assert(Is_same<double&&, Add_rvalue_reference<double> >(), "Add_rvalue_reference: something wrong");

///////
// remove/add const
//
///////
template<class T>
using Remove_const     = typename std::remove_const<T>::type;
static_assert(Is_same<double,Remove_const<const double> >(), "Remove_const: something wrong");
static_assert(Is_same<double,Remove_const<double const> >(), "Remove_const: something wrong");
static_assert(Is_same<double,Remove_const<double> >()      , "Remove_const: something wrong");

static_assert(Is_same<double,Remove_const<Remove_reference<const double &> > >(), "something wrong");

template<class T>
using Add_const = typename std::add_const<T>::type;
static_assert(Is_same<const double,Add_const<double> >(), "Remove_const: something wrong");
static_assert(Is_same<const double,Add_const<const double> >(), "Remove_const: something wrong");

///////
// remove/add pointer
//
///////
template<class T>
using Remove_pointer = typename std::remove_pointer<T>::type;
static_assert(Is_same<double, Remove_pointer<double*> >(), "Remove_pointer: something wrong");

template<class T>
using Add_pointer    = typename std::add_pointer<T>::type;
static_assert(Is_same<double*, Add_pointer<double> >(), "Add_pointer: something wrong");

///////
// std::decay
//
///////
template<class T>
using Decay = typename std::decay<T>::type;
static_assert(Is_same<Decay<int&>,int>(),"Decay: something wrong");

/************
 *
 * Functions
 *
 ************/
///////
// Convertible()
//
///////
template<class T, class U>
constexpr bool Convertible()
{ return std::is_convertible<T,U>::value; }

static_assert( Convertible<double,double>()       , "Convertible<>(): something wrong");
static_assert( Convertible<const double,double>() , "Convertible<>(): something wrong");
static_assert( Convertible<double&,double>()      , "Convertible<>(): something wrong");
static_assert( Convertible<const double&,double>(), "Convertible<>(): something wrong");
static_assert( Convertible<double,int>()          , "Convertible<>(): something wrong");
static_assert(!Convertible<double,int*>()         , "Convertible<>(): something wrong");

static_assert( Convertible<int, unsigned int>()       , "Convertible<>(): something wrong");


///////
// Size<>() (just use sizeof...() instead....)
//
///////
template<class... T>
constexpr size_t Size()  // NB this can give problems with the intel compiler...
{ return sizeof...(T); }
static_assert(Size<double,int>() == 2, "Size<>(): something wrong!");

///////
// All () 
//
///////
constexpr bool All()
{ return true; }

template<typename... Args>
constexpr bool All(bool b, Args... args)
{ return b && All(args...); }
static_assert( All(true,true ,true),"All<>(): something wrong!");
static_assert(!All(true,false,true),"All<>(): something wrong!");

///////
// AND() same as All()
//
///////
template<typename... Args>
constexpr bool AND(Args... args) { return All(args...); }
static_assert( AND(true,true ,true),"AND<>(): something wrong!");
static_assert(!AND(true,false,true),"AND<>(): something wrong!");
static_assert( AND(),"AND<>(): something wrong!");

///////
// OR()
//
///////
constexpr bool OR() { return false; }

template<typename... Args>
constexpr bool OR(bool b, Args... args) { return b || OR(args...); }
static_assert( OR(true ,false,false),"OR<>(): something wrong!");
static_assert(!OR(false,false,false),"OR<>(): something wrong!");
static_assert(!OR(),"OR<>(): something wrong!");

///////
// Value()
//
///////
template<class A> 
constexpr bool Value() { return A::value; }

///////////
// Is_const
//
///////////
template<class T> 
constexpr bool Is_const() { return std::is_const<T>::value; }
static_assert( Is_const<const double>(), "Is_const(): something wrong");
static_assert(!Is_const<double>()      , "Is_const(): something wrong");

//////////
// Is_pod
//
//////////
template<class T>
constexpr bool Is_pod() { return std::is_pod<T>::value; }
static_assert(Is_pod<int>()    , "Is_pod(): something wrong");
static_assert(Is_pod<double>() , "Is_pod(): something wrong");

} // namespace stdwrap

using namespace stdwrap;

} // namespace meta

// make available in namespace libmda
using namespace meta::stdwrap;

} // namespace libmda

#endif /* LIBMDA_METAPROG_STD_WRAPPER_H */
