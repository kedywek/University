#include "complexNumber.h"
#include <math.h>

ComplexNumber::ComplexNumber(){
    this->real = 0;
    this->imaginary = 0;
}

ComplexNumber::ComplexNumber(double real){
    this->real = real;
    this->imaginary = 0;
}

ComplexNumber::ComplexNumber(double real, double imaginary){
    this->real = real;
    this->imaginary = imaginary;
}

ComplexNumber::~ComplexNumber(){
}

ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& secondComplexNumber){
    this->real += secondComplexNumber.real;
    this->imaginary += secondComplexNumber.imaginary;
    return *this;
}

ComplexNumber& ComplexNumber::operator-=(const ComplexNumber& secondComplexNumber){
    this->real -= secondComplexNumber.real;
    this->imaginary -= secondComplexNumber.imaginary;
    return *this;
}

ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& secondComplexNumber){
    double tempReal = this->real;
    this->real = this->real * secondComplexNumber.real - this->imaginary * secondComplexNumber.imaginary;
    this->imaginary = tempReal * secondComplexNumber.imaginary + this->imaginary * secondComplexNumber.real;
    return *this;
}

ComplexNumber& ComplexNumber::operator/=(const ComplexNumber& secondComplexNumber){
    double tempReal = this->real;
    this->real = (this->real * secondComplexNumber.real + this->imaginary * secondComplexNumber.imaginary) / (pow(secondComplexNumber.real, 2) + pow(secondComplexNumber.imaginary, 2));
    this->imaginary = (this->imaginary * secondComplexNumber.real - tempReal * secondComplexNumber.imaginary) / (pow(secondComplexNumber.real, 2) + pow(secondComplexNumber.imaginary, 2));
    return *this;
}

ComplexNumber operator+(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber){
    ComplexNumber tempComplexNumber;
    tempComplexNumber.real = firstComplexNumber.real + secondComplexNumber.real;
    tempComplexNumber.imaginary = firstComplexNumber.imaginary + secondComplexNumber.imaginary;
    return tempComplexNumber;
}

ComplexNumber operator-(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber){
    ComplexNumber tempComplexNumber;
    tempComplexNumber.real = firstComplexNumber.real - secondComplexNumber.real;
    tempComplexNumber.imaginary = firstComplexNumber.imaginary - secondComplexNumber.imaginary;
    return tempComplexNumber;
}

ComplexNumber operator*(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber){
    ComplexNumber tempComplexNumber;
    tempComplexNumber.real = firstComplexNumber.real * secondComplexNumber.real - firstComplexNumber.imaginary * secondComplexNumber.imaginary;
    tempComplexNumber.imaginary = firstComplexNumber.real * secondComplexNumber.imaginary + firstComplexNumber.imaginary * secondComplexNumber.real;
    return tempComplexNumber;
}

ComplexNumber operator/(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber){
    ComplexNumber tempComplexNumber;
    tempComplexNumber.real = (firstComplexNumber.real * secondComplexNumber.real + firstComplexNumber.imaginary * secondComplexNumber.imaginary) / (pow(secondComplexNumber.real, 2) + pow(secondComplexNumber.imaginary, 2));
    tempComplexNumber.imaginary = (firstComplexNumber.imaginary * secondComplexNumber.real - firstComplexNumber.real * secondComplexNumber.imaginary) / (pow(secondComplexNumber.real, 2) + pow(secondComplexNumber.imaginary, 2));
    return tempComplexNumber;
}
std::ostream& operator<<(std::ostream& os, const ComplexNumber& secondComplexNumber){
    os << secondComplexNumber.real << " + " << secondComplexNumber.imaginary << "i";
    return os;
}

bool ComplexNumber::operator==(const ComplexNumber& secondComplexNumber){
    return (this->real == secondComplexNumber.real && this->imaginary == secondComplexNumber.imaginary);
}

bool ComplexNumber::operator!=(const ComplexNumber& secondComplexNumber){
    return (this->real != secondComplexNumber.real || this->imaginary != secondComplexNumber.imaginary);
}

double ComplexNumber::amplitude(){
    return sqrt(pow(this->real, 2) + pow(this->imaginary, 2));
}

double ComplexNumber::phase(){
    return atan(this->imaginary / this->real);
}
