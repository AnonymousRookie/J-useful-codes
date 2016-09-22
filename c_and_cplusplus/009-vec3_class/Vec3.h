/************************************************************************
* CREATED TIME: 2016-9-22 17:26:44
* LAST MODIFIED TIME: 2016-9-22 17:26:44
* DESCRIPTION: 三维向量类
* BY: 357688981@qq.com
************************************************************************/

#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include <cmath>
/**
 * Util macro for const float such as epsilon, small float and float precision tolerance.
 */
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_EPSILON                0.000001f

class Vec3
{
public:
    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vec3(float xx, float yy, float zz): x(xx), y(yy), z(zz) {}

    Vec3(const float* array) {
        set(array);
    }

    /**
     * Constructs a vector that describes the direction between the specified points.
     *
     * @param p1 The first point.
     * @param p2 The second point.
     */
    Vec3(const Vec3& p1, const Vec3& p2) {
        set(p1, p2);
    }

    /**
     * Constructs a new vector that is a copy of the specified vector.
     *
     * @param copy The vector to copy.
     */
    Vec3(const Vec3& copy) {
        set(copy);
    }

    /**
     * Destructor.
     */
    ~Vec3() {}

public:
    inline void Vec3::set(float xx, float yy, float zz);

    inline void Vec3::set(const float* array);

    inline void Vec3::set(const Vec3& v);

    inline void Vec3::set(const Vec3& p1, const Vec3& p2);

    inline void Vec3::setZero();

public:
    /**
     * Returns the angle (in radians) between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     *
     * @return The angle between the two vectors (in radians).
     */
    static float angle(const Vec3& v1, const Vec3& v2);


    /**
     * Adds the elements of the specified vector to this one.
     *
     * @param v The vector to add.
     */
    inline void add(const Vec3& v);


   /**
    * Adds the elements of this vector to the specified values.
    *
    * @param xx The add x coordinate.
    * @param yy The add y coordinate.
    * @param zz The add z coordinate.
    */
    inline void add(float xx, float yy, float zz);

    /**
     * Adds the specified vectors and stores the result in dst.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst A vector to store the result in.
     */
    static void add(const Vec3& v1, const Vec3& v2, Vec3* dst);

    /**
     * Returns the distance between this vector and v.
     *
     * @param v The other vector.
     *
     * @return The distance between this vector and v.
     *
     * @see distanceSquared
     */
    float distance(const Vec3& v) const;

    /**
     * Returns the squared distance between this vector and v.
     *
     * When it is not necessary to get the exact distance between
     * two vectors (for example, when simply comparing the
     * distance between different vectors), it is advised to use
     * this method instead of distance.
     *
     * @param v The other vector.
     *
     * @return The squared distance between this vector and v.
     *
     * @see distance
     */
    float distanceSquared(const Vec3& v) const;

    /**
     * Returns the dot product of this vector and the specified vector.
     *
     * @param v The vector to compute the dot product with.
     *
     * @return The dot product.
     */
    float dot(const Vec3& v) const;

    /**
     * Returns the dot product between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     *
     * @return The dot product between the vectors.
     */
    static float dot(const Vec3& v1, const Vec3& v2);
    /**
     * Subtracts this vector and the specified vector as (this - v)
     * and stores the result in this vector.
     *
     * @param v The vector to subtract.
     */
    inline void subtract(const Vec3& v);
    /**
     * Negates this vector.
     */
    inline void negate();
    /**
     * Scales all elements of this vector by the specified value.
     *
     * @param scalar The scalar value.
     */
    inline void scale(float scalar);
    /**
     * Computes the length of this vector.
     *
     * @return The length of the vector.
     *
     * @see lengthSquared
     */
    inline float length() const;

    /**
     * Returns the squared length of this vector.
     *
     * When it is not necessary to get the exact length of a
     * vector (for example, when simply comparing the lengths of
     * different vectors), it is advised to use this method
     * instead of length.
     *
     * @return The squared length of the vector.
     *
     * @see length
     */
    inline float lengthSquared() const;
    /**
     * Subtracts the specified vectors and stores the result in dst.
     * The resulting vector is computed as (v1 - v2).
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst The destination vector.
     */
    static void subtract(const Vec3& v1, const Vec3& v2, Vec3* dst);
    /**
     * Calculates the sum of this vector with the given vector.
     *
     * Note: this does not modify this vector.
     *
     * @param v The vector to add.
     * @return The vector sum.
     */
    inline const Vec3 operator+(const Vec3& v) const;

    /**
     * Adds the given vector to this vector.
     *
     * @param v The vector to add.
     * @return This vector, after the addition occurs.
     */
    inline Vec3& operator+=(const Vec3& v);

    /**
     * Calculates the difference of this vector with the given vector.
     *
     * Note: this does not modify this vector.
     *
     * @param v The vector to subtract.
     * @return The vector difference.
     */
    inline const Vec3 operator-(const Vec3& v) const;

    /**
     * Subtracts the given vector from this vector.
     *
     * @param v The vector to subtract.
     * @return This vector, after the subtraction occurs.
     */
    inline Vec3& operator-=(const Vec3& v);

    /**
     * Calculates the negation of this vector.
     *
     * Note: this does not modify this vector.
     *
     * @return The negation of this vector.
     */
    inline const Vec3 operator-() const;

    /**
     * Calculates the scalar product of this vector with the given value.
     *
     * Note: this does not modify this vector.
     *
     * @param s The value to scale by.
     * @return The scaled vector.
     */
    inline const Vec3 operator*(float s) const;

    /**
     * Scales this vector by the given value.
     *
     * @param s The value to scale by.
     * @return This vector, after the scale occurs.
     */
    inline Vec3& operator*=(float s);

    /**
     * Returns the components of this vector divided by the given constant
     *
     * Note: this does not modify this vector.
     *
     * @param s the constant to divide this vector with
     * @return a smaller vector
     */
    inline const Vec3 operator/(float s) const;


    /**
     * Normalizes this vector.
     *
     * This method normalizes this Vec3 so that it is of
     * unit length (in other words, the length of the vector
     * after calling this method will be 1.0f). If the vector
     * already has unit length or if the length of the vector
     * is zero, this method does nothing.
     *
     * @return This vector, after the normalization occurs.
     */
    void normalize();

    /**
     * Get the normalized vector.
     */
    Vec3 getNormalized() const;

private:
    float x;
    float y;
    float z;
};

#include "Vec3.inl"

#endif  // MATH_VEC3_H