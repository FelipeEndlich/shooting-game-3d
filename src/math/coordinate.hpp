#pragma once

class Coordinate
{
public:
    Coordinate(double x, double y);
    Coordinate(const Coordinate &other);
    Coordinate &operator=(const Coordinate &other);
    bool operator==(const Coordinate &other) const;
    bool operator!=(const Coordinate &other) const;
    double x;
    double y;

    static Coordinate zero();
};