// Slice s004f85b0 -- SP::ForceGrid, a 512-bucket force grid.  Every bucket holds an array of
// 0x80-byte SphereFields blocks; one block carries four spheres, one per SIMD lane.
// Skinner module: /Od /Ob1 /MD /Gy /TP /arch:SSE2 /fp:fast (no /EHsc).
#ifndef S004F85B0_H
#define S004F85B0_H

typedef unsigned int uint32_t;

// ------------------------------------------------------------------ image globals
extern int g_vtbl_13f1140;              // 0x013f1140  ForceGrid vtable
extern int g_vtbl_13ef094;              // 0x013ef094  hkReferencedObject vtable
extern unsigned char g_bForceGridInit;  // 0x015db590  set once, on the first construction

// ------------------------------------------------------------------ free helpers
void*  FUN_00f473a0(uint32_t size, const char* name, int, int, int, int);  // 0x00f473a0 operator new
void   FUN_00f47380(void* p);            // 0x00f47380  FreeRawBlock
void   FUN_004f80b0(void* p);            // 0x004f80b0  free an aligned block (raw pointer at [-0xc])
void   FUN_004c0b80(void* p);            // 0x004c0b80  SimpleVector<uint> destroy
int    FUN_004f8120();                   // 0x004f8120  GetSimdLevel (cdecl)
void*  FUN_004f8750(int size, int param2);  // 0x004f8750 aligned allocate
extern "C" void* __cdecl memset(void* p, int c, unsigned int n);  // 0x011e073e

// ------------------------------------------------------------------ vector math (defined elsewhere)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    float&       operator[](int i)       { return ((float*)this)[i]; }
    const float& operator[](int i) const { return ((const float*)this)[i]; }
};
Vector3* FUN_0041db10(Vector3* out, const Vector3* a, const Vector3* b);  // 0x0041db10  a - b
Vector3* FUN_0041dc10(Vector3* out, const Vector3* a, const Vector3* b);  // 0x0041dc10  a + b
Vector3* FUN_0041c0c0(Vector3* out, const Vector3* a, const Vector3* b);  // 0x0041c0c0  component min
Vector3* FUN_0041bfb0(Vector3* out, const Vector3* a, const Vector3* b);  // 0x0041bfb0  component max
Vector3* FUN_004fc510(Vector3* out, const Vector3* a, const Vector3* b);  // 0x004fc510  component product

// ------------------------------------------------------------------ chunk pool
struct SPMemPool {
    void  FUN_009276c0(void* p);          // 0x009276c0  free (ret 4)
    void* FUN_00928a30(uint32_t size, uint32_t align,
                       int a, int b, int c, int d, int e, int f);  // 0x00928a30 (ret 0x20)
};
extern SPMemPool* g_pSPMemPool;           // 0x016c8b44

// ------------------------------------------------------------------ vector of chunk pointers
struct SimpleVector {
    void** mpBegin;                        // +0x00
    void** mpEnd;                          // +0x04
    void** mpCapacity;                     // +0x08
    void   FUN_004fc4a0();                 // 0x004fc4a0  ctor
    void   FUN_004fc610(void** value);     // 0x004fc610  push_back(&value) (ret 4)
    void** erase(void** first, void** last);  // 0x004769b0 (ret 8)
};

// ------------------------------------------------------------------ 4-sphere block
struct SphereFields {                      // 0x80 bytes: four spheres, one per SIMD lane
    float    mX[4];                        // +0x00
    float    mY[4];                        // +0x10
    float    mZ[4];                        // +0x20
    float    mRadiusSq[4];                 // +0x30
    float    mInvRadiusSq[4];              // +0x40
    float    mStrength[4];                 // +0x50
    float    mScaledStrength[4];           // +0x60
    uint32_t mId[4];                       // +0x70

    void  Clear(int index);                                            // 0x004f81a0
    void  Set(int index, const Vector3* point, float strength,
              float radius, int id);                                   // 0x004f8270
    void  SetRadius(int index, float radius);                          // 0x004f8300
    float Distance(const float* point);                                // 0x004f8e20 (ret 4)
    void  Accumulate(const float* point, float* cost, float* acc);     // 0x004f9360 (ret 0xc)
};

struct ForceGrid {
    void*    mpVtbl;                       // +0x00  hkReferencedObject / ForceGrid vtable
    int      mnRefCount;                   // +0x04  hkReferencedObject
    typedef void (ForceGrid::*EvalFn)(const float*, float*);
    EvalFn   mpEval;                       // +0x08  evaluator for this CPU's SIMD level
    float    mfCost;                       // +0x0c
    float    mfNegCost;                    // +0x10
    uint32_t mnPointCount;                 // +0x14  spheres inserted
    uint32_t mnCapacity;                   // +0x18  SphereFields blocks allocated
    SphereFields* mpFields;                // +0x1c  block array (block count at -8)
    Vector3  mMin;                         // +0x20
    Vector3  mMax;                         // +0x2c
    Vector3  mVec38;                       // +0x38
    float    mfRadScale;                   // +0x44  0.001f
    Vector3* mpGridBlock;                  // +0x48  two quad-aligned Vector3 (scale, origin)
    Vector3* mpGridScale;                  // +0x4c  == mpGridBlock
    Vector3* mpGridOrigin;                 // +0x50  == mpGridBlock + 1
    SphereFields** mppBuckets;             // +0x54  512 bucket heads (0x800 bytes)
    SimpleVector mChunks;                  // +0x58  pool chunks backing the block allocations
    char     mPad64[0xf0 - 0x64];
    char*    mpBump;                       // +0xf0  bump pointer inside the current chunk
    uint32_t mnRemaining;                  // +0xf4  bytes left in the current chunk

    ForceGrid* Init(float cost);                            // 0x004f85b0
    void  FUN_004f87f0();                                   // 0x004f87f0  teardown
    void* FUN_004f8880(uint32_t size, int param3);           // 0x004f8880  bump allocate
    void  FUN_004f89a0();                                   // 0x004f89a0  release chunks
    void  Insert(const Vector3* point, float strength, float radius, int id);  // 0x004f8a40 (ret 0x10)
    void  FUN_004f8580(float cost);                         // 0x004f8580  set cost / negated cost
    void  FUN_004f8d80(const float* point, float* out);      // 0x004f8d80  scalar evaluator (ret 8)
    SphereFields* FUN_004f8f70(const float* point);          // 0x004f8f70  bucket lookup (ret 4)
    float* FUN_004f90a0(const float* point, float* out);     // 0x004f90a0  SSE2 evaluator (ret 8), returns out in eax
    void  FUN_004f9180(const float* point, float* out);      // 0x004f9180  SSE1 evaluator (ret 8)
    bool  FUN_004f9250(const float* point, float* out);      // 0x004f9250  accumulated cost (ret 8)
    void  FUN_004fc320(int reset);                          // 0x004fc320  clear spheres / bounds (ret 4)
};

#endif
