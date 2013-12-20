#ifndef LIMBDA_METAPROG_TAG_H
#define LIMBDA_METAPROG_TAG_H

namespace libmda
{
namespace metaprog
{

template<class T>
using Tag = typename T::tag;

} // namespace metaprog
} // namespace libmda

#endif /* LIMBDA_METAPROG_TAG_H */
