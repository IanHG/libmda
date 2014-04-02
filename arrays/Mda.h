#ifndef LIBMDA_MDA_H
#define LIBMDA_MDA_H

#include<ostream>
#include "Mda_i.h"
#include "Mda_slice.h"
#include "Mda_init.h"
#include "Mda_ref.h"
#include "do_slice.h"
#include "do_fold_last.h"
#include "../util/Requesting.h"
#include "../ostream_output.h"
#include "scalar.h"

namespace libmda
{
namespace arrays
{

template<size_t N, typename T=double, typename U=size_t>
class Mda: public Mda_i<Mda<N,T,U>,N,T,U>
{
   public:
      // public typedefs needed by libmda interface
      typedef T value_type;
      typedef U size_type;
      static const int order = N;
      using This = Mda<N,T,U>;
      
      explicit Mda() = delete;
   public:
      // c-tor
      template<class... Is>
      explicit Mda(Is... is): m_slice(0,is...) 
      { 
         allocate(); 
      }
      Mda(const Mda& a_mda): m_slice(a_mda.m_slice)
      {
         allocate();
         MDACopy((*this),a_mda); 
      }
      Mda(Mda&& a_mda): m_slice(a_mda.m_slice), m_ptr(nullptr)
      {
         std::swap(m_ptr,a_mda.m_ptr);
      }
      // d-tor
      ~Mda() 
      { 
         deallocate(); 
      }


      Mda& operator=(const Mda& a_mda)
      { 
         MDACopy((*this),a_mda); 
         return *this; 
      }
      
      using Mda_i<Mda<N,T,U>,N,T,U>::operator=;
      
      //
      // at()
      //
      template<class... Is
             , iEnable_if<util::detail::requesting_elem<order,size_type,Is...>::value> = 0
             //, util::Requesting_elem<order,size_type,ints...> = 0
             >
      value_type& at(Is... is)
      { 
         return m_ptr[m_slice.index(is...)]; 
      }
      // const version
      template<class... Is
             , iEnable_if<util::detail::requesting_elem<order,size_type,Is...>::value> = 0
             //, util::Requesting_elem<order,size_type,ints...> = 0
             >
      value_type const& at(Is... is) const 
      { 
         return m_ptr[m_slice.index(is...)]; 
      }

      template<class I>
      value_type& vec_at(I i)
      {
         return m_ptr[i];
      }
      template<class I>
      value_type const& vec_at(I i) const
      {
         return m_ptr[i];
      }
      
      //
      // operator()
      //
      template<class... Is>
      auto operator()(Is... is)
         -> decltype(std::declval<This>().at(is...))
      { 
         return at(is...); 
      }
      // const version
      template<class... Is>
      auto operator()(Is... is) const
         -> decltype(std::declval<const This>().at(is...))
      { 
         return at(is...); 
      }
      
      
      //
      // size() 
      //
      size_type size() const 
      { 
         return m_slice.size(); 
      }
      
      //
      // extent
      //
      template<size_t D
             , iEnable_if<D<N> = 0
             >
      size_type extent() const 
      { 
         return m_slice.template extent<D>(); 
      }

      //
      //
      //
      template<class... Args>
      Mda_ref<sizeof...(Args),T,U> slicing(Args&&... args)
      {
         Mda_slice<sizeof...(Args)> ref;
         ref.start() = do_slice(m_slice,ref,std::forward<Args>(args)...);
         ref.init_size();
         return {m_ptr,ref};
      }

      Mda_ref<N+1,T,U> fold_last(size_t i)
      {
         Mda_slice<N+1> ref;
         do_fold_last(m_slice,ref,i);
         ref.start() = m_slice.start();
         ref.init_size();
         return {m_ptr,ref};
      }
      
      template<class... Is>
      Mda_ref<sizeof...(Is),T,U> reshape(Is... is)
      {
         Mda_slice<sizeof...(Is)> ref(0,is...);
         return {m_ptr,ref};
      }
      
      template<class P>
      void permute()
      {
         m_slice.template permute<P>();
      }

      //
      // get_slice
      //
      Mda_slice<N,size_type>& get_slice()
      {
         return m_slice;
      }
      Mda_slice<N,size_type> const& get_slice() const
      {
         return m_slice;
      }

      value_type* get() const
      {
         return m_ptr;
      }

   private:
      Mda_slice<N,size_type> m_slice;
      value_type*            m_ptr;
      
      //
      // allocate and deallocate functions
      //
      void allocate()    
      { 
         m_ptr = new value_type[m_slice.size()]; 
      }
      void deallocate()  
      { 
         delete[] m_ptr; m_ptr=nullptr; 
      }
};

template<class T, class U>
class Mda<0,T,U>: public scalar<T,U>
{
   public:
      Mda<0,T,U>& operator=(const T& t)
      {
         scalar<T,U>::operator=(t);
         return *this;
      }
};


} // namespace arrays
} // namespace libmda

#endif /* LIBMDA_MDA_H */
