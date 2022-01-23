#pragma once

#include "coordinate.hpp"
#include <vector>

namespace math
{
    class Matrix
    {
    public:
        Matrix(int rows);
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

        Matrix &operator++();
        Matrix &operator--();
        Matrix operator++(int);
        Matrix operator--(int);

        Coordinate operator[](int i) const;
        Coordinate &operator[](int i);

        Matrix transpose();
        Matrix inverse();
        Matrix cofactor();
        Matrix adjoint();
        double determinant();
        double trace();

        const char *toString() const;

        static Matrix zero(int rows);
        static Matrix identity(int rows);

    protected:
        void allocate();
        void deallocate();
        void copy(const Matrix &other);

    private:
        std::vector<Coordinate> coordinates;
    };
} // namespace Math
