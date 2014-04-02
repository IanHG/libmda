#ifndef LIBMDA_METAPROG_REQUIRES_H_INCLUDED
#define LIBMDA_METAPROG_REQUIRES_H_INCLUDED

namespace libmda
{
namespace meta
{
namespace detail
{   

template<bool B, class T>
struct requires
{
   static_assert(B, "Requirement not met...");
   using type = T;
};

} // namespace detail

template<bool B, class T = void>
using Requires = typename detail::requires<B,T>::type;

template<bool B>
using iRequires = typename detail::requires<B,int>::type;

} // namespace meta
} // namespace libmda

#endif /* LIBMDA_METAPROG_REQUIRES_H_INCLUDED */
