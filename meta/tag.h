#ifndef LIMBDA_METAPROG_TAG_H
#define LIMBDA_METAPROG_TAG_H

namespace libmda
{
namespace meta
{

template<class T>
using Tag = typename T::tag;

} // namespace meta
} // namespace libmda

#endif /* LIMBDA_METAPROG_TAG_H */
