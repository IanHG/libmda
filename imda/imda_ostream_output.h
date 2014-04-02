#ifndef LIBMDA_IMDA_OSTREAM_OUTPUT_H_INCLUDED
#define LIBMDA_IMDA_OSTREAM_OUTPUT_H_INCLUDED

#include"imda_access.h"
#include"../util/for_loop_expand.h"
#include"../util/require.h"

namespace libmda
{
namespace imda
{
namespace detail
{

//
// functor for outputting
//
struct op_output
{
   //template<class V,  typename... ints>
   //static void apply(const V& v, std::ostream& s, const ints... i)
   //{
   //   s << " " << v.at(i...);
   //}
   template<class V,  typename... ints>
   void operator()(const V& v, std::ostream& s, const ints... i)
   {
      s << " " << v.at(i...);
   }
};

}// namespace detail

/***************************/
/*                         */
/* number output           */
/*                         */
/***************************/
template<class A, Require_order<A,0> = 0>
std::ostream& operator<<(std::ostream& a_ostream, const access_combined<A>& mda)
{
   a_ostream << mda.at();
   return a_ostream;
}

/***************************/
/*                         */
/* vector output           */
/*                         */
/***************************/
template<class A
       , Require_order<A,1> = 0
       >
std::ostream& operator<<(std::ostream& a_ostream, const access_combined<A>& mda)
{
   a_ostream << "(";
   if(mda.size() > 0)
   {
      for(Size_type<A> i = 0; i<mda.size()-1; ++i)
         a_ostream << mda.at(i) << ",";
      a_ostream << mda.at(mda.size()-1);
   }
   a_ostream << ")";
   return a_ostream;
}

/***************************/
/*                         */
/* matrix output           */
/*                         */
/***************************/
template<class A
       , Require_order<A,2> = 0
       >
std::ostream& operator<<(std::ostream& a_ostream, const access_combined<A>& mda)
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
/*                         */
/* 3rd order tensor output */
/*                         */
/***************************/
template<class A
       , Require_order<A,3> = 0
       >
std::ostream& operator<<(std::ostream& a_ostream, const access_combined<A>& mda)
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
/*                            */
/* higher order tensor output */
/*                            */
/******************************/
template<class A
       , Require_order_geq<A,4> = 0
       >
std::ostream& operator<<(std::ostream& a_ostream, const access_combined<A>& mda)
{
   util::for_each_elem(detail::op_output(),mda,a_ostream);
   return a_ostream;
}

} // namespace imda
} // namespace libmda

#endif /* LIBMDA_IMDA_OSTREAM_OUTPUT_H_INCLUDED */
