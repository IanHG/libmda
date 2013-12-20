#ifndef LIBMDA_METAPROG_TYPE_H
#define LIBMDA_METAPROG_TYPE_H

namespace libmda
{
namespace metaprog
{

// alternative names: encapsulate_type
//                    use_as_type

// struct for giving class T the name "type"
// primarily used for inheritance in metaprogramming classes/funcitons
template<class T> struct make_type
{
   using type = T;
};

} // namespace metaprog
} // namespace libmda

#endif /* LIBMDA_METAPROG_POP_BACK_H */
