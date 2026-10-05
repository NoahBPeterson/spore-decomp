// Slice s00767ee0: "RenderAsset" raster writer, resource reload/arm helpers,
// 0x7c-stride vector resize and the BakeSprites job object ctors/dtors.
// /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <new>

extern char g_file[];

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void  __cdecl UnionDestroy(void* p, int type);                              // 0x7668c0 (slice 30)
void  __fastcall FUN_007642c0(void* self);                                // 0x7642c0 (thiscall)
void  __cdecl FUN_00764760(void* self, int v);                              // 0x764760 (thiscall)
void  __cdecl FUN_0041f2d0(void* p);                                        // 0x41f2d0
void  __cdecl FUN_00700670(void* a, void* b);                               // 0x700670
void  __cdecl FUN_00767760(void* p);                                        // 0x767760
void  __cdecl FUN_004b5440(void* p);                                        // 0x4b5440
void  __cdecl FUN_00767350(void* self, void* pos, uint32_t n, void* value); // 0x767350
void* __cdecl FUN_0093b530(int a, int b, void* c);                          // 0x93b530
void  __cdecl FUN_0041cc60(void* p);                                        // 0x41cc60
void* __cdecl FUN_007003a0(void* a, int n);                                 // 0x7003a0
void  __cdecl FUN_00700670b(void* a, void* b);
bool  __cdecl ReadValue68(void* stream, void* dst, int n);   // 0x93a6c0
bool  __cdecl WriteValue68(void* stream, int a, uint32_t b); // 0x93a890
}

// ===========================================================================
// @ 0x00767ee0  SP::cGraphicsResourceFactory::WriteResourceRaster
// ===========================================================================
struct Raster {
    char pad0[4];
    int mFlags;               // +0x4
    char pad8[4];
    unsigned short mWidth;    // +0xc
    unsigned short mHeight;   // +0xe
    unsigned char mLevels;    // +0x11
    unsigned char mFace;      // +0x12
};
int __stdcall WriteResourceRaster(void* arg, int* stream) {
    Raster* r = *(Raster**)((char*)arg + 0x18);
    (void)r; (void)stream;
    // full writer is a register-heavy event loop over mip levels/faces;
    // modelled only structurally here.
    return 1;
}

// ===========================================================================
// @ 0x00768200  release the current raster-load union state
// ===========================================================================
struct C68200 {
    char pad[0xd0];
    int mD0;                  // +0xd0
    void Release();
};
void C68200::Release() {
    int v = mD0;
    if (v) {
        if (v == 5) {
            FUN_007642c0(this);
        } else {
            UnionDestroy(this, v);
        }
        mD0 = 0;
    }
}

// ===========================================================================
// @ 0x00768240  ctor: init a 0x7c-stride inline vector and register a job
// ===========================================================================
struct C68240 {
    void* m0;                 // +0x00
    void* m4;                 // +0x04
    void* m8;                 // +0x08
    int   mc;                 // +0x0c
    void* m10;                // +0x10
    int   m14;                // +0x14
    char  m18[0x7c];          // +0x18 inline storage
    C68240(void* arg);
};
C68240::C68240(void* arg) {
    char* base = m18;
    m10 = base;
    m4 = base;
    m0 = base;
    m8 = base + 0x80;
    FUN_00767760(arg);
}

// ===========================================================================
// @ 0x007682a0  vector<0x7c>::resize(n)
// ===========================================================================
struct V7cB {
    char* b; char* e; char* c;
    void Resize(uint32_t n);
};
void V7cB::Resize(uint32_t n) {
    uint32_t count = (uint32_t)((e - b) / 0x7c);
    if (count < n) {
        char tmp[0x7c];
        FUN_00764760(&tmp, 0);
        FUN_00767350(this, e, n - count, tmp);
        FUN_0041f2d0(&tmp);
    } else {
        FUN_00700670(b + n * 0x7c, e);
    }
}

// ===========================================================================
// @ 0x00768370  BakeSprites job ctor (vtable + refcounted members + fan-out)
// ===========================================================================
struct C68370 {
    void* m0; void* m4; void* m8; void* mc; void* m10; void* m14;
    int   m18; int m1c; int m20; int m24; void* m28;
    char pad2c[0xd0];
    int   mFC; int m100; void* m104; void* m108; void* m10c; void* m118;
    void* m19c; void* m1a0; void* m1a4; void* m1b0; char m334;
    C68370(void* a, int* b, void* c, int* d, void* e);
};
C68370::C68370(void* a, int* b, void* c, int* d, void* e) {
    m0 = (void*)0;            // vtable (masked)
    m4 = (void*)0;
    _InterlockedExchange((volatile long*)&m8, 0);
    m0 = (void*)0;
    m4 = (void*)0;
    mc = b;
    if (b) ((void(__thiscall**)(void*))*(void***)b)[1](b);
    m10 = e;
    if (e) ((void(__thiscall**)(void*))*(void***)e)[1](e);
    m14 = a;
    if (a) ((void(__thiscall**)(void*))*(void***)a)[0](a);
    m18 = 0; // param_6 (int) - approximated
    m1c = d[0];
    m20 = d[1];
    m24 = d[2];
    m28 = 0;
    mFC = 0; m100 = 0;
    m104 = (char*)this + 0x11c;
    m108 = (char*)this + 0x11c;
    m10c = (char*)this + 0x19c;
    m118 = 0;
    m19c = (char*)this + 0x1b4;
    m1a0 = (char*)this + 0x1b4;
    m1a4 = (char*)this + 0x334;
    m1b0 = 0;
    m334 = 0;
}

// ===========================================================================
// @ 0x00768540  BakeSprites job destructor
// ===========================================================================
void __fastcall C68370Dtor(C68370* self) {
    self->m0 = (void*)0;
    self->m4 = (void*)0;
    if (self->m19c && ((int*)self->m19c)[-1] != 0)
        Dealloc(self->m19c);
    FUN_004b5440((char*)self + 0x104);
    if (self->m100) ((void(__thiscall**)(void*))*(void***)self->m100)[1]((void*)self->m100);
    int u = self->mFC;
    if (u) {
        if (u == 5) FUN_007642c0((char*)self + 0x2c);
        else UnionDestroy((char*)self + 0x2c, u);
        *(int*)((char*)self + 0xfc) = 0;
    }
    if (self->m28) ((void(__thiscall**)(void*))*(void***)self->m28)[2](self->m28);
    if (self->m14) ((void(__thiscall**)(void*))*(void***)self->m14)[1](self->m14);
    if (self->m10) ((void(__thiscall**)(void*))*(void***)self->m10)[2](self->m10);
    if (self->mc) ((void(__thiscall**)(void*))*(void***)self->mc)[2](self->mc);
    self->m0 = (void*)0;
    self->m4 = (void*)0;
}

// ===========================================================================
// @ 0x00768650  load a set of 0x7c records and attach visual effects
// ===========================================================================
struct C68650 {
    char pad[0x108];
    void* vecBegin;           // +0x108
    char pad10c[4];
    void* vecEnd;             // +0x10c  (approximate)
};
bool __stdcall LoadRecords(void* stream, int obj) {
    uint32_t count;
    if (!ReadValue68(stream, &count, 4))
        return false;
    if (!WriteValue68(stream, 0x38, count))
        return false;
    // per-record load + visual-effect attach (structurally modelled)
    for (uint32_t i = 0; i < count; i++) {
        void* rec = (void*)(*(int*)(obj + 0x108) + i * 0x7c);
        if (!ReadValue68(stream, rec, 0x38)) return false;
        if (!ReadValue68(stream, (char*)rec + 0x38, 0x38)) return false;
        if (!ReadValue68(stream, (char*)rec + 0x70, 4)) return false;
    }
    return true;
}
