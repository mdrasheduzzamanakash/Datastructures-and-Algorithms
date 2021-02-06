#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

struct point2d
{
    double x, y;
    point2d() {}
    point2d(double x, double y) : x(x), y(y) {}
    point2d &operator+=(const point2d &t)
    {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d &operator-=(const point2d &t)
    {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d &operator*=(double t)
    {
        x *= t;
        y *= t;
        return *this;
    }
    point2d &operator/=(double t)
    {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const
    {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const
    {
        return point2d(*this) -= t;
    }
    point2d operator*(double t) const
    {
        return point2d(*this) *= t;
    }
    point2d operator/(double t) const
    {
        return point2d(*this) /= t;
    }
    double dot(point2d a, point2d b)
    {
        return a.x * b.x + a.y * b.y;
    }
    double norm(point2d a)
    {
        return dot(a, a);
    }
    double abs(point2d a)
    {
        return sqrt(norm(a));
    }
    double proj(point2d a, point2d b)
    {
        return dot(a, b) / abs(b);
    }
    double angle(point2d a, point2d b)
    {
        return acos(dot(a, b) / abs(a) / abs(b));
    }
    double cross(point2d a, point2d b)
    {
        return a.x * b.y - a.y * b.x;
    }
    point2d intersect(point2d a1, point2d d1, point2d a2, point2d d2)
    {
        return a1 + (cross(a2 - a1, d2) / cross(d1, d2)) * d1;
    }
};
point2d operator*(double a, point2d b)
{
    return b * a;
};
struct point3d
{
    double x, y, z;
    point3d() {}
    point3d(double x, double y, double z) : x(x), y(y), z(z) {}
    point3d &operator+=(const point3d &t)
    {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    point3d &operator-=(const point3d &t)
    {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    point3d &operator*=(double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point3d &operator/=(double t)
    {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    point3d operator+(const point3d &t) const
    {
        return point3d(*this) += t;
    }
    point3d operator-(const point3d &t) const
    {
        return point3d(*this) -= t;
    }
    point3d operator*(double t) const
    {
        return point3d(*this) *= t;
    }
    point3d operator/(double t) const
    {
        return point3d(*this) /= t;
    }
    double dot(point3d a, point3d b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    point3d cross(point3d a, point3d b)
    {
        return point3d(a.y * b.z - a.z * b.y,
                       a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x);
    }
    double cross(point2d a, point2d b)
    {
        return a.x * b.y - a.y * b.x;
    }
    double triple(point3d a, point3d b, point3d c)
    {
        return dot(a, cross(b, c));
    }
};
point3d operator*(double a, point3d b)
{
    return b * a;
}
// intersection of two lines
struct pt
{
    double x, y;
};

struct line
{
    double a, b, c;
};

double det(double a, double b, double c, double d)
{
    return a * d - b * c;
}

bool intersect(line m, line n, pt &res)
{
    double zn = det(m.a, m.b, n.a, n.b);
    if (abs(zn) < EPS)
        return false;
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return true;
}

bool parallel(line m, line n)
{
    return abs(det(m.a, m.b, n.a, n.b)) < EPS;
}

bool equivalent(line m, line n)
{
    return abs(det(m.a, m.b, n.a, n.b)) < EPS && abs(det(m.a, m.c, n.a, n.c)) < EPS && abs(det(m.b, m.c, n.b, n.c)) < EPS;
}

int main()
{
    
}