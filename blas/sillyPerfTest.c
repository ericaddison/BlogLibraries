#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "ArrayPrint.h"

#define TIC struct timeval ticT1 = getTimeStamp();   
#define TOC struct timeval tocT2 = getTimeStamp();
#define TIMEDIFF (TIMEDIFFSEC + TIMEDIFFUSEC/1000000.0)   
#define TIMEDIFFSEC (tocT2.tv_sec - ticT1.tv_sec)
#define TIMEDIFFUSEC (tocT2.tv_usec - ticT1.tv_usec)


struct timeval getTimeStamp();
void genRandomMatrices(int M, int N, int K, double *A, double *B, double* C);
double matrixMultiplyBLAS(int M, int N, int K, double *A, double *B, double *C);
double matrixMultiplyLoop(int M, int N, int K, double *A, double *B, double *C);

int main(int argc, char **argv){
  // initialize size ints
  int N = 10;
  int M = 10;
  int K = 10;
  int nLoop = 100;
 
  // check for comand line arguments
  if(argc>=2){
    M = atoi(argv[1]);
    M = (M<=0)?10:M;
    M = (M>10000)?10000:M;
    N = M;
    K = M;
  }
  if(argc>=3){
    nLoop = atoi(argv[2]);
    nLoop = (nLoop<=0)?100:nLoop;
  }

  // report sizes
  //printf("Using matrix dimensions M=N=K=%d\n",M);
  //printf("Using number of loops = %d\n\n",nLoop);
 
  // malloc space for matrices
  double *A = malloc(M*N*sizeof(double));
  double *B = malloc(N*K*sizeof(double));
  double *C = malloc(M*K*sizeof(double));

  // run test loop
  double t_BLAS = 0.0;
  double t_loop = 0.0;
  int iloop;
  for(iloop=0; iloop<nLoop; iloop++){
    genRandomMatrices(M,N,K,A,B,C);  
    t_BLAS += matrixMultiplyBLAS(M,N,K,A,B,C);

    genRandomMatrices(M,N,K,A,B,C);  
    t_loop += matrixMultiplyLoop(M,N,K,A,B,C);
  }

  // print results
  //printf("Elapsed BLAS time = %.5g\n",t_BLAS);
  //printf("Elapsed Loop time = %.5g\n",t_loop);

  // print out for plotting
  printf("%d %.5g\n",M,t_loop/t_BLAS);

  // free memory
  free(A);
  free(B);
  free(C);
  return 0;
}

// reset the values of the vectors and matrix to some default
void genRandomMatrices(int M, int N, int K, double *A, double *B, double* C){
  int i, j;
  for(i=0; i<M; i++)
    for(j=0; j<N; j++)
      A[i*N+j] = rand()%100;
  for(i=0; i<N; i++)
    for(j=0; j<K; j++)
      B[i*K+j] = rand()%100;
  for(i=0; i<M; i++)
    for(j=0; j<K; j++)
      C[i*K+j] = 0;
}

// get a time value for the current time
struct timeval getTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}

// multiply two matrices using the BLAS dgemm routine
// return elapsed time for multiply operation
double matrixMultiplyBLAS(int M, int N, int K, double *A, double *B, double *C){
  double one = 1;
  int lda = M;
  int ldb = K;
  int ldc = N;
  char trans='N';

  TIC
  dgemm_(&trans, &trans, &M, &K, &N, &one, A, &lda, B, &ldb, &one, C, &ldc);
  TOC
  return TIMEDIFF;
}

// multiply two matrices using simple loops (column major)
// return elapsed time for multiply operation
double matrixMultiplyLoop(int M, int N, int K, double *A, double *B, double *C){
  int i, j, k;
  TIC
  for(i=0; i<M; i++)
    for(k=0; k<K; k++){
      C[i+k*K]=0;
      for(j=0; j<N; j++)
        C[i+k*K]+=A[i+j*M]*B[k*N+j];
    }
  TOC
  return TIMEDIFF;
}
