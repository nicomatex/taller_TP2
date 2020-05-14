#include "map_parser.h"

#include <exception>
#include <fstream>
#include <string>
#include <unordered_map>

#include "config.h"

char const *MapFileException::what() { return ERR_MAPFILE; }

MapParser::MapParser(ResourceQueue &farmer_queue,
                     ResourceQueue &lumberjack_queue,
                     ResourceQueue &miner_queue, const std::string map_filename)
    : farmer_queue(farmer_queue),
      lumberjack_queue(lumberjack_queue),
      miner_queue(miner_queue),
      map_filename(map_filename),
      char_to_resource(std::unordered_map<char, Resource>()) {
    char_to_resource.insert(
        {{'T', WHEAT}, {'M', WOOD}, {'C', COAL}, {'H', IRON}});
}

MapParser::~MapParser() {}

/* Cierra todas las colas para indicar que ya no habra
mas recursos disponibles.*/
void MapParser::done() {
    farmer_queue.close();
    lumberjack_queue.close();
    miner_queue.close();
}

void MapParser::parse_and_fill_queues() {
    char buffer;

    std::ifstream map_file(this->map_filename, std::ifstream::in);
    if (!map_file) {
        this->done();
        throw MapFileException();
    }

    while (map_file >> std::skipws >> buffer) {
        if (this->char_to_resource.find(buffer) ==
            this->char_to_resource.end()) {
            std::cerr << "Caracter invalido." << std::endl;
            continue;
        }

        Resource resource = this->char_to_resource[buffer];

        switch (resource) {
            case WOOD:
                this->lumberjack_queue.push(resource);
                break;
            case WHEAT:
                this->farmer_queue.push(resource);
                break;
            case IRON:
                this->miner_queue.push(resource);
                break;
            case COAL:
                this->miner_queue.push(resource);
                break;
        }
    }
    this->done();
}
