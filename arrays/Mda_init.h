#ifndef LIBMDA_MDA_INIT_H
#define LIBMDA_MDA_INIT_H

namespace libmda
{
namespace arrays
{

namespace detail
{
template<size_t N, typename T, typename U>
struct Mda_init
{
   using type = std::initializer_list<typename Mda_init<N-1,T,U>::type>;
};

template<typename T, typename U>
struct Mda_init<1,T,U>
{
   using type = std::initializer_list<T>;
};
} // namespace detail 

template<size_t N, typename T, typename U>
using Mda_initializer = typename detail::Mda_init<N,T,U>::type;

} // namespace arrays
} // namespace libmda

#endif /* LIBMDA_MDA_INIT_H */
