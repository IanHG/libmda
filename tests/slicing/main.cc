#include<typeinfo>
#include<iostream>
#include "../../arrays/SDArray2D.h"
#include "../../utility/has_member.h"
//#include "../../arrays/Mda_slice.h"
//using libmda::arrays::mda_impl::Mda_slice;
//#include "../../arrays/Mda.h"
//using libmda::arrays::mda_impl::Mda;
//#include "../../metaprog/std_wrappers.h"
//using libmda::All;

//#include "../../arrays/Mda_piece.h"
//using libmda::arrays::mda_impl::Mda_piece;
//using libmda::arrays::mda_impl::detail::Pow;

#include "../../metaprog/std_wrappers.h"

#include "../../metaprog/permutation.h"
using libmda::metaprog::permutation;

//#include "../../expr/cindex.h"
//using libmda::cindex;

//#include "../../metaprog/type_tuple_.h"
//using libmda::metaprog::type_tuple_;

#include "../../metaprog/tuple.h"
#include "../../metaprog/loop.h"
using libmda::metaprog::tuple;
using libmda::metaprog::loop;

#include "../../utility/slice.h"
using libmda::slice;

using libmda::next;
using libmda::prev;
using libmda::deref;
using libmda::metaprog::pos;
using libmda::advance;
using libmda::begin;
using libmda::end;
using libmda::metaprog::permute;
using libmda::metaprog::i_permute;
using libmda::metaprog::partition;
using libmda::metaprog::at;

#include "../../expr/find_positions.h"
using libmda::metaprog::find_positions;

//#include "../../arrays/MultiDimArray.h"
//using libmda::MDA;

//#include<initializer_list>

template<class T, class U>
struct Forr_
{
   static void apply()
   {
      std::cout << deref<T>::value << " ";
      Forr_<next<T>,U>::apply();
   }
};

template<class T> struct Forr_<T,T>
{
   static void apply()
   { }
};

template<class T, class U>
static void Forr()
{
   Forr_<T,U>::apply();
   std::cout << std::endl;
};

template<class T> struct find_type
{  
   template<class U> struct apply
   {
      static const bool value = libmda::metaprog::Is_same<T,U>();
   };
};

template<class T> struct tuple_overlap
{
   template<class U> struct apply
   {
      static const bool value = (libmda::metaprog::Find_pos<T,U>() != T::Size());
   };
};

using libmda::metaprog::same_as;

int main()
{
   //Mda<2> mda(2,2);
   //mda(0,0) = 1.0;
   //mda(0,1) = 2.0;
   //mda(1,0) = 3.0;
   //mda(1,1) = 4.0;
   //
   //std::cout << mda << std::endl;
   
   std::cout << libmda::utility::has_size<midas::mmv::SDArray2D<double>, size_t>::value << std::endl;
   midas::mmv::SDArray2D<double> sd(3,3);
   std::cout << sd.size() << std::endl;
   //using p = permutation<1,0,2>;
   //std::cout << typeid(permute<p,p>).name() << std::endl;
   //std::cout << typeid(i_permute<p,1,0,2>).name() << std::endl;
   //using p2 = p::Permute<1,0,2>;
   //std::cout << typeid(p::Permute<1,0,2>).name() << std::endl;

   using t  = tuple<int,double,size_t>;
   std::cout << "at: " << typeid(libmda::metaprog::at<t,0>).name() << std::endl;
   std::cout << "push_back  : " << typeid(libmda::metaprog::push_back <t,float,int>).name() << std::endl;
   std::cout << "push_front : " << typeid(libmda::metaprog::push_front<t,float,int>).name() << std::endl;
   
   std::cout << "pop_front  : " << typeid(libmda::metaprog::pop_front<t>).name() << std::endl;
   //std::cout << "pop_back   : " << typeid(libmda::metaprog::pop_back <t>).name() << std::endl;
   
   using t2 = tuple<double>;
   std::cout << "catenate   : " << typeid(libmda::metaprog::catenate<t,t2>).name() << std::endl;
   
   using t3 = tuple<int,double,int>;
   std::cout << "all_unique : " << libmda::metaprog::detail::all_unique<t >::value << std::endl;
   std::cout << "all_unique : " << libmda::metaprog::detail::all_unique<t3>::value << std::endl;
   
   std::cout << "remove_if  : " << typeid(libmda::metaprog::remove_if<t,same_as<double> >).name() << std::endl;
   std::cout << "remove     : " << typeid(libmda::metaprog::remove   <t,double>).name() << std::endl;

   using p  = partition<t ,tuple_overlap<t2> >;
   //using p2 = partition<t2,tuple_overlap<t > >;
  
   //std::cout << typeid(t).name() << std::endl;
   std::cout << " partition true : " << typeid(typename p ::t).name() << std::endl;
   //std::cout << typeid(typename p2::t).name() << std::endl;
   std::cout << " partition false: " << typeid(typename p ::f).name() << std::endl;
   //std::cout << typeid(typename p2::f).name() << std::endl;
   
   using perm = libmda::metaprog::permutation<0,2,1>;
   std::cout << " i_permute: " << typeid(libmda::metaprog::i_permute<t,0,2,1>).name() << std::endl;
   std::cout << "   permute: " << typeid(libmda::metaprog::permute<t,perm>).name() << std::endl;

   std::cout << libmda::metaprog::Find_pos<t,float>()  << std::endl;
   std::cout << libmda::metaprog::Find_pos<t,double>() << std::endl;
   std::cout << " find_if          : " << typeid(deref<libmda::metaprog::find_if<t,same_as<double> > >).name() << std::endl;
   std::cout << " find_if pos      : " << typeid(pos<libmda::metaprog::find_if<t,same_as<double> > >).name() << std::endl;
   std::cout << " find_if pos value: " << pos<libmda::metaprog::find_if<t,same_as<double> > >::value << std::endl;
   std::cout << " find             : " << typeid(deref<libmda::metaprog::find<t,double> >).name() << std::endl;
   std::cout << " find    pos      : " << typeid(pos<libmda::metaprog::find<t,double> >).name() << std::endl;
   std::cout << " find    pos value: " << pos<libmda::metaprog::find<t,double> >::value << std::endl;
   std::cout << " range: " << typeid(libmda::metaprog::range<t,0,2>).name() << std::endl;
   
   std::cout << " insert: \n ";
   std::cout << typeid(libmda::metaprog::insert<t,float,1>).name() << std::endl;

   //typedef tuple<cindex<'j'>, cindex<'k'>, cindex<'i'> > t2;
   //std::cout << All_unique<t2>() << std::endl;
   //std::cout << " tuple: " << All_unique<t>() << std::endl;
   
   //std::cout << t::Is_empty() << std::endl;
   //std::cout << t::Size()  << std::endl;
   //std::cout << typeid(t).name() << std::endl;
   //std::cout << typeid(t2::At<0>).name() << std::endl;
   //std::cout << typeid(t2::Push_back<int,double>).name()  << std::endl;
   //std::cout << typeid(t::Push_front<int,double>).name() << std::endl;
   std::cout << "begin    " << typeid(deref<begin<t> >).name()        << std::endl;
   std::cout << "next     " << typeid(deref<next<begin<t> > >).name() << std::endl;
   std::cout << "advance: " << typeid(deref<advance<next<begin<t> >, -1> >).name() << std::endl;
   
   using t4  = tuple<double,size_t,int>;
   using find_pos = libmda::metaprog::find_positions<t,t4>;
   std::cout << "find_positions: " << typeid(find_pos).name() << std::endl;
   std::cout << at<find_pos,0>::value << " " << at<find_pos,1>::value << " " << at<find_pos,2>::value << std::endl;  
   
   //std::cout << typeid(deref<t::End>).name() << std::endl;
   //std::cout << typeid(deref<end<t> >).name() << std::endl;
   //std::cout << typeid(t::Range<0,2>).name() << std::endl;
   //std::cout << typeid(t::Range<1,1>).name() << std::endl;
   //
   //std::cout << typeid(t::Insert<float,1>).name() << std::endl;
   
   //std::cout << t::Find<double>() << std::endl;
   //std::cout << typeid(t::Att<0,1>).name() << std::endl;

   using l = loop<0,10>;
   //std::cout << deref<begin<l> >::value << std::endl;
   //std::cout << deref<l::Begin::next>::value << std::endl;
   //std::cout << deref<l::Begin::next::next>::value << std::endl;
   std::cout << " for loop<0,10> : "; Forr<begin<l>, end<l> >();

   //std::cout << deref<l::Begin::next>::value << std::endl;
   //std::cout << typeid(deref<l::End>).name() << std::endl;
   
   //Forr<p ::Begin, p ::End>();
   //Forr<p2::Begin, p2::End>();

   //std::cout << typeid(t).name() << std::endl;
   //std::cout << typeid(permute<t,p>).name() << std::endl;
   //std::cout << typeid(i_permute<t,1,0,2>).name() << std::endl;
   //

   //cindex<'i'> i;
   //std::cout << slice(i,0,10).lower() << std::endl;
   //std::cout << slice(0,10).upper() << std::endl;

   return 0;
}
