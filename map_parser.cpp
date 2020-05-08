#include "map_parser.h"
#include <unordered_map>
#include <fstream>

MapParser::MapParser(BlockingQueue<Resource> &farmer_queue,
                BlockingQueue<Resource> &lumberjack_queue,
                BlockingQueue<Resource> &miner_queue,
                const std::string map_filename) : 
                farmer_queue(farmer_queue),
                lumberjack_queue(lumberjack_queue),
                miner_queue(miner_queue),
                map_filename(map_filename),
                char_to_resource(std::unordered_map<char, Resource>()) 
                {
                    char_to_resource.insert({{'T',WHEAT},{'M',WOOD},
                                            {'C',COAL},{'H',IRON}});
                };

void MapParser::parse_and_fill_queues(){
    char buffer;

    try{
    std::fstream map_file(this->map_filename,std::fstream::in); 
        while(map_file >> std::skipws >> buffer){
            if(this->char_to_resource.find(buffer) == 
                this->char_to_resource.end()){
                    std::cerr << "Caracter invalido." << std::endl;
                    continue;
                }

            Resource resource = this->char_to_resource[buffer];

            switch(resource){
                case WOOD:
                    this->lumberjack_queue.push(resource);
                    break;
                case WHEAT:
                    this->farmer_queue.push(resource);
                    break;
                case IRON:
                case COAL:
                    this->miner_queue.push(resource);
                    break;
            }
        }
    }catch(const std::fstream::failure& e){
        std::cerr << "Error abriendo el archivo" << std::endl;
    }

    this->lumberjack_queue.close();
    this->miner_queue.close();
    this->farmer_queue.close();
}
