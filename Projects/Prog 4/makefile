bintree: main.o movefunc.o
	gcc main.o func.o -o bintree
main.o: main.c
	gcc -c main.c
movefunc.o: func.c
	gcc -c func.c
clean:
	rm -f *.o core
