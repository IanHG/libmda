#ifndef LIBMDA_ARRAYS_SCALAR_H_INCLUDED
#define LIBMDA_ARRAYS_SCALAR_H_INCLUDED

#include "../expr/interface.h"

namespace libmda
{
namespace arrays
{

template<class T, class S = size_t>
class scalar: 
   public libmda::expression_interface<scalar<T,S>,traits<scalar<T,S> > >
{
   public:
      using value_type = typename std::decay<T>::type;
      
      explicit scalar()
      {
      }

      explicit scalar(T t): m_elem(t)
      {
      }

      scalar<T,S>& operator=(const T& t)
      {
         m_elem = t;
         return *this;
      }
      
      //
      // at
      //
      T& at()
      {
         return m_elem;
      }
      // const version
      const T& at() const
      {
         return m_elem;
      }

      //
      // size
      //
      S size() const
      {
         return 1;
      }

      //
      // extent
      //
      template<size_t N>
      S extent() const
      {
         return 0;
      }

   private:
      T m_elem;
};

//template<class T, class S>
//std::ostream& operator<<(std::ostream& a_ostream, const scalar<T,S>& scal)
//{
//   a_ostream << scal.at();
//   return a_ostream;
//}

template<class S = size_t, class T>
scalar<T,S> make_scalar(T&& t)
{
   return scalar<T,S>(std::forward<T>(t));
}

} /* namespace arrays */
} /* namespace libmda */

template<class T, class S>
struct traits<libmda::arrays::scalar<T,S> >
{
   using value_type = T;
   using size_type = S;
   using type = libmda::arrays::scalar<T,S>;
   static const int order = 0;
};

#endif /* LIBMDA_ARRAYS_SCALAR_H_INCLUDED */
