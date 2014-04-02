#ifndef LIBMDA_BENCHMARK_PTR_H
#define LIBMDA_BENCHMARK_PTR_H

#include <iostream>
using std::cout;
using std::endl;

#include "../../meta/get_type_n_.h"
using libmda::meta::get_type_n_;
#include "../../testing/testing_interface.h"
#include "../../util/for_loop_expand.h"

#include "../../util/sequence.h"

namespace libmda
{
namespace benchmark
{

using libmda::util::sequence;

#define PTR_SIZE 250000000

struct ptr_manager: virtual public unit_test
{
   double m_ptr[PTR_SIZE];

   ptr_manager(): m_ptr() { }

   void setup()     { for(size_t i=0; i<PTR_SIZE; ++i) m_ptr[i] = 1.0; }
   void tear_down() { for(size_t i=0; i<PTR_SIZE; ++i) m_ptr[i] = 0.0; }
};

struct ptr_test1: virtual public unit_test,
                  virtual public ptr_manager
{
   ptr_test1(): ptr_manager() { }

   void do_test() throw(test_failed)
   { 
      double ptr2[PTR_SIZE];
      for(size_t i=0; i<PTR_SIZE; ++i)
         ptr2[i] = m_ptr[i];
   }
};

#define SEQ_SIZE 100000000

struct sequence_test: virtual public unit_test
{
   sequence<SEQ_SIZE,double> seq;
   
   sequence_test(): seq() { }

   void do_test() throw(test_failed)
   { 
      sequence<SEQ_SIZE,double> seq2;
      seq2 = seq;
   }
};

struct sequence_test2: virtual public unit_test
{
   sequence<SEQ_SIZE,double> seq;
   
   sequence_test2(): seq() { }

   void do_test() throw(test_failed)
   { 
      sequence<SEQ_SIZE,double> seq2;
      for(size_t i=0; i<SEQ_SIZE; ++i)
         seq2[i] = seq[0];
   }
};


} // namespace benchmark
} // namespace libmda

#endif /* LIBMDA_BENCHMARK_PTR_H */
