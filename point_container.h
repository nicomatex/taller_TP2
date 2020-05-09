#ifndef __POINT_CONTAINER_H
#define __POINT_CONTAINER_H

/* Includes */
#include <mutex>

/* Interfaz */

class PointContainer {
 private:
  std::mutex m;
  unsigned int points;

 public:
  PointContainer();
  ~PointContainer();

  /* Agrega puntos al contenedor de puntos*/
  void add_points(unsigned int amount);

  /* Devuelve la cantidad de puntos acumulada*/
  unsigned int get_points();
};

#endif