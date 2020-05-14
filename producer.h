#ifndef __PRODUCER_H
#define __PRODUCER_H

/* Includes */
#include <unordered_map>
#include <utility>

#include "inventory.h"
#include "point_container.h"
#include "thread.h"

/* Constantes */
#define PRODUCE_TIME 60000

/* Interfaz */
class Producer : public Thread {
   private:
    Inventory &inventory;
    Recipe recipe;
    unsigned int puntos_generados;  // debug
    unsigned int benefit_generation;
    PointContainer &point_container;

   public:
    Producer(
        Inventory &inventory,
        std::initializer_list<std::pair<const Resource, unsigned int>> recipe,
        unsigned int benefit_generation, PointContainer &point_container);
    virtual void run() override;
};

#endif
