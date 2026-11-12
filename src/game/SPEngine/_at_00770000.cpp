// src/game/SPEngine/_at_00770000.cpp -- migrated from slice(s) s0077f020, s0077c8b0, s0077bc10, s0077a160, s00779f20, s00778fd0, s007776f0, s00776730, s00775760, s00773f60, s00770320, s0076fdc0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00770000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include <string.h>
#include <new>
#include <intrin.h>
#include "rw/graphics/ActiveState.h"
#include "rw/graphics/CompiledState.h"
#include "SP/cShaderBase.h"
#include "SP/cTextureInstance.h"
#include "SP/cViewer.h"
#include "SP/cILayer.h"
#include "EA/RefCountTemplate.h"
#include <math.h>

// ---- items of slice s0076fdc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SortElem {
    int f0, f1, f2, f3, f4;
};
typedef bool (__cdecl *SortCompare)(const SortElem&, const SortElem&);
struct Elem30 {
    __m128 v;
    float f4, f5, f6, f7, f8, f9;
    unsigned int tail0, tail1;
};
struct Big30 {
    __m128 v;
    unsigned int b[8];
};
// ---- items of slice s0076fdc0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
__declspec(noinline) void adjust_heap(SortElem* first, int topPosition, int heapSize, int position, SortElem value, SortCompare compare);  // 0x0076fef0 (stays in the slice: not this object's)

// ---- items of slice s00770320 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct __declspec(align(16)) Mat4 {
    __m128 r[4];        // rows; rows 0-2 are the 3x3 part, row 3 the translation
    Mat4() {}
    Mat4(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; }
    Mat4& operator=(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; return *this; }
};
static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }
static __forceinline __m128 SplatY(__m128 v) { return _mm_shuffle_ps(v, v, 0x55); }
static __forceinline __m128 SplatZ(__m128 v) { return _mm_shuffle_ps(v, v, 0xaa); }
static __forceinline __m128 SplatW(__m128 v) { return _mm_shuffle_ps(v, v, 0xff); }
static __forceinline __m128 MakeVec3(float x, float y, float z)
{
    __m128 vx = _mm_set1_ps(x);
    __m128 vy = _mm_set1_ps(y);
    __m128 vz = _mm_set1_ps(z);
    return _mm_unpacklo_ps(_mm_unpacklo_ps(vx, vz), _mm_unpacklo_ps(vy, vx));
}
static __forceinline __m128 MakeVec4(const __m128& x, const __m128& y, const __m128& z, const __m128& w)
{
    return _mm_shuffle_ps(_mm_shuffle_ps(x, y, 0x10), _mm_shuffle_ps(z, w, 0x32), 0x88);
}
static __forceinline __m128 MakeVec4u(float x, float y, float z, float w)
{
    return _mm_unpacklo_ps(_mm_unpacklo_ps(_mm_set1_ps(x), _mm_set1_ps(z)),
                           _mm_unpacklo_ps(_mm_set1_ps(y), _mm_set1_ps(w)));
}
static __forceinline __m128 Vec3Of(__m128 v)
{
    return _mm_shuffle_ps(_mm_shuffle_ps(v, v, 0x10), v, 0x28);
}
static __forceinline void Mul(Mat4& o, const Mat4& a, const Mat4& b)
{
    const __m128 one = _mm_set1_ps(1.0f);
    __m128 r0 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[0]), b.r[0]), _mm_mul_ps(SplatY(a.r[0]), b.r[1])),
                           _mm_mul_ps(SplatZ(a.r[0]), b.r[2]));
    __m128 r1 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[1]), b.r[0]), _mm_mul_ps(SplatY(a.r[1]), b.r[1])),
                           _mm_mul_ps(SplatZ(a.r[1]), b.r[2]));
    __m128 r2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[2]), b.r[0]), _mm_mul_ps(SplatY(a.r[2]), b.r[1])),
                           _mm_mul_ps(SplatZ(a.r[2]), b.r[2]));
    __m128 r3 = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[3]), b.r[0]),
                                                 _mm_mul_ps(SplatY(a.r[3]), b.r[1])),
                                      _mm_mul_ps(SplatZ(a.r[3]), b.r[2])),
                           _mm_mul_ps(one, b.r[3]));
    o.r[0] = r0; o.r[1] = r1; o.r[2] = r2; o.r[3] = r3;
}
static __forceinline void ScaleMat(Mat4& o, __m128 s)
{
    const __m128 z = _mm_setzero_ps();
    o.r[0] = _mm_shuffle_ps(_mm_shuffle_ps(z, s, 0x05), z, 0xe2);
    o.r[1] = _mm_shuffle_ps(_mm_shuffle_ps(z, s, 0x50), z, 0xe8);
    o.r[2] = _mm_shuffle_ps(z, _mm_shuffle_ps(z, s, 0xaf), 0x24);
    o.r[3] = z;
}
static __forceinline void TranslateMat(Mat4& o, __m128 t)
{
    ScaleMat(o, _mm_set1_ps(1.0f));
    o.r[3] = t;
}
static __forceinline void RotationMat(Mat4& o, __m128 q)
{
    const __m128 z = _mm_setzero_ps();
    const __m128 half = _mm_set1_ps(0.5f);
    __m128 q2 = _mm_mul_ps(_mm_set1_ps(1.41421354f), q);
    __m128 d = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(z, q2), q2), half);            // 0.5 - q*q
    __m128 xy = _mm_mul_ps(_mm_shuffle_ps(q2, q2, 0x09), q2);                  // (yx, zy, xz)
    __m128 wv = _mm_mul_ps(SplatW(q2), _mm_shuffle_ps(q2, q2, 0x12));          // (wz, wx, wy)
    __m128 p = _mm_add_ps(wv, xy);
    __m128 m = _mm_sub_ps(xy, wv);
    __m128 l = _mm_add_ps(_mm_shuffle_ps(d, d, 0x09), d);                      // 1 - 2(a^2 + b^2)
    o.r[0] = _mm_shuffle_ps(_mm_shuffle_ps(l, p, 0x01), m, 0x28);
    o.r[1] = _mm_shuffle_ps(_mm_shuffle_ps(m, l, 0x20), p, 0x18);
    o.r[2] = _mm_shuffle_ps(_mm_shuffle_ps(p, m, 0x12), l, 0x08);
    o.r[3] = z;
}
static __forceinline __m128 QuatMul(__m128 a, __m128 b)
{
    __m128 a3 = Vec3Of(a);
    __m128 b3 = Vec3Of(b);
    __m128 cross = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(b3, b3, 0x12), _mm_shuffle_ps(a3, a3, 0x09)),
                              _mm_mul_ps(_mm_shuffle_ps(b3, b3, 0x09), _mm_shuffle_ps(a3, a3, 0x12)));
    __m128 v = _mm_add_ps(cross, _mm_add_ps(_mm_mul_ps(SplatW(a), b3), _mm_mul_ps(SplatW(b), a3)));
    __m128 pr = _mm_mul_ps(b3, a3);
    __m128 dot = SplatX(_mm_add_ps(_mm_add_ps(_mm_shuffle_ps(pr, pr, 0x02), _mm_shuffle_ps(pr, pr, 0x01)), pr));
    __m128 w = _mm_sub_ps(_mm_mul_ps(SplatW(a), SplatW(b)), dot);
    return MakeVec4(SplatX(v), SplatY(v), SplatZ(v), w);
}
static __forceinline __m128 QuatConjugate(__m128 q)
{
    const __m128 z = _mm_setzero_ps();
    return MakeVec4(_mm_sub_ps(z, SplatX(q)), _mm_sub_ps(z, SplatY(q)), _mm_sub_ps(z, SplatZ(q)), SplatW(q));
}
static __forceinline bool AffineInverse(Mat4& o, const float* m)
{
    const __m128 Z = _mm_set1_ps(0.0f);
    const __m128 O = _mm_set1_ps(1.0f);
#define E(k) _mm_set1_ps(m[k])
#define MUL _mm_mul_ps
#define SUB _mm_sub_ps
#define ADD _mm_add_ps
    __m128 det = ADD(ADD(MUL(SUB(MUL(E(5), E(10)), MUL(E(6), E(9))), E(0)),
                         MUL(SUB(MUL(E(6), E(8)), MUL(E(10), E(4))), E(1))),
                     MUL(SUB(MUL(E(9), E(4)), MUL(E(5), E(8))), E(2)));
    if (_mm_movemask_ps(_mm_cmpeq_ps(det, Z)) == 0xf)
        return false;

    __m128 i32 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(5), E(2)), MUL(E(6), E(1))), E(12)),
                                    MUL(SUB(MUL(E(6), E(0)), MUL(E(4), E(2))), E(13))),
                                MUL(SUB(MUL(E(4), E(1)), MUL(E(5), E(0))), E(14))), det);
    __m128 i31 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(2)), MUL(E(14), E(1))), E(8)),
                                    MUL(SUB(MUL(E(14), E(0)), MUL(E(12), E(2))), E(9))),
                                MUL(SUB(MUL(E(12), E(1)), MUL(E(13), E(0))), E(10))), det);
    __m128 i30 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(10)), MUL(E(9), E(14))), E(4)),
                                    MUL(SUB(MUL(E(14), E(8)), MUL(E(10), E(12))), E(5))),
                                MUL(SUB(MUL(E(9), E(12)), MUL(E(13), E(8))), E(6))), det);
    __m128 i22 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), Z), MUL(E(5), Z)), E(12)),
                                    MUL(SUB(MUL(E(5), E(0)), MUL(E(4), E(1))), O)),
                                MUL(SUB(MUL(E(4), Z), MUL(E(0), Z)), E(13))), det);
    __m128 i21 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), O), MUL(E(13), Z)), E(8)),
                                    MUL(SUB(MUL(E(13), E(0)), MUL(E(12), E(1))), Z)),
                                MUL(SUB(MUL(E(12), Z), MUL(E(0), O)), E(9))), det);
    __m128 i20 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(8)), MUL(E(9), E(12))), Z),
                                    MUL(SUB(MUL(E(9), O), MUL(E(13), Z)), E(4))),
                                MUL(SUB(MUL(E(12), Z), MUL(E(8), O)), E(5))), det);
    __m128 i12 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(4), E(2)), MUL(E(6), E(0))), O),
                                    MUL(SUB(MUL(E(0), Z), MUL(E(4), Z)), E(14))),
                                MUL(SUB(MUL(E(6), Z), MUL(E(2), Z)), E(12))), det);
    __m128 i11 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(12), E(2)), MUL(E(14), E(0))), Z),
                                    MUL(SUB(MUL(E(0), O), MUL(E(12), Z)), E(10))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(2), O)), E(8))), det);
    __m128 i10 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), E(12)), MUL(E(14), E(8))), Z),
                                    MUL(SUB(MUL(E(8), O), MUL(E(12), Z)), E(6))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(10), O)), E(4))), det);
    __m128 i02 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), Z), MUL(E(6), Z)), E(13)),
                                    MUL(SUB(MUL(E(5), Z), MUL(E(1), Z)), E(14))),
                                MUL(SUB(MUL(E(6), E(1)), MUL(E(5), E(2))), O)), det);
    __m128 i01 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), O), MUL(E(14), Z)), E(9)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(1), O)), E(10))),
                                MUL(SUB(MUL(E(14), E(1)), MUL(E(13), E(2))), Z)), det);
    __m128 i00 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), O), MUL(E(14), Z)), E(5)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(9), O)), E(6))),
                                MUL(SUB(MUL(E(9), E(14)), MUL(E(13), E(10))), Z)), det);
#undef E
#undef MUL
#undef SUB
#undef ADD
    o.r[0] = _mm_unpacklo_ps(_mm_unpacklo_ps(i00, i02), _mm_unpacklo_ps(i01, i00));
    o.r[1] = _mm_unpacklo_ps(_mm_unpacklo_ps(i10, i12), _mm_unpacklo_ps(i11, i10));
    o.r[2] = _mm_unpacklo_ps(_mm_unpacklo_ps(i20, i22), _mm_unpacklo_ps(i21, i20));
    o.r[3] = _mm_unpacklo_ps(_mm_unpacklo_ps(i30, i32), _mm_unpacklo_ps(i31, i30));
    return true;
}
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o);          // @ 0x004098a0 (out of line, fld/fstp copy)
};
static __forceinline Vector3 operator/(Vector3 a, Vector3 b)
{
    return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
}
struct __declspec(align(16)) BoneXform {
    __m128  rot;        // +0x00 quaternion
    Vector3 pos;        // +0x10
    Vector3 scale;      // +0x1c
    float   f28, f2c;   // +0x28
};
struct __declspec(align(16)) BoneXform20 {
    __m128 rot;         // +0x00
    __m128 pos;         // +0x10
};
struct __declspec(align(16)) BakeRecord {
    char   c;               // +0x00  set once a hierarchy transform was applied
    float  a, b, d;         // +0x04  offset
    __m128 v[8];            // +0x10  forward matrix (v[0..3]) and inverse matrix (v[4..7])
    float  x, y, z;         // +0x90  scale
    float  w, p, q;         // +0x9c  inverse scale
    BakeRecord() {}
    BakeRecord(const BakeRecord& o);    // @ 0x0076f580
};
struct StridedArray {
    char  pad0[8];
    char* mpData;           // +0x08
    int   pad0c;
    int   mStride;          // +0x10
    void* At(int i);        // @ 0x011fda50: mpData + mStride * i
};
template <class T> struct VecView { T* mpBegin; };
struct BakeJob {
    StridedArray*   mpSource;   // +0x00 local bone transforms
    int             pad04, pad08;
    VecView<int>*   mpFlags;    // +0x0c push/pop flags per bone
    VecView<Mat4>*  mpBinds;    // +0x10 bind matrices per bone
};
extern "C" void MatrixToQuat(__m128* out, const Mat4* m, const __m128* eps);   // @ 0x0075ad80
struct Unk770320 {
    int          pad00;
    int          mCount;        // +0x04 bones
    int          pad08;
    int*         mpParent;      // +0x0c attachment slot per bone, or -1
    char*        mpSkin;        // +0x10 3x4 skin matrices, 0x30 bytes each
    BoneXform*   mpAttach;      // +0x14
    BakeRecord*  mpRecords;     // +0x18

    // @ 0x00770320
    int Method(int unused, BakeJob* job);
};
enum { kStackDepth = 64 };
// ---- items of slice s00770320 end

// ---- items of slice s00773f60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* malloc(unsigned bytes);
extern "C" void free(void* p);
extern "C" void* memcpy(void* dst, const void* src, unsigned n);
extern "C" void* memmove(void* dst, const void* src, unsigned n);
void insertion_sort(SortElem* first, SortElem* last, SortCompare compare);
void unguarded_insertion_sort(SortElem* first, SortElem* last, SortCompare compare);
void make_heap(SortElem* first, SortElem* last, SortCompare compare);
void sort_heap(SortElem* first, SortElem* last, SortCompare compare);
void partial_sort(SortElem* first, SortElem* middle, SortElem* last, SortCompare compare);
void introsort_loop(SortElem* first, SortElem* last, int depthLimit, SortCompare compare);
struct Unk770320_s0077_3f60 {
    unsigned int Method(unsigned int param_2, int* param_3);  // 0x00770320 (Unk770320::Method)
};
extern Unk770320_s0077_3f60 g_770320;
struct Idx2 {
    int m0;
    int m1;
    Idx2(int v) { m0 = v; m1 = v; }
};
struct VecIdx2 {
    Idx2* mpBegin;              // +0
    Idx2* mpEnd;                // +4
    Idx2* mpCapacity;           // +8
    void InsertN(Idx2* position, unsigned n, const Idx2& value);   // 0x00707D10
    void Erase(Idx2* first, Idx2* last);                           // 0x00D018D0
    void resize(unsigned n);
};
struct __declspec(align(16)) Blob30 {
    float m[12];
};
void Move30(Blob30* first, Blob30* last, Blob30* dst);             // 0x0076F990
void MoveB0(void* first, void* last, void* dst);                   // 0x0076FA30
struct Vec30 {
    Blob30* mpBegin;            // +0
    Blob30* mpEnd;              // +4
    Blob30* mpCapacity;         // +8
    void InsertN(Blob30* position, unsigned n, const Blob30& value);   // 0x007743B0
    void resize(unsigned n);
};
struct __declspec(align(16)) BlobB0 {
    char m[0xb0];
};
struct VecB0 {
    BlobB0* mpBegin;            // +0
    BlobB0* mpEnd;              // +4
    BlobB0* mpCapacity;         // +8
    void InsertN(BlobB0* position, unsigned n, const BlobB0& value);   // 0x007745D0
    void resize(unsigned n);
};
struct Mat34 {
    float m[12];
};
struct VecM34 {
    Mat34* mpBegin;             // +0
    Mat34* mpEnd;               // +4
    Mat34* mpCapacity;          // +8
    void InsertN(Mat34* position, unsigned n, const Mat34& value);     // 0x007747C0
    void Erase(Mat34* first, Mat34* last);                             // 0x009C69F0
    void resize(unsigned n);
};
#define INSERT_N_BODY(T)                                                   \
    T* begin = mpBegin;                                                        \
    T* end = mpEnd;                                                            \
    unsigned size = (unsigned)(end - begin);                                   \
    unsigned index = (unsigned)(position - begin);                             \
    unsigned after;                                                            \
    unsigned i;                                                                \
    if (n > (unsigned)(mpCapacity - end)) {                                    \
        /* EASTL grows to max(2 * size, size + n). */                          \
        unsigned newCapacity = size + n;                                       \
        unsigned grown = size * 2;                                             \
        if (grown == 0)                                                        \
            grown = 1;                                                         \
        if (newCapacity < grown)                                               \
            newCapacity = grown;                                               \
        T* newBuf = (T*)malloc(newCapacity * sizeof(T));                       \
        if (index)                                                             \
            memcpy(newBuf, begin, index * sizeof(T));                          \
        for (i = 0; i < n; ++i)                                                \
            memcpy(newBuf + index + i, &value, sizeof(T));                     \
        after = size - index;                                                  \
        if (after)                                                             \
            memcpy(newBuf + index + n, begin + index, after * sizeof(T));      \
        if (begin)                                                             \
            free(begin);                                                       \
        mpBegin = newBuf;                                                      \
        mpEnd = newBuf + size + n;                                             \
        mpCapacity = newBuf + newCapacity;                                     \
    } else {                                                                   \
        after = size - index;                                                  \
        if (after)                                                             \
            memmove(position + n, position, after * sizeof(T));                \
        for (unsigned i = 0; i < n; ++i)                                       \
            memcpy(position + i, &value, sizeof(T));                           \
        mpEnd = end + n;                                                       \
    }
struct Elt14 {
    int m[5];
};
Elt14* Copy14(const Elt14* first, const Elt14* last, Elt14* dst);         // 0x00951BF0
Elt14* Alloc14Range(unsigned n, const Elt14* first, const Elt14* last, const void* owner);  // 0x00774980
void Free14(Elt14* p);                                                    // 0x00F47380
struct Vec14Fixed {
    Elt14* mpBegin;             // +0x00
    Elt14* mpEnd;               // +0x04
    Elt14* mpCapacity;          // +0x08
    void* mUnkC;                // +0x0c
    Elt14* mpFixed;             // +0x10
    int mUnk14;                 // +0x14
    Elt14 mBuffer[16];          // +0x18
    Vec14Fixed* assign(const Elt14* first, const Elt14* last, const Elt14* endHint);
    Vec14Fixed(const Elt14* first, const Elt14* last);
};
// ---- items of slice s00773f60 end

// ---- items of slice s00775760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_poseQuatX;                               // 0x01630b8c
extern const float g_poseQuatY;                               // 0x01630b90
extern const float g_poseQuatZ;                               // 0x01630b94
extern const float g_realOne;                                 // 0x01485720
extern const float g_bindMatrix[];                            // 0x01630ccc
struct cRuntimeModelBuilder {
    char pad[0x140];

    // @ 0x007763f0
    char setFlagA(int key, int unused);
    // @ 0x00776470
    char setFlagB(int key, int unused);
    // @ 0x007764c0
    int setBoneA(int unused, const float* v, float w, int unused2);
    // @ 0x00776520
    int setBoneB(int unused, const float* v, float w, int unused2);
};
int cRuntimeModelBuilder::setBoneA(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x120) = v[0];
    *(float*)((char*)this + 0x124) = v[1];
    *(float*)((char*)this + 0x128) = v[2];
    *(float*)((char*)this + 0x12c) = w;
    return *(const int*)(v + 2);   // original leaves v[2] in eax (copied via a stack temp)
}
int cRuntimeModelBuilder::setBoneB(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x12c) = v[0];
    *(float*)((char*)this + 0x130) = v[1];
    *(float*)((char*)this + 0x134) = v[2];
    *(float*)((char*)this + 0x138) = w;
    return *(const int*)(v + 2);   // original leaves v[2] in eax (copied via a stack temp)
}
void operator_delete_array(void* p);                       // 0x00f47380 (operator delete[])
struct RCObj { void** vptr; volatile long rc; };
inline void RC_AddRef(RCObj* o) { _InterlockedExchangeAdd(&o->rc, 1); }
struct GmeRefCount {
    volatile long rc;
    __forceinline GmeRefCount() { _InterlockedExchange(&rc, 0); }
    virtual ~GmeRefCount() {}
};
struct GmeObj : GmeRefCount {                                // sizeof 0x58
    int f08, f0c, f10, p14[2], f1c, f20, f24, p28[2], f30, f34, f38, p3c[2], f44, f48, f4c, p50[2];
    __forceinline GmeObj() {
        f08 = f0c = f10 = 0; f1c = f20 = f24 = 0; f30 = f34 = f38 = 0; f44 = f48 = f4c = 0;
    }
    virtual ~GmeObj() {}
};
struct IRefObj { virtual int AddRef() = 0; virtual int Release() = 0; virtual int v2() = 0; virtual void* GetSub(uint32_t type) = 0; };
struct ResKey3 { uint32_t inst, type, group; };
struct RefVec {                                               // vector of intrusive refs
    RCObj** b; RCObj** e; RCObj** cap;
    RefVec() : b(0), e(0), cap(0) {}
    ~RefVec() { sub_41eb80(); }
    void sub_41eb80();
    void sub_41ef20(GmeObj** p);                              // push_back(const intrusive_ptr<GmeObj>&)
    void sub_424430(RCObj** pos, RCObj** val);                // DoInsertValue, ret 8
};
__forceinline void PushBack(RefVec* v, RCObj** src) {
    RCObj** e = v->e;
    if (e < v->cap) {
        v->e = e + 1;
        if (e) { RCObj* x = *src; *e = x; if (x) RC_AddRef(x); }
    } else {
        v->sub_424430(e, src);
    }
}
struct Drawer { void sub_740550(void* boneBuf); };            // ret 4
struct ArenaRes {                                             // GetArenaResource record
    char pad08[8];
    uint32_t keyInst, keyType, keyGroup;                      // +0x08, +0x0c, +0x10
};
struct Inst {
    char pad[0xf0]; Drawer* draw;
    bool sub_73eb90(RefVec* out);                             // GetMeshes, ret 4
    ArenaRes* sub_73d160();                                   // GetArenaResource
    void sub_73ba50(void (*fn)());                            // ret 4
};
void FUN_0072c100(RefVec* meshes, void* obj, int a, int b);
void* EAAllocate(size_t size, const char* name, int flags, int debugFlags, int file, int line);  // 0x00f473a0
void SetKeyKind(ResKey3* key, int kind, int flags);           // 0x0068c6d0
struct EABlockCookie { int users; };                          // EAAllocate keeps its owner count just before a block
inline bool EABlockInUse(void* block) { return ((EABlockCookie*)block)[-1].users != 0; }
struct Matrix3 {
    float rows[9];
    void Assign(const float* src);                            // 0x0041cb40
};
struct TransformPose {
    short flags;                                              // +0x00
    short id;                                                 // +0x02
    float qx, qy, qz, qw;                                     // +0x04..+0x13
    Matrix3 matrix;                                           // +0x14
};
struct BuilderOut;                                            // refcount at +0x04, Destroy at slot 0
struct Elem7c {
    Elem7c* Init(const TransformPose* src, IRefObj* sub, BuilderOut* builder);  // 0x00757e20
    void Destroy();                                           // 0x0041f2d0
    char bytes[0x7c];
};
struct ElemVec {
    Elem7c* begin; Elem7c* end; Elem7c* cap;
    void PushBack(Elem7c* elem);                              // 0x0041f650
};
struct MeshObj {
    virtual void AddRef();                                    // slot 0
    virtual void Release();                                   // slot 1
    MeshObj* Init();                                          // 0x007004d0
    char pad04[0x104];                                        // +0x004
    ElemVec elems;                                            // +0x108
    char pad114[0x20];                                        // +0x114
    float field134;                                           // +0x134
    char pad138[8];                                           // +0x138
};
struct BuilderOut {
    virtual void Destroy(int arg);                            // slot 0
    int refs;                                                 // +0x04
};
struct Counted {
    void* vptr;                                               // +0x00
    int field04;                                              // +0x04
    volatile long refs;                                       // +0x08
    void Release() {
        _InterlockedDecrement(&refs);
        if (_InterlockedExchangeAdd(&refs, 0) < 1) _InterlockedIncrement(&refs);
        else _InterlockedExchangeAdd(&refs, 0);
    }
};
struct HtTable {
    void* base;                                               // +0x00
    void* buckets;                                            // +0x04
    unsigned bucketCount;                                     // +0x08
    unsigned elementCount;                                    // +0x0c
    void DoFreeNodes(void* buckets, unsigned bucketCount);    // 0x007611f0
    void FreeAll() {
        DoFreeNodes(buckets, bucketCount);
        elementCount = 0;
        if (bucketCount > 1) operator_delete_array(buckets);
    }
};
struct PtrVec {
    void** begin; void** end;
    void DestroyRange(void** begin, void** end);              // 0x0070f520
    void FreeAll() {
        DestroyRange(begin, end);
        if (begin && EABlockInUse(begin)) operator_delete_array(begin);
    }
};
struct ShaderPreview {
    void* vtbl0;                                              // +0x000
    int field04;                                              // +0x004
    void* vtbl8;                                              // +0x008
    char pad0c[0x100];                                        // +0x00c
    void* buffer10c;                                          // +0x10c
    char pad110[0x30];                                        // +0x110
    HtTable table;                                            // +0x140
    char pad150[0x10];                                        // +0x150
    PtrVec meshes;                                            // +0x160
    char pad168[0x0c];                                        // +0x168
    Counted* counted;                                         // +0x174
};
struct ShaderPreviewA : ShaderPreview { void Destroy(); };
struct ShaderPreviewB : ShaderPreview { void Destroy(); };
// ---- items of slice s00775760 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int FUN_00775760(Inst* inst, RefVec* outMeshes, void** out3, void** out4, ResKey3 key, int arg8);  // 0x00775760 (stays in the slice: not this object's)

// ---- items of slice s00776730 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl VectorLength(const float* v);         // 0x40ae50
extern "C" void* __cdecl eastl_move_thunk(void* dst, const void* src, uint32_t n);      // 0x11e0744
extern uint32_t g_rasterDelta;          // 0x16f8b00
extern "C" void*             __cdecl operator_new(uint32_t sz, const char* name, int, int, int, int);   // 0xf473a0
extern "C" void              __cdecl operator_delete__(void* p);   // 0xf47380
extern char g_matDesc[];                 // 0x1631058
extern float g_xfInit[3];                // 0x1630df8
extern float g_vec4[4];                   // 0x1539bc8
extern float g_one;                       // 0x1485720 (1.0f)
extern float g_two;                       // 0x1470f1c (2.0f)
extern float g_vec3[3];                   // 0x1630eb8
extern char g_emptyBuckets[];             // 0x154df28
struct Matrix3_s0077_6730 {
    float m[9];
    void Assign(const Matrix3_s0077_6730* src);
};
struct Xform {
    uint16_t a, b;
    float    pos[3];
    float    one;
    Matrix3_s0077_6730  m;
    void AccumulateScaled(const uint32_t* flags);   // 0x40cd80
};
struct Transform : Xform {
    Transform();   // 0x409930
    void Init();   // 0x5aa530
};
struct ResKey { uint32_t a, b; };
struct cTextureInstance { void* tex; uint32_t pad; volatile long refCount; };
struct TexPtr {
    cTextureInstance* p;
    TexPtr() : p(0) {}
    TexPtr(const TexPtr& o) : p(o.p) { if (p) _InterlockedExchangeAdd(&p->refCount, 1); }
    ~TexPtr() {
        if (p) {
            _InterlockedExchangeAdd(&p->refCount, -1);
            long n = _InterlockedExchangeAdd(&p->refCount, 0);
            if (n < 1) _InterlockedExchangeAdd(&p->refCount, 1);
            else       _InterlockedExchangeAdd(&p->refCount, 0);
        }
    }
    void Assign(void* res);   // 0x576650 GetImageResource
};
struct TexPtrVec {
    TexPtr* mpBegin; TexPtr* mpEnd; TexPtr* mpCap;
    void DoInsertValue(TexPtr* pos, const TexPtr* v);   // 0x425a80
    void DestroyRange(TexPtr* first, TexPtr* last);     // 0x70f520
};
extern "C" TexPtr* __cdecl copy_intrusive(TexPtr* first, TexPtr* last, TexPtr* dest);   // 0x6f43e0
struct TexHash {                       // 0x20 bytes, at +0x140
    uint32_t pad0;
    void*    mpBuckets;
    uint32_t mnBuckets;
    uint32_t mnCount;
    float    mfLoad;
    float    mfGrow;
    uint32_t mnRehash;
    uint32_t pad1;
    int* Find(const ResKey* key);      // 0x6f6630 operator[]
};
struct CompiledState {
    void Dispatch();   // 0x11ee580
};
struct ActiveState {
    static void SetTexture(int slot, void* tex);   // 0x11f1280
};
extern "C" void __cdecl FUN_00761f90(CompiledState* cs, const void* vec, uint32_t flags);
struct ShConst {
    char data[0x100];
    ShConst();                                                  // 0x77d170
    void SetIndexed(int idx, float a, float b, float c, float d);  // 0x77ca20
};
struct cViewer {
    cViewer();    // 0x7c3f70
    ~cViewer();   // 0x7c4000
    void Copy(uint32_t v, int a, int b);   // 0x7c50b0
    void GetXform(Xform* out);             // 0x7c40f0
    void SetXform(const Xform* in);        // 0x7c4d00
    bool Update();                         // 0x7c4fd0
    void Finish();                         // 0x7c3c10
    void Init(int a);                      // 0x7c4dd0
    void Cleanup();                        // 0x7c3ba0
};
struct cImageInfo { uint32_t pad[3]; uint16_t width; uint16_t height; };
struct cImageRes {
    uint32_t pad; uint32_t flags;
    cImageInfo* GetInfo();   // 0x46f260
};
struct ImgPtr {
    cImageRes* p;
    void Assign(void* res);   // 0x576650
};
struct ImgRef {
    void* p;
    ImgRef() : p(0) {}
    ~ImgRef();   // 0x576620
};
struct SlotEntry { uint32_t pad; CompiledState* cs; };
struct IImageSource {
virtual void i0();
virtual void i1();
virtual void i2();
virtual void i3();
virtual void i4();
virtual void i5();
virtual void i6();
virtual void i7();
    virtual void* Lookup(uint32_t k0, uint32_t k1, int flags);   // +0x20
};
extern "C" IImageSource* __cdecl GetImageSource();                // 0x67dd60
struct IResSource {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
    virtual bool IsReady();                 // slot 15 (+0x3c)
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
    virtual void* GetDefaultTexture();      // slot 34 (+0x88)
};
struct IMessageServer {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
    virtual void AddListener(void* listener, uint32_t msgId);                       // +0x20
virtual void m9();
virtual void m10();
    virtual void RemoveListener(void* listener, uint32_t msgId, uint32_t extra);    // +0x2c
};
struct IMaterialManager {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
    virtual void Register(int id, const void* desc, void* data);                    // +0x2c
};
extern "C" IMessageServer*   __cdecl GetMessageServer();      // 0x67dcc0
extern "C" IMaterialManager* __cdecl GetMaterialManager();    // 0x67dd70
extern "C" IResSource*       __cdecl GetResSourceA();         // 0x67dda0
extern "C" IResSource*       __cdecl GetResSourceB();         // 0x67dd40
extern Matrix3_s0077_6730 g_identityB;              // 0x1630f38
struct cRefObjBase {
    virtual ~cRefObjBase() {}
    int refCount;
    cRefObjBase() : refCount(0) {}
};
struct cListenerBase { virtual ~cListenerBase() {} virtual void l0(); };
struct SlotVec {                 // fixed vector header at +0x10c
    SlotEntry** mpBegin; SlotEntry** mpEnd; SlotEntry** mpCap;
    void Init(int n);            // 0x758ee0
};
extern Matrix3_s0077_6730 g_identity3;               // 0x1630ff4
struct AGap { float vec[4]; uint32_t key[2]; uint16_t mode; uint8_t has; uint8_t flagB; cViewer* viewer; };
struct BGap { uint32_t key[2]; uint16_t mode; uint16_t pad; float vec[4]; uint8_t flagA; uint8_t flagB; uint16_t pad2; };
struct cShaderBase : cRefObjBase, cListenerBase {
    ShConst  sh;                          // +0x0c
    SlotVec  slots;                       // +0x10c
    uint32_t pad118[2];
    union { AGap a; BGap b; } g;          // +0x120
    TexHash  hash;                        // +0x140
    TexPtrVec texVec;                     // +0x160

    cShaderBase() {
        slots.mpBegin = 0; slots.mpEnd = 0; slots.mpCap = 0;
        hash.mpBuckets = g_emptyBuckets; hash.mnBuckets = 1; hash.mnCount = 0;
        hash.mfLoad = g_one; hash.mfGrow = g_two; hash.mnRehash = 0;
        texVec.mpBegin = 0; texVec.mpEnd = 0; texVec.mpCap = 0;
    }
    bool LoadTexture(ResKey key);         // 0x777290
    bool LoadImg(uint32_t k0, uint32_t k1, void** out);   // 0x6f44c0
    void BaseInit();                      // 0x67dd50
    void ClearTexVec() {
        TexPtr* b = texVec.mpBegin; TexPtr* e = texVec.mpEnd;
        TexPtr* r = copy_intrusive(e, e, b);
        texVec.DestroyRange(r, texVec.mpEnd);
        texVec.mpEnd += -(e - b);
    }
    void ClearSlotVec() {
        SlotEntry** b = slots.mpBegin; SlotEntry** e = slots.mpEnd;
        eastl_move_thunk(b, e, (uint32_t)((char*)e - (char*)e));
        slots.mpEnd += -(e - b);
    }
};
struct cShaderPreviewA : cShaderBase {
    uint32_t pad16c[2];
    ImgPtr   imgRes;                      // +0x174
    uint16_t scaleFlags;                  // +0x178 (low flag bits tested with 6)
    uint16_t pad17a;
    float    v17c[3];
    float    scale;                       // +0x188
    Matrix3_s0077_6730  mat;                         // +0x18c
    IResSource* res1b0;
    IResSource* res1b4;
    float    f1b8;
    int      mode1bc;
    float    f1c0, f1c4;

    cShaderPreviewA();
    void  Draw(int unused, uint32_t* pViewerArg, uint32_t flags);   // 0x776a60
    bool  Init();                                                   // 0x776f40
    bool  Shutdown();                                               // 0x777060
    bool  SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext);  // 0x7773c0
    virtual void r0();
    virtual void l0();
};
struct cShaderPreviewB : cShaderBase {
    uint32_t pad16c[2];
    uint8_t  flag174;
    uint8_t  pad175[3];
    IResSource* res178;
    IResSource* res17c;

    cShaderPreviewB();
    void  Draw(int unused, int unused2, cViewer** ppViewer, uint32_t flags);   // 0x776e60
    bool  Init();                                                   // 0x777130
    bool  Shutdown();                                               // 0x7771f0
    bool  SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext);  // 0x7775a0
    virtual void r0();
    virtual void l0();
};
static inline float Clamp01(float t) {
    if (t <= 0.0f) t = 0.0f;
    if (t >= 1.0f) t = 1.0f;
    return t;
}
// ---- items of slice s00776730 end

// ---- items of slice s007776f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_shaderStackTop;              // 0x01632bf0
extern char g_shaderStackRaw[];  // 0x016312e8 (= g_shaderStack - 8)
extern int g_table1631ef0[];  // 0x01631ef0
extern int* g_maxVertexCount;                   // 0x016f65b4
extern void* g_shaderData[];                    // 0x016f65a8
extern unsigned int g_shaderDirty[];            // 0x016f89f8
extern int g_softStateUpdated;                  // 0x016f9110
extern int* g_pData6dec;                        // 0x016f6dec
extern void* g_pData6df0;                       // 0x016f6df0
extern void* g_pData6e28;                       // 0x016f6e28
extern float* g_pFloat6ec8;                     // 0x016f6ec8
extern char g_emptyString16[];                  // 0x01667bac
extern void* g_graphicsAllocator;               // 0x013ebb38
extern "C" void* memset(void* dst, int value, unsigned int count);
extern void* BuildStateLookupShader(void* key);                          // 0x011fa000
extern void RemoveShader(void* key);                                     // 0x011fa050
struct __declspec(align(16)) Mat44 {
    __m128 r[4];
    void assignTo(Mat44* dst) const;  // @ 0x007779e0
};
struct ShaderState {
    char pad[0x18];
    void setSlotU0(int idx, char v);  // @ 0x00777a60
    void setSlotU1(int idx, char v);  // @ 0x00777a80
    void setSlotV0(int idx, char v);  // @ 0x00777aa0
    void setSlotV1(int idx, char v);  // @ 0x00777ac0
};
struct ShaderStackEntry {
    short key;
    short pad;
    int value;
};
extern ShaderStackEntry g_shaderStack[];  // 0x016312f0
struct D3DDevice;
struct D3DVtbl {
    void* m_pad0[0x178 / 4];
    void (__stdcall *m_call178)(D3DDevice*, int, int, int);
    void* m_pad1[(0x1b4 - 0x17c) / 4];
    void (__stdcall *m_call1b4)(D3DDevice*, int, int, int);
};
struct D3DDevice {
    D3DVtbl* m_vtbl;
};
struct VertexDescElement {
    unsigned int m_id;              // +0x00
    union {
        unsigned int m_flags;       // +0x04 (dword view)
        unsigned char m_count;      // +0x04 (byte view)
    };
    unsigned char m_pad[3];         // +0x05
};
struct VertexDescriptor {
    VertexDescElement m_elements[16];
    unsigned int FindElement(unsigned int index);
};
struct DrawBatch {
    unsigned char m_a;
    unsigned char m_b;
    unsigned char m_c;
};
struct DrawState {
    int m_base;
    int m_count;
    int m_batchCount;
    unsigned char* m_batches;
    int m_vertexBase;
};
struct Arena {
    void* ObjectToId(void* object);
    void* IdToObject(void* id);
};
struct ArenaHandle {
    char m_pad[0x78];
    Arena* m_arena;
};
struct ArenaCtx {
    char m_pad[0x1c];
    ArenaHandle* m_handle;
};
struct ArenaObject {
    void* m_unused;
    void* m_value;
};
extern D3DDevice* g_d3dDevice;                  // 0x016f89d0
extern VertexDescriptor* g_vertexDescriptor;    // 0x016f65a0
extern DrawState* g_drawState;                  // 0x016f65b8
struct EAIOStream;
namespace EA {
namespace IO {
int ReadInt32(void* stream, void* data, int count, int flags);
}
}
int gfxRead(void* stream, void* data, int count);                        // 0x0093a6c0
void* gfxAlloc(unsigned int size, const char* name, int a, int b, void* alloc, int line);  // 0x00f473a0
void gfxFree(void* p);                                                   // 0x00f47380
struct cShaderBase_s0077_76f0;
extern void* ShaderConstruct(cShaderBase_s0077_76f0* self, void* key, unsigned int flags,
                             unsigned int geom, unsigned int elem,
                             unsigned int vs1, unsigned int vs2,
                             unsigned int ps1, unsigned int ps2);          // 0x011f4440
struct cShaderBase_s0077_76f0 {
    unsigned int m_flags;             // +0x00
    unsigned int m_geomType;          // +0x04
    unsigned int m_elementTypes;      // +0x08
    unsigned char m_pad0c[2];         // +0x0c
    unsigned short m_maxVSVersion;    // +0x0e
    unsigned char m_pad10[2];         // +0x10
    unsigned short m_maxPSVersion;    // +0x12
    unsigned char m_pad14[0x28];      // +0x14
    int m_refCount;                   // +0x3c
    unsigned char m_pad40[4];         // +0x40
    unsigned int m_nameFlags;         // +0x44

    bool Write(EAIOStream* io);  // 0x00777760 (cShaderBase::Write)
    bool Read(EAIOStream* io, void* key, unsigned int reserved);
};
// ---- items of slice s007776f0 end

// ---- items of slice s00778fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pDevice;  // 0x16f89d0
extern float g_1539ef8;   // 0x1539ef8: degrees-per-radian constant used by the projector angle
extern float g_1470f1c;   // 0x1470f1c = 2.0f
extern int*   g_178fd0;   // 0x16f6e68
extern float* g_179030;   // 0x16f6e6c
extern char*  g_1790a0;   // 0x16f6de8
extern float* g_179130;   // 0x16f6e94
extern float* g_179560;   // 0x16f6e0c
extern float* g_179670;   // 0x16f6dbc
extern float* g_179670b;  // 0x16f6ec8
extern float* g_179b60;   // 0x16f6e34
extern int    g_flag_1632f44;          // 0x1632f44
extern unsigned char g_buf_1632ea0[];  // 0x1632ea0
extern int     g_lightsCount;   // 0x16f8910
extern void*   g_17a5b8;        // 0x16fa5b8
extern float*  g_16f6e40;       // 0x16f6e40
extern char*   g_16f85ac;       // 0x16f85ac
extern float*  g_16f6e38;       // 0x16f6e38
extern float   g_1632c08, g_1632c0c, g_1632c10, g_1632c14;  // 0x1632c08
extern void*   FUN_011fca60(void* out, const void* in);
extern void*   FUN_011f1120();
extern void*   FUN_0067dd50();
struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))
struct LightRow { char pad[0x10]; float px, py, pz; float cx, cy, cz, cw; };
struct __declspec(align(16)) Vec4f { float x, y, z, w; };
extern LightRow* g_lights[];    // 0x16f8914
namespace rw {
namespace graphics {
void RWShader_SetShConst_projector(unsigned reg, unsigned count, int isVS);   // 0x007799f0
}
}
struct __declspec(align(16)) Transform3030 { float mOrigin[4]; };
struct LightParams {
    float m0;   // +0x00
    float m1;   // +0x04
    float m2;   // +0x08
    float m3;   // +0x0c  radius
    float m4;   // +0x10  enabled/interest (<= 0 disables the disc solve)
    float m5;   // +0x14
    float m6;   // +0x18
    float m7;   // +0x1c
    float m8;   // +0x20
    float m9;   // +0x24  x-axis weight
    float m10;  // +0x28  y-axis weight
    float m11;  // +0x2c  z-axis weight
    float m12;  // +0x30  falloff start
};
namespace rw {
namespace graphics {
void RWShader_SetShConst_cameraLight(unsigned reg, unsigned p2, int isVS);   // 0x00779c10
}
}
// ---- items of slice s00778fd0 end

// ---- items of slice s00779f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int    g_16f6ed8;    // 0x16f6ed8
void __cdecl SP_MatrixFromDirection(const float* dir, float* out);
// ---- items of slice s00779f20 end

// ---- items of slice s0077a160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float*       g_transform;           // 0x16f85ac  ActiveState::m_transform (Matrix44Affine*)
extern int          g_transformType;       // 0x16f8b50  ActiveState::m_transformType (MatrixType)
extern const float* g_inverseTransform;    // 0x16f9120  ActiveState::m_inverseTransform (lazily built)
extern float        g_invScratch[16];      // 0x1632c90  storage for the cached inverse transform
extern float        g_M[16];               // 0x16f8be0  the 4x4 matrix that is inverted
float* __cdecl Matrix4_invert(float* out, const float* m, int type);   // @ 0x778060
static __forceinline float Minor3(const float* m, int r, int c) {
    float a[9];
    int k = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == r) continue;
        for (int j = 0; j < 4; ++j) {
            if (j == c) continue;
            a[k++] = m[i * 4 + j];
        }
    }
    return a[0] * (a[4] * a[8] - a[5] * a[7])
         - a[1] * (a[3] * a[8] - a[5] * a[6])
         + a[2] * (a[3] * a[7] - a[4] * a[6]);
}
static __forceinline float RcpRefined(float d) {
    __m128 x = _mm_set1_ps(d);
    __m128 two = _mm_set1_ps(2.0f);
    __m128 r = _mm_rcp_ps(x);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), _mm_rcp_ps(x));
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    return _mm_cvtss_f32(r);
}
static __forceinline void Inverse44(const float* m, float* n) {
    float c[16];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            c[i * 4 + j] = (((i + j) & 1) ? -1.0f : 1.0f) * Minor3(m, i, j);   // cofactor C(i,j)
    float det = ((c[0] * m[0] + c[1] * m[1]) + c[2] * m[2]) + c[3] * m[3];     // expansion along row 0
    for (int k = 0; k < 16; ++k) n[k] = 0.0f;
    if (det != 0.0f) {
        float r = RcpRefined(det);
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                n[i * 4 + j] = c[j * 4 + i] * r;                                // adj = cofactor^T
    }
}
static __forceinline void UploadTransposed(const float* v, unsigned reg, unsigned count, int isVS) {
    float data[16];
    for (int j = 0; j < 4; ++j)
        for (int k = 0; k < 4; ++k)
            data[j * 4 + k] = v[k * 4 + j];
    if (isVS) SETVS(g_pDevice, reg, data, count);
    else      SETPS(g_pDevice, reg, data, count);
}
// ---- items of slice s0077a160 end

// ---- items of slice s0077bc10 begin (TODO(rewrite): local stubs, replace by canonical classes)
#undef MUL
#undef SUB
#undef ADD
struct Mat4_s0077_bc10 { __m128 r0, r1, r2, r3; };   // named rows (no array, so no /GS cookie)
extern Mat4_s0077_bc10  g_shConstMatrix;   // 0x16f90d0
#define MUL _mm_mul_ps
#define SUB _mm_sub_ps
#define ADD _mm_add_ps
static __forceinline bool Invert(Mat4_s0077_bc10& out, const Mat4_s0077_bc10& m)
{
    const __m128 m00 = SplatX(m.r0), m01 = SplatY(m.r0), m02 = SplatZ(m.r0), m03 = SplatW(m.r0);
    const __m128 m10 = SplatX(m.r1), m11 = SplatY(m.r1), m12 = SplatZ(m.r1), m13 = SplatW(m.r1);
    const __m128 m20 = SplatX(m.r2), m21 = SplatY(m.r2), m22 = SplatZ(m.r2), m23 = SplatW(m.r2);
    const __m128 m30 = SplatX(m.r3), m31 = SplatY(m.r3), m32 = SplatZ(m.r3), m33 = SplatW(m.r3);

    __m128 d0 = ADD(ADD(MUL(SUB(MUL(m22, m33), MUL(m23, m32)), m11),
                        MUL(SUB(MUL(m31, m23), MUL(m21, m33)), m12)),
                    MUL(SUB(MUL(m21, m32), MUL(m31, m22)), m13));
    __m128 d1 = ADD(ADD(MUL(SUB(MUL(m23, m32), MUL(m22, m33)), m10),
                        MUL(SUB(MUL(m33, m20), MUL(m23, m30)), m12)),
                    MUL(m13, SUB(MUL(m30, m22), MUL(m20, m32))));
    __m128 d2 = ADD(ADD(MUL(m10, SUB(MUL(m33, m21), MUL(m23, m31))),
                        MUL(m11, SUB(MUL(m23, m30), MUL(m33, m20)))),
                    MUL(m13, SUB(MUL(m31, m20), MUL(m21, m30))));
    __m128 c30 = ADD(ADD(MUL(m10, SUB(MUL(m22, m31), MUL(m32, m21))),
                         MUL(m11, SUB(MUL(m32, m20), MUL(m22, m30)))),
                     MUL(m12, SUB(MUL(m21, m30), MUL(m31, m20))));
    __m128 det = ADD(ADD(ADD(MUL(d0, m00), MUL(m01, d1)), MUL(m02, d2)), MUL(m03, c30));

    if (_mm_movemask_ps(_mm_cmpeq_ps(_mm_set1_ps(0.0f), det)) == 0xf)
        return false;

    const __m128 two = _mm_set1_ps(2.0f);
    __m128 rcp = MUL(SUB(two, MUL(_mm_rcp_ps(det), det)), _mm_rcp_ps(det));
    rcp = MUL(SUB(two, MUL(rcp, det)), rcp);

    __m128 c00 = ADD(ADD(MUL(m11, SUB(MUL(m33, m22), MUL(m32, m23))),
                         MUL(m12, SUB(MUL(m23, m31), MUL(m33, m21)))),
                     MUL(m13, SUB(MUL(m32, m21), MUL(m22, m31))));
    __m128 c01 = ADD(ADD(MUL(SUB(MUL(m02, m33), MUL(m03, m32)), m21),
                         MUL(SUB(MUL(m03, m31), MUL(m01, m33)), m22)),
                     MUL(SUB(MUL(m01, m32), MUL(m02, m31)), m23));
    __m128 c02 = ADD(ADD(MUL(SUB(MUL(m02, m13), MUL(m03, m12)), m31),
                         MUL(SUB(MUL(m03, m11), MUL(m01, m13)), m32)),
                     MUL(SUB(MUL(m01, m12), MUL(m02, m11)), m33));
    __m128 c03 = ADD(ADD(MUL(SUB(MUL(m13, m22), MUL(m12, m23)), m01),
                         MUL(SUB(MUL(m11, m23), MUL(m13, m21)), m02)),
                     MUL(SUB(MUL(m12, m21), MUL(m11, m22)), m03));

    __m128 c10 = ADD(ADD(MUL(SUB(MUL(m20, m33), MUL(m30, m23)), m12),
                         MUL(SUB(MUL(m30, m22), MUL(m20, m32)), m13)),
                     MUL(SUB(MUL(m23, m32), MUL(m33, m22)), m10));
    __m128 c11 = ADD(ADD(MUL(SUB(MUL(m33, m00), MUL(m03, m30)), m22),
                         MUL(m23, SUB(MUL(m02, m30), MUL(m32, m00)))),
                     MUL(m20, SUB(MUL(m32, m03), MUL(m33, m02))));
    __m128 c12 = ADD(ADD(MUL(m32, SUB(MUL(m13, m00), MUL(m03, m10))),
                         MUL(m33, SUB(MUL(m02, m10), MUL(m12, m00)))),
                     MUL(m30, SUB(MUL(m12, m03), MUL(m13, m02))));
    __m128 c13 = ADD(ADD(MUL(m02, SUB(MUL(m13, m20), MUL(m23, m10))),
                         MUL(m03, SUB(MUL(m22, m10), MUL(m12, m20)))),
                     MUL(m00, SUB(MUL(m23, m12), MUL(m22, m13))));

    __m128 c20 = ADD(ADD(MUL(m13, SUB(MUL(m31, m20), MUL(m21, m30))),
                         MUL(m10, SUB(MUL(m33, m21), MUL(m23, m31)))),
                     MUL(m11, SUB(MUL(m23, m30), MUL(m33, m20))));
    __m128 c21 = ADD(ADD(MUL(m23, SUB(MUL(m31, m00), MUL(m01, m30))),
                         MUL(m20, SUB(MUL(m33, m01), MUL(m31, m03)))),
                     MUL(m21, SUB(MUL(m03, m30), MUL(m33, m00))));
    __m128 c22 = ADD(ADD(MUL(m33, SUB(MUL(m11, m00), MUL(m01, m10))),
                         MUL(m30, SUB(MUL(m13, m01), MUL(m11, m03)))),
                     MUL(m31, SUB(MUL(m03, m10), MUL(m13, m00))));
    __m128 c23 = ADD(ADD(MUL(m03, SUB(MUL(m11, m20), MUL(m21, m10))),
                         MUL(m00, SUB(MUL(m21, m13), MUL(m23, m11)))),
                     MUL(m01, SUB(MUL(m23, m10), MUL(m13, m20))));

    __m128 c31 = ADD(ADD(MUL(m20, SUB(MUL(m31, m02), MUL(m32, m01))),
                         MUL(m21, SUB(MUL(m32, m00), MUL(m02, m30)))),
                     MUL(m22, SUB(MUL(m01, m30), MUL(m31, m00))));
    __m128 c32 = ADD(ADD(MUL(m30, SUB(MUL(m02, m11), MUL(m01, m12))),
                         MUL(SUB(MUL(m00, m12), MUL(m10, m02)), m31)),
                     MUL(SUB(MUL(m10, m01), MUL(m00, m11)), m32));
    __m128 c33 = ADD(ADD(MUL(SUB(MUL(m11, m22), MUL(m12, m21)), m00),
                         MUL(SUB(MUL(m20, m12), MUL(m10, m22)), m01)),
                     MUL(SUB(MUL(m10, m21), MUL(m20, m11)), m02));

    out.r0 = _mm_setr_ps(_mm_cvtss_f32(MUL(c00, rcp)), _mm_cvtss_f32(MUL(c01, rcp)),
                           _mm_cvtss_f32(MUL(c02, rcp)), _mm_cvtss_f32(MUL(c03, rcp)));
    out.r1 = _mm_setr_ps(_mm_cvtss_f32(MUL(c10, rcp)), _mm_cvtss_f32(MUL(c11, rcp)),
                           _mm_cvtss_f32(MUL(c12, rcp)), _mm_cvtss_f32(MUL(c13, rcp)));
    out.r2 = _mm_setr_ps(_mm_cvtss_f32(MUL(c20, rcp)), _mm_cvtss_f32(MUL(c21, rcp)),
                           _mm_cvtss_f32(MUL(c22, rcp)), _mm_cvtss_f32(MUL(c23, rcp)));
    out.r3 = _mm_setr_ps(_mm_cvtss_f32(MUL(c30, rcp)), _mm_cvtss_f32(MUL(c31, rcp)),
                           _mm_cvtss_f32(MUL(c32, rcp)), _mm_cvtss_f32(MUL(c33, rcp)));
    return true;
}
// ---- items of slice s0077bc10 end

// ---- items of slice s0077c8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int*   g_16f6f00;   // 0x16f6f00
extern float* g_16f6e60;   // 0x16f6e60
extern void*  g_16f6ebc;   // 0x16f6ebc
extern void*  g_16f6e64;   // 0x16f6e64
extern float* g_16f6ec8;   // 0x16f6ec8
extern void*  g_16f6dd0;   // 0x16f6dd0
extern float* g_lights0;   // 0x16f8914
extern float  g_1632e28, g_1632e2c, g_1632e30, g_1632e34;  // 0x1632e28
extern void* g_vtbl_13ef094;  // 0x13ef094
extern void* g_vtbl_140e878;  // 0x140e878
extern "C" void* __cdecl FUN_00f473d0(unsigned size, unsigned align, unsigned a, const char* name,
                                      unsigned b, unsigned c, const char* file, unsigned line); // 0x00f473d0
extern "C" void* __cdecl FUN_00f473a0(unsigned size, const char* name, int a, int b,
                                      const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl FUN_00f47380(void* p); // 0x00f47380
extern const char kAllocName[]; // 0x013eb8a4  "Graphics"
extern const char kAllocFile[]; // 0x013ebb38  ".../EASTL/allocator.h"
extern "C" void* __cdecl FUN_00706ab0(const void* first, const void* last, void* dst);      // 0x00706ab0
extern "C" void* __cdecl FUN_0047c1c0(const void* first, const void* last, void* dest);     // 0x0047c1c0
extern "C" void  __cdecl FUN_0047cae0(void* dst, unsigned n, const void* value, void* pos);  // 0x0047cae0
extern "C" void  __cdecl FUN_0047a500(void** out, const void* first, const void* last,
                                      void* dest, const void* pos);                          // 0x0047a500
extern "C" void  __cdecl FUN_00edba80(void* first, void* last, void* destEnd);              // 0x00edba80
extern "C" void  __cdecl FUN_00898580(void* dst, const void* last, const void* value);       // 0x00898580
extern "C" void  __cdecl FUN_0045eac0(void* out, const void* in, void* parent);             // 0x0045eac0
extern "C" void  __fastcall FUN_007779e0(void* self, void* unused, void* dst);               // 0x007779e0
extern "C" void* __fastcall FUN_0040d010(void* self, void* unused);                          // 0x0040d010
struct ChangedFlag { unsigned char value; };
void __cdecl FUN_00777ae0(int code, void* obj, ChangedFlag changed);
struct GfxConst {
    void FUN_0077c970(float a, float b, float c, float d);
    void FUN_0077ca20(unsigned idx, float a, float b, float c, float d);
    int  FUN_0077cad0(short id);
    int  FUN_0077cb10(unsigned a, unsigned b);
};
struct ImgElt { void GetImageResource(unsigned arg); };  // 0x00576650
struct CtorObj { void* vtbl; volatile long refcount; int field2; int field3; int field4; };
extern void* g_16f85ac_s0077_c8b0; // 0x16f85ac
static __forceinline int FloorToInt(float x) {
    int i = _mm_cvtss_si32(_mm_set_ss(x));
    if (x < (float)i)
        --i;
    return i;
}
static __forceinline int CeilToInt(float x) {
    int i = _mm_cvtss_si32(_mm_set_ss(x));
    if ((float)i < x)
        ++i;
    return i;
}
struct WireRef {
    unsigned char pad0[8];
    volatile long refcount;      // +8
};
struct WireElem {
    unsigned      field0;        // +0
    WireRef*      ref;           // +4
    unsigned char b0;            // +8
    unsigned char b1;            // +9
    unsigned char b2;            // +0xa
    unsigned char b3;            // +0xb
    unsigned char flag;          // +0xc
    unsigned char pad1[3];       // +0xd
};
struct WireObj {
    unsigned  header;            // +0
    WireElem  elems[6];          // +4, stride 0x10
    WireObj* CopyWire(const WireObj* src);
};
struct Vec4 { float x, y, z, w; };
struct Vec4Vector {
    Vec4* begin;        // +0
    Vec4* end;          // +4
    Vec4* cap;          // +8
    unsigned pad0;      // +0xc
    Vec4* fixedBuf;     // +0x10
    void DoInsertValues(Vec4* pos, unsigned n, const Vec4* value);
};
struct DescObj {
    unsigned       field0;   // +0
    unsigned short kind;     // +4
    unsigned short size;     // +6
    void*          data;     // +8
};
struct KindObj {
    void*          vtbl;     // +0
    unsigned short kind;     // +4
    unsigned short size;     // +6
    void*          payload;  // +8, points at +0xc
};
// ---- items of slice s0077c8b0 end

// ---- items of slice s0077f020 begin (TODO(rewrite): local stubs, replace by canonical classes)
// The shadow-effects adapter preserves the ordinary layer call and forces
// the shadow rendering flags. The adapter stores a nonowning layer pointer.
struct ShadowEffectsLayer_s0077f020 : SP::cILayer, EA::RefCountTemplate<int> {
    SP::cILayer* mLayer; // +0x0c
    virtual void DrawLayer(unsigned int, unsigned int,
        SP::cViewer const* const* const, SP::cRenderStats*);
};
// ---- items of slice s0077f020 end

// @ 0x00770010
Elem30** uninit_copy30(Elem30** result, Elem30* first, Elem30* last, Elem30* dest)
{
    *result = dest;
    if (first != last) {
        do {
            if (dest) {
                dest->v = first->v;
                dest->f4 = first->f4;
                dest->f5 = first->f5;
                dest->f6 = first->f6;
                dest->f7 = first->f7;
                dest->f8 = first->f8;
                dest->f9 = first->f9;
            }
            ++first;
            ++dest;
        } while (first != last);
        *result = dest;
    }
    return result;
}

// @ 0x00770080
void fill30(Big30* first, Big30* last, const Big30& value)
{
    while (first != last) {
        first->v = value.v;
        first->b[0] = value.b[0];
        first->b[1] = value.b[1];
        first->b[2] = value.b[2];
        first->b[3] = value.b[3];
        first->b[4] = value.b[4];
        first->b[5] = value.b[5];
        first->b[6] = value.b[6];
        first->b[7] = value.b[7];
        ++first;
    }
}

// @ 0x007700e0
void uninit_fill_n30(Elem30* dest, unsigned int n, const Elem30& value)
{
    if (n == 0) return;
    float* p = (float*)dest + 6;
    do {
        if (dest) {
            dest->v = value.v;
            p[-2] = value.f4;
            p[-1] = value.f5;
            p[0] = value.f6;
            p[1] = value.f7;
            p[2] = value.f8;
            p[3] = value.f9;
        }
        dest = (Elem30*)((char*)dest + 0x30);
        p += 12;
    } while (--n);
}

// @ 0x00770180
__declspec(noinline) void pop_heap(SortElem* first, SortElem* last, SortCompare compare)
{
    const SortElem tempBottom(*(last - 1));
    *(last - 1) = *first;
    adjust_heap(first, 0, (int)(last - first) - 1, 0, tempBottom, compare);
}

// @ 0x00770240
__declspec(noinline) void make_heap(SortElem* first, SortElem* last, SortCompare compare)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            adjust_heap(first, parentPosition, heapSize, parentPosition, first[parentPosition],
                        compare);
        } while (parentPosition != 0);
    }
}

// @ 0x007702c0
__declspec(noinline) void sort_heap(SortElem* first, SortElem* last, SortCompare compare)
{
    for (; (last - first) > 1; --last)
        pop_heap(first, last, compare);
}

// @ 0x00770320
int Unk770320::Method(int unused, BakeJob* job)
{
    (void)unused;
    StridedArray* src = job->mpSource;

    const Vector3 zero3(0.0f, 0.0f, 0.0f);
    const Vector3 ones(1.0f, 1.0f, 1.0f);
    Vector3 V(1.0f, 1.0f, 1.0f);            // current inverse parent scale

    Mat4 identity;
    identity.r[0] = MakeVec4u(1.0f, 0.0f, 0.0f, 0.0f);
    identity.r[1] = MakeVec4u(0.0f, 1.0f, 0.0f, 0.0f);
    identity.r[2] = MakeVec4u(0.0f, 0.0f, 1.0f, 0.0f);
    identity.r[3] = _mm_setzero_ps();
    Mat4 A = identity;                      // accumulated parent transform
    Mat4 B = identity;                      // bind matrix of the current parent
    Mat4 C = identity;                      // rotation applied to attachment positions

    BakeRecord next;                        // record built for this bone
    BakeRecord cur;                         // record of the current parent
    memset(&next, 0, sizeof(next));
    memset(&cur, 0, sizeof(cur));
    cur.c = 0;

    Mat4 stackA[kStackDepth];
    Mat4 stackB[kStackDepth];
    Mat4 stackC[kStackDepth];
    Vector3 stackV[kStackDepth];
    BakeRecord stackRec[kStackDepth];
    Mat4* pA = stackA;
    Mat4* pB = stackB;
    Mat4* pC = stackC;
    Vector3* pV = stackV;
    BakeRecord* pRec = stackRec;

    // Inverses kept across bones (a singular matrix keeps the previous result).
    Mat4 invBind;
    Mat4 invM1;
    Mat4 invM0;

    BoneXform local;
    const __m128 zeroSplat = _mm_set1_ps(0.0f);

    for (int i = 0; i < mCount; ++i) {
        if (src->mStride == 0x30) {
            const BoneXform* p = (const BoneXform*)src->At(i);
            local.rot = p->rot;
            local.pos.x = p->pos.x;
            local.pos.y = p->pos.y;
            local.pos.z = p->pos.z;
            local.scale.x = p->scale.x;
            local.scale.y = p->scale.y;
            local.scale.z = p->scale.z;
            local.f28 = p->f28;
            local.f2c = p->f2c;
        } else {
            const BoneXform20* p = (const BoneXform20*)src->At(i);
            local.rot = p->rot;
            __m128 pos = p->pos;
            local.pos.x = pos.m128_f32[0];
            local.pos.y = pos.m128_f32[1];
            local.pos.z = pos.m128_f32[2];
            local.scale.x = ones.x;
            local.scale.y = ones.y;
            local.scale.z = ones.z;
        }

        const Mat4& bind = job->mpBinds->mpBegin[i];
        float* skin = (float*)(mpSkin + i * 0x30);

        AffineInverse(invBind, (const float*)&bind);
        Mat4 M;
        Mul(M, invBind, B);

        Mat4 T;                             // this bone's accumulated transform
        Mat4 Cnext;
        Vector3 Vnext;

        int parent = mpParent[i];
        if (parent != -1) {
            // Attachment: rotation and offset relative to M, recorded in slot `parent`.
            __m128 q;
            __m128 eps = zeroSplat;
            MatrixToQuat(&q, &M, &eps);

            BoneXform& att = mpAttach[parent];
            att.rot = QuatMul(QuatConjugate(q), local.rot);
            __m128 mt = M.r[3];
            att.pos.x = local.pos.x - mt.m128_f32[0];
            att.pos.y = local.pos.y - mt.m128_f32[1];
            att.pos.z = local.pos.z - mt.m128_f32[2];
            att.scale.x = local.scale.x;
            att.scale.y = local.scale.y;
            att.scale.z = local.scale.z;

            __m128 ap = MakeVec3(att.pos.x, att.pos.y, att.pos.z);
            __m128 rp = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatY(ap), C.r[1]), _mm_mul_ps(SplatX(ap), C.r[0])),
                                   _mm_mul_ps(SplatZ(ap), C.r[2]));
            att.pos.x = rp.m128_f32[0];
            att.pos.y = rp.m128_f32[1];
            att.pos.z = rp.m128_f32[2];

            Cnext = identity;
            new (&mpRecords[parent]) BakeRecord(cur);

            att.scale.x = ones.x;
            att.scale.y = ones.y;
            att.scale.z = ones.z;

            next.c = 0;
            next.a = zero3.x;
            next.b = zero3.y;
            next.d = zero3.z;
            next.v[0] = identity.r[0];
            next.v[1] = identity.r[1];
            next.v[2] = identity.r[2];
            next.v[3] = identity.r[3];
            next.x = local.scale.x;
            next.y = local.scale.y;
            next.z = local.scale.z;
            next.w = ones.x;
            next.p = ones.y;
            next.q = ones.z;

            Mat4 S;
            ScaleMat(S, MakeVec3(local.scale.x, local.scale.y, local.scale.z));
            Mul(T, S, invBind);

            Vnext.x = 1.0f / local.scale.x;
            Vnext.y = 1.0f / local.scale.y;
            Vnext.z = 1.0f / local.scale.z;
        } else {
            Mat4 MC;
            Mul(MC, M, C);
            Cnext = MC;

            __m128 scale;
            if (cur.c != 0) {
                scale = MakeVec3(local.scale.x, local.scale.y, local.scale.z);
                // Child of a hierarchy record: compose with the record's matrices.
                Mat4 S, R, SR, S2, SRS2, Tr, X;
                ScaleMat(S, scale);
                RotationMat(R, local.rot);
                Mul(SR, S, R);
                ScaleMat(S2, MakeVec3(cur.w, cur.p, cur.q));
                Mul(SRS2, SR, S2);
                TranslateMat(Tr, MakeVec3(local.pos.x, local.pos.y, local.pos.z));
                Mul(X, SRS2, Tr);

                Mat4 W, curV;
                curV.r[0] = cur.v[0]; curV.r[1] = cur.v[1]; curV.r[2] = cur.v[2]; curV.r[3] = cur.v[3];
                Mul(W, X, curV);
                next.v[0] = W.r[0];
                next.v[1] = W.r[1];
                next.v[2] = W.r[2];
                next.v[3] = W.r[3];
                next.c = 1;
                next.a = cur.a;
                next.b = cur.b;
                next.d = cur.d;

                AffineInverse(invM1, (const float*)&M);
                Mat4 curI, WI;
                curI.r[0] = cur.v[4]; curI.r[1] = cur.v[5]; curI.r[2] = cur.v[6]; curI.r[3] = cur.v[7];
                Mul(WI, curI, invM1);
                next.v[4] = WI.r[0];
                next.v[5] = WI.r[1];
                next.v[6] = WI.r[2];
                next.v[7] = WI.r[3];
            } else {
                // First hierarchy level: offset scaled by the record's scale.
                next.c = 1;
                next.a = local.pos.x * cur.x;
                next.b = cur.y * local.pos.y;
                next.d = cur.z * local.pos.z;
                scale = MakeVec3(local.scale.x, local.scale.y, local.scale.z);

                Mat4 S, R, SR;
                RotationMat(R, local.rot);
                ScaleMat(S, scale);
                Mul(SR, S, R);
                next.v[0] = SR.r[0];
                next.v[1] = SR.r[1];
                next.v[2] = SR.r[2];
                next.v[3] = SR.r[3];

                AffineInverse(invM0, (const float*)&M);
                next.v[4] = invM0.r[0];
                next.v[5] = invM0.r[1];
                next.v[6] = invM0.r[2];
                next.v[7] = invM0.r[3];
            }

            next.x = ones.x;
            next.y = ones.y;
            next.z = ones.z;
            Vector3 invScale = ones / local.scale;
            next.w = invScale.x;
            next.p = invScale.y;
            next.q = invScale.z;

            // T = scale * rotation * inverse parent scale * translation * A
            Mat4 S, R, SR, SV, SRV, Tr, X;
            ScaleMat(S, scale);
            RotationMat(R, local.rot);
            Mul(SR, S, R);
            ScaleMat(SV, MakeVec3(V.x, V.y, V.z));
            Mul(SRV, SR, SV);
            TranslateMat(Tr, MakeVec3(local.pos.x, local.pos.y, local.pos.z));
            Mul(X, SRV, Tr);
            Mul(T, X, A);

            Vnext = invScale;
        }

        // Skin matrix: bind * T, stored transposed as 3x4.
        Mat4 K;
        Mul(K, bind, T);
        skin[0]  = K.r[0].m128_f32[0];
        skin[1]  = K.r[1].m128_f32[0];
        skin[2]  = K.r[2].m128_f32[0];
        skin[3]  = K.r[3].m128_f32[0];
        skin[4]  = K.r[0].m128_f32[1];
        skin[5]  = K.r[1].m128_f32[1];
        skin[6]  = K.r[2].m128_f32[1];
        skin[7]  = K.r[3].m128_f32[1];
        skin[8]  = K.r[0].m128_f32[2];
        skin[9]  = K.r[1].m128_f32[2];
        skin[10] = K.r[2].m128_f32[2];
        skin[11] = K.r[3].m128_f32[2];

        switch (job->mpFlags->mpBegin[i] & 3) {
        case 2:     // push the current state, then descend into this bone
            *pA = A;
            *pV = V;
            ++pV;
            new (pRec) BakeRecord(cur);
            ++pRec;
            *pB = B;
            *pC = C;
            ++pA;
            ++pB;
            ++pC;
            // fall through
        case 0:     // this bone becomes the current parent
            A = T;
            V = Vnext;
            new (&cur) BakeRecord(next);
            B = bind;
            C = Cnext;
            break;
        case 1:     // pop the saved state
            --pA;
            A = *pA;
            --pV;
            V = *pV;
            --pRec;
            new (&cur) BakeRecord(*pRec);
            --pB;
            --pC;
            B = *pB;
            C = *pC;
            break;
        default:
            break;
        }
    }
    return 1;
}

// @ 0x00773f60
SortElem* get_partition(SortElem* first, SortElem* last, SortElem pivotValue, SortCompare compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        const SortElem temp(*first);
        *first = *last;
        *last = temp;
    }
}

// @ 0x00774010
void partial_sort(SortElem* first, SortElem* middle, SortElem* last, SortCompare compare)
{
    make_heap(first, middle, compare);
    for (SortElem* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const SortElem temp(*i);
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    sort_heap(first, middle, compare);
}

// @ 0x007740f0
void FUN_007740f0(unsigned int param_1, int* param_2)
{
    g_770320.Method(param_1, param_2);
}

// @ 0x00774290
void introsort_loop(SortElem* first, SortElem* last, int depthLimit, SortCompare compare)
{
    do {
        if (((last - first) <= 0x1c) || (depthLimit <= 0)) {
            if (depthLimit == 0)
                partial_sort(first, last, last, compare);
            return;
        }
        SortElem* middle = first + (last - first) / 2;
        SortElem* pivot = first;
        if (compare(*first, *middle)) {
            if (compare(*middle, *(last - 1))) {
                pivot = middle;
            } else {
                middle = last - 1;
                if (compare(*first, *(last - 1)))
                    pivot = last - 1;
                else
                    pivot = first;
            }
        } else {
            if (compare(*first, *(last - 1))) {
                pivot = first;
            } else {
                if (compare(*middle, *(last - 1)))
                    pivot = last - 1;
                else
                    pivot = middle;
            }
        }
        SortElem* cut = get_partition(first, last, *pivot, compare);
        --depthLimit;
        introsort_loop(cut, last, depthLimit, compare);
        last = cut;
    } while (true);
}

// @ 0x007743b0
void Vec30::InsertN(Blob30* position, unsigned n, const Blob30& value)
{
    INSERT_N_BODY(Blob30)
}

// @ 0x007745d0
void VecB0::InsertN(BlobB0* position, unsigned n, const BlobB0& value)
{
    INSERT_N_BODY(BlobB0)
}

// @ 0x007747c0
void VecM34::InsertN(Mat34* position, unsigned n, const Mat34& value)
{
    INSERT_N_BODY(Mat34)
}

// @ 0x007749e0
void sort_range(SortElem* first, SortElem* last, SortCompare compare)
{
    if (first != last) {
        const int nSize = (int)(last - first);
        int nDepth = 0;
        for (int i = nSize; i > 0; i >>= 1)
            ++nDepth;
        introsort_loop(first, last, (nDepth * 2) - 2, compare);
        if (nSize > 0x1c) {
            insertion_sort(first, first + 0x1c, compare);
            unguarded_insertion_sort(first + 0x1c, last, compare);
        } else {
            insertion_sort(first, last, compare);
        }
    }
}

// @ 0x00774a60
Vec14Fixed* Vec14Fixed::assign(const Elt14* first, const Elt14* last, const Elt14* endHint)
{
    (void)endHint;
    unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        Elt14* p = Alloc14Range(n, first, last, endHint);
        if (mpBegin && mpBegin != mpFixed)
            Free14(mpBegin);
        mpBegin = p;
        mpEnd = p + n;
        mpCapacity = p + n;
    } else {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        if (n > size) {
            // Copy the existing tail, then construct the remaining elements
            // in the spare capacity.
            Elt14* mid = const_cast<Elt14*>(first) + size;
            Copy14(first, mid, mpBegin);
            for (unsigned i = size; i < n; ++i)
                mpBegin[i] = first[i];
            mpEnd = mpBegin + n;
        } else {
            mpEnd = Copy14(first, last, mpBegin);
        }
    }
    return this;
}

// @ 0x00774b50
void VecIdx2::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        Idx2 value(-1);
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00774bb0
void Vec30::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        Blob30 value;
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        Blob30* position = mpBegin + n;
        Blob30* last = mpEnd;
        Move30(last, last, position);
        mpEnd -= (last - position);
    }
}

// @ 0x00774c30
void VecB0::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        BlobB0 value;
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        BlobB0* position = mpBegin + n;
        BlobB0* last = mpEnd;
        MoveB0(last, last, position);
        mpEnd -= (last - position);
    }
}

// @ 0x00774cc0
void VecM34::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        Mat34 value;
        InsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
    } else {
        Erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00774f10
Vec14Fixed::Vec14Fixed(const Elt14* first, const Elt14* last)
{
    // mpFixed = mBuffer; begin = end = mBuffer; capacity = mBuffer + 16;

    mpFixed = mBuffer;
    mpBegin = mBuffer;
    mpEnd = mBuffer;
    mpCapacity = mBuffer + 16;
    assign(first, last, last);
}

// @ 0x007760a0
int FUN_007760a0(Inst* inst, void** out, ResKey3 key, int arg8)
{
    RefVec meshes;
    void* out3 = 0;
    void* out4 = 0;
    if (key.inst == 0xffffffff) {
        ArenaRes* arena = inst->sub_73d160();
        if (arena) {
            arena = inst->sub_73d160();
            key.inst = arena->keyInst;
            key.type = arena->keyType;
            key.group = arena->keyGroup;
            SetKeyKind(&key, 0x61, 0);
        }
    }
    int res = FUN_00775760(inst, &meshes, &out3, &out4, key, arg8);
    if (res == 0) {
        MeshObj* obj = (MeshObj*)EAAllocate(0x140, "Graphics", 0, 0, 0, 0);
        if (obj) obj = obj->Init();
        if (obj) obj->AddRef();
        obj->field134 = 0.0f;
        FUN_0072c100(&meshes, obj, -1, 0);

        TransformPose pose;
        pose.flags = 0;
        pose.id = 0;
        pose.qx = g_poseQuatX;
        pose.qy = g_poseQuatY;
        pose.qz = g_poseQuatZ;
        pose.qw = g_realOne;
        pose.matrix.Assign(g_bindMatrix);

        Elem7c elem;
        Elem7c* built = elem.Init(&pose, (IRefObj*)out3, (BuilderOut*)out4);
        obj->elems.PushBack(built);
        elem.Destroy();

        obj->AddRef();
        *out = obj;
        obj->Release();
    }
    int result = res;
    if (out4) {
        BuilderOut* builder = (BuilderOut*)out4;
        int refs = builder->refs - 1;
        builder->refs = refs;
        if (refs == 0) {
            builder->refs = 1;
            builder->Destroy(1);
        }
    }
    if (out3) ((IRefObj*)out3)->Release();
    return result;
}

// @ 0x007763f0
char cRuntimeModelBuilder::setFlagA(int key, int unused)
{
    (void)unused;
    if (key == 0x692ea61) {
        if (*(char*)((char*)this + 0x133) != 0) {
            *(char*)((char*)this + 0x133) = 0;
            *(char*)((char*)this + 0x132) = 1;
        }
        return 1;
    }
    return 0;
}

// @ 0x00776470
char cRuntimeModelBuilder::setFlagB(int key, int unused)
{
    (void)unused;
    if (key == 0x692ea61) {
        if (*(char*)((char*)this + 0x135) != 0) {
            *(char*)((char*)this + 0x135) = 0;
            *(char*)((char*)this + 0x134) = 1;
        }
        return 1;
    }
    return 0;
}

// @ 0x00776590
void ShaderPreviewA::Destroy()
{
    vtbl0 = (void*)0x140e670;
    vtbl8 = (void*)0x140e660;
    _ReadWriteBarrier();
    if (counted) counted->Release();
    meshes.FreeAll();
    table.FreeAll();
    if (buffer10c && EABlockInUse(buffer10c)) operator_delete_array(buffer10c);
    vtbl8 = (void*)0x13eb394;
    vtbl0 = (void*)0x13ec458;
}

// @ 0x00776680
void ShaderPreviewB::Destroy()
{
    vtbl0 = (void*)0x140e698;
    vtbl8 = (void*)0x140e688;
    meshes.FreeAll();
    table.FreeAll();
    if (buffer10c && EABlockInUse(buffer10c)) operator_delete_array(buffer10c);
    vtbl8 = (void*)0x13eb394;
    vtbl0 = (void*)0x13ec458;
}

// @ 0x00776730
cShaderPreviewA::cShaderPreviewA()
{
    g.a.vec[0] = g_vec4[0]; g.a.vec[1] = g_vec4[1]; g.a.vec[2] = g_vec4[2]; g.a.vec[3] = g_vec4[3];
    g.a.key[0] = 0xffffffff; g.a.key[1] = 0xffffffff;
    g.a.has = 0; g.a.flagB = 0; g.a.viewer = 0; g.a.mode = 0;
    imgRes.p = 0; scaleFlags = 0; pad17a = 0;
    v17c[0] = g_vec3[0]; v17c[1] = g_vec3[1]; v17c[2] = g_vec3[2];
    scale = g_one;
    mat.Assign(&g_identity3);
    f1b8 = g_one;
    res1b0 = 0; res1b4 = 0;
    mode1bc = -1;
    f1c0 = 0.0f; f1c4 = 0.0f;
}

// @ 0x00776920
cShaderPreviewB::cShaderPreviewB()
{
    g.b.key[0] = 0xffffffff; g.b.key[1] = 0xffffffff;
    g.b.mode = 0;
    g.b.vec[0] = g_one; g.b.vec[1] = g_one; g.b.vec[2] = g_one; g.b.vec[3] = g_one;
    g.b.flagA = 0; g.b.flagB = 0;
    flag174 = 0; res178 = 0; res17c = 0;
}

// @ 0x00776a60
void cShaderPreviewA::Draw(int unused, uint32_t* pViewerArg, uint32_t flags)
{
    (void)unused;
    if (!g.a.has) return;
    cViewer* viewer = g.a.viewer;
    viewer->Copy(*pViewerArg, 0, 0);
    if (scale != 1.0f || (scaleFlags & 6)) {
        Xform xf;
        xf.a = 0; xf.b = 0;
        xf.pos[0] = g_xfInit[0]; xf.pos[1] = g_xfInit[1]; xf.pos[2] = g_xfInit[2];
        xf.one = 1.0f;
        xf.m.Assign(&g_identityB);
        viewer->GetXform(&xf);
        xf.AccumulateScaled((uint32_t*)&scaleFlags);
        viewer->SetXform(&xf);
    }
    uint16_t mode = g.a.mode;
    CompiledState* cs = slots.mpBegin[mode]->cs;
    void* tex = 0;
    if (mode == 5) {
        uint32_t k0 = g.a.key[0], k1 = g.a.key[1];
        if ((k0 & k1) != 0xffffffff) {
            if (k0 == 0x11330cf && k1 == 0) {
                tex = res1b4->GetDefaultTexture();
            } else {
                int* idx = hash.Find((ResKey*)g.a.key);
                tex = texVec.mpBegin[*idx].p->tex;
                if (!tex) return;
            }
        }
    } else if (mode == 4) {
        if (!imgRes.p) return;
        if (!(imgRes.p->flags & 1)) return;
        cImageInfo* info = imgRes.p->GetInfo();
        float w = (float)info->width;
        float h = (float)info->height;
        float invW = g_one / w;
        float invH = g_one / h;
        Transform tf;
        tf.Init();
        float aux = 0.0f;
        float f10 = 50.0f;
        int m = mode1bc;
        if (m != -1) {
            if (m == 2) {
                f10 = 80.0f;
            } else {
                viewer->GetXform(&tf);
                float len = VectorLength(tf.pos);
                aux = len;
                if (m == 0) {
                    float t = Clamp01((2338.0f - (len - 300.0f)) * 0.000427716f);
                    f10 = t * -15.0f + 60.0f;
                    aux = 0.2f;
                } else if (m == 1) {
                    float t = Clamp01((2190.0f - (len - 10.0f)) * 0.000456621f);
                    aux = t;
                    f10 = t * -10.0f + 80.0f;
                }
            }
        }
        sh.SetIndexed(0, f1b8, f10, aux, 0.0f);
        sh.SetIndexed(2, w, h, invW, invH);
    }
    if (viewer->Update()) {
        cs->Dispatch();
        if (tex) {
            ActiveState::SetTexture(0, tex);
            g_rasterDelta |= 1;
        }
        FUN_00761f90(cs, &g.a.vec, flags);
        viewer->Finish();
    }
}

// @ 0x00776e60
void cShaderPreviewB::Draw(int unused, int unused2, cViewer** ppViewer, uint32_t flags)
{
    (void)unused; (void)unused2;
    if (!g.b.flagA) return;
    void* tex = 0;
    if (!(*ppViewer)->Update()) return;
    uint32_t k0 = g.b.key[0], k1 = g.b.key[1];
    SlotEntry** arr = slots.mpBegin;
    uint32_t mode = g.b.mode;
    SlotEntry* ent;
    if ((k0 & k1) == 0xffffffff)
        ent = arr[mode];
    else
        ent = arr[mode + 6];
    CompiledState* cs = ent->cs;
    if ((k0 & k1) != 0xffffffff) {
        if (k0 == 0x11330cf && k1 == 0) {
            tex = res17c->GetDefaultTexture();
        } else {
            int* idx = hash.Find((ResKey*)g.b.key);
            tex = texVec.mpBegin[*idx].p->tex;
            if (!tex) return;
        }
    }
    cs->Dispatch();
    ActiveState::SetTexture(0, tex);
    g_rasterDelta |= 1;
    FUN_00761f90(cs, g.b.vec, flags);
    (*ppViewer)->Finish();
}

// @ 0x00776f40
bool cShaderPreviewA::Init()
{
    BaseInit();
    g.a.vec[0] = g_vec4[0]; g.a.vec[1] = g_vec4[1]; g.a.vec[2] = g_vec4[2]; g.a.vec[3] = g_vec4[3];
    g.a.has = 0;
    g.a.mode = 0;
    g.a.key[0] = 0xffffffff; g.a.key[1] = 0xffffffff;
    res1b0 = GetResSourceA();
    res1b4 = GetResSourceB();
    void* mem = operator_new(0x174, "Graphics", 0, 0, 0, 0);
    cViewer* v = mem ? new (mem) cViewer() : 0;
    g.a.viewer = v;
    v->Init(0);
    slots.Init(10);
    GetMaterialManager()->Register(10, g_matDesc, slots.mpBegin);
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->AddListener(static_cast<cListenerBase*>(this), 0x692ea61);
    return true;
}

// @ 0x00777060
bool cShaderPreviewA::Shutdown()
{
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->RemoveListener(static_cast<cListenerBase*>(this), 0x692ea61, 0xffffd8f1);
    ClearTexVec();
    if (g.a.viewer) {
        g.a.viewer->Cleanup();
        cViewer* v = g.a.viewer;
        if (v) {
            v->~cViewer();
            operator_delete__(v);
        }
    }
    ClearSlotVec();
    return true;
}

// @ 0x00777130
bool cShaderPreviewB::Init()
{
    uint32_t* dst = (uint32_t*)&g.b.vec[0];
    const uint32_t* src = (const uint32_t*)&g_vec4[0];
    dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3];
    g.b.flagA = 0;
    g.b.mode = 0xffff;
    g.b.key[0] = 0xffffffff; g.b.key[1] = 0xffffffff;
    res178 = GetResSourceA();
    res17c = GetResSourceB();
    slots.Init(10);
    GetMaterialManager()->Register(10, g_matDesc, slots.mpBegin);
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->AddListener(static_cast<cListenerBase*>(this), 0x692ea61);
    return true;
}

// @ 0x007771f0
bool cShaderPreviewB::Shutdown()
{
    IMessageServer* ms = GetMessageServer();
    if (ms) ms->RemoveListener(static_cast<cListenerBase*>(this), 0x692ea61, 0xffffd8f1);
    ClearTexVec();
    ClearSlotVec();
    return true;
}

// @ 0x00777290
bool cShaderBase::LoadTexture(ResKey key)
{
    if ((key.a & key.b) == 0xffffffff) return false;
    TexPtr tmp;
    void* res = GetImageSource()->Lookup(key.a, key.b, 0);
    if (!res) return false;
    tmp.Assign(res);
    if (texVec.mpEnd < texVec.mpCap) {
        TexPtr* e = texVec.mpEnd;
        texVec.mpEnd = e + 1;
        if (e) new (e) TexPtr(tmp);
    } else {
        texVec.DoInsertValue(texVec.mpEnd, &tmp);
    }
    int n = (int)(texVec.mpEnd - texVec.mpBegin);
    *hash.Find(&key) = n - 1;
    return true;
}

// @ 0x007773c0
bool cShaderPreviewA::SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext)
{
    *pNext = mode + 1;
    if (mode < 4 || mode > 5) return false;
    g.a.mode = (uint16_t)mode;
    g.a.has = 1;
    if ((k0 & k1) == 0xffffffff) {
        void* def = res1b4->GetDefaultTexture();
        if (def && mode == 5) {
            g.a.key[0] = 0x11330cf;
            g.a.key[1] = 0;
            g.a.has = 1;
            return true;
        }
        g.a.key[0] = 0xffffffff; g.a.key[1] = 0xffffffff;
        return true;
    }
    if (mode == 4) {
        ImgRef local;
        if (k0 != 0x1677f2a || k1 != 0) {
            if (!LoadImg(k0, k1, &local.p)) return false;
            imgRes.Assign(local.p);
        }
        g.a.has = 1;
        return true;
    }
    if (mode == 5) {
        if (k0 == 0x11330cf && k1 == 0) {
            g.a.key[0] = k0;
            g.a.key[1] = k1;
            if (res1b4->IsReady()) {
                g.a.flagB = 1;
                g.a.has = 0;
                return true;
            }
            g.a.has = 1;
            return true;
        }
        ResKey key; key.a = k0; key.b = k1;
        if (LoadTexture(key)) {
            g.a.key[0] = k0;
            g.a.key[1] = k1;
            g.a.has = 1;
            return true;
        }
    }
    return false;
}

// @ 0x007775a0
bool cShaderPreviewB::SetSlot(int mode, uint32_t k0, uint32_t k1, int* pNext)
{
    *pNext = mode + 1;
    switch (mode) {
    case 0: case 1: case 2: case 3:
        g.b.mode = (uint16_t)mode;
        g.b.flagA = 1;
        flag174 = 0;
        break;
    default:
        g.b.mode = 1;
        g.b.flagA = 1;
        flag174 = 0;
        break;
    case 6: case 7: case 8: case 9:
        g.b.mode = (uint16_t)(mode - 6);
        g.b.flagA = 1;
        flag174 = 1;
        break;
    }
    if ((k0 & k1) == 0xffffffff) {
        g.b.key[0] = 0xffffffff; g.b.key[1] = 0xffffffff;
        return true;
    }
    if (k0 == 0x11330cf && k1 == 0) {
        g.b.key[0] = k0;
        g.b.key[1] = 0;
        if (res17c->IsReady()) {
            g.b.flagA = 0;
            g.b.flagB = 1;
        }
        return true;
    }
    ResKey key; key.a = k0; key.b = k1;
    if (LoadTexture(key)) {
        g.b.key[0] = k0;
        g.b.key[1] = k1;
        return true;
    }
    return false;
}

// @ 0x00777840
bool cShaderBase_s0077_76f0::Read(EAIOStream* io, void* key, unsigned int reserved)
{
    (void)reserved;
    unsigned int geom;
    unsigned int flags;
    unsigned int elem;
    unsigned int vs;
    unsigned int ps;
    EA::IO::ReadInt32(io, &geom, 1, 0);
    EA::IO::ReadInt32(io, &flags, 1, 0);
    EA::IO::ReadInt32(io, &elem, 1, 0);
    EA::IO::ReadInt32(io, &vs, 1, 0);
    EA::IO::ReadInt32(io, &ps, 1, 0);
    EA::IO::ReadInt32(io, &m_nameFlags, 1, 0);

    cShaderBase_s0077_76f0* found = (cShaderBase_s0077_76f0*)BuildStateLookupShader(key);
    if (found) {
        if (found != this)
            found->m_refCount++;
        RemoveShader(key);
    }
    int savedRefCount = m_refCount;
    bool ok = ShaderConstruct(this, key, flags, geom, elem, vs, vs, ps, ps) != 0;
    if (savedRefCount > 0)
        m_refCount += savedRefCount;
    if ((m_nameFlags & 0x10) != 0) {
        int len;
        EA::IO::ReadInt32(io, &len, 1, 0);
        unsigned int cap = (unsigned int)len + 1;
        char* buf;
        if (cap <= 1)
            buf = g_emptyString16;
        else
            buf = (char*)gfxAlloc(cap, "Graphics", 0, 0, g_graphicsAllocator, 0xd1);
        memset(buf, 0x20, (unsigned int)len);
        buf[len] = 0;
        gfxRead(io, buf, len);
        if (cap > 1 && buf)
            gfxFree(buf);
    }
    return ok;
}

// @ 0x007779e0
void Mat44::assignTo(Mat44* dst) const
{
    Mat44* destination = *(Mat44* volatile*)&dst;
    destination->r[0] = r[0];
    destination->r[1] = r[1];
    destination->r[2] = r[2];
    destination->r[3] = r[3];
}

// @ 0x00777a10
int FUN_00777a10()
{
    int maxCount = *g_maxVertexCount;
    VertexDescriptor* vd = g_vertexDescriptor;
    if ((vd->m_elements[1].m_flags & 0x8000) == 0)
        return 1;
    unsigned int idx = vd->FindElement(0xf);
    VertexDescElement* e = &vd->m_elements[idx + 2];
    int count = (int)e->m_count + 1;
    if (count < 0 || maxCount <= count)
        count = maxCount;
    return count;
}

// @ 0x00777a60
void ShaderState::setSlotU0(int idx, char v)
{
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 1;
    p[0x19] = v;
}

// @ 0x00777a80
void ShaderState::setSlotU1(int idx, char v)
{
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 2;
    p[0x1a] = v;
}

// @ 0x00777aa0
void ShaderState::setSlotV0(int idx, char v)
{
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 4;
    p[0x1b] = v;
}

// @ 0x00777ac0
void ShaderState::setSlotV1(int idx, char v)
{
    char* p = (char*)this + idx * 0x10;
    p[0x18] = p[0x18] | 8;
    p[0x1c] = v;
}

// @ 0x00777ae0
void FUN_00777ae0(unsigned short index, void* value, char force)
{
    void* old = g_shaderData[index];
    if (old == value && force == 0)
        return;
    int top = g_shaderStackTop;
    if (top > 0) {
        g_shaderStack[top].key = index;
        g_shaderStack[top].value = (int)old;
        g_shaderStackTop = top + 1;
    }
    g_shaderData[index] = value;
    g_shaderDirty[index >> 5] |= 1u << (index & 0x1f);
    g_softStateUpdated |= 8;
}

// @ 0x00777bf0
void pushShaderDataNull()
{
    int top = g_shaderStackTop;
    g_shaderStack[top].key = 0;
    g_shaderStack[top].value = 0;
    g_shaderStackTop = top + 1;
}

// @ 0x00777c10
void FUN_00777c10()
{
    int top = g_shaderStackTop - 1;
    unsigned short key = g_shaderStack[top].key;
    g_shaderStackTop = top;
    if (key == 0)
        return;
    int soft = g_softStateUpdated;
    do {
        g_shaderData[key] = (void*)g_shaderStack[top].value;
        g_shaderDirty[key >> 5] |= 1u << (key & 0x1f);
        --top;
        key = g_shaderStack[top].key;
        soft |= 8;
    } while (key != 0);
    g_softStateUpdated = soft;
    g_shaderStackTop = top;
}

// @ 0x00777c90
int shaderDataStackNotEmpty()
{
    if (g_shaderStackTop > 0 && *(short*)(g_shaderStackRaw + g_shaderStackTop * 8) != 0)
        return 1;
    return 0;
}

// @ 0x00777cb0
void FUN_00777cb0(int params)
{
    DrawState* st = g_drawState;
    if (!st)
        return;
    if (st->m_batchCount == 0) {
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice,
            params + st->m_base * 3,
            st->m_base * 0x30 + st->m_vertexBase,
            st->m_count * 3);
        return;
    }
    for (int i = 0; i < st->m_batchCount; i += 3) {
        DrawBatch* batch = (DrawBatch*)(st->m_batches + i);
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice,
            params + batch->m_b * 3,
            batch->m_c * 0x30 + st->m_vertexBase,
            batch->m_a * 3);
    }
}

// @ 0x00777d60
void FUN_00777d60(int a, int b, int hard)
{
    (void)b;
    int count = *g_maxVertexCount;
    VertexDescriptor* vd = g_vertexDescriptor;
    if ((vd->m_elements[1].m_flags & 0x8000) == 0) {
        count = 1;
    } else {
        unsigned int idx = vd->FindElement(0xf);
        VertexDescElement* e = &vd->m_elements[idx + 2];
        int n = (int)e->m_count + 1;
        if (n >= 0 && count > n)
            count = n;
    }
    float data[4];
    data[0] = (float)count;
    data[1] = 0.0f;
    data[2] = 1.0f;
    data[3] = 0.0f;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 1);
    else
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 1);
}

// @ 0x00777e10
void FUN_00777e10(ArenaObject* object, ArenaCtx* ctx)
{
    Arena* arena = ctx->m_handle->m_arena;
    object->m_value = arena->ObjectToId(object->m_value);
}

// @ 0x00777e30
void FUN_00777e30(ArenaObject* object, ArenaHandle* handle)
{
    Arena* arena = handle->m_arena;
    object->m_value = arena->IdToObject(object->m_value);
}

// @ 0x00777e50
void FUN_00777e50(int a, int b, int hard)
{
    (void)b;
    int* base = g_pData6dec;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)(base + 1), 1);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)(base + 1), 1);
}

// @ 0x00777e90
void FUN_00777e90(int a, int b, int hard)
{
    (void)b;
    void* data = g_pData6df0;
    if (!data)
        return;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 2);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)data, 2);
}

// @ 0x00777ed0
void FUN_00777ed0(int a, int b, int hard)
{
    (void)b;
    void* data = g_pData6e28;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 1);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)data, 1);
}

// @ 0x00777f80
void FUN_00777f80(int a, int b, int hard)
{
    (void)b;
    float* p = g_pFloat6ec8;
    if (!p)
        return;
    float t = *p;
    float s = sinf(t);
    __declspec(align(16)) float data[8];
    data[0] = t;
    data[1] = s;
    data[2] = 0.25f * s + 0.5f;
    data[3] = (s + 1.0f) * 0.5f;
    data[4] = t * 0.0035f;
    data[5] = t * 0.0045f;
    data[6] = t * 0.0065f;
    data[7] = t * 0.0055f;
    if (hard)
        g_d3dDevice->m_vtbl->m_call178(g_d3dDevice, a, (int)data, 2);
    else
        g_d3dDevice->m_vtbl->m_call1b4(g_d3dDevice, a, (int)data, 2);
}

// @ 0x00778050
int tableLookup(unsigned short idx)
{
    return g_table1631ef0[idx];
}

// @ 0x00778fd0
void FUN_00778fd0(unsigned reg, unsigned p2, int isVS)
{
    int* p = g_178fd0;
    if (p) {
        float v[4] = { (float)p[0], 0.0f, 0.0f, 0.0f };
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00779030
void FUN_00779030(unsigned reg, unsigned p2, int isVS)
{
    float* p = g_179030;
    if (p) {
        float v[4] = { p[0], p[1], p[2], 0.0f };
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x007790a0
void FUN_007790a0(unsigned reg, unsigned p2, int isVS)
{
    char* p = g_1790a0;
    if (p) {
        float v[4];
        v[0] = *(float*)(p + 4);
        v[1] = *(float*)(p + 8);
        v[2] = *(float*)(p + 0xc);
        v[3] = g_one;
        if (p[1] == '\\' && p[2] == 'D' && p[3] == '&')
            v[3] = *(float*)(p + 0x10);
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00779130
void FUN_00779130(unsigned reg, unsigned p2, int isVS)
{
    float* p = g_179130;
    float v[32];
    if (p) {
        for (int k = 0; k < 8; ++k) {
            v[k * 4 + 0] = p[k * 2];
            v[k * 4 + 1] = p[k * 2 + 1];
            v[k * 4 + 2] = p[0x10 + k];
        }
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, 8);
    else
        SETPS(g_pDevice, reg, v, 8);
}

// @ 0x00779290
void FUN_00779290(unsigned reg, unsigned count, int isVS)
{
    int target = (int)((count + 1) >> 1);
    int n = g_lightsCount;
    if (target < n)
        n = target;
    float buf[256];
    for (int i = 0; i < n; ++i) {
        LightRow* L = g_lights[i];
        float* o = buf + i * 8;
        o[0] = -L->cx;
        o[1] = -L->cy;
        o[2] = -L->cz;
        o[3] = 0.0f;
        o[4] = L->px;
        o[5] = L->py;
        o[6] = L->pz;
        o[7] = 1.0f;
    }
    if (n < target)
        memset(buf + n * 8, 0, (target - n) * 0x20);
    if (isVS)
        SETVS(g_pDevice, reg, buf, count);
    else
        SETPS(g_pDevice, reg, buf, count);
}

// @ 0x007793e0
void FUN_007793e0(unsigned reg, unsigned count, int isVS)
{
    int target = (int)((count + 1) >> 1);
    int n = g_lightsCount;
    if (target < n)
        n = target;
    float buf[256];
    for (int i = 0; i < n; ++i) {
        LightRow* L = g_lights[i];
        float lp[4] = { L->cx, L->cy, L->cz, L->cw };
        float t[4];
        FUN_011fca60(t, lp);
        float* o = buf + i * 8;
        o[0] = -t[0];
        o[1] = -t[1];
        o[2] = -t[2];
        o[3] = 0.0f;
        o[4] = L->px;
        o[5] = L->py;
        o[6] = L->pz;
        o[7] = 1.0f;
    }
    if (n < target)
        memset(buf + n * 8, 0, (target - n) * 0x20);
    if (isVS)
        SETVS(g_pDevice, reg, buf, count);
    else
        SETPS(g_pDevice, reg, buf, count);
}

// @ 0x00779560
void FUN_00779560(unsigned reg, unsigned count, int isVS)
{
    float* p = g_179560;
    if (p) {
        if (isVS)
            SETVS(g_pDevice, reg, p + 1, count);
        else
            SETPS(g_pDevice, reg, p + 1, count);
    }
}

// @ 0x007795a0
#pragma intrinsic(sqrt)
void FUN_007795a0(unsigned reg, unsigned count, int isVS)
{
    __m128 a = *(const __m128*)((const char*)g_17a5b8 + 0x30);
    float b0, b1, b2;
    if (g_16f6e40) {
        b0 = g_16f6e40[0];
        b1 = g_16f6e40[1];
        b2 = g_16f6e40[2];
    } else {
        b0 = *(float*)(g_16f85ac + 0x30);
        b1 = *(float*)(g_16f85ac + 0x34);
        b2 = *(float*)(g_16f85ac + 0x38);
    }
    Vec4f v;
    v.x = (float)sqrt((double)((a.m128_f32[2] - b2) * (a.m128_f32[2] - b2) + (a.m128_f32[1] - b1) * (a.m128_f32[1] - b1) + (a.m128_f32[0] - b0) * (a.m128_f32[0] - b0)));
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    if (isVS)
        SETVS(g_pDevice, reg, &v.x, count);
    else
        SETPS(g_pDevice, reg, &v.x, count);
}

// @ 0x00779670
void FUN_00779670(unsigned reg, unsigned p2, int isVS)
{
    float* p = g_179670;
    if (p) {
        float v[4] = { p[4] * g_179670b[0], 0.0f, 0.0f, 0.0f };
        if (isVS) {
            SETVS(g_pDevice, reg, p, 1);
            SETVS(g_pDevice, reg + 1, v, 1);
        } else {
            SETPS(g_pDevice, reg, p, 1);
            SETPS(g_pDevice, reg + 1, v, 1);
        }
    }
}

// @ 0x00779710
void FUN_00779710(unsigned reg, unsigned p2, int isVS)
{
    void* p = FUN_0067dd50();
    int* q = (int*)((int*(__thiscall*)(void*))((*(void***)p)[0x1c / 4]))(p);
    float v[4];
    v[0] = (float)q[2];
    v[1] = (float)q[3];
    v[2] = (float)q[2] / (float)q[0];
    v[3] = (float)q[3] / (float)q[1];
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}

// @ 0x007799f0
void rw::graphics::RWShader_SetShConst_projector(unsigned reg, unsigned count, int isVS)
{
    float v[12];
    int obj = (int)FUN_011f1120();
    if (obj != 0) {
        int tex = *(int*)(obj + 0x40);
        float w = (float)*(unsigned short*)(tex + 0xc);
        float h = (float)*(unsigned short*)(tex + 0xe);
        v[0] = w;   v[1] = h;   v[2] = 1.0f / w; v[3] = 1.0f / h;
        if (count > 1) {
            float pw = (float)*(unsigned short*)(obj + 0x80);
            float ph = (float)*(unsigned short*)(obj + 0x84);
            float angle = (float)atan2(*(float*)(obj + 0x5c), 1.0f);
            v[4] = pw;
            v[5] = ph;
            v[6] = 1.0f / pw;
            v[7] = 1.0f / ph;
            v[8] = *(float*)(obj + 0x70);
            v[9] = *(float*)(obj + 0x74);
            v[10] = (360.0f / g_1539ef8) * angle;
        }
        v[11] = 1.0f;
    } else {
        v[1] = g_1632c08;  v[2] = g_1632c0c;  v[3] = g_1632c10;
        v[4] = g_1632c14;
        v[5] = g_1632c08;  v[6] = g_1632c0c;  v[7] = g_1632c10;
        v[8] = g_1632c14;
        v[9] = g_1632c08;  v[10] = g_1632c0c; v[11] = g_1632c10;
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, count);
    else
        SETPS(g_pDevice, reg, v, count);
}

// @ 0x00779b60
void FUN_00779b60(unsigned reg, unsigned count, int isVS)
{
    float* p = g_179b60;
    if (p) {
        if (isVS)
            SETVS(g_pDevice, reg, p + 1, count);
        else
            SETPS(g_pDevice, reg, p + 1, count);
        return;
    }
    if (!(g_flag_1632f44 & 1)) {
        g_flag_1632f44 |= 1;
        memset(g_buf_1632ea0, 0, 0xa4);
    }
    float* data = (float*)(g_buf_1632ea0 + 4);
    if (isVS)
        SETVS(g_pDevice, reg, data, count);
    else
        SETPS(g_pDevice, reg, data, count);
}

// @ 0x00779c10
void rw::graphics::RWShader_SetShConst_cameraLight(unsigned reg, unsigned p2, int isVS)
{
    if (g_17a5b8 == 0)
        return;

    __declspec(align(16)) float out[4];
    if (g_16f6e38 == 0) {
        out[0] = g_1632c08;
        out[1] = g_1632c0c;
        out[2] = g_1632c10;
        out[3] = g_1632c14;
    } else {
        const Transform3030* xform = (const Transform3030*)((const char*)g_17a5b8 + 0x30);
        const float a0 = xform->mOrigin[0];
        const float a1 = xform->mOrigin[1];
        const float a2 = xform->mOrigin[2];

        float b0, b1, b2;
        if (g_16f6e40) {
            b0 = g_16f6e40[0]; b1 = g_16f6e40[1]; b2 = g_16f6e40[2];
        } else {
            b0 = *(float*)(g_16f85ac + 0x30);
            b1 = *(float*)(g_16f85ac + 0x34);
            b2 = *(float*)(g_16f85ac + 0x38);
        }

        const float d0 = a0 - b0;
        const float d1 = a1 - b1;
        const float d2 = a2 - b2;
        const float len = (float)sqrt((double)(d2 * d2 + (d1 * d1 + d0 * d0)));
        const float inv = 1.0f / len;

        LightParams* lp = (LightParams*)g_16f6e38;

        // Distance along the light direction to the sphere's near intersection, clamped to
        // [0, len]; falls back to len when the parameters are disabled.
        float reach;
        if (0.0f < lp->m4) {
            const float n = -((d2 * inv) * a2 + ((d1 * inv) * a1 + (d0 * inv) * a0));
            float disc = n * n - ((a2 * a2 + (a1 * a1 + a0 * a0)) - lp->m3 * lp->m3);
            if (disc > 0.0f) {
                float t = (float)sqrt((double)disc) - n;
                if (t < 0.0f)
                    t = 0.0f;
                reach = (t <= len) ? t : len;
            } else {
                reach = 0.0f;
            }
        } else {
            reach = len;
        }

        // Normalised focus direction dotted with the light's axis weights.
        const float r = 1.0f / (float)sqrt((double)(b2 * b2 + (b1 * b1 + b0 * b0) + 1e-08f));
        const float fVar3 = lp->m11 * (a2 * r) + (lp->m10 * (a1 * r) + (r * a0) * lp->m9);

        float falloff = fVar3 + 0.95f;
        if (falloff < 0.0f)
            falloff = 0.0f;
        if (falloff > 1.0f)
            falloff = 1.0f;

        float ratio = 1.0f;
        if (fVar3 <= lp->m12) {
            float start = fVar3 + lp->m12;
            if (start < 0.001f)
                start = 0.001f;
            ratio = start / (lp->m12 * g_1470f1c);
        }

        out[0] = (len - reach) + lp->m0;
        out[1] = lp->m1;
        out[2] = ratio;
        out[3] = falloff;
    }

    if (isVS)
        SETVS(g_pDevice, reg, out, 1);
    else
        SETPS(g_pDevice, reg, out, 1);
}

// @ 0x00779f20
void FUN_00779f20(unsigned reg, unsigned count, int isVS)
{
    float dir[3];
    dir[0] = g_16f6e40[0];
    dir[1] = g_16f6e40[1];
    dir[2] = g_16f6e40[2];
    float r[9];
    float m[12];
    if (g_16f6ed8 != 0) {
        SP_MatrixFromDirection(dir, r);
        m[0] = r[0]; m[1] = r[1]; m[2] = r[2];
        m[3] = -((r[2] * dir[2] + r[1] * dir[1]) + r[0] * dir[0]);
        m[4] = r[3]; m[5] = r[4]; m[6] = r[5];
        m[7] = -((r[5] * dir[2] + r[4] * dir[1]) + r[3] * dir[0]);
        m[8] = r[6]; m[9] = r[7]; m[10] = r[8];
        m[11] = -((r[8] * dir[2] + r[7] * dir[1]) + r[6] * dir[0]);
    } else {
        m[0] = g_one;  m[1] = 0.0f;   m[2] = 0.0f;   m[3] = -dir[0];
        m[4] = 0.0f;   m[5] = g_one;  m[6] = 0.0f;   m[7] = -dir[1];
        m[8] = 0.0f;   m[9] = 0.0f;   m[10] = g_one; m[11] = -dir[2];
    }
    if (isVS)
        SETVS(g_pDevice, reg, m, count);
    else
        SETPS(g_pDevice, reg, m, count);
}

// @ 0x0077a160
void __cdecl FUN_0077a160(unsigned reg, unsigned count, int isVS)
{
    if (g_inverseTransform == 0) {                       // build and cache the inverse of m_transform
        for (int i = 0; i < 16; ++i) g_invScratch[i] = g_transform[i];
        float tmp[19];
        const float* inv = Matrix4_invert(tmp, g_invScratch, g_transformType);
        for (int i = 0; i < 16; ++i) g_invScratch[i] = inv[i];
        g_inverseTransform = g_invScratch;
    }
    const float* B = g_inverseTransform;
    float n[16];
    Inverse44(g_M, n);
    float v[16];                                         // v = n * B (row k = n.row(k) * B)
    for (int k = 0; k < 4; ++k) {
        for (int j = 0; j < 4; ++j) {
            v[k * 4 + j] = B[12 + j] * n[k * 4 + 3]
                         + (n[k * 4 + 2] * B[8 + j]
                         + (B[4 + j] * n[k * 4 + 1] + B[j] * n[k * 4 + 0]));
        }
    }
    UploadTransposed(v, reg, count, isVS);
}

// @ 0x0077bc10
void __cdecl FUN_0077bc10(unsigned reg, unsigned count, int isVS)
{
    Mat4_s0077_bc10 inv;
    Invert(inv, g_shConstMatrix);
    _MM_TRANSPOSE4_PS(inv.r0, inv.r1, inv.r2, inv.r3);
    if (isVS)
        SETVS(g_pDevice, reg, (const float*)&inv, count);
    else
        SETPS(g_pDevice, reg, (const float*)&inv, count);
}

// @ 0x0077c8b0
void __cdecl FUN_0077c8b0(unsigned reg, unsigned p2, int isVS)
{
    if (g_16f6f00 == 0)
        return;
    int obj = (int)FUN_011f1120();
    float x = *(float*)(obj + 0x30);
    float y = *(float*)(obj + 0x34);
    float z = *(float*)(obj + 0x38);
    float len2 = x * x + (y * y + z * z);
    float inv = 1.0f / (float)sqrt(len2 + 1e-08f);
    float len = (float)sqrt(len2);
    float v[4];
    v[0] = x * inv;
    v[1] = y * inv;
    v[2] = z * inv;
    v[3] = len;
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}

// @ 0x0077c970
void GfxConst::FUN_0077c970(float a, float b, float c, float d)
{
    float* p = (float*)this;
    bool changed = false;
    if (p[0] != a || p[1] != b || p[2] != c || p[3] != d)
        changed = true;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    ChangedFlag cf;
    cf.value = changed ? 1 : 0;
    FUN_00777ae0(0x20c, this, cf);
}

// @ 0x0077ca20
void GfxConst::FUN_0077ca20(unsigned idx, float a, float b, float c, float d)
{
    float* q = (float*)((char*)this + (idx & 0xffff) * 0x10);
    bool changed = false;
    if (q[0] != a || q[1] != b || q[2] != c || q[3] != d)
        changed = true;
    q[0] = a;
    q[1] = b;
    q[2] = c;
    q[3] = d;
    ChangedFlag cf;
    cf.value = changed ? 1 : 0;
    FUN_00777ae0(0x206, this, cf);
}

// @ 0x0077cad0
int GfxConst::FUN_0077cad0(short id)
{
    int n = (*(int*)((char*)this + 0xc) - *(int*)((char*)this + 8)) >> 2;
    if (n > 0) {
        int* q = *(int**)((char*)this + 8);
        int i = 0;
        do {
            if (*(short*)(*q + 4) == id)
                return i;
            ++i;
            ++q;
        } while (i < n);
    }
    return -1;
}

// @ 0x0077cb10
int GfxConst::FUN_0077cb10(unsigned a, unsigned b)
{
    int n1 = *(int*)((char*)this + 0xc) + 1;
    char* elem = (char*)this + n1 * 0x10;
    *(unsigned*)elem = a;
    ((ImgElt*)(elem + 4))->GetImageResource(b);
    *(int*)((char*)this + 0xc) += 1;
    return *(int*)((char*)this + 0xc) - 1;
}

// @ 0x0077cb40
void __cdecl FUN_0077cb40(unsigned reg, unsigned p2, int isVS)
{
    float v[4];
    v[0] = g_16f6e60[0];
    v[1] = g_16f6e60[1];
    v[2] = g_16f6e60[2];
    v[3] = g_16f6e60[3];
    float* fade = (float*)g_16f6ebc;
    if (v[3] == 0.0f) {
        float lit[4];
        lit[0] = 3.0f;
        lit[1] = 3.0f;
        lit[2] = 2.0f;
        lit[3] = 1.0f;
        float shadow[4];
        shadow[0] = 0.3f;
        shadow[1] = 0.3f;
        shadow[2] = 0.3f;
        shadow[3] = 1.0f;
        float in[4];
        in[0] = g_lights0[8];
        in[1] = g_lights0[9];
        in[2] = g_lights0[10];
        in[3] = g_lights0[11];
        float out[4];
        FUN_011fca60(out, in);
        if (out[2] <= 0.2f) {
            v[0] = shadow[0];
            v[1] = shadow[1];
            v[2] = shadow[2];
            v[3] = shadow[3];
        } else {
            v[0] = lit[0];
            v[1] = lit[1];
            v[2] = lit[2];
            v[3] = lit[3];
        }
    } else if (v[3] == 0.5f) {
        v[3] = fade ? fade[0] : 1.0f;
    } else if (fade) {
        float m[16];
        FUN_007779e0(FUN_011f1120(), 0, m);
        float dist = (float)sqrt(m[12] * m[12] + (m[13] * m[13] + m[14] * m[14]));
        float k = (dist - fade[1]) / (fade[2] - fade[1]);
        k = k < 0.0f ? 0.0f : k;
        k = k > 1.0f ? 1.0f : k;
        v[3] = (k * 0.975f + 0.025f) * fade[0];
    } else {
        v[3] = 1.0f;
    }
    if (isVS)
        SETVS(g_pDevice, reg, v, 1);
    else
        SETPS(g_pDevice, reg, v, 1);
}

// @ 0x0077cd50
void __cdecl FUN_0077cd50(unsigned reg, unsigned count, int isVS)
{
    int* base = (int*)g_16f6e64;
    if (base == 0)
        return;
    int n = base[0];
    float t = (float)base[1] * *g_16f6ec8;
    int i0 = FloorToInt(t);
    float* cur = (float*)((char*)base + 0xc + (i0 % n) * 0x110);
    const float* data = cur;
    float lerped[4 * 16 + 4];
    if (((unsigned char*)base)[8]) {
        int i1 = CeilToInt(t);
        const float* next = (const float*)((char*)base + 0xc + (i1 % n) * 0x110);
        float frac = t - (float)i0;
        float inv = 1.0f - frac;
        for (int i = 0; i < 4 * 16 + 4; ++i)
            lerped[i] = cur[i] * inv + next[i] * frac;
        data = lerped;
    }
    if (isVS)
        SETVS(g_pDevice, reg, data, count);
    else
        SETPS(g_pDevice, reg, data, count);
}

// @ 0x0077d130
float* __fastcall FUN_0077d130(float* p)
{
    p[0] = g_1632e28;
    p[1] = g_1632e2c;
    p[2] = g_1632e30;
    p[3] = g_1632e34;
    return p;
}

// @ 0x0077d170
float* __fastcall FUN_0077d170(float* p)
{
    __m128 z = _mm_setzero_ps();
    _mm_store_ss(p + 0, z);
    _mm_store_ss(p + 4, z);
    _mm_store_ss(p + 1, z);
    _mm_store_ss(p + 2, z);
    _mm_store_ss(p + 3, z);
    _mm_store_ss(p + 5, z);
    _mm_store_ss(p + 6, z);
    _mm_store_ss(p + 7, z);
    _mm_store_ss(p + 8, z);
    _mm_store_ss(p + 9, z);
    _mm_store_ss(p + 10, z);
    _mm_store_ss(p + 11, z);
    _mm_store_ss(p + 12, z);
    _mm_store_ss(p + 13, z);
    _mm_store_ss(p + 14, z);
    _mm_store_ss(p + 15, z);
    return p;
}

// @ 0x0077d1d0
CtorObj* __fastcall FUN_0077d1d0(CtorObj* p)
{
    p->vtbl = &g_vtbl_13ef094;
    _InterlockedExchange(&p->refcount, 0);
    p->vtbl = &g_vtbl_140e878;
    p->field2 = 0;
    p->field3 = 0;
    p->field4 = 0;
    return p;
}

// @ 0x0077d200
void __cdecl FUN_0077d200(unsigned reg, unsigned p2, int isVS)
{
    if (g_16f6dd0 == 0)
        return;
    const float* src = (const float*)g_16f85ac_s0077_c8b0;
    float in[16];
    in[0] = src[0];
    in[1] = src[1];
    in[2] = src[2];
    in[3] = 0.0f;
    in[4] = src[4];
    in[5] = src[5];
    in[6] = src[6];
    in[7] = 0.0f;
    in[8] = src[8];
    in[9] = src[9];
    in[10] = src[10];
    in[11] = 0.0f;
    in[12] = src[12];
    in[13] = src[13];
    in[14] = src[14];
    in[15] = 1.0f;
    float out[16];
    FUN_0045eac0(out, in, g_16f6dd0);
    float data[12];
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 4; ++i)
            data[j * 4 + i] = out[i * 4 + j];
    }
    if (isVS)
        SETVS(g_pDevice, reg, data, 3);
    else
        SETPS(g_pDevice, reg, data, 3);
}

// @ 0x0077d450
WireObj* WireObj::CopyWire(const WireObj* src)
{
    this->header = src->header;
    for (int i = 0; i < 6; ++i) {
        const WireElem* s = &src->elems[i];
        WireElem* d = &this->elems[i];
        d->field0 = s->field0;
        WireRef* op = d->ref;
        WireRef* np = s->ref;
        if (np != op) {
            if (np)
                _InterlockedIncrement(&np->refcount);
            d->ref = np;
            if (op) {
                _InterlockedDecrement(&op->refcount);
                if (_InterlockedExchangeAdd(&op->refcount, 0) < 1)
                    _InterlockedIncrement(&op->refcount);
                else
                    _InterlockedExchangeAdd(&op->refcount, 0);
            }
        }
        d->b0 = s->b0;
        d->b1 = s->b1;
        d->b2 = s->b2;
        d->b3 = s->b3;
        d->flag = s->flag;
    }
    return this;
}

// @ 0x0077d510
void Vec4Vector::DoInsertValues(Vec4* pos, unsigned n, const Vec4* value)
{
    Vec4* end = this->end;
    unsigned freeSlots = (unsigned)((char*)this->cap - (char*)end) >> 4;
    if (n > freeSlots) {
        Vec4* begin = this->begin;
        unsigned oldCount = (unsigned)((char*)end - (char*)begin) >> 4;
        unsigned newCap = oldCount * 2;
        if (oldCount == 0)
            newCap = 1;
        if (newCap <= oldCount + n)
            newCap = oldCount + n;
        Vec4* buf = newCap ? (Vec4*)FUN_00f473a0(newCap * 16, kAllocName, 0, 0, kAllocFile, 0xd1) : 0;
        Vec4* mid = (Vec4*)FUN_0047c1c0(begin, pos, buf);
        FUN_0047cae0(mid, n, value, pos);
        Vec4* newEnd = (Vec4*)FUN_0047c1c0(pos, end, mid + n);
        if (begin && begin != this->fixedBuf)
            FUN_00f47380(begin);
        this->begin = buf;
        this->end = newEnd;
        this->cap = buf + newCap;
        return;
    }
    if (n == 0)
        return;
    Vec4 tmp = *value;
    unsigned after = (unsigned)((char*)end - (char*)pos) >> 4;
    if (n >= after) {
        unsigned extra = n - after;
        FUN_0047cae0(end, extra, &tmp, pos);
        Vec4* oldEnd = end;
        this->end = end + extra;
        void* scratch;
        FUN_0047a500(&scratch, pos, oldEnd, this->end, pos);
        this->end += after;
        FUN_00898580(pos, oldEnd, &tmp);
    } else {
        Vec4* split = end - n;
        void* scratch;
        FUN_0047a500(&scratch, split, end, end, pos);
        this->end = end + n;
        FUN_00edba80(pos, split, end);
        FUN_00898580(pos, pos + n, &tmp);
    }
}

// @ 0x0077d6c0
void* __stdcall FUN_0077d6c0(unsigned n, const void* first, const void* last)
{
    void* p = n ? FUN_00f473d0(n << 4, 0x10, 0, kAllocName, 0, 0, kAllocFile, 0xe5) : 0;
    FUN_00706ab0(first, last, p);
    return p;
}

// @ 0x0077d710
void* __cdecl FUN_0077d710(DescObj* desc)
{
    unsigned short kind = desc->kind;
    if (kind == 0x200)
        return 0;
    if (kind != 0x20d) {
        KindObj* obj = (KindObj*)FUN_00f473a0((unsigned)desc->size + 0xc, kAllocName, 0, 0, 0, 0);
        if (obj) {
            obj->payload = 0;
            obj->vtbl = &g_vtbl_13ef094;
            obj->kind = kind;
            obj->size = desc->size;
        }
        obj->payload = (char*)obj + 0xc;
        memcpy((char*)obj + 0xc, desc->data, desc->size);
        return obj;
    }
    void* src = desc->data;
    KindObj* obj = (KindObj*)FUN_00f473a0(0x70, kAllocName, 0, 0, 0, 0);
    if (obj)
        obj = (KindObj*)FUN_0040d010(obj, 0);
    ((WireObj*)((char*)obj + 0xc))->CopyWire((const WireObj*)src);
    return obj;
}

// @ 0x0077f020
void ShadowEffectsLayer_s0077f020::DrawLayer(unsigned int layer, unsigned int flags,
    SP::cViewer const* const* const viewers, SP::cRenderStats* stats)
{
    mLayer->DrawLayer(layer, 0x12, viewers, stats);
}
