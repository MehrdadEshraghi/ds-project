#pragma once
#include <cmath>
#include "Stack.h"
#include "AVLTree.h"
#include "Queue.h"
#include "Soldier.h"
#include "Vector.h"
#include <vector>

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
    vector<Soldier*> soldiersAttacking;
    vector<Soldier*> attackers;
    Stack<Soldier*> deathHall;
public:
    Castle(int _distances[], int _numberOfCastles, int _castleID):deathHall(_castleID) {
        this->castleID = _castleID;
        this->owner = _castleID;
        for(int i = 0; i < _numberOfCastles; i++)
            this->distances[i] = _distances[i];
    };

//    ~Castle() {
//        delete armies;
//    }

    void setSoldiers(int _soldiers[], int _numberOfSoldiers) {
        this->numberOfSoldiers = _numberOfSoldiers;
        this->numberOfSoldiersInTheCastle = _numberOfSoldiers;
        for(int i = 0; i < _numberOfSoldiers; i++)
            nationalGuard.insert(new Soldier(_soldiers[i], this->castleID));
    }

    static void setOutputCapacityOfCastles(int _outputCapacityOfCastles) {
        outputCapacityOfCastles = _outputCapacityOfCastles;
    }

    static int getOutputCapacityOfCastles() {
        return outputCapacityOfCastles;
    }

    int updateInputCapacityOfCastle() {
        int temp = 0;
        for(int i = 0; i < soldiersAttacking.size(); i++)
            if(soldiersAttacking[i]->getDistance() == 0)
                temp ++;
        float cal = temp / numberOfSoldiersInTheCastle;
        this->inputCapacityOfCastle = ceilf(cal);
    }

    void updateDeathHall() {
        Soldier* recoveredSoldier = deathHall.updateRecoveredSoldiers(this->owner);
        if(recoveredSoldier) {
            numberOfSoldiersInTheCastle++;
            nationalGuard.insert(recoveredSoldier);
        }
    }

    void defence() {
        int counter = 0;
        while(counter != inputCapacityOfCastle) {
            for(int i = 0; i < soldiersAttacking.size(); i++) {
                if(soldiersAttacking[i]->getDistance() <= 0) {
                    this->attackers.push_back(soldiersAttacking[i]);
                    soldiersAttacking.erase(soldiersAttacking.begin() + i);
                    counter++;
                }
            }
        }

        for(int i = 0; i < attackers.size(); i++) {
            if(attackers[i]->getCastleNum() == this->owner) {
                nationalGuard.insert(attackers[i]);
                soldiersAttacking.erase(soldiersAttacking.begin() + i);
            }
        }



    }
};

int Castle::outputCapacityOfCastles = 0;
