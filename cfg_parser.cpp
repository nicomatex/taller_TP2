#include "cfg_parser.h"

#include <fstream>
#include <sstream>
#include <string>

#include "config.h"

char const *WorkerFileException::what() { return ERR_WORKERFILE; }

ConfigParser::ConfigParser(const std::string worker_filename)
    : worker_filename(worker_filename) {}

ConfigParser::~ConfigParser() {}

WorkerList ConfigParser::get_worker_list() {
    std::ifstream worker_file(this->worker_filename);
    if (!worker_file) {
        throw WorkerFileException();
    }

    WorkerList worker_list({{NM_CARPENTERS, 0},
                            {NM_COOKS, 0},
                            {NM_SMITHS, 0},
                            {NM_FARMERS, 0},
                            {NM_LUMBERJACKS, 0},
                            {NM_MINERS, 0}});

    std::string line;

    while (std::getline(worker_file, line)) {
        std::istringstream linestream(line);
        std::string worker;

        if (std::getline(linestream, worker, '=')) {
            std::string amount;

            if (std::getline(linestream, amount)) {
                worker_list[worker] = std::stoi(amount);
            } else {
                throw WorkerFileException();
                break;
            }
        } else {
            throw WorkerFileException();
            break;
        }
    }
    return worker_list;
}
