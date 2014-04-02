#ifndef LIBMDA_BASIC_USING_H_INCLUDED
#define LIBMDA_BASIC_USING_H_INCLUDED

namespace libmda
{

// using declarations to get out value_type, size_type and type of class
template<class A>
using Type       = typename A::type;
template<class A>
using Value_type = typename A::value_type;
template<class A>
using Size_type  = typename A::size_type;

template<class A>
constexpr int Order()
{ 
   return A::order; 
}

} // namespace libmda

#endif /* LIBMDA_BASIC_USING_H_INCLUDED */
