#pragma once

#include "vector.hpp"
#include <vector>
#include <string>

namespace math
{
    class Matrix
    {
    public:
        Matrix();
        Matrix(int rows, int columns);
        Matrix(const Matrix &other);
        ~Matrix();

        Matrix &operator=(const Matrix &other);
        Matrix operator+(const Matrix &other);
        Matrix operator-(const Matrix &other);
        Matrix operator*(const Matrix &other);
        Vector operator*(const Vector &other) const;
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

        int get_rows() const;
        int get_columns() const;

        void set_rows(int rows);
        void set_columns(int columns);

        Matrix Transpose();
        std::string to_string() const;

        static Matrix Zero(int rows, int columns);
        static Matrix Identity(int rows, int columns);

    protected:
        void Allocate(int rows, int columns);
        void Deallocate();
        void Copy(const Matrix &other);

    private:
        int rows_;
        int columns_;
        std::vector<Vector> values_;
    };
} // namespace Math
