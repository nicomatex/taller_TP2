#include <iostream>

#include "config.h"
#include "engine.h"

int main(void) {
  Engine engine("map.txt");
  engine.spawn_gatherers(2, 3, 1);
  engine.spawn_producers(1, 3, 1);

  engine.spawn_resources();
  engine.join_gatherers();
  engine.close_inventory();
  engine.join_producers();

  engine.print_resources_left();
  engine.print_benefit_points();
  return 0;
}