#pragma once
#include "Castle.h"
#include "Vector.h"

class Map {
    int numberOfCastles;
    int outputCapacityOfCastles;
    Castle* castles[400];
    int graph[400][400];
public:
    Map() {};

    Map(int arr[][400], int _numberOfCastles) {
        this->numberOfCastles = _numberOfCastles;
        for(int i = 0; i < numberOfCastles; i++)
            for(int j = 0; j < numberOfCastles; j++)
                this->graph[i][j] = arr[i][j];
        for(int i = 0; i < numberOfCastles; i++)
            castles[i] = new Castle(arr[i], numberOfCastles, i);
    }

    setSoldiers(int _soldiersStrength[], int _numberOfSoldiers, int index) {
        this->castles[index]->setSoldiers(_soldiersStrength, _numberOfSoldiers);
    }
};
