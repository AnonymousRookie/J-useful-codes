/************************************************************************
* CREATED TIME: 2016-9-4 19:47:52
* LAST MODIFIED TIME: 2016-9-4 20:50:46
* DESCRIPTION: 二维向量类
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
/**
 * Defines a 2-element floating point vector.
 */
class Vec2
{
public:
    float x;  // The x coordinate.
    float y;  // The y coordinate.

    Vec2(): x(0.0f), y(0.0f) {}

    Vec2(float xx, float yy): x(xx), y(yy) {}

    Vec2(const float* array) {
        // MY_ASSERT(array);
        x = array[0];
        y = array[1];
    }

    /**
     * Constructs a vector that describes the direction between the specified points.
     *
     * @param p1 The first point.
     * @param p2 The second point.
     */
    Vec2(const Vec2& p1, const Vec2& p2) {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }

    Vec2(const Vec2& copy) {
        this->x = copy.x;
        this->y = copy.y;
    }

    /**
     * Destructor.
     */
    ~Vec2() {}


    /**
     * Indicates whether this vector contains all zeros.
     *
     * @return true if this vector contains all zeros, false otherwise.
     */
    bool isZero() const{
        return x == 0.0f && y == 0.0f;
    }

    /**
     * Indicates whether this vector contains all ones.
     *
     * @return true if this vector contains all ones, false otherwise.
     */
    bool isOne() const{
        return x == 1.0f && y == 1.0f;
    }

    /**
     * Returns the angle (in radians) between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     *
     * @return The angle between the two vectors (in radians).
     */
    static float angle(const Vec2& v1, const Vec2& v2);

    /**
     * Adds the elements of the specified vector to this one.
     *
     * @param v The vector to add.
     */
    void add(const Vec2& v) {
        x += v.x;
        y += v.y;
    }

    /**
     * Adds the specified vectors and stores the result in dst.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst A vector to store the result in.
     */
    static void add(const Vec2& v1, const Vec2& v2, Vec2* dst);
    /**
     * Returns the distance between this vector and v.
     *
     * @param v The other vector.
     *
     * @return The distance between this vector and v.
     *
     * @see distanceSquared
     */
    float distance(const Vec2& v) const;

    /**
     * Returns the dot product of this vector and the specified vector.
     *
     * @param v The vector to compute the dot product with.
     *
     * @return The dot product.
     */
    float dot(const Vec2& v) const {
        return (x * v.x + y * v.y);
    }

    /** Calculates cross product of two points.
     @return float
     */
    inline float cross(const Vec2& other) const {
        return x*other.y - y*other.x;
    };
    /**
     * Returns the dot product between the specified vectors.
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     *
     * @return The dot product between the vectors.
     */
    static float dot(const Vec2& v1, const Vec2& v2);

    /**
     * Computes the length of this vector.
     *
     * @return The length of the vector.
     *
     * @see lengthSquared
     */
    float length() const;

    /**
     * Normalizes this vector.
     *
     * This method normalizes this Vec2 so that it is of
     * unit length (in other words, the length of the vector
     * after calling this method will be 1.0f). If the vector
     * already has unit length or if the length of the vector
     * is zero, this method does nothing.
     *
     * @return This vector, after the normalization occurs.
     */
    void normalize();

    /**
     Get the normalized vector.
     */
    Vec2 getNormalized() const;
    /**
     * Scales all elements of this vector by the specified value.
     *
     * @param scalar The scalar value.
     */
    void scale(float scalar) {
        x *= scalar;
        y *= scalar;
    }
    /**
     * Scales each element of this vector by the matching component of scale.
     *
     * @param scale The vector to scale by.
     */
    void scale(const Vec2& scale) {
        x *= scale.x;
        y *= scale.y;
    }
    /**
     * Rotates this vector by angle (specified in radians) around the given point.
     *
     * @param point The point to rotate around.
     * @param angle The angle to rotate by (in radians).
     */
    void rotate(const Vec2& point, float angle);

    /**
    * Sets the elements of this vector to zero.
    */
    inline void setZero() {
        x = y = 0.0f;
    }

    /**
     * Subtracts this vector and the specified vector as (this - v)
     * and stores the result in this vector.
     *
     * @param v The vector to subtract.
     */
    inline void subtract(const Vec2& v) {
        x -= v.x;
        y -= v.y;
    }

    /**
     * Subtracts the specified vectors and stores the result in dst.
     * The resulting vector is computed as (v1 - v2).
     *
     * @param v1 The first vector.
     * @param v2 The second vector.
     * @param dst The destination vector.
     */
    static void subtract(const Vec2& v1, const Vec2& v2, Vec2* dst);

    bool equals(const Vec2& target) const;

    /**
     * Calculates the sum of this vector with the given vector.
     *
     * Note: this does not modify this vector.
     *
     * @param v The vector to add.
     * @return The vector sum.
     */
    inline const Vec2 operator+(const Vec2& v) const {
        Vec2 result(*this);
        result.add(v);
        return result;
    }

    /**
     * Adds the given vector to this vector.
     *
     * @param v The vector to add.
     * @return This vector, after the addition occurs.
     */
    inline Vec2& operator+=(const Vec2& v) {
        add(v);
        return *this;
    }

    inline const Vec2 operator-(const Vec2& v) const {
        Vec2 result(*this);
        result.subtract(v);
        return result;
    }

    inline Vec2& operator-=(const Vec2& v) {
        subtract(v);
        return *this;
    }

    inline void Vec2::negate()
    {
        x = -x;
        y = -y;
    }
    /**
     * Calculates the negation of this vector.
     *
     * Note: this does not modify this vector.
     *
     * @return The negation of this vector.
     */
    inline const Vec2 operator-() const {
        Vec2 result(*this);
        result.negate();
        return result;
    }

    inline const Vec2 Vec2::operator*(float s) const
    {
        Vec2 result(*this);
        result.scale(s);
        return result;
    }

    inline Vec2& Vec2::operator*=(float s)
    {
        scale(s);
        return *this;
    }

    inline const Vec2 Vec2::operator/(const float s) const
    {
        return Vec2(this->x / s, this->y / s);
    }

    inline bool Vec2::operator<(const Vec2& v) const
    {
        if (x == v.x)
        {
            return y < v.y;
        }
        return x < v.x;
    }

    inline bool Vec2::operator>(const Vec2& v) const
    {
        if (x == v.x)
        {
            return y > v.y;
        }
        return x > v.x;
    }

    inline bool Vec2::operator==(const Vec2& v) const
    {
        return x==v.x && y==v.y;
    }

    inline bool Vec2::operator!=(const Vec2& v) const
    {
        return x!=v.x || y!=v.y;
    }
    /**
     returns true if Line A-B parallel with segment C-D
     */
    static bool isLineParallel(const Vec2& A, const Vec2& B,
                   const Vec2& C, const Vec2& D);

    /**
     @returns the angle in radians between this vector and the x axis
     */
    inline float getAngle() const {
        return atan2f(y, x);
    };
    /**
     @returns the angle in radians between two vector directions
     */
    float getAngle(const Vec2& other) const;
};


float Vec2::angle(const Vec2& v1, const Vec2& v2)
{
    float dz = v1.x * v2.y - v1.y * v2.x;
    return atan2f(fabsf(dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void Vec2::add(const Vec2& v1, const Vec2& v2, Vec2* dst)
{
    // MY_ASSERT(dst);
    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
}

float Vec2::distance(const Vec2& v) const
{
    float dx = v.x - x;
    float dy = v.y - y;

    return std::sqrt(dx * dx + dy * dy);
}

float Vec2::dot(const Vec2& v1, const Vec2& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

float Vec2::length() const
{
    return std::sqrt(x * x + y * y);
}

void Vec2::normalize()
{
    float n = x * x + y * y;
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
}

Vec2 Vec2::getNormalized() const
{
    Vec2 v(*this);
    v.normalize();
    return v;
}

void Vec2::rotate(const Vec2& point, float angle)
{
    float sinAngle = std::sin(angle);
    float cosAngle = std::cos(angle);

    if (point.isZero())
    {
        float tempX = x * cosAngle - y * sinAngle;
        y = y * cosAngle + x * sinAngle;
        x = tempX;
    }
    else
    {
        float tempX = x - point.x;
        float tempY = y - point.y;

        x = tempX * cosAngle - tempY * sinAngle + point.x;
        y = tempY * cosAngle + tempX * sinAngle + point.y;
    }
}

void Vec2::subtract(const Vec2& v1, const Vec2& v2, Vec2* dst)
{
    // MY_ASSERT(dst);
    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
}

bool Vec2::equals(const Vec2& target) const
{
    return (std::abs(this->x - target.x) < FLT_EPSILON)
        && (std::abs(this->y - target.y) < FLT_EPSILON);
}

// cross product of 2 vector. A->B X C->D
float crossProduct2Vector(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D)
{
    return (D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y);
}

bool Vec2::isLineParallel(const Vec2& A, const Vec2& B,
                          const Vec2& C, const Vec2& D)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }

    if (crossProduct2Vector(A, B, C, D) == 0)
    {
        // line overlap
        if (crossProduct2Vector(C, D, C, A) == 0 || crossProduct2Vector(A, B, C, A) == 0)
        {
            return false;
        }

        return true;
    }

    return false;
}

float Vec2::getAngle(const Vec2& other) const
{
    Vec2 a2 = getNormalized();
    Vec2 b2 = other.getNormalized();
    float angle = atan2f(a2.cross(b2), a2.dot(b2));
    if (std::abs(angle) < FLT_EPSILON) return 0.f;
    return angle;
}

int main()
{

    return 0;
}