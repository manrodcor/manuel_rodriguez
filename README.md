Juego de la vida
================

Tarea 1: Versión inicial del mundo

    Haz un fork del repositorio con tu nombre
    Clona tu repositorio
    Completa el esqueleto proporcionado para implementar una primera versión funcional del juego de la vida
    Sube los cambios al tu repositorio
    Haz un pull request
    Arregla las correcciones del profesor
    Sube las correcciones a tu repo
    ¿Has conseguido que te acepten el pull request?
        NO -> goto 6
        Sí -> ¡Enhorabuena! Ya has terminado la tarea 1 



Tarea 2: Código modular, estructuras y makefile

a) Divide tu programa en 3 fichero:

    main.c : Implementará el bucle principal del juego
    gol.h  : Tendrá las declaraciones de las funciones relacionadas con el juego de la vida
    gol.c  : Tendrá las definiciones de las funciones anteriores 

b) Crea un makefile para gestionar la compilación y dependencias 


Tarea 3: Primera aproximación a objetos

1. Encapsula tu mundo en la siguiente estructura:

struct world {
        bool w1[W_SIZE_X][W_SIZE_Y];
        bool w2[W_SIZE_X][W_SIZE_Y];
};

2. Modifica tus funciones para que reciban un puntero a tu objeto. Añade el modificador const siempre que no sea necesario modificar el objeto

Tu main.c debería quedar más o menos así:

#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

int main()
{
	int i = 0;
	struct world w;

	world_init(&w);
	do {
		printf("\033cIteration %d\n", i++);
		world_print(&w);
		world_step(&w);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}


TAREA 4: Objetos: Reserva dinámica de memoria
Interfaz pública

gol.h

struct world;

struct world *world_alloc(int size_x, int size_y);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

    world_alloc: Reserva en memoria e inicializa nuestro objeto struct world. Esto implica reservar memoria para la estrucutra y para los dos arrays que tiene dentro.
    world_free: Libera la memoria que ocupa nuestro objeto. Esto implica liberar primero la memoria de los arrays que tiene dentro la estrucutra, y luego la propia estructura.
    world_print: Imprime el mundo
    world_iterate: Realiza una iteración del juego de la vida 


Implementación (privada)

gol.c

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);

/* ... */
/* Definiciones de funciones privadas y públicas */
/* ... */

    fix_coords: Recibe unas coordenadas (x,y) y las modifica para implementar un mundo toroidal
    get_cell: Devuelve la célula en la posición (x,y), arreglando las coordenadas.
    set_cell: Cambia el valor de la célula de la posición (x,y), arreglando las coordenadas.
    count_neighbors: Cuenta las células vecinas haciendo uso de la función get_cell 

NOTAS

    No olvides comprobar que has podido realizar correctamente la reserva de memoria: 

En world_alloc():

w = (struct world *)malloc(sizeof(struct world));
if (!w)
	return NULL;

En main():

w = world_alloc(WORLD_X, WORLD_Y);
if (!w) {
	perror("Can't allocate world");
	exit(EXIT_FAILURE);
}

    Las funciones privadas se declaran como static y no aparecen el el .h
    Ahora debes calcular a mano el offset en el array para llegar a la célula (x,y) con la fórmula: size_x*y + x. Encapsula esta fórmula en las funciones get_cell y set_cell. 
