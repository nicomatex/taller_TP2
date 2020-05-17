#include <iostream>
#include <utility>

#include "config.h"
#include "resource.h"
#include "inventory.h"

char const* InventoryClosedException::what() { return ERR_CLOSED; }

/* Inicializacion del inventario, con todos los recursos en cantidad 0.*/
Inventory::Inventory() : content(INITIAL_INVENTORY_CONTENT), is_closed(false) {}

/* Incrementa la cantidad del recurso indicado por parametro en 1.*/
void Inventory::deposit(Resource& resource) {
    std::unique_lock<std::mutex> lk(m);
    if (is_closed) {
        throw InventoryClosedException();
    }
    this->content[resource.get_id()] += 1;
    cv.notify_all();
}

void Inventory::operator<<(Resource& resource) { this->deposit(resource); }

void Inventory::print_content() {
    std::cout << "  - " << NM_WHEAT << ": " << std::to_string(content[ID_WHEAT])
              << std::endl;

    std::cout << "  - " << NM_WOOD << ": " << std::to_string(content[ID_WOOD])
              << std::endl;

    std::cout << "  - " << NM_COAL << ": " << std::to_string(content[ID_COAL])
              << std::endl;

    std::cout << "  - " << NM_IRON << ": " << std::to_string(content[ID_IRON])
              << std::endl;
}

Inventory::~Inventory() {}

bool Inventory::enough_resources(const Recipe& recipe) {
    /* Se itera sobre todos los recursos de la solicitud */
    for (std::pair<ResourceId, unsigned int> element : recipe) {
        /* Si el contenido del inventario no es suficiente
        para alguno de los recursos, entonces no hay
        suficiente. */
        if (this->content[element.first] < element.second) {
            return false;
        }
    }
    return true;
}

bool Inventory::take_resources(const Recipe& recipe) {
    std::unique_lock<std::mutex> lk(m);

    while (!enough_resources(recipe)) {
        if (is_closed) {
            return false;
        }
        cv.wait(lk);
    }

    for (std::pair<ResourceId, unsigned int> element : recipe) {
        this->content[element.first] -= element.second;
    }

    return true;
}

void Inventory::close() {
    std::unique_lock<std::mutex> lk(m);
    is_closed = true;
    cv.notify_all();
}
