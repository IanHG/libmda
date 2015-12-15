#include<iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <functional>

std::ostream& operator<<(std::ostream& os, const std::vector<double>& vec)
{
   os << "(";
   for(int i = 0; i < vec.size() - 1; ++i)
   {
      os << vec[i] << " ";
   }
   if(vec.size() > 0)
   {
      os << vec[vec.size() - 1];
   }
   os << ")";
   return os;
}

#include "../../util/expected.h"
#include "../../util/scope_guard.h"

using libmda::util::expected;
using libmda::util::scope_guard;
using libmda::util::make_scope_guard;

void handle_exception(std::exception_ptr eptr)
{
   try
   {
      if(eptr)
      {
         std::cout << " will rethrow " << std::endl;
         std::rethrow_exception(eptr);
      }
   }
   catch(std::exception& e)
   {
      std::cout << e.what() << std::endl;
   }
   catch(...)
   {
      std::cout << " whatever " << std::endl;
   }
}

std::vector<double> make_vector()
{
   return {3,3};
}

expected<double> make_double()
{
   return {3.0};
}

int main()
{
   //std::vector<double> vec{4,4};
   //expected<std::vector<double> > v = std::vector<double>{2,3};
   //expected<std::vector<double> > v2 = std::move(v);
   //
   //expected<std::vector<double> > v3(make_vector());
   //
   //expected<std::vector<double> > v4 = vec;
   //expected<std::vector<double> > v5 = v3;
   //expected<std::vector<double> > v6(std::vector<double>(11,2));
   //v6 = v4;

   //expected<std::string> str = std::string("affe");
   //
   //auto dd = make_double();
   union U
   {
      double ud;
      std::exception_ptr ue;
      U() {};
      ~U() {};
   };

   expected<double> d = 2.0;
   std::cout << sizeof(double) << std::endl;
   std::cout << sizeof(expected<double>) << std::endl;
   std::cout << sizeof(U) << std::endl;
   std::cout << sizeof(std::exception_ptr) << std::endl;
   std::cout << sizeof(bool) << std::endl;
   //
   expected<double> d2 = expected<double>::from_exception(std::runtime_error("this is error"));
   ////expected<double> d2 = expected<double>::from_exception(1);
   //
   d = std::move(d2);

   try
   {
      double* ptr = new double[2];
      auto g = make_scope_guard([&](){ delete[] ptr; });
      std::cout << d.get() << std::endl;
   }
   catch(...)
   {
      std::cout << " caught something " << std::endl;
      auto g = make_scope_guard(std::bind(handle_exception,std::current_exception()));
   }
   handle_exception(std::current_exception());
   //std::cout << d2.get() << std::endl;
   //std::cout << dd.get() << std::endl;
   
   auto g1 = make_scope_guard([](){ std::cout << 2 << std::endl;});
   auto g2 = make_scope_guard([](){ std::cout << 3 << std::endl;});
   g2.dismiss();

   return 0;
}
