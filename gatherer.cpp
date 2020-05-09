/* Includes */
#include "gatherer.h"
#include <unistd.h>
#include "resource.h"
#include "inventory.h"

/* Implementacion */
Gatherer::Gatherer(BlockingQueue<int> &resource_queue, Inventory &inventory):
    resource_queue(resource_queue), resource(RESOURCE_EMPTY), inventory(inventory){}

void Gatherer::run(){
    resource = resource_queue.pop();
    while(resource != RESOURCE_EMPTY){
        usleep(GATHER_TIME);
        try{
            inventory.deposit(resource);
        }catch(InventoryClosedException &e){
            std::cerr << e.what() << std::endl;
            break;
        }
        resource = resource_queue.pop();
    }
}