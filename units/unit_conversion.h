#ifndef LIBMDA_UNIT_CONVERSION_H
#define LIBMDA_UNIT_CONVERSION_H


namespace libmda
{
namespace units
{
namespace unit_conversion
{

// struct for holding conversion constants 
// usage: converter<au,si> for convert from au to si
template<class A, class B> struct converter;

template<class A, class B, class C=Unit_system<B> >
A convert(B);

// F_si = convert<si>(F_au);

} // namespace unit_conversion
} // namespace units
} // namespace libmda

#endif /* LIBMDA_UNIT_CONVERSION_H */
