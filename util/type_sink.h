#ifndef LIBMDA_TYPE_SINK_H_INCLUDED
#define LIBMDA_TYPE_SINK_H_INCLUDED

namespace libmda
{
namespace util
{

//////
// type sink
//
/////
template<typename... Ts>
struct type_sink: std::true_type 
{
};

} // namespace util
} // namespace libmda

#endif /* LIBMDA_TYPE_SINK_H_INCLUDED */
