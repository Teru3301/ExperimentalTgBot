
#include "math.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>


Vector::Vector() = default;
Vector::Vector(size_t size) : data_(size){}

size_t Vector::size() const
{
    return data_.size();
}

float& Vector::operator[](size_t index)
{
    return data_.at(index);
}

const float& Vector::operator[](size_t index) const
{
    return data_.at(index);
}

float Vector::dot(const Vector& other) const
{
    if (size() != other.size())
    {
        throw std::invalid_argument("Vector sizes do not match. vector.cpp");
    }

    return std::inner_product(
        data_.begin(),
        data_.end(),
        other.data_.begin(),
        0.0f
    );
}

float Vector::sum() const
{
    return std::accumulate(
        data_.begin(),
        data_.end(),
        0.0f
    );
}

float Vector::mean() const
{
    if (data_.empty())
    {
        throw std::runtime_error("Cannot compute mean of empty vector. vector.cpp");
    }

    return sum() / static_cast<float>(size());
}


float Vector::norm() const
{
    return std::sqrt(dot(*this));
}

void Vector::zero()
{
    std::fill(
        data_.begin(),
        data_.end(),
        0.0f
    );
}

Vector Vector::operator+(const Vector& other) const
{
    if (size() != other.size())
    {
        throw std::invalid_argument("Vector sizes do not match.");
    }

    Vector result(size());

    for (size_t i = 0; i < size(); ++i)
    {
        result.data_[i] = data_[i] + other.data_[i];
    }

    return result;
}

Vector Vector::operator-(const Vector& other) const
{
    if (size() != other.size())
    {
        throw std::invalid_argument("Vector sizes do not match.");
    }

    Vector result(size());

    for (size_t i = 0; i < size(); ++i)
    {
        result.data_[i] = data_[i] - other.data_[i];
    }

    return result;
}

Vector Vector::operator*(float scalar) const
{
    Vector result(size());

    for (size_t i = 0; i < size(); ++i)
    {
        result.data_[i] = data_[i] * scalar;
    }

    return result;
}

Vector& Vector::operator+=(const Vector& other)
{
    if (size() != other.size())
    {
        throw std::invalid_argument("Vector sizes do not match.");
    }

    for (size_t i = 0; i < size(); ++i)
    {
        data_[i] += other.data_[i];
    }

    return *this;
}

Vector& Vector::operator-=(const Vector& other)
{
    if (size() != other.size())
    {
        throw std::invalid_argument("Vector sizes do not match.");
    }

    for (size_t i = 0; i < size(); ++i)
    {
        data_[i] -= other.data_[i];
    }

    return *this;
}

Vector& Vector::operator*=(float scalar)
{
    for (float& value : data_)
    {
        value *= scalar;
    }

    return *this;
}

Vector operator*(float scalar, const Vector& vector)
{
    return vector * scalar;
}

