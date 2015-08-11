#ifndef LIBMDA_UTIL_NON_COPYABLE_H_INCLUDED
#define LIBMDA_UTIL_NON_COPYABLE_H_INCLUDED

namespace libmda
{
namespace util
{

class non_copyable {
   public:
      non_copyable(const non_copyable&) = delete;
      non_copyable& operator=(const non_copyable&) = delete;
   protected:
      constexpr non_copyable() = default;
      ~non_copyable() = default;
   private:
};

} /* namespace util */
} /* namespace libmda */

#endif /* LIBMDA_UTIL_NON_COPYABLE_H_INCLUDED */
