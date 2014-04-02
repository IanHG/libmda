#ifndef LIBMDA_SLICE_H
#define LIBMDA_SLICE_H

namespace libmda
{
namespace detail
{

template<class I>
class slice_
{
   using size_type = size_t;
   public:
      slice_(size_type a_lower, size_type a_upper):
         m_lower(a_lower), m_upper(a_upper) { };
      
      size_type lower() const { return m_lower; }
      size_type upper() const { return m_upper; }
      
      using index = I;
   private:
      const size_type m_lower;
      const size_type m_upper;
};

class slice__
{
   using size_type = size_t;
   public:
      slice__(size_type a_lower, size_type a_upper, size_type a_stride):
         m_lower(a_lower), m_upper(a_upper), m_stride(a_stride) { };
      
      size_type lower()  const { return m_lower; }
      size_type upper()  const { return m_upper; }
      size_type stride() const { return m_stride; }
      
   private:
      const size_type m_lower;
      const size_type m_upper;
      const size_type m_stride;
};

} // namespace detail

template<class I, typename T>
detail::slice_<I> slice(I, T lower, T upper)
{ return detail::slice_<I>(lower,upper); }

template<typename T>
detail::slice__ slice(T lower, T upper, T stride = 1)
{ return detail::slice__(lower,upper,stride); }

} // namespace libmda

#endif /* LIBMDA_SLICE_H */
