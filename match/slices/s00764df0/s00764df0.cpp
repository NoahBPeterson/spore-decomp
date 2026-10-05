// slice s00764df0
// SP::cGraphicsResourceFactory raster/game-mesh/arena serialization tail.
// flags: /O2 /MD /Gy /EHsc /TP /GS-
#include <intrin.h>
#include "types.h"

// ---------------------------------------------------------------------------
// @ 0x007650d0 / 0x00765150  loader dispatch wrappers
struct Ctx764df0 { char CreateRaster(void* a, void* b, void* c); };   // 0x764df0 thiscall, 3 args
struct Ctx764a50 { char ReadArena(void* a, void* b, void* c); };      // 0x764a50 thiscall, 3 args

struct Loader29 {
    char pad0[0xc];
    void* pC;                  // +0xc
    char pad10[4];
    void* p14;                 // +0x14
    char pad18[0x10];
    void* p28;                 // +0x28
    char p2c[0x308];           // +0x2c
    unsigned char b334;
    void WrapDf0(int);
    void WrapA50(int);
};

// @ 0x00765150
void Loader29::WrapDf0(int) {
    Ctx764df0* ctx = (Ctx764df0*)pC;
    char ok = ctx->CreateRaster(p2c, p28, p14);
    if (ok)
        b334 = 1;
}

// @ 0x007650d0
void Loader29::WrapA50(int) {
    ((Ctx764a50*)pC)->ReadArena(p2c, p28, p14);
}

// ===========================================================================
// @ 0x00765980  eastl hashtable bucket-array grow
extern "C" {
void* __cdecl EA_New(uint32_t size, const char* f, int a, int b, const char* g, int line); // 0x0f473a0
void  __cdecl EA_Delete(void* p);                                                          // 0x0f47380
void  __cdecl DoFreeNodes(void* b, void* e, void* n);                                      // 0x04554f0
}
extern const char g_allocFile[];   // 0x13ebb38
struct Node8 { int x, y; };
struct HVec { Node8* b; Node8* e; Node8* cap; void grow(unsigned n); };
void HVec::grow(unsigned n) {
    if (n > (unsigned)(cap - b)) {
        Node8* newp = n ? (Node8*)EA_New(n * 8, "Graphics", 0, 0, g_allocFile, 0xd1) : 0;
        DoFreeNodes(b, e, newp);
        if (b && *(int*)((char*)b - 4) != 0)
            EA_Delete(b);
        Node8* oldb = b;
        size_t count = e - oldb;
        b = newp;
        e = newp + count;
        cap = newp + n;
    }
}

// ===========================================================================
// @ 0x00765ac0  destructor: owned-pointer vector at +0x78 and vector at +0x20
struct Vec { void** b; void** e; void** cap; int alloc; void** inlinebuf; };
struct D765ac0 {
    char pad[0x20];
    Vec v20;                 // +0x20
    char padX[0x78 - 0x34];
    Vec v78;                 // +0x78
    ~D765ac0();
};
D765ac0::~D765ac0() {
    int n = (int)(v78.e - v78.b);
    for (int i = 0; i < n; i++) {
        if (v78.b[i])
            EA_Delete(v78.b[i]);
    }
    if (v78.b && v78.b != v78.inlinebuf)
        EA_Delete(v78.b);
    if (v20.b && v20.b != v20.inlinebuf)
        EA_Delete(v20.b);
}

// ===========================================================================
// @ 0x00765f10  ctor (partial: EH frame / member model not reproduced)
struct IUnknown32 { virtual void u0(); virtual void u1(); virtual void u2(); };
struct AtomicInt { int v; int operator=(int x) { return _InterlockedExchange((volatile long*)&v, x); } };
struct Resource : IUnknown32 {
    AtomicInt mRefCount; int k0, k1, k2;
    Resource() { mRefCount = 0; k0 = 0; k1 = 0; k2 = 0; }
};
struct cResourceBase : Resource { int* cb; cResourceBase() { cb = 0; } };
struct D765f10 : cResourceBase {
    int f18;
    void* f1c;
    D765f10(void* arg);
};
D765f10::D765f10(void* arg) {
    f18 = 0;
    f1c = arg;
    if (arg)
        ((IUnknown32*)arg)->u0();
    f18 = 0;
}

// ===========================================================================
// @ 0x00765580  ~cGraphicsResourceFactory (refcounted cJobLock member at +8)
struct RefCountedBase { virtual void dtor(int); };
struct AutoRcT {
    RefCountedBase* p;
    ~AutoRcT() {
        RefCountedBase* q = p;
        if (q) {
            int n = _InterlockedExchangeAdd((volatile long*)((char*)q + 4), -1) - 1;
            if (n == 0) {
                _InterlockedExchange((volatile long*)((char*)q + 4), 1);
                if (q)
                    q->dtor(1);
            }
        }
    }
};
struct FactoryBase {
    virtual void f0();
    virtual void f1();
    int f4;
    ~FactoryBase() {}
};
struct D765580 : FactoryBase {
    AutoRcT m8;    // +8
    ~D765580();
};
D765580::~D765580() {}

// ===========================================================================
// partial stubs
void __cdecl FUN_764df0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }   // 00764df0
int  __stdcall FUN_764f60(void* a, void* b) { (void)a; (void)b; return 1; }          // 00764f60
void __cdecl FUN_7650f0(void* a, void* b) { (void)a; (void)b; }                     // 007650f0
void __cdecl FUN_765230(void* a, int n, void* c) { (void)a; (void)n; (void)c; }     // 00765230
int  __cdecl FUN_7652c0(void* p) { (void)p; return 0; }                             // 007652c0
void __cdecl FUN_7654f0(void* p) { (void)p; }                                       // 007654f0
char __cdecl FUN_7655f0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; return 0; } // 007655f0
int  __stdcall FUN_7656c0(void* a, void* b) { (void)a; (void)b; return 1; }         // 007656c0
int  __cdecl FUN_765b30(void* p) { (void)p; return 0; }                             // 00765b30
int  __cdecl FUN_765d30(void* p) { (void)p; return 0; }                             // 00765d30
