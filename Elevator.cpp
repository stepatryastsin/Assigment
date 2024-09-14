#include "Elevator.h"
#include <chrono>
#include <thread>
#include <algorithm>
#include <string>
#include <sstream>  // Для работы с потоками в памяти
#include <iomanip>  // Для форматирования

Elevator::Elevator(const std::string& nameElevator, unsigned short capacity)
    : _elevatorName(nameElevator), _capacity(capacity), _targetFloor(1), _currentFloor(1), _currentPeopleCount(0), _state(State::NONE) {
    _manager = std::make_unique<Manager>("Master Elevator");
    _bufferFloor = 0;
}

void Elevator::move(unsigned short targetFloor) {
    _bufferFloor = targetFloor;
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
        std::cout << *this << std::endl;
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

bool Elevator::checkDoor()
{
    return _state == State::OPENDOOR;
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
        setButtonState(Button::NUMBER);
        move(index + 1);  // Move to the selected floor
        setState(State::WAIT);
        unpressButton(index);
        setButtonState(Button::NOTHING);
    }
    // Handle service buttons
    else if (index == Button::OPEN) {
        setButtonState(Button::OPEN);
        std::cout << "Opening door..." << std::endl;
        setState(State::OPENDOOR);
        std::cout << *this << std::endl;
        unpressButton(index);
        setButtonState(Button::NOTHING);
    }
    else if (index == Button::CLOSE) {
        setButtonState(Button::CLOSE);
        std::cout << "Closing door..." << std::endl;
        setState(State::CLOSEDOOR);
        std::cout << *this << std::endl;
        unpressButton(index);
        setButtonState(Button::NOTHING);
    }
    else if (index == Button::DISPETCHER) {
        setButtonState(Button::DISPETCHER);
        std::cout << "Calling dispatcher..." << std::endl;
        std::cout << *this << std::endl;
        master();

        std::cout << std::endl;
        unpressButton(index);
        setButtonState(Button::NOTHING);
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

std::string Elevator::printStatusLift() const {
    switch (_state) {
    case State::UP:
        return "Up";
    case State::DOWN:
        return "Down";
    case State::WAIT:
        return "WAIT";
    case State::OPENDOOR:
        return "DOOR OPEN";
    case State::CLOSEDOOR:
        return "DOOR CLOSE";
    default:
        break;
    }
}

std::string Elevator::printStatusPanel() const
{
    switch (getButton()) {
    case Button::NUMBER:
        return "Press Floor: " + std::to_string(this->_bufferFloor);
    case Button::OPEN:
        return "Press Open";
    case Button::CLOSE:
        return "Press Close";
    case Button::DISPETCHER:
        return "Press Dispetcher";
    case Button::NOTHING:
        return "Nothing";
    default:
        break;
    }
}

std::ostream& operator<<(std::ostream& out, const Elevator& curr) {
    // Собираем текст в строковый поток
    std::ostringstream oss;
    oss << "Current Floor: " << curr._currentFloor << std::endl;
    oss << "Current People: " << curr._currentPeopleCount << std::endl;
    oss << "Name Elevator: " << curr._elevatorName << std::endl;
    oss << "Status Lift: " << curr.printStatusLift() << std::endl;
    oss << "Status Panel: " << curr.printStatusPanel() << std::endl;

    std::string content = oss.str();
    std::istringstream iss(content);
    std::string line;
    size_t maxWidth = 0;
    while (std::getline(iss, line)) {
        if (line.length() > maxWidth) {
            maxWidth = line.length();
        }
    }

    
    std::string border(maxWidth + 4, '*');  
    out << border << std::endl;

   
    std::istringstream iss2(content); 
    while (std::getline(iss2, line)) {
        out << "* " << std::left << std::setw(maxWidth) << line << " *" << std::endl;  
    }

    out << border << std::endl;

    return out;
}
