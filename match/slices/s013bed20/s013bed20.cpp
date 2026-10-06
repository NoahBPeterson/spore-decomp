// Slice s013bed20: compiler-generated static cleanup/destructor functions from the
// engine's startup/shutdown module (MSVC 2008 SP1, /O2). Each entry is a small
// "destroy the file-scope global" routine: array destructor iterators, EASTL
// container teardown, singleton deletes and Variant destructors.
//
// NOTE: for the VAs whose Ghidra bounds extend over a following *unlisted* tail thunk
// (an interior int3 or a second prologue), byte-exact matching is impossible from a
// single C++ function; those are listed in nonmatching.txt.
#include "types.h"

// ---- imports (declared; relocations are masked) ----
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void*);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(void*);
extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);
extern "C" __declspec(dllimport) void* __cdecl memset(void*, int, unsigned int);

// ---- shared helpers ----
extern "C" void __stdcall eh_vector_dtor(void* p, unsigned int size, int count,
                                         void(__stdcall* dtor)(void*));
extern "C" void __stdcall arr_dtor1(void*);
extern "C" void __stdcall arr_dtor2(void*);
extern "C" void __stdcall arr_dtor3(void*);
extern void __cdecl cdecl_free(void*);          // operator delete
extern void __cdecl cdecl_f9250c0(int);
extern char __cdecl cdecl_f935ad0(void*);

struct Method { void M(); };
struct Method1 { void M(void*); };
struct MethodI { void M(int); };
struct HT {
    char pad0[4];
    void* mBegin;    // +4
    unsigned mEnd;   // +8
    unsigned mCount; // +0xc
    char pad1[0xc];
    void* mAlloc;    // +0x1c
    void DoFreeNodes(void*, void*);
};
struct VecB { void* mBegin; int mEnd; int mPad; void* mAlloc; void Free(void*, void*); };
struct Alloc {
    virtual void a();
    virtual void b();
    virtual void c();
    virtual void dealloc(void*, unsigned);
};

struct VA { void Destruct(int); };
struct V4 { virtual void a(); virtual void b(); virtual void c(); virtual void d(); };
struct Obj10 { virtual void a(); virtual void b(); };
struct CleanObj {
    char pad[0x10];
    Obj10* m;  // +0x10
};
struct Ref {
    virtual void Release(int);
    int count;  // +4
};
struct DDC { void Dispose(int); };
struct MI {
    virtual void a();
    virtual void b();
    virtual void c();
    virtual void d();
    virtual void e(int);
};
struct HT2 {
    char pad0[4];
    void* mBegin;      // +4
    unsigned mCount;   // +8
    unsigned mFieldC;  // +0xc
    void DoAllocateBuckets(void*, unsigned);
};

// ---- globals ----
extern char g_16029b0[];
extern unsigned char g_16029c0;
extern char g_16032a8[];
extern char g_16198c0[];
extern char g_1624710[];
extern char g_162a386[];
extern int g_1604b80;
extern char g_1604b48[];
extern int g_1540df0, g_1540de8;
extern int g_1687104, g_16870fc;
extern int g_154744c, g_154745c;
extern int g_15671b8, g_15671b0, g_15671c0;
extern int g_156858c, g_1568584, g_1568594;
extern int g_156c5c4, g_156c5bc, g_156c5cc;
extern char g_16679d0[];
extern char g_1667bc0[];
extern void* g_1668f1c;
extern int g_1679e8c;
extern void* g_1638280;
extern char g_1638254[];
extern char vtbl_1414ba0[];
extern char vtbl_1417694[];
extern void* g_1542214;
extern char g_154220c[];
extern void* g_164b410;
extern char g_164c078[];
extern void* g_164c0b4, *g_164c0b0, *g_164c094, *g_164c080;
extern char vtbl_1417804[];
extern char vtbl_1417790[];
extern char g_1544138[];
extern char g_1544140[];
extern char g_1544184[];
extern unsigned char g_1544194;
extern char vtbl_13ec458[];
extern char vtbl_13eb938[];
extern char g_1547f54[];
extern char g_1547f78[];
extern char g_16519a8[];
extern char g_1651994p[];
extern int g_165199c;
extern void* g_165199a0;
extern char g_16519ac[];
extern void* g_16519c4;
extern int g_1667b24;
extern int g_1668e9c;
extern int g_1668ea4;
extern int g_166b0f0;
extern unsigned char g_166aa7c;
extern int g_154ed20, g_154ed24;
extern char g_154df80[];
extern void* g_154df84;
extern unsigned char g_154df88;
extern void* g_154df8c;
extern void* g_154df90;
extern char g_166b0f0_v;
extern int g_166b170;
extern char g_166b140[];
extern char g_166b190[];
extern char g_166d9a0[];
extern unsigned char g_166d9b0;
extern char g_1567e2c[];
extern int g_1567e38;
extern char g_1568568[];
extern int g_1568574;
extern int g_167bef0, g_167bef4;
extern int g_167c324, g_167c328;
extern void* g_167c320;
extern char g_167c30c[];
extern char g_167c31c[];
extern char vtbl_145ed3c[];
extern char vtbl_143e0e4[];
extern char vtbl_1403934[];

// =====================================================================
// @ 0x013BED20
void f_013bed20() {
    if (g_16029c0 & 4) ((VA*)g_16029b0)->Destruct(0);
}

// @ 0x013BED40
void f_013bed40() { eh_vector_dtor(g_16032a8, 0x150, 0xb, arr_dtor1); }

// @ 0x013BEDC0
void f_013bedc0() {
    if (g_1604b80) {
        if (g_1604b80 == 1) ((Method*)g_1604b48)->M();
        g_1604b80 = 0;
    }
}

// @ 0x013BF360
void f_013bf360() { eh_vector_dtor(g_16198c0, 0x64, 0x100, arr_dtor2); }

// @ 0x013BF480
void f_013bf480() { eh_vector_dtor(g_1624710, 0x44, 0x100, arr_dtor3); }

// @ 0x013BF600
void f_013bf600() { ((Method*)g_162a386)->M(); }

// @ 0x013C0100
void f_013c0100() {
    if (g_1638280) {
        FreeLibrary(g_1638280);
        g_1638280 = 0;
        memset(g_1638254, 0, 0x2c);
    }
}

// @ 0x013C0230
void f_013c0230() {
    if ((g_1540df0 - g_1540de8) > 1 && g_1540de8) cdecl_free((void*)g_1540de8);
}

// @ 0x013C0250
void f_013c0250() {
    void* p = g_1542214;
    *(void**)g_154220c = vtbl_1414ba0;
    if (p) ((V4*)p)->d();
}

// @ 0x013C0300
void f_013c0300() {
    if (g_164b410) ((V4*)g_164b410)->b();
}

// @ 0x013C0510
void f_013c0510() {
    *(void**)g_164c078 = vtbl_1417694;
    ((DDC*)g_164c078)->Dispose(0);
    if (g_164c0b4) ((V4*)g_164c0b4)->b();
    if (g_164c0b0) ((V4*)g_164c0b0)->b();
    if (g_164c094) ((V4*)g_164c094)->b();
    if (g_164c080) ((V4*)g_164c080)->b();
}

// @ 0x013C0570
void f_013c0570() {
    *(void**)g_1544138 = vtbl_1417804;
    *(void**)g_1544140 = vtbl_1417790;
    ((MI*)g_1544140)->e(0);
    if (g_1544194 & 4) ((VA*)g_1544184)->Destruct(0);
    *(void**)g_1544138 = vtbl_13ec458;
    *(void**)g_1544140 = vtbl_13eb938;
}

// @ 0x013C08E0
void f_013c08e0() {
    if (g_154744c && g_154744c != g_154745c) cdecl_free((void*)g_154744c);
}

// @ 0x013C0950
void f_013c0950() {
    HT* h = (HT*)g_1547f54;
    h->DoFreeNodes(h->mBegin, (void*)h->mEnd);
    unsigned n = h->mEnd;
    h->mCount = 0;
    if (n > 1) ((Alloc*)h->mAlloc)->dealloc(h->mBegin, n * 4 + 4);
}

// @ 0x013C09A0
void f_013c09a0() {
    HT* h = (HT*)g_1547f78;
    h->DoFreeNodes(h->mBegin, (void*)h->mEnd);
    unsigned n = h->mEnd;
    h->mCount = 0;
    if (n > 1) ((Alloc*)h->mAlloc)->dealloc(h->mBegin, n * 4 + 4);
}

// @ 0x013C0BA0
void f_013c0ba0() {
    VecB* v = (VecB*)g_1651994p;
    v->Free(v->mBegin, (void*)v->mEnd);
    if (v->mBegin)
        ((Alloc*)v->mAlloc)->dealloc(v->mBegin, (unsigned)(((g_165199c - (int)v->mBegin) / 0x14) * 0x14));
}

// @ 0x013C0C00
void f_013c0c00() {
    HT* h = (HT*)g_16519ac;
    h->DoFreeNodes(h->mBegin, (void*)h->mEnd);
    unsigned n = h->mEnd;
    h->mCount = 0;
    if (n > 1) ((Alloc*)h->mAlloc)->dealloc(h->mBegin, n * 4 + 4);
}

// @ 0x013C0C50
void f_013c0c50() { DeleteCriticalSection(g_16679d0); }

// @ 0x013C0CE0
void f_013c0ce0() {
    char ok = cdecl_f935ad0((void*)g_1667b24);
    int v = g_1667b24;
    if (ok && v) {
        Ref* r = *(Ref**)(v + 0x10);
        if (r) {
            int n = r->count - 1;
            r->count = n;
            if (n == 0) {
                r->count = 1;
                r->Release(1);
            }
        }
        cdecl_free((void*)v);
    }
}

// @ 0x013C0D40
void f_013c0d40() {
    ((MethodI*)g_1667bc0)->M(1);
    DeleteCriticalSection(g_1667bc0 + 0x40);
}

// @ 0x013C0DA0
void f_013c0da0() {
    if (cdecl_f935ad0((void*)g_1668e9c)) {
        if (g_1668e9c) {
            Obj10* m = ((CleanObj*)g_1668e9c)->m;
            if (m) m->b();
            cdecl_free((void*)g_1668e9c);
        }
    }
}

// @ 0x013C0DE0
void f_013c0de0() {
    if (cdecl_f935ad0((void*)g_1668ea4)) {
        if (g_1668ea4) {
            Obj10* m = ((CleanObj*)g_1668ea4)->m;
            if (m) m->b();
            cdecl_free((void*)g_1668ea4);
        }
    }
}

// @ 0x013C0E80
void f_013c0e80() { cdecl_f9250c0(0); }

// @ 0x013C0E90
void f_013c0e90() {
    *(void**)g_154df80 = vtbl_143e0e4;
    if (g_154df88) {
        if (g_154df8c) {
            ((void(__cdecl*)(void*, void*, void*))g_154df8c)(g_154df80, g_154df84,
                                                             g_154df90);
            *(void**)g_154df80 = vtbl_1403934;
            return;
        }
        if (g_154df84) {
            ((Method*)g_154df84)->M();  // ~GeneralAllocatorDebug(this)
            cdecl_free(g_154df84);
        }
    }
    *(void**)g_154df80 = vtbl_1403934;
}

// @ 0x013C0F40
void f_013c0f40() { FreeLibrary(g_1668f1c); }

// @ 0x013C0FC0
void f_013c0fc0() {
    if (g_166aa7c) WSACleanup();
}

// @ 0x013C1060
void f_013c1060() {
    if (cdecl_f935ad0((void*)g_166b0f0)) {
        if (g_166b0f0) {
            Obj10* m = ((CleanObj*)g_166b0f0)->m;
            if (m) m->b();
            cdecl_free((void*)g_166b0f0);
        }
    }
}

// @ 0x013C10C0
void f_013c10c0() {
    if (g_154ed20 != (int)&g_154ed20) {
        int p = g_154ed20;
        do {
            int n = *(int*)p;
            *(int*)(p + 4) = 0;
            *(int*)p = 0;
            p = n;
        } while (p != (int)&g_154ed20);
    }
    g_154ed20 = 0;
    g_154ed24 = 0;
}

// @ 0x013C1110
void f_013c1110() {
    if (g_166b170 && *(int*)(g_166b170 - 4) != 0) cdecl_free((void*)g_166b170);
    ((Method*)g_166b140)->M();
}

// @ 0x013C1150
void f_013c1150() {
    HT* h = (HT*)g_166b190;
    h->DoFreeNodes(h->mBegin, (void*)h->mEnd);
    unsigned n = h->mEnd;
    h->mCount = 0;
    if (n > 1) ((Alloc*)h->mAlloc)->dealloc(h->mBegin, n * 4 + 4);
}

// @ 0x013C1760
void f_013c1760() {
    if (g_166d9b0 & 4) ((VA*)g_166d9a0)->Destruct(0);
}

// @ 0x013C1B90
void f_013c1b90() {
    if (g_1679e8c && *(int*)(g_1679e8c - 4) != 0) cdecl_free((void*)g_1679e8c);
}

// @ 0x013C1E00
void f_013c1e00() {
    int d = g_15671b8 - g_15671b0;
    if (((d & ~1) > 2) && g_15671b0 && g_15671b0 != g_15671c0) cdecl_free((void*)g_15671b0);
}

// @ 0x013C1EA0
void f_013c1ea0() {
    ((Method1*)g_1567e2c)->M((void*)g_1567e38);
}

// @ 0x013C1F50
void f_013c1f50() {
    if (g_167bef0 != (int)&g_167bef0) {
        int p = g_167bef0;
        do {
            int n = *(int*)p;
            *(int*)(p + 4) = 0;
            *(int*)p = 0;
            p = n;
        } while (p != (int)&g_167bef0);
    }
    g_167bef0 = 0;
    g_167bef4 = 0;
}

// @ 0x013C20F0
void f_013c20f0() {
    HT2* h = (HT2*)g_167c31c;
    *(void**)g_167c30c = vtbl_145ed3c;
    h->DoAllocateBuckets(h->mBegin, h->mCount);
    h->mFieldC = 0;
    if (h->mCount > 1) cdecl_free(h->mBegin);
    *(void**)g_167c30c = vtbl_1403934;
}

// @ 0x013C2140
void f_013c2140() {
    if ((g_156858c - g_1568584) > 1 && g_1568584 && g_1568584 != g_1568594)
        cdecl_free((void*)g_1568584);
}

// @ 0x013C21D0
void f_013c21d0() { ((Method1*)g_1568568)->M(*(void**)&g_1568574); }

// @ 0x013C29F0
void f_013c29f0() {
    if ((g_1687104 - g_16870fc) > 1 && g_16870fc) cdecl_free((void*)g_16870fc);
}

// @ 0x013C3020
void f_013c3020() {
    int d = g_156c5c4 - g_156c5bc;
    if (((d & ~1) > 2) && g_156c5bc && g_156c5bc != g_156c5cc) cdecl_free((void*)g_156c5bc);
}
