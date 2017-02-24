organizer: main.o movefunc.o
	gcc main.o movefunc.o -o organizer
main.o: main.c
	gcc -c main.c
movefunc.o: movefunc.c
	gcc -c movefunc.c
clean:
	rm -f *.o core
