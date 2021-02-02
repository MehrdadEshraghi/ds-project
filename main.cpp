#include <iostream>
#include "Map.h"
#include "Soldier.h"
#include "Castle.h"
#include "Stack.h"

using namespace std;

int main()
{
    int numberOfCastles, arr[400][400], outputCapacityOfCastles, soldiersSpeed, numberOfSoldiers, soldiers[400];
    float soldiersRecovery;
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
    cout << "Enter The Number Soldiers Which Will Be Recovered In Each Iteration:" << endl;
    cin >> soldiersRecovery;
    Stack<Soldier>::setSoldiersRecovery(soldiersRecovery);
    for(int i = 0; i < numberOfCastles; i++) {
        cout << "Enter The Number Of Soldiers For Castle " << i << " My Lord:" << endl;
        cin >> numberOfSoldiers;
        cout << "Enter The Strength Of Each Soldier: " << endl;
        for(int j = 0; j < numberOfSoldiers; j++) {
            cin >> soldiers[j];
        }
        m.setSoldiers(soldiers, numberOfSoldiers, i);
    }

    int iteration;
    int totalIterations = 0;
    while(1) {
        cout << "How Many Iterations Should The Game Progress:" << endl;
        cin >> iteration;
        cout << endl;
        totalIterations += iteration;
        for(int i = 0; i < iteration; i++) {
            m.progress();
        }
    }

    return 0;
}
