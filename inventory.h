#ifndef __INVENTORY_H
#define __INVENTORY_H

/* Includes */
#include <unordered_map>
#include "resource.h"
#include <mutex>
#include <condition_variable>

/* Excepciones */
struct InventoryClosedException : std::exception { 
    char const* what();
};

/* Interfaz */
class Inventory{
    private:
        std::unordered_map<Resource,unsigned int> content;
        std::mutex m;
        std::condition_variable cv;
        bool enough_resources(const std::unordered_map<Resource,unsigned int> &request);
        bool isClosed;

    public:
        /* Constructor y destructor */
        Inventory();
        ~Inventory();

        /* Deposita el recurso en el inventario, incrementando la 
        cantidad disponible de ese recurso en 1. */
        void deposit(Resource resource);

        /* Imprimir contenido del inventario.*/
        void print_content();

        /* Recibe un mapa de recurso:cantidad de recursos a retirar
        del inventario. Devuelve true si el proceso fue exitoso 
        y false en caso de que no hubiera los suficientes 
        recursos disponibles, y sea seguro que tampoco los vaya a 
        haber. */
        bool take_resources(const std::unordered_map<Resource,unsigned int> &request);

        void close();

};

#endif