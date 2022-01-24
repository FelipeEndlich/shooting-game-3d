#include "matrix.hpp"
#include <stdexcept>
#include <sstream>

using namespace math;

#pragma region Constructor and Destructor
Matrix::Matrix()
{
    allocate(0, 0);
}

Matrix::Matrix(int rows, int columns)
{
    allocate(rows, columns);
}

Matrix::Matrix(const Matrix &other)
{
    copy(other);
}

Matrix::~Matrix()
{
    deallocate();
}
#pragma endregion // Constructor and Destructor

#pragma region Getters and Setters
int Matrix::getRows() const
{
    return rows;
}

int Matrix::getColumns() const
{
    return columns;
}

void Matrix::setRows(int rows)
{
    if (rows < 0)
    {
        throw std::invalid_argument("rows must be greater than or equal to 0");
    }
    if (rows != this->rows)
    {
        deallocate();
        allocate(rows, columns);
    }
}

void Matrix::setColumns(int columns)
{
    if (columns < 0)
    {
        throw std::invalid_argument("columns must be greater than or equal to 0");
    }
    if (columns != this->columns)
    {
        deallocate();
        allocate(rows, columns);
    }
}
#pragma endregion // Getters and Setters

#pragma region Operator Overloading
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        deallocate();
        copy(other);
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other)
{

    if (this->rows != other.rows || this->columns != other.columns)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows, this->columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            result[i][j] = this->values[i][j] + other.values[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix &other)
{
    if (this->rows != other.rows || this->columns != other.columns)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows, this->columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            result[i][j] = this->values[i][j] - other.values[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix &other)
{
    if (this->columns != other.rows)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows, other.columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < other.columns; j++)
            for (int k = 0; k < this->columns; k++)
                result[i][j] += this->values[i][k] * other.values[k][j];

    return result;
}

Vector Matrix::operator*(const Vector &other) const
{
    if (this->columns != other.getDimension())
        throw std::invalid_argument("Dimension mismatch");

    Vector result(this->rows);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            result[i] += this->values[i][j] * other[j];

    return result;
}

Matrix Matrix::operator*(const double &other)
{
    Matrix result(this->rows, this->columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            result[i][j] = this->values[i][j] * other;

    return result;
}

Matrix Matrix::operator/(const double &other)
{
    Matrix result(this->rows, this->columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            result[i][j] = this->values[i][j] / other;

    return result;
}

Matrix Matrix::operator^(const int &other)
{
    if (other < 1)
        throw std::invalid_argument("Invalid exponent");

    Matrix result(*this);

    for (int i = 1; i < other; i++)
        result = result * (*this);

    return result;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (this->rows != other.rows || this->columns != other.columns)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            this->values[i][j] += other.values[i][j];

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if (this->rows != other.rows || this->columns != other.columns)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            this->values[i][j] -= other.values[i][j];

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    if (this->columns != other.rows)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows, other.columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < other.columns; j++)
            for (int k = 0; k < this->columns; k++)
                result[i][j] += this->values[i][k] * other.values[k][j];

    *this = result;

    return *this;
}

Matrix &Matrix::operator*=(const double &other)
{
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            this->values[i][j] *= other;

    return *this;
}

Matrix &Matrix::operator/=(const double &other)
{
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            this->values[i][j] /= other;

    return *this;
}

Matrix &Matrix::operator^=(const int &other)
{
    if (other < 1)
        throw std::invalid_argument("Invalid exponent");

    for (int i = 1; i < other; i++)
        *this = *this * (*this);

    return *this;
}

Vector Matrix::operator[](int i) const
{
    if (i < 0 || i >= this->rows)
        throw std::invalid_argument("Index out of bounds");

    return this->values[i];
}

Vector &Matrix::operator[](int i)
{
    if (i < 0 || i >= this->rows)
        throw std::invalid_argument("Index out of bounds");

    return this->values[i];
}
#pragma endregion // Operator Overloading

#pragma region Other Methods
Matrix Matrix::transpose()
{
    Matrix result(this->columns, this->rows);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            result[j][i] = this->values[i][j];

    return result;
}

std::string Matrix::to_string() const
{
    std::stringstream ss;

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
            ss << this->values[i][j] << " ";

        ss << std::endl;
    }

    return ss.str();
}
#pragma endregion // Other Methods

#pragma region Static Methods
Matrix Matrix::zero(int rows, int columns)
{
    Matrix result(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result[i][j] = 0;

    return result;
}

Matrix Matrix::identity(int rows, int columns)
{
    Matrix result(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result[i][j] = (i == j) ? 1 : 0;

    return result;
}
#pragma endregion // Static Methods

#pragma region Protected Methods
void Matrix::allocate(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    this->values.resize(rows);
    for (int i = 0; i < rows; i++)
        this->values[i].resize(columns);
}

void Matrix::deallocate()
{
    this->rows = 0;
    this->columns = 0;
    this->values.clear();
}

void Matrix::copy(const Matrix &other)
{
    allocate(other.rows, other.columns);
    for (int i = 0; i < other.rows; i++)
        for (int j = 0; j < other.columns; j++)
            this->values[i][j] = other.values[i][j];
}
#pragma endregion // Protected Methods