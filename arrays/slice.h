#ifndef LIBMDA_ARRAYS_SLICE_H_INCLUDED
#define LIBMDA_ARRAYS_SLICE_H_INCLUDED

namespace libmda
{
namespace arrays
{

struct slice
{
   using size_type = size_t;

   slice(size_type a_start, size_type a_length, size_type a_stride = 1):
      m_start(a_start), m_length(a_length), m_stride(a_stride) { }

   size_type operator()(size_type i) const { return m_start + i*m_stride; };

   const size_type m_start;
   const size_type m_length;
   const size_type m_stride;
};

} // namespace arrays
} // namespace libmda

#endif /*LIBMDA_ARRAYS_SLICE_H_INCLUDED */
