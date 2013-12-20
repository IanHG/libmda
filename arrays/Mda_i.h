#ifndef LIBDMA_MDA_I_H
#define LIBDMA_MDA_I_H

#include "../interface.h"
#include "../utility/Requesting.h"

namespace libmda
{
namespace arrays
{
namespace mda_impl
{

// forward declartation of Mda_i
template<class A, size_t N, class T, class U> class Mda_i;

// traits class for Mda_i for use with IMDA interface
template<class T> struct mda_trait;
template<class A, size_t N, class T, class U>
struct mda_trait<Mda_i<A,N,T,U> >
{
   typedef T value_type;
   typedef U size_type;
   typedef Mda_i<A,N,T,U> type;
   const static size_t order = N;
};

template<class A, size_t N, class T, class U>
class Mda_i: public expression_interface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >
             //public libmda::IMDAInterface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >
{ 
   private:
      /////
      // self functions
      //
      /////
      A&       self()       { return static_cast<A&>(*this); }
      A const& self() const { return static_cast<A const&>(*this); }

   public:
      typedef T value_type;
      typedef U size_type;
      static const int order = N;
      using expression_interface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >::operator();
      
      using libmda::expression_interface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >::operator=;
      
      /////
      // size() + extent()
      //
      /////
      auto size() const -> decltype(self().size()) { return self().size(); }
      template<size_t D, iEnable_if<D<N> = 0>
      
      auto extent() const -> decltype(self().template extent<D>()) 
      { return self().template extent<D>(); }
      
      //template<typename... ints,
      //         iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
      //         //utility::Requesting_elem<order,size_type,ints...> = 0>
      //value_type&       operator()(ints... i)       { return self()(i...); }
      //template<typename... ints, 
      //         iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
      //         //utility::Requesting_elem<order,size_type,ints...> = 0>
      //value_type const& operator()(ints... i) const { return self()(i...); }
      
      //template<typename... ints, 
      //         iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
      //         //utility::Requesting_elem<order,size_type,ints...> = 0>
      //value_type&       at(ints... i)       { return self().at(i...); }
      //template<typename... ints,
      //         iEnable_if<utility::detail::requesting_elem<order,size_type,ints...>::value> = 0>
      //         //utility::Requesting_elem<order,size_type,ints...> = 0>
      //value_type const& at(ints... i) const { return self().at(i...); }
      
      template<typename... ints>
      auto operator()(ints... i)       -> decltype(self()(i...)) { return self()(i...); }
      
      template<typename... ints>
      auto operator()(ints... i) const -> decltype(self()(i...)) { return self()(i...); }
      
      template<typename... ints>
      auto at(ints... i)       -> decltype(self().at(i...)) { return self().at(i...); }
      
      template<typename... ints>
      auto at(ints... i) const -> decltype(self().at(i...)) { return self().at(i...); }

   private:
      
      //////
      // delete copy constructor + copy assignement
      //
      //////
      Mda_i(const Mda_i&)            = delete;
      Mda_i& operator=(const Mda_i&) = delete;
};

} // namespace mda_impl
} // namespace arrays
} // namespace libmda
#endif /* LIBDMA_MDA_I_H */
