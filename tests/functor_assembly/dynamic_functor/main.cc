#include<iostream>
#include "../../../metaprog/loop.h"

struct Forr_
{
   template<class T, class U>
   void operator()(std::ostream& aout, T t, U u)
   {
      aout << libmda::deref<T>::value << " ";
      this->operator()(aout,libmda::next<T>(),u);
   }
   template<class T>
   void operator()(std::ostream& aout, T t, T u)
   { };
};


template<class F, class T, class U>
static void Forr(F f, T t, U u)
{
   f(std::cout,t,u);
};

int main()
{
   using l = libmda::metaprog::loop<0,200>;
   Forr(Forr_(), libmda::metaprog::begin<l>(), libmda::metaprog::end<l>());

   return 0;
}
