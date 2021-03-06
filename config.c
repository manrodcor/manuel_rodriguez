
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define LONG_TEXT 10

static const char *init_mode_str[] = {
	[CFG_DEFAULT] = "default",
	[CFG_GLIDER] = "glider",
	[CFG_RANDOM] = "random",
};

static const char *init_forma[] = {
	[CFG_TOROIDAL] = "toroidal",
	[CFG_PLANO] = "plano",
};

static const struct option long_options[] =
{
	{"help", no_argument, 0, 'h'},
	{"size_x", required_argument, 0, 'x'},
	{"size_y", required_argument, 0, 'y'},
	{"mode", required_argument, 0, 'i'},
	{"forma", required_argument, 0, 'f'},
	{ 0, 0, 0, 0 }
};

static bool check_config(const struct config *configuracion);
static enum cfg_init_mode str2init_mode(const char *opt);
static enum cfg_init_forma str2init_forma(const char *opt);
static bool load_config(struct config *configuracion);


int config_parse_argv(struct config *configuracion, int argc, char *argv[])
{
	int option_index = 0;
	int c;

	// Default values
	configuracion->show_help = false;
	configuracion->size_x = 8;
	configuracion->size_y = 8;
	configuracion->init_mode = CFG_RANDOM;
	configuracion->init_forma = CFG_TOROIDAL;

	while ((c = getopt_long(argc, argv, "hx:y:i:f:", long_options, &option_index)) != -1) {
		switch (c) {
		case 'h':
			configuracion->show_help = true;
			break;
		case 'x':
			configuracion->size_x = strtol(optarg, NULL, 0);
			break;
		case 'y':
			configuracion->size_y = strtol(optarg, NULL, 0);
			break;
		case 'i':
			configuracion->init_mode = str2init_mode(optarg);
			break;
		case 'f':
			configuracion->init_forma = str2init_forma(optarg);
			break;
		case '?':
			return false;
		}
	}

	if (optind != argc){
		if(optind == argc - 1) {
			configuracion->cfg_file = argv[optind];
			if(!load_config(configuracion)){
				return false;
			}
		}
		else{
			return false;
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
	correct &= configuracion->init_forma >= 0;
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

static enum cfg_init_forma str2init_forma(const char *opt)
{
	int i;
	for (i = 0; i < CFG_N_INIT_FORMA; i++){
		if(!strcmp(init_forma[i], opt)){
			break;
		}
	}

	return i == CFG_N_INIT_FORMA ? CFG_NOT_FORMA : i;
}
void config_print_usage(const char *arg0)
{
	printf("Usage: %s\n"
		"\t[-h|--help]\n"
		"\t[-x|--size_x <num>]\n"
		"\t[-y|--size_y <num>]\n"
		"\t[-i|--init <init_mode>]\n"
		"\t[-f|--init <init_forma>]\n"
		, arg0);

	printf("\nInitialization mode: ");
	printf("\nModo %s ", init_mode_str[0]);
	printf("\nModo %s ", init_mode_str[1]);
	printf("\nModo %s \n", init_mode_str[2]);

	printf("\nInicialization type: ");
	printf("\nTipo %s ", init_forma[0]);
	printf("\nTipo %s \n", init_forma[1]);
}

void config_print(const struct config *configuracion)
{
	printf("config {\n");
	printf("\tshow help = %s\n", configuracion->show_help ? "TRUE" : "FALSE");
	printf("\tsize_x    = %d\n", configuracion->size_x);
	printf("\tsize_y    = %d\n", configuracion->size_y);
	printf("\tinit_mode = %d(%s)\n",
			configuracion->init_mode, init_mode_str[configuracion->init_mode]);
	printf("\tinit_forma = %d(%s)\n",
			configuracion->init_forma, init_forma[configuracion->init_forma]);
	printf("}\n");
}


static bool load_config(struct config *configuracion){

	FILE *archivo;
	char linea[LONG_TEXT];

	archivo = fopen(configuracion->cfg_file, "r");
	if(archivo == NULL){
		return NULL;
	}

	// Size x
	fgets(linea, LONG_TEXT, archivo);
	if (ferror(archivo)){
		perror("Error reading config file");
		return false;
	}
	configuracion->size_x = strtol(linea, NULL, 0);

	// Size y
	fgets(linea, LONG_TEXT, archivo);
	if (ferror(archivo)){
		perror("Error reading config file");
		return false;
	}
	configuracion->size_y = strtol(linea, NULL, 0);

	// Mode
	fgets(linea, LONG_TEXT, archivo);
	if (ferror(archivo)){
		perror("Error reading config file");
		return false;
	}

	char *eol = strchr(linea, '\n');
	if (eol){
		*eol = '\0';
	}

	configuracion->init_mode = str2init_mode(linea);

	fgets(linea, LONG_TEXT, archivo);
	if (ferror(archivo)){
		perror("Error reading config file");
		return false;
	}

	eol = strchr(linea, '\n');
	if (eol){
		*eol = '\0';
	}

	configuracion->init_forma = str2init_forma(linea);

	fclose(archivo);
	return true;
}
