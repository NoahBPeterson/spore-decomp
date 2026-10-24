// Slice s0066ee50: SP::cSPUILargeAssetView and feed-item helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidP)(void*, void*);
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

typedef void* (__thiscall *FnPtrI)(void*, uint32_t);
typedef unsigned char (__thiscall *FnU8V)(void*);
typedef float (__thiscall *FnFloatV)(void*);
typedef bool (__thiscall *FnBoolI)(void*, uint32_t);

void FUN_0066bf70();      // 0x0066bf70
void FUN_0066c9e0();      // 0x0066c9e0
void FUN_0066d280();      // 0x0066d280
void FUN_010829f0();      // 0x010829f0
float FUN_00a049f0();     // 0x00a049f0
bool FUN_006a25a0();      // 0x006a25a0
void* __cdecl SP_AppSystem();  // 0x0067dd00
extern void* g_15fd918;   // 0x015fd918

struct LargeAssetView {
    char pad00[0x24];
    void* mWinBakingArea;         // +0x24
    char pad28[0x14];
    void* mWinDescription;        // +0x3c
    char pad40[0x8];
    void* mWinBakingForeground;   // +0x48
    char pad4c[0x10];
    void* mWin5c;                 // +0x5c
    char pad60[0x4];
    void* mExpansionPackBrowser;  // +0x64
    char pad68[0x8];
    void* mAssetVerbs;            // +0x70
    void* mAssetData;             // +0x74
    char pad78[0x8];
    void* mRollover;              // +0x80
    char pad84[0x24];
    uint32_t mFlagsA8;            // +0xa8 (mIsLoaded/mIsPlayable/field_aa/mHasResource)
    uint8_t mIsEditable;          // +0xac
    char padAD[3];

    void FUN_0066ee50(void* arg);
};

// @ 0x0066ee50
void LargeAssetView::FUN_0066ee50(void* arg) {
    if (mWin5c)
        ((FnVoidP)VT(mWin5c)[0x1c / 4])(mWin5c, arg);
    if (mExpansionPackBrowser)
        ((FnVoidP)FUN_010829f0)(mExpansionPackBrowser, arg);
    if (mRollover)
        ((FnVoidP)VT(mRollover)[0x1c / 4])(mRollover, arg);

    if (mWinBakingArea && mWinDescription &&
        (((FnU8V)VT(mWinDescription)[0x28 / 4])(mWinDescription) & 1)) {
        float v[4];
        v[3] = SPUIHelpers_GetElapsedSeconds() * gF13ef61c;
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = gF1485720;
        FUN_00808230(mWinBakingArea, v);
        if (!mIsEditable) {
            mIsEditable = 1;
            void* app = SP_AppSystem();
            ((FnVoidI)VT(app)[0x40 / 4])(app, 1);
        }
    } else if (mIsEditable) {
        mIsEditable = 0;
        void* app = SP_AppSystem();
        ((FnVoidI)VT(app)[0x40 / 4])(app, 0);
    }

    if (mWinBakingForeground &&
        (((FnU8V)VT(mWinBakingForeground)[0x28 / 4])(mWinBakingForeground) & 1)) {
        float v[4];
        v[3] = SPUIHelpers_GetElapsedSeconds() * gF13ef61c;
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = gF1485720;
        FUN_00808230(mWinBakingForeground, v);
    }

    if (mAssetData)
        ((FnVoid)FUN_0066bf70)(mAssetData);

    if (mAssetVerbs) {
        void* r = ((FnPtrV)VT(mAssetVerbs)[0x3c / 4])(mAssetVerbs);
        if (r) {
            void* av = mAssetVerbs;
            uint32_t flags = mFlagsA8;
            void* r2 = ((FnPtrI)VT(av)[0x3c / 4])(av, flags);
            float f = ((FnFloatV)FUN_00a049f0)(r2);
            if (f >= 1.0f)
                ((FnVoid)FUN_0066c9e0)((char*)this - 0xc);
        }
    }

    if (((FnBoolI)FUN_006a25a0)(g_15fd918, 0xb4daca6a))
        ((FnVoid)FUN_0066d280)((char*)this - 0xc);
}

// -----------------------------------------------------------------------------
// @ 0x0066efe0 / 0x0066f090 / 0x0066f200 / 0x0066f5c0 / 0x0066f8e0
// (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void __fastcall FUN_0066efe0(void* self, void* a) { (void)self; (void)a; }
void __fastcall FUN_0066f090(void* self) { (void)self; }
void __fastcall FUN_0066f200(void* self) { (void)self; }
void __fastcall FUN_0066f5c0(void* self) { (void)self; }
void __fastcall FUN_0066f8e0(void* self) { (void)self; }
