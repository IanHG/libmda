#ifndef LIBMDA_BENCHMARK_PTR_H
#define LIBMDA_BENCHMARK_PTR_H

#include <iostream>
using std::cout;
using std::endl;

#include "../../testing/testing_interface.h"
#include "../../arrays/Mda.h"
using libmda::arrays::mda_impl::Mda;
#include "../../arrays/Mda_piece.h"
using libmda::arrays::mda_impl::Mda_piece;

namespace libmda
{
namespace benchmark
{

using libmda::util::sequence;

#define SIZE 5

struct mda_copy_test: virtual public unit_test
{
   Mda<3,double,size_t> mda;
   
   mda_copy_test(): mda(SIZE,SIZE,SIZE) { mda=2.0; }

   void do_test() throw(test_failed)
   { 
      Mda<3,double,size_t> mda2(SIZE,SIZE,SIZE);
      mda2 = mda;
   }
};

struct mda_piece_copy_test: virtual public unit_test
{
   mda_piece_copy_test() {  }
   
   void do_test() throw(test_failed)
   { 
      Mda_piece<3,double,size_t,SIZE> mda;
      mda = 2.0;
      Mda_piece<3,double,size_t,SIZE> mda2;
      mda2 = mda;
   }
};

} // namespace benchmark
} // namespace libmda

#endif /* LIBMDA_BENCHMARK_PTR_H */
