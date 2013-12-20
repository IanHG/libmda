#include<typeinfo>
#include<iostream>
#include "../../units/interface.h"
#include "../../units/au_unit.h"
using namespace libmda::units::si;
using namespace libmda::units::au;

int main()
{
   quantity<bohr<1> > bb = quantity<bohr<1> >(2.0);
   quantity<kg<-1> > ddddd = 2.0/10.0_kg;

   //bb * ddddd;

   quantity<m<1> > delta_length = 10.0_m;
   quantity<m<1> > delta_length2 = 12.0_m;
   
   quantity<s<1> > delta_s = 5.57_s;
   quantity<s<1> > delta_s2 = 12.0_s;

   quantity<m<1>,s<-1> > velocity1 = delta_length/delta_s;
   quantity<m<1>,s<-1> > velocity2 = delta_length2/delta_s;
   
   quantity<m<1>,s<-2> > acc = (velocity2-velocity1)/delta_s2;
   
   std::cout << acc << std::endl;
   
   return 0;
}
