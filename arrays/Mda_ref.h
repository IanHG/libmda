#ifndef LIBMDA_MDA_REF_H_INCLUDED
#define LIBMDA_MDA_REF_H_INCLUDED

#include "Mda_i.h"
#include "Mda_slice.h"

namespace libmda
{
namespace arrays
{

template<size_t N, typename T=double, typename U=size_t>
class Mda_ref : public Mda_i<Mda_ref<N,T,U>,N,T,U>
{ 
   public:
      typedef T value_type;
      typedef U size_type;
      static const int order = N;
   
   private:
      using This = Mda_ref<N,T,U>;
      
      Mda_slice<N,size_type> m_slice;
      value_type*            m_ptr; // no ownership over this!

   public:
      using Mda_i<Mda_ref<N,T,U>,N,T,U>::operator();
      using Mda_i<Mda_ref<N,T,U>,N,T,U>::operator=;
      
      template<typename... Ts>
      Mda_ref(value_type* ptr, Ts&&... ts): m_ptr{ptr}
                                          , m_slice{std::forward<Ts>(ts)...}
      {
      }
      
      //
      // get_slice
      //
      Mda_slice<N,size_type>& get_slice()
      {
         return m_slice;
      }
      // const version
      Mda_slice<N,size_type> const& get_slice() const
      {
         return m_slice;
      }
      
      //////
      // at() const + non const version
      //
      //////
      template<class... Is
             , util::Requesting_elem<order,size_type,Is...> = 0
             >
      value_type& at(Is... is)
      { 
         return m_ptr[m_slice.index(is...)]; 
      }
      
      template<class... Is 
             , util::Requesting_elem<order,size_type,Is...> = 0
             >
      value_type const& at(Is... is) const 
      { 
         return m_ptr[m_slice.index(is...)]; 
      }
      
      ////
      // operator()
      //
      ////
      template<class... Is>
      auto operator()(Is... is)
         -> decltype(std::declval<This>().at(is...))
      { 
         return at(is...); 
      }
      
      template<class... Is>
      auto operator()(Is... is) const
         -> decltype(std::declval<const This>().at(is...))
      { 
         return at(is...); 
      }
      
      ////
      // size() and extent()
      //
      ////
      auto size() const 
         -> decltype(m_slice.size())
      { 
         return m_slice.size(); 
      }
      
      template<size_t D
             , iEnable_if<D<N> = 0
             >
      auto extent() const
         -> decltype(m_slice.template extent<D>())
      { 
         return m_slice.template extent<D>(); 
      }
      
      
      Mda_ref<N+1,T,U> fold_last(size_t i)
      {
         Mda_slice<N+1> ref;
         do_fold_last(m_slice,ref,i);
         ref.start() = m_slice.start();
         ref.init_size();
         return {m_ptr,ref};
      }
      
      template<class P>
      void permute()
      {
         m_slice.template permute<P>();
      }
};

} // namespace arrays
} // namespace libmda

#endif /*  LIBMDA_MDA_REF_H_INCLUDED */
