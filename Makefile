all: T2 run

main.o: main.c
	gcc -c -o main.o main.c -g -Wall -ansi -pedantic

T2_lib.o: T2_lib.c
	gcc -c -o T2_lib.o T2_lib.c -g -Wall -ansi -pedantic

skipList.o: skipList.c
	gcc -c -o skipList.o skipList.c -g -Wall -ansi -pedantic

T2: T2_lib.o main.o skipList.o
	gcc -o T2 skipList.o main.o T2_lib.o -g -Wall -ansi -pedantic

run: T2
	./T2

clean:
	rm *.o