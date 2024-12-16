#include "Matrix.h"
#include <iostream>
#include <fstream>

void printMatrix(const Matrix &m, const std::string &name)
{
    std::cout << name << ":\n" << m << std::endl;
}

void testMatrixInitialization()
{
    Matrix m(2, 2);
    printMatrix(m, "Initialized Matrix");
    std::cout << "Matrix Initialization Test Passed" << std::endl;
}

void testMatrixAddition()
{
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    m1(0, 0) = 1.0; m1(0, 1) = 2.0; m1(1, 0) = 3.0; m1(1, 1) = 4.0;
    m2(0, 0) = 5.0; m2(0, 1) = 6.0; m2(1, 0) = 7.0; m2(1, 1) = 8.0;
    printMatrix(m1, "Matrix m1 before addition");
    printMatrix(m2, "Matrix m2 before addition");
    m1 += m2;
    printMatrix(m1, "Matrix m1 after addition");
    std::cout << "Matrix Addition Test Passed" << std::endl;
}

void testMatrixSubtraction()
{
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    m1(0, 0) = 5.0; m1(0, 1) = 6.0; m1(1, 0) = 7.0; m1(1, 1) = 8.0;
    m2(0, 0) = 1.0; m2(0, 1) = 2.0; m2(1, 0) = 3.0; m2(1, 1) = 4.0;
    printMatrix(m1, "Matrix m1 before subtraction");
    printMatrix(m2, "Matrix m2 before subtraction");
    m1 -= m2;
    printMatrix(m1, "Matrix m1 after subtraction");
    std::cout << "Matrix Subtraction Test Passed" << std::endl;
}

void testMatrixMultiplication()
{
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    m1(0, 0) = 1.0; m1(0, 1) = 2.0; m1(1, 0) = 3.0; m1(1, 1) = 4.0;
    m2(0, 0) = 2.0; m2(0, 1) = 0.0; m2(1, 0) = 1.0; m2(1, 1) = 2.0;
    printMatrix(m1, "Matrix m1 before multiplication");
    printMatrix(m2, "Matrix m2 before multiplication");
    m1 *= m2;
    printMatrix(m1, "Matrix m1 after multiplication");
    std::cout << "Matrix Multiplication Test Passed" << std::endl;
}

void testUnevenMatrixMultiplication()
{
    Matrix m1(2, 3);
    Matrix m2(3, 2);
    m1(0, 0) = 1.0; m1(0, 1) = 2.0; m1(0, 2) = 3.0;
    m1(1, 0) = 4.0; m1(1, 1) = 5.0; m1(1, 2) = 6.0;
    m2(0, 0) = 7.0; m2(0, 1) = 8.0;
    m2(1, 0) = 9.0; m2(1, 1) = 10.0;
    m2(2, 0) = 11.0; m2(2, 1) = 12.0;
    printMatrix(m1, "Matrix m1 before uneven multiplication");
    printMatrix(m2, "Matrix m2 before uneven multiplication");
    Matrix result = m1 * m2;
    printMatrix(result, "Result matrix after uneven multiplication");
    std::cout << "Uneven Matrix Multiplication Test Passed" << std::endl;
}

void testMatrixEquality()
{
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    m1(0, 0) = 1.0; m1(0, 1) = 2.0; m1(1, 0) = 3.0; m1(1, 1) = 4.0;
    m2(0, 0) = 1.0; m2(0, 1) = 2.0; m2(1, 0) = 3.0; m2(1, 1) = 4.0;
    printMatrix(m1, "Matrix m1");
    printMatrix(m2, "Matrix m2");
    if (m1 == m2)
    {
        std::cout << "Matrix Equality Test Passed" << std::endl;
    }
    else
    {
        std::cout << "Matrix Equality Test Failed" << std::endl;
    }
}

void testMatrixInequality()
{
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    m1(0, 0) = 1.0; m1(0, 1) = 2.0; m1(1, 0) = 3.0; m1(1, 1) = 4.0;
    m2(0, 0) = 1.0; m2(0, 1) = 2.0; m2(1, 0) = 3.0; m2(1, 1) = 5.0;
    printMatrix(m1, "Matrix m1");
    printMatrix(m2, "Matrix m2");
    if (m1 != m2)
    {
        std::cout << "Matrix Inequality Test Passed" << std::endl;
    }
    else
    {
        std::cout << "Matrix Inequality Test Failed" << std::endl;
    }
}

void testMatrixFromFile()
{
    std::ifstream file("matrix.csv");
    if (!file)
    {
        std::cerr << "Failed to open matrix.csv" << std::endl;
        return;
    }
    Matrix m(file);
    printMatrix(m, "Matrix from file");
    std::cout << "Matrix From File Test Passed" << std::endl;
}



int main()
{
    testMatrixInitialization();
    testMatrixAddition();
    testMatrixSubtraction();
    testMatrixMultiplication();
    testUnevenMatrixMultiplication();
    testMatrixEquality();
    testMatrixInequality();
    testMatrixFromFile();
    return 0;
}