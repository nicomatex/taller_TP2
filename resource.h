/* Defines de cada resource asociado a su numero de tipo */
#ifndef __RESOURCE_H
#define __RESOURCE_H
#include <string>

#include "blocking_queue.h"

typedef int Resource;
typedef BlockingQueue<Resource> ResourceQueue;

std::string res_name(Resource res);

#define RESOURCE_EMPTY 0
#define WHEAT 1
#define WOOD 2
#define IRON 3
#define COAL 4

#endif
