// Slice s007df780 (w2g5 slice 25).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// Swarm split-model-kernel description, kernel-storage setters and the
// ArgScript SplitModelKernelEffect command.
#include "types.h"

struct cSPVector3 { float x, y, z; };

// Error object thrown by the kernel-storage validators.
struct cError { cError(const char*); };

// ===========================================================================
// SP::cSplitModelKernelDescription::cSafeDynamicKernelStorage
// ===========================================================================
struct cSafeDynamicKernelStorage {
    int mKernelType;            // +0x0
    void* mKernelData;          // +0x4
    void* mKernelDataVariation; // +0x8

    void SetKernelType(int type);                              // 007e0340
    void SetNormal(const cSPVector3& a, const cSPVector3& b);  // 007e0420
    void SetOrigin(const cSPVector3& a, const cSPVector3& b);  // 007e0480
    void SetRadius(float a, float b);                          // 007e04f0
    void SetDirection(const cSPVector3& a, const cSPVector3& b);// 007e0570
    cSafeDynamicKernelStorage& operator=(const cSafeDynamicKernelStorage& o);  // 007e05e0
};

void EFree2(void*);   // 0x00f47380

void cSafeDynamicKernelStorage::SetNormal(const cSPVector3& a, const cSPVector3& b)
{
    if (mKernelType != 0)
        throw cError("Either type not specified or type does not support this parameter");
    *(cSPVector3*)mKernelData = a;
    *(cSPVector3*)mKernelDataVariation = b;
}

void cSafeDynamicKernelStorage::SetOrigin(const cSPVector3& a, const cSPVector3& b)
{
    if (mKernelType == 1 || mKernelType == 2) {
        *(cSPVector3*)mKernelData = a;
        *(cSPVector3*)mKernelDataVariation = b;
        return;
    }
    throw cError("Either type not specified or type does not support this parameter");
}

void cSafeDynamicKernelStorage::SetRadius(float a, float b)
{
    if (mKernelType == 1) {
        *(float*)((char*)mKernelData + 0xc) = a;
        *(float*)((char*)mKernelDataVariation + 0xc) = b;
        return;
    }
    if (mKernelType == 2) {
        *(float*)((char*)mKernelData + 0x18) = a;
        *(float*)((char*)mKernelDataVariation + 0x18) = b;
        return;
    }
    throw cError("Either type not specified or type does not support this parameter");
}

void cSafeDynamicKernelStorage::SetDirection(const cSPVector3& a, const cSPVector3& b)
{
    if (mKernelType != 2)
        throw cError("Either type not specified or type does not support this parameter");
    *(cSPVector3*)((char*)mKernelData + 0xc) = a;
    *(cSPVector3*)((char*)mKernelDataVariation + 0xc) = b;
}

// ===========================================================================
// 0x007dfbf0  allocate a MapDescription, initialise its vtable.
// ===========================================================================
void* __cdecl EAllocSwarm(int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

void* FUN_007dfbf0()
{
    int* p = (int*)EAllocSwarm(8, "Swarm", 0, 0, 0, 0);
    if (p) {
        p[1] = 0;
        p[0] = 0x1453948;
        return p;
    }
    return 0;
}

// ===========================================================================
// Remaining functions in this slice (best-effort skeletons).
// ===========================================================================
void FUN_007df780() { /* 817B */ }                 // 007df780
void FUN_007dfac0() { /* 262B */ }                 // 007dfac0
void FUN_007dfbd0() { /* 18B */ }                  // 007dfbd0
void FUN_007dfc20() { /* 364B */ }                 // 007dfc20
void FUN_007dfd90() { /* 228B */ }                 // 007dfd90
void FUN_007dfe80() { /* 68B  ctor */ }            // 007dfe80
void FUN_007dfed0() { /* 564B */ }                 // 007dfed0
void FUN_007e0110() { /* 80B  ctor */ }            // 007e0110
void FUN_007e0160() { /* 49B */ }                  // 007e0160
void FUN_007e01a0() { /* 90B */ }                  // 007e01a0
void FUN_007e0200() { /* 126B */ }                 // 007e0200
void FUN_007e0280() { /* 112B */ }                 // 007e0280
void FUN_007e02f0() { /* 65B  deleting dtor */ }   // 007e02f0

void cSafeDynamicKernelStorage::SetKernelType(int) { /* 224B */ }  // 007e0340
cSafeDynamicKernelStorage& cSafeDynamicKernelStorage::operator=(
    const cSafeDynamicKernelStorage&) { /* 193B */ return *this; }  // 007e05e0
