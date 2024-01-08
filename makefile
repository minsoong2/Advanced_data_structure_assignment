CC = gcc
main : 20193060.o
	gcc -o 20193060_exe 20193060.o
20193060.o : 20193060.c
	gcc -c 20193060.c
clean:
	rm *.o 20193060_exe
