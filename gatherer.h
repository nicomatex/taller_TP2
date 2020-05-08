#ifndef __GATHERER_H
#define __GATHERER_H

/* Includes */
#include "blocking_queue.h"
#include "inventory.h"
#include "thread.h"

/* Interfaz */
class Gatherer: public Thread{
    private:
        BlockingQueue<int> &resource_queue;
        int resource;
        Inventory &inventory;
    public:
        Gatherer(BlockingQueue<int> &resource_queue, Inventory &inventory);
        virtual void run() override;
};

#endif