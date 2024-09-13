#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>


class Manager {
public:
    Manager(const std::string& name);
    const std::string& getName() const;
    void work();
    void free();

private:
    static unsigned int _id;
    std::string _name;
};

#endif // !MANAGER_H