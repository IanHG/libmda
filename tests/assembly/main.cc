#include<iostream>
#include "../../metaprog/loop.h"

template<class T, class U>
struct Forr_
{
   static void apply(std::ostream& aout)
   {
      aout << libmda::deref<T>::value << " ";
      Forr_<libmda::next<T>,U>::apply(aout);
   }
};

template<class T> struct Forr_<T,T>
{
   static void apply(std::ostream&)
   { }
};

template<class T, class U>
static void Forr()
{
   Forr_<T,U>::apply(std::cout);
};

int main()
{
   using l = libmda::metaprog::loop<0,10>;
   Forr<libmda::metaprog::begin<l>, libmda::metaprog::end<l> >();

   return 0;
}
