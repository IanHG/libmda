#ifndef LIBMDA_MDA_H
#define LIBMDA_MDA_H

#include<ostream>
#include "Mda_i.h"
#include "Mda_slice.h"
#include "Mda_init.h"
#include "../utility/Requesting.h"
#include "../ostream_output.h"

namespace libmda
{
namespace arrays
{

namespace mda_impl
{

template<size_t N, typename T=double, typename U=size_t>
class Mda: public Mda_i<Mda<N,T,U>,N,T,U>
{
   public:
      // public typedefs needed by libmda interface
      typedef T value_type;
      typedef U size_type;
      static const int order = N;
   public:
      // constructors
      template<typename... ints>
      Mda(ints... i): m_slice(i...) { allocate(); }
      //Mda(Mda_initializer<N,T,U> init): m_slice() 
      //{ std::cout << " this !" << std::endl; }
      ~Mda() { deallocate(); } // destructor
      Mda& operator=(const Mda& a_mda)
      { MDACopy((*this),a_mda); return *this; }
      using Mda_i<Mda<N,T,U>,N,T,U>::operator=;

      // operator()
      template<typename... ints, 
               iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               //utility::Requesting_elem<order,size_type,ints...> = 0>
      value_type&       operator()(ints... i)       { return at(i...); }
      template<typename... ints, 
               iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               //utility::Requesting_elem<order,size_type,ints...> = 0>
      value_type const& operator()(ints... i) const { return at(i...); }
      
      // at()
      template<typename... ints, 
               iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               //utility::Requesting_elem<order,size_type,ints...> = 0>
      value_type&       at(ints... i)       { return m_ptr[m_slice.index(i...)]; }
      template<typename... ints, 
               iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
               //utility::Requesting_elem<order,size_type,ints...> = 0>
      value_type const& at(ints... i) const { return m_ptr[m_slice.index(i...)]; }
      
      // size() and extent()
      size_type size() const { return m_slice.size(); }
      template<size_t D, iEnable_if<D<N> = 0>
      size_type extent() const { return m_slice.template extent<D>(); }

   private:
      Mda_slice<N,size_type> m_slice;
      value_type*            m_ptr;
      
      // allocate and deallocate functions
      void allocate()    { m_ptr = new value_type[m_slice.size()]; }
      void deallocate()  { delete[] m_ptr; m_ptr=nullptr; }
};



} // namepsace mda_impl

} // namespace arrays
} // namespace libmda

#endif /* LIBMDA_MDA_H */
