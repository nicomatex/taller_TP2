/* Includes */
#include "gatherer.h"
#include <unistd.h>
#include "resource.h"
#include "inventory.h"

/* Constantes */
#define GATHER_TIME 50000

/* Implementacion */
Gatherer::Gatherer(BlockingQueue<int> &resource_queue, Inventory &inventory):
    inventory(inventory), resource_queue(resource_queue), resource(RESOURCE_EMPTY){}

void Gatherer::run(){
    resource = resource_queue.pop();
    while(resource != RESOURCE_EMPTY){
        usleep(GATHER_TIME);
        inventory.deposit(resource);
        resource = resource_queue.pop();
    }
}