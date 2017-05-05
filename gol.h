#ifndef GOL_H_
#define GOL_H_

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

#endif /* GOL_H_ */
