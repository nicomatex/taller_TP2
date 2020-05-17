#include "PointContainer.h"

PointContainer::PointContainer() : points(0) {}

PointContainer::~PointContainer() {}

void PointContainer::add_points(unsigned int amount) {
    std::unique_lock<std::mutex> lk(m);
    points += amount;
}

unsigned int PointContainer::get_points() { return points; }
