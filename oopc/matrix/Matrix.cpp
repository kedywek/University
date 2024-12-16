#include "Matrix.h"
#include <string>
#include <new>


Matrix::MatrixData::MatrixData(unsigned int rows, unsigned int cols)
{
    this->rows = rows;
    this->cols = cols;
    try
    {     
        data = new double*[rows];
        for (unsigned int i = 0; i < rows; i++)
        {
            data[i] = new double[cols];
            for (unsigned int j = 0; j < cols; j++)
            {
                data[i][j] = 0.0;
            }
        }
    }
    catch (std::bad_alloc &e)
    {
        throw MatrxiAllocationFailException();
    }
    refCount = 1;
}

Matrix::MatrixData::~MatrixData()
{
    for (unsigned int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::MatrixData* Matrix::MatrixData::detach()
{
    if (refCount == 1)
    {
        return this;
    }
    try
    {
        MatrixData *t = new MatrixData(rows, cols);    
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < cols; j++)
            {
                t->data[i][j] = data[i][j];
            }
        }
        this->refCount--;
        return t;
    }
    catch (std::bad_alloc &e)
    {
        throw MatrxiAllocationFailException();
    }
    
    
}

Matrix::Dref::Dref(Matrix &m, unsigned int col, unsigned int row) : m(m), col(col), row(row) {}

Matrix::Dref::operator double() const
{
    return m.data->data[row][col];
}

Matrix::Dref &Matrix::Dref::operator=(double d)
{
    m.data = m.data->detach();
    m.data->data[row][col] = d;
    return *this;
}

Matrix::Dref &Matrix::Dref::operator=(const Dref &ref)
{
    return operator=((double)ref);
}

Matrix::Matrix(unsigned int rows, unsigned int cols)
{
    try
    {
        data = new MatrixData(rows, cols);
    }
    catch (std::bad_alloc &e)
    {
        throw MatrxiAllocationFailException();
    }
    
}

Matrix::~Matrix()
{
    if (--data->refCount == 0)
    {
        delete data;
    }
}

Matrix::Matrix(const Matrix &m)
{
    data = m.data;
    data->refCount++;
}

Matrix &Matrix::operator=(const Matrix &m)
{   
    if (this == &m)
    {
        return *this;
    }
    m.data->refCount++;
    if (--data->refCount == 0)
    {
        delete data;
    }
    data = m.data;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
    if (data->rows != m.data->rows || data->cols != m.data->cols)
    {
        throw MatrixDimensionMismatchException();
    }
    data = data->detach();
    for (unsigned int i = 0; i < data->rows; i++)
    {
        for (unsigned int j = 0; j < data->cols; j++)
        {
            data->data[i][j] += m.data->data[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m)
{
    if (data->rows != m.data->rows || data->cols != m.data->cols)
    {
        throw MatrixDimensionMismatchException();
    }
    data = data->detach();
    for (unsigned int i = 0; i < data->rows; i++)
    {
        for (unsigned int j = 0; j < data->cols; j++)
        {
            data->data[i][j] -= m.data->data[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m)
{
    if (data->cols != m.data->rows)
    {
        throw MatrixDimensionMismatchException(); 
    }
    
    try
    {
        Matrix *t = new Matrix(data->rows, m.data->cols);
            for (unsigned int i = 0; i < data->rows; i++)
        {
            for (unsigned int j = 0; j < m.data->cols; j++)
            {
                for (unsigned int k = 0; k < data->cols; k++)
                {
                    t->data->data[i][j] += data->data[i][k] * m.data->data[k][j];
                }
            }
        }
        *this = *t;
        delete t;
        return *this;
    }
    catch(const std::exception& e)
    {
        throw MatrxiAllocationFailException();
    }
    
    
}

Matrix::Dref Matrix::operator()(unsigned int row, unsigned int col)
{
    if (row >= data->rows || col >= data->cols)
    {
        throw MatrixOutOfBoundsException();
    }
    
    return Dref(*this, col, row);
}

double Matrix::operator()(unsigned int row, unsigned int col) const
{
    if (row >= data->rows || col >= data->cols)
    {
        throw MatrixOutOfBoundsException();
    }
    
    return data->data[row][col];
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for (unsigned int i = 0; i < m.data->rows; i++)
    {
        for (unsigned int j = 0; j < m.data->cols; j++)
        {
            os << m.data->data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

Matrix::Matrix(std::ifstream &is)
{
    try
    {
        std::string line;
        std::getline(is, line);
        unsigned int rows = 0;
        unsigned int cols = 0;
        while (!line.empty() && !is.eof())
        {
            rows++;
            std::getline(is, line);
        }
        if (!line.empty())
        {
            rows++;
        }
        size_t pos = 0;
        while ((pos = line.find(";")) != std::string::npos)
        {
            cols++;
            line = line.substr(pos + 1);
        }
        cols++;
        data = new MatrixData(rows, cols);
        is.clear();
        is.seekg(0, std::ios::beg);
        for (unsigned int i = 0; i < rows; i++)
        {
            std::getline(is, line);
            size_t pos = 0;
            unsigned int j = 0;
            while ((pos = line.find(";")) != std::string::npos)
            {
                data->data[i][j] = std::stod(line.substr(0, pos));
                line = line.substr(pos + 1);
                j++;
            }
            data->data[i][j] = std::stod(line);
        }
        
    }
    catch(const std::exception& e)
    {
        throw MatrixFileIOException();
    }
    
    
}

Matrix operator+(const Matrix &m1, const Matrix &m2)
{
    if (m1.data->rows != m2.data->rows || m1.data->cols != m2.data->cols)
    {
        throw MatrixDimensionMismatchException();
    }
    Matrix m(m1);
    m += m2; 
    return m;
}

Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    if (m1.data->rows != m2.data->rows || m1.data->cols != m2.data->cols)
    {
        throw MatrixDimensionMismatchException();
    }
    Matrix m(m1);
    m -= m2;
    return m;
}

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    if (m1.data->cols != m2.data->rows)
    {
        throw MatrixDimensionMismatchException();
    }
    Matrix m(m1);
    m *= m2;
    return m;
}

bool operator==(const Matrix &m1, const Matrix &m2)
{
    if (m1.data->rows != m2.data->rows || m1.data->cols != m2.data->cols)
    {
        return false;
    }
    for (unsigned int i = 0; i < m1.data->rows; i++)
    {
        for (unsigned int j = 0; j < m1.data->cols; j++)
        {
            if (m1.data->data[i][j] != m2.data->data[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix &m1, const Matrix &m2)
{
    return !(m1 == m2);
}