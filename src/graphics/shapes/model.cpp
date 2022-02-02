#include "model.hpp"

using ::graphics::color::RGBA;
using ::graphics::shapes::Model;

#pragma region Constructors and Destructors
Model::Model()
{
    points_ = math::Matrix(0, 0);
    color_ = RGBA();
}

Model::Model(const math::Matrix &matrix)
{
    points_ = matrix;
    color_ = RGBA();
}

Model::Model(const math::Matrix &matrix, const RGBA &color)
{
    points_ = matrix;
    color_ = color;
}

Model::Model(const Model &other)
{
    points_ = other.points_;
    color_ = other.color_;
}

Model::Model(const Model &&other)
{
    points_ = other.points_;
    color_ = other.color_;
}
#pragma endregion // Constructors and Destructors

#pragma region Operators
Model &Model::operator=(const Model &other)
{
    if (this != &other)
    {
        points_ = other.points_;
        color_ = other.color_;
    }
    return *this;
}

Model &Model::operator=(const Model &&other)
{
    if (this != &other)
    {
        points_ = other.points_;
        color_ = other.color_;
    }
    return *this;
}
#pragma endregion // Operators