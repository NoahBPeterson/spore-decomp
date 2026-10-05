// Slice s0077d800: EASTL vector helpers and shader-constant registration tables.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- EASTL-ish container helpers ---------------------------------------------------------
struct U32Vec {
    unsigned* begin;   // +0
    unsigned* end;     // +4
    unsigned* cap;     // +8
    void DoInsertValue(unsigned* pos, unsigned* val);   // 0x004558a0
};

extern void __cdecl copy_impl_r(void* a, void* b, void* c);  // 0x00705250
extern void* __cdecl FUN_00706ab0(void* a, void* b, void* c);

struct Vec16 {
    char pad[0x14];
    void Grow(void* a, unsigned b, void* c);   // 0x0077d510
};

struct Vec8Thing {
    char pad[8];
    int  FUN_0077d970(unsigned val);
    void FUN_0077d800(void* first, void* last);
    void FUN_0077d9c0(unsigned n, void* val);
};

struct BigVec {
    char pad[0x14];
    void* FUN_0077e260(unsigned a, unsigned b);
    void* FUN_0077e2c0(void* a, void* b);
};

struct CamThing {
    char pad[0x180];
    void FUN_0077ef60(float* v);
};

#pragma warning(disable:4035)
static __forceinline int FloorToInt(float f) {
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// @ 0x0077d970
int Vec8Thing::FUN_0077d970(unsigned val) {
    U32Vec* v = (U32Vec*)((char*)this + 8);
    unsigned* end = v->end;
    if (end < v->cap) {
        v->end = end + 1;
        if (end != 0) {
            *end = val;
            return (int)(v->end - v->begin) - 1;
        }
    } else {
        v->DoInsertValue(end, &val);
    }
    return (int)(v->end - v->begin) - 1;
}

// @ 0x0077d9c0
void Vec8Thing::FUN_0077d9c0(unsigned n, void* val) {
    int p = (int)this;
    int end = *(int*)(p + 4);
    int cur = (end - *(int*)(p)) >> 4;
    if (n > (unsigned)cur) {
        ((Vec16*)p)->Grow((void*)end, n - cur, val);
        return;
    }
    int dest = n * 0x10 + *(int*)(p);
    copy_impl_r((void*)end, (void*)end, (void*)dest);
    *(int*)(p + 4) = *(int*)(p + 4) + (((end - dest) >> 4) * -0x10);
}

// @ 0x0077eef0  linear interpolation into a float array (x87 return)
float __cdecl FUN_0077eef0(int n, float* arr, float t) {
    if (n == 1)
        return arr[0];
    t = (float)(n - 1) * t;
    int i = FloorToInt(t);
    float r = arr[i];
    float d = t - (float)i;
    if (d > 0.0f)
        r = (arr[i + 1] - r) * d + r;
    return r;
}

struct Float3 { float x, y, z; };

// @ 0x0077ef60
void CamThing::FUN_0077ef60(float* v) {
    char* th = (char*)this;
    float f = 1.0f - (*(float*)(th + 0x16c) * v[2] +
                      *(float*)(th + 0x168) * v[1] +
                      *(float*)(th + 0x164) * v[0]);
    if (f > *(float*)(th + 0x20c))
        *(Float3*)(th + 0x164) = *(Float3*)v;
    *(Float3*)(th + 0x170) = *(Float3*)v;
}

// ---- partial skeletons (see partial.txt) -------------------------------------------------

// @ 0x0077d800  (partial) vector assign/grow
void Vec8Thing::FUN_0077d800(void* first, void* last) {
    (void)first; (void)last;
}

// @ 0x0077d8c0  (partial) EH destructor: release elements, reset vector, restore vftable
void __fastcall FUN_0077d8c0(void* p) {
    (void)p;
}

// @ 0x0077e260  (partial) EH constructor with inline 0x100-byte storage
void* BigVec::FUN_0077e260(unsigned a, unsigned b) {
    (void)a; (void)b;
    return this;
}

// @ 0x0077e2c0  (partial) EH constructor with inline 0x40-byte storage
void* BigVec::FUN_0077e2c0(void* a, void* b) {
    (void)a; (void)b;
    return this;
}

// @ 0x0077e4a0  (partial) inverse-transform + normalization-constant setup
void __cdecl FUN_0077e4a0(unsigned reg, unsigned p2, int isVS) {
    (void)reg; (void)p2; (void)isVS;
}

// @ 0x0077e6d0  (partial) registers the whole rw shader-constant table
void __cdecl FUN_0077e6d0() {
}
