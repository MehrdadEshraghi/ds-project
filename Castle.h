#pragma once
#include "Stack.h"
#include "Queue.h"


class Castle {
    friend class Map;
    int numberOfSoldiers;
    int* distances;
public:
    Castle() {};
    Castle(int* _distances) {
        this->distances = _distances;
    };
};
