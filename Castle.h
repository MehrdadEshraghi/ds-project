#pragma once
#include "Stack.h"
#include "AVLTree.h"
#include "Queue.h"
#include "Soldier.h"
#include <cmath>

class Castle {
    friend class Map;
    static int outputCapacityOfCastles;
    int numberOfSoldiers;
    int numberOfSoldiersInTheCastle;
    int inputCapacityOfCastle;
    int castleID;
    int owner;
    AVLTree nationalGuard;
    int distances[400];
    Soldier* soldiersInTheCastle[400];
    Queue<Queue<Soldier*>>* armies;
    Stack<Soldier*> deathHall;
public:
//    Castle() {};

    Castle(int _distances[], int _numberOfCastles, int _castleID):deathHall(_castleID) {
        this->castleID = _castleID;
        this->owner = _castleID;
        for(int i = 0; i < _numberOfCastles; i++)
            this->distances[i] = _distances[i];
    };

    ~Castle() {
        delete[] soldiersInTheCastle;
        delete armies;
    }

    void setSoldiers(int _soldiers[], int _numberOfSoldiers) {
        this->numberOfSoldiers = _numberOfSoldiers;
        for(int i = 0; i < _numberOfSoldiers; i++)
            this->soldiersInTheCastle[i] = new Soldier(_soldiers[i], this->castleID);
    }

    static void setOutputCapacityOfCastles(int _outputCapacityOfCastles) {
        outputCapacityOfCastles = _outputCapacityOfCastles;
    }

    int updateInputCapacityOfCastle() {
        int temp;
        for(int i = 0; i < armies->queueSize(); i++)
            if(armies[i].getDistance() == 0)
                temp += armies[i].queueSize();
        int arrSize = sizeof(soldiersInTheCastle)/sizeof(soldiersInTheCastle[0]);
        float cal = temp / arrSize;
        this->inputCapacityOfCastle = ceilf(cal);
    }

    void updateDeathHall() {
        Soldier* recoveredSoldier = deathHall.updateRecoveredSoldiers(this->owner);
        if(recoveredSoldier) {
            soldiersInTheCastle[numberOfSoldiersInTheCastle] = recoveredSoldier;
            numberOfSoldiersInTheCastle++;
        }
    }
};

int Castle::outputCapacityOfCastles = 0;
