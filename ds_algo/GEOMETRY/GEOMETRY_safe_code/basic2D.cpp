#include <bits/stdc++.h>
using namespace std;
typedef double T;
struct pt
{
    T x, y;
    pt operator+(pt p) { return {x + p.x, y + p.y}; }
    pt operator-(pt p) { return {x - p.x, y - p.y}; }
    pt operator*(T d) { return {x * d, y * d}; }
    pt operator*(pt p) { return {x * p.x - y * p.y, x * p.y + p.x * y}; }
    pt operator/(pt p) { return {(x * p.x + y * p.y) / (p.x * p.x + p.y * p.y), (p.x * y - x * p.y) / (p.x * p.x + p.y * p.y)}; }
    pt operator/(T d) { return {x / d, y / d}; }
};
T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }
T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); } // which side of AB pt c is
bool isPerp(pt v, pt w) { return dot(v, w) == 0; }
bool operator==(pt a, pt b) { return a.x == b.x && a.y == b.y; }
bool operator!=(pt a, pt b) { return !(a == b); }
T sq(pt p) { return p.x * p.x + p.y * p.y; }
double abs(pt p) { return sqrt(sq(p)); }
ostream &operator<<(ostream &os, pt p) { return os << "(" << p.x << "," << p.y << ")"; }
template <typename T>
int sgn(T x) { return (T(0) < x) - (x < (T(0))); }
bool inAngle(pt a, pt b, pt c, pt p)
{
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0)
        swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}
double angle(pt a, pt b) { return acos(dot(a, b) / abs(a) / abs(b)); }
double orientedAngle(pt a, pt b, pt c)
{
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    else
        return 2 * M_PI - angle(b - a, c - a);
}
bool isConvex(vector<pt> p)
{
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++)
    {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0)
            hasPos = true;
        if (o < 0)
            hasNeg = true;
    }
    return !(hasPos && hasNeg);
}
bool half(pt p)
{ //true if in upper half
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<pt> &v)
{ // sort the poits
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w));
    });
}
void polarSortAround(pt o, vector<pt> &v)
{
    sort(v.begin(), v.end(), [&o](pt v, pt w) {
        return make_tuple(half(v - o), 0, sq(v - o)) <
               make_tuple(half(w - o), cross(v - o, w - o), sq(w - o));
    });
}
// Transformations
pt translate(pt v, pt p) { return p + v; }
pt scale(pt c, double factor, pt p) { return c + (p - c) * factor; }
pt rot(pt p, double a) { return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)}; }
pt perp(pt p) { return {-p.y, p.x}; }
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) { return fp + (r - p) * (fq - fp) / (q - p); }

struct line
{
    pt v;
    T c;
    line(pt v, T c) : v(v), c(c) {}
    line(T a, T b, T c) : v({b, -a}), c(c) {}
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}
    T side(pt p) { return cross(v, p) - c; }
    double dist(pt p) { return abs(side(p)) / abs(v); }
    double sqDist(pt p) { return side(p) * side(p) / (double)sq(v); }
    line perpThrough(pt p) { return {p, p + perp(v)}; }
    line translate(pt t) { return {v, c + cross(v, t)}; }
    line shiftLeft(double dist) { return {v, c + dist * abs(v)}; } // shifting upward
    pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
    pt refl(pt p) { return p - perp(v) * 2 * side(p) / sq(v); }
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
};
bool inter(line l1, line l2, pt &out)
{
    T d = cross(l1.v, l2.v);
    if (d == 0)
        return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}
line bisector(line l1, line l2, bool interior)
{
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    double sign = interior ? 1 : -1;
    return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign, l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign};
}
bool inDisk(pt a, pt b, pt p) { return dot(a - p, b - p) <= 0; }
bool onSegment(pt a, pt b, pt p) { return orient(a, b, p) == 0 && inDisk(a, b, p); }
bool properInter(pt a, pt b, pt c, pt d, pt &out)
{
    double oa = orient(c, d, a),
           ob = orient(c, d, b),
           oc = orient(a, b, c),
           od = orient(a, b, d);
    if (oa * ob < 0 && oc * od < 0)
    {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}
// getting all intersection pointsstruct cmpX {
struct cmpX
{
    bool operator()(pt a, pt b)
    {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};
set<pt, cmpX> inters(pt a, pt b, pt c, pt d)
{
    pt out;
    if (properInter(a, b, c, d, out))
        return {out};
    set<pt, cmpX> s;
    if (onSegment(c, d, a))
        s.insert(a);
    if (onSegment(c, d, b))
        s.insert(b);
    if (onSegment(a, b, c))
        s.insert(c);
    if (onSegment(a, b, d))
        s.insert(d);
    return s;
}
double segPoint(pt a, pt b, pt p)
{ //dist from a point to segment
    if (a != b)
    {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b))
            return l.dist(p);
    }
    return min(abs(p - a), abs(p - b));
}
double segSeg(pt a, pt b, pt c, pt d)
{
    pt dummy;
    if (properInter(a, b, c, d, dummy))
        return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d),
                segPoint(c, d, a), segPoint(c, d, b)});
}
int main()
{
    pt a{2, 0}, b{0, 2};
    vector<pt> v = {{-1, 2}, {4, 6}, {2, 3}, {3, -3}, {-2, -3}};
    polarSortAround({0, 0}, v);
    for (auto i : v)
        cout << i << endl;
}