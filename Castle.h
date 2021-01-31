#pragma once
#include "Stack.h"
#include "AVLTree.h"
#include "Queue.h"
#include "Soldier.h"

class Castle {
    friend class Map;
    static int outputCapacityOfCastles;
    int numberOfSoldiers;
    int castleID;
    int distances[400];
    Soldier* soldiersInTheCastle[400];
    Queue<Soldier*> armies[400];
public:
    Castle() {};

    Castle(int _distances[], int _numberOfCastles, int _castleID) {
        this->castleID = _castleID;
        for(int i = 0; i < _numberOfCastles; i++)
            this->distances[i] = _distances[i];
    };

    setSoldiers(int _soldiers[], int _numberOfSoldiers) {
        this->numberOfSoldiers = _numberOfSoldiers;
        for(int i = 0; i < _numberOfSoldiers; i++)
            this->soldiersInTheCastle[i] = new Soldier(_soldiers[i], this->castleID);
    }

    static void setOutputCapacityOfCastles(int _outputCapacityOfCastles) {
        outputCapacityOfCastles = _outputCapacityOfCastles;
    }
};

int Castle::outputCapacityOfCastles = 0;
