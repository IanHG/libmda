#ifndef LIBMDA_DIMENSIONS_CHECK_H
#define LIBMDA_DIMENSIONS_CHECK_H

namespace libmda
{
namespace utility
{

// dimension_check implementation
template<int N, int M>
struct dimensions_check_
{
   template<class L, class R>
   static void apply(const L& l, const R& r)
   {
      assert(l.template extent<N>()==r.template extent<N>());
      dimensions_check_<N+1,M>::apply(l,r);
   }
};

template<int N>
struct dimensions_check_<N,N> // end recursion on N === M
{
   template<class L, class R>
   static void apply(const L& l, const R& r) { } // we do nothing
};

struct dimensions_check
{
   template<class L, class R>
   static void apply(const L& l, const R& r)
   {
      static_assert(L::order == R::order, "order not equal");
      dimensions_check_<0,L::order>::apply(l,r);
   }
};


struct dimensions_nocheck
{
   template<class L, class R>
   static void apply(const L& l, const R& r)
   {
      static_assert(L::order == R::order, "order not equal");
   }
};

} // namespace utility
} // namespace libmda

#endif /* LIBMDA_DIMENSIONS_CHECK_H */
