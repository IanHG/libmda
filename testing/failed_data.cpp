#include "failed_data.h"

namespace libmda
{
namespace testing
{

//
//
//
void failed_data_destroy(failed_data_base* a_failed_data)
{ 
   delete a_failed_data; 
}

} // namespace testing
} // namespace libmda
