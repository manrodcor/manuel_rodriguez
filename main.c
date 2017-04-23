#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>//importa booleanos


// TODO: Crea dos macros con el tamaño horizontal y vertical del mundo

#define TAM_HOR 10
#define TAM_VER 10

void world_init(bool *matriz);
void world_print(bool *matriz);/* Recibo un mundo */
void world_step(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR]);// Recibo dos mundos 
int world_count_neighbors(bool matriz[TAM_VER][TAM_HOR], int i, int j);/* Recibo un mundo y unas coordenadas */
bool world_get_cell(bool matriz[TAM_VER][TAM_HOR], int i, int j);/* Recibo un mundo y unas coordenadas */
void world_copy(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR]);/* Recibo dos mundos */

bool *pmundo01;
bool *pmundo02;


int main()
{
	int i = 0;
	int j = 0;
	// TODO: Declara dos mundos
	bool mundo01[TAM_VER][TAM_HOR];
	bool mundo02[TAM_VER][TAM_HOR];

	
	pmundo01 = *mundo01;
	pmundo02 = *mundo02;

	// TODO: inicializa el mundo
	world_init(*mundo01);
	world_init(*mundo02);

	do {
		printf("\033cIteration %d\n", i++);
		// TODO: Imprime el mundo
		world_print(*mundo01);
		//printf("\n");
		//world_print(*mundo02);
		// TODO: Itera
		world_step(mundo01, mundo02);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void world_init(bool *matriz)
{
	// TODO: Poner el mundo a false
	int i = 0;
	int j = 0;
	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			*matriz = false;
			*matriz++;
		}
	}

	/* TODO: Inicializar con el patrón del glider:
	 *           . # .
	 *           . . #
	 *           # # #
	 */

	matriz = pmundo01;
	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			if((i == 0 && j == 1)||(i == 1 && j == 2)||(i == 2 && j == 0)||(i == 2 && j == 1)||(i == 2 && j == 2)){
				*matriz = true;
			}
		*matriz++;
		}
	}
}

void world_print(bool *matriz)
{
	// TODO: Imprimir el mundo por consola. Sugerencia:
	/*
	 *     . # . . . . . . . .
	 *     . . # . . . . . . .
	 *     # # # . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 *     . . . . . . . . . .
	 */
	int i = 0;
	int j = 0;
	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			if(*matriz == false){
				printf(". ");
			}
			else{
				printf("# ");			
			}
			*matriz++;
		}
		printf("\n");
	}
}

void world_step(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR])/* Recibo dos mundos */
{
	/*
	 * TODO:
	 * - Recorrer el mundo célula por célula comprobando si nace, sobrevive
	 *   o muere.
	 *
	 * - No se puede cambiar el estado del mundo a la vez que se recorre:
	 *   Usar un mundo auxiliar para guardar el siguiente estado.
	 *
	 * - Copiar el mundo auxiliar sobre el mundo principal
	 */

	int i = 0;
	int j = 0;	
	int v;	//numero de vecinos
	bool estado;//Estado de la celda

	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			v = world_count_neighbors(matriz01, i, j);
			estado = world_get_cell(matriz01, i, j);
			if((estado == false) & (v == 3)){
				matriz02[i][j] = true;
			}
			else if((estado == true) & (v > 1) & (v < 4)){
				matriz02[i][j] = false;			
			}
			else{
				matriz02[i][j] = false;
			}
		}
	}
	world_copy(matriz01, matriz02);
}

int world_count_neighbors(bool matriz[TAM_VER][TAM_HOR], int i, int j)/* Recibo un mundo y unas coordenadas */
{
	// Devuelve el número de vecinos
	int numeroVecinos = 0;
	int iaux = i - 1;
	int jaux = j - 1;
	int aux01 = i + 1;
	int aux02 = j + 1;
	if(i == 0 || j == 0 || i == TAM_VER - 1 || j == TAM_HOR - 1){//Estamos en la periferia del mundo
		if(i == 0)
			iaux = TAM_VER - 1;
		if(i == TAM_VER - 1){
			iaux = 0;
			aux01 = i - 1;
			}
		if(j == 0)
			jaux = TAM_HOR - 1;
		if(j == TAM_HOR - 1){
			jaux = 0;
			aux02 = j - 1;
			}

		if(matriz[i][jaux])
			numeroVecinos++;
		if(matriz[iaux][jaux])
			numeroVecinos++;
		if(matriz[iaux][j])
			numeroVecinos++;
		if(matriz[iaux][aux02])
			numeroVecinos++;
		if(matriz[i][aux02])
			numeroVecinos++;
		if(matriz[aux01][aux02])
			numeroVecinos++;
		if(matriz[aux01][j])
			numeroVecinos++;
		if(matriz[aux01][jaux])
			numeroVecinos++;
	}
	else{
		if(matriz[i - 1][j - 1])
			numeroVecinos++;
		if(matriz[i - 1][j])
			numeroVecinos++;
		if(matriz[i - 1][j + 1])
			numeroVecinos++;
		if(matriz[i][j - 1])
			numeroVecinos++;
		if(matriz[i][j + 1])
			numeroVecinos++;
		if(matriz[i + 1][j - 1])
			numeroVecinos++;
		if(matriz[i + 1][j])
			numeroVecinos++;
		if(matriz[i + 1][j + 1])
			numeroVecinos++;
	}
	return numeroVecinos;
}

bool world_get_cell(bool matriz[TAM_VER][TAM_HOR], int i, int j)/* Recibo un mundo y unas coordenadas */
{
	/*
	 * TODO: Devuelve el estado de la célula de posición indicada
	 * (¡cuidado con los límites del array!)
	 */
	bool estado = matriz[i][j];
	return estado;
}

void world_copy(bool matriz01[TAM_VER][TAM_HOR], bool matriz02[TAM_VER][TAM_HOR])/* Recibo dos mundos */
{
	// TODO: copia el mundo segundo mundo sobre el primero

	int i,j;

	for(i = 0; i < TAM_VER; i++){
		for(j = 0; j < TAM_HOR; j++){
			if(matriz02[i][j] == true){
				matriz01[i][j] = true;
			}
			else{
				matriz01[i][j] = false;
			}	
		}
	}

}
