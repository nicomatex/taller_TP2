#include <iostream>

#include "config.h"
#include "engine.h"

#define ARG_QTY 3

#define ARG_POS_MAP 2
#define ARG_POS_WORKERS 1

int main(int argc, char *argv[]) {
    if (argc != ARG_QTY) {
        std::cerr << ERR_PARAM_QTY << std::endl;
        return -1;
    }

    Engine engine(argv[ARG_POS_MAP], argv[ARG_POS_WORKERS]);

    engine.spawn_workers();

    engine.spawn_resources();
    engine.join_gatherers();
    engine.close_inventory();
    engine.join_producers();

    engine.print_resources_left();
    engine.print_benefit_points();
    return 0;
}
