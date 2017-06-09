
#ifndef GOL_INT_H_
#define GOL_INT_H_

#include <stdbool.h>
#include "config.h"
#include "gol.h"

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
	int modo;
	bool flanco;
	bool valor;

	bool (*get_cell)(const struct world *w, int x, int y);
	void (*set_cell)(struct world *w, int buf, int x, int y, bool val);
	void (*world_iterate)(struct world *w);
	void (*world_print)(const struct world *w);
	int (*count_neighbors)(const struct world *w, int x, int y);
};

void world_init(struct world *w, struct config *configuracion);

#endif
