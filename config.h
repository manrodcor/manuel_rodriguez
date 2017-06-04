
#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdbool.h>

#define CFG_N_INIT_MODES (_CFG_MAX_)

enum cfg_init_mode {
	CFG_NOT_DEF = -1,
	CFG_DEFAULT,
	CFG_GLIDER,
	CFG_RANDOM,
	_CFG_MAX_,
};

enum cfg_forma{
	CFG_NOT_FORMA = -1,
	CFG_TOROIDAL,
	CFG_PLANO,
	_CFG_MAX2_,
};


struct config {
	bool show_help;
	int size_x;
	int size_y;
	enum cfg_init_mode init_mode;
	enum cfg_forma init_forma;
	char *cfg_file;
};

int config_parse_argv(struct config *configuracion, int argc, char *argv[]);
void config_print(const struct config *configuracion);
void config_print_usage(const char *arg0);


#endif
