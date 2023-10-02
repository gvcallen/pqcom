#include "Core.h"

namespace gel
{

Vec3f::Vec3f()
    : Vec3f(0.f, 0.f, 0.f)
{
    // intentionally empty
}

Vec3f::Vec3f(float const x, float const y, float const z)
    : x(x)
    , y(y)
    , z(z)
{
    // intentionally empty
}

Vec3f Vec3f::operator+() const
{
    return *this;
}

Vec3f Vec3f::operator-() const
{
    return Vec3f{-x,
                    -y,
                    -z};
}

Vec3f Vec3f::operator+(Vec3f const & summand) const
{
    return Vec3f{x + summand.x,
                    y + summand.y,
                    z + summand.z};
}

Vec3f Vec3f::operator-(Vec3f const & subtrahend) const
{
    return Vec3f{x - subtrahend.x,
                    y - subtrahend.y,
                    z - subtrahend.z};
}

Vec3f Vec3f::operator*(float const operand) const
{
    return Vec3f{x * operand,
                    y * operand,
                    z * operand};
}

Vec3f Vec3f::operator/(float const divisor) const
{
    return Vec3f{x / divisor,
                    y / divisor,
                    z / divisor};
}

Vec3f & Vec3f::operator+=(Vec3f const & summand)
{
    x += summand.x;
    y += summand.y;
    z += summand.z;
    return *this;
}

Vec3f & Vec3f::operator-=(Vec3f const & subtrahend)
{
    x -= subtrahend.x;
    y -= subtrahend.y;
    z -= subtrahend.z;
    return *this;
}

Vec3f & Vec3f::operator*=(float const operand)
{
    x *= operand;
    y *= operand;
    z *= operand;
    return *this;
}

Vec3f & Vec3f::operator/=(float const divisor)
{
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}

} // namespace gel