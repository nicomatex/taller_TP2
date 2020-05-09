#ifndef __PRODUCER_H
#define __PRODUCER_H

/* Includes */
#include <unordered_map>

#include "inventory.h"
#include "point_container.h"
#include "thread.h"

/* Constantes */
#define PRODUCE_TIME 60000

/* Interfaz */
class Producer : public Thread {
 private:
  Inventory &inventory;
  std::unordered_map<Resource, unsigned int> request;
  unsigned int puntos_generados;  // debug
  unsigned int benefit_generation;
  PointContainer &point_container;

 public:
  Producer(
      Inventory &inventory,
      std::initializer_list<std::pair<const Resource, unsigned int>> request,
      unsigned int benefit_generation, PointContainer &point_container);
  virtual void run() override;
};

#endif