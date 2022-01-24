#include "model.hpp"

using namespace graphics::elements;

#pragma region Constructors and Destructors
Model::Model()
{
    this->points = math::Matrix(0, 0);
    this->color = graphics::color::RGBA();
}

Model::Model(const math::Matrix &matrix)
{
    this->points = matrix;
    this->color = graphics::color::RGBA();
}

Model::Model(const math::Matrix &matrix, const graphics::color::RGBA &color)
{
    this->points = matrix;
    this->color = color;
}

Model::Model(const Model &other)
{
    this->points = other.points;
    this->color = other.color;
}

Model::Model(const Model &&other)
{
    this->points = other.points;
    this->color = other.color;
}
#pragma endregion // Constructors and Destructors

#pragma region Operators
Model &Model::operator=(const Model &other)
{
    if (this != &other)
    {
        this->points = other.points;
        this->color = other.color;
    }
    return *this;
}

Model &Model::operator=(const Model &&other)
{
    if (this != &other)
    {
        this->points = other.points;
        this->color = other.color;
    }
    return *this;
}
#pragma endregion // Operators