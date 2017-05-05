#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"



void world_init(struct world *mundo)
{
	//Poner el mundo a false
	int i = 0;
	int j = 0;
	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			mundo->mundo01[i][j] = false;
			mundo->mundo02[i][j] = false;
		}
	}

	/*Inicializar con el patrón del glider:
	 *           . # .
	 *           . . #
	 *           # # #
	 */

	mundo->mundo01[0][1] = true;
	mundo->mundo01[1][2] = true;
	mundo->mundo01[2][0] = true;
	mundo->mundo01[2][1] = true;
	mundo->mundo01[2][2] = true;
	
}

void world_print(const struct world *mundo)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			printf("%s ", mundo->mundo01[i][j] ? "#" : ".");
		}
		printf("\n");
	}
}

void world_step(struct world *mundo)
{
	int i = 0;
	int j = 0;	
	int nVecinos;

	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			nVecinos = world_count_neighbors(mundo, i, j);
			mundo->mundo02[i][j] = (mundo->mundo01[i][j] && nVecinos == 2) || nVecinos == 3;
		}
	}
	world_copy(mundo);
}

int world_count_neighbors(const struct world *mundo, int i, int j)
{
	int numeroVecinos = 0;
	
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i, j - 1);
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i - 1, j - 1);
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i - 1, j);
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i - 1, j + 1);
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i, j + 1);
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i + 1, j + 1);
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i + 1, j);
	numeroVecinos += world_get_cell((struct world*)mundo->mundo01, i + 1, j - 1);
	
	return numeroVecinos;
}

bool world_get_cell(const struct world *mundo, int i, int j)
{
	bool estado;
	if(i == -1){
		i = TAM_VER -1;
	}
	else if(i == TAM_VER){
		i = 0;
	}
	if(j == -1){
		j = TAM_VER -1;
	}
	else if(j == TAM_VER){
		j = 0;
	}
	estado = mundo->mundo01[i][j];
	return estado;
}

void world_copy(struct world *mundo)
{
	int i,j;

	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			mundo->mundo01[i][j] = mundo->mundo02[i][j];	
		}
	}
}
