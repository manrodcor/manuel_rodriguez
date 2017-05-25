CFLAGS = -Wall -Werror

.PHONY : all clean

all : gol

gol :	main.o	gol.o config.o
	gcc main.o gol.o config.o -o gol

main.o:	main.c gol.h config.h
	gcc -c main.c

gol.o	:	gol.c gol.h
	gcc -c gol.c
config.o:	config.c config.h
	gcc -c config.c

clean :
	rm *.o
