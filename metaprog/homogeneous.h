#ifndef LIBMDA_HOMOGENEOUS_H_INCLUDED
#define LIBMDA_HOMOGENEOUS_H_INCLUDED

// Disclamer:
//    All credit goes to Andy Prowl from his answer on this question on Stack Overflow
//    http://stackoverflow.com/questions/14261183/how-to-make-generic-computations-over-heterogeneous-argument-packs-of-a-variadic
//

namespace libmda
{
namespace metaprog
{

//===============================================================================
// METAFUNCTION FOR COMPUTING THE UNDERLYING TYPE OF HOMOGENEOUS PARAMETER PACKS

// Used as the underlying type of non-homogeneous parameter packs
struct null_type
{
};

// Declare primary template
template<typename... Ts>
struct homogeneous_type;

// Base step
template<typename T>
struct homogeneous_type<T>
{
   using type = T;
   static const bool isHomogeneous = true;
};

// Induction step
template<typename T, typename... Ts>
struct homogeneous_type<T, Ts...>
{
   // The underlying type of the tail of the parameter pack
   using type_of_remaining_parameters = typename homogeneous_type<Ts...>::type;

   // True if each parameter in the pack has the same type
   static const bool isHomogeneous = std::is_same<T, type_of_remaining_parameters>::value;

   // If isHomogeneous is "false", the underlying type is the fictitious null_type
   using type = typename std::conditional<isHomogeneous, T, null_type>::type;
};

// Meta-function to determine if a parameter pack is homogeneous
template<typename... Ts>
struct is_homogeneous_pack
{
   static const bool value = homogeneous_type<Ts...>::isHomogeneous;
};

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_HOMOGENEOUS_H_INCLUDED */
