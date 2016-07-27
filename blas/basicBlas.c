#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void resetValues(int N, double *x, double *y, double *m);
void printVec(int N, double* v, const char * s);
void printMatrixRowMajor(int M, int N, double* m, const char * s);
void printMatrixColMajor(int M, int N, double* m, const char * s);


int main(){
  int N=2;
  int inc=1;
  double alpha=2;
  char trans = 'N';
  double one = 1;
  double zero = 0;

  // allocate memory for arrays
  double *x = malloc(N*sizeof(double));
  double *y = malloc(N*sizeof(double));
  double *A = malloc(N*N*sizeof(double));
  
  // print out initial values
  resetValues(N,x,y,A);
  puts("");
  printVec(N, x, "x");
  printVec(N,y,"y");
  printMatrixRowMajor(N,N,A,"A RowMajor");
  printMatrixColMajor(N,N,A,"A ColMajor");
  puts("");

  // call dscal_
  dscal_(&N, &alpha, x, &inc);
  printVec(N, x, "dscal (2x)\t");
  resetValues(N,x,y,A);

  // call daxpy_
  daxpy_(&N,&alpha,x,&inc,y,&inc);
  printVec(N, y, "daxpy (2x+y)\t");
  resetValues(N,x,y,A);

  // call dgemv_
  dgemv_(&trans,&N,&N,&one,A,&N,x,&inc,&zero,y,&inc);
  printVec(N, y, "dgemv (Ax)\t");
  resetValues(N,x,y,A);

  // free the malloc'd memory
  free(x);
  free(y);
  free(A);

  puts("");
  return 0;
}


// reset the values of the vectors and matrix to some default
void resetValues(int N, double *x, double *y, double *m){
  int i=0;
  int j=0;
  for(i=0; i<N; i++){
    x[i] = i+1;
    y[i] = i+2;
    for(j=0; j<N; j++)
      m[i*N+j] = i+2*j;
  }
}

// print a vector v of length N, with prepended string "s = [...]"
void printVec(int N, double* v, const char * s){
  int i = 0;
  printf("%s = [",s);
  for(i=0; i<N-1; i++)
    printf("%g, ", v[i]);
  printf("%g]\n", v[N-1]);
}


// print a linear array as a matrix in row major order
void printMatrixRowMajor(int M, int N, double* m, const char * s){
  int i = 0;
  int j = 0;
  printf("%s = \n",s);
  for(i=0; i<M; i++)
  {
    printf("     [");
    for(j=0; j<N-1; j++)
      printf("%g, ", m[i*N+j]);
    printf("%g]\n", m[i*N+(M-1)]);
  }  
}

// print a linear array as a matrix in column major order
void printMatrixColMajor(int M, int N, double* m, const char * s){
  int i = 0;
  int j = 0;
  printf("%s = \n",s);
  for(i=0; i<N; i++)
  {
    printf("     [");
    for(j=0; j<M-1; j++)
      printf("%g, ", m[j*N+i]);
    printf("%g]\n", m[(M-1)*N+i]);
  }  
}
