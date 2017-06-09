
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "config.h"
#include <getopt.h>
#include "gol.h"
#include "gol_int.h"
#include "gol_plano.h"

struct world_plano{
	struct world super;
};

static bool get_cell_p(const struct world *w, int x, int y);
static void set_cell_p(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors_p(const struct world *w, int x, int y);
static void world_iterate_p(struct world *w);
static void world_print_p(const struct world *w);


struct world_plano *world_plano_alloc(struct config *configuracion)
{
	int i, j;
	struct world_plano *w;
	w = (struct world_plano *)malloc(2 * sizeof(struct world_plano));
	if(!w){
		return NULL;
	}
	world_init((struct world *)w, configuracion);

	w->super.get_cell = get_cell_p;
	w->super.set_cell = set_cell_p;
	w->super.world_iterate = world_iterate_p;
	w->super.world_print = world_print_p;
	w->super.count_neighbors = count_neighbors_p;

	int modo = configuracion->init_mode;
	w->super.size_x = configuracion->size_x;;
	w->super.size_y = configuracion->size_y;;
	w->super.flanco = false;
	w->super.cells[0] = (bool *)malloc(w->super.size_x * w->super.size_y * sizeof(bool));
	w->super.cells[1] = (bool *)malloc(w->super.size_x * w->super.size_y * sizeof(bool));

	if(!w->super.cells[0] || !w->super.cells[1]){
		if(!w->super.cells[0]){
			free(w->super.cells[1]);
		}
		if(!w->super.cells[1]){
			free(w->super.cells[0]);
		}
		free(w);
		return NULL;
	}

	for (i = 0; i < w->super.size_y; i++){
		for (j = 0; j < w->super.size_x; j++){
			w->super.set_cell((struct world *)w, 0, j, i, false);
		}
	}
	if(modo == CFG_DEFAULT){
		w->super.set_cell((struct world *)w, 0, 1, 0, true);
		w->super.set_cell((struct world *)w, 0, 2, 0, true);
		w->super.set_cell((struct world *)w, 0, 0, 1, true);
		w->super.set_cell((struct world *)w, 0, 3, 1, true);
		w->super.set_cell((struct world *)w, 0, 1, 2, true);
		w->super.set_cell((struct world *)w, 0, 2, 2, true);
		w->super.set_cell((struct world *)w, 0, 3, 2, true);
		w->super.set_cell((struct world *)w, 0, 3, 3, true);
	}
	else if(modo == CFG_GLIDER){
		w->super.set_cell((struct world *)w, 0, 1, 0, true);
		w->super.set_cell((struct world *)w, 0, 2, 1, true);
		w->super.set_cell((struct world *)w, 0, 0, 2, true);
		w->super.set_cell((struct world *)w, 0, 1, 2, true);
		w->super.set_cell((struct world *)w, 0, 2, 2, true);
	}
	else if(modo == CFG_RANDOM){
		srand(time(0)); //use current time as seed for random generator

		for (i = 0; i < w->super.size_y; i++){
			for (j = 0; j < w->super.size_x; j++){
				w->super.valor = rrand(0, 1);
				w->super.set_cell((struct world *)w, 0, j, i, w->super.valor);
			}
		}
	}
	return w;
}

static void world_print_p(const struct world *w)
{
	int i;
	int j;

	for (i = 0; i < w->size_y; i++){
		for (j = 0; j < w->size_x; j++){
			printf("%s ", w->get_cell(w, j, i) ? "#" : ".");
		}
		printf("\n");
	}

}

static void world_iterate_p(struct world *w)
{
	int i;
	int j;
	int selectMatriz;
	int nVecinos;
	bool val;

	selectMatriz = !w->flanco;

	for(i = 0; i < w->size_y; i++){
		for(j = 0; j < w->size_x; j++){
			nVecinos = count_neighbors_p((struct world *)w, j, i);
			val = (w->get_cell(w, j, i) && nVecinos == 2) || nVecinos == 3;
			w->set_cell(w, selectMatriz, j, i, val);
		}
	}
	w->flanco = !w->flanco;
}

static bool get_cell_p(const struct world *w, int x, int y)
{
	return w->cells[w->flanco][y * w->size_x + x];
}

static void set_cell_p(struct world *w, int buf, int x, int y, bool val)
{
	w->cells[buf][y * w->size_x + x] = val;
}

static int count_neighbors_p(const struct world *w, int x, int y)
{
	int numeroVecinos = 0;

	numeroVecinos += w->get_cell(w, x, y - 1);
	numeroVecinos += w->get_cell(w, x - 1, y - 1);
	numeroVecinos += w->get_cell(w, x - 1, y);
	numeroVecinos += w->get_cell(w, x - 1, y + 1);
	numeroVecinos += w->get_cell(w, x, y + 1);
	numeroVecinos += w->get_cell(w, x + 1, y + 1);
	numeroVecinos += w->get_cell(w, x + 1, y);
	numeroVecinos += w->get_cell(w, x + 1, y - 1);

	return numeroVecinos;
}
