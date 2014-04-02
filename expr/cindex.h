#ifndef LIMBDA_CINDEX_H_INCLUDED
#define LIMBDA_CINDEX_H_INCLUDED

#include"../meta/index_list.h"
#include"../units/meta_string.h"

namespace libmda
{

//
// old index type using char
//
template<char C> 
struct cindex: util::meta_string<C>
{ 
};

//
// new index type... using ints for easier meta programming
//
template<unsigned N>
struct index: meta::index_list<N>
{
};

} // namespace libmda

#endif /* LIMBDA_CINDEX_H_INCLUDED */
