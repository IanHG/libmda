#ifndef IAXPY_H_INCLUDED
#define IAXPY_H_INCLUDED

extern "C"
{
   void daxpy_(int* n, double* a, double* x, int* incx, double* y, int* incy);
}

#endif /* IAXPY_H_INCLUDED */
