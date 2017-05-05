#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"


int main()
{
	int i = 0;

	//Declara dos mundos
	bool mundo01[TAM_VER][TAM_HOR];
	bool mundo02[TAM_VER][TAM_HOR];


	//Inicializa el mundo
	world_init(mundo01);
	world_init(mundo02);

	do {
		printf("\033cIteration %d\n", i++);
		world_print(mundo01);
		world_step(mundo01, mundo02);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}
