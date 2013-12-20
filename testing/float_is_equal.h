#ifndef LIBMDA_TESTING_FLOAT_IS_EQUAL_H
#define LIBMDA_TESTING_FLOAT_IS_EQUAL_H

//#include<iostream>
#include "../metaprog/std_wrappers.h"
#include "../metaprog/if.h"

namespace libmda
{
namespace numeric
{
namespace detail
{

// struct for finding integer of same size as T
template<typename T>
struct integer_type_
{
   using type = If<sizeof(int)==sizeof(T) 
                 , int
                 , If<sizeof(long int)==sizeof(T)
                    , long int 
                    , If<sizeof(long long int)==sizeof(T), long long int, void>
                   > 
                 >;

   // assert that we have a type large enough
   static_assert(!Is_same<type,void>(),"Integer type is void :(");
};

} // namespace detail

// interface to integer_type
template<typename T>
using integer_type = typename detail::integer_type_<T>::type;

template<typename T>
union float_int
{
   using float_type = T;
   using int_type   = integer_type<T>;
   
   float_int(const float_type a_float):  
      m_float(a_float) 
   { 
   };

   const float_type m_float;
   const int_type   m_int;
};

template<typename T>
union int_float
{
   using float_type = T;
   using int_type   = integer_type<T>;
   
   int_float(const int_type a_int):  
      m_int(a_int) 
   { 
   };

   const float_type m_float;
   const int_type   m_int;
};


template<typename T, typename I = integer_type<T> >
bool float_is_equal(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
{
   //std::cout << a_lhs << std::endl;
   //std::cout << a_rhs << std::endl; 

   const float_int<T> lhs(a_lhs);
   const float_int<T> rhs(a_rhs);
   
   //std::cout << "ulps: " << lhs.m_int - rhs.m_int << std::endl;

   return std::abs(lhs.m_int - rhs.m_int) <= max_ulps_diff;
}

/********************************/
// float equal
/********************************/
template<typename T, typename I = integer_type<T> >
bool float_eq(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
{
   //std::cout << a_lhs << std::endl;
   //std::cout << a_rhs << std::endl; 

   const float_int<T> lhs(a_lhs);
   const float_int<T> rhs(a_rhs);
   
   //std::cout << "ulps: " << lhs.m_int - rhs.m_int << std::endl;
   //std::cout << "max_ulps_diff: " << max_ulps_diff << std::endl;
   //std::cout << "abs ulps: " << std::abs(lhs.m_int - rhs.m_int) << std::endl;
   //std::cout << typeid(lhs.m_int).name() << std::endl;
   //std::cout << sizeof(lhs.m_int) << std::endl;
   //std::cout << sizeof(lhs.m_float) << std::endl;

   return std::abs(lhs.m_int - rhs.m_int) <= max_ulps_diff;
}

/********************************/
// float not equal
/********************************/
template<typename T, typename I = integer_type<T> >
bool float_neq(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
{
   return !float_eq(a_lhs, a_rhs, max_ulps_diff);
}

/********************************/
// float less than or equal
/********************************/
template<typename T, typename I = integer_type<T> >
bool float_leq(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
{
   return float_eq(a_lhs,a_rhs,max_ulps_diff) ? true : (a_lhs < a_rhs);
}

/********************************/
// float greater than or equal
/********************************/
template<typename T, typename I = integer_type<T> >
bool float_geq(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
{
   return float_eq(a_lhs,a_rhs,max_ulps_diff) ? true : (a_lhs > a_rhs);
}

/********************************/
// float less than
/********************************/
template<typename T, typename I = integer_type<T> >
bool float_lt(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
{
   // not greater than or equal -> less than
   return !float_geq(a_lhs, a_rhs, max_ulps_diff); 
}

/********************************/
// float greater than
/********************************/
template<typename T, typename I = integer_type<T> >
bool float_gt(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
{
   // not less than or equal -> greater than
   return !float_leq(a_lhs, a_rhs, max_ulps_diff); 
}

} // namespace numeric
} // namespace libmda

#endif /* LIBMDA_TESTING_FLOAT_IS_EQUAL_H */
