/* Includes */
#include <unistd.h>

#include "gatherer.h"
#include "config.h"
#include "inventory.h"
#include "resource.h"

/* Implementacion */
Gatherer::Gatherer(ResourceQueue *resource_queue, Inventory *inventory)
    : resource_queue(resource_queue), inventory(inventory) {}

void Gatherer::run() {
    Resource resource(ID_EMPTY);
    while ((resource = resource_queue->pop()).get_id() != ID_EMPTY) {
        usleep(GATHER_TIME);
        try {
            *inventory << resource;
        } catch(InventoryClosedException &e) {
            std::cerr << e.what() << std::endl;
            break;
        }
    }
}
