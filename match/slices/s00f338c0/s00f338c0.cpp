// Slice s00f338c0 -- Simulator property-list object, part 3 (bfs2 slice 13).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- smart-pointer element (0x10)
struct RCObj { virtual void AddRef(); virtual void Release(); };
struct SmartPtr {
    void* p;
    SmartPtr& operator=(const SmartPtr& o) {
        if (p != o.p) {
            if (o.p) ((RCObj*)o.p)->AddRef();
            void* old = p;
            p = o.p;
            if (old) ((RCObj*)old)->Release();
        }
        return *this;
    }
};
struct E { SmartPtr sp; int a; int b; float c; };

// @ 0x00F33A10
E* CopyFwd(E* first, E* last, E* dest) { for (; first != last; ++first, ++dest) *dest = *first; return dest; }
// @ 0x00F33AC0
E* CopyBwd(E* first, E* last, E* dest) { while (first != last) { --last; --dest; *dest = *last; } return dest; }

// ---------------------------------------------------------------- property-list object
struct CPL {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual void s11(void* parent);
    char padC[0x30-4];
    void* m30;
    void SetParent(void* parent);          // 0x006A1710
};

struct PObj {
    char pad0[0xc];
    CPL* mC;                               // +0x00c
    char pad10[0xf4-0x10];
    int mF4;                               // +0x0f4
    int mF8;                               // +0x0f8
    int mFC;                               // +0x0fc
    void setF4(int* p);
    void resetParent(CPL* p);
    void v323c0();
    void v32cb0();
    void v32d10();
};

// @ 0x00F33B50
void PObj::setF4(int* p)
{
    if (mF4 != p[0] || mF8 != p[1] || mFC != p[2]) {
        mF4 = p[0]; mF8 = p[1]; mFC = p[2];
        v323c0();
        v32cb0();
    }
}

// @ 0x00F33BB0
void PObj::resetParent(CPL* p)
{
    v32d10();
    if (p != mC) {
        p->s11(mC);
        p->SetParent(mC->m30);
    }
}

// ---------------------------------------------------------------- not yet matching
void FUN_00f338c0(void* self) { (void)self; }   // @ 0x00F338C0
E* FUN_00f33bf0(E* a, E* b, E* c) { (void)b; (void)c; return a; }  // @ 0x00F33BF0
void FUN_00f33d70(void* self) { (void)self; }   // @ 0x00F33D70
void FUN_00f33f90(void* self) { (void)self; }   // @ 0x00F33F90
void FUN_00f340e0(void* self) { (void)self; }   // @ 0x00F340E0
void FUN_00f342d0(void* self) { (void)self; }   // @ 0x00F342D0
void FUN_00f343a0(void* self) { (void)self; }   // @ 0x00F343A0
void FUN_00f344e0(void* self, void* a) { (void)self; (void)a; }  // @ 0x00F344E0
void FUN_00f34560(void* self) { (void)self; }   // @ 0x00F34560
void FUN_00f34660(void* self, void* a) { (void)self; (void)a; }  // @ 0x00F34660
