// Slice s00485b90: cSPEditorHandleRotationRing physics/bbox helpers, /Od /Ob1 /arch:SSE.
// 0x004860b0 (UpdateBig) is complete; 0x00485b90 / 0x00485eb0 are still PARTIAL stubs
// (dominated by inlined bounding-box transforms and vector math).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// rw::math::fpu::Vector3Template<float,0>: copy ctor and operator= are out of line (both 0x004098A0,
// folded by the linker).
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                                    // 0x004098A0
    Vector3T& operator=(const Vector3T& v);                         // 0x004098A0
    float& operator[](int i) { return (&x)[i]; }
};

struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : Vector3T(v) {}
    cSPVector3(const Vector3T& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    cSPVector3& operator=(const Vector3T& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
};

// rw::math::fpu::Matrix33Template<float,0>: copy constructor out of line.
struct Matrix33T {
    Vector3T xAxis;
    Vector3T yAxis;
    Vector3T zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m);                                  // 0x0041CB40
};

struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& m);                                // 0x00449CC0
};

Vector3T operator-(const Vector3T& a, const Vector3T& b);           // 0x0041DB10
Vector3T operator+(const Vector3T& a, const Vector3T& b);           // 0x0041DC10
Vector3T operator*(const Vector3T& v, const float& s);              // 0x0041DCA0
Vector3T operator*(const float& s, const Vector3T& v);              // 0x0041DE40
Vector3T operator/(const Vector3T& v, const float& s);              // 0x00453880
float VectorLength(const Vector3T& v);                              // 0x0040AE50
Vector3T normalized_safe(const Vector3T& v);                        // 0x00449C20
extern const float kZero;                                           // 0x01485378

template<class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
template<class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

struct cSPEditorBlock {
    char pad0[0x48];
    Vector3T mPosition;                                             // +0x48
    char pad1[0xa8 - 0x54];
    cSPMatrix3 mOrientation;                                        // +0xa8
    char pad2[0x340 - 0xcc];
    vector<AutoRefCount<cSPEditorBlock> > mSymmetricBlocks;         // +0x340
    char pad3[0x3ec - 0x354];
    void* mSkin;                                                    // +0x3ec
    char pad4[0xdc8 - 0x3f0];
    bitset<60> mFlags;                                              // +0xdc8
    float GetRadius();                                              // 0x0043EED0
};

namespace SP { namespace EditorUtils {
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 pos, cSPMatrix3 orient, int flags);   // 0x0049FBD0
} }

struct HandleRef { cSPEditorBlock* mBlock; };

struct RotationRing {
    cSPEditorBlock* mBlock;                 // +0x00
    int   pad4;
    vector<HandleRef*> mHandles;            // +0x08

    float Compute1();          // 0x485b90
    float Compute2();          // 0x485eb0
    void  UpdateBig(float rA, float rB);    // 0x4860b0
};

// @ 0x00485b90 -- PARTIAL: bbox/direction distance blend; body omitted.
float RotationRing::Compute1()
{
    return 0.0f;
}

// @ 0x00485eb0 -- PARTIAL: bounding-box transform returning a min component; body omitted.
float RotationRing::Compute2()
{
    return 0.0f;
}

static inline float Dot(const Vector3T& a, const Vector3T& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline float Lerp(float a, float b, float t)
{
    float d = b - a;
    d *= t;
    return a + d;
}

// @ 0x004860b0
void RotationRing::UpdateBig(float rA, float rB)
{
    cSPEditorBlock* blockA = mBlock;
    cSPEditorBlock* blockB = mHandles[0]->mBlock;
    cSPVector3 a(blockA->mPosition);
    cSPVector3 b(blockB->mPosition);
    float radA = blockA->GetRadius();
    float radB = blockB->GetRadius();
    cSPVector3 ab(b - a);
    float dist = VectorLength(ab) + 1e-12f;
    cSPVector3 u(ab / dist);

    vector<AutoRefCount<cSPEditorBlock> >* list = &blockA->mSymmetricBlocks;
    int n = list->size();
    for (int i = 0; i < n; i++) {
        cSPEditorBlock* m = (*list)[i];
        if (m->mSkin != 0)
            continue;
        cSPVector3 p(m->mPosition);
        cSPVector3 result((const Vector3T&)p);
        cSPVector3 pa(p - a);
        float lenA = VectorLength(pa);
        cSPVector3 pb(p - b);
        float lenB = VectorLength(pb);
        cSPVector3 q(p - a);
        float t = Dot(u, q);
        cSPVector3 w(t * u);
        float s = Dot(u, normalized_safe(w));
        if (s < 0.0f) {
            cSPVector3 d(p - a);
            float r = rA / radA;
            cSPVector3 scaled(d * r);
            result = a + scaled;
        } else if (t > dist) {
            cSPVector3 d(p - b);
            float r = rB / radB;
            Vector3T tmp;
            tmp = d * r;
            (Vector3T&)result = b + tmp;
        } else {
            Vector3T e;
            e = p - (w + a);
            float f = t / dist;
            float rr = Lerp(radA, radB, f);
            float pp = Lerp(rA, rB, f);
            float k = pp / rr;
            Vector3T scaled;
            scaled = e * k;
            (Vector3T&)result = (w + a) + scaled;
        }
        if (m->mFlags.test(15))
            result[0] = kZero;
        SP::EditorUtils::RepinBlockToTorso(m, result, m->mOrientation, 0);
    }
}
