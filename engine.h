/* Includes */
#include <string>
#include <vector>

#include "cfg_parser.h"
#include "gatherer.h"
#include "inventory.h"
#include "map_parser.h"
#include "point_container.h"
#include "producer.h"

/* Interfaz */

class Engine {
   private:
    ResourceQueue lumberjack_queue;
    ResourceQueue miner_queue;
    ResourceQueue farmer_queue;

    Inventory inventory;
    MapParser map_parser;
    ConfigParser config_parser;

    std::vector<Gatherer *> gatherers;
    std::vector<Producer *> producers;

    PointContainer point_container;

   public:
    /* El constructor recibe una cadena hacia el archivo de mapa.*/
    Engine(const std::string map_file, const std::string config_file);
    ~Engine();

    /* "Spawnea" y pone a trabajar a los recolectores. */
    void spawn_gatherers(WorkerList &worker_list);

    /* "Spawnea" y pone a trabajar a los productores. */
    void spawn_producers(WorkerList &worker_list);

    /* "Spawnea" a todos los trabajadores: Recolectores y productores.*/
    void spawn_workers();

    /* Parsea el archivo de mapa y pone los recursos
    a disponibilidad de los recolectores.*/
    void spawn_resources();

    /* Cierra el inventario e impide que se agreguen nuevos
    recursos. Debe llamarse cuando todos los recolectores hayan terminado
    su labor. */
    void close_inventory();

    /* Espera que los recolectores terminen de recolectar los recursos. */
    void join_gatherers();

    /* Espera a que los productores terminen de producir puntos. */
    void join_producers();

    /* Devuelve los puntos acumulados. */
    unsigned int get_points();

    /* Imprime por stdout una lista de los recursos
    disponibles en el inventario. */
    void print_resources_left();

    /* Imprime por stdout un mensaje que indica la cantidad de
    puntos de beneficio acumulados. */
    void print_benefit_points();

    /* No se permite construccion por copia ni por movimiento.*/
    Engine(const Engine &other) = delete;
    Engine(Engine &&other) = delete;
};
