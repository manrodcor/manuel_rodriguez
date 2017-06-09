CFLAGS = -Wall -Werror

.PHONY : all clean

all : gol

gol :	main.o	gol.o config.o gol_toroidal.o gol_plano.o
	gcc main.o gol.o config.o gol_toroidal.o gol_plano.o -o gol

main.o:	main.c gol.h gol_toroidal.h gol_plano.h gol_int.h config.h
	gcc -c main.c

gol.o	:	gol.c gol.h
	gcc -c gol.c
config.o:	config.c config.h
	gcc -c config.c
gol_toroidal.o :	gol_toroidal.c gol_toroidal.h
	gcc -c gol_toroidal.c
gol_plano.o :	gol_plano.c gol_plano.h
	gcc -c gol_plano.c


clean :
	rm *.o
