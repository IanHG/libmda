#ifndef LIBDMA_MDA_I_H
#define LIBDMA_MDA_I_H

//#include "../interface.h"
#include "../util/Requesting.h"
#include "../expr/interface.h"

namespace libmda
{
namespace arrays
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
class Mda_i : 
   public expression_interface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >
{ 
   private:
      /////
      // self functions
      //
      /////
      A&       self()       
      { 
         return static_cast<A&>(*this); 
      }
      
      A const& self() const 
      { 
         return static_cast<A const&>(*this); 
      }

   public:
      typedef T value_type;
      typedef U size_type;
      static const int order = N;
      
      //using expression_interface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >::operator();
      using expression_interface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >::operator=;
      
      /////
      // size() + extent()
      //
      /////
      template<class B = A>
      auto size() const 
         -> decltype(std::declval<const B>().self().size()) 
      { 
         return self().size(); 
      }
      
      template<size_t D, class B = A, iEnable_if<D<N> = 0>
      auto extent() const 
         -> decltype(std::declval<const B>().self().template extent<D>()) 
      { 
         return self().template extent<D>(); 
      }
      
      /////
      // operator ()
      //
      ////
      template<typename... ints, class B = A>
      auto operator()(ints... i)       
         //-> decltype(std::declval<B>().self().operator()(i...)) 
         -> decltype(std::declval<B>().self().at(i...)) 
      //{ return self().operator()(i...); }
      { 
         return self().at(i...); 
      }
      
      template<typename... ints, class B = A>
      auto operator()(ints... i) const 
         //-> decltype(std::declval<const B>().self().operator()(i...)) 
         -> decltype(std::declval<const B>().self().at(i...)) 
      //{ return self().operator()(i...); }
      { 
         return self().at(i...); 
      }
      
      /////
      // at ()
      //
      ////
      template<typename... ints, class B = A>
      auto at(ints... i)       
         -> decltype(std::declval<B>().self().at(i...)) 
      { 
         return self().at(i...); 
      }
      
      template<typename... ints, class B = A>
      auto at(ints... i) const 
         -> decltype(std::declval<const B>().self().at(i...)) 
      { 
         return self().at(i...); 
      }

      //////
      // delete copy constructor + copy assignement
      //
      //////
      //Mda_i(const Mda_i&)            = delete;
      // not the prettiest solution... but it works for now
      Mda_i& operator=(const Mda_i& other)
      { 
         return expression_interface<Mda_i<A,N,T,U>, mda_trait<Mda_i<A,N,T,U> > >::operator=(other); 
      }
};

} // namespace arrays
} // namespace libmda
#endif /* LIBDMA_MDA_I_H */
