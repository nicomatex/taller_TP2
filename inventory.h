
#ifndef __INVENTORY_H
#define __INVENTORY_H

/* Includes */
#include <unordered_map>
#include "resource.h"
#include <mutex>
#include <condition_variable>

/* Interfaz */
class Inventory{
    private:
        std::unordered_map<Resource,unsigned int> content;
        std::mutex m;
        std::condition_variable cv;

    public:
        /* Constructor y destructor */
        Inventory();
        ~Inventory();

        /* Deposita el recurso en el inventario, incrementando la 
        cantidad disponible de ese recurso en 1. */
        void deposit(Resource resource);

        /* Imprimir contenido del inventario. Solo para debug*/
        void print_content();

};

#endif