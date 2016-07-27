#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printVec(int N, double* v, const char * s);


int main(){
  int N=2;
  int inc=1;
  double alpha=2;
  int i=0;
  int j=0;
  char trans = 'N';
  double one = 1;
  double zero = 0;

  double *x = malloc(N*sizeof(double));
  double *y = malloc(N*sizeof(double));
  double *m = malloc(N*N*sizeof(double));
  
  for(i=0; i<N; i++){
    x[i] = i+1;
    y[i] = i+2;
    for(j=0; j<N; j++)
      m[i*N+j] = i+j;
  }

  printVec(N, x, "x");
  printVec(N,y,"y");
  printVec(N*N,m,"m");

  // call dscal_
  dscal_(&N, &alpha, x, &inc);
  printVec(N, x, "dscal(x)");

  // call daxpy_
  daxpy_(&N,&alpha,x,&inc,y,&inc);
  printVec(N, y, "daxpy(y)");

  // call dgemv_
  dgemv_(&trans,&N,&N,&one,m,&N,x,&inc,&zero,y,&inc);
  printVec(N, y, "dgemv(y)");


  // free the malloc'd memory
  free(x);
  free(y);
  free(m);

  return 0;
}


void printVec(int N, double* v, const char * s){
  int i = 0;
  printf("%s = [",s);
  for(i=0; i<N-1; i++)
    printf("%g, ", v[i]);
  printf("%g]\n", v[N-1]);
}
