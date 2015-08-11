#ifndef LIBMDA_TESTS_IMDA_TEST_H
#define LIBMDA_TESTS_IMDA_TEST_H

#include<typeinfo> // for typeid
#include<iostream>
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../util/require.h"
#include "../../util/Assert.h"

namespace libmda
{
namespace tests
{
namespace imda
{

//
//
//
//
template<class vector_type>
struct float_vector_test_base: public virtual unit_test
{
   static_assert(util::Assert_value_type<vector_type,util::Is_floating_point>()," must be float ");
   static_assert(util::Assert_order<vector_type,util::Order_equal<1> >()," must be order 1 ");
};

//
//
//
//
template<class vector_type>
struct vector_assign_test: float_vector_test_base<vector_type>
{
   void do_test() throw(test_failed)
   {
       vector_type vec(3);

       vec.at(0) = 3.14159;
       vec.at(1) = 42.0;
       vec.at(2) = 9.10938291e-31;

       UNIT_ASSERT_FEQUAL_PREC(vec.at(0),3.14159       ,2, " vec(0) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(1),42.0          ,2, " vec(1) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(2),9.10938291e-31,2, " vec(2) is wrong ");
   }
};

//
//
//
//
template<class vector_type>
struct vector_assign_scalar_test: float_vector_test_base<vector_type>
{
   void do_test() throw(test_failed)
   {
       vector_type vec(3);

       vec = 3.14159;

       UNIT_ASSERT_FEQUAL_PREC(vec.at(0),3.14159,2, " vec(0) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(1),3.14159,2, " vec(1) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(2),3.14159,2, " vec(2) is wrong ");
   }
};

//
//
//
//
template<class vector_type>
struct vector_add_assign_scalar_test: float_vector_test_base<vector_type>
{
   void do_test() throw(test_failed)
   {
       vector_type vec(3);

       vec = 0.0;
       vec += 42.0;

       UNIT_ASSERT_FEQUAL_PREC(vec.at(0),42.0,2, " vec(0) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(1),42.0,2, " vec(1) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(2),42.0,2, " vec(2) is wrong ");
   }
};

//
//
//
//
template<class vector_type>
struct vector_sub_assign_scalar_test: float_vector_test_base<vector_type>
{
   void do_test() throw(test_failed)
   {
       vector_type vec(3);

       vec = 0.0;
       vec -= 42.0;

       UNIT_ASSERT_FEQUAL_PREC(vec.at(0),-42.0,2, " vec(0) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(1),-42.0,2, " vec(1) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(2),-42.0,2, " vec(2) is wrong ");
   }
};

//
//
//
//
template<class vector_type>
struct vector_mul_assign_scalar_test: float_vector_test_base<vector_type>
{
   void do_test() throw(test_failed)
   {
       vector_type vec(3);

       vec = 1.0;
       vec *= 3.14159;

       UNIT_ASSERT_FEQUAL_PREC(vec.at(0),3.14159,2, " vec(0) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(1),3.14159,2, " vec(1) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(2),3.14159,2, " vec(2) is wrong ");
   }
};

//
//
//
//
template<class vector_type>
struct vector_div_assign_scalar_test: float_vector_test_base<vector_type>
{
   void do_test() throw(test_failed)
   {
       vector_type vec(3);

       vec = 3.14159;
       vec /= 3.14159;

       UNIT_ASSERT_FEQUAL_PREC(vec.at(0),1.0,2, " vec(0) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(1),1.0,2, " vec(1) is wrong ");
       UNIT_ASSERT_FEQUAL_PREC(vec.at(2),1.0,2, " vec(2) is wrong ");
   }
};

} // namespace imda
} // namespace tests
} // namespace libmda

#endif /* LIBMDA_TESTS_IMDA_TEST_H */
