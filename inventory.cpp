#include "inventory.h"
#include "resource.h"
#include <iostream>

char const* InventoryClosedException::what(){
    return "Se intento agregar un recurso con el inventario cerrado.\n";
}

/* Inicializacion del inventario, con todos los recursos en cantidad 0.*/
Inventory::Inventory():content(std::unordered_map<Resource, unsigned int>()),
                        isClosed(false){
    this->content.insert({{WHEAT,0},{WOOD,0},{IRON,0},{COAL,0}});
}

/* Incrementa la cantidad del recurso indicado por parametro en 1.*/
void Inventory::deposit(Resource resource){
    std::unique_lock<std::mutex> lk(m);
    if(isClosed){
        throw InventoryClosedException();
    }
    this->content[resource] += 1;
    cv.notify_all();
}

void Inventory::print_content(){
    std::cout << "De madera hay " << std::to_string(this->content[WOOD]) << std::endl;
    std::cout << "De trigo hay " << std::to_string(this->content[WHEAT]) << std::endl;
    std::cout << "De carbon hay " << std::to_string(this->content[COAL]) << std::endl;
    std::cout << "De hierro hay " << std::to_string(this->content[IRON]) << std::endl;
}

Inventory::~Inventory(){}

bool Inventory::enough_resources(const std::unordered_map<Resource,unsigned int>& request){
    /* Se itera sobre todos los recursos de la solicitud */
    for(std::pair<Resource, unsigned int> element: request){
        /* Si el contenido del inventario no es suficiente 
        para alguno de los recursos, entonces no hay 
        suficiente. */
        if(content[element.first] < element.second){
            return false;
        }
    }
    return true;
}

bool Inventory::take_resources(const std::unordered_map<Resource,unsigned int> &request){
    std::unique_lock<std::mutex> lk(m);

    while(!enough_resources(request)){
        if(isClosed){
            return false;
        }
        cv.wait(lk);
    }

    std::cout << "-------" << std::endl;
    for(std::pair<Resource, unsigned int> element: request){
        content[element.first] -= element.second;
        std::cout << "quitados " << std::to_string(element.second) 
        << " de " << std::to_string(element.first) << std::endl;
    }
    std::cout << "-------" << std::endl;
    return true;
}

void Inventory::close(){
    std::unique_lock<std::mutex> lk(m);
    isClosed = true;
    cv.notify_all();
}