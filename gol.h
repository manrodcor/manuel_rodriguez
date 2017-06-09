
#ifndef GOL_H_
#define GOL_H_

#include "config.h"

struct world *world_alloc(struct config *configuracion);
void world_free(struct world *w);
void world_print(const struct world *world);
void world_iterate(struct world *w);
bool world_get_cell(const struct world *w, int x, int y);
void world_set_cell(struct world *w, int buf, int x, int y, bool val);
int rrand(int from, int to);

struct world;

#endif
