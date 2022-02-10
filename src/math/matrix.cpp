#include "matrix.hpp"
#include <stdexcept>
#include <sstream>

#include <iostream>

using ::math::Matrix;
using ::math::Vector;

#pragma region Constructor and Destructor
Matrix::Matrix()
{
    Allocate(0, 0);
}

Matrix::Matrix(int rows, int columns)
{
    Allocate(rows, columns);
}

Matrix::Matrix(const Matrix &other)
{
    Copy(other);
}

Matrix::~Matrix()
{
    Deallocate();
}
#pragma endregion // Constructor and Destructor

#pragma region Getters and Setters
int Matrix::get_rows() const
{
    return rows_;
}

int Matrix::get_columns() const
{
    return columns_;
}

void Matrix::set_rows(int rows)
{
    if (rows < 0)
    {
        throw std::invalid_argument("rows must be greater than or equal to 0");
    }
    if (rows != this->rows_)
    {
        Deallocate();
        Allocate(rows, columns_);
    }
}

void Matrix::set_columns(int columns)
{
    if (columns < 0)
    {
        throw std::invalid_argument("columns must be greater than or equal to 0");
    }
    if (columns != this->columns_)
    {
        Deallocate();
        Allocate(rows_, columns);
    }
}
#pragma endregion // Getters and Setters

#pragma region Operator Overloading
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        Deallocate();
        Copy(other);
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other)
{

    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] + other.values_[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix &other)
{
    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] - other.values_[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix &other)
{
    if (this->columns_ != other.rows_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, other.columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < other.columns_; j++)
            for (int k = 0; k < this->columns_; k++)
                result[i][j] += this->values_[i][k] * other.values_[k][j];

    return result;
}

Vector Matrix::operator*(const Vector &other) const
{
    if (this->columns_ != other.get_dimension())
        throw std::invalid_argument("Dimension mismatch");

    Vector result(this->rows_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i] += this->values_[i][j] * other[j];

    return result;
}

Matrix Matrix::operator*(const double &other)
{
    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] * other;

    return result;
}

Matrix Matrix::operator/(const double &other)
{
    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] / other;

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
    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] += other.values_[i][j];

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] -= other.values_[i][j];

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    if (this->columns_ != other.rows_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, other.columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < other.columns_; j++)
            for (int k = 0; k < this->columns_; k++)
                result[i][j] += this->values_[i][k] * other.values_[k][j];

    *this = result;

    return *this;
}

Matrix &Matrix::operator*=(const double &other)
{
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] *= other;

    return *this;
}

Matrix &Matrix::operator/=(const double &other)
{
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] /= other;

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
    if (i < 0 || i >= this->rows_)
        throw std::invalid_argument("Index out of bounds");

    return this->values_[i];
}

Vector &Matrix::operator[](int i)
{
    if (i < 0 || i >= this->rows_)
        throw std::invalid_argument("Index out of bounds");

    return this->values_[i];
}
#pragma endregion // Operator Overloading

#pragma region Other Methods
double Matrix::Det() const
{   
    // This function implements the laplacian method for determinants

    auto submatrix = [this] (int i, int j) {
        Matrix sm = Matrix::Zero(get_rows() - 1, get_columns() - 1);
        for (int x = 0; x < get_rows(); x++) {
            if (x == i) continue;

            int row = x < i ? x : x - 1;
            for (int y = 0; y < get_columns(); y++) {
                if (y == j) continue;

                int column = y < j ? y : y - 1;
                sm[row][column] = values_[x][y];
            }
        }
        return sm;
    };

    // To find the determinant, rows == columns
    if (get_rows() != get_columns()) {
        std::cout << "The matrix dimensions are invalid!" << std::endl;
        exit(-1);
    }

    if (get_rows() == 1)
        return values_[0][0];

    else if (get_rows() == 2)
        return values_[0][0] * values_[1][1] - values_[0][1] * values_[1][0];

    double determinant = 0, sign = 1;
    for (int i = 0; i < get_rows(); i++) {
        auto subM = submatrix(0, i);
        determinant += sign * values_[0][i] * subM.Det();
        sign *= -1;
    }

    return determinant;
}

Matrix Matrix::Adj() const
{
    auto submatrix = [this] (int i, int j) {
        Matrix sm = Matrix::Zero(get_rows() - 1, get_columns() - 1);
        for (int x = 0; x < get_rows(); x++) {
            if (x == i) continue;

            int row = x < i ? x : x - 1;
            for (int y = 0; y < get_columns(); y++) {
                if (y == j) continue;

                int column = y < j ? y : y - 1;
                sm[row][column] = values_[x][y];
            }
        }
        return sm;
    };

    // To find the adj, rows == columns
    if (get_rows() != get_columns()) {
        std::cout << "The matrix dimensions are invalid!" << std::endl;
        exit(-1);
    }
    int N = get_rows();

    // Finding the matrix of coef
    Matrix coef(get_rows(), get_columns()); double signal = 1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            Matrix subM = submatrix(i, j);
            coef[i][j] = subM.Det() * signal;
            signal *= -1;
        }

    return coef.Transpose();
}

Matrix Matrix::Transpose()
{
    Matrix result(this->columns_, this->rows_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[j][i] = this->values_[i][j];

    return result;
}

Matrix Matrix::Inverse()
{
    return Adj() / Det();
}

std::string Matrix::to_string() const
{
    std::stringstream ss;

    for (int i = 0; i < this->rows_; i++)
    {
        for (int j = 0; j < this->columns_; j++)
            ss << this->values_[i][j] << " ";

        ss << std::endl;
    }

    return ss.str();
}
#pragma endregion // Other Methods

#pragma region Static Methods
Matrix Matrix::Zero(int rows, int columns)
{
    Matrix result(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result[i][j] = 0;

    return result;
}

Matrix Matrix::Identity(int rows, int columns)
{
    Matrix result(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result[i][j] = (i == j) ? 1 : 0;

    return result;
}

Matrix Matrix::ThreeDimMatrix(double i1, double i2, double i3,
                              double j1, double j2, double j3,
                              double k1, double k2, double k3)
{
    Matrix result(3, 3);

    result[0][0] = i1; result[0][1] = i2; result[0][2] = i3;
    result[1][0] = j1; result[1][1] = j2; result[1][2] = j3;
    result[2][0] = k1; result[2][1] = k2; result[2][2] = k3;

    return result;
}

Matrix Matrix::FourDimMatrix(double i1, double i2, double i3, double i4,
                             double j1, double j2, double j3, double j4,
                             double k1, double k2, double k3, double k4,
                             double l1, double l2, double l3, double l4)
{
    Matrix result(4, 4);

    result[0][0] = i1; result[0][1] = i2; result[0][2] = i3; result[0][3] = i4;
    result[1][0] = j1; result[1][1] = j2; result[1][2] = j3; result[1][3] = j4;
    result[2][0] = k1; result[2][1] = k2; result[2][2] = k3; result[2][3] = k4;
    result[3][0] = l1; result[3][1] = l2; result[3][2] = l3; result[3][3] = l4;

    return result;
}
#pragma endregion // Static Methods

#pragma region Protected Methods
void Matrix::Allocate(int rows, int columns)
{
    this->rows_ = rows;
    this->columns_ = columns;
    this->values_.resize(rows);
    for (int i = 0; i < rows; i++)
        this->values_[i].Resize(columns);
}

void Matrix::Deallocate()
{
    this->rows_ = 0;
    this->columns_ = 0;
    this->values_.clear();
}

void Matrix::Copy(const Matrix &other)
{
    Allocate(other.rows_, other.columns_);
    for (int i = 0; i < other.rows_; i++)
        for (int j = 0; j < other.columns_; j++)
            this->values_[i][j] = other.values_[i][j];
}
#pragma endregion // Protected Methods