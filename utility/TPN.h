#ifndef LIBMDA_UTILITY_TPN_H
#define LIBMDA_UTILITY_TPN_H

namespace libmda
{
namespace utility
{
namespace detail
{
// Make T* with N stars by TPN<T,N>::type
template<typename T, int N> struct TPN_
{
   typedef typename TPN_<T,N-1>::type* type;
   private: TPN_() {}; // Only to prevent instantiate TPN
};

template<typename T> struct TPN_<T,0>
{
   typedef T type;
   private: TPN_() {}; // Only to prevent instantiate TPN
};
} // namespace detail
// For nicer syntax. Not implementet in MSVS yet & need gcc 4.7
template<typename T, int N> using TPN = typename detail::TPN_<T,N>::type;

} // utility
} // libmda

#endif /* LIBMDA_UTILITY_TPN_H */
