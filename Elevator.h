#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "ControlPanel.h"
#include"Manager.h"
#include <string>
#include <iostream>

enum State {
    NONE = 0,
    DOWN,
    WAIT,
    UP,
    OPENDOOR,
    CLOSEDOOR
};

class Elevator : public ControlPanel {
public:
    Elevator(const std::string& nameElevator, unsigned short capacity);

    void move(unsigned short targetFloor);
    bool checkWeight(unsigned short people) const;
    void addPeople(unsigned short people);
    void removePeople(unsigned short people);
    bool checkDoor();
    void action();
    void handleDoorAction(const std::string& message, State doorState);
    unsigned short getCurrentPeopleCount() const;
    unsigned short getCurrentFloor() const;
    unsigned short getCapacity() const;
    unsigned short getTarget() const;
    State getState() const;

    void master() const;

    friend std::ostream& operator<<(std::ostream& out, const Elevator& elevator);

private:
    unsigned short _currentFloor;
    unsigned short _targetFloor;
    unsigned short _bufferFloor;
    unsigned short _capacity;
    unsigned short _currentPeopleCount;
    std::string _elevatorName;
    std::unique_ptr<Manager> _manager;
    State _state;

    std::string printStatusLift() const;
    std::string printStatusPanel() const;
    void setState(State newState);
};

#endif // ELEVATOR_H
