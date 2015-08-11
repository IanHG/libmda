#ifndef UTILITY_INDEX_CHECK
#define UTILITY_INDEX_CHECK

#include<assert.h>

#include "stacktrace.h"

namespace libmda
{
namespace util
{

struct index_check
{
   template<typename T, typename U>
   static void apply(const T index1, const U index2)
   { 
      assert(index1>=0);
      assert(index1<index2); 
   }
};

struct index_check_return_addr
{
   template<typename T, typename U>
   static void apply(const T index1, const U index2)
   { 
      if(!(index1>=0))
      {
         std::cout << " index1<=0 \n"
                   << " presumeably called from here: " << __builtin_return_address(1) << std::endl;
         exit(40);
      }
      if(!(index1<index2))
      {
         std::cout << " index1>index2 \n"
                   << " presumeably called from here: " << __builtin_return_address(1) << std::endl;
         exit(40);
      }
   }
};

struct index_check_stack_trace
{
   template<typename T, typename U>
   static void apply(const T index1, const U index2)
   { 
      if(!(index1>=0))
      {
         std::cout << " index1<=0 \n";
         print_stacktrace(std::cout);
         exit(40);
      }
      if(!(index1<index2))
      {
         std::cout << " index1>index2 \n";
         print_stacktrace(std::cout);
         exit(40);
      }
   }
};
 
struct index_nocheck
{
   template<typename T, typename U>
   static void apply(const T index1, const U index2)
   { 
   }
};

} // namespace util
} // namespace libmda

#endif /* UTILITY_INDEX_CHECK */
