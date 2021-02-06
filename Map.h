#pragma once
#include "Castle.h"
#include "Vector.h"
#include "Queue.h"

class Map {
    int numberOfCastles;
    int outputCapacityOfCastles;
    Castle* castles[400];
    int graph[400][400];
public:
    Map() {};

    ~Map() {
        delete[] castles;
    }

    Map(int arr[][400], int _numberOfCastles) {
        this->numberOfCastles = _numberOfCastles;
        for(int i = 0; i < numberOfCastles; i++)
            for(int j = 0; j < numberOfCastles; j++)
                this->graph[i][j] = arr[i][j];
        for(int i = 0; i < numberOfCastles; i++)
            castles[i] = new Castle(arr[i], numberOfCastles, i);
    }

    void setSoldiers(int _soldiersStrength[], int _numberOfSoldiers, int index) {
        this->castles[index]->setSoldiers(_soldiersStrength, _numberOfSoldiers);
    }

    void progress() {
        for(int i = 0; i < numberOfCastles; i++)
            castles[i]->updateDeathHall();
        prepareArmies();
        moveSoldiers();
        for(int i = 0; i < numberOfCastles; i++)
            castles[i]->updateInputCapacityOfCastle();
        attack();
        showInfo();
    }

    int calcTotalDistance(int i) {
        int result = 0;
        for(int j = 0; j < numberOfCastles; j++)
            if(castles[i]->distances[j] > 0)
                result += castles[j]->numberOfSoldiers;
        return result;
    }

    void prepareArmies() {
        int i, j;
        for( i = 0; i < numberOfCastles; i++) {
            int totalSoldiers = calcTotalDistance(i);
            int sentSoldiers = 0;
            for( j = 0; j < numberOfCastles; j++) {
                if(castles[i]->distances[j] > 0) {
                    int sizeOfArmy = (outputCapacityOfCastles * castles[j]->numberOfSoldiersInTheCastle) / totalSoldiers;
                    for(int k = 0; k < sizeOfArmy; k++) {
                        Soldier* s = this->castles[i]->nationalGuard.pullSoldier();
                        if(s == NULL) break;
                        else {
                            s->setDistance(castles[i]->distances[j]);
                            sentSoldiers++;
                            castles[j]->soldiersAttacking.push_back(s);
                        }
                    }
                }
            }
            int temp = outputCapacityOfCastles - sentSoldiers;
            if(temp != 0) {
                int castleIndex = this->castleWithMinSoldiers(i);
                for(int l = 0; l < temp; l++) {
                    Soldier* s = this->castles[i]->nationalGuard.pullSoldier();
                    if(s == NULL) break;
                    sentSoldiers++;
                    castles[castleIndex]->soldiersAttacking.push_back(s);
                }
            }
        }

    }

    void moveSoldiers() {
        for(int i = 0; i < numberOfCastles; i++)
            for(int j = 0; j < castles[i]->soldiersAttacking.size(); j++)
                castles[i]->soldiersAttacking[j]->updateDistance();
    }

    void attack() {
        for(int i = 0; i < numberOfCastles; i++) {
            castles[i]->defence();
        }
    }

    int castleWithMinSoldiers(int i) {
        int result = INT_MAX;
        for(int j = 0; j < castles[i]->numberOfSoldiers; j++)
            if(castles[i]->distances[j] > 0 && castles[j]->numberOfSoldiersInTheCastle < result)
                result = j;
        return result;
    }

    void printAVLInfo() {
        for(int i = 0; i < numberOfCastles; i++) {
            castles[i]->nationalGuard.display();
            cout << endl;
            cout << endl;
            cout << endl;
        }
    }

    void printQueues() {
        for(int i = 0; i < numberOfCastles; i++) {
            cout << "Soldiers Attacking Castle " << i << " :" << endl;
            for(int j = 0; j < castles[i]->soldiersAttacking.size(); j++) {
                cout << castles[i]->soldiersAttacking[j]->getStrength() << "  ";
            }
            cout << endl;
        }

    }

    void setOutputCapacityOfCastles(int _outputCapacityOfCastles) {
        this->outputCapacityOfCastles = _outputCapacityOfCastles;
    }

    void showInfo() {
        printAVLInfo();
        printQueues();
    }
};
