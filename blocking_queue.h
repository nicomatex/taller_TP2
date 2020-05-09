#ifndef __BLOCKING_QUEUE_H
#define __BLOCKING_QUEUE_H

/* Includes */
#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>

/* Interfaz */
template <class T>
class BlockingQueue {
 private:
  bool isClosed;
  std::mutex m;
  std::queue<T> queue;
  std::condition_variable cv;

  // Este objeto solo sera devuelto cuando la cola este cerrada y vacia.
  T empty_return;

 public:
  /*Constructor y destructor*/
  BlockingQueue(T empty_return) : isClosed(false), empty_return(empty_return) {}
  ~BlockingQueue(){};

  T pop() {
    std::unique_lock<std::mutex> lk(m);

    while (queue.empty()) {  // Para prevenir spurious wakeups
      if (isClosed) {
        // Devuelve el objeto especial empty_return
        return empty_return;
      }
      cv.wait(lk);
    }

    T t = queue.front();
    queue.pop();
    return t;
  }

  void push(T t) {
    std::unique_lock<std::mutex> lk(m);
    queue.push(t);
    cv.notify_all();
  }

  void close() {
    std::unique_lock<std::mutex> lk(m);
    isClosed = true;
    cv.notify_all();
  }
};

#endif