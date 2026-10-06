// slice s0050aac0 -- 0x50aac0 (4542 bytes): UV chart atlas packer (/Od module).
//
// Pads every chart rectangle, turns charts so they are taller than wide, sorts them, packs them
// into horizontal shelves no wider than 1.1 * sqrt(total area), interlocks the shelves pairwise
// (shelf 2k+1 is slid down into the gaps of shelf 2k, whose chart order is reversed), then moves
// every chart's UVs (and its extra points) into place and normalizes the atlas to [0,1].
// The class/method names are placeholders (no symbol in the image); the layout is from the asm:
//   this+0x30  eastl::vector<Vector2>   per-vertex UVs
//   this+0x80  eastl::vector<uint32_t>  triangle vertex indices (3 per triangle)
//   this+0xe4  eastl::vector<UVChart*>  charts
// Flags: /Od /Ob1 /Oi /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the locals' dtors get no EH
// frame; /Oi is what turns sqrtf into the static-CRT _CIsqrt call).
// Status: complete. Same instruction stream as the original once stack-slot offsets are
// masked (26 calls in the same order, consistent one-to-one slot mapping); not byte-exact
// because the /Od frame is 0x864 instead of 0x914 (local slot order/holes) and the empty
// comparator temporary is zeroed with xor+mov instead of `mov byte ptr [t],0`.
#include "types.h"
#include <math.h>

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float a, float b) { x = a; y = b; }
    float& operator[](int i) { return (&x)[i]; }
};
Vector2& operator+=(Vector2& a, const Vector2& b);                   // 0x0050E570
Vector2& operator*=(Vector2& a, const float& s);                      // 0x0050D020

namespace eastl {

struct sp_vector_allocator {
    sp_vector_allocator() {}
    sp_vector_allocator(const sp_vector_allocator& x);               // 0x00429360
};

template <class T> struct less {
    bool operator()(const T& a, const T& b) const { return a < b; }
};

template <class T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }

template <class T> inline void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T> inline void iter_swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <class T> inline void reverse(T* first, T* last)
{
    for (; first < --last; ++first)
        eastl::iter_swap(first, last);
}

template <class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <class T> void quick_sort(T* first, T* last);               // 0x0050F0D0 (uint32_t)
template <class T> inline void sort(T* first, T* last) { quick_sort(first, last); }
template <class T, class C> void quick_sort(T* first, T* last, C compare);  // 0x0050EBE0 (UVChart*)
template <class T, class C> inline void sort(T* first, T* last, C compare) { quick_sort(first, last, compare); }
template <class T> T* unique(T* first, T* last);                     // 0x0050E4B0 (uint32_t)

template <class T> class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    vector(const sp_vector_allocator& allocator = sp_vector_allocator())
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(allocator) {}
    vector(const vector& x);                                         // 0x0050D440 (UVChart*)
    ~vector()
    {
        destruct(mpBegin, mpEnd);
        DoFree();
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return *(mpBegin + n); }
    void reserve(unsigned int n);                                    // 0x004E0880
    void push_back(const T& value);                                  // 0x00454860 (uint32_t)
    T* erase(T* first, T* last);                                     // 0x004769B0 (uint32_t)
    void clear() { erase(mpBegin, mpEnd); }
    void DoFree();                                                   // 0x00425990
};

template <class T, int N> class fixed_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[(N * sizeof(T)) / 4];

    fixed_vector();                                                  // 0x0041CFE0 (UVChart*, 16)
    fixed_vector(unsigned int n);                                    // 0x0050CEC0 (UVShelf, 16)
    ~fixed_vector();                                                 // 0x004209B0 / 0x0050E290
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return *(mpBegin + n); }
    void push_back(const T& value);                                  // 0x0050E410 (UVShelf)
};

} // namespace eastl

struct UVChartPoint {
    uint32_t pad00[3];
    Vector2 mUV;                                // +0xc
};

struct UVChart {
    uint32_t pad00[2];
    eastl::vector<uint32_t> mTriangles;         // +0x8  triangle numbers
    uint32_t pad18[(0x44 - 0x18) / 4];
    eastl::vector<UVChartPoint> mPoints;        // +0x44
    uint32_t pad54;
    float mLeft;                                // +0x58
    float mRight;                               // +0x5c
    float mBottom;                              // +0x60
    float mTop;                                 // +0x64
    uint32_t mFlags;                            // +0x68  bit 0: rotated by 90 degrees
    void Rotate();                                                   // 0x0050BC80
};

struct UVChartCompare {
    bool operator()(const UVChart* a, const UVChart* b) const;
};

struct UVShelf {
    eastl::fixed_vector<UVChart*, 16> mCharts;  // +0x0
    float mWidth;                               // +0x58
    float mHeight;                              // +0x5c
    float mOffset;                              // +0x60
    UVShelf() { mWidth = 0.0f; mHeight = 0.0f; mOffset = 0.0f; }
    void Add(UVChart* chart, float width);                           // 0x0050BD10
};

class cUVAtlas {
public:
    uint32_t pad00[0x30 / 4];
    eastl::vector<Vector2> mUVs;                // +0x30
    uint32_t pad40[(0x80 - 0x40) / 4];
    eastl::vector<uint32_t> mIndices;           // +0x80
    uint32_t pad90[(0xe4 - 0x90) / 4];
    eastl::vector<UVChart*> mCharts;            // +0xe4

    void PackCharts(float padding);
};

// @ 0x0050aac0
void cUVAtlas::PackCharts(float padding)
{
    unsigned int chartCount = mCharts.size();
    float totalArea = 0.0f;
    unsigned int i;
    for (i = 0; i < chartCount; ++i) {
        UVChart* chart = mCharts[i];
        chart->mRight += padding;
        chart->mLeft -= padding;
        chart->mTop += padding;
        chart->mBottom -= padding;
        float width = chart->mRight - chart->mLeft;
        float height = chart->mTop - chart->mBottom;
        totalArea += width * height;
        if (width > height) {
            chart->Rotate();
            eastl::swap(width, height);
        }
    }

    float side = sqrtf(totalArea);
    float slack = 1.1f;

    // Fill shelves left to right; a chart that does not fit makes the rest of the list fill
    // the current shelf first, then a new shelf is started.
    eastl::vector<UVChart*> charts(mCharts);
    eastl::sort(charts.begin(), charts.end(), UVChartCompare());
    eastl::fixed_vector<UVShelf, 16> shelves(1);
    UVShelf* shelf = &shelves[0];
    unsigned int index = 0;
    while (index < charts.size()) {
        UVChart* chart = charts[index];
        while (chart == 0 && index < charts.size() - 1) {
            ++index;
            chart = charts[index];
        }
        if (chart == 0)
            break;
        float width = chart->mRight - chart->mLeft;
        if (shelf->mWidth + width < side * slack) {
            shelf->Add(chart, width);
            ++index;
        } else {
            for (unsigned int j = index + 1; j < charts.size(); ++j) {
                UVChart* other = charts[j];
                if (other != 0) {
                    float otherWidth = other->mRight - other->mLeft;
                    if (shelf->mWidth + otherWidth < side * slack) {
                        shelf->Add(other, otherWidth);
                        charts[j] = 0;
                    }
                }
            }
            shelves.push_back(UVShelf());
            unsigned int shelfCount = shelves.size();
            shelf = &shelves[shelfCount - 1];
        }
    }

    // Interlock shelf pairs: the odd shelf is moved down as far as its charts allow.
    float maxWidth = 0.0f;
    float totalHeight = 0.0f;
    for (i = 0; i < shelves.size() / 2; ++i) {
        UVShelf* lower = &shelves[i * 2];
        UVShelf* upper = &shelves[i * 2 + 1];
        eastl::reverse(lower->mCharts.begin(), lower->mCharts.end());
        float offset = -(lower->mHeight + upper->mHeight);
        unsigned int lowerIndex = 0;
        unsigned int upperIndex = 0;
        float lowerUsed = 0.0f;
        float upperUsed = 0.0f;
        while (lowerIndex < lower->mCharts.size() && upperIndex < upper->mCharts.size()) {
            UVChart* lowerChart = lower->mCharts[lowerIndex];
            UVChart* upperChart = upper->mCharts[upperIndex];
            float lowerWidth = lowerChart->mRight - lowerChart->mLeft;
            float lowerHeight = lowerChart->mTop - lowerChart->mBottom;
            float upperWidth = upperChart->mRight - upperChart->mLeft;
            float upperHeight = upperChart->mTop - upperChart->mBottom;
            float needed = lowerHeight;
            float room = lower->mHeight + upper->mHeight - upperHeight + offset;
            if (needed > room)
                offset += needed - room;
            float lowerLeft = lowerWidth - lowerUsed;
            float upperLeft = upperWidth - upperUsed;
            if (upperLeft > lowerLeft) {
                ++lowerIndex;
                lowerUsed = 0.0f;
                upperUsed += lowerLeft;
            } else if (lowerLeft > upperLeft) {
                ++upperIndex;
                upperUsed = 0.0f;
                lowerUsed += upperLeft;
            } else {
                ++lowerIndex;
                ++upperIndex;
                lowerUsed = 0.0f;
                upperUsed = 0.0f;
            }
        }
        upper->mOffset = offset;
        maxWidth = eastl::max(eastl::max(upper->mWidth, lower->mWidth), maxWidth);
        totalHeight += eastl::max(lower->mHeight + upper->mHeight + upper->mOffset, lower->mHeight);
    }
    if (shelves.size() & 1) {
        unsigned int shelfCount = shelves.size();
        UVShelf* last = &shelves[shelfCount - 1];
        maxWidth = eastl::max(last->mWidth, maxWidth);
        totalHeight += last->mHeight;
    }

    // Move every chart into place and normalize to [0,1].
    eastl::vector<uint32_t> vertices;
    float scale = 1.0f / eastl::max(maxWidth, totalHeight);
    float y = 0.0f;
    for (i = 0; i < shelves.size(); ++i) {
        UVShelf* row = &shelves[i];
        float x = 0.0f;
        for (unsigned int k = 0; k < row->mCharts.size(); ++k) {
            UVChart* chart = row->mCharts[k];
            float width = chart->mRight - chart->mLeft;
            float height = chart->mTop - chart->mBottom;
            float dx = x - chart->mLeft;
            float dy = y - chart->mBottom;
            if (i & 1)
                dy += row->mHeight - height + row->mOffset;
            Vector2 delta(dx, dy);

            vertices.clear();
            vertices.reserve(chart->mTriangles.size() * 3);
            unsigned int t;
            for (t = 0; t < chart->mTriangles.size(); ++t) {
                uint32_t tri = chart->mTriangles[t];
                vertices.push_back(mIndices[tri * 3]);
                vertices.push_back(mIndices[tri * 3 + 1]);
                vertices.push_back(mIndices[tri * 3 + 2]);
            }
            eastl::sort(vertices.begin(), vertices.end());
            vertices.erase(eastl::unique(vertices.begin(), vertices.end()), vertices.end());

            bool rotated = (chart->mFlags & 1) ? true : false;
            float flip = chart->mRight + chart->mLeft;
            for (uint32_t* it = vertices.begin(); it != vertices.end(); ++it) {
                Vector2& uv = mUVs[*it];
                if (rotated) {
                    float u = uv[1];
                    uv[1] = uv[0];
                    uv[0] = flip - u;
                }
                uv += delta;
                uv *= scale;
            }
            for (t = 0; t < chart->mPoints.size(); ++t) {
                Vector2& uv = chart->mPoints[t].mUV;
                if (rotated) {
                    float u = uv[1];
                    uv[1] = uv[0];
                    uv[0] = flip - u;
                }
                uv += delta;
                uv *= scale;
            }

            chart->mLeft += dx;
            chart->mLeft *= scale;
            chart->mRight += dx;
            chart->mRight *= scale;
            chart->mBottom += dy;
            chart->mBottom *= scale;
            chart->mTop += dy;
            chart->mTop *= scale;
            chart->mFlags &= ~1u;
            x += width;
        }
        y += row->mHeight + row->mOffset;
    }
}
