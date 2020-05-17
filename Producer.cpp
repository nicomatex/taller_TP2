/* Includes */
#include <unistd.h>
#include <iostream>
#include <utility>
#include "Producer.h"

/* Implementacion */
Producer::Producer(
    Inventory *inventory,
    std::initializer_list<std::pair<const ResourceId, unsigned int>> recipe,
    unsigned int benefit_generation, PointContainer *point_container)
    : inventory(inventory),
      recipe(recipe),
      benefit_generation(benefit_generation),
      point_container(point_container) {}

void Producer::run() {
    while (inventory->take_resources(recipe)) {
        usleep(PRODUCE_TIME);
        point_container->add_points(benefit_generation);
    }
}
