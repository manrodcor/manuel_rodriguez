#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
	int i = 0;
	struct world *w;

	w = world_alloc(WORLD_X, WORLD_Y);
	if (!w) {
		printf("Can't allocate world");
		exit(EXIT_FAILURE);
	}

	do {
		printf("\033cIteration %d\n", i++);
		world_print(w);
		world_iterate(w);
	} while (getchar() != 'q');
	world_free(w);

	return EXIT_SUCCESS;
}
