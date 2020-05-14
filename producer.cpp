/* Includes */
#include "producer.h"

#include <unistd.h>

#include <iostream>
#include <unordered_map>
#include <utility>

/* Implementacion */
Producer::Producer(
    Inventory &inventory,
    std::initializer_list<std::pair<const Resource, unsigned int>> recipe,
    unsigned int benefit_generation, PointContainer &point_container)
    : inventory(inventory),
      recipe(Recipe()),
      benefit_generation(benefit_generation),
      point_container(point_container) {
    this->recipe.insert(recipe);
    puntos_generados = 0;
}

void Producer::run() {
    while (inventory.take_resources(recipe)) {
        usleep(PRODUCE_TIME);
        point_container.add_points(benefit_generation);
    }
}
