#ifndef LIBMDA_META_TYPE_SINK_H_INCLUDED
#define LIBMDA_META_TYPE_SINK_H_INCLUDED

namespace libmda
{
namespace meta
{

//////
// type sink
//
/////
template<typename... Ts>
struct type_sink: std::true_type
{
};

} /* namespace meta */
} /* namespace libmda */

#endif /* LIBMDA_META_TYPE_SINK_H_INCLUDED */
