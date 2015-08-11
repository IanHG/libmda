#ifndef IDGEMM_H_INCLUDED
#define IDGEMM_H_INCLUDED

extern "C"
{

void dgemm_(char* transa, char* transb, int* m, int* n, int* k
          , double* alpha, double* a, int* lda
          , double* b, int* ldb
          , double* beta, double* c, int* ldc);

}



#endif /* IDGEMM_H_INCLUDED */
