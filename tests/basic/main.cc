#include<iostream>
using std::cout;
using std::endl;
#include "../../testing/unit_test.h"
using libmda::testing::unit_test;
#include "../../testing/test_suite.h"
using libmda::testing::test_suite;
#include "../../testing/test_failed.h"
using libmda::testing::test_failed;

template<int N>
struct the_test: public virtual unit_test
{
   private:
      double m_number;
   
   public:
   the_test(const double a_number): m_number(a_number) { };

   void do_test() throw(test_failed)
   { 
      cout << " im testing with template " << N
           << " and number " << m_number << endl; 
   }
};

struct mult_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      cout << " multi test " << endl;
      double a = 2;
      double b = 3;
      for(int i=0; i<10000000; ++i)
      {
         double c = a * b;
         //cout << " jeg bruger clocks !!" << endl;
         UNIT_ASSERT(c == 6," c = a * b failed ");
      }
   }
};

int main()
{
   test_suite suite;
   
   suite.add_test<mult_test>();
   suite.add_performance_test<3,mult_test>();
   suite.add_performance_test<2,the_test<1> >("the_test",3.0);
   
   suite.do_tests();
   return 0;
}
