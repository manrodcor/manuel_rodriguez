#ifndef GOL_H_
#define GOL_H_

#define WORLD_X 6
#define WORLD_Y 6

struct world;

struct world *world_alloc(int tam_x, int tam_y);
void world_free(struct world *w);
void world_print(const struct world *world);
void world_iterate(struct world *w);

#endif
