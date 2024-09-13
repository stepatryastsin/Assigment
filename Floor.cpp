#include "Floor.h"

unsigned short Floor::_people = 0;

Floor::Floor() : _floor(0) {}

void Floor::call(unsigned short floor) {
    _floor = floor;
}

void Floor::addPeople(unsigned short people) {
    _people = people;
}

unsigned short Floor::getFloor() const {
    return _floor;
}

unsigned short Floor::getPeople() const {
    return _people;
}
