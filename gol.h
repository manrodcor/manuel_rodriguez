#ifndef GOL_H_
#define GOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_HOR 8
#define TAM_VER 8

struct world{
	bool mundo01[TAM_VER][TAM_HOR];
	bool mundo02[TAM_VER][TAM_HOR];
};

void world_init(struct world *mundo);
void world_print(const struct world *mundo);
void world_step(struct world *mundo);
int world_count_neighbors(const struct world *mundo, int i, int j);
bool world_get_cell(const struct world *mundo, int i, int j);
void world_copy(struct world *mundo);

#endif /* GOL_H_ */
