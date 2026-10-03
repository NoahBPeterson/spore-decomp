// Axis-aligned bounding box helpers and component-wise Vector3 min/max.
// Built without optimization: /Od /Ob1 /arch:SSE /fp:fast (inlined operator[] with constant index).

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    inline float& operator[](int i) { return (&x)[i]; }
    inline const float& operator[](int i) const { return (&x)[i]; }
};

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

struct BoundingBox {
    Vector3 lo;
    Vector3 hi;
    inline bool IsEmpty() const { return lo[0] > hi[0]; }
    void Extend(const Vector3& p);
};

// @ 0x0041bd50
void BoundingBox::Extend(const Vector3& p)
{
    if (IsEmpty()) {
        // empty box: seed with the point
        lo = p;
        hi = p;
        return;
    }
    if (lo[0] > p[0]) lo[0] = p[0];
    else if (hi[0] < p[0]) hi[0] = p[0];
    if (lo[1] > p[1]) lo[1] = p[1];
    else if (hi[1] < p[1]) hi[1] = p[1];
    if (lo[2] > p[2]) lo[2] = p[2];
    else if (hi[2] < p[2]) hi[2] = p[2];
}

// @ 0x0041bf30
float MaxComponent(const Vector3* v)
{
    return Max(Max((*v)[0], (*v)[1]), (*v)[2]);
}

// @ 0x0041bfb0
Vector3 MaxVec(const Vector3& a, const Vector3& b)
{
    return Vector3(Max(a[0], b[0]), Max(a[1], b[1]), Max(a[2], b[2]));
}

// @ 0x0041c0c0
Vector3 MinVec(const Vector3& a, const Vector3& b)
{
    return Vector3(Min(a[0], b[0]), Min(a[1], b[1]), Min(a[2], b[2]));
}
