#include <iostream>
#include <thread>
#include <vector>

#include "resource.h"
#include "blocking_queue.h"
#include "map_parser.h"
#include "gatherer.h"
#include "inventory.h"

int main(){
    BlockingQueue<Resource> lumberjack_queue(RESOURCE_EMPTY);
    BlockingQueue<Resource> farmer_queue(RESOURCE_EMPTY);
    BlockingQueue<Resource> miner_queue(RESOURCE_EMPTY);
    Inventory inventario;

    Gatherer lumberjack(lumberjack_queue,inventario);
    Gatherer miner(miner_queue,inventario);
    Gatherer farmer(farmer_queue,inventario);

    lumberjack.start();
    miner.start();
    farmer.start();

    MapParser parser(farmer_queue,lumberjack_queue,miner_queue,"map.txt");
    parser.parse_and_fill_queues();

    lumberjack.join();
    miner.join();
    farmer.join();

    inventario.print_content();
    return 0;
}