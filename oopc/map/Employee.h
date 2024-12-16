#pragma once

#include <iostream>
#include <string>

class Employee{
public:
    std::string name;														
    std::string position;													
    unsigned int age;						

    Employee(std::string name, std::string position, unsigned int age);
    Employee();
};

std::ostream& operator<<(std::ostream& os, const Employee& employee);