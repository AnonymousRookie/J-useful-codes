/************************************************************************
* CREATED TIME: 2016-9-22 17:26:44
* LAST MODIFIED TIME: 2016-9-22 17:26:44
* DESCRIPTION: 三维向量类
* BY: 357688981@qq.com
************************************************************************/

#include "Vec3.h"

float Vec3::angle(const Vec3& v1, const Vec3& v2)
{
    float dx = v1.y * v2.z - v1.z * v2.y;
    float dy = v1.z * v2.x - v1.x * v2.z;
    float dz = v1.x * v2.y - v1.y * v2.x;

    return std::atan2(std::sqrt(dx * dx + dy * dy + dz * dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void Vec3::add(const Vec3& v1, const Vec3& v2, Vec3* dst)
{
    // MY_ASSERT(dst);
    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
    dst->z = v1.z + v2.z;
}

float Vec3::distance(const Vec3& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

float Vec3::distanceSquared(const Vec3& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;
    float dz = v.z - z;

    return (dx * dx + dy * dy + dz * dz);
}

float Vec3::dot(const Vec3& v) const
{
    return (x * v.x + y * v.y + z * v.z);
}

float Vec3::dot(const Vec3& v1, const Vec3& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

void Vec3::normalize()
{
    float n = x * x + y * y + z * z;
    // Already normalized.
    if (n == 1.0f)
        return;

    n = std::sqrt(n);
    // Too close to zero.
    if (n < MATH_TOLERANCE)
        return;

    n = 1.0f / n;
    x *= n;
    y *= n;
    z *= n;
}

Vec3 Vec3::getNormalized() const
{
    Vec3 v(*this);
    v.normalize();
    return v;
}
