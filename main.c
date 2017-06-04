
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"
#include "config.h"
#include <getopt.h>
#include "gol_toroidal.h"
//#include "gol_plano.h"
#include "gol_int.h"

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

	if(configuracion.init_forma == CFG_TOROIDAL){

		w = (struct world *)world_toroidal_alloc(&configuracion);

		if (!w) {
			perror("Can't allocate world");
			exit(EXIT_FAILURE);
		}

	}
	else if(configuracion.init_forma == CFG_PLANO){

		//w = (struct world *)world_plano_alloc(&configuracion);
		if (!w) {
			perror("Can't allocate world");
			exit(EXIT_FAILURE);
		}
	}

	do {
		printf("\033cIteration %d\n", i++);
		world_print((struct world *)w);
		world_iterate((struct world *)w);
	} while (getchar() != 'q');
	world_free(w);

	return EXIT_SUCCESS;
}



