// Slice s0066ee50: SP::cSPUILargeAssetView and feed-item helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef int   (__thiscall *FnIntV)(void*);
typedef int   (__thiscall *FnIntIII)(void*, int, int);
typedef char  (__thiscall *FnChrIIP)(void*, int, int, void*);
typedef char  (__thiscall *FnChrIII)(void*, int, int, int);
typedef char  (__thiscall *FnChr6)(void*, void*, int, int, int, int, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl FUN_0067cb30();                        // 0x0067cb30
void* __cdecl EA_GetManager();                       // 0x0067dcd0
float __cdecl SPUIHelpers_GetElapsedSeconds();       // 0x00805080
void  __cdecl FUN_00808230(void* w, float* v);       // 0x00808230
extern float gF13ef61c;   // 0x013ef61c
extern float gF1485720;   // 0x01485720

struct Dir { unsigned char GetLocalKey(int a, int b, void* key); unsigned char FUN_0054e740(int a, int b); };

// -----------------------------------------------------------------------------
// @ 0x0066f130
// -----------------------------------------------------------------------------
bool __cdecl FUN_0066f130(void* p) {
    if (p) ((FnVoidII)VT(p)[31])(p, 0x1000, 0);
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x0066f1e0
// -----------------------------------------------------------------------------
bool __fastcall FUN_0066f1e0(void* self) {
    int v = *(int*)((char*)self + 0x68);
    if (v != 0 && v != 8) return true;
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x0066f980
// -----------------------------------------------------------------------------
struct LargeView {
    void FUN_0066f980(void* arg);
};

void LargeView::FUN_0066f980(void* arg) {
    (void)arg;
    void** p = (void**)((char*)this + 0xa8);
    int n = 2;
    do {
        void* w = *p;
        if (w) {
            if (((FnIntV)VT(w)[10])(w) & 1) {
                float t = SPUIHelpers_GetElapsedSeconds() * gF13ef61c;
                float v[4];
                v[0] = 0.0f;
                v[1] = 0.0f;
                v[2] = gF1485720;
                v[3] = t;
                FUN_00808230(w, v);
            }
        }
        ++p;
    } while (--n);
}

// -----------------------------------------------------------------------------
// @ 0x0066f150
// -----------------------------------------------------------------------------
bool __cdecl FUN_0066f150(int a, int b) {
    unsigned char key[12];
    *(uint32_t*)&key[0] = 0;
    *(uint32_t*)&key[4] = 0;
    *(uint32_t*)&key[8] = 0;
    void* r = FUN_0067cb30();
    void* dir = *(void**)((char*)r + 0x58);
    bool got = ((Dir*)dir)->GetLocalKey(a, b, key) != 0;
    bool ok = false;
    if (got) {
        void* r2 = FUN_0067cb30();
        void* dir2 = *(void**)((char*)r2 + 0x58);
        if (((Dir*)dir2)->FUN_0054e740(a, b)) {
            ok = true;
        } else {
            void* mgr = EA_GetManager();
            if (((FnChr6)VT(mgr)[3])(mgr, key, 0, 0, 0, 0, 0)) ok = true;
        }
    }
    if (ok) return true;
    return false;
}

// -----------------------------------------------------------------------------
// @ 0x0066ee50 / 0x0066efe0 / 0x0066f090 / 0x0066f200 / 0x0066f5c0 / 0x0066f8e0
// (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void __fastcall FUN_0066ee50(void* self) { (void)self; }
void __fastcall FUN_0066efe0(void* self, void* a) { (void)self; (void)a; }
void __fastcall FUN_0066f090(void* self) { (void)self; }
void __fastcall FUN_0066f200(void* self) { (void)self; }
void __fastcall FUN_0066f5c0(void* self) { (void)self; }
void __fastcall FUN_0066f8e0(void* self) { (void)self; }
