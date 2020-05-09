/* Includes */
#include <vector>

#include "gatherer.h"
#include "inventory.h"
#include "map_parser.h"
#include "point_container.h"
#include "producer.h"

/* Interfaz */

class Engine {
 private:
  BlockingQueue<Resource> lumberjack_queue;
  BlockingQueue<Resource> miner_queue;
  BlockingQueue<Resource> farmer_queue;

  Inventory inventory;
  MapParser map_parser;

  std::vector<Gatherer*> gatherers;
  std::vector<Producer*> producers;

  PointContainer point_container;

 public:
  /* El constructor recibe una cadena hacia el archivo de mapa.*/
  Engine(const std::string map_file);
  ~Engine();

  /* "Spawnea" y pone a trabajar a los recolectores. */
  void spawn_gatherers(int farmers, int miners, int lumberjacks);

  /* "Spawnea" y pone a trabajar a los productores. */
  void spawn_producers(int cooks, int carpenters, int smiths);

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
};