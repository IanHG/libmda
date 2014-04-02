#include <iostream>
#include <typeinfo>

#include "../../imda/imda_interface.h"
#include "../../meta/sum.h"
#include "../../meta/index_list.h"
#include "../../meta/tuple.h"

class custom_vector;

struct custom_vector_trait
{
   using type       = custom_vector;
   using value_type = double;
   using size_type  = size_t;
   static const size_t order = 1;
};

class custom_vector:
   public libmda::imda::iextended<custom_vector, custom_vector_trait>
{
   public:
      double&       at(size_t i)       
      { 
         return _elem; 
      } 
      
      const double& at(size_t i) const 
      { 
         return _elem; 
      } 
      
      size_t size() const
      {
         return 1;
      }

      template<int I>
      size_t extent() const
      {
         return 1;
      }
   
   private:
      double _elem = 2.0;
};

int main()
{
   custom_vector vec;
   custom_vector vec2;
   vec *= vec2;
   std::cout << vec << std::endl;
   
   libmda::meta::catenate<libmda::meta::index_list<1,2>, libmda::meta::index_list<3,4>, libmda::meta::index_list<5,6> > l;
   std::cout << l << std::endl;
   
   return 0;
}
