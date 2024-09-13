#include "Manager.h"

unsigned int Manager::_id = 1;  

Manager::Manager(const std::string& name) : _name(name) {
    _id++;
}

const std::string& Manager::getName() const
{
    return _name;
}



void Manager::work() {
    std::cout << std::endl<< "Name: " << _name << std::endl << "Started working on the elevator...wait" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    free();

}

void Manager::free() {
    std::cout << std::endl << "Name: " << _name << std::endl << "Finished working on the elevator..." << std::endl;
}