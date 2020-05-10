#include "inventory.h"

#include <iostream>
#include <utility>

#include "config.h"
#include "resource.h"

char const* InventoryClosedException::what() { return ERR_CLOSED; }

/* Inicializacion del inventario, con todos los recursos en cantidad 0.*/
Inventory::Inventory()
    : content(std::unordered_map<Resource, unsigned int>()), isClosed(false) {
  this->content.insert({{WHEAT, 0}, {WOOD, 0}, {IRON, 0}, {COAL, 0}});
}

/* Incrementa la cantidad del recurso indicado por parametro en 1.*/
void Inventory::deposit(Resource resource) {
  std::unique_lock<std::mutex> lk(m);
  if (isClosed) {
    throw InventoryClosedException();
  }
  this->content[resource] += 1;
  cv.notify_all();
}

void Inventory::print_content() {
  std::cout << "  - " << NM_WHEAT << ": " << std::to_string(content[WHEAT])
            << std::endl;

  std::cout << "  - " << NM_WOOD << ": " << std::to_string(content[WOOD])
            << std::endl;

  std::cout << "  - " << NM_COAL << ": " << std::to_string(content[COAL])
            << std::endl;

  std::cout << "  - " << NM_IRON << ": " << std::to_string(content[IRON])
            << std::endl;
}

Inventory::~Inventory() {}

bool Inventory::enough_resources(const Request& request) {
  /* Se itera sobre todos los recursos de la solicitud */
  for (std::pair<Resource, unsigned int> element : request) {
    /* Si el contenido del inventario no es suficiente
    para alguno de los recursos, entonces no hay
    suficiente. */
    if (this->content[element.first] < element.second) {
      return false;
    }
  }
  return true;
}

bool Inventory::take_resources(const Request& request) {
  std::unique_lock<std::mutex> lk(m);

  while (!enough_resources(request)) {
    if (isClosed) {
      return false;
    }
    cv.wait(lk);
  }

  for (std::pair<Resource, unsigned int> element : request) {
    this->content[element.first] -= element.second;
  }

  return true;
}

void Inventory::close() {
  std::unique_lock<std::mutex> lk(m);
  isClosed = true;
  cv.notify_all();
}
