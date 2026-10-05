// slice s00763cb0
// SP::cGraphicsResourceFactory arena/raster loading module.
// flags: /O2 /MD /Gy /EHsc /TP /GS-
#include <intrin.h>
#include "types.h"

// ---------------------------------------------------------------------------
// externs (relocation targets)
// ---------------------------------------------------------------------------
extern "C" {
void* __cdecl AddRegistrationCallback(int id, void* cb);   // 0x06adfe0
void* __cdecl ArenaTypeRegGetType(int t);                   // 0x011e22c0
void* __cdecl GetManager();                                 // 0x067dcd0
int   __cdecl FUN_011f06c0(void* a, void* b);               // 0x011f06c0
}
extern void* g_sAppProperties;                              // 0x015fd918
extern char  kRasterRecordTypes[];                          // 0x0140e000

// 0x764320 thiscall (3 stack args): call kept out of line so Wrap670 keeps its call
struct RasterCtx { char Create(void* a, void* b, void* c); };

// 0x763620 / 0x763770 thiscall (3 stack args)
struct Ctx63620 { char Load(void* a, void* b, void* c); };
struct Ctx63770 { char Fill(void* a, void* b, void* c); };

// ---------------------------------------------------------------------------
namespace SP {
class cGraphicsResourceFactory {
public:
    bool Init();    // 007641c0
};
}

// ===========================================================================
// @ 0x00763df0
int __cdecl FUN_763df0(void* a, void* b) {
    void* p = g_sAppProperties;
    int c = *(int*)((char*)p + 0x3c);
    if (*(int*)((char*)c + 0x130) != 0) {
        int n = *(int*)((char*)b + 0x134);
        int i = 0;
        if (n > 0) {
            int* arr = (int*)((char*)b + 0x138);
            do {
                if (a == (void*)*arr) {
                    *(int*)((char*)a + 8) = 0;
                    return 1;
                }
                i++;
                arr++;
            } while (i < n);
        }
    }
    return FUN_011f06c0(a, b);
}

// ===========================================================================
// @ 0x007641c0
bool SP::cGraphicsResourceFactory::Init() {
    AddRegistrationCallback(0x2f4e681b, (void*)0x7632f0);
    void* t = ArenaTypeRegGetType(0x20003);
    *(void**)((char*)t + 0xc) = (void*)0x763df0;
    t = ArenaTypeRegGetType(0x2000b);
    *(void**)((char*)t + 0xc) = (void*)0x763cb0;
    void* m = GetManager();
    ((void(__thiscall*)(void*, int, void*, int))(*(void***)m)[0x24 / 4])(m, 0x2f4e681c, kRasterRecordTypes, 3);
    return true;
}

// ===========================================================================
// @ 0x007642c0 / 0x007643d0  refcounted subobject destructors
struct RefObj { virtual void s0(); virtual void s1(); virtual void s2(); };
struct AutoRef { RefObj* p; ~AutoRef() { if (p) p->s1(); } };
struct D7642c0 {
    char pad4[4];
    AutoRef a;                 // +4
    AutoRef b;                 // +8
    ~D7642c0();
};
D7642c0::~D7642c0() {}
struct D7643d0 {
    AutoRef a;                 // +0
    AutoRef b;                 // +4
    ~D7643d0();
};
D7643d0::~D7643d0() {}

// ===========================================================================
// @ 0x00764670 / 0x007646a0 / 0x007646c0
struct Loader {
    char pad0[0xc];
    void* pC;                  // +0xc
    char pad10[4];
    void* p14;                 // +0x14
    char pad18[0x10];
    void* p28;                 // +0x28
    char p2c[0x308];           // +0x2c
    unsigned char b334;        // +0x334
    void Wrap670(int);
    void Wrap6a0(int);
    void Wrap6c0(int);
};
void Loader::Wrap670(int) {
    RasterCtx* ctx = (RasterCtx*)pC;
    char ok = ctx->Create(p2c, p28, p14);
    if (ok)
        b334 = 1;
}
void Loader::Wrap6a0(int) {
    ((Ctx63620*)pC)->Load(p2c, p28, p14);
}
void Loader::Wrap6c0(int) {
    if (((Ctx63770*)pC)->Fill(p2c, p28, p14))
        b334 = 1;
}

// ===========================================================================
// partial stubs -----------------------------------------------------------------
void __cdecl FUN_763cb0(void* a, void* b) { (void)a; (void)b; }           // 00763cb0
void __cdecl FUN_763e50(void* d, const void* s) { (void)d; (void)s; }     // 00763e50
int  __cdecl FUN_763fd0(void* arena) { (void)arena; return 0; }          // 00763fd0
void __cdecl FUN_7640c0(void* p) { (void)p; }                            // 007640c0
void __cdecl FUN_764220(void* p) { (void)p; }                            // 00764220
int  __cdecl FUN_764320(void* ctx, void* a, void* b, void* c) { (void)ctx; (void)a; (void)b; (void)c; return 0; } // 00764320
int  __stdcall FUN_764430(int* a, int b) { (void)a; (void)b; return 1; } // 00764430
int  __stdcall FUN_764580(void* a) { (void)a; return 0; }                // 00764580
void __cdecl FUN_764760(void* p, int v) { (void)p; (void)v; }            // 00764760
int  __cdecl FUN_764820(void* p) { (void)p; return 0; }                  // 00764820
int  __cdecl FUN_7649f0(void* p, int a) { (void)p; (void)a; return 0; }  // 007649f0
int  __cdecl FUN_764a50(void* p, void* a, void* b) { (void)p; (void)a; (void)b; return 0; } // 00764a50
int  __cdecl FUN_764ce0(void* p, void* a, void* b) { (void)p; (void)a; (void)b; return 0; } // 00764ce0
