#ifndef LIBMDA_TESTING_UNIT_TEST_H
#define LIBMDA_TESTING_UNIT_TEST_H

#include "test_failed.h"
#include "float_is_equal.h"

namespace libmda
{
namespace testing
{

// do assertion (will not increase assertion counter)
#define ASSERT(a,b) if(!(a)) throw test_failed("no name",__FILE__,__LINE__,(b),true,(a))

// do assertion and increase assertion counter
#define UNIT_ASSERT(a,b) unit_test::incr_num_assertions(); \
   if(!(a)) throw test_failed(this->name(),__FILE__,__LINE__,(b),true,(a))

// do assertion and increase assertion counter
#define UNIT_ASSERT_EQUAL(a,b,c) unit_test::incr_num_assertions(); \
   if(!((a)==(b))) \
   throw test_failed(this->name(),__FILE__,__LINE__,(c),(b),(a))

// do assertion and increase assertion counter
#define UNIT_ASSERT_FEQUAL(a,b,c) unit_test::incr_num_assertions(); \
   if(!numeric::float_is_equal((a),(b))) \
   throw test_failed(this->name(),__FILE__,__LINE__,(c),(b),(a))

// do assertion and increase assertion counter
#define UNIT_ASSERT_FEQUAL_PREC(a,b,c,d) unit_test::incr_num_assertions(); \
   if(!numeric::float_is_equal((a),(b),(c))) \
   throw test_failed(this->name(),__FILE__,__LINE__,(d),(b),(a))

class unit_test
{
   private:
      typedef unsigned int count_type;
      count_type m_num_assertions;

   public:
      unit_test(): m_num_assertions(0) { };
      virtual ~unit_test() { };
      virtual void do_test() throw(test_failed) = 0;
      virtual void setup()    { };
      virtual void teardown() { };
      
      void incr_num_assertions(int a_incr=1)
      { m_num_assertions+=a_incr; }
      count_type num_assertions() const
      { return m_num_assertions; }

      virtual unsigned int num_test() const { return 1; }
      virtual string name() const = 0;
};

template<class T>
class unit_test_name: public T
{
   private:
      const string m_name;
   public:
      template<typename... Args>
      unit_test_name(const string a_name, Args... args): T(args...), m_name(a_name) { };

      string name() const { return m_name; }
};

class default_test_name
{
   private:
      static string       m_name;
      static unsigned int m_num;
   
   public:
      static string acquire_name()
      { ++m_num; return m_name+"_"+std::to_string(m_num); }
};

string default_test_name::m_name="default_test";
unsigned int default_test_name::m_num=0;

} // namespace testing
} // namespace libmda

#endif /* LIBMDA_TESTING_UNIT_TEST_H */
