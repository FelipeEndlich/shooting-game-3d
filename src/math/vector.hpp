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

        int get_dimension() const;

        void set_dimension(int dimension);

        double DotProduct(const Vector &other) const;
        Vector CrossProduct(const Vector &other) const;
        double ScalarProduct(const Vector &other) const;
        double Magnitude() const;
        Vector Normalize() const;
        double Distance(const Vector &other) const;
        double Angle(const Vector &other) const;

        std::string to_string() const;
        void Resize(int dimension);
        void Swap(Vector &other);

        static Vector Zero(int dimension);
        static Vector Fill(int dimension, double value);
        static Vector ThreeDimPoint(double x, double y, double z);

    protected:
        void Copy(const Vector &other);
        void Allocate(int dimension);
        void Deallocate();

    private:
        int dimension_;
        std::vector<double> values_;
    };
} // namespace Math