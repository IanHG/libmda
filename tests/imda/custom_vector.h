#ifndef LIBMDA_TESTS_CUSTOM_VECTOR_H_INCLUDED
#define LIBMDA_TESTS_CUSTOM_VECTOR_H_INCLUDED

#include "../../util/enforce.h"
#include "../../imda/imda_interface.h"

template<class T, class trait>
class custom_vector;

template<class T, class S = size_t>
struct custom_vector_trait
{
   using type       = custom_vector<T,custom_vector_trait<T,S> >;
   using value_type = T;
   using size_type  = S;
   static const size_t order = 1;
};

template<class T, class trait = custom_vector_trait<T,int> >
class custom_vector:
   public libmda::imda::iextended_scalar<custom_vector<T>, trait>
{
   using size_type = typename trait::size_type;

   public:
      explicit custom_vector(size_type i): size_(i), elem_(new T[i])
      {
      }

      ~custom_vector()
      {
         if(elem_)
         {
            delete[] elem_;
         }
      }

      template<class U>
      custom_vector& operator=(U&& rhs)
      {  
         libmda::imda::iextended_scalar<custom_vector<T>,trait>::operator=(std::forward<U>(rhs));
         return *this;
      }

      T& at(size_type i)       
      { 
         return elem_[i]; 
      } 
      
      const T& at(size_type i) const 
      { 
         return elem_[i]; 
      } 
      
      size_type size() const
      {
         return size_;
      }

      template<int I
             , libmda::util::Enforce_order_bound<custom_vector<T>,I> = 0
             >
      size_type extent() const
      {
         return size_;
      }
   
   private:
      size_type size_ = 0;
      T* elem_ = nullptr;
};

#endif /* LIBMDA_TESTS_CUSTOM_VECTOR_H_INCLUDED */
