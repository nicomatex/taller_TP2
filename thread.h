#ifndef __THREAD_H
#define __THREAD_H

/* Includes */
#include <thread>

/* Interfaz */
class Thread {
 private:
  std::thread thread;

 public:
  /*Constructor y destructor*/
  Thread();
  virtual ~Thread();

  /*Los constructores por copia no estan permitidos.*/
  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

  /*Los constructores por movimiento si estan permitidos.*/
  Thread(Thread&& other);
  Thread& operator=(Thread&& other);

  /*Inicia la ejecucion del thread*/
  void start();

  /*Pausa el hilo llamante hasta que este hilo finalice.*/
  void join();

  /*Metodo que debe ser implementado por las clases herederas. Sera
  la funcion que correra en el thread.*/
  virtual void run() = 0;
};
#endif
