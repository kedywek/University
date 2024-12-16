#pragma once
#include <iostream>

class ComplexNumber
{
private:
public:
    double real, imaginary;
    ComplexNumber();
    ComplexNumber(double real);
    ComplexNumber(double real, double imaginary);
    ~ComplexNumber();
    ComplexNumber& operator+=(const ComplexNumber& secondComplexNumber);
    ComplexNumber& operator-=(const ComplexNumber& secondComplexNumber);
    ComplexNumber& operator*=(const ComplexNumber& secondComplexNumber);
    ComplexNumber& operator/=(const ComplexNumber& secondComplexNumber);

    double amplitude();
    double phase();

    bool operator==(const ComplexNumber& secondComplexNumber);
    bool operator!=(const ComplexNumber& secondComplexNumber);
    friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& secondComplexNumber);
    friend ComplexNumber operator+(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber);
    friend ComplexNumber operator-(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber);
    friend ComplexNumber operator*(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber);
    friend ComplexNumber operator/(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber);
    friend ComplexNumber operator==(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber);
    friend ComplexNumber operator!=(const ComplexNumber& firstComplexNumber, const ComplexNumber& secondComplexNumber);
};

