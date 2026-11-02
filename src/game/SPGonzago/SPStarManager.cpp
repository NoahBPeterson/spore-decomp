// src/game/SPGonzago/SPStarManager.cpp -- migrated from slice(s) s013249a0, s006860e0, s00512840, s00512400, s00511670, s005107d0, s0050e850, s013277d0, s0050f8b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPStarManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/ResourceMan/KeyFilter.h"
#include "SP/cPropertyList.h"

// ---- items of slice s0050f8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { unsigned int s[N]; }
void* EASTL_Allocate(void* alloc, unsigned int n, unsigned int align, unsigned int offset);  // 0x0042dee0
void EASTL_allocator_deallocate(void* p);                                                    // 0x00f47380
void FixedVec_Destroy();   // 0x004c0b80 (called on an element address)
struct Keyed { char pad[0x60]; float k60; float k64; };
inline float KeyOf(Keyed* p) { return p->k64 - p->k60; }
inline bool StopCmp(Keyed* value, Keyed* cur, uint8_t desc)
{
    const float a = KeyOf(value);
    const float b = KeyOf(cur);
    return desc ? (b <= a) : (a <= b);
}
void QuickSortCmp(Keyed** first, Keyed** last, int n, uint8_t desc);   // 0x0050f950
Keyed** MedianCmp(Keyed** a, Keyed** b, Keyed** c, uint8_t d1, uint8_t d2);  // 0x005111b0
Keyed** GetPartitionCmp(Keyed** first, Keyed** last, Keyed* pivot);     // 0x005114f0
void PartialSortCmp(Keyed** first, Keyed** middle, Keyed** last, uint8_t desc);  // 0x00511670
void* CopyCommit(Keyed** first, Keyed** last, Keyed** dest);  // 0x00511d50
void UninitRelocateCommit(void* first, void* last, void* dest);           // 0x00511880
void QuickSortU32(uint32_t* first, uint32_t* last, int n);   // 0x005100c0
void PartialSortU32(uint32_t* first, uint32_t* middle, uint32_t* last);  // 0x00511900
struct FixedVec_s0050_f8b0 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[3];
    uint32_t mBuf[16];
    void Destroy();
};
struct Base100_s0050_f8b0 {
    FixedVec_s0050_f8b0 vec;
    Base100_s0050_f8b0();
    Base100_s0050_f8b0(const Base100_s0050_f8b0&);
};
struct Elem100_s0050_f8b0 : Base100_s0050_f8b0 {
    float f58, f5c, f60;
    Elem100_s0050_f8b0() : f58(0), f5c(0), f60(0) {}
};
struct T12 { uint32_t a, b, c; };
Elem100_s0050_f8b0* Relocate100(Elem100_s0050_f8b0* first, Elem100_s0050_f8b0* last, Elem100_s0050_f8b0* dest);  // 0x00511d50
void RelocateCommit100(Elem100_s0050_f8b0* first, Elem100_s0050_f8b0* last, Elem100_s0050_f8b0* dest); // 0x00511880
void UninitCopy100(Elem100_s0050_f8b0* first, Elem100_s0050_f8b0* last, Elem100_s0050_f8b0* dest);   // 0x00511be0
Elem100_s0050_f8b0* UninitCopy100b(Elem100_s0050_f8b0* first, Elem100_s0050_f8b0* last, Elem100_s0050_f8b0* dest); // 0x00510080
void CopyBackward100(Elem100_s0050_f8b0* first, Elem100_s0050_f8b0* last, Elem100_s0050_f8b0* resultEnd); // 0x00511d00
void UninitFillN100(Elem100_s0050_f8b0* first, uint32_t n, const Elem100_s0050_f8b0& value);  // 0x00511c80
void Fill100(Elem100_s0050_f8b0* first, Elem100_s0050_f8b0* last, const Elem100_s0050_f8b0& value);      // 0x005117d0
void Copy100(Elem100_s0050_f8b0* first, Elem100_s0050_f8b0* last, Elem100_s0050_f8b0* dest);             // 0x00511790
struct Vec100 {
    Elem100_s0050_f8b0* mpBegin;
    Elem100_s0050_f8b0* mpEnd;
    Elem100_s0050_f8b0* mpCapacity;
    uint32_t mAlloc;
    Elem100_s0050_f8b0* mFixed;

    void DoInsertValues(Elem100_s0050_f8b0* position, uint32_t n, const Elem100_s0050_f8b0& value);
};
void* UninitCopy12a(void* first, void* last, void* dest);   // 0x004b66b0
void* UninitCopy12b(void* first, void* last, void* dest);   // 0x00475ef0
void* UninitCopy12c(void* first, void* last, void* dest);   // 0x004b6bf0
struct Vec12I {
    T12* mpBegin;
    T12* mpEnd;
    T12* mpCapacity;
    uint32_t mAlloc;

    void insert(T12* position, T12* first, T12* last);
};
// ---- items of slice s0050f8b0 end

// ---- items of slice s013277d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SimAttr {
    const char* name;    // +0x00
    uint32_t    key;     // +0x04
    uint32_t    offset;  // +0x08
    uint32_t    r0c;     // +0x0c  (never assigned)
    uint32_t    r10;     // +0x10  (never assigned)
    uint32_t    r14;     // +0x14  (never assigned)
    uint32_t    z18;     // +0x18
    uint32_t    z1c;     // +0x1c
    void*       dflt;    // +0x20  Simulator::Attribute::DefaultOffset (0x692ca0)
    void*       w24;     // +0x24
    void*       w28;     // +0x28
    void*       w2c;     // +0x2c
    void*       w30;     // +0x30
    void*       w34;     // +0x34  0xb1fbf0 UTFWin::Window::Initialize
    void*       w38;     // +0x38
};
#define ROW(dst, nm, ky, of, f24, f28, f2c, f30, f38)   \
    attr.name   = (const char*)(nm);                     \
    attr.key    = (uint32_t)(ky);                        \
    attr.z18    = 0;                                     \
    attr.z1c    = 0;                                     \
    attr.dflt   = (void*)0x692ca0;                       \
    attr.w24    = (void*)(f24);                          \
    attr.w28    = (void*)(f28);                          \
    attr.w2c    = (void*)(f2c);                          \
    attr.w30    = (void*)(f30);                          \
    attr.offset = (uint32_t)(of);                        \
    attr.w34    = (void*)0xb1fbf0;                       \
    attr.w38    = (void*)(f38);                          \
    *(SimAttr*)(dst) = attr;
#define ROWF(dst, nm, ky, of, f24, f28, f2c, f30, f34, f38) \
    attr.name   = (const char*)(nm);                         \
    attr.key    = (uint32_t)(ky);                            \
    attr.z18    = 0;                                         \
    attr.z1c    = 0;                                         \
    attr.dflt   = (void*)0x692ca0;                           \
    attr.w24    = (void*)(f24);                              \
    attr.w28    = (void*)(f28);                              \
    attr.w2c    = (void*)(f2c);                              \
    attr.w30    = (void*)(f30);                              \
    attr.offset = (uint32_t)(of);                            \
    attr.w34    = (void*)(f34);                              \
    attr.w38    = (void*)(f38);                              \
    *(SimAttr*)(dst) = attr;
// ---- items of slice s013277d0 end

// ---- items of slice s0050e850 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) { return p; }

struct T20 { uint32_t a[5]; };
void __cdecl UninitCopy20(void** out, T20* first, T20* last, T20* dest, uint8_t tag);  // 0x0050f7f0
template <class In, class Out>
inline Out CopyImpl(In first, In last, Out dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}
template <class In, class Out>
inline Out Copy(In first, In last, Out dest)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return CopyImpl(first, last, dest);
}
template <class T>
inline void Destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; Vector3() {} Vector3(const Vector3&); };  // 0x004098a0
struct T24 { Vector3 v[2]; };
struct FixedVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[3];
    uint32_t mBuf[16];
    void Destroy();   // 0x004c0b80
    uint32_t* erase(uint32_t* first, uint32_t* last);                    // 0x004769b0
    void assign(uint32_t* first, uint32_t* last, uint8_t tag);           // 0x0042c750
    FixedVec& operator=(const FixedVec& o)
    {
        if (this != &o) {
            erase(mpBegin, mpEnd);
            uint8_t tag;
            assign(o.mpBegin, o.mpEnd, tag);
        }
        return *this;
    }
};
struct Base100 {
    FixedVec vec;
    Base100();
    Base100(const Base100&);
};
struct Elem100 : Base100 {
    float f58, f5c, f60;
    Elem100() : f58(0), f5c(0), f60(0) {}
    Elem100& operator=(const Elem100& x);   // 0x0050f210
};
struct Vec12 {
    T12* mpBegin;
    T12* mpEnd;
    T12* mpCapacity;
    uint32_t mAlloc;

    T12* erase(T12* first, T12* last);
};
struct Vec24Full {
    T24* mpBegin;
    T24* mpEnd;
    T24* mpCapacity;
    uint32_t mAlloc;

    void DoInsertValues(T24* position, uint32_t n, const T24& value);
};
T24* UninitCopy24(T24* first, T24* last, T24* dest)
{
    T24* d = dest;
    for (; first != last; ++first, ++d)
        ::new (d) T24(*first);
    return d;
}
void UninitFillN24(T24* first, uint32_t n, const T24& value)
{
    for (; n > 0; --n, ++first)
        ::new (first) T24(value);
}
void CopyBackward24(T24* first, T24* last, T24* resultEnd)
{
    while (last != first) {
        --last;
        --resultEnd;
        *resultEnd = *last;
    }
}
void Fill24(T24* first, T24* last, const T24& value)
{
    for (; first != last; ++first)
        *first = value;
}
// ---- items of slice s0050e850 end

// ---- items of slice s005107d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0051_07d0 { float x, y, z; Vector3_s0051_07d0() {} Vector3_s0051_07d0(const Vector3_s0051_07d0& o) { x = o.x; y = o.y; z = o.z; } };
struct T24_s0051_07d0 { Vector3_s0051_07d0 a, b; T24_s0051_07d0() {} T24_s0051_07d0(const T24_s0051_07d0& o); };
inline bool Le(Keyed* a, Keyed* b, uint8_t desc)
{
    const float x = KeyOf(a);
    const float y = KeyOf(b);
    return desc ? (y > x) : (x > y);
}
struct P2 { int first; int second; };
void* UninitCopyP2A(void* first, void* last, void* dest);   // 0x0040cce0
void* UninitCopyP2B(void* first, void* last, void* dest);   // 0x00476290
struct Vec8I {
    P2* mpBegin;
    P2* mpEnd;
    P2* mpCapacity;
    uint32_t mAlloc;

    void insert(P2* position, P2* first, P2* last);
};
void* UninitCopy24A(void* first, void* last, void* dest);   // 0x004b?? (24-byte)
void* UninitCopy24B(void* first, void* last, void* dest);
void* UninitCopy24C(void* first, void* last, void* dest);
struct Vec24I {
    T24_s0051_07d0* mpBegin;
    T24_s0051_07d0* mpEnd;
    T24_s0051_07d0* mpCapacity;
    uint32_t mAlloc;

    void insert(T24_s0051_07d0* position, T24_s0051_07d0* first, T24_s0051_07d0* last);
};
// ---- items of slice s005107d0 end

// ---- items of slice s00511670 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s0051_1670() { uint32_t slots[N]; }
template <> inline void ScratchSlots_s0051_1670<0>() {}
namespace eastl {
class allocator_s0051_1670 { public: allocator_s0051_1670() {} };
}
namespace eastl {
template <typename Iterator> class generic_iterator { public:
    Iterator mIterator;
    generic_iterator(const Iterator& x) : mIterator(x) {}
    Iterator base() const { return mIterator; }
};
}
namespace eastl {
template <typename T> struct generic_iterator<T*> {
    T* mIterator;
    generic_iterator(T* x) : mIterator(x) {}
    T* base() const { return mIterator; }
    T& operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
};
}
namespace eastl {
template <typename I>
inline bool operator!=(const generic_iterator<I>& a, const generic_iterator<I>& b) { return a.mIterator != b.mIterator; }
}
struct Obj {
    char pad[0x60];
    float mMin;   // +0x60
    float mMax;   // +0x64
};
namespace eastl {
template <typename RandomAccessIterator, typename Distance, typename T>
inline void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, T value)
{
    for (Distance parentPosition = (position - 1) >> 1;
         (position > topPosition) && (*(first + parentPosition) < value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}
}
struct Vector3_s0051_1670 {
    float x, y, z;
    Vector3_s0051_1670() {}
    Vector3_s0051_1670(const Vector3_s0051_1670& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vector3Diff : Vector3_s0051_1670 {};
Vector3Diff operator-(const Vector3_s0051_1670& a, const Vector3_s0051_1670& b);   // 0x0041db10
Vector3_s0051_1670 Cross(const Vector3_s0051_1670& a, const Vector3_s0051_1670& b);           // 0x0044e460
Vector3_s0051_1670 Normalize(const Vector3_s0051_1670& v);                         // 0x00436ce0
struct TriMesh {
    char pad0[8];
    Vector3_s0051_1670* mpVertices;       // +0x08
    char pad1[0x58 - 0x0c];
    int* mpTriangles;          // +0x58 (3 vertex indices per triangle)
    Vector3_s0051_1670 GetTriangleNormal(int i);
};
struct Elem1C { uint32_t d[7]; };
struct Elem18 { uint32_t d[6]; };
struct VecBase1C {
    Elem1C* mpBegin; Elem1C* mpEnd; Elem1C* mpCapacity; uint32_t mAllocator[2];
    VecBase1C(const eastl::allocator_s0051_1670&) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~VecBase1C();                                     // 0x005141b0
};
struct Vec1C : VecBase1C {
    Vec1C(const eastl::allocator_s0051_1670& a = eastl::allocator_s0051_1670()) : VecBase1C(a) {}
    ~Vec1C() { for (Elem1C* p = mpBegin; p < mpEnd; ++p) ; ScratchSlots_s0051_1670<3>(); }
    Elem1C* erase(Elem1C* first, Elem1C* last);        // 0x00514110
    void clear() { erase(mpBegin, mpEnd); }
};
struct VecBase18 {
    Elem18* mpBegin; Elem18* mpEnd; Elem18* mpCapacity; uint32_t mAllocator[2];
    VecBase18(const eastl::allocator_s0051_1670&) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~VecBase18();                                     // 0x004fd940
};
struct Vec18 : VecBase18 {
    Vec18(const eastl::allocator_s0051_1670& a = eastl::allocator_s0051_1670()) : VecBase18(a) {}
    ~Vec18() { for (Elem18* p = mpBegin; p < mpEnd; ++p) ; ScratchSlots_s0051_1670<3>(); }
    Elem18* erase(Elem18* first, Elem18* last);        // 0x00514210
    void clear() { erase(mpBegin, mpEnd); }
};
struct Less { Less() {} };
struct Map28 {
    uint32_t d[6];
    Map28(const Less& c = Less());                    // 0x00513e20
    ~Map28();                                         // 0x00513e40
    void clear();                                     // 0x00513f20
};
struct Owner {
    Vec1C mA;     // +0x00
    Vec18 mB;     // +0x14
    Map28 mC;     // +0x28
    Owner();
    ~Owner();
    void Clear();
};
// ---- items of slice s00511670 end

// ---- items of slice s00512400 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RenderCfg;
struct JobAlloc {
    void Begin();      // 0x00513ec0
    void* Get();       // 0x00513e90
};
struct RenderJobSink {
    uint8_t pad[0x28];
    JobAlloc alloc;    // +0x28
    void InitRenderJob(RenderCfg* cfg, uint32_t* pBones, uint32_t id, float* pos, float* color,
                       uint32_t a6, uint32_t a7);
};
struct RenderCfg {
    uint8_t pad0[0x10];
    float f10;        // 0x10
    float f14;        // 0x14
    float f18;        // 0x18
    uint8_t pad1[0x40 - 0x1c];
    float f40;        // 0x40
    uint8_t pad2[0x5c - 0x44];
    float f5c;        // 0x5c
    float f60;        // 0x60
    float f64;        // 0x64
    float f68;        // 0x68
    float f6c;        // 0x6c
    uint8_t pad3[0x74 - 0x70];
    float f74;        // 0x74
    uint8_t pad4[0x7c - 0x78];
    float f7c;        // 0x7c
    float f80;        // 0x80
    float f84;        // 0x84
    uint8_t b88;      // 0x88
    uint8_t pad5[0x9c - 0x89];
    uint8_t b9c;      // 0x9c
    uint8_t pad6[3];
    uint8_t ba0;      // 0xa0
    uint8_t pad7[3];
    uint8_t ba4;      // 0xa4

    void BuildMatrix(float* p5, uint32_t p6, uint32_t p7, int mode, float* out0, float* out1, int z); // 0x004fe510
};
inline float Saturate(float x)
{
    float f = 0.0f;
    if (x >= 0.0f)
        f = x;
    f = f * 255.0f;
    if (f >= 255.0f)
        f = 255.0f;
    return f;
}
inline int RoundInt(float x) { return (int)(x + 0.5f); }
// ---- items of slice s00512400 end

// ---- items of slice s00512840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gDecalAngleBias;   // 0x015DD788
extern float gDecalAngleScale;  // 0x015DD784
struct RwVector2 {
    float x, y;
    RwVector2() {}
    RwVector2(float ax, float ay) : x(ax), y(ay) {}
};
RwVector2 operator+(const RwVector2& a, const RwVector2& b);  // 0x004FE7F0
struct Vector2 {
    float x, y;
    Vector2& operator=(const RwVector2& o) {
        x = o.x;
        y = o.y;
        return *this;
    }
    float& operator[](int i) { return (&x)[i]; }
};
struct Vector3_s0051_2840 {
    float x, y, z;
    float Dot(const Vector3_s0051_2840& o) const { return x * o.x + y * o.y + z * o.z; }
};
inline float Dot(const Vector3_s0051_2840& a, const Vector3_s0051_2840& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
float FastAcos(float x);                              // 0x00513930
bool IsEdgeInside(const Vector2& a, const Vector2& b);  // 0x00513BA0
static const signed char kNextEdge[3] = {1, 1, -2};   // 0x013F18D0
static const signed char kPrevEdge[3] = {2, -1, -1};  // 0x013F18D8
inline void GetTriangleEdges(uint32_t e, uint32_t& next, uint32_t& prev) {
    uint32_t edge = e;
    uint32_t m = edge - (edge / 3) * 3;
    next = kNextEdge[m] + edge;
    prev = kPrevEdge[m] + edge;
}
struct FillEntry {
    uint32_t edge;
    int a;
    int b;
    FillEntry() {}
    FillEntry(int e, int va, int vb) : edge(e), a(va), b(vb) {}
};
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];

    bool empty() const;                     // out of line
    void push_back();                       // out of line
    void push_back(const T& v);             // out of line
    void resize(uint32_t n);                // out of line
    void resize(uint32_t n, const T& v);    // out of line
    T* erase(T* first, T* last);            // out of line
    T& back() { return *(mpEnd - 1); }
    void pop_back() { --mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
};
struct Mesh {
    uint32_t pad0[2];
    SpVector<Vector3_s0051_2840> mPositions;      // +0x08
    SpVector<Vector3_s0051_2840> mNormals;        // +0x1c
    SpVector<Vector2> mUVs;            // +0x30
    uint32_t pad44[5];
    SpVector<int> mPositionIndices;    // +0x58
    SpVector<int> mNormalIndices;      // +0x6c
    SpVector<int> mUVIndices;          // +0x80
    SpVector<uint32_t> mOpposite;      // +0x94
};
struct HalfEdge {
    uint32_t edge;
    bool seamless;
};
struct MeshAccessor {
    const Vector3_s0051_2840* mPositions;      // -0x20
    const Vector3_s0051_2840* mNormals;        // -0x1c
    const Vector2* mUVs;            // -0x18
    const int* mPositionIndices;    // -0x14
    const int* mNormalIndices;      // -0x10
    const int* mUVIndices;          // -0x0c
    const uint32_t* mOpposite;      // -0x08

    MeshAccessor(const Mesh& mesh);    // 0x005139F0
    const Vector3_s0051_2840& Normal(uint32_t e) const { return mNormals[mNormalIndices[e]]; }
    const Vector3_s0051_2840& Position(uint32_t e) const { return mPositions[mPositionIndices[e]]; }
    const Vector2& UV(uint32_t e) const { return mUVs[mUVIndices[e]]; }
    HalfEdge Opposite(uint32_t e) const;  // 0x00513A90
};
struct DecalParams {
    int mStartTriangle;     // +0x00
    Vector3_s0051_2840 mDir;           // +0x04
    Vector3_s0051_2840 mUAxis;         // +0x10
    Vector3_s0051_2840 mVAxis;         // +0x1c
    RwVector2 mOffset;      // +0x28
    int mBatchData[3];      // +0x30
    int mVertexData[2];     // +0x3c
    uint8_t mFlags[4];      // +0x44
};
struct DecalVertex {  // 0x1c
    Vector2 mUV;        // +0x00
    int mData[2];       // +0x08
    Vector2 mDecalUV;   // +0x10
    float mFade;        // +0x18
};
inline void CopyVertex(DecalVertex& d, const DecalVertex& s) { d = s; }
struct DecalBatch {  // 0x18
    int mStart;          // +0x00
    int mCount;          // +0x04
    uint8_t mFlags[4];   // +0x08
    int mData[3];        // +0x0c
};
SpVector<uint8_t> sVisitedTriangles;  // 0x015DD75C
SpVector<FillEntry> sFillStack;       // 0x015DD770
struct cDecalBuilder {
    SpVector<DecalVertex> mVertices;  // +0x00
    SpVector<DecalBatch> mBatches;    // +0x14

    void Project(const Mesh& mesh, const DecalParams& params);
};
// ---- items of slice s00512840 end

// ---- items of slice s006860e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* p) { return *(void***)p; }
struct HashIter {
    void*  mpNode;      // +0x00
    void** mpBucket;    // +0x04
};
struct HashIterPair {
    HashIter first;     // +0x00
    uint8_t  second;    // +0x08
    uint8_t  pad[3];
};
struct Hashtable {
    char pad00[0x04];   // +0x00
    void** mpBucket;    // +0x04
    int    mnBucket;    // +0x08
    int    mnCount;     // +0x0c
    char pad10[0x08];   // +0x10..+0x17 (editor map is 0x18 bytes)
    void FreeNodes();                       // va 00685ed0
    HashIter find(const void* key);         // va 00685f30
    HashIter erase(HashIter i);             // va 006859b0
    HashIterPair insert(const void* value, const void* hint); // va 00685f90
};
struct cPropertyList {
    void* vtbl;                 // +0x00
    volatile int mRef;          // +0x04
    uint32_t f08, f0c, f10, f14;
    Hashtable mPropertyMap;     // +0x18 (embedded hashtable: FreeNodes on this)
    void* mModCount;            // +0x30 (retail: pointer to a refcounted object)
    uint32_t f34;               // +0x34
    bool Read(void* stream);    // 0x006a2f60
    cPropertyList();            // 0x006a1c40 (Editor::cPropertyList ctor, out of slice)
    ~cPropertyList();
};
// ---- items of slice s006860e0 end

// ---- items of slice s013249a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0132_49a0; 
}
typedef eastl::string8_s0132_49a0 string8_s0132_49a0;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0132_49a0&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute
{
    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
bool Read_00bb67d0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba73b0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00badf20(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bab080(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba94e0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ba7420(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ba8250(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bab200(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ba66d0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba66f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b5cb60(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b5cb80(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ba6710(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba6730(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bb1660(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba8280(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bb1830(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba7490(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b04e00(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c761c0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bb19d0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba7510(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bab620(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba7590(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);          // 0x00572810
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);        // 0x00572840
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0132_49a0& text, void* pData);               // 0x00693090
}
namespace Simulator {
template<typename T> bool AlwaysValid();                                               // 0x00b1fbf0
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0132_49a0& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
template<typename T> void ReadTextMap(const string8_s0132_49a0& text, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694bd0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00b6f860();
}
namespace Simulator {
bool Validate_00ba7450();
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool Validate_00ba6690();
}
namespace Simulator {
bool Validate_00d011e0();
}
namespace Simulator {
bool ToXml_00c51440(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00baa2b0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00bab380(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00eafe40(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00bab4d0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00bab740(void* pData, const char* pName, int depth);
}
namespace Simulator {
extern uint32_t cStarManager_sGameTimeManagerContainer;       // 0x01689644
}
namespace Simulator {
extern uint32_t cStarManager_sRelationshipManagerContainer;   // 0x01689640
}
namespace Simulator {
extern uint32_t cStarManager_sNameCountMap;                   // 0x0156c64c
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot cStarManager_sAttributes[19];   // 0x0156c668
}
namespace Simulator {
#define GRID_ATTR     Read_00bb67d0, Write_00ba73b0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00c51440
}
namespace Simulator {
#define STARVEC_ATTR  Read_00badf20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define HOMEVEC_ATTR  Read_00bab080, Write_00ba94e0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba7450, ToXml_00baa2b0
}
namespace Simulator {
#define ID_ATTR       Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0
}
namespace Simulator {
#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cStarManager_sAttributes[IDX] = a; }
}
// ---- items of slice s013249a0 end

// @ 0x0050f210
Elem100& Elem100::operator=(const Elem100& x)
{
    vec = x.vec;
    f58 = x.f58;
    f5c = x.f5c;
    f60 = x.f60;
    return *this;
}

// @ 0x0050f290
void Vec24Full::DoInsertValues(T24* position, uint32_t n, const T24& value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < n) {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
        T24* const pNewData = nNewSize ? (T24*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(T24), 4, 0) : 0;
        T24* pNewEnd = UninitCopy24(mpBegin, position, pNewData);
        UninitFillN24(pNewEnd, n, value);
        pNewEnd = UninitCopy24(position, mpEnd, pNewEnd + n);
        for (T24* p = mpBegin; p < mpEnd; ++p) {}
        if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
            void* q = mpBegin;
            EASTL_allocator_deallocate(q);
        }
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n != 0) {
        const T24 valueSaved(value);
        const uint32_t nExtra = (uint32_t)(mpEnd - position);
        if (n < nExtra) {
            UninitCopy24(mpEnd - n, mpEnd, mpEnd);
            T24* const pEnd = mpEnd;
            mpEnd += n;
            CopyBackward24(position, pEnd - n, pEnd);
            Fill24(position, position + n, valueSaved);
        } else {
            UninitFillN24(mpEnd, n - nExtra, valueSaved);
            T24* const pEnd = mpEnd;
            mpEnd += n - nExtra;
            UninitCopy24(position, pEnd, mpEnd);
            mpEnd += nExtra;
            Fill24(position, pEnd, valueSaved);
        }
    }
}

// @ 0x0050f740
T12* Vec12::erase(T12* first, T12* last)
{
    T12* const position = Copy(last, mpEnd, first);
    Destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x0050f7f0
void __cdecl UninitCopy20(void** out, T20* first, T20* last, T20* dest, uint8_t tag)
{
    (void)tag;
    T20* d = dest;
    for (T20* p = first; p != last; ++p, ++d) {
        if (d) {
            for (int i = 0; i < 5; ++i)
                ((uint32_t*)d)[i] = ((uint32_t*)p)[i];
        }
    }
    *out = d;
}

// @ 0x0050f8b0
T12* UninitRelocate12(T12* first, T12* last, T12* dest)
{
    uint8_t tag = 0;
    (void)tag;
    ScratchSlots<6>();
    T12* d = dest;
    for (T12* p = first; p != last; ++p, ++d) {
        if (d) {
            d->a = p->a;
            d->b = p->b;
            d->c = p->c;
        }
    }
    for (T12* q = first; q != last; ++q) {}
    return d;
}

// @ 0x0050f950
void QuickSortCmp(Keyed** first, Keyed** last, int n, uint8_t desc)
{
    while (((int)(last - first) > 0x1c) && (n > 0)) {
        Keyed** p = MedianCmp(first, first + ((last - first) - ((int)(last - first) >> 31)) / 2, last - 1, desc, desc);
        Keyed** mid = GetPartitionCmp(first, last, *p);
        --n;
        QuickSortCmp(mid, last, n, desc);
        last = mid;
    }
    if (n == 0)
        PartialSortCmp(first, last, last, desc);
}

// @ 0x0050fa10
void InsertionSortCmp(Keyed** first, Keyed** last, uint8_t desc)
{
    if (first != last) {
        Keyed** iCurrent;
        Keyed** iNext;
        Keyed** iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            Keyed* const temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && !StopCmp(temp, *iCurrent, desc); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x0050fb30
void InsertionSortSimpleCmp(Keyed** first, Keyed** last, uint8_t desc)
{
    for (Keyed** current = first; current != last; ++current) {
        Keyed** end = current;
        Keyed** prev = current;
        Keyed* value = *current;
        for (--prev; !StopCmp(value, *prev, desc); --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// @ 0x0050fc30
void Vec100::DoInsertValues(Elem100_s0050_f8b0* position, uint32_t n, const Elem100_s0050_f8b0& value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < n) {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
        Elem100_s0050_f8b0* const pNewData = nNewSize ? (Elem100_s0050_f8b0*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(Elem100_s0050_f8b0), 4, 0) : 0;
        Elem100_s0050_f8b0* pNewEnd = UninitCopy100b(mpBegin, position, pNewData);
        UninitFillN100(pNewEnd, n, value);
        pNewEnd = Relocate100(position, mpEnd, pNewEnd + n);
        RelocateCommit100(position, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mFixed) {
            void* q = mpBegin;
            EASTL_allocator_deallocate(q);
        }
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    } else if (n != 0) {
        Elem100_s0050_f8b0 valueSaved(value);
        const uint32_t nExtra = (uint32_t)(mpEnd - position);
        if (n < nExtra) {
            UninitCopy100(mpEnd - n, mpEnd, mpEnd);
            Elem100_s0050_f8b0* const pEnd = mpEnd;
            mpEnd += n;
            CopyBackward100(position, pEnd - n, pEnd);
            Fill100(position, position + n, valueSaved);
        } else {
            UninitFillN100(mpEnd, n - nExtra, valueSaved);
            Elem100_s0050_f8b0* const pEnd = mpEnd;
            mpEnd += n - nExtra;
            Copy100(position, pEnd, mpEnd);
            mpEnd += nExtra;
            Fill100(position, pEnd, valueSaved);
        }
        for (Elem100_s0050_f8b0* p = mpBegin; p < mpEnd; ++p) {}
        FixedVec_Destroy();
    }
}

// @ 0x00510080
void* RelocateCommit(void* first, void* last, void* dest)
{
    uint8_t tag = 0;
    (void)tag;
    ScratchSlots<12>();
    void* p = CopyCommit((Keyed**)first, (Keyed**)last, (Keyed**)dest);
    UninitRelocateCommit(first, last, dest);
    return p;
}

// @ 0x005100c0
void QuickSortU32(uint32_t* first, uint32_t* last, int n)
{
    while (((int)(last - first) > 0x1c) && (n > 0)) {
        uint32_t* pEnd = last - 1;
        uint32_t* mid = first + (((int)(last - first)) / 2);
        uint32_t* pivot;
        if (*first < *mid) {
            if (*pEnd <= *mid) {
                pivot = pEnd;
                if (*pEnd <= *first)
                    pivot = first;
            } else {
                pivot = mid;
            }
        } else if (*first < *pEnd) {
            pivot = first;
        } else if (*mid < *pEnd) {
            pivot = pEnd;
        } else {
            pivot = mid;
        }
        const uint32_t value = *pivot;
        uint32_t* p = last;
        uint32_t* q = first;
        for (;;) {
            while (*q < value)
                ++q;
            do {
                --p;
            } while (value < *p);
            if (p <= q)
                break;
            const uint32_t t = *q;
            *q = *p;
            *p = t;
            ++q;
        }
        --n;
        QuickSortU32(q, last, n);
        last = q;
    }
    if (n == 0)
        PartialSortU32(first, last, last);
}

// @ 0x00510240
void InsertionSortU32(uint32_t* first, uint32_t* last)
{
    if (first != last) {
        uint32_t* iCurrent;
        uint32_t* iNext;
        uint32_t* iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const uint32_t temp(*iSorted);
            iNext = iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && (temp < *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x005102d0
void InsertionSortSimpleU32(uint32_t* first, uint32_t* last)
{
    for (uint32_t* current = first; current != last; ++current) {
        uint32_t* end(current);
        uint32_t* prev(current);
        const uint32_t value(*current);
        for (--prev; value < *prev; --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// @ 0x00510350
void Vec12I::insert(T12* position, T12* first, T12* last)
{
    if (first != last) {
        const uint32_t n = (uint32_t)(last - first);
        if ((uint32_t)(mpCapacity - mpEnd) < n) {
            const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
            const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
            const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
            T12* const pNewData = nNewSize ? (T12*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(T12), 4, 0) : 0;
            T12* pNewEnd = (T12*)UninitCopy12a(mpBegin, position, pNewData);
            pNewEnd = (T12*)UninitCopy12b(first, last, pNewEnd);
            pNewEnd = (T12*)UninitCopy12c(position, mpEnd, pNewEnd);
            for (T12* p = position; p != mpEnd; ++p) {}
            if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
                void* q = mpBegin;
                EASTL_allocator_deallocate(q);
            }
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        } else {
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            T12* const pOldEnd = mpEnd;
            if (n < nExtra) {
                for (uint32_t i = 0; i < n; ++i)
                    pOldEnd[i] = pOldEnd[i - n];
                for (T12* d = pOldEnd, *s = pOldEnd - n; d != position; ) {
                    --d;
                    --s;
                    *d = *s;
                }
                mpEnd = pOldEnd + n;
                for (uint32_t i = 0; i < n; ++i)
                    position[i] = first[i];
            } else {
                for (uint32_t i = 0; i < n - nExtra; ++i)
                    pOldEnd[i] = first[i];
                mpEnd = pOldEnd + (n - nExtra);
                for (uint32_t i = 0; i < nExtra; ++i)
                    mpEnd[i] = position[i];
                mpEnd += nExtra;
                for (uint32_t i = 0; i < nExtra; ++i)
                    position[i] = first[i + (n - nExtra)];
            }
        }
    }
}

// @ 0x005107d0
void Vec8I::insert(P2* position, P2* first, P2* last)
{
    if (first != last) {
        const uint32_t n = (uint32_t)(last - first);
        if ((uint32_t)(mpCapacity - mpEnd) < n) {
            const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
            const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
            const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
            P2* const pNewData = nNewSize ? (P2*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(P2), 4, 0) : 0;
            P2* pNewEnd = (P2*)UninitCopyP2A(mpBegin, position, pNewData);
            pNewEnd = (P2*)UninitCopyP2B(first, last, pNewEnd);
            pNewEnd = (P2*)UninitCopyP2A(position, mpEnd, pNewEnd);
            for (P2* p = position; p != mpEnd; ++p) {}
            if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
                void* q = mpBegin;
                EASTL_allocator_deallocate(q);
            }
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        } else {
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            P2* const pOldEnd = mpEnd;
            if (n < nExtra) {
                for (uint32_t i = 0; i < n; ++i)
                    pOldEnd[i] = pOldEnd[i - n];
                for (P2* d = pOldEnd, *s = pOldEnd - n; d != position; ) {
                    --d;
                    --s;
                    *d = *s;
                }
                mpEnd = pOldEnd + n;
                for (uint32_t i = 0; i < n; ++i)
                    position[i] = first[i];
            } else {
                for (uint32_t i = 0; i < n - nExtra; ++i)
                    pOldEnd[i] = first[i];
                mpEnd = pOldEnd + (n - nExtra);
                for (uint32_t i = 0; i < nExtra; ++i)
                    mpEnd[i] = position[i];
                mpEnd += nExtra;
                for (uint32_t i = 0; i < nExtra; ++i)
                    position[i] = first[i + (n - nExtra)];
            }
        }
    }
}

// @ 0x00510bc0
void Vec24I::insert(T24_s0051_07d0* position, T24_s0051_07d0* first, T24_s0051_07d0* last)
{
    if (first != last) {
        const uint32_t n = (uint32_t)(last - first);
        if ((uint32_t)(mpCapacity - mpEnd) < n) {
            const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
            const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
            const uint32_t nNewSize = (nPrevSize + n < nGrowSize) ? nGrowSize : (nPrevSize + n);
            T24_s0051_07d0* const pNewData = nNewSize ? (T24_s0051_07d0*)EASTL_Allocate(&mAlloc, nNewSize * sizeof(T24_s0051_07d0), 4, 0) : 0;
            T24_s0051_07d0* pNewEnd = (T24_s0051_07d0*)UninitCopy24A(mpBegin, position, pNewData);
            pNewEnd = (T24_s0051_07d0*)UninitCopy24B(first, last, pNewEnd);
            pNewEnd = (T24_s0051_07d0*)UninitCopy24C(position, mpEnd, pNewEnd);
            for (T24_s0051_07d0* p = position; p != mpEnd; ++p) {}
            if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
                void* q = mpBegin;
                EASTL_allocator_deallocate(q);
            }
            mpBegin = pNewData;
            mpEnd = pNewEnd;
            mpCapacity = pNewData + nNewSize;
        } else {
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            T24_s0051_07d0* const pOldEnd = mpEnd;
            if (n < nExtra) {
                for (uint32_t i = 0; i < n; ++i)
                    pOldEnd[i] = pOldEnd[i - n];
                for (T24_s0051_07d0* d = pOldEnd, *s = pOldEnd - n; d != position; ) {
                    --d;
                    --s;
                    *d = *s;
                }
                mpEnd = pOldEnd + n;
                for (uint32_t i = 0; i < n; ++i)
                    position[i] = first[i];
            } else {
                for (uint32_t i = 0; i < n - nExtra; ++i)
                    pOldEnd[i] = first[i];
                mpEnd = pOldEnd + (n - nExtra);
                for (uint32_t i = 0; i < nExtra; ++i)
                    mpEnd[i] = position[i];
                mpEnd += nExtra;
                for (uint32_t i = 0; i < nExtra; ++i)
                    position[i] = first[i + (n - nExtra)];
            }
        }
    }
}

// @ 0x00511140
T24_s0051_07d0::T24_s0051_07d0(const T24_s0051_07d0& o)
: a(o.a), b(o.b)
{
}

// @ 0x005111b0
Keyed** MedianCmp(Keyed** a, Keyed** b, Keyed** c, uint8_t desc)
{
    if (Le(*a, *b, desc)) {
        if (Le(*b, *c, desc))
            return b;
        if (Le(*a, *c, desc))
            return c;
        return a;
    }
    if (Le(*a, *c, desc))
        return a;
    if (Le(*b, *c, desc))
        return c;
    return b;
}

// @ 0x005114f0
Keyed** GetPartitionCmp(Keyed** first, Keyed** last, Keyed* pivot, uint8_t desc)
{
    for (;;) {
        while (Le(*first, pivot, desc))
            ++first;
        --last;
        while (Le(pivot, *last, desc))
            --last;
        if (first >= last)
            return first;
        Keyed* const t = *first;
        *first = *last;
        *last = t;
        ++first;
    }
}

// @ 0x005119f0
namespace eastl {
template <typename RandomAccessIterator, typename Compare> void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            eastl::adjust_heap<RandomAccessIterator, int, const Obj*, Compare>(first, parentPosition, heapSize, parentPosition, *(first + parentPosition), compare);
        } while (parentPosition != 0);
    }
}
}  // namespace eastl

// @ 0x00511a50
namespace eastl {
template <typename RandomAccessIterator, typename Distance, typename T, typename Compare> void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value, Compare compare)
{
    Distance childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    ScratchSlots_s0051_1670<5>();
    eastl::promote_heap<RandomAccessIterator, Distance, T, Compare>(first, topPosition, position, value, compare);
}
}  // namespace eastl

// @ 0x00511b80
namespace eastl {
template <typename RandomAccessIterator, typename Compare> void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    for (; (last - first) > 1; --last) {
        const Obj* tempBottom(*(last - 1));
        *(last - 1) = *first;
        eastl::adjust_heap<RandomAccessIterator, int, const Obj*, Compare>(first, 0, (int)(last - first - 1), 0, tempBottom, compare);
    }
}
}  // namespace eastl

// @ 0x00511dd0
namespace eastl {
template <typename RandomAccessIterator> void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            eastl::adjust_heap<RandomAccessIterator, int, uint32_t>(first, parentPosition, heapSize, parentPosition, *(first + parentPosition));
        } while (parentPosition != 0);
    }
}
}  // namespace eastl

// @ 0x00511e30
namespace eastl {
template <typename RandomAccessIterator, typename Distance, typename T> void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value)
{
    Distance childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (*(first + childPosition) < *(first + (childPosition - 1)))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    eastl::promote_heap<RandomAccessIterator, Distance, T>(first, topPosition, position, value);
}
}  // namespace eastl

// @ 0x00511f10
namespace eastl {
template <typename RandomAccessIterator> void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    for (; (last - first) > 1; --last) {
        const uint32_t tempBottom(*(last - 1));
        *(last - 1) = *first;
        eastl::adjust_heap<RandomAccessIterator, int, uint32_t>(first, 0, (int)(last - first - 1), 0, tempBottom);
    }
}
}  // namespace eastl

// @ 0x005120d0
namespace eastl {
template <typename RandomAccessIterator, typename Distance, typename T, typename Compare> void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, T value, Compare compare)
{
    for (Distance parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}
}  // namespace eastl

// @ 0x005121c0
Vector3_s0051_1670 TriMesh::GetTriangleNormal(int i)
{
    Vector3_s0051_1670* verts = mpVertices;
    int* tris = mpTriangles;
    Vector3_s0051_1670 edge2 = verts[tris[i * 3 + 2]] - verts[tris[i * 3]];
    Vector3_s0051_1670 edge1 = verts[tris[i * 3 + 1]] - verts[tris[i * 3]];
    return Normalize(Cross(edge1, edge2));
}

// @ 0x005122c0
Owner::Owner()
: mA(), mB(), mC(Less()) {}

// @ 0x00512330
Owner::~Owner()
{
    Clear();
}

// @ 0x005123b0
void Owner::Clear()
{
    ScratchSlots_s0051_1670<8>();
    mA.clear();
    mB.clear();
    mC.clear();
}

// @ 0x00512400
void RenderJobSink::InitRenderJob(RenderCfg* cfg, uint32_t* pBones, uint32_t id, float* pos, float* color, uint32_t a6, uint32_t a7)
{
    if (cfg->f10 > 0.0f && cfg->f40 > 0.0f) {
        alloc.Begin();
        uint32_t* job = (uint32_t*)alloc.Get();
        job[0] = id;
        job[1] = *(uint32_t*)&color[0];
        job[2] = *(uint32_t*)&color[1];
        job[3] = *(uint32_t*)&color[2];

        float local[6];
        cfg->BuildMatrix(color, a6, a7, 2, &local[0], &local[3], 0);

        job[4] = *(uint32_t*)&local[0];
        job[5] = *(uint32_t*)&local[1];
        job[6] = *(uint32_t*)&local[2];
        job[7] = *(uint32_t*)&local[3];
        job[8] = *(uint32_t*)&local[4];
        job[9] = *(uint32_t*)&local[5];

        const float v10 = -((local[0] * pos[0] + local[1] * pos[1]) + local[2] * pos[2]) + 0.5f - cfg->f14;
        const float v11 = -((local[3] * pos[0] + local[4] * pos[1]) + local[5] * pos[2]) + 0.5f - cfg->f18;
        job[10] = *(uint32_t*)&v10;
        job[11] = *(uint32_t*)&v11;

        for (int i = 0; i < 3; ++i)
            job[12 + i] = pBones[i];

        const uint32_t c0 =
            (uint32_t)RoundInt(Saturate(cfg->f5c * cfg->f6c)) << 24 |
            ((uint32_t)RoundInt(Saturate(cfg->f60)) & 0xff) << 16 |
            ((uint32_t)RoundInt(Saturate(cfg->f64)) & 0xff) << 8 |
            ((uint32_t)RoundInt(Saturate(cfg->f68)) & 0xff);
        job[15] = c0;

        const uint32_t c1 =
            (uint32_t)RoundInt(Saturate(cfg->f84 * cfg->f5c)) << 24 |
            ((uint32_t)RoundInt(Saturate(cfg->f74)) & 0xff) << 16 |
            ((uint32_t)RoundInt(Saturate(cfg->f7c * cfg->f5c)) & 0xff) << 8 |
            ((uint32_t)RoundInt(Saturate(cfg->f80)) & 0xff);
        job[16] = c1;

        ((uint8_t*)job)[0x44] = cfg->b9c;
        ((uint8_t*)job)[0x45] = cfg->ba0;
        ((uint8_t*)job)[0x46] = cfg->ba4;
        ((uint8_t*)job)[0x47] = cfg->b88;
    }
}

// @ 0x00512840
void cDecalBuilder::Project(const Mesh& mesh, const DecalParams& params)
{
    bool first;
    DecalVertex* verts;
    int i;
    DecalBatch* batch;
    uint32_t numTris;
    int e;
    uint32_t next, prev;
    FillEntry entry;
    int base, i1, i2;
    DecalVertex* dst;
    Vector3_s0051_2840 pos;
    Vector2 uv0, uv1, uv2;
    float fade0, fade1, fade2;
    float d0, d1, d2;
    uint32_t remaining;
    uint32_t maxVerts;

    mBatches.push_back();
    batch = &mBatches.back();
    batch->mStart = (int)(mVertices.mpEnd - mVertices.mpBegin);
    batch->mCount = 0;
    batch->mFlags[0] = params.mFlags[0];
    batch->mFlags[1] = params.mFlags[1];
    batch->mFlags[2] = params.mFlags[2];
    batch->mFlags[3] = params.mFlags[3];
    for (i = 0; i < 3; i++)
        batch->mData[i] = params.mBatchData[i];

    MeshAccessor acc(mesh);
    numTris = (uint32_t)mesh.mPositionIndices.size() / 3;
    sVisitedTriangles.erase(sVisitedTriangles.mpBegin, sVisitedTriangles.mpEnd);
    sVisitedTriangles.resize(numTris, 0);
    sFillStack.erase(sFillStack.mpBegin, sFillStack.mpEnd);
    sFillStack.push_back(FillEntry(params.mStartTriangle * 3, -1, -1));
    sVisitedTriangles[params.mStartTriangle] = 1;

    first = true;
    verts = mVertices.mpBegin;
    while (!sFillStack.empty()) {
        entry = sFillStack.back();
        sFillStack.pop_back();
        e = entry.edge;
        GetTriangleEdges(e, next, prev);

        if (entry.a != -1) {
            d0 = Dot(params.mDir, acc.Normal(e));
            fade0 = (gDecalAngleBias - FastAcos(d0)) * gDecalAngleScale;
            pos = acc.Position(e);
            uv0 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
            uv1 = verts[entry.a].mDecalUV;
            fade1 = verts[entry.a].mFade;
            uv2 = verts[entry.b].mDecalUV;
            fade2 = verts[entry.b].mFade;
        } else {
            d0 = Dot(params.mDir, acc.Normal(e));
            d1 = Dot(params.mDir, acc.Normal(next));
            d2 = Dot(params.mDir, acc.Normal(prev));
            fade0 = (gDecalAngleBias - FastAcos(d0)) * gDecalAngleScale;
            fade1 = (gDecalAngleBias - FastAcos(d1)) * gDecalAngleScale;
            fade2 = (gDecalAngleBias - FastAcos(d2)) * gDecalAngleScale;
            pos = acc.Position(e);
            uv0 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
            pos = acc.Position(next);
            uv1 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
            pos = acc.Position(prev);
            uv2 = params.mOffset + RwVector2(params.mUAxis.Dot(pos), params.mVAxis.Dot(pos));
        }

        // reject triangles entirely outside the unit uv square
        if ((uv0[0] <= 0.0f && uv1[0] <= 0.0f && uv2[0] <= 0.0f) ||
            (uv0[0] >= 1.0f && uv1[0] >= 1.0f && uv2[0] >= 1.0f) ||
            (uv0[1] <= 0.0f && uv1[1] <= 0.0f && uv2[1] <= 0.0f) ||
            (uv0[1] >= 1.0f && uv1[1] >= 1.0f && uv2[1] >= 1.0f))
            continue;
        // (the original tests the (uv0, uv1) edge twice)
        if (!IsEdgeInside(uv0, uv1) || !IsEdgeInside(uv0, uv1) || !IsEdgeInside(uv2, uv0))
            continue;
        {
            base = (int)(mVertices.mpEnd - mVertices.mpBegin);
            mVertices.resize(base + 3);
            verts = mVertices.mpBegin;
            dst = &verts[base];
            dst[0].mUV = acc.UV(e);
            dst[0].mData[0] = params.mVertexData[0];
            dst[0].mData[1] = params.mVertexData[1];
            dst[0].mDecalUV = uv0;
            dst[0].mFade = fade0;
            if (entry.a != -1) {
                i1 = entry.a;
                i2 = entry.b;
                CopyVertex(dst[1], verts[entry.a]);
                CopyVertex(dst[2], verts[entry.b]);
            } else {
                i1 = base + 1;
                i2 = base + 2;
                dst[1].mUV = acc.UV(next);
                dst[1].mData[0] = params.mVertexData[0];
                dst[1].mData[1] = params.mVertexData[1];
                dst[1].mDecalUV = uv1;
                dst[1].mFade = fade1;
                dst[2].mUV = acc.UV(prev);
                dst[2].mData[0] = params.mVertexData[0];
                dst[2].mData[1] = params.mVertexData[1];
                dst[2].mDecalUV = uv2;
                dst[2].mFade = fade2;
            }

            // spread across edges where the decal still faces the surface
            if (fade0 > 0.0f || fade1 > 0.0f) {
                HalfEdge h = acc.Opposite(e);
                uint32_t tri = h.edge / 3;
                if (!sVisitedTriangles[tri]) {
                    sVisitedTriangles[tri] = 1;
                    sFillStack.push_back();
                    if (h.seamless)
                        sFillStack.back() = FillEntry(h.edge, i1, base);
                    else
                        sFillStack.back() = FillEntry(h.edge, -1, -1);
                }
            }
            if (fade2 > 0.0f || fade0 > 0.0f) {
                HalfEdge h = acc.Opposite(prev);
                uint32_t tri = h.edge / 3;
                if (!sVisitedTriangles[tri]) {
                    sVisitedTriangles[tri] = 1;
                    sFillStack.push_back();
                    if (h.seamless)
                        sFillStack.back() = FillEntry(h.edge, base, i2);
                    else
                        sFillStack.back() = FillEntry(h.edge, -1, -1);
                }
            }
            if (first && (fade1 > 0.0f || fade2 > 0.0f)) {
                HalfEdge h = acc.Opposite(next);
                uint32_t tri = h.edge / 3;
                if (!sVisitedTriangles[tri]) {
                    sVisitedTriangles[tri] = 1;
                    sFillStack.push_back();
                    if (h.seamless)
                        sFillStack.back() = FillEntry(h.edge, i2, i1);
                    else
                        sFillStack.back() = FillEntry(h.edge, -1, -1);
                }
            }
            first = false;
        }
    }

    // split the new vertices into batches of at most 36000
    remaining = mVertices.size() - mBatches.back().mStart;
    maxVerts = 36000;
    while (remaining > 36000) {
        mBatches.back().mCount = 36000;
        mBatches.push_back(mBatches.back());
        mBatches.back().mStart += 36000;
        remaining -= 36000;
    }
    if (remaining == 0)
        mBatches.pop_back();
    else
        mBatches.back().mCount = remaining;
}

// @ 0x00686320
cPropertyList::~cPropertyList()
{
    if (mModCount != 0)
        ((void (__thiscall*)(void*))VT(mModCount)[1])(mModCount);
    mPropertyMap.FreeNodes();
    vtbl = (void*)0x013eb938;   // Editor::cEditorResource vtable
}

// @ 0x01326120
namespace Simulator {
void InitStarManagerAttributes()
{
    ADD(0,  "mStarRecordGrid", 0x03fabad0, 0xc8, GRID_ATTR)
    ADD(1,  "mStarterStarRecords", 0x03ea8676, 0xdc, STARVEC_ATTR)
    ADD(2,  "mSavedGameStarRecords", 0x03ea8679, 0xf0, STARVEC_ATTR)
    ADD(3,  "mBlackHoles", 0x055ceb62, 0x104, STARVEC_ATTR)
    ADD(4,  "mEmpireHomeStarRecords", 0x04274872, 0x12c, HOMEVEC_ATTR)
    ADD(5,  "mPossibleStartLocations", 0x0563c450, 0x118, STARVEC_ATTR)
    ADD(6,  "mSol", 0x03f5bbc2, 0x148, Read_00ba7420, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(7,  "mpGlobalCLGItems", 0x044ee63e, 0x220, Read_00ba8250, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(8,  "mNextPoliticalID", 0x044ee640, 0x1d4, Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(9,  "mGrobID", 0x044ee641, 0x1d8, Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(10, "mEmpires", 0x052c47aa, 0x150, Read_00bab200, Write_00ba94e0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba7450, ToXml_00baa2b0)
    ADD(11, "mTradeRouteManager", 0x05528d40, 0x1e0, Read_00ba66d0, Write_00ba66f0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba6690, ToXml_00ac8050)
    ADD(12, "sGameTimeManagerContainer", 0x0579f61c, &cStarManager_sGameTimeManagerContainer, Read_00b5cb60, Write_00b5cb80, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>)
    ADD(13, "sRelationshipManagerContainer", 0x056e616c, &cStarManager_sRelationshipManagerContainer, Read_00ba6710, Write_00ba6730, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>)
    ADD(14, "sNameCountMap", 0x05d55277, &cStarManager_sNameCountMap, Read_00bb1660, Write_00ba8280, ReadTextMap<int>, WriteText_00694bd0, AlwaysValid<void*>)
    ADD(15, "mTransactionLog", 0x05d55278, 0x208, Read_00bb1830, Write_00ba7490, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00bab380)
    ADD(16, "mAvailableStarterWorlds", 0x0563c451, 0xa0, Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00eafe40)
    ADD(17, "mEmpireNamesInUse", 0x06b94eb9, 0x16c, Read_00bb19d0, Write_00ba7510, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00bab4d0)
    ADD(18, "mAdventureIDs", 0x0799479d, 0x184, Read_00bab620, Write_00ba7590, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00d011e0, ToXml_00bab740)
}
}  // namespace Simulator

// @ 0x013277d0
void __cdecl FUN_013277d0(void)
{
    SimAttr attr;
    ROW(0x156cb70, 0x1465750, 0x3d58bf2, 0x70, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cbac, 0x145bc18, 0x3d58bf1, 0x3c, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xacbba0)
    ROW(0x156cbe8, 0x14665d4, 0x3e95e04, 0x48, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0x57cde0)
    ROW(0x156cc24, 0x14665c8, 0x3d58bf6, 0x4c, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0x57cde0)
    ROW(0x156cc60, 0x1411e88, 0x3d58bf4, 0x60, 0xac87c0, 0xac87f0, 0x694c80, 0x694c10, 0xacbbc0)
    ROW(0x156cc9c, 0x145ca9c, 0x3d58bf3, 0x5c, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ccd8, 0x14665b4, 0x3d58bf5, 0x74, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xae5720)
    ROW(0x156cd14, 0x14665a4, 0x3d58bf7, 0x58, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cd50, 0x1466598, 0x3f1389b, 0x54, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cd8c, 0x1466584, 0x3f1389a, 0x0c, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156cdc8, 0x1466570, 0x3f1389c, 0x18, 0xb26970, 0xb26990, 0xc2e4e0, 0x692fb0, 0xac8050)
    ROW(0x156ce04, 0x1466558, 0x3f1389d, 0x10, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ce40, 0x1466540, 0x3f1389e, 0x14, 0x572810, 0x572840, 0x693090, 0x694f00, 0x675ca0)
    ROW(0x156ce7c, 0x1466534, 0x51a1188, 0xac, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0x595a50)
}

// @ 0x01328ee0
void __cdecl FUN_01328ee0(void)
{
    SimAttr attr;
    ROWF(0x156cfe0, 0x14667b8, 0x4e3b373, 0x00, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d01c, 0x14667a8, 0x4e3b37d, 0x04, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0)
    ROWF(0x156d058, 0x145ca9c, 0x4e3b37e, 0x28, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0xb1fbf0, 0x595a50)
    ROWF(0x156d094, 0x1466798, 0x4e3b37f, 0x12, 0xbb9cd0, 0xbb9d00, 0x693070, 0x694f80, 0xb1fbf0, 0x595a50)
    ROWF(0x156d0d0, 0x1466790, 0x4e3b380, 0x10, 0xbc3270, 0xff05d0, 0x693030, 0x694f40, 0xb1fbf0, 0xbc3470)
    ROWF(0x156d10c, 0x1466788, 0x5c41511, 0x14, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80)
    ROWF(0x156d148, 0x1466778, 0x5d0f859, 0x18, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0)
    ROWF(0x156d184, 0x1465750, 0x5de82a2, 0x1c, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720)
}
