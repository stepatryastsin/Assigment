#include <memory>
#include <iostream>
#include <string>
#include <limits>
#include "Elevator.h"
#include "Floor.h"

class Start {
public:
    void simulation() const;
private:
    // Simulation modes
    void freeMode() const;
    void taskMode() const;

    // Core process methods
    void elevatorProcess(std::unique_ptr<Elevator>& elevator, std::unique_ptr<Floor>& floor) const;

    // Utility methods
    int getValidatedInput(const std::string& prompt, int min, int max) const;
    std::string getCommand() const;

    // Helper for task simulation
    void simulatePassenger(Elevator& elevator, Floor& floorControl, int startFloor, int targetFloor) const;
};

// Main function
int main() {
    Start app;
    app.simulation();
    return 0;
}

void Start::freeMode() const {
    auto elevator = std::make_unique<Elevator>("Big Elevator", 5);
    auto floor = std::make_unique<Floor>();

    elevatorProcess(elevator, floor);
}

void Start::taskMode() const {
    // Task setup: two elevators
    Elevator elevator1("Elevator 1", 5); // 5 people capacity
    Elevator elevator2("Elevator 2", 10); // 10 people capacity
    Floor floorControl;

    // Simulate Passenger 1 (calls elevator on floor 1, goes to floor 14)
    simulatePassenger(elevator1, floorControl, 1, 14);

    // Simulate Passenger 2 (calls elevator on floor 15, goes to floor 1)
    simulatePassenger(elevator2, floorControl, 15, 1);
}

void Start::simulation() const {
    int choice = getValidatedInput("Choose simulation: (1) Free Mode / (2) Task Mode: ", 1, 2);
    switch (choice) {
    case 1:
        freeMode();
        break;
    case 2:
        taskMode();
        break;
    default:
        std::cout << "Incorrect input" << std::endl;
        break;
    }
}

void Start::elevatorProcess(std::unique_ptr<Elevator>& elevator, std::unique_ptr<Floor>& floor) const {
    while (true) {
        int currentFloor = getValidatedInput("Enter floor (1 - 20): ", 1, 20);
        floor->call(currentFloor);
        elevator->move(floor->getFloor());

        int peopleOnFloor = getValidatedInput("How many people on the floor (1 - 5): ", 1, 5);

        while (!elevator->checkWeight(peopleOnFloor)) {
            std::cout << "The elevator can't carry this many people!" << std::endl;
            peopleOnFloor = getValidatedInput("Enter the number of people entering the elevator (1 - 5): ", 1, 5);
        }

        floor->addPeople(peopleOnFloor);
        elevator->addPeople(peopleOnFloor);

        std::string command;
        while (elevator->getCurrentPeopleCount() > 0) {
            command = getCommand();
            if (!elevator->pressButton(command)) {
                std::cout << "Error pressing button." << std::endl;
            }

            elevator->action();

            if (elevator->getState() == State::OPENDOOR) {
                int peopleOut = getValidatedInput("How many people will leave the elevator (1 - " + std::to_string(elevator->getCurrentPeopleCount()) + "): ", 0, elevator->getCurrentPeopleCount());
                elevator->removePeople(peopleOut);
            }
        }
    }
}

int Start::getValidatedInput(const std::string& prompt, int min, int max) const {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value < min || value > max) {
            std::cout << "Invalid input! Please enter a number between " << min << " and " << max << "." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    return value;
}

std::string Start::getCommand() const {
    std::string command;
    while (true) {
        std::cout << "Enter floor (1 - 20) or service button (D, O, C): ";
        std::cin >> command;

        if (std::isdigit(command[0])) {
            int floor = std::stoi(command);
            if (floor >= 1 && floor <= 20) {
                return command;
            }
        }
        else if (command == "D" || command == "O" || command == "C") {
            return command;
        }

        std::cout << "Invalid input! Please enter a floor (1 - 20) or one of the buttons (D, O, C)." << std::endl;
    }
}

// Simulates an individual passenger calling and using an elevator
void Start::simulatePassenger(Elevator& elevator, Floor& floorControl, int startFloor, int targetFloor) const {
    std::cout << "Passenger calls elevator at floor " << startFloor << " to go to floor " << targetFloor << "." << std::endl;
    floorControl.call(startFloor);
    elevator.move(startFloor);
    elevator.addPeople(1);
    elevator.pressButton(std::to_string(targetFloor));
    elevator.action();
}