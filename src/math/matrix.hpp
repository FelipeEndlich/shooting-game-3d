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

        double Det() const;
        Matrix Adj() const;
        Matrix Transpose();
        Matrix Inverse();
        std::string to_string() const;

        static Matrix Zero(int rows, int columns);
        static Matrix Identity(int rows, int columns);
        static Matrix ThreeDimMatrix(double i1, double i2, double i3,
                                     double j1, double j2, double j3,
                                     double k1, double k2, double k3);
        static Matrix FourDimMatrix(double i1, double i2, double i3, double i4,
                                    double j1, double j2, double j3, double j4,
                                    double k1, double k2, double k3, double k4,
                                    double l1, double l2, double l3, double l4);

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
