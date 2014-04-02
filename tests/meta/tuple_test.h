#ifndef LIBMDA_TESTS_TUPLE_TEST_H
#define LIBMDA_TESTS_TUPLE_TEST_H

#include "../../testing/testing_interface.h"
#include "../../meta/std_wrappers.h"
#include "../../meta/tuple.h"

namespace libmda
{
namespace meta_test
{

//
//
//
struct tuple_empty_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::tuple<double,int> t1;
      meta::empty<decltype(t1)> t2;

      UNIT_ASSERT((Is_same<decltype(t2),meta::tuple<> >()),"tuple not empty");
   }
};

//
//
//
struct tuple_catenation_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::tuple<double,int> t1;
      meta::tuple<double,int> t2;
      
      meta::catenate<decltype(t1),decltype(t2)> t3;
      
      UNIT_ASSERT((Is_same<decltype(t3),meta::tuple<double,int,double,int> >()),"not same types");
   }
};

//
//
//
struct tuple_at_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::tuple<double,int> t1;
      
      UNIT_ASSERT((Is_same<meta::at<decltype(t1),0>,double >()),"first type not double");
      UNIT_ASSERT((Is_same<meta::at<decltype(t1),1>,int >()),   "second type not int");
   }
};

//
//
//
struct tuple_size_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::tuple<double,int,int> t1;
      
      UNIT_ASSERT((meta::size<decltype(t1)>::value == 3),"size not correct: test 1");
      UNIT_ASSERT((meta::Size<decltype(t1)>() == 3),"size not correct: test 2");
   }
};

//
//
//
struct tuple_find_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::tuple<double,int> t;
      
      UNIT_ASSERT((meta::Is_same<meta::deref<meta::find<decltype(t),double> >,double>()),"find not correct: test 1");
      //UNIT_ASSERT((meta::find<decltype(t1)> == 3),"size not correct: test 2");
   }
};

} // namespace meta_test
} // namespace libmda

#endif /* LIBMDA_TESTS_TUPLE_TEST_H */
