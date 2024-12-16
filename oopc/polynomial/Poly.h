#pragma once
#include <map>
#include <iostream>

class Poly{
    private:
        std::map<int, double> coefficients;   
    public:
        Poly();
        Poly(double coefficient);
        ~Poly();
        double operator()(double x) const;
        double& operator[](unsigned int i);
        double operator[](unsigned int i) const;
        Poly& operator+=(const Poly& p);
        Poly& operator-=(const Poly& p);
        Poly& operator*=(const Poly& p);
        friend Poly operator-(const Poly& p);
        friend Poly operator+(const Poly& p1,const Poly& p2);
        friend Poly operator-(const Poly& p1,const Poly& p2);
        friend Poly operator*(const Poly& p1,const Poly& p2);
        friend std::ostream& operator<<(std::ostream& os, const Poly& p);
};

