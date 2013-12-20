#ifndef LIBMDA_MDA_REF_H_INCLUDED
#define LIBMDA_MDA_REF_H_INCLUDED

#include "Mda_i.h"
#include "Mda_ref.h"

namespace libmda
{
namespace arrays
{
namespace mda_impl
{

template<size_t N, typename T=double, typename U=size_t>
class Mda_ref : public Mda_i<Mda_ref<N,T,U>,N,T,U>
{ 
   public:
      typedef T value_type;
      typedef U size_type;
      static const int order = N;
      
      using Mda_i<Mda_ref<N,T,U>,N,T,U>::operator();
      using Mda_i<Mda_ref<N,T,U>,N,T,U>::operator=;
      
      template<typename... Ts>
      Mda_ref(value_type* ptr, Ts&&... ts): m_ptr{ptr}
                                          , m_slice{std::forward<Ts>(ts)...}
      {
      }
      
      ////
      // operator()
      //
      ////
      template<typename... ints>
      auto operator()(ints... i)       -> decltype(at(i...)) { return at(i...); }
      
      template<typename... ints>
      auto operator()(ints... i) const -> decltype(at(i...)) { return at(i...); }
      
      //////
      // at() const + non const version
      //
      //////
      template<typename... ints
             , utility::Requesting_elem<order,size_type,ints...> = 0
             >
      value_type&       at(ints... i)       { return m_ptr[m_slice.index(i...)]; }
      
      template<typename... ints 
             , utility::Requesting_elem<order,size_type,ints...> = 0
             >
      value_type const& at(ints... i) const { return m_ptr[m_slice.index(i...)]; }
      
      ////
      // size() and extent()
      //
      ////
      size_type size() const { return m_slice.size(); }
      
      template<size_t D, iEnable_if<D<N> = 0>
      size_type extent() const { return m_slice.template extent<D>(); }

   private:
      Mda_slice<N,size_type> m_slice;
      value_type*            m_ptr; // no ownership over this!
};

} // namespace mda_impl
} // namespace arrays
} // namespace libmda

#endif /*  LIBMDA_MDA_REF_H_INCLUDED */
