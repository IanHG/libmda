#ifndef MDA_SLICE_H_INCLUDED
#define MDA_SLICE_H_INCLUDED

#include <tuple>
#include "../meta/std_wrappers.h"
#include "../util/sequence.h"

namespace libmda
{
namespace storage
{
namespace detail
{

// helper to do index calculation (think about design...)
template<size_t N>
struct index_help
{
   template<class S, class Tuple>
   static size_t apply(const S& s, const Tuple& t)
   {
   return s[N]*std::get<N>(t)+index_help<N-1>::apply(s,t);
   }
};

template<>
struct index_help<0>
{
   template<class S, class Tuple>
   static size_t apply(const S& s, const Tuple& t)
   {
      return s[0]*std::get<0>(t);
   }
};

} /* namespace detail */

template<size_t N>
class mda_slice
{
   public:
      template<class... Is
             , iEnable_if<sizeof...(Is) == N> = 0
             >
      mda_slice(size_t start, Is... is): start_{start}
                                       , extents_{is...}
                                       , strides_{}
                                       , size_{}
      {
         strides_[0] = 1;
         size_ = extents_[0];
         for(int i=1; i<N; ++i)
         {
            strides_[i] = strides_[i-1]*extents_[i-1]; 
            size_ *= extents_[i];
         }

      }

      size_t size() const
      {
         return size_;
      }
      
      template<class... Is
             , iEnable_if<sizeof...(Is) == N> = 0
             >
      size_t index(Is... is) const
      {
         return start_ + detail::index_help<N-1>::apply(strides_,std::forward_as_tuple(is...));
      }

      size_t extent(size_t n) const
      {
         return extents_[n];
      }
                        
   private:
      size_t start_;
      util::sequence<N,size_t> extents_;
      util::sequence<N,size_t> strides_;
      size_t size_;
};

} /* namespace storage */
} /* namespace libmda */

#endif /* MDA_SLICE_H_INCLUDED */
