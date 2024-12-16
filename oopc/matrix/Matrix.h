#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

class MatrixException : public std::exception{
public:
    MatrixException(const std::string& msg) : message(msg) {}
    const char * what() const noexcept { return message.c_str(); }
private:
    std::string message;
};

class MatrxiAllocationFailException : public MatrixException{
public:
    MatrxiAllocationFailException() : MatrixException("Matrix allocation failed") {}
};
class MatrixOutOfBoundsException : public MatrixException{
public:
    MatrixOutOfBoundsException() : MatrixException("Matrix out of bounds") {}
};
class MatrixDimensionMismatchException : public MatrixException{
public:
    MatrixDimensionMismatchException() : MatrixException("Matrix dimensions do not match") {}
};
class MatrixFileIOException : public MatrixException{
public:
    MatrixFileIOException() : MatrixException("Matrix file IO exception") {}
};

class Matrix
{
private:
    struct MatrixData;
    MatrixData *data;
public:
    class Dref;
    Matrix(unsigned int rows, unsigned int cols);
    ~Matrix();
    Matrix(const Matrix &m);
    Matrix(std::ifstream &is);
    Matrix &operator=(const Matrix &m);
    Matrix &operator+=(const Matrix &m);
    Matrix &operator-=(const Matrix &m);
    Matrix &operator*=(const Matrix &m);
    Dref operator()(unsigned int row, unsigned int col);
    double operator()(unsigned int row, unsigned int col) const;
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);
    friend bool operator==(const Matrix &m1, const Matrix &m2);
    friend bool operator!=(const Matrix &m1, const Matrix &m2);
    
};    
class Matrix::Dref
{
    friend class Matrix;
    Matrix &m;
    unsigned int col;
    unsigned int row;
    Dref(Matrix &m, unsigned int col, unsigned int row);
public:
    operator double() const;
    Matrix::Dref &operator=(double d);
    Matrix::Dref &operator=(const Dref &ref);
};

struct Matrix::MatrixData
{
    MatrixData(unsigned int rows, unsigned int cols);
    ~MatrixData();
    unsigned int rows;
    unsigned int cols;
    double **data;
    unsigned int refCount;
    MatrixData* detach();
};