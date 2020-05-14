#include "engine.h"

#include <string>

#include "config.h"
#include "resource.h"

Engine::Engine(const std::string map_file, const std::string config_file)
    : lumberjack_queue(RESOURCE_EMPTY),
      miner_queue(RESOURCE_EMPTY),
      farmer_queue(RESOURCE_EMPTY),
      inventory(),
      map_parser(farmer_queue, lumberjack_queue, miner_queue, map_file),
      config_parser(config_file) {}

void Engine::spawn_gatherers(WorkerList &worker_list) {
    for (int i = 0; i < worker_list[NM_FARMERS]; i++) {
        Gatherer *g = new Gatherer(farmer_queue, inventory);
        g->start();
        gatherers.push_back(g);
    }
    for (int i = 0; i < worker_list[NM_MINERS]; i++) {
        Gatherer *g = new Gatherer(miner_queue, inventory);
        g->start();
        gatherers.push_back(g);
    }
    for (int i = 0; i < worker_list[NM_LUMBERJACKS]; i++) {
        Gatherer *g = new Gatherer(lumberjack_queue, inventory);
        g->start();
        gatherers.push_back(g);
    }
}

void Engine::spawn_producers(WorkerList &worker_list) {
    for (int i = 0; i < worker_list[NM_SMITHS]; i++) {
        Producer *p =
            new Producer(inventory, {{COAL, 2}, {IRON, 2}}, 3, point_container);
        p->start();
        producers.push_back(p);
    }
    for (int i = 0; i < worker_list[NM_COOKS]; i++) {
        Producer *p = new Producer(inventory, {{WHEAT, 2}, {COAL, 1}}, 5,
                                   point_container);
        p->start();
        producers.push_back(p);
    }
    for (int i = 0; i < worker_list[NM_CARPENTERS]; i++) {
        Producer *p =
            new Producer(inventory, {{WOOD, 3}, {IRON, 1}}, 2, point_container);
        p->start();
        producers.push_back(p);
    }
}

void Engine::spawn_workers() {
    WorkerList worker_list;
    try {
        worker_list = config_parser.get_worker_list();
    } catch(WorkerFileException &e){
        std::cerr << e.what() << std::endl;
        return;
    }

    spawn_gatherers(worker_list);
    spawn_producers(worker_list);
}

void Engine::spawn_resources() {
    try {
        map_parser.parse_and_fill_queues();
    } catch(MapFileException &e){
        std::cerr << e.what() << std::endl;
    }
}

void Engine::close_inventory() { inventory.close(); }

void Engine::join_gatherers() {
    for (std::size_t i = 0; i < gatherers.size(); i++) {
        gatherers[i]->join();
    }
}

void Engine::join_producers() {
    for (std::size_t i = 0; i < producers.size(); i++) {
        producers[i]->join();
    }
}

Engine::~Engine() {
    for (std::size_t i = 0; i < gatherers.size(); i++) {
        delete gatherers[i];
    }

    for (std::size_t i = 0; i < producers.size(); i++) {
        delete producers[i];
    }
}

unsigned int Engine::get_points() { return point_container.get_points(); }

void Engine::print_resources_left() {
    std::cout << MSG_RESOURCES_LEFT << std::endl;
    inventory.print_content();
    std::cout << '\n';
}

void Engine::print_benefit_points() {
    unsigned int points = point_container.get_points();
    std::cout << MSG_POINTS << std::to_string(points) << std::endl;
}
