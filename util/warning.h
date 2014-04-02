#ifndef LIBMDA_WARNING_H_INCLUDED
#define LIBMDA_WARNING_H_INCLUDED

namespace libmda
{
namespace util
{
namespace detail
{

/////
// struct that will overflow and print integer s at compile-time
//
////
template<size_t s>
struct overflow
{
   operator char() { return (s + 256); }
};

} // namespace detail

/////
// function that will print warning message at compile-time
// warning message must be made as a class/struct
////
template<class MESSAGE>
void print_warning(MESSAGE)
{
   char(detail::overflow<sizeof(MESSAGE)>());
};

/////
// static warning
// will print static warning depending on condition
/////
//#define static_warning(cond,msg)\
//template<bool> struct static_warning_impl\
//{\
//   static void apply()\
//   {\
//   }\
//};\
//\
//template<> struct static_warning_impl<false>\
//{\
//   static void apply()\
//   {\
//      ::detail::print_warning(msg());\
//   }\
//};\
//\
//static_warning_impl<cond>::apply()

} // namespace util
} // namespace libmda

#endif /* LIBMDA_WARNING_H_INCLUDED */
