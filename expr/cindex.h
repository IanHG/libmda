#ifndef CINDEX_H
#define CINDEX_H

#include<iostream>

namespace libmda
{

template<char c> struct cindex { };

template<char c>
std::ostream& operator<<(std::ostream& a_stream, const cindex<c>)
{ a_stream << c; return a_stream; }

} // namespace libmda

#endif /* CINDEX_H */
