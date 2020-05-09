#include <iostream>
#include "engine.h"

int main(void){
    Engine engine("map.txt");
    engine.spawn_gatherers(2,3,1);
    engine.spawn_producers(0,0,1);
    engine.spawn_resources();
    engine.join_gatherers();
    engine.close_inventory();
    engine.join_producers();
    std::cout << "Puntos generados: " << engine.get_points() << std::endl;
    engine.print_resources_left();
    return 0;
}