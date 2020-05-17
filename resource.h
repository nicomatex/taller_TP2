#ifndef __RESOURCE_H
#define __RESOURCE_H
#include <string>
#include <unordered_map>

#include "blocking_queue.h"
#include "config.h"

/* Tipo de dato del id. */
typedef int ResourceId;
/* Asociacion de cada ID a su nombre. */
#define NAMES_BY_ID                                                   \
    {                                                                 \
        {ID_WHEAT, NM_WHEAT}, {ID_WOOD, NM_WOOD}, {ID_IRON, NM_IRON}, \
            {ID_COAL, NM_COAL}, {                                     \
            ID_EMPTY, NM_EMPTY                                        \
        }                                                             \
    }

class Resource {
   private:
    ResourceId id;
    static std::unordered_map<ResourceId, std::string> resource_names;

   public:
    /* Constructor por id */
    explicit Resource(ResourceId id);

    /* Constructor por copia */
    Resource(const Resource& other);

    /* Constructor por movimiento */
    Resource(Resource&& other);

    /* Devuelve el nombre del recurso con el id indicado. Metodo estatico*/
    static std::string get_name_by_id(const ResourceId id);

    /* Devuelve el nombre del recurso. */
    std::string get_name();

    /* Devuelve el id del recurso. */
    ResourceId get_id();

    /* El = es como el constructor por copia. */
    Resource operator=(const Resource& other);

    bool operator==(const Resource& other) const;

    bool operator!=(const Resource& other) const;
};

/* Typedef para la blocking queue de recursos. */
typedef BlockingQueue<Resource> ResourceQueue;

#endif
