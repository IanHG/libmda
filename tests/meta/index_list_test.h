#ifndef LIBMDA_TESTS_INDEX_LIST_TEST_H
#define LIBMDA_TESTS_INDEX_LIST_TEST_H

#include "../../testing/testing_interface.h"
#include "../../meta/std_wrappers.h"
#include "../../meta/index_list.h"

namespace libmda
{
namespace meta_test
{

//
//
//
struct index_list_empty_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::index_list<1,2> t1;
      meta::empty<decltype(t1)> t2;

      UNIT_ASSERT((Is_same<decltype(t2),meta::index_list<> >()),"index_list not empty");
   }
};

//
//
//
struct index_list_catenation_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::index_list<1,2> t1;
      meta::index_list<3,4> t2;
      
      meta::catenate<decltype(t1),decltype(t2)> t3;
      
      UNIT_ASSERT((Is_same<decltype(t3),meta::index_list<1,2,3,4> >()),"not same types");
   }
};

////
////
////
//struct index_list_at_test: public virtual unit_test
//{
//   void do_test() throw(test_failed)
//   {
//      meta::index_list<double,int> t1;
//      
//      UNIT_ASSERT((Is_same<meta::at<decltype(t1),0>,double >()),"first type not double");
//      UNIT_ASSERT((Is_same<meta::at<decltype(t1),1>,int >()),   "second type not int");
//   }
//};

//
//
//
struct index_list_size_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      meta::index_list<1,2,3> t1;
      
      UNIT_ASSERT((meta::size<decltype(t1)>::value == 3),"size not correct: test 1");
      UNIT_ASSERT((meta::Size<decltype(t1)>() == 3),"size not correct: test 2");
   }
};

} /* namespace meta_test */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_INDEX_LIST_TEST_H */
