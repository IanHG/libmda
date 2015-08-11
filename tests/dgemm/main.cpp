#include <iostream>
#include <algorithm>
#include "../../iblas/igemm.h"
#include "../../iblas/iaxpy.h"
#include "../../storage/storage.h"
#include "../../storage/mda.h"
#include "../../new_expr/scalar_expression.h"

using std::max;
using namespace libmda::storage;
using namespace libmda::expr;

int main()
{
   char transa = 'n';
   char transb = 'n';

   scalar_value<int> m {2};
   int n = 2;
   int k = 2;

   double alpha = 1.0;
   mda<2,double> a(int(m),k);
   int lda = max(1,k);

   mda<2,double> b(n,k);
   int ldb = max(1,k);
   
   double beta = 1.0;
   mda<2,double> c(n,int(m));
   int ldc = max(1,int(m));

   for(int i=0; i<b.size(); ++i)
   {
      a[i] = 2.0;
      b[i] = 2.0;
      c[i] = 2.0;
   }

   a.at(0,0) = 1.0;
   a.at(0,1) = 1.0;


   dgemm_(&transa,&transb,&m,&n,&k,&alpha,a.data(),&lda,b.data(),&ldb,&beta,c.data(),&ldc);
   
   int incx = 1;
   int incy = 1;
   int size = b.size();
   daxpy_(&size,&alpha,b.data(),&incx,c.data(),&incy);

   std::cout << a << std::endl;
   std::cout << b << std::endl;
   std::cout << c << std::endl;

   return 0;
}
