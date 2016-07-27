#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ArrayPrint.h"

void resetExampleValues(int N, double *x, double *y, double *A, double* Z);

int main(){
  int N=3;
  int inc=1;
  char trans='N';
  double alpha=2;
  double one=1;
  double zero=0;

  // allocate memory for arrays
  double *x = malloc(N*sizeof(double));
  double *y = malloc(N*sizeof(double));
  double *A = malloc(N*N*sizeof(double));
  double *Z = malloc(N*N*sizeof(double));
  
  // print out initial values
  resetExampleValues(N,x,y,A,Z);
  puts("");
  printVec(N, x, "x");
  printVec(N,y,"y");
  printMatrixRowMajor(N,N,A,"A RowMajor");
  printMatrixColMajor(N,N,A,"A ColMajor");
  puts("");

  // call dscal_
  dscal_(&N, &alpha, x, &inc);
  printVec(N, x, "dscal (2x)\t");
  resetExampleValues(N,x,y,A,Z);

  // call daxpy_
  daxpy_(&N,&alpha,x,&inc,y,&inc);
  printVec(N, y, "daxpy (2x+y)\t");
  resetExampleValues(N,x,y,A,Z);

  // call dgemv_
  dgemv_(&trans,&N,&N,&one,A,&N,x,&inc,&zero,y,&inc);
  printVec(N, y, "dgemv (Ax+0y)\t");
  resetExampleValues(N,x,y,A,Z);

  // call dger_ (outer product)
  dger_(&N,&N,&one,x,&inc,y,&inc,Z,&N);
  printMatrixColMajor(N, N, Z, "dger  (xy')\t");
  resetExampleValues(N,x,y,A,Z);

  // free the malloc'd memory
  free(x);
  free(y);
  free(A);
  free(Z);

  puts("");
  return 0;
}


// reset the values of the vectors and matrix to some default
void resetExampleValues(int N, double *x, double *y, double *A, double* Z){
  int i=0;
  int j=0;
  for(i=0; i<N; i++){
    x[i] = i+1;
    y[i] = i+2;
    for(j=0; j<N; j++){
      A[i*N+j] = 2*i+j;
      Z[i*N+j] = 0;
    }
  }
}
