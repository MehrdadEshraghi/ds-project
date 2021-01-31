#include <iostream>
#include "Map.h"
#include "Soldier.h"
#include "Castle.h"
#include "FibonacciHeap.h"

using namespace std;

int main()
{
    int numberOfCastles, arr[400][400], outputCapacityOfCastles, soldiersSpeed, numberOfSoldiers, soldiers[400];
    cout << "Enter The Number Of Castles My Lord:" << endl;
    cin >> numberOfCastles;
    cout << "Enter The Graph Of The Kingdom My Lord:" << endl;
    for(int i = 0; i < numberOfCastles; i++)
        for(int j = 0; j < numberOfCastles; j++)
            cin >> arr[i][j];
    Map m(arr, numberOfCastles);
    cout << "Enter The Output Capacity Of Castles Your Lordship:" << endl;
    cin >> outputCapacityOfCastles;
    Castle::setOutputCapacityOfCastles(outputCapacityOfCastles);
    cout << "Enter The Speed Of Soldiers My Lord:" << endl;
    cin >> soldiersSpeed;
    Soldier::setSoldiersSpeed(soldiersSpeed);
    for(int i = 0; i < numberOfCastles; i++) {
        cout << "Enter The Number Of Soldiers For Castle " << i << " My Lord:" << endl;
        cin >> numberOfSoldiers;
        cout << "Enter The Strength Of Each Soldier: " << endl;
        for(int j = 0; j < numberOfSoldiers; j++) {
            cin >> soldiers[j];
        }
        m.setSoldiers(soldiers, numberOfSoldiers, i);
    }

    return 0;
}
