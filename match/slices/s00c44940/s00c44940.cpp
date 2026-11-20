// Slice s00c44940: appends a 3-float point to a global vector (EASTL vector layout:
// begin / end / capacity), falling back to the out-of-line insert when it is full.

#include <new>

struct Point3_s00c4_4940 {
    float x, y, z;

    Point3_s00c4_4940(const Point3_s00c4_4940& o) : x(o.x), y(o.y), z(o.z) {}
};

struct PointVector_s00c4_4940 {
    Point3_s00c4_4940* mpBegin;     // +0x0
    Point3_s00c4_4940* mpEnd;       // +0x4
    Point3_s00c4_4940* mpCapacity;  // +0x8

    void DoInsertValue(Point3_s00c4_4940* position, const Point3_s00c4_4940& value);  // 0x004b5ad0

    void push_back(const Point3_s00c4_4940& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) Point3_s00c4_4940(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

extern PointVector_s00c4_4940 g_PointList_s00c4_4940;  // 0x0168e81c

// @ 0x00c44940
void AddPoint_s00c4_4940(Point3_s00c4_4940 p)
{
    g_PointList_s00c4_4940.push_back(p);
}
