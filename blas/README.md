#BLAS
This directory contains some examples of how to call the BLAS library from C and C++. 

### Files
* ArrayPrint.c: some simple array/matrix printing routines.
* ArrayPrint.h: header file for ArrayPrint.c.
* MakeFile: very simple Makefile to compile the code in this directory.
* basicBlas.c: Examples of calling raw BLAS routines from C.
* sillyPerfTest.c: performance test to compare BLAS matrix multiply vs. simple loops

### Compiling
I compiled this code using the provided `Makefile` on Linux Mint 17, gcc version 4.8.4. I did not have to install any additional packages to link to the BLAS library, but to use openBLAS specifically, I had to install libopenblas-dev. Here are the BLAS packages installed on my system (`dpkg --get-selections | grep blas`):
* libblas-dev
* libblas3
* libopenblas-base
* libopenblas-dev

If you have trouble with linking to the BLAS library, you might want to install these packages.
