#ifndef __MAP_PARSER_H
#define __MAP_PARSER_H

/* Includes */
#include <string>
#include <unordered_map>

#include "blocking_queue.h"
#include "config.h"
#include "resource.h"

/* Asociacion de cada caracter al id del recurso que representa. */
#define IDS_BY_CHAR                                                           \
    {                                                                         \
        {CHAR_WHEAT, ID_WHEAT}, {CHAR_WOOD, ID_WOOD}, {CHAR_COAL, ID_COAL}, { \
            CHAR_IRON, ID_IRON                                                \
        }                                                                     \
    }

/* Excepciones */
struct MapFileException : std::exception {
    char const *what();
};

/* Interfaz */
class MapParser {
   private:
    ResourceQueue *farmer_queue;
    ResourceQueue *lumberjack_queue;
    ResourceQueue *miner_queue;
    const std::string map_filename;
    std::unordered_map<char, ResourceId> char_to_id;
    std::unordered_map<ResourceId, ResourceQueue *> queue_by_id;
    void done();

   public:
    /*Recibe por parametro referencias a las colas
    correspondientes a cada tipo de recolector y la
    ruta del archivo que se debe parsear.*/
    MapParser(ResourceQueue *farmer_queue, ResourceQueue *lumberjack_queue,
              ResourceQueue *miner_queue, const std::string map_filename);

    ~MapParser();
    /*Parsea el archivo y envia los recursos
    correspondientes a cada cola segun el tipo
    de recurso.*/
    void parse_and_fill_queues();

    /* No se permite la construccion por copia ni por movimiento. */
    MapParser(const MapParser& other) = delete;
    MapParser(MapParser&& other) = delete;
};

#endif
