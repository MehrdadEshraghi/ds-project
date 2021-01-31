#include <iostream>
#include "Map.h"
#include "Soldier.h"
#include "Castle.h"
#include "FibonacciHeap.h"
#include "AVLTree.h"

using namespace std;

int main()
{
    BST t;
    Soldier* a = new Soldier(5, 3);
    Soldier* b = new Soldier(7, 3);
    Soldier* c = new Soldier(99, 2);
    Soldier* d = new Soldier(2, 3);
    Soldier* e = new Soldier(1, 3);
    Soldier* f = new Soldier(6, 1);
    Soldier* g = new Soldier(9, 3);
    Soldier* h = new Soldier(5, 1);
    Soldier* i = new Soldier(12, 1);
    Soldier* j = new Soldier(8, 1);
    Soldier* k = new Soldier(6, 3);
    Soldier* l = new Soldier(10, 3);
    t.insert(a);

    t.insert(b);

    t.insert(c);
    t.insert(d);
    t.insert(e);
    t.insert(f);

    t.insert(g);
    t.insert(h);
    t.insert(i);

    t.insert(j);

    t.insert(k);

    t.insert(l);

    t.display();
    t.remove(a);

    t.remove(b);

    t.remove(f);
                                                    cout << "salam" << endl;

    t.remove(b);

    t.remove(i);
    t.remove(k);

    t.display();

//    int numberOfCastles, arr[400][400], outputCapacityOfCastles, soldiersSpeed, numberOfSoldiers, soldiers[400];
//    cout << "Enter The Number Of Castles My Lord:" << endl;
//    cin >> numberOfCastles;
//    cout << "Enter The Graph Of The Kingdom My Lord:" << endl;
//    for(int i = 0; i < numberOfCastles; i++)
//        for(int j = 0; j < numberOfCastles; j++)
//            cin >> arr[i][j];
//    Map m(arr, numberOfCastles);
//    cout << "Enter The Output Capacity Of Castles Your Lordship:" << endl;
//    cin >> outputCapacityOfCastles;
//    Castle::setOutputCapacityOfCastles(outputCapacityOfCastles);
//    cout << "Enter The Speed Of Soldiers My Lord:" << endl;
//    cin >> soldiersSpeed;
//    Soldier::setSoldiersSpeed(soldiersSpeed);
//    for(int i = 0; i < numberOfCastles; i++) {
//        cout << "Enter The Number Of Soldiers For Castle " << i << " My Lord:" << endl;
//        cin >> numberOfSoldiers;
//        cout << "Enter The Strength Of Each Soldier: " << endl;
//        for(int j = 0; j < numberOfSoldiers; j++) {
//            cin >> soldiers[j];
//        }
//        m.setSoldiers(soldiers, numberOfSoldiers, i);
//    }

    return 0;
}
