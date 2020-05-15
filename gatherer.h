#ifndef __GATHERER_H
#define __GATHERER_H

/* Includes */
#include "blocking_queue.h"
#include "inventory.h"
#include "thread.h"

/* Constantes */
#define GATHER_TIME 50000

/* Interfaz */
class Gatherer : public Thread {
   private:
    ResourceQueue *resource_queue;
    Inventory *inventory;

   public:
    Gatherer(ResourceQueue *resource_queue, Inventory *inventory);
    virtual void run() override;
};

#endif
