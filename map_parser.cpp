#include <exception>
#include <fstream>
#include <string>

#include "map_parser.h"

char const *MapFileException::what() { return ERR_MAPFILE; }

MapParser::MapParser(ResourceQueue *farmer_queue,
                     ResourceQueue *lumberjack_queue,
                     ResourceQueue *miner_queue, const std::string map_filename)
    : farmer_queue(farmer_queue),
      lumberjack_queue(lumberjack_queue),
      miner_queue(miner_queue),
      map_filename(map_filename),
      char_to_id(IDS_BY_CHAR),
      queue_by_id({{ID_WHEAT, farmer_queue},
                   {ID_COAL, miner_queue},
                   {ID_IRON, miner_queue},
                   {ID_WOOD, lumberjack_queue}}) {}

MapParser::~MapParser() {}

/* Cierra todas las colas para indicar que ya no habra
mas recursos disponibles.*/
void MapParser::done() {
    farmer_queue->close();
    lumberjack_queue->close();
    miner_queue->close();
}

void MapParser::parse_and_fill_queues() {
    char buffer;

    std::ifstream map_file(this->map_filename, std::ifstream::in);
    if (!map_file) {
        this->done();
        throw MapFileException();
    }

    while (map_file >> std::skipws >> buffer) {
        if (this->char_to_id.count(buffer) == 0) {
            std::cerr << ERR_INVALID_CHAR << std::endl;
            continue;
        }
        int resource_id = this->char_to_id[buffer];

        /* Se encola una copia del recurso. */
        queue_by_id[resource_id]->push(Resource(resource_id));
    }
    this->done();
}
