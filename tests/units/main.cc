#include<typeinfo>
#include<iostream>

#include "units_test.h"

#include "../../units/interface.h"
#include "../../units/au_unit.h"
using namespace libmda::units::si;
using namespace libmda::units::au;
#include"../../units/meta_string.h"

int main()
{
   libmda::util::meta_string<'a','b','c'>  ms1;
   libmda::util::meta_string<'d','e','f'>  ms2;
   libmda::util::Int_to_meta_string<-1213> msi1;
   libmda::util::Int_to_meta_string< 1213> msi2;

   auto ms3 = libmda::util::Catenate<decltype(ms1),decltype(msi1)>(); 
   
   std::cout << ms1 << std::endl;
   std::cout << ms3 << std::endl;
   std::cout << msi1 << std::endl;
   std::cout << msi2 << std::endl;
   std::cout << msi2+msi2 << std::endl;

   //quantity<bohr<1> > bb = quantity<bohr<1> >(2.0);
   //quantity<kg<-1> > ddddd = 2.0/10.0_kg;

   ////bb * ddddd;

   //quantity<m<1> > delta_length = 10.0_m;
   //quantity<m<1> > delta_length2 = 12.0_m;
   //
   //quantity<s<1> > delta_s = 5.57_s;
   //quantity<s<1> > delta_s2 = 12.0_s;

   //quantity<m<1>,s<-1> > velocity1 = delta_length/delta_s;
   //quantity<m<1>,s<-1> > velocity2 = delta_length2/delta_s;
   //
   //quantity<m<1>,s<-2> > acc = (velocity2-velocity1)/delta_s2;
   //
   //std::cout << acc << std::endl;
   //

   libmda::testing::test_suite suite;
   suite.add_test<libmda::units_test::addition_assignment_test<double> >();
   suite.do_tests();
   
   return 0;
}
