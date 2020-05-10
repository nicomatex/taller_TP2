#ifndef __MAP_PARSER_H
#define __MAP_PARSER_H

/* Includes */
#include <unordered_map>
#include <string>

#include "blocking_queue.h"
#include "resource.h"

/* Excepciones */
struct MapFileException : std::exception {
  char const *what();
};

/* Interfaz */
class MapParser {
 private:
  ResourceQueue &farmer_queue;
  ResourceQueue &lumberjack_queue;
  ResourceQueue &miner_queue;
  const std::string map_filename;
  std::unordered_map<char, Resource> char_to_resource;
  void done();

 public:
  /*Recibe por parametro referencias a las colas
  correspondientes a cada tipo de recolector y la
  ruta del archivo que se debe parsear.*/
  MapParser(ResourceQueue &farmer_queue,
            ResourceQueue &lumberjack_queue,
            ResourceQueue &miner_queue,
            const std::string map_filename);

  ~MapParser();
  /*Parsea el archivo y envia los recursos
  correspondientes a cada cola segun el tipo
  de recurso.*/
  void parse_and_fill_queues();
};

#endif
