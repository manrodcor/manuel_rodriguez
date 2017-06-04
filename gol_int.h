
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
	bool flanco;

	bool (*get_cell)(const struct world *w, int x, int y);
	void (*set_cell)(struct world *w, int buf, int x, int y, bool val);
};

void world_init(struct world *w);

#endif
