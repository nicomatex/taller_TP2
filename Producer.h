#ifndef __PRODUCER_H
#define __PRODUCER_H

/* Includes */
#include <unordered_map>
#include <utility>

#include "Inventory.h"
#include "PointContainer.h"
#include "Thread.h"

/* Constantes */
#define PRODUCE_TIME 60000

/* Interfaz */
class Producer : public Thread {
   private:
    Inventory *inventory;
    Recipe recipe;
    unsigned int benefit_generation;
    PointContainer *point_container;

   public:
    Producer(
        Inventory *inventory,
        std::initializer_list<std::pair<const ResourceId, unsigned int>> recipe,
        unsigned int benefit_generation, PointContainer *point_container);
    virtual void run() override;
};

#endif
