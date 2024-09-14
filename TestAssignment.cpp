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


    void elevatorProcess(std::unique_ptr<Elevator>& elevator1, std::unique_ptr<Elevator>& elevator2, std::unique_ptr<Floor>& floor) const;

  
    int getValidatedInput(const std::string& prompt, int min, int max) const;
    std::string getCommand() const;


    void simulatePassenger(Elevator& elevator, Floor& floorControl, int startFloor, int targetFloor) const;
};


int main() {
    Start app;
    app.simulation();
    return 0;
}

void Start::freeMode() const {
    auto elevator2 = std::make_unique<Elevator>("Big", 10);
    auto elevator1 = std::make_unique<Elevator>("Small", 5);
    auto floor = std::make_unique<Floor>();

    elevatorProcess(elevator2, elevator1, floor);
}

void Start::taskMode() const {
   
    Elevator elevator1("Elevator 1", 5);
    Elevator elevator2("Elevator 2", 10); 
    Floor floorControl;

    
    simulatePassenger(elevator1, floorControl, 1, 14);

    simulatePassenger(elevator2, floorControl, 15, 1);

    std::cout<< std::endl;

    std::cout << "Test assigment was success" << std::endl;
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

void Start::elevatorProcess(std::unique_ptr<Elevator>& elevator1, std::unique_ptr<Elevator>& elevator2, std::unique_ptr<Floor>& floor) const {
    while (true) {

        int currentFloor = getValidatedInput("Enter floor (1 - 20): ", 1, 20);

 
        Elevator* chosenElevator = nullptr;
        if (abs(elevator1->getCurrentFloor() - currentFloor) < abs(elevator2->getCurrentFloor() - currentFloor)) {
            chosenElevator = elevator1.get();  
        }
        else {
            chosenElevator = elevator2.get();  
        }

        floor->call(currentFloor);
        chosenElevator->move(floor->getFloor());

        int peopleOnFloor = getValidatedInput("How many people on the floor (1 - 5): ", 1, 5);


        while (!chosenElevator->checkWeight(peopleOnFloor)) {
            std::cout << "The elevator can't carry this many people!" << std::endl;
            peopleOnFloor = getValidatedInput("Enter the number of people entering the elevator (1 - 5): ", 1, 5);
        }

        floor->addPeople(peopleOnFloor);
        chosenElevator->addPeople(peopleOnFloor);

        std::string command;
        while (chosenElevator->getCurrentPeopleCount() > 0) {
            command = getCommand();
            if (!chosenElevator->pressButton(command)) {
                std::cout << "Error pressing button." << std::endl;
            }

            chosenElevator->action();

            if (chosenElevator->checkDoor()) {
                int peopleOut = getValidatedInput("How many people will leave the elevator (1 - " + std::to_string(chosenElevator->getCurrentPeopleCount()) + "): ", 0, chosenElevator->getCurrentPeopleCount());
                chosenElevator->removePeople(peopleOut);
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


void Start::simulatePassenger(Elevator& elevator, Floor& floorControl, int startFloor, int targetFloor) const {
    std::cout << "Passenger calls elevator at floor " << startFloor << " to go to floor " << targetFloor << "." << std::endl;
    floorControl.call(startFloor);
    elevator.move(startFloor);
    elevator.addPeople(1);
    elevator.pressButton(std::to_string(targetFloor));
    elevator.action();
    elevator.removePeople(1);
}