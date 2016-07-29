#include <stdio.h>
#include "ArrayPrint.h"

// print a vector v of length N, with prepended string "s = [...]"
void printVec(int N, double* v, const char * s){
  int i=0;
  printf("%s = [",s);
  for(i=0; i<N-1; i++)
    printf("%g, ", v[i]);
  printf("%g]\n", v[N-1]);
}


// print a linear array as a matrix in row major order
// matrix has M rows and N columns
void printMatrixRowMajor(int M, int N, double* m, const char * s){
  int i=0;
  int j=0;
  printf("%s = \n",s);
  for(i=0; i<M; i++)
  {
    printf("\t[");
    for(j=0; j<N-1; j++)
      printf("%3g, ", m[i*N+j]);
    printf("%3g]\n", m[i*N+(N-1)]);
  }  
}

// print a linear array as a matrix in column major order
// matrix has M rows and N columns
void printMatrixColMajor(int M, int N, double* m, const char * s){
  int i=0;
  int j=0;
  printf("%s = \n",s);
  for(i=0; i<M; i++)
  {
    printf("\t[");
    for(j=0; j<N-1; j++)
      printf("%3g, ", m[j*M+i]);
    printf("%3g]\n", m[(N-1)*M+i]);
  }  
}
