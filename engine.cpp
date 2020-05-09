#include "engine.h"
#include "resource.h"

Engine::Engine(const std::string map_file):
        lumberjack_queue(RESOURCE_EMPTY),
        miner_queue(RESOURCE_EMPTY),
        farmer_queue(RESOURCE_EMPTY),
        inventory(),
        map_parser(lumberjack_queue,miner_queue,farmer_queue,map_file)
{}

void Engine::spawn_gatherers(int farmers,int miners,int lumberjacks){
    for ( int i = 0; i < farmers; i++){
        Gatherer *g = new Gatherer(farmer_queue,inventory);
        g->start();
        gatherers.push_back(g);
    }
    for (int  i = 0; i < miners; i++){
        Gatherer *g = new Gatherer(miner_queue,inventory);
        g->start();
        gatherers.push_back(g);
    }
    for (int  i = 0; i < lumberjacks; i++){
        Gatherer *g = new Gatherer(lumberjack_queue,inventory);
        g->start();
        gatherers.push_back(g);
    }
}

void Engine::spawn_producers(int cooks,int carpenters,int smiths){
    for ( int  i = 0; i < smiths; i++ ){
        Producer *p = new Producer(inventory,{{COAL,2},{IRON,2}},3
        ,point_container);
        p->start();
        producers.push_back(p);
    }
    for ( int  i = 0; i < cooks; i++){
        Producer *p = new Producer(inventory,{{WHEAT,2},{COAL,1}},5
        ,point_container);
        p->start();
        producers.push_back(p);
    }
    for ( int  i = 0; i < carpenters; i++ ){
        Producer *p = new Producer(inventory,{{WOOD,3},{IRON,1}},2
        ,point_container);
        p->start();
        producers.push_back(p);
    }
    
}

void Engine::spawn_resources(){
    map_parser.parse_and_fill_queues();
}

void Engine::close_inventory(){
    inventory.close();
}

void Engine::join_gatherers(){
    for ( std::size_t  i = 0;i < gatherers.size(); i++){
        gatherers[i]->join();
    }
}

void Engine::join_producers(){
    for ( std::size_t  i = 0;i < producers.size(); i++){
        producers[i]->join();
    }
}

Engine::~Engine(){
    for ( std::size_t  i = 0;i < gatherers.size(); i++){
        delete gatherers[i];
    }

    for ( std::size_t  i = 0;i < producers.size(); i++){
        delete producers[i];
    }
}

unsigned int Engine::get_points(){
    return point_container.get_points();
}

void Engine::print_resources_left(){
    inventory.print_content();
}