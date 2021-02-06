#pragma once

class Soldier {
    static int soldiersSpeed;
    int strength;
    int castleNum;
    int distance;
public:
    Soldier() {};

    Soldier(int _strength, int _castleNum) {
        this->strength = _strength;
        this->castleNum = _castleNum;
    };

    Soldier(int _strength, int _castleNum, int _distance) {
        this->strength = _strength;
        this->castleNum = _castleNum;
        this->distance = _distance;
    };

    int getStrength() const {
        return this->strength;
    }

    int getCastleNum() const {
        return this->castleNum;
    }

    static void setSoldiersSpeed(int _speed) {
        soldiersSpeed = _speed;
    }

    void setDistance(int _distance) {
        this->distance = _distance;
    }

    int getDistance() const {
        return this->distance;
    }

    void updateDistance() {
        if(this->distance - soldiersSpeed <= 0)
            this->distance = 0;
        else
            this->distance -= soldiersSpeed;
    }
};

int Soldier::soldiersSpeed = 0;
