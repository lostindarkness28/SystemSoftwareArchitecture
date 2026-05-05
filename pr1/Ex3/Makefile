all:
	gcc -c input.c output.c
	gcc main.c input.o output.o -L/usr/lib -lprocess1 -L$(HOME)/mylibs -lprocess -g -O2 -o my_program

clean:
	rm -f *.o my_program
