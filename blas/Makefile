all:
	gcc basicBlas.c ArrayPrint.c -lopenblas

run: all
	./a.out

perfTest:
	gcc sillyPerfTest.c ArrayPrint.c -o perfTest -lopenblas
