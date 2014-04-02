#ifndef LIBMDA_MULTIPLE_RETURN_H_INCLUDED
#define LIBMDA_MULTIPLE_RETURN_H_INCLUDED

namespace libmda
{
namespace util
{
namespace detail
{

//
//
//
template<class... T>
using return_type = std::tuple<T...>;

//
//
//
template<class... T>
inline return_type<T...> ret(T&&... t)
{
   return return_type<T...>(std::forward<T>(t)...);
}

//
// struct that ignores assignment from any type
//
struct ignore_assignment
{
   template<class T>
   ignore_assignment& operator=(T&&) { return *this; }
} _;

} // namespace detail

using detail::_;
using detail::return_type;
using detail::ret;

} // namespace util
} // namespace libmda

#endif /* LIBMDA_MULTIPLE_RETURN_H_INCLUDED */
