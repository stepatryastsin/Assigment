#ifndef FLOOR_H
#define FLOOR_H

#include "Elevator.h"

class Floor {
public:
    Floor();

    void call(unsigned short floor);
    void addPeople(unsigned short people);

    unsigned short getFloor() const;
    unsigned short getPeople() const;
private:
    unsigned short _floor;
    static unsigned short _people;
};

#endif // FLOOR_H