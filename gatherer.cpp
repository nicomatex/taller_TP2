/* Includes */
#include "gatherer.h"

#include <unistd.h>

#include "inventory.h"
#include "resource.h"

/* Implementacion */
Gatherer::Gatherer(ResourceQueue &resource_queue, Inventory &inventory)
    : resource_queue(resource_queue), inventory(inventory) {}

void Gatherer::run() {
  Resource resource;
  while ((resource = resource_queue.pop()) != RESOURCE_EMPTY) {
    usleep(GATHER_TIME);
    try {
      inventory.deposit(resource);
    } catch(InventoryClosedException &e) {
      std::cerr << e.what() << std::endl;
      break;
    }
  }
}
