CFLAGS = -Wall -Werror

.PHONY : all clean

all : gol

gol :	main.o	gol.o
	gcc main.o gol.o -o gol

main.o:	main.c gol.h
	gcc -c main.c

gol.o	:	gol.c gol.h
	gcc -c gol.c

clean :
	rm *.o
