/**
 * sequence.h
 * 
 **/

#ifndef LIBMDA_SEQUENCE_H
#define LIBMDA_SEQUENCE_H

#include <iostream>

#include "../metaprog/std_wrappers.h"

namespace libmda
{
namespace utility
{
namespace detail
{

template<int i, int j, int stride> struct for_helper
{
   template<class F>
   static void apply(F&& f)
   {
      f(i);
      for_helper<i+stride,j,stride>::apply(f);
   }
};

template<int i, int stride> 
struct for_helper<i,i,stride>
{
   template<class F>
   static void apply(F&& f) { }
};

} // namespace detail

// beware this can be slow, when using lambdas
template<int i, int j, int stride=1, class F, iEnable_if<(i-j)%stride==0> = 0 >
inline void For(F&& f)
{
   detail::for_helper<i,j,stride>::apply(f);
}

template<size_t N, typename T>
class sequence
{
   public:
      typedef T        value_type;
      static const int order = N;

   private:
      T m_sequence[N];

   public:
      /****************************
       * construction/destruction *
       ****************************/
      sequence() = default; // default construction
      //sequence(sequence<N,T>&& a_sequence) // move construction (does copy)
      //{ 
      //   //For<0,N>([this,&a_sequence](size_t i){(*this)[i]=a_sequence[i];}); // this is slow...
      //   std::cout << " move ctor " << std::endl;
      //   for(register size_t i = 0; i<N; ++i) m_sequence[i] = a_sequence[i]; 
      //}
      template<typename... U, 
               iEnable_if<(sizeof...(U) == N) && All(Convertible<U,T>()...)> = 0 >
      sequence(U&&... u): m_sequence{ static_cast<T>(std::forward<U>(u))... } 
      {
         //std::cout << " variadic ctor " << std::endl;
         //for(register size_t i = 0; i<N; ++i) std::cout << m_sequence[i] << " ";
      }// construction from variadic template
      sequence(sequence<N,T> const& a_sequence) // copy construction 
      { 
         //For<0,N>([this,&a_sequence](size_t i){(*this)[i]=a_sequence[i];}); // this is slow...
         std::cout << " copy ctor " << std::endl;
         for(register size_t i = 0; i<N; ++i) m_sequence[i] = a_sequence[i]; 
      }
      //~sequence() { }; // ian: commented out to allow for more compiler optimization..
         
      // construction from initializer list
      //sequence(std::initializer_list<value_type> init): arr{ init }
      //{ std::cout << " using initializer list ctor" << std::endl; }
      
      /************************
       * assignemnt operators *
       ************************/
      sequence<N,T>& operator=(const sequence<N,T>& a_sequence)
      {
         //For<0,N>([this,&a_sequence](size_t i){(*this)[i]=a_sequence[i];}); // this is slow :(
         for(register size_t i = 0; i<N; ++i) m_sequence[i] = a_sequence[i]; 
         return (*this);
      }
      
      /**************************
       * operator[] overloading *
       **************************/
      T&       operator[](const size_t i)       { return m_sequence[i]; }
      const T& operator[](const size_t i) const { return m_sequence[i]; }
      
      /**
       * get
       **/
      template<size_t M>
      T&       get()       { return m_sequence[M]; }
      template<size_t M>
      const T& get() const { return m_sequence[M]; }

      /************
       * get size *
       ************/
      constexpr size_t size() const { return N; }
      
      /**
       * output 
       **/
      void output(std::ostream& a_ostream = std::cout) const 
      { 
         //for(int i=0; i<N; ++i) a_ostream << " " << m_sequence[i]; 
         a_ostream << "(" << (*this)[0]; // output starting brace and first element without space
         //For<1,N>([&a_ostream,this](size_t i){a_ostream << "," << (*this)[i];});
         for(register size_t i = 1; i<N; ++i) a_ostream << "," << m_sequence[i]; 
         a_ostream << ")"; // output closing brace
      }
};

/**
 * operator== overload 
 **/
template<size_t N, typename T>
bool operator==(const sequence<N,T>& a_sequence1, const sequence<N,T>& a_sequence2)
{
   for(register size_t i=0; i<N; ++i)     // loop over dimensions
      if(a_sequence1[i] != a_sequence2[i]) // check if elements are equal
         return false;                 // if some elements are not equal we return false
   return true;                        // if all elements are equal we return true
}

/**
 * operator<< overload
 **/
template<size_t N, typename T>
std::ostream& operator<<(std::ostream& a_ostream, const sequence<N,T>& a_sequence)
{
   a_sequence.output(a_ostream);
   return a_ostream;
}

} // namespace utility
} // namespace libmda

#endif /* LIBMDA_SEQUENCE_H */
