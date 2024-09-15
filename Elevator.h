#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "ControlPanel.h"
#include "Manager.h"
#include <string>
#include <iostream>

enum State {
    NONE = 0,    // No active state
    DOWN,        // Elevator moving down
    WAIT,        // Elevator is idle
    UP,          // Elevator moving up
    OPENDOOR,    // Elevator doors open
    CLOSEDOOR    // Elevator doors close
};

class Elevator : public ControlPanel {
public:
    // Constructor initializes elevator name and capacity. Defaults current and target floors to 1, and state to WAIT.
    Elevator(const std::string& nameElevator, unsigned short capacity);

    // Moves elevator to the target floor.
    void move(unsigned short targetFloor);

    // Checks if the elevator can hold additional people.
    bool checkWeight(unsigned short people) const;

    // Adds people to the elevator.
    void addPeople(unsigned short people);

    // Removes people from the elevator.
    void removePeople(unsigned short people);

    // Checks if the door is currently open.
    bool checkDoor();

    // Handles the main actions of the elevator like moving, opening doors, etc.
    void action();

    // Handles door-related actions (open/close) and updates the state accordingly.
    void handleDoorAction(const std::string& message, const State& doorState);

    // Getter for current people count inside the elevator.
    unsigned short getCurrentPeopleCount() const;

    // Getter for current floor of the elevator.
    unsigned short getCurrentFloor() const;

    // Getter for the elevator capacity.
    unsigned short getCapacity() const;

    // Getter for the target floor of the elevator.
    unsigned short getTarget() const;

    // Getter for the current state of the elevator.
    State getState() const;

    // Calls the Manager class to handle dispatcher-related actions.
    void master() const;

    // Overloaded << operator to print elevator status.
    friend std::ostream& operator<<(std::ostream& out, const Elevator& elevator);

private:
    unsigned short _currentFloor;       // Current floor where the elevator is.
    unsigned short _targetFloor;        // Target floor for the elevator to move to.
    unsigned short _bufferFloor;        // Temporary storage of target floor during movement.
    unsigned short _capacity;           // Maximum capacity of the elevator.
    unsigned short _currentPeopleCount; // Current number of people in the elevator.
    std::string _elevatorName;          // Name of the elevator.
    std::unique_ptr<Manager> _manager;  // Pointer to the Manager object (handles dispatcher).
    State _state;                       // Current state of the elevator (e.g., UP, DOWN, OPENDOOR).

    // Prints the status of the lift (moving direction, door state).
    std::string printStatusLift() const;

    // Prints the status of the control panel (pressed buttons).
    std::string printStatusPanel() const;

    // Updates the state of the elevator.
    void setState(State newState);
};

#endif // ELEVATOR_H