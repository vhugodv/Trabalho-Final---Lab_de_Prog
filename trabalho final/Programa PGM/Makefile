all: prog.e

prog.e: main_alg1.o readwritePGM.o extractfreeimg.o coords1.o main_alg2.o listfiles.o findmatch.o calcularMSE.o
	gcc -o prog.e main_alg1.o readwritePGM.o extractfreeimg.o coords1.o main_alg2.o listfiles.o findmatch.o calcularMSE.o

main_alg1.o:	main_alg1.c
	gcc -o main_alg1.o -c main_alg1.c

readwritePGM.o:	readwritePGM.c
	gcc -o readwritePGM.o -c readwritePGM.c

extractimg.o:	extractfreeimg.c
	gcc -o extractfreeimg.o -c extractfreeimg.c

coords1.o:	coords1.c
	gcc -o coords1.o -c coords1.c

main_alg2.o: main_alg2.c
	gcc -o main_alg2.o -c main_alg2.c

listfiles.o: listfiles.c
	gcc -o listfiles.o -c listfiles.c

findmatch.o: findmatch.c
	gcc -o findmatch.o -c findmatch.c

calcularMSE.o: calcularMSE.c
	gcc -o calcularMSE.o -c calcularMSE.c

clean:
	rm -f *.o prog.e