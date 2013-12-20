#ifndef LIBMDA_MPSIZE_T_H
#define LIBMDA_MPSIZE_T_H

namespace libmda
{
namespace metaprog
{

template<size_t N>
struct mpsize_t
{
   static const size_t value = N;
   using type = size_t;
   using next = mpsize_t<N+1>;
   using prev = mpsize_t<N-1>;
};

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_MPSIZE_T_H */
