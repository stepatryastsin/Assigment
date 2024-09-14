#include "Elevator.h"
#include <chrono>
#include <thread>
#include <algorithm>


Elevator::Elevator(const std::string& nameElevator, unsigned short capacity)
    : _elevatorName(nameElevator), _capacity(capacity), _targetFloor(1), _currentFloor(1), _currentPeopleCount(0), _state(State::NONE) {
    _manager = std::make_unique<Manager>("Master Elevator");
}

void Elevator::move(unsigned short targetFloor) {
    if (targetFloor == _currentFloor) {
        std::cout << "Elevator "<< this->_elevatorName <<" already on floor " << _currentFloor << std::endl;
        return;
    }
    while (_currentFloor != targetFloor) {
        if (targetFloor > _currentFloor) {
            ++_currentFloor;
            setState(State::UP);
        }
        else {
            --_currentFloor;
            setState(State::DOWN);
        }

        printStatus();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    setState(State::WAIT);
}

bool Elevator::checkWeight(unsigned short people) const {
    return _capacity >= people + _currentPeopleCount;
}

void Elevator::addPeople(unsigned short people) {
    if (checkWeight(people)) {
        _currentPeopleCount += people;
    }
}

void Elevator::removePeople(unsigned short people) {
    if (_currentPeopleCount >= people) {
        _currentPeopleCount -= people;
    }
}

unsigned short Elevator::getCurrentPeopleCount() const {
    return _currentPeopleCount;
}

unsigned short Elevator::getCurrentFloor() const
{
    return _currentFloor;
}

void Elevator::action() {
    int index = -1;

    // Find the first pressed button
    auto it = std::find_if(getButtons().begin(), getButtons().end(),
        [](const std::pair<bool, std::string>& p) {
            return p.first == true;
        });

    if (it != getButtons().end()) {
        index = std::distance(getButtons().begin(), it);
    }

    // Handle floor buttons
    if (index >= 0 && index < BUTTONFLOOR) {
        move(index + 1);  // Move to the selected floor
        setState(State::WAIT);
        unpressButton(index);
    }
    // Handle service buttons
    else if (index == Button::OPEN) {
        std::cout << "Opening door..." << std::endl;
        setState(State::OPENDOOR);
        unpressButton(index);
    }
    else if (index == Button::CLOSE) {
        std::cout << "Closing door..." << std::endl;
        setState(State::CLOSEDOOR);
        unpressButton(index);
    }
    else if (index == Button::DISPETCHER) {
        std::cout << "Calling dispatcher..." << std::endl;
        master();
        std::cout << std::endl;
        unpressButton(index);
    }
    else {
        std::cout << "No valid button pressed." << std::endl;
    }
}

void Elevator::setState(State newState) {
    _state = newState;
}

unsigned short Elevator::getCapacity() const {
    return _capacity;
}

unsigned short Elevator::getTarget() const {
    return _targetFloor;
}

State Elevator::getState() const {
    return _state;
}

void Elevator::master() const
{
    _manager->work();
}

void Elevator::printStatus() const {
    std::cout << "Elevator " << _elevatorName << ": ";
    switch (_state) {
    case State::UP:
        std::cout << "Moving up, current floor: " << _currentFloor << std::endl;
        break;
    case State::DOWN:
        std::cout << "Moving down, current floor: " << _currentFloor << std::endl;
        break;
    case State::WAIT:
        std::cout << "Waiting on floor " << _currentFloor << std::endl;
        break;
    default:
        break;
    }
}

std::ostream& operator<<(std::ostream& out, const Elevator& curr) {
    out << "Current Floor: " << curr._currentFloor << std::endl;
    out << "Current People: " << curr._currentPeopleCount << std::endl;
    out << "Name Elevator: " << curr._elevatorName << std::endl;
    return out;
}