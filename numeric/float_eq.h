#ifndef LIBMDA_TESTING_FLOAT_IS_EQUAL_H_INCLUDED
#define LIBMDA_TESTING_FLOAT_IS_EQUAL_H_INCLUDED

#include <limits>
#include <complex>
#include <type_traits> // for std::is_floating_point

#include "../meta/std_wrappers.h"
#include "../meta/if.h"

namespace libmda
{
namespace numeric
{
namespace detail
{

//
// struct for finding integer of same size as T
//
template<typename T>
struct integer_type_
{
   struct void_type {};

   using type2 = If<(sizeof(unsigned char)==sizeof(T))
                 , unsigned char
                 , If<(sizeof(unsigned short)==sizeof(T))
                    , unsigned short
                    , If<(sizeof(unsigned)==sizeof(T))
                       , unsigned
                       , If<(sizeof(unsigned long)==sizeof(T))
                          , unsigned long
                          , If<(sizeof(unsigned long long)==sizeof(T))
                             , unsigned long long
                             , void_type
                             >
                          >
                       >
                    >
                 >;

   // assert that we have a type large enough
   static_assert(!Is_same<type2,void_type>(), "Integer type is void :(, nothing large enough");
   //static_assert(std::is_floating_point<T>::value, "Type is not floating point"); // THINK ABOUT THIS ONE

   using type = type2;
};

} // namespace detail

//
// interface to integer_type
//
template<typename T>
using integer_type = typename detail::integer_type_<T>::type;

//
// conversion from float to int
//
template<typename T>
class floating_point
{
   public:
   using float_type = T;
   using int_type   = integer_type<T>;
   
   static const int_type k_max_ulps = 4;
   static const size_t k_bit_count = 8*sizeof(T);
   static const size_t k_fraction_bit_count = std::numeric_limits<T>::digits-1;
   static const size_t k_exponent_bit_count = k_bit_count - 1 - k_fraction_bit_count;
   static const int_type k_sign_bit_mask = static_cast<int_type>(1) << (k_bit_count - 1);
   static const int_type k_fraction_bit_mask = ~static_cast<int_type>(0) >> (k_exponent_bit_count + 1);
   static const int_type k_exponent_bit_mask = ~(k_sign_bit_mask | k_fraction_bit_mask);
   
   bool negative() const
   {
      return (k_sign_bit_mask & u_.bits_);
   }

   //http://en.wikipedia.org/wiki/Signed_number_representations
   static int_type sign_and_magnitude_to_biased(const int_type& sam)
   {
      if(k_sign_bit_mask & sam)
      {
         // sam is a negative number
         return ~sam + 1;
      }
      else
      {
         // sam is positive
         return k_sign_bit_mask | sam;
      }
   }

   static int_type distance_between_sign_and_magnitude_numbers(const int_type& sam1
                                                             , const int_type& sam2)
   {
      const int_type biased1 = sign_and_magnitude_to_biased(sam1);
      const int_type biased2 = sign_and_magnitude_to_biased(sam2);
      //std::cout << " distance:" << ( (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1) ) << std::endl;
      
      //std::cout << biased1 << std::endl;
      //std::cout << biased2 << std::endl;

      return (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1);
   }

   explicit floating_point(const T& t)
   {
      u_.value_ = t;
   }
   
   bool almost_equal(const floating_point& rhs, int_type max_ulps = k_max_ulps) const
   {
      return distance_between_sign_and_magnitude_numbers(u_.bits_,rhs.u_.bits_) <= max_ulps;
   }

   int_type distance(const floating_point& rhs) const
   {
      return distance_between_sign_and_magnitude_numbers(u_.bits_,rhs.u_.bits_);
   }
   
   //bool almost_equal_zero(int_type max_ulps = k_max_ulps) const
   //{
   //   floating_point rhs(std::numeric_limits<T>::epsilon());
   //   if(negative())
   //   {
   //      return ((u_.bits_^k_sign_bit_mask) <= (rhs.u_.bits_ + max_ulps)); // <= max_ulps;
   //   }
   //   else
   //   {
   //      return (u_.bits_ <= (rhs.u_.bits_ + max_ulps));
   //      //return distance_between_sign_and_magnitude_numbers(u_.bits_,rhs.u_.bits_) <= max_ulps;
   //   }
   //}

   int_type bits() const
   {
      return u_.bits_;
   }
   
   int_type biased_bits() const
   {
      return sign_and_magnitude_to_biased(u_.bits_);
   }

   private:
   union float_union
   {
      float_type value_;
      int_type   bits_;
   } u_;
};

template<class T>
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
//
// conversion from int to float (OLD STRUCT... ABOVE IS THE NEW ONE!)
//
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

//
// old implementation (name has now changed)
//
//template<typename T, typename I = integer_type<T> >
//bool float_is_equal(const T a_lhs, const T a_rhs, const I max_ulps_diff = 2)
//{
//   //std::cout << a_lhs << std::endl;
//   //std::cout << a_rhs << std::endl; 
//
//   const float_int<T> lhs(a_lhs);
//   const float_int<T> rhs(a_rhs);
//   
//   //std::cout << "ulps: " << lhs.m_int - rhs.m_int << std::endl;
//
//   return std::abs(lhs.m_int - rhs.m_int) <= max_ulps_diff;
//}

//
//
// ULP: Unit of least precision, i.e. the 'spacing' between floating-point numbers
//
//
/********************************/
// float ulps (bool specialization)
/********************************/
inline integer_type<bool> float_ulps(const bool a_lhs, const bool a_rhs)
{
   floating_point<bool> lhs(a_lhs);
   floating_point<bool> rhs(a_rhs);

   return lhs.distance(rhs);
}
         

/********************************/
// float ulps
/********************************/
template<class T
       , typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr
       >
integer_type<T> float_ulps(const T a_lhs, const T a_rhs)
{
   floating_point<T> lhs(a_lhs);
   floating_point<T> rhs(a_rhs);

   return lhs.distance(rhs);
}

/********************************/
// float ulps (for complex, defined as float_ulps(real) + float_ulps(imag)) 
/********************************/
template<class T
       , typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr
       >
integer_type<T> float_ulps(const std::complex<T>& a_lhs, const std::complex<T>& a_rhs)
{
   return float_ulps(a_lhs.real(),a_rhs.real()) + float_ulps(a_lhs.imag(),a_rhs.imag());
}

/********************************/
// float equal
/********************************/
template<class T
       , typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr
       >
bool float_eq(const T a_lhs, const T a_rhs, const integer_type<T> max_ulps_diff = 2)
{
   floating_point<T> lhs(a_lhs);
   floating_point<T> rhs(a_rhs);

   return lhs.almost_equal(rhs,max_ulps_diff);
}

/********************************/
// float equal (for complex, defined as float_eq(real) && float_eq(imag))
/********************************/
template<class T
       , typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr
       > 
bool float_eq(const std::complex<T>& a_lhs, const std::complex<T>& a_rhs, const integer_type<T> max_ulps_diff = 2)
{
   return float_eq(a_lhs.real(),a_rhs.real(),max_ulps_diff) && float_eq(a_lhs.imag(),a_rhs.imag(),max_ulps_diff);
}

/********************************/
// float equal to zero ?? EXPERIMENTAL !
/********************************/
//template<class T, typename I = integer_type<T> >
//bool float_eq_zero(const T a_lhs, const I max_ulps_diff = 2)
//{
//   floating_point<T> lhs(a_lhs);
//   return lhs.almost_equal_zero(max_ulps_diff);
//}

template<class T> //, class I = integer_type<T> >
inline bool float_numeq_zero(const T a_zero, const T a_comp, const integer_type<T> max_ulps_diff = 2)
{
   //return float_eq(a_comp+a_zero,a_comp,max_ulps_diff);
   return float_eq(a_comp,a_comp+a_zero,max_ulps_diff);
}

template<class T, class U>
inline bool float_numeq_zero(const T a_zero, const U a_comp, const integer_type<T> max_ulps_diff = 2)
{  
   return float_numeq_zero(a_zero,T(a_comp),max_ulps_diff);
}


/********************************/
// float negative?
/********************************/
template<class T>
inline bool float_neg(const T a_lhs)
{
   floating_point<T> lhs(a_lhs);
   return lhs.negative();
}

/********************************/
// float positive?
/********************************/
template<class T>
inline bool float_pos(const T a_lhs)
{
   return !float_neg(a_lhs);
}

/********************************/
// float not equal
/********************************/
template<class T> //, typename I = integer_type<T> >
inline bool float_neq(const T a_lhs, const T a_rhs, const integer_type<T> max_ulps_diff = 2)
{
   return !float_eq(a_lhs, a_rhs, max_ulps_diff);
}

/********************************/
// float less than or equal
/********************************/
template<class T> //, typename I = integer_type<T> >
inline bool float_leq(const T a_lhs, const T a_rhs, const integer_type<T> max_ulps_diff = 2)
{
   return float_eq(a_lhs,a_rhs,max_ulps_diff) ? true : (a_lhs < a_rhs);
}

/********************************/
// float greater than or equal
/********************************/
template<class T> //, typename I = integer_type<T> >
inline bool float_geq(const T a_lhs, const T a_rhs, const integer_type<T> max_ulps_diff = 2)
{
   return float_eq(a_lhs,a_rhs,max_ulps_diff) ? true : (a_lhs > a_rhs);
}

/********************************/
// float less than
/********************************/
template<class T> //, typename I = integer_type<T> >
inline bool float_lt(const T a_lhs, const T a_rhs, const integer_type<T> max_ulps_diff = 2)
{
   // not greater than or equal -> less than
   return !float_geq(a_lhs, a_rhs, max_ulps_diff); 
}

/********************************/
// float greater than
/********************************/
template<class T> //, typename I = integer_type<T> >
inline bool float_gt(const T a_lhs, const T a_rhs, const integer_type<T> max_ulps_diff = 2)
{
   // not less than or equal -> greater than
   return !float_leq(a_lhs, a_rhs, max_ulps_diff); 
}

/********************************/
// float numerically not zero
/********************************/
template<class T, class U>
inline bool float_numneq_zero(const T a_lhs, const U a_comp, const integer_type<T> max_ulps_diff = 2)
{
   return !float_numeq_zero(a_lhs,a_comp,max_ulps_diff);
}

/********************************/
// float numerically greater than zero
/********************************/
template<class T, class U>
inline bool float_numgeq_zero(const T a_lhs, const U a_comp, const integer_type<T> max_ulps_diff = 2)
{
   return float_numeq_zero(a_lhs,a_comp,max_ulps_diff) ? true : float_pos(a_lhs);
}

/********************************/
// float numerically less than zero
/********************************/
template<class T, class U>
inline bool float_numleq_zero(const T a_lhs, const U a_comp, const integer_type<T> max_ulps_diff = 2)
{
   return float_numeq_zero(a_lhs,a_comp,max_ulps_diff) ? true : float_neg(a_lhs);
}

/********************************/
// float greater than
/********************************/
template<class T, class U> 
inline bool float_numgt_zero(const T a_lhs, const U a_comp, const integer_type<T> max_ulps_diff = 2)
{
   // not less than or equal -> greater than
   return !float_numleq_zero(a_lhs, a_comp, max_ulps_diff); 
}

/********************************/
// float less than
/********************************/
template<class T, class U> 
inline bool float_numlt_zero(const T a_lhs, const U a_comp, const integer_type<T> max_ulps_diff = 2)
{
   // not less than or equal -> greater than
   return !float_numgeq_zero(a_lhs, a_comp, max_ulps_diff); 
}

} /* namespace numeric */
} /* namespace libmda */

#endif /* LIBMDA_TESTING_FLOAT_IS_EQUAL_H_INCLUDED */
