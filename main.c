#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"
#include "config.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
	int i = 0;
	struct config configuracion;
	struct world *w;

	if (!config_parse_argv(&configuracion, argc, argv)) {
		printf("ERROR\n");
		config_print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	else if (configuracion.show_help){
		config_print_usage(argv[0]);
		return EXIT_SUCCESS;
	}
	w = world_alloc(&configuracion);
	if (!w) {
		perror("Can't allocate world");
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

