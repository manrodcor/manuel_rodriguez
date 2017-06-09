Juego de la vida
================

Tarea 1: Versión inicial del mundo

    Haz un fork del repositorio con tu nombre
    Clona tu repositorio
    Completa el esqueleto proporcionado para implementar una primera versión funcional del juego de la vida
    Sube los cambios al tu repositorio
    Haz un pull request
    Arregla las correcciones del profesor
    Sube las correcciones a tu repo
    ¿Has conseguido que te acepten el pull request?
        NO -> goto 6
        Sí -> ¡Enhorabuena! Ya has terminado la tarea 1 



Tarea 2: Código modular, estructuras y makefile

a) Divide tu programa en 3 fichero:

    main.c : Implementará el bucle principal del juego
    gol.h  : Tendrá las declaraciones de las funciones relacionadas con el juego de la vida
    gol.c  : Tendrá las definiciones de las funciones anteriores 

b) Crea un makefile para gestionar la compilación y dependencias 


Tarea 3: Primera aproximación a objetos

1. Encapsula tu mundo en la siguiente estructura:

struct world {
        bool w1[W_SIZE_X][W_SIZE_Y];
        bool w2[W_SIZE_X][W_SIZE_Y];
};

2. Modifica tus funciones para que reciban un puntero a tu objeto. Añade el modificador const siempre que no sea necesario modificar el objeto

Tu main.c debería quedar más o menos así:

#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

int main()
{
	int i = 0;
	struct world w;

	world_init(&w);
	do {
		printf("\033cIteration %d\n", i++);
		world_print(&w);
		world_step(&w);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}


TAREA 4: Objetos: Reserva dinámica de memoria
Interfaz pública

gol.h

struct world;

struct world *world_alloc(int size_x, int size_y);
void world_free(struct world *w);

void world_print(const struct world *w);
void world_iterate(struct world *w);

    world_alloc: Reserva en memoria e inicializa nuestro objeto struct world. Esto implica reservar memoria para la estrucutra y para los dos arrays que tiene dentro.
    world_free: Libera la memoria que ocupa nuestro objeto. Esto implica liberar primero la memoria de los arrays que tiene dentro la estrucutra, y luego la propia estructura.
    world_print: Imprime el mundo
    world_iterate: Realiza una iteración del juego de la vida 


Implementación (privada)

gol.c

struct world
{
	bool *cells[2];
	int size_x;
	int size_y;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);

/* ... */
/* Definiciones de funciones privadas y públicas */
/* ... */

    fix_coords: Recibe unas coordenadas (x,y) y las modifica para implementar un mundo toroidal
    get_cell: Devuelve la célula en la posición (x,y), arreglando las coordenadas.
    set_cell: Cambia el valor de la célula de la posición (x,y), arreglando las coordenadas.
    count_neighbors: Cuenta las células vecinas haciendo uso de la función get_cell 

NOTAS

    No olvides comprobar que has podido realizar correctamente la reserva de memoria: 

En world_alloc():

w = (struct world *)malloc(sizeof(struct world));
if (!w)
	return NULL;

En main():

w = world_alloc(WORLD_X, WORLD_Y);
if (!w) {
	perror("Can't allocate world");
	exit(EXIT_FAILURE);
}

    Las funciones privadas se declaran como static y no aparecen el el .h
    Ahora debes calcular a mano el offset en el array para llegar a la célula (x,y) con la fórmula: size_x*y + x. Encapsula esta fórmula en las funciones get_cell y set_cell. 

Tarea 5: Argumentos y lectura de ficheros

Al final de esta tarea tu juego de la vida deberá poder configurarse tanto por paso de argumentos como mediante un archivo de configuración. La ayuda del programa devolvería lo siguiente:

Usage: gol
	[-h|--help]
	[-x|--size_x <num>]
	[-y|--size_y <num>]
	[-i|--init <init_mode>]
	[config_file]


Esta tarea se divide en 3 subtareas distintas que deben corresponder con 3 commits, uno por subtarea. La subtarea 3 es **opcional**.
[editar] Tarea 5.1: Objeto struct config

Completa la plantilla que encontrarás aquí: Archivo:Cfg template.tar para agrupar toda la lógica de configuración en un objeto.

Intégrala después en tu main de esta forma (debes modificar también world_alloc):

    int main(int argc, char *argv[])

    {

    	struct config config;

    	struct world * w;

     

    	if (!config_parse_argv(&config, argc, argv)) {

    		printf("ERROR\n");

    		config_print_usage(argv[0]);

    		return EXIT_FAILURE;

    	} else if (config.show_help){

    		config_print_usage(argv[0]);

    		return EXIT_SUCCESS;

    	}

     

    	w = world_alloc(&config);

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

De esta plantilla hay que destacar los siguientes puntos:

    Se define un objeto sencillo, público, sin reserva dinámica de memoria
    Se usa un enumerado para definir el tipo de inicialización con las siguientes peculiaridades:
        El primer elemento representa un modo no válido y forzamos su valor a -1
        El último elemento se usa para tener en una macro el número de elementos del enumerado. Por ello el nombre está entre barras bajas, para marcarlo como una opción no válida
        En el .c se define un array constante de cadenas, asociando cada cadena con su correspondiente valor en el enumerado. Se utiliza un inicializador un tanto particular, dónde inicializamos explicitamente los elementos del array mediante su índice: El índice se indica entre corchetes y se le asigna un valor con el operador igual: [3] = 41
        Se usa el array anterior para convertir el enumerado a una cadena, simplemente hay que acceder al array con el valor del enumerado como índice: init_mode_str[CFG_GLIDER] 
    Se define una función privada check_config que agrupa la lógica de validación de argumentos. Devuelve false si los argumentos nos son válidos y true si lo son
    La función str2init_mode recibe una cadena y la va comparando una por una con las cadenas de modos de inicialización para ver con cual coincide. Si no coincide con ninguna devuelve CFG_NOT_DEF para indicar que no es un modo válido. 

[editar] Tarea 5.2: Cargar fichero de configuración

Ahora has de permitir que tu programa lea la configuración de un archivo:

    El nombre del archivo ha de recibirse a través de los argumentos del programa, pero **no a través de un flag con getopt**. Ejemplo: > gol config.txt
    Las configuraciones del archivo tienen preferencia sobre los argumentos por consola
    El archivo de configuración constará de 3 líneas:
        Ancho del mundo
        Alto del mundo
        Tipo de inicialización 

Ejemplo config.txt:

20
15
glider

    Crea una función privada static bool load_config(struct config *config); que se encarge de abrir, parsear y cerrar el fichero. Devolverá cierto si todo ha ido bien y falso en caso contrario.
    La función fgets devuelve una cadena con un salto de línea (si lo hay). Vas a tener que quitárselo haciendo uso de la función strchr
    Échale un ojo a este fragmento de código: 

    int config_parse_argv(struct config *config, int argc, char *argv[])

    {

    	...

     

    	// Check for config file name

    	if (optind != argc) {

    		if (optind == argc - 1) {

    			config->cfg_file = argv[optind];

    			if (!load_config(config))

    				return false;

    		} else {

    			return false;

    		}

    	}

     

    	return check_config(config);

    }

    Y a este otro: 

    	// Size x

    	char line[LINE_LEN];

    	fgets(line, LINE_LEN, file);

    	if (ferror(file)) {

    		perror("Error reading config file");

    		return false;

    	}

    	config->size_x = strtol(line, NULL, 0);

[editar] Tarea 5.3 [opcional]: Guarda y carga de estado

Haz que tu juego de la vida guarde el estado del mundo antes de salir, en un archivo con el nombre que elijas. Haz también que este archivo se pueda cargar al lanzarlo de nuevo, para que comience por el mismo estado.

Notas:

    Has de crear dos nuevas opciones getopt para indicar el nombre del archivo a guardar y a cargar
    Para guardar el estado, haz un volcado directo en binario del array en un archivo. Utiliza la función fwrite pasándole tu array y su tamaño. Ten en cuenta que debes guardar también las dimensiones de tu mundo.
    Para cargar el estado, haz una lectura directa del archivo binario con la función fread. Puedes volcar el contenido del archivo directamente en el array de tu estructura, pero no olvides reservar la memoria primero (para esto debes leer antes las dimensiones de tu mundo) 

 Tarea 6: Herencia

    Divide tu arquitectura en tres objetos:
        world: Objeto abstracto que no tienen implementada las funciones world_get_cell y world_set_cell, pero sí el resto
        world_limited: Objeto que hereda de world e implementa las funciones world_get_cell y world_set_cell de forma que se devuelva una célula muerta si los índices se salen del array y no haga nada en el caso del setter
        world_toroidal: Objeto que hereda de world e implementa las funciones world_get_cell y world_set_cell para accedar al mundo de forma toroidal. Aquí además debes implementar la función fix_coords para usarla en tu getter y setter. 

Herencia.png 

