// Slice s00c68280: Simulator object helpers (ornament / nano-drone / ground-locomotion).
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast (SSE ucomiss code shape).
#include "types.h"
#include <stdlib.h>

struct Vec { int* begin; int* end; int* cap; };

// Embedded cSpatialObject vtable helpers (subobject at +0x34).
struct cSpatial {
    void** vt;
    float* GetPosition() {
        typedef float* (__thiscall* Fn)(cSpatial*);
        return ((Fn)vt[0x2c / 4])(this);
    }
    void SetPosition(float* p) {
        ((void(__thiscall*)(cSpatial*, float*))vt[0x38 / 4])(this, p);
    }
};

// A movable ornament / locomotive-derived Simulator object. Unknown spans padded.
struct COrn {
    char   pad000[0x2c];
    int*   mp2c;                       // +0x2c (interface, released in Shutdown)
    char   pad030[0x34 - 0x30];
    void** spatialVt;                  // +0x34
    char   pad038[0xd0 - 0x38];
    int*   mpModel;                    // +0xd0
    char   pad0d4[0x118 - 0xd4];
    float  mPosX, mPosY, mPosZ;        // +0x118,+0x11c,+0x120
    char   mFlag124;                   // +0x124
    int    mKey128;                    // +0x128
    float  mF12c;                      // +0x12c
    int*   mVec130;                    // +0x130 (fixed_vector begin)
    int*   mVec134;                    // +0x134 (fixed_vector end)
    char   pad138[0x508 - 0x138];
    char   mBuf508;                    // +0x508
    char   pad509[0x5d0 - 0x509];
    char   mBuf5d0;                    // +0x5d0

    __declspec(noinline) void Update();  // 0xc68280
    void H3f90();                      // 0xc63f90
    void H4460();                      // 0xc64460
    void H64b0(int* out);              // 0xc649b0
    void E6d0();                       // 0xc686d0 (unknown)
    void E850(int* noun);              // 0xc68850
    void E8a0(void* a, void* b);       // 0xc688a0
    void E930();                       // 0xc68930
    void E980(int* view);              // 0xc68980
    void Eaa0();                       // 0xc68aa0
    void Eae0(float* p);               // 0xc68ae0
    void Eb40(int key);                // 0xc68b40
    void Ebd0(float v);                // 0xc68bd0
    int  Ed20(int noun);               // 0xc68d20
    void Ed70(void* a, int* v);        // 0xc68d70
    void Eed0();                       // 0xc68ed0 (destructor-ish)
    int  Ef30(int id);                 // 0xc68f30
    void F030();                       // 0xc69030
    void F090();                       // 0xc69090
    int  F1e0(int id);                 // 0xc691e0
    void F290();                       // 0xc69290
    cSpatial* Spatial() { return (cSpatial*)((char*)this + 0x34); }
};

// cMovableDestructibleOrnament / cNanoDrone constructors (complex, separate stubs).
struct cMovableDestructibleOrnament { void* Ctor(); };   // 0xc68e30
struct cNanoDrone { void* Ctor(); };                       // 0xc69150

// ---- external module helpers ----
void __cdecl ClearVector(Vec* v);                 // 0xc687e0
int* __cdecl CreateNoun(int* v, int* key);        // 0xc68c00
void __cdecl FUN_00ebb720(void* p, unsigned int flags);
void __cdecl FUN_00c63f90(COrn* p);
void __cdecl FUN_00c64460(COrn* p);
void __cdecl FUN_00c649b0(COrn* p, int* v, int* out);
void __cdecl FUN_00c421b0(void* p);
void __cdecl FUN_00bfc720(void* p);
void __cdecl FUN_00abf710(void* p);
void __cdecl FUN_00abfec0(void* p);
void __cdecl FUN_00bfcd00(void* p);
void __cdecl FUN_00c432e0(void* p);
void __cdecl FUN_00b184c0(void* p);
int  __cdecl FUN_00c41d00(int id);
int  __cdecl FUN_00bfc380(int id);
int  __cdecl FUN_00b18460(int id);
int  __cdecl FUN_00abf740(int id);
int  __cdecl FUN_00c884f0(int id);
void __cdecl FUN_00bfc380b(int id);

// static-local guard data for 0xc69110
extern int g_guard1693e00;
extern int g_data1693dec[3];
extern "C" void __cdecl FUN_013c4150();
extern "C" void __cdecl Opaque();   // keeps complex stub bodies from being elided

// ===========================================================================
// @ 0x00c68280  (large rebuild of the position/segment list; incomplete)
// ===========================================================================
void COrn::Update()
{
    Opaque();
}

// ===========================================================================
// @ 0x00c686d0
// ===========================================================================
void COrn::E6d0()
{
    Opaque();
}

// ===========================================================================
// @ 0x00c687e0  (cdecl) clear a vector of noun refs
// ===========================================================================
void __cdecl ClearVector(Vec* v)
{
    int n = v->end - v->begin;
    for (int i = 0; i < n; ++i) {
        int noun = v->begin[i];
        ((void(__thiscall*)(int, int))(*(void***)noun)[0x54 / 4])(noun, 0);
        FUN_00c884f0(noun);
    }
    v->end = v->begin;
}

// ===========================================================================
// @ 0x00c68840
// ===========================================================================
void __fastcall F68840(COrn* o)
{
    ClearVector((Vec*)((char*)o + 4));
}

// ===========================================================================
// @ 0x00c68850
// ===========================================================================
void COrn::E850(int* noun)
{
    if (noun == 0) {
        ClearVector((Vec*)((char*)this + 4));
        return;
    }
    int* first = *(int**)((char*)this + 4);
    float* p = ((cSpatial*)((char*)noun + 0x34))->GetPosition();
    *(float*)((char*)first + 0x118) = p[0];
    *(float*)((char*)first + 0x11c) = p[1];
    *(float*)((char*)first + 0x120) = p[2];
    H4460();
}

// ===========================================================================
// @ 0x00c688a0
// ===========================================================================
void COrn::E8a0(void* a, void* b)
{
    (void)a; (void)b;
    Opaque();
}

// ===========================================================================
// @ 0x00c68930
// ===========================================================================
void COrn::E930()
{
    H3f90();
    Update();
    if (mVec134 != 0) {
        char c = ((char(__thiscall*)(int*))((*(void***)mVec134)[0x10 / 4]))(mVec134);
        if (c == 0)
            ((void(__thiscall*)(int*, int))((*(void***)mVec134)[8 / 4]))(mVec134, 0);
    }
    if (mpModel != 0)
        *(unsigned int*)((char*)mpModel + 4) |= 1;
}

// ===========================================================================
// @ 0x00c68980
// ===========================================================================
void COrn::E980(int* view)
{
    if (mpModel != 0) {
        if (view == 0) {
            *(unsigned int*)((char*)mpModel + 4) &= ~1u;
            goto lab;
        }
        *(unsigned int*)((char*)mpModel + 4) |= 1;
    }
    if (view != 0) {
        float* p = ((cSpatial*)((char*)view + 0x34))->GetPosition();
        if (mPosX != p[0] || mPosY != p[1] || mPosZ != p[2]) {
            mPosX = p[0]; mPosY = p[1]; mPosZ = p[2];
            H3f90();
            Update();
        }
        return;
    }
lab:
    (void)0;
}

// ===========================================================================
// @ 0x00c68aa0
// ===========================================================================
void COrn::Eaa0()
{
    cSpatial* sp = Spatial();
    if (mFlag124 != 0)
        FUN_00ebb720(sp, 0x1707u);
    else
        FUN_00ebb720(sp, 0x705u);
    H3f90();
    Update();
}

// ===========================================================================
// @ 0x00c68ae0
// ===========================================================================
void COrn::Eae0(float* p)
{
    float* cur = Spatial()->GetPosition();
    if (cur[0] != p[0] || cur[1] != p[1] || cur[2] != p[2]) {
        Spatial()->SetPosition(p);
        H3f90();
        Update();
    }
}

// ===========================================================================
// @ 0x00c68b40
// ===========================================================================
void COrn::Eb40(int key)
{
    if (mKey128 == key)
        return;
    if (mVec134 != 0) {
        ((void(__thiscall*)(int*, int))((*(void***)mVec134)[0xc / 4]))(mVec134, 0);
        int* p = mVec134;
        if (p != 0) { mVec134 = 0; ((void(__thiscall*)(int*))((*(void***)p)[4 / 4]))(p); }
    }
    mKey128 = key;
    // EffectsManager()->Create(...) path omitted (needs type info)
    Update();
}

// ===========================================================================
// @ 0x00c68bd0
// ===========================================================================
void COrn::Ebd0(float v)
{
    if (mF12c != v) {
        mF12c = v;
        Update();
    }
}

// ===========================================================================
// @ 0x00c68c00  (cdecl)
// ===========================================================================
int* __cdecl CreateNoun(int* v, int* key)
{
    (void)v; (void)key;
    return 0;
}

// ===========================================================================
// @ 0x00c68d20
// ===========================================================================
int COrn::Ed20(int noun)
{
    int* p = *(int**)((char*)this + 4);
    int n = (*(int**)((char*)this + 8) - p) >> 2;
    int i = 0;
    if (n > 0) {
        do {
            if (*p == noun)
                break;
            ++i;
            ++p;
        } while (i < n);
    }
    // locate noun index then create
    (void)i;
    return 1;
}

// ===========================================================================
// @ 0x00c68d70
// ===========================================================================
void COrn::Ed70(void* a, int* v)
{
    (void)a; (void)v;
}

// ===========================================================================
// @ 0x00c68e30  SP::cMovableDestructibleOrnament::cMovableDestructibleOrnament
// ===========================================================================
void* cMovableDestructibleOrnament::Ctor()
{
    Opaque(); return this;
}

// ===========================================================================
// @ 0x00c68ed0  (destructor-ish: resets vtables then base dtors)
// ===========================================================================
void COrn::Eed0()
{
    Opaque();
}

// ===========================================================================
// @ 0x00c68f30  interface query
// ===========================================================================
int COrn::Ef30(int id)
{
    if (id == 0x283d961)
        return (int)this;
    int r = FUN_00c41d00(id);
    if (r == 0) {
        r = FUN_00bfc380(id);
        if (r == 0) {
            r = FUN_00b18460(id);
            if (r == 0)
                r = FUN_00abf740(id);
        }
    }
    return r;
}

// ===========================================================================
// @ 0x00c69030
// ===========================================================================
void COrn::F030()
{
    FUN_00bfc720(this);
    // SP::cLocomotiveObject::Shutdown((char*)this+0x34) omitted
    FUN_00abf710(this);
    if (mp2c != 0) {
        mp2c = 0;
        ((void(__thiscall*)(int*))((*(void***)mp2c)[4 / 4]))(mp2c);
    }
}

// ===========================================================================
// @ 0x00c69090
// ===========================================================================
void COrn::F090()
{
    Opaque();
}

// ===========================================================================
// @ 0x00c69110  static-local accessor
// ===========================================================================
void* FUN_00c69110()
{
    if ((g_guard1693e00 & 1) == 0) {
        g_guard1693e00 |= 1;
        g_data1693dec[0] = 0;
        g_data1693dec[1] = 0;
        g_data1693dec[2] = 0;
        atexit(FUN_013c4150);
    }
    return g_data1693dec;
}

// ===========================================================================
// @ 0x00c69150  Simulator::cNanoDrone::cNanoDrone
// ===========================================================================
void* cNanoDrone::Ctor()
{
    Opaque(); return this;
}

// ===========================================================================
// @ 0x00c691e0  interface query
// ===========================================================================
int COrn::F1e0(int id)
{
    if (id == 0x6ef0ec9)
        return (int)this;
    int r = FUN_00b18460(id);
    if (r == 0) {
        r = FUN_00c884f0(id);
        if (r == 0)
            return FUN_00bfc380(id);
    }
    return r;
}

// ===========================================================================
// @ 0x00c69290
// ===========================================================================
void COrn::F290()
{
    Opaque();
}
