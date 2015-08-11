#ifndef MDA_H_INCLUDED
#define MDA_H_INCLUDED

#include "storage.h"
#include "mda_slice.h"
#include "../meta/std_wrappers.h"
#include "../imda/imda_interface.h"
#include "../imda/imda_ostream_output.h"


namespace libmda
{
namespace storage
{

using imda::operator<<;

template<size_t N, class T, class Alloc>
class mda;

template<class T>
class mda_trait;

template<size_t N, class T, class Alloc>
struct mda_trait<mda<N,T,Alloc> >
{
   using value_type = T;
   using size_type = size_t;
   static const int order = N;
};


template<size_t N, class T, class Alloc = std::allocator<T> >
class mda: public mda_slice<N>
         , public storage<T,Alloc>
         , public imda::iextended<mda<N,T,Alloc>, mda_trait<mda<N,T,Alloc> > >
{
   public:
      template<class... Is
             , iEnable_if<sizeof...(Is) == N> = 0
             >
      mda(Is... is): mda_slice<N>(0,std::forward<Is>(is)...)
                   , storage<T,Alloc>(mda_slice<N>::size())
      {
      }
      
      /////
      // at
      /////
      template<class... Is
             , iEnable_if<sizeof...(Is) == N> = 0
             >
      T& at(Is... is)
      {
         return this->operator[](this->index(is...));
      }
      
      template<class... Is
             , iEnable_if<sizeof...(Is) == N> = 0
             >
      const T& at(Is... is) const
      {
         return this->operator[](this->index(is...));
      }
      
      /////
      // size
      /////
      size_t size() const
      {
         return mda_slice<N>::size();
      }

      /////
      // extent
      /////
      template<size_t D>
      size_t extent() const
      {
         return mda_slice<N>::extent(D);
      }

   private:
      //storage<T,Alloc> storage_;
      //mda_slice<N> mda_slice_;
};

} /* namespace storage */
} /* namespace libmda */

#endif /* MDA_H_INCLUDED */
