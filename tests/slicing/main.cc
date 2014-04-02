#include<typeinfo>
#include<iostream>
#include "../../meta/tuple.h"
#include "../../meta/permutation.h"
#include "../../meta/mpsize_t.h"
#include "../../arrays/slice.h"
#include "../../arrays/Mda_slice.h"
#include "../../arrays/Mda.h"

using libmda::arrays::multi_slice;
using libmda::arrays::slice;
using libmda::arrays::Mda;
//using libmda::meta::mpsize_t;
using libmda::meta::permutation;

int main()
{
   Mda<2> mda(4,4);
   
   int counter = 1;
   for(int i=0; i<mda.extent<0>(); ++i)
      for(int j=0; j<mda.extent<1>(); ++j)
      {  
         mda.at(i,j) = counter;
         ++counter;
      }  
   
   std::cout << mda << std::endl;
   
   std::cout << std::endl;
   for(int i=0; i<mda.size(); ++i)
      std::cout << mda.vec_at(i) << " ";
   std::cout << std::endl;
   
   //
   std::cout << " reshape " << std::endl;
   auto mda_reshape = mda.reshape(4,2,2);
   std::cout << mda.get_slice() << std::endl;
   std::cout << mda_reshape.get_slice() << std::endl;
   std::cout << mda_reshape << std::endl;
   mda_reshape.permute<permutation<1,2,0> >();
   std::cout << mda_reshape << std::endl;

   //
   std::cout << " rest " << std::endl;
   auto mda_slice = mda.slicing(slice(1,2,1),slice(0,3,1));
   auto mda_fold = mda.fold_last(2);
   auto mda_fold1 = mda_slice.fold_last(2);

   //
   std::cout << " permute " << std::endl;
   std::cout << mda_slice << std::endl;
   mda_slice.permute<permutation<1,0> >();
   std::cout << mda_slice << std::endl;
   
   return 0;
}
