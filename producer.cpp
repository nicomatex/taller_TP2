/* Includes */
#include "producer.h"

#include <unistd.h>
#include <iostream>
#include <unordered_map>
#include <utility>

/* Implementacion */
Producer::Producer(
    Inventory &inventory,
    std::initializer_list<std::pair<const Resource, unsigned int>> request,
    unsigned int benefit_generation, PointContainer &point_container)
    : inventory(inventory),
      request(Request()),
      benefit_generation(benefit_generation),
      point_container(point_container) {
  this->request.insert(request);
  puntos_generados = 0;
}

void Producer::run() {
  while (inventory.take_resources(request)) {
    usleep(PRODUCE_TIME);
    point_container.add_points(benefit_generation);
  }
}
