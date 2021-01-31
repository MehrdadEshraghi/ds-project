#pragma once

class Soldier {
    static int soldiersSpeed;
    int strength;
    int castleNum;
public:
    Soldier() {};

    Soldier(int _strength, int _castleNum) {
        this->strength = _strength;
        this->castleNum = _castleNum;
    };

    static void setSoldiersSpeed(int _speed) {
        soldiersSpeed = _speed;
    }
};

int Soldier::soldiersSpeed = 0;
