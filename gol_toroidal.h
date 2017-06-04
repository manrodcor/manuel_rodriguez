
#ifndef GOL_TOROIDAL_H_
#define GOL_TOROIDAL_H_

#include <stdbool.h>

struct world_toroidal *world_toroidal_alloc(struct config *configuracion);
void world_init_toroidal(struct world_toroidal *wt);

#endif
