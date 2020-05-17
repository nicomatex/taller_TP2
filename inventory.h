#ifndef __INVENTORY_H
#define __INVENTORY_H

/* Includes */
#include <condition_variable>
#include <mutex>
#include <unordered_map>

#include "resource.h"

#define INITIAL_INVENTORY_CONTENT                                 \
    {                                                             \
        {ID_WHEAT, 0}, {ID_WOOD, 0}, {ID_IRON, 0}, { ID_COAL, 0 } \
    }
/* Excepciones */
struct InventoryClosedException : std::exception {
    char const *what();
};

/* Tipos */
typedef std::unordered_map<ResourceId, unsigned int> Recipe;

/* Interfaz */
class Inventory {
   private:
    std::unordered_map<ResourceId, unsigned int> content;
    std::mutex m;
    std::condition_variable cv;
    bool enough_resources(const Recipe &recipe);
    bool is_closed;

   public:
    /* Constructor y destructor */
    Inventory();
    ~Inventory();

    /* Deposita el recurso en el inventario, incrementando la
    cantidad disponible de ese recurso en 1. */
    void deposit(Resource &resource);
    void operator<<(Resource &resource);

    /* Imprimir contenido del inventario.*/
    void print_content();

    /* Recibe un mapa de recurso:cantidad de recursos a retirar
    del inventario. Devuelve true si el proceso fue exitoso
    y false en caso de que no hubiera los suficientes
    recursos disponibles, y sea seguro que tampoco los vaya a
    haber. */
    bool take_resources(const Recipe &recipe);

    void close();

    /* No se permite la construccion por copia ni movimiento. */
    Inventory(const Inventory &other) = delete;
    Inventory(Inventory &&other) = delete;
};

#endif
