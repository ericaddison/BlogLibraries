#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ArrayPrint.h"

void resetExampleValues(int N, int M, double *x, double *y, double *A, double *B, double* Z);

int main(){
  int N=3;
  int M = N+1;
  int inc=1;
  char trans='N';
  double alpha=2;
  double one=1;
  double zero=0;

  // allocate memory for arrays
  double *x = malloc(N*sizeof(double));
  double *y = malloc(N*sizeof(double));
  double *A = malloc(N*N*sizeof(double));
  double *B = malloc(N*M*sizeof(double));
  double *Z = malloc(N*M*sizeof(double));
  
  // print out initial values
  resetExampleValues(N,M,x,y,A,B,Z);
  puts("");
  printVec(N, x, "x");
  printVec(N,y,"y");
  puts("");
  printVec(N*N,A,"A(:)");
  printVec(N*M,B,"B(:)");
  puts("");
  printMatrixColMajor(N,N,A,"A ColMajor");
  puts("");
  printMatrixColMajor(N,M,B,"B ColMajor");
  puts("");

  // call dscal_ (x = ax)
  dscal_(&N, &alpha, x, &inc);
  printVec(N, x, "dscal (2x)\t");
  resetExampleValues(N,M,x,y,A,B,Z);

  // call daxpy_ (y = ax+y)
  daxpy_(&N,&alpha,x,&inc,y,&inc);
  printVec(N, y, "daxpy (2x+y)\t");
  resetExampleValues(N,M,x,y,A,B,Z);

  // call dgemv_ (general matrix-vector multiply)
  dgemv_(&trans,&N,&N,&one,A,&N,x,&inc,&zero,y,&inc);
  printVec(N, y, "dgemv (Ax+0y)\t");
  resetExampleValues(N,M,x,y,A,B,Z);

  // call dger_ (vector outer product)
  dger_(&N,&N,&one,x,&inc,y,&inc,Z,&N);
  printMatrixColMajor(N, N, Z, "dger  (xy')\t");
  resetExampleValues(N,M,x,y,A,B,Z);

  // call dgemm_ (general matrix-matrix multiply)
  dgemm_(&trans,&trans,&N,&M,&N,&one,A,&N,B,&N,&one,Z,&N);
  printMatrixColMajor(N, M, Z, "dgemm A*B\t");
  resetExampleValues(N,M,x,y,A,B,Z);

  // free the malloc'd memory
  free(x);
  free(y);
  free(A);
  free(B);
  free(Z);

  puts("");
  return 0;
}


// reset the values of the vectors and matrix to some default
void resetExampleValues(int N, int M, double *x, double *y, double *A, double *B, double* Z){
  int i=0;
  int j=0;
  for(i=0; i<N; i++){
    x[i] = i+1;
    y[i] = i+2;
    for(j=0; j<N; j++)
      A[i*N+j] = 2*i+j;
    for(j=0; j<M; j++){
      B[i*M+j] = i+j;
      Z[i*M+j] = 0;
    }
  }	
}
