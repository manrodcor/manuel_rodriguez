
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "config.h"
#include <getopt.h>
#include "gol.h"
#include "gol_int.h"
#include "gol_toroidal.h"
//#include "gol_plano.h"


struct world_toroidal
{
	struct world super;
};

struct world_toroidal *world_toroidal_alloc(struct config *configuracion);
bool get_cell_t(const struct world *wt, int x, int y);
void set_cell_t(struct world *wt, int buf, int x, int y, bool val);
void fix_coords(struct world *wt, int *x, int *y);
void world_toroidal_init(struct world_toroidal *wt);


void world_toroidal_init(struct world_toroidal *wt){
	wt->super.get_cell = &get_cell_t;
	wt->super.set_cell = &set_cell_t;
}
struct world_toroidal *world_toroidal_alloc(struct config *configuracion)
{
	struct world_toroidal *wt;

	wt = (struct world_toroidal *)malloc(sizeof(struct world_toroidal));
	if (!wt){
		return NULL;
	}


	world_toroidal_init(wt);

	wt = (struct world_toroidal *)world_alloc(configuracion);

	return wt;
}


bool get_cell_t(const struct world *wt, int x, int y)
{
	return wt->cells[wt->flanco][y * wt->size_x + x];
}

void set_cell_t(struct world *wt, int buf, int x, int y, bool val)
{
	fix_coords(wt, &x, &y);
	wt->cells[buf][y * wt->size_x + x] = val;
}

void fix_coords(struct world *wt, int *x, int *y)
{
	if(*x == -1){
		*x = wt->size_x - 1;
	}
	else if(*x == wt->size_x){
		*x = 0;
	}
	if(*y == -1){
		*y = wt->size_y - 1;
	}
	else if(*y == wt->size_y){
		*y = 0;
	}
}
