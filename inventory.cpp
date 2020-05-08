#include "inventory.h"
#include "resource.h"
#include <iostream>

/* Inicializacion del inventario, con todos los recursos en cantidad 0.*/
Inventory::Inventory():content(std::unordered_map<Resource, unsigned int>()){
   
    this->content.insert({{WHEAT,0},{WOOD,0},{IRON,0},{COAL,0}});
}

/* Incrementa la cantidad del recurso indicado por parametro en 1.*/
void Inventory::deposit(Resource resource){
    std::unique_lock<std::mutex> lk(m);
    this->content[resource] += 1;
}

void Inventory::print_content(){
    std::cout << "De madera hay " << std::to_string(this->content[WOOD]) << std::endl;
    std::cout << "De trigo hay " << std::to_string(this->content[WHEAT]) << std::endl;
    std::cout << "De carbon hay " << std::to_string(this->content[COAL]) << std::endl;
    std::cout << "De hierro hay " << std::to_string(this->content[IRON]) << std::endl;
}

Inventory::~Inventory(){}