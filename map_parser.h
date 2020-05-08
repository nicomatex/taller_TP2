#ifndef __MAP_PARSER_H
#define __MAP_PARSER_H

/* Includes */
#include "blocking_queue.h"
#include "resource.h"
#include <unordered_map>

/* Interfaz */
class MapParser{
    private:
        BlockingQueue<Resource> &farmer_queue;
        BlockingQueue<Resource> &lumberjack_queue;
        BlockingQueue<Resource> &miner_queue;
        const std::string map_filename;
        std::unordered_map<char, Resource> char_to_resource; 
    public:

        /*Recibe por parametro referencias a las colas
        correspondientes a cada tipo de recolector y la 
        ruta del archivo que se debe parsear.*/
        MapParser(BlockingQueue<Resource> &farmer_queue,
                BlockingQueue<Resource> &lumberjack_queue,
                BlockingQueue<Resource> &miner_queue,
                const std::string map_filename);

        /*Parsea el archivo y envia los recursos 
        correspondientes a cada cola segun el tipo
        de recurso.*/
        void parse_and_fill_queues();
};

#endif