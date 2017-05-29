
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "config.h"
#include <getopt.h>
#include "gol.h"


struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
	bool flanco;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);
static int rrand(int from, int to);


struct world *world_alloc(struct config *configuracion)
{
	int i, j;
	bool valor;
	struct world *w;
	w = malloc(2 * sizeof(struct world));
	if(!w){
		return NULL;
	}

	int modo = configuracion->init_mode;
	w->size_x = configuracion->size_x;;
	w->size_y = configuracion->size_y;;
	w->flanco = false;
	w->cells[0] = (bool *)malloc(w->size_x * w->size_y * sizeof(bool));
	w->cells[1] = (bool *)malloc(w->size_x * w->size_y * sizeof(bool));

	if(!w->cells[0] || !w->cells[1]){
		if(!w->cells[0]){
			free(w->cells[1]);
		}
		if(!w->cells[1]){
			free(w->cells[0]);
		}
		free(w);
		return NULL;
	}

	for (i = 0; i < w->size_y; i++){
		for (j = 0; j < w->size_x; j++){
			set_cell(w, 0, j, i, false);
		}
	}
	if(modo == CFG_DEFAULT){
		set_cell(w, 0, 1, 0, true);
		set_cell(w, 0, 2, 0, true);
		set_cell(w, 0, 0, 1, true);
		set_cell(w, 0, 3, 1, true);
		set_cell(w, 0, 1, 2, true);
		set_cell(w, 0, 2, 2, true);
		set_cell(w, 0, 3, 2, true);
		set_cell(w, 0, 3, 3, true);
	}
	else if(modo == CFG_GLIDER){
		set_cell(w, 0, 1, 0, true);
		set_cell(w, 0, 2, 1, true);
		set_cell(w, 0, 0, 2, true);
		set_cell(w, 0, 1, 2, true);
		set_cell(w, 0, 2, 2, true);
	}
	else if(modo == CFG_RANDOM){
		srand(time(0)); //use current time as seed for random generator

		for (i = 0; i < w->size_y; i++){
			for (j = 0; j < w->size_x; j++){
				valor = rrand(0, 1);
				set_cell(w, 0, j, i, valor);
			}
		}
	}
	return w;
}

void world_free(struct world *w)
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}

void world_print(const struct world *w)
{
	int i;
	int j;

	for (i = 0; i < w->size_y; i++){
		for (j = 0; j < w->size_x; j++){
			printf("%s ", get_cell(w, j, i) ? "#" : ".");
		}
		printf("\n");
	}

}

void world_iterate(struct world *w)
{
	int i;
	int j;
	int selectMatriz;
	int nVecinos;
	bool val;

	selectMatriz = !w->flanco;

	for(i = 0; i < w->size_y; i++){
		for(j = 0; j < w->size_x; j++){
			nVecinos = count_neighbors(w, j, i);
			val = (get_cell(w, j, i) && nVecinos == 2) || nVecinos == 3;
			set_cell(w, selectMatriz, j, i, val);
		}
	}
	w->flanco = !w->flanco;
}


static void fix_coords(const struct world *w, int *x, int *y)
{
	if(*x == -1){
		*x = w->size_x - 1;
	}
	else if(*x == w->size_x){
		*x = 0;
	}
	if(*y == -1){
		*y = w->size_y - 1;
	}
	else if(*y == w->size_y){
		*y = 0;
	}
}

static bool get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	return w->cells[w->flanco][y * w->size_x + x];

}

static void set_cell(struct world *w, int buf, int x, int y, bool val)
{
	fix_coords(w, &x, &y);
	w->cells[buf][y * w->size_x + x] = val;
}

static int count_neighbors(const struct world *w, int x, int y)
{
	int numeroVecinos = 0;

	numeroVecinos += get_cell(w, x, y - 1);
	numeroVecinos += get_cell(w, x - 1, y - 1);
	numeroVecinos += get_cell(w, x - 1, y);
	numeroVecinos += get_cell(w, x - 1, y + 1);
	numeroVecinos += get_cell(w, x, y + 1);
	numeroVecinos += get_cell(w, x + 1, y + 1);
	numeroVecinos += get_cell(w, x + 1, y);
	numeroVecinos += get_cell(w, x + 1, y - 1);

	return numeroVecinos;
}

static int rrand(int from, int to){
	return rand()%(to - from + 1) + from;
}

