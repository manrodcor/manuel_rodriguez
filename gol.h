#ifndef GOL_H_
#define GOL_H_

struct world *world_alloc(struct config *configuracion);
void world_free(struct world *w);
void world_print(const struct world *world);
void world_iterate(struct world *w);

struct world;

#endif
