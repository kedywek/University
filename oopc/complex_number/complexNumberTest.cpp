#include <iostream>
#include "complexNumber.h"
void displayAllComplexNumbers(ComplexNumber a, ComplexNumber b, ComplexNumber c);
void resetAllNumbers(ComplexNumber& a, ComplexNumber& b, ComplexNumber& c);
int main(){
    ComplexNumber a(4, 7);
    ComplexNumber b(2, 4);
    ComplexNumber c(1, 2);
    ComplexNumber d(1);
    ComplexNumber e(0, 1);
    displayAllComplexNumbers(a, b, c);
    a += b += c;
    displayAllComplexNumbers(a, b, c);
    resetAllNumbers(a, b, c);
    (a += b) += c;
    displayAllComplexNumbers(a, b, c); 
    resetAllNumbers(a, b, c);
    a -= b -= c;
    displayAllComplexNumbers(a, b, c);
    resetAllNumbers(a, b, c);
    (a -= b) -= c;
    displayAllComplexNumbers(a, b, c);
    resetAllNumbers(a, b, c);
    a *= b *= c;
    displayAllComplexNumbers(a, b, c);
    resetAllNumbers(a, b, c);
    (a *= b) *= c;
    displayAllComplexNumbers(a, b, c);
    resetAllNumbers(a, b, c);
    a /= b /= c;
    displayAllComplexNumbers(a, b, c);
    resetAllNumbers(a, b, c);
    (a /= b) /= c;
    displayAllComplexNumbers(a, b, c);
    std::cout << a + 7 << std::endl;
    std::cout << 7 + a << std::endl;
    std::cout << a - 7 << std::endl;
    std::cout << 7 - a << std::endl;
    std::cout << a * 7 << std::endl;
    std::cout << 7 * a << std::endl;
    std::cout << a / 7 << std::endl;
    std::cout << 7 / a << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << (a != b) << std::endl;
    std::cout << (d == 1) << std::endl;
    std::cout << (d != 1) << std::endl;
    std::cout << (e == 1) << std::endl;
    std::cout << (e != 1) << std::endl;
    std::cout << a.amplitude() << std::endl;
    std::cout << a.phase() << std::endl;




    return 0;
}

void displayAllComplexNumbers(ComplexNumber a, ComplexNumber b, ComplexNumber c){
    std::cout << "a: " << a << "b: " << b << "c: " << c << std::endl;
}

void resetAllNumbers(ComplexNumber& a, ComplexNumber& b, ComplexNumber& c){
    a = ComplexNumber(4, 7);
    b = ComplexNumber(2, 4);
    c = ComplexNumber(1, 2);
}