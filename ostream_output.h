#ifndef LIBMDA_OSTREAM_OUTPUT_H_INCLUDED
#define LIBMDA_OSTREAM_OUTPUT_H_INCLUDED

#include "IMDA.h"
#include "utility/for_loop_expand.h"
#include "utility/require.h"

namespace libmda
{

struct op_output
{
   template<class V,  typename... ints>
   static void apply(const V& v, std::ostream& s, const ints... i)
   {
      s << " " << v.at(i...);
   }
};

/***************************/
/* vector output           */
/***************************/
template<class A, Require_order<A,1> = 0>
std::ostream& operator<<(std::ostream& a_ostream, const IMDAAccessComb<A>& mda)
{
   a_ostream << "(";
   for(Size_type<A> i = 0; i<mda.size()-1; ++i)
      a_ostream << mda.at(i) << ",";
   a_ostream << mda.at(mda.size()-1) << ")";
   return a_ostream;
}

/***************************/
/* matrix output           */
/***************************/
template<class A, Require_order<A,2> = 0>
std::ostream& operator<<(std::ostream& a_ostream, const IMDAAccessComb<A>& mda)
{
   a_ostream << mda.template extent<0>() << "x" 
             << mda.template extent<1>() << "\n";
   for(Size_type<A> i=0; i<mda.template extent<0>(); ++i)
   {
      for(Size_type<A> j=0; j<mda.template extent<1>(); ++j)
         a_ostream << " " << mda.at(i,j);
      a_ostream << "\n";
   }
   return a_ostream;
}

/***************************/
/* 3rd order tensor output */
/***************************/
template<class A, Require_order<A,3> = 0>
std::ostream& operator<<(std::ostream& a_ostream, const IMDAAccessComb<A>& mda)
{
   a_ostream << mda.template extent<0>() << "x" 
             << mda.template extent<1>() << "x" 
             << mda.template extent<2>() << "\n";
   for(Size_type<A> k=0; k<mda.template extent<2>(); ++k)
   {
      for(Size_type<A> i=0; i<mda.template extent<0>(); ++i)
      {
         for(Size_type<A> j=0; j<mda.template extent<1>(); ++j)
            a_ostream << " " << mda.at(i,j,k);
         a_ostream << "\n";
      }
      a_ostream << "\n";
   }
   return a_ostream;
}
   
/******************************/
/* higher order tensor output */
/*******************************/
template<class A, Require_order_geq<A,4> = 0>
std::ostream& operator<<(std::ostream& a_ostream, const IMDAAccessComb<A>& mda)
{
   utility::for_loop_expand<op_output>::apply(mda,a_ostream);
   return a_ostream;
}

} // namespace libmda

#endif /* LIBMDA_OSTREAM_OUTPUT_H_INCLUDED */
