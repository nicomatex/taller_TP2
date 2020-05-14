#ifndef __CONFIG_H
#define __CONFIG_H

/* Mensajes */
#define MSG_POINTS "Puntos de Beneficio acumulados: "
#define MSG_RESOURCES_LEFT "Recursos restantes:"

/* Nombres de recursos */
#define NM_EMPTY "Vacio"
#define NM_WHEAT "Trigo"
#define NM_IRON "Hierro"
#define NM_COAL "Carbon"
#define NM_WOOD "Madera"

/* Nombres de trabajadores */
#define NM_FARMERS "Agricultores"
#define NM_LUMBERJACKS "Leniadores"
#define NM_MINERS "Mineros"
#define NM_COOKS "Cocineros"
#define NM_CARPENTERS "Carpinteros"
#define NM_SMITHS "Armeros"

/* Id de cada recurso */
#define ID_EMPTY 0
#define ID_WHEAT 1
#define ID_WOOD 2
#define ID_IRON 3
#define ID_COAL 4

/* Asociacion de cada char del archivo mapa 
al id que representa */
#define CHAR_WHEAT 'T'
#define CHAR_IRON 'H'
#define CHAR_WOOD 'M'
#define CHAR_COAL 'C'

/* Errores */
#define ERR_MAPFILE "Error con el archivo de mapa."
#define ERR_CLOSED "Se intento agregar un recurso con el inventario cerrado."
#define ERR_WORKERFILE "Error con el archivo de trabajadores."
#define ERR_PARAM_QTY "Cantidad erronea de parametros."
#define ERR_INVALID_CHAR "Caracter invalido."

/* Recetas */
#define RECIPE_SMITH {{ID_COAL, 2}, {ID_IRON, 2}}
#define RECIPE_COOK {{ID_WHEAT, 2}, {ID_COAL, 1}}
#define RECIPE_CARPENTER {{ID_WOOD, 3}, {ID_IRON, 1}}

/* Puntos de beneficio generados */
#define PTS_SMITH 3
#define PTS_COOK 5
#define PTS_CARPENTER 2
#endif
