#ifndef LIBMDA_MIXIN_IF_H
#define LIBMDA_MIXIN_IF_H

namespace libmda
{
namespace utility
{

/**
 * mixin_if: can be used as a switch to decide whether or not to use a mixin...
 *           the mixin MUST provide a typedef for its base_type,
 *           which is what the mixin itself would inherit from
 **/
template<bool, class>
struct mixin_if;

template<class A>
struct mixin_if<true, A >: A
{ };

template<class A>
struct mixin_if<false, A >: A::base_type
{ };

} // namespace utility
} // namespace libmda

#endif /* LIBMDA_MIXIN_IF_H */
