#include "Employee.h"

Employee::Employee(std::string name, std::string position, unsigned int age) : name(name), position(position), age(age) {}
Employee::Employee() : name(""), position(""), age(0) {}

std::ostream& operator<<(std::ostream& os, const Employee& employee){
    os << employee.name << " (" << employee.position << ", " << employee.age << ")";
    return os;
}