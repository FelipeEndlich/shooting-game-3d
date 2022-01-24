#pragma once

#include "vector.hpp"
#include <vector>
#include <string>

namespace math
{
    class Matrix
    {
    public:
        Matrix(int rows, int columns);
        Matrix(const Matrix &other);
        ~Matrix();

        Matrix &operator=(const Matrix &other);
        Matrix operator+(const Matrix &other);
        Matrix operator-(const Matrix &other);
        Matrix operator*(const Matrix &other);
        Matrix operator*(const double &other);
        Matrix operator/(const double &other);
        Matrix operator^(const int &other);

        Matrix &operator+=(const Matrix &other);
        Matrix &operator-=(const Matrix &other);
        Matrix &operator*=(const Matrix &other);
        Matrix &operator*=(const double &other);
        Matrix &operator/=(const double &other);
        Matrix &operator^=(const int &other);

        Vector operator[](int i) const;
        Vector &operator[](int i);

        Matrix transpose();
        std::string to_string() const;

        static Matrix zero(int rows, int columns);
        static Matrix identity(int rows, int columns);

    protected:
        void allocate(int rows, int columns);
        void deallocate();
        void copy(const Matrix &other);

    private:
        int rows;
        int columns;
        std::vector<Vector> values;
    };
} // namespace Math
