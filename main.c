#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define TAM_HOR 8
#define TAM_VER 8

void world_init(bool matriz[TAM_VER][TAM_HOR]);
void world_print(bool matriz[TAM_VER][TAM_HOR]);
void world_step(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR]);
int world_count_neighbors(bool matriz[TAM_VER][TAM_HOR], int i, int j);
bool world_get_cell(bool matriz[TAM_VER][TAM_HOR], int i, int j);
void world_copy(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR]);


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

void world_init(bool matriz[TAM_VER][TAM_HOR])
{
	//Poner el mundo a false
	int i = 0;
	int j = 0;
	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			matriz[i][j] = false;
		}
	}

	/*Inicializar con el patrón del glider:
	 *           . # .
	 *           . . #
	 *           # # #
	 */

	matriz[0][1] = true;
	matriz[1][2] = true;
	matriz[2][0] = true;
	matriz[2][1] = true;
	matriz[2][2] = true;
	
}

void world_print(bool matriz[TAM_VER][TAM_HOR])
{
	int i = 0;
	int j = 0;
	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			printf("%s ", matriz[i][j] ? "#" : ".");
		}
		printf("\n");
	}
}

void world_step(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR])
{
	int i = 0;
	int j = 0;	
	int nVecinos;

	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			nVecinos = world_count_neighbors(matriz01, i, j);
			matriz02[i][j] = (matriz01[i][j] && nVecinos == 2) || nVecinos == 3;
		}
	}
	world_copy(matriz01, matriz02);
}

int world_count_neighbors(bool matriz[TAM_VER][TAM_HOR], int i, int j)
{
	int numeroVecinos = 0;
	
	numeroVecinos += world_get_cell(matriz, i, j - 1);
	numeroVecinos += world_get_cell(matriz, i - 1, j - 1);
	numeroVecinos += world_get_cell(matriz, i - 1, j);
	numeroVecinos += world_get_cell(matriz, i - 1, j + 1);
	numeroVecinos += world_get_cell(matriz, i, j + 1);
	numeroVecinos += world_get_cell(matriz, i + 1, j + 1);
	numeroVecinos += world_get_cell(matriz, i + 1, j);
	numeroVecinos += world_get_cell(matriz, i + 1, j - 1);
	
	return numeroVecinos;
}

bool world_get_cell(bool matriz[TAM_VER][TAM_HOR], int i, int j)
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
	estado = matriz[i][j];
	return estado;
}

void world_copy(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR])
{
	int i,j;

	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			matriz01[i][j] = matriz02[i][j];	
		}
	}

}
