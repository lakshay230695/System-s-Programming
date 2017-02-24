indexer: main.o treeboiz.o functions.o
	gcc main.o treeboiz.o functions.o -o indexer
main.o: main.c
	gcc -c main.c
functions.o: functions.c
	gcc -c functions.c
treeboiz.o: treeboiz.c
	gcc -c treeboiz.c
clean:
	rm -f *.o core
