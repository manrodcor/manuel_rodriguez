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

