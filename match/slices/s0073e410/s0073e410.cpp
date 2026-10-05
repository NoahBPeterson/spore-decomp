// Slice s0073e410 (0x0073e410-0x0073f2e0): SP::cModelInstance mesh/dispatch helpers.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"
#include <intrin.h>

// External callees (masked relocations).
extern "C" void  FUN_01201660();          // 0x1201660
extern "C" void  FUN_012016d0();          // 0x12016d0
extern "C" void  FUN_0073a6e0();          // 0x73a6e0
extern "C" void  FUN_006c1c80();          // 0x6c1c80
extern "C" void  FUN_007c5490();          // 0x7c5490
extern "C" void  FUN_01200940();          // 0x1200940
extern "C" void  FUN_00730210(int, int);  // 0x730210
extern "C" void  FUN_0072fff0(int, int);  // 0x72fff0
extern "C" void  FUN_0073bab0(void*);     // 0x73bab0
extern "C" void  FUN_00777bf0();          // 0x777bf0
extern "C" void  FUN_00777ae0();          // 0x777ae0
extern "C" void  FUN_007789d0();          // 0x7789d0
extern "C" void  FUN_00777c10();          // 0x777c10
extern "C" void  FUN_011f9710();          // 0x11f9710
extern "C" int   FUN_011f2bc0();          // 0x11f2bc0
void __cdecl Matrix3_Assign(void* dst, const void* src);   // 0x41cb40
void __cdecl SetShaderData();                              // 0x777b50
void __cdecl CompiledState_Dispatch();                     // 0x11ee580

// ---------------------------------------------------------------------------
// 16-byte-aligned Vector3 / AABB (used by the bounding-box overlap test).
// ---------------------------------------------------------------------------
struct Vec3A { float x, y, z, w; };
struct AABB  { Vec3A mn, mx; };

struct BBoxTest {
    AABB box;
    bool Test(const AABB* other);   // 0x73f110
};

// ---------------------------------------------------------------------------
// Refcounted object with the vtable at +0 and the refcount at +4.
// ---------------------------------------------------------------------------
struct RC {
    virtual void v0(int mode);
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};

// Array element stride 0xc4, refcounted pointer at +0xc.
struct RCItem {
    char pad0[0xc];
    RC*  mpObject;                   // +0xc
    char pad10[0xb4];
};

// ---------------------------------------------------------------------------
// @ 0x0073f110  AABB overlap test (this <=> other).
// ---------------------------------------------------------------------------
bool BBoxTest::Test(const AABB* other)
{
    if (box.mn.x <= other->mx.x)
        if (other->mn.x <= box.mx.x)
            if (box.mn.y <= other->mx.y)
                if (other->mn.y <= box.mx.y)
                    if (box.mn.z <= other->mx.z)
                        if (other->mn.z <= box.mx.z)
                            return true;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0073f2e0  release a range of refcounted items [first, last)  (__stdcall)
// ---------------------------------------------------------------------------
void __stdcall ReleaseRange(RCItem* first, RCItem* last)
{
    for (; first < last; ++first) {
        RC* p = first->mpObject;
        if (p) {
            int n = (p->mnRefCount += -1);
            if (n == 0) {
                p->mnRefCount = 1;
                _ReadWriteBarrier();
                p->v0(1);
            }
        }
    }
}

// ===========================================================================
// Remaining mesh/dispatch functions (large; reconstruction in progress).
// ===========================================================================

struct cModelInstance_Dispatch {
    char pad[0x154];

    int GetMeshes(void* param_2);                       // 0x73eb90
    int Dispatch(int a2, float* a3, void* a4, float* a5,
                 float* a6, float* a7, void* a8, void* a9);  // 0x73e410
    void DispatchMesh(int a2, void* a3, int a4, int a5);    // 0x73ede0
};

// @ 0x0073eb90
int cModelInstance_Dispatch::GetMeshes(void* param_2)
{
    (void)param_2;
    return 0;
}

// @ 0x0073e410
int cModelInstance_Dispatch::Dispatch(int a2, float* a3, void* a4, float* a5,
                                      float* a6, float* a7, void* a8, void* a9)
{
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6; (void)a7; (void)a8; (void)a9;
    return 0;
}

// @ 0x0073ede0
void cModelInstance_Dispatch::DispatchMesh(int a2, void* a3, int a4, int a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
}

// ---------------------------------------------------------------------------
// @ 0x0073eca0  build a Matrix44 variant + mark global render state dirty
// ---------------------------------------------------------------------------
void __stdcall Eca0_SetTransform(uint8_t* p, float* outMatrix)
{
    float s = *(float*)(p + 0x10);
    outMatrix[0] = *(float*)(p + 0x14) * s;
    outMatrix[1] = *(float*)(p + 0x18) * s;
    outMatrix[2] = *(float*)(p + 0x1c) * s;
    outMatrix[4] = *(float*)(p + 0x20) * s;
    outMatrix[5] = *(float*)(p + 0x24) * s;
    outMatrix[6] = *(float*)(p + 0x28) * s;
    outMatrix[8] = *(float*)(p + 0x2c) * s;
    outMatrix[9] = *(float*)(p + 0x30) * s;
    outMatrix[10] = *(float*)(p + 0x34) * s;
    outMatrix[0xc] = *(float*)(p + 4);
    outMatrix[0xd] = *(float*)(p + 8);
    outMatrix[0xe] = *(float*)(p + 0xc);
    (void)FUN_0073bab0(outMatrix);
}

// ---------------------------------------------------------------------------
// @ 0x0073f000  PartTransform constructor (partial)
// ---------------------------------------------------------------------------
struct PartTransformStub {
    char pad[0xc4];
    void* init(int a2, int a3, void* a4, void* a5);
    void* copyFrom(const void* src);
};

void* PartTransformStub::init(int a2, int a3, void* a4, void* a5)
{
    (void)a2; (void)a3; (void)a4; (void)a5;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x0073f1c0  PartTransform copy constructor (partial)
// ---------------------------------------------------------------------------
void* PartTransformStub::copyFrom(const void* src)
{
    (void)src;
    return this;
}
