#pragma once

#include <vector>
#include <string>

namespace math
{
    class Vector
    {
    public:
        Vector();
        Vector(int dimension);
        Vector(const Vector &other);
        ~Vector();

        Vector &operator=(const Vector &other);
        bool operator==(const Vector &other) const;
        bool operator!=(const Vector &other) const;

        Vector operator+(const Vector &other) const;
        Vector operator-(const Vector &other) const;
        Vector operator*(const double &other) const;
        Vector operator/(const double &other) const;
        Vector operator^(const int &other) const;

        Vector &operator+=(const Vector &other);
        Vector &operator-=(const Vector &other);
        Vector &operator*=(const double &other);
        Vector &operator/=(const double &other);
        Vector &operator^=(const int &other);

        double operator[](int i) const;
        double &operator[](int i);

        double dotProduct(const Vector &other) const;
        Vector crossProduct(const Vector &other) const;
        double scalarProduct(const Vector &other) const;
        double magnitude() const;
        Vector normalize() const;
        double distance(const Vector &other) const;
        double angle(const Vector &other) const;

        std::string to_string() const;
        void resize(int dimension);
        void swap(Vector &other);

        static Vector zero(int dimension);
        static Vector fill(int dimension, double value);

    protected:
        void copy(const Vector &other);
        void allocate(int dimension);
        void deallocate();

    private:
        int dimension;
        std::vector<double> values;
    };
} // namespace Math