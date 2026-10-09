// Slice s013c31a0: continuation of the engine shutdown/static-destructor module
// (MSVC 2008 SP1, /O2). Same families as the previous slice: rbtree/hashtable/vector
// teardown, singleton release, Variant destructors and refcount releases.
//
// NOTE: VAs whose Ghidra bounds span a following unlisted tail thunk are behaviourally
// complete here but cannot match from one C++ function; see nonmatching.txt.
#include "types.h"

extern "C" __declspec(dllimport) int __stdcall TlsFree(unsigned long);
extern void __cdecl cdecl_free(void*);          // operator delete // 0x00f47380
extern void __cdecl cdecl_shutdown_shared();    // EA::Allocator::ShutdownSharedAllocator
extern void __cdecl RemoveHandler(int, int, int, int, int);

struct Method { void M(); };
struct MethodI { void M(int); };
struct VR { virtual void Rel(int); int count; };
struct V2 { virtual void a(); virtual void b(); };
struct V3 { virtual void a(); virtual void b(); virtual void c(); };
struct VA { void Destruct(int); };
struct VBig {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66();
};
struct HTb { void* mBegin; unsigned mEnd; void DoFreeNodes(void*, void*); };
struct Str { ~Str(); };
struct CS { void Shutdown(int); ~CS(); };

#define DBGFREE(p) do { if ((p) && *(int*)((char*)(p) - 4) != 0) cdecl_free((void*)(p)); } while (0)

extern char g_168bd4c[];
extern char g_168cb28[];
extern char g_168db30[];
extern char g_168dc98[];
extern int g_168e7cc;
extern int g_168e754;
extern char g_168f010[];
extern char g_1699a0c[];
extern char g_157abb0[];
extern int g_157abc0;
extern void* g_169d2a8;
extern int g_15821d4, g_15821cc, g_15821dc;
extern void* g_169e2d4;
extern void* g_169e2d0;
extern int g_169e2a8;
extern char g_169f200[];
extern void* g_16a15f8;
extern char g_15a4878[];
extern char vtbl_147f198[];
extern char g_15a51b4[];
extern char g_15a51b8[];
extern char g_15a51bc[];
extern char vtbl_1480344[];
extern char vtbl_1480338[];
extern char g_16b4178[];
extern char g_16b4278[];
extern char g_15accb8[];
extern char g_15accbc[];
extern char vtbl_13ec458[];
extern char vtbl_13eb938[];
extern int g_15ace40, g_15ace38, g_15ace48;
extern char g_16c7c08[];
extern int g_16c7c14;
extern char vtbl_148b708[];
extern char g_16c7f30[];
extern int g_15ad7d4, g_15ad7cc, g_15ad7dc;
extern int g_16c89c4, g_16c89c8;
extern unsigned char g_16c8b48;
extern int g_16c9f54, g_16c9f58, g_16c9f5c;
extern char g_16d6d70[];
extern char g_16d6db0[];
extern void* g_16d714c;
extern void* g_16d7150;
extern void* g_15b7478;
extern char g_15b7458[];
extern char g_15b749c[];
extern void* g_15b74a4;
extern char vtbl_149953c[];
extern char vtbl_1416f14[];
extern char g_15b7510[];
extern void* g_15b7518;
extern char vtbl_1499570[];
extern char g_15b7648[];
extern void* g_15b7650;
extern int g_15b7654;
extern char vtbl_14996d4[];
extern char g_16df428[];
extern char g_15b7b2c[];
extern char g_15b79b8[];
extern char g_15b7844[];
extern char g_15b7840[];
extern void* g_15b8508;
extern int g_15b84f4, g_15b84f8, g_15b84fc, g_15b8500, g_15b8504;
extern char g_15b84f0[];
extern char vtbl_13eb394[];
extern int g_16e0d04;
extern int g_16e4174;

// @ 0x013C31A0
void f_013c31a0() {
    HTb* h = (HTb*)g_168bd4c;
    h->DoFreeNodes(h->mBegin, (void*)h->mEnd);
    DBGFREE(h->mBegin);
}

// @ 0x013C33A0
void f_013c33a0() {
    char* base = g_168cb28;
    for (int i = 2; i >= 0; i--) {
        void* p = *(void**)(base + 0xc);
        while (p) {
            void* next = *(void**)((char*)p + 4);
            ((MethodI*)base)->M(*(int*)p);
            cdecl_free(p);
            p = next;
        }
        base -= 0x1c;
    }
}

// @ 0x013C3550
void f_013c3550() {
    char* p = g_168db30;
    for (int i = 5; i >= 0; i--) {
        p -= 0x44;
        ((Method*)p)->M();
    }
}

// @ 0x013C35B0
void f_013c35b0() {
    char* p = g_168dc98;
    for (int i = 1; i >= 0; i--) {
        p -= 0x44;
        ((Method*)p)->M();
    }
}

// @ 0x013C3900
void f_013c3900() {
    DBGFREE(g_168e7cc);
    DBGFREE(g_168e754);
}

// @ 0x013C3A20
void f_013c3a20() {
    char* p = g_168f010;
    for (int i = 9; i >= 0; i--) {
        p -= 0x14;
        ((Str*)p)->~Str();
    }
}

// @ 0x013C42D0
void f_013c42d0() {
    char* p = g_1699a0c;
    for (int i = 0x5f; i >= 0; i--) {
        p -= 0xb8;
        void* q = *(void**)p;
        if (q) ((V2*)q)->b();
        DBGFREE(*(void**)(p - 0x14));
    }
}

// @ 0x013C43B0
void f_013c43b0() {
    HTb* h = (HTb*)g_157abb0;
    h->DoFreeNodes(h->mBegin, (void*)h->mEnd);
    if (h->mBegin && h->mBegin != (void*)g_157abc0) cdecl_free(h->mBegin);
}

// @ 0x013C4C10
void f_013c4c10() {
    if (g_169d2a8) ((V2*)g_169d2a8)->b();
}

// @ 0x013C4F20
void f_013c4f20() {
    int d = g_15821d4 - g_15821cc;
    if (((d & ~1) > 2) && g_15821cc && g_15821cc != g_15821dc) cdecl_free((void*)g_15821cc);
}

// @ 0x013C52D0
void f_013c52d0() {
    if (g_169e2d4) ((V2*)g_169e2d4)->b();
    if (g_169e2d0) ((V2*)g_169e2d0)->b();
    DBGFREE(g_169e2a8);
}

// @ 0x013C5790
void f_013c5790() {
    char* p = g_169f200;
    for (int i = 3; i >= 0; i--) {
        p -= 0x44;
        ((Method*)p)->M();
    }
}

// @ 0x013C6B00
void f_013c6b00() {
    if (g_16a15f8) ((V2*)g_16a15f8)->b();
}

// @ 0x013C6E20
void f_013c6e20() {
    *(void**)g_15a4878 = vtbl_147f198;
    *(void**)(g_15a4878 + 4) = 0;
}

// @ 0x013C72D0
void f_013c72d0() {
    *(void**)g_15a51b4 = vtbl_1480344;
    *(void**)g_15a51b8 = vtbl_1480338;
    ((CS*)g_15a51bc)->Shutdown(1);
    ((CS*)g_15a51bc)->~CS();
    *(void**)g_15a51b4 = vtbl_13eb938;
}

// @ 0x013C7DB0
void f_013c7db0() {
    char* p = g_16b4178;
    for (int i = 5; i >= 0; i--) {
        p -= 0x98;
        ((Method*)p)->M();
    }
}

// @ 0x013C7E80
void f_013c7e80() {
    char* p = g_16b4278;
    for (int i = 0x3f; i >= 0; i--) {
        p -= 4;
        void* q = *(void**)p;
        if (q) ((V3*)q)->c();
    }
}

// @ 0x013C8D90
void f_013c8d90() {
    *(void**)g_15accbc = vtbl_13ec458;
    *(void**)g_15accb8 = vtbl_13eb938;
}

// @ 0x013C8F60
void f_013c8f60() {
    int d = g_15ace40 - g_15ace38;
    if (((d & ~1) > 2) && g_15ace38 && g_15ace38 != g_15ace48) cdecl_free((void*)g_15ace38);
}

// @ 0x013C9030
void f_013c9030() {
    char* p = (char*)g_16c7c14;
    *(void**)g_16c7c08 = vtbl_148b708;
    if (p) {
        void* q = *(void**)p;
        if (q) ((V2*)q)->b();
        cdecl_free(p);
    }
    g_16c7c14 = 0;
}

// @ 0x013C9140
void f_013c9140() {
    char* p = g_16c7f30;
    for (int i = 9; i >= 0; i--) {
        void* q = *(void**)(p - 0x1c);
        p -= 0x20;
        if (q) ((VBig*)q)->v48();
        void* r = *(void**)p;
        if (r) ((V3*)r)->c();
    }
}

// @ 0x013C9400
void f_013c9400() {
    int d = g_15ad7d4 - g_15ad7cc;
    if (((d & ~1) > 2) && g_15ad7cc && g_15ad7cc != g_15ad7dc) cdecl_free((void*)g_15ad7cc);
}

// @ 0x013C9910
void f_013c9910() {
    char* e = (char*)g_16c89c8;
    for (char* p = (char*)g_16c89c4; p < e; p += 0x44)
        ((Method*)(p + 4))->M();
    DBGFREE(g_16c89c4);
}

// @ 0x013C9950
void f_013c9950() {
    if (g_16c8b48) cdecl_shutdown_shared();
}

// @ 0x013C9C30
void f_013c9c30() {
    if (g_16c9f54) {
        int* p = (int*)(g_16c9f54 + 8);
        int n = (*(volatile int*)p += -1);
        if (n < 1) *(volatile int*)p += 1;
    }
}

// @ 0x013C9C70
void f_013c9c70() {
    if (g_16c9f58) {
        int* p = (int*)(g_16c9f58 + 8);
        int n = (*(volatile int*)p += -1);
        if (n < 1) *(volatile int*)p += 1;
    }
}

// @ 0x013C9CB0
void f_013c9cb0() {
    if (g_16c9f5c) {
        int* p = (int*)(g_16c9f5c + 8);
        int n = (*(volatile int*)p += -1);
        if (n < 1) *(volatile int*)p += 1;
    }
}

// @ 0x013C9DD0
void f_013c9dd0() {
    char* p = g_16d6d70;
    for (int i = 0xf; i >= 0; i--) {
        p -= 4;
        void* q = *(void**)p;
        if (q) ((V2*)q)->b();
    }
}

// @ 0x013C9E00
void f_013c9e00() {
    char* p = g_16d6db0;
    for (int i = 0xf; i >= 0; i--) {
        p -= 4;
        void* q = *(void**)p;
        if (q) ((V2*)q)->b();
    }
}

// @ 0x013C9F40
void f_013c9f40() {
    VR* p = (VR*)g_16d714c;
    if (p && --p->count == 0) {
        p->count = 1;
        p->Rel(1);
    }
}

// @ 0x013C9F70
void f_013c9f70() {
    VR* p = (VR*)g_16d7150;
    if (p && --p->count == 0) {
        p->count = 1;
        p->Rel(1);
    }
}

// @ 0x013CA670
void f_013ca670() {
    if (g_15b7478) ((V2*)g_15b7478)->b();
    HTb* h = (HTb*)g_15b7458;
    h->DoFreeNodes(h->mBegin, (void*)h->mEnd);
    unsigned n = h->mEnd;
    *(unsigned*)((char*)h + 0xc) = 0;
    if (n > 1) cdecl_free(h->mBegin);
}

// @ 0x013CA6C0
void f_013ca6c0() {
    void* p = g_15b74a4;
    *(void**)g_15b749c = vtbl_149953c;
    if (p) ((V2*)p)->b();
    *(void**)g_15b749c = vtbl_1416f14;
}

// @ 0x013CA6F0
void f_013ca6f0() {
    void* p = g_15b7518;
    *(void**)g_15b7510 = vtbl_1499570;
    if (p) {
        g_15b7518 = 0;
        ((V2*)p)->b();
        void* q = g_15b7518;
        if (q) ((V2*)q)->b();
    }
    *(void**)g_15b7510 = vtbl_1416f14;
}

// @ 0x013CA7F0
void f_013ca7f0() {
    void* p = g_15b7650;
    *(void**)g_15b7648 = vtbl_14996d4;
    if (p) {
        g_15b7650 = 0;
        if (p) ((V2*)p)->b();
    }
    DBGFREE(g_15b7654);
    void* q = g_15b7650;
    if (q) ((V2*)q)->b();
    *(void**)g_15b7648 = vtbl_1416f14;
}

// @ 0x013CA8F0
void f_013ca8f0() {
    char* p = g_16df428;
    for (int i = 3; i >= 0; i--) {
        p -= 0x14;
        if (p[0x10] & 4) ((VA*)p)->Destruct(0);
    }
}

// @ 0x013CA920
void f_013ca920() {
    ((Method*)g_15b7b2c)->M();
    ((Method*)g_15b79b8)->M();
    ((Method*)g_15b7844)->M();
    *(void**)g_15b7840 = vtbl_13eb938;
}

// @ 0x013CAAB0
void f_013caab0() {
    DBGFREE(g_15b8508);
    int h = g_15b84f4;
    if (h) {
        g_15b84f4 = 0;
        RemoveHandler(h, g_15b84f8, g_15b84fc, g_15b8500, g_15b8504);
    }
    *(void**)g_15b84f0 = vtbl_13eb394;
}

// @ 0x013CAB50
void f_013cab50() {
    void* p = (void*)g_16e0d04;
    if (p) {
        g_16e0d04 = 0;
        ((V2*)p)->b();
        void* q = (void*)g_16e0d04;
        if (q) ((V2*)q)->b();
    }
}

// @ 0x013CB250
void f_013cb250() { TlsFree(g_16e4174); }
// --- equivalence checker address annotations
    void cdecl_free(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
