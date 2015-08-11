#ifndef LIBMDA_TESTS_NUMERIC_H_INCLUDED
#define LIBMDA_TESTS_NUMERIC_H_INCLUDED

// std headers
#include<typeinfo> // for typeid
#include<iostream>

// libmda headers
#include "../../interface.h"
#include "../../testing/testing_interface.h"
#include "../../util/type_info.h"
#include "../../units/quantity.h"
#include "../../units/si_unit.h"

namespace libmda
{
namespace units_test
{

template<class T = double>
struct addition_assignment_test: public virtual unit_test
{
   void do_test() throw(test_failed)
   {
      units::quantity< units::si::kg<1> > mass1(2.0);
      units::quantity< units::si::kg<1> > mass2(3.0);
      mass1+=mass2;
      UNIT_ASSERT( numeric::float_eq(mass1.val(),5.0),"addition assignment failed for type: "/*+util::typeof(T)*/);
   }
};


} /* namespace units_test */
} /* namespace libmda */

#endif /* LIBMDA_TESTS_NUMERIC_H_INCLUDED */
