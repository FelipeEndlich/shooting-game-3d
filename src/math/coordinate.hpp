#pragma once

namespace math
{
    class Coordinate
    {
    public:
        Coordinate(double x, double y);
        Coordinate(const Coordinate &other);

        double getX() const;
        double getY() const;

        void setX(double x);
        void setY(double y);

        Coordinate &operator=(const Coordinate &other);
        bool operator==(const Coordinate &other) const;
        bool operator!=(const Coordinate &other) const;

        double operator[](int i) const;
        double &operator[](int i);

        static Coordinate zero();

    protected:
        void copy(const Coordinate &other);

    private:
        double x;
        double y;
    };
} // namespace Math