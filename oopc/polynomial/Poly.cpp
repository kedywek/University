#include "Poly.h"
#include <map>
#include <cmath>
#include <iostream>

Poly::Poly(){
}
Poly::Poly(double coefficient){
    this->coefficients[0] = coefficient;
}
Poly::~Poly(){
}
double Poly::operator()(double x) const{
    double result = 0;
    for (std::map<int, double>::const_iterator i = coefficients.begin(); i != coefficients.end(); ++i) {
        result += i->second * pow(x, i->first);
    }
    return result;
}
double& Poly::operator[](unsigned int i){
    return coefficients[i];
}
double Poly::operator[](unsigned int i) const{
    std::map<int, double>::const_iterator coefficient = coefficients.find(i);
    if (coefficient != coefficients.end()){
        return coefficient->second;
    }
    else{
        throw std::out_of_range("Index out of range");
    }
}
Poly& Poly::operator+=(const Poly& p) {
    for (std::map<int, double>::const_iterator i = p.coefficients.begin(); i != p.coefficients.end(); ++i) {
        this->coefficients[i->first] += i->second;
    }
    return *this;
}

Poly& Poly::operator-=(const Poly& p) {
    for (std::map<int, double>::const_iterator i = p.coefficients.begin(); i != p.coefficients.end(); ++i) {
        this->coefficients[i->first] -= i->second;
    }
    return *this;
}

Poly& Poly::operator*=(const Poly& p) {
    std::map<int, double> result;
    for (std::map<int, double>::iterator i = this->coefficients.begin(); i != this->coefficients.end(); ++i) {
        for (std::map<int, double>::const_iterator j = p.coefficients.begin(); j != p.coefficients.end(); ++j) {
            result[i->first + j->first] += i->second * j->second;
        }
    }
    this->coefficients = result;
    return *this;
}

Poly operator-(const Poly& p) {
    Poly tmp = Poly(p);
    for (std::map<int, double>::iterator i = tmp.coefficients.begin(); i != tmp.coefficients.end(); ++i) {
        i->second = -i->second;
    }
    return tmp;
}

Poly operator+(const Poly& p1,const Poly& p2) {
    Poly tmp = Poly(p1);
    tmp += p2;
    return tmp;
}

Poly operator-(const Poly& p1,const Poly& p2) {
    Poly tmp = Poly(p1);
    tmp -= p2;
    return tmp;
}

Poly operator*(const Poly& p1,const Poly& p2) {
    Poly tmp = Poly(p1);
    tmp *= p2;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const Poly& p) {
    for (std::map<int, double>::const_iterator i = p.coefficients.begin(); i != p.coefficients.end(); ++i) {
        if (i != p.coefficients.begin()) {
            os << " + ";
        }
        os << i->second;
        if (i->first != 0)
        {
            os << "x^" << i->first;
        }
        
    }
    return os;
}