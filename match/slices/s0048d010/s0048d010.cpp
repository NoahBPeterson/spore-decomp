// Slice s0048d010: SP::cSPEditorManipulationStacking helper + small Havok ctor/dtor/copy helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

// hkMemory singleton (vtable slot 5 = Free)
struct hkMemory {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void* Free(void* p, int align, int size);
};
extern hkMemory* g_hkMemory;                    // @ 0x16e4178

// ---- small Havok object ctor/dtor/copy helpers ----
struct HkObj {
    char data0[4];
    float mField4;                              // +0x04
    char data1[0x20 - 8];
    float mArray[4];                            // +0x20
    int mField30;                               // +0x30
    char rest[0x40 - 0x34];
    void* F_48db10(unsigned flags);             // @ 0x48db10
    void  F_48db60();                           // @ 0x48db60
    void* F_48dbb0(unsigned flags);             // @ 0x48dbb0
    void* F_48dc50(HkObj* src);                 // @ 0x48dc50
    void* F_48dc00(HkObj* src);                 // @ 0x48dc00
};

// @ 0x48db10
void* HkObj::F_48db10(unsigned flags)
{
    *(void**)this = (void*)0x13ef534;
    if (flags & 1) {
        hkMemory* node = g_hkMemory;
        node->Free(this, 8, 0x1c);
    }
    return this;
}

// @ 0x48db60
void HkObj::F_48db60()
{
    mField30 = 0;
    float k = *(float*)0x13ef4f8;
    mArray[3] = k;
    mField4 = *(float*)0x13ef4f8;
}

// @ 0x48dbb0
void* HkObj::F_48dbb0(unsigned flags)
{
    *(void**)this = (void*)0x13ef52c;
    *(void**)this = (void*)0x13ef534;
    if (flags & 1) {
        hkMemory* node = g_hkMemory;
        node->Free(this, 8, 0x1c);
    }
    return this;
}

// @ 0x48dc50
void* HkObj::F_48dc50(HkObj* src)
{
    *(float*)((char*)this + 0x0) = *(float*)((char*)src + 0x0);
    *(float*)((char*)this + 0x4) = *(float*)((char*)src + 0x4);
    *(float*)((char*)this + 0x8) = *(float*)((char*)src + 0x8);
    *(float*)((char*)this + 0xc) = *(float*)((char*)src + 0xc);
    float* d = (float*)((char*)src + 0x10);
    float* s = (float*)((char*)this + 0x10);
    s[0] = d[0]; s[1] = d[1]; s[2] = d[2]; s[3] = d[3];
    return this;
}

// @ 0x48dc00
void* HkObj::F_48dc00(HkObj* src)
{
    F_48dc50(src);
    *(int*)((char*)this + 0x20) = *(int*)((char*)src + 0x20);
    *(int*)((char*)this + 0x24) = *(int*)((char*)src + 0x24);
    *(int*)((char*)this + 0x28) = *(int*)((char*)src + 0x28);
    *(int*)((char*)this + 0x2c) = *(int*)((char*)src + 0x2c);
    return this;
}

// @ 0x48d010
// Best-effort skeleton of the manipulation-stacking evaluation; the full per-branch
// math of the 2783-byte original is not reproduced.
int F_48d010(int param_1, int param_2, float p3, float p4, float p5, float* out)
{
    (void)param_2; (void)p3; (void)p4; (void)p5; (void)out;
    int result = 0;
    int stacking = *(int*)(param_1 + 0x18c);
    if (stacking != 0) {
        // original: resolves the target block, builds a stacking move, compares the
        // candidate position against the current block radius and writes the chosen
        // position through `out`.
        result = 0;
    }
    return result;
}
