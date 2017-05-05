#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"


int main()
{
	int i = 0;
	struct world mundo01;
	world_init(&mundo01);
	do {
		printf("\033cIteration %d\n", i++);
		world_print(&mundo01);
		world_step(&mundo01);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

