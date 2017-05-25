#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


static const char *init_mode_str[] = {
	[CFG_DEFAULT] = "default",
	[CFG_GLIDER] = "glider",
	[CFG_RANDOM] = "random",
};

static const struct option long_options[] =
{
	{ "help", no_argument, 0, 'h' },
	{ "size_x", required_argument, 0, 'x' },
	{ "size_y", required_argument, 0, 'y' },
	{"mode", required_argument, 0, 'i'},
	{ 0, 0, 0, 0 }
};

static bool check_config(const struct config *configuracion);
static enum cfg_init_mode str2init_mode(const char *opt);


int config_parse_argv(struct config *configuracion, int argc, char *argv[])
{
	int option_index = 0;
	int c;

	// Default values
	configuracion->show_help = false;
	configuracion->size_x = 10;
	configuracion->size_y = 14;
	configuracion->init_mode = 0;

	while ((c = getopt_long(argc, argv, "hx:y:i:", long_options, &option_index)) != -1) {
		switch (c) {
		case 'h':
			configuracion->show_help = true;
			break;
		case 'x':
			configuracion->size_x = strtol(optarg, NULL, NULL);
			break;
		case 'y':
			configuracion->size_y = strtol(optarg, NULL, NULL);
			break;
		case 'i':
			configuracion->init_mode = str2init_mode(optarg);
			break;
		}
	}

	return check_config(configuracion);
}

static bool check_config(const struct config *configuracion)
{
	bool correct = true;

	if (configuracion->show_help)
		return true;
	correct &= configuracion->size_x > 0;
	correct &= configuracion->size_y > 0;
	correct &= configuracion->init_mode >= 0;
	return correct;
}

static enum cfg_init_mode str2init_mode(const char *opt)
{
	int i;
	for (i = 0; i < CFG_N_INIT_MODES; i++){
		if(!strcmp(init_mode_str[i], opt)){
			break;
		}
	}

	return i == CFG_N_INIT_MODES ? CFG_NOT_DEF : i;
}

void config_print_usage(const char *arg0)
{
	printf("Usage: %s\n"
		"\t[-h|--help]\n"
		"\t[-x|--size_x <num>]\n"
		"\t[-y|--size_y <num>]\n"
		"\t[-i|--init <init_mode>]\n"
		, arg0);

	// Print all initialization modes
	printf("\ninitialization modes: ");
	printf("\nModo %s ", init_mode_str[0]);
	printf("\nModo %s ", init_mode_str[1]);
	printf("\nModo %s \n", init_mode_str[2]);
}

void config_print(const struct config *configuracion)
{
	printf("config {\n");
	printf("\tshow help = %s\n", configuracion->show_help ? "TRUE" : "FALSE");
	printf("\tsize_x    = %d\n", configuracion->size_x);
	printf("\tsize_y    = %d\n", configuracion->size_y);
	printf("\tinit_mode = %d(%s)\n",
			configuracion->init_mode, init_mode_str[configuracion->init_mode]);
	printf("}\n");
}

