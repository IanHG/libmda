#ifndef LIBMDA_EXPR_TAKE_OUT_TYPES_H
#define LIBMDA_EXPR_TAKE_OUT_TYPES_H

namespace libmda
{
namespace expr
{

template<class L, class R>
struct take_out_types
{
   typedef typename L::value_type value_type;
   typedef typename L::size_type  size_type;
   typedef typename L::type       type;
};

template<class R>
struct take_out_types<typename R::value_type, R>
{
   typedef typename R::value_type value_type;
   typedef typename R::size_type  size_type;
   typedef typename R::type       type;
};

} // namespace expr
} // namespace libmda

#endif  /* LIBMDA_EXPR_TAKE_OUT_TYPES_H */
