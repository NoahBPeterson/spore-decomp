// Slice s0065a070: SP::cSPUIAssetView::LoadLayout / Update plus two Sporepedia
// vector helpers.  UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Raw virtual-call helpers (vtable slot offsets in bytes, as in the original).
// ---------------------------------------------------------------------------
inline void  vc0(void* p, int o) { (*(void(__thiscall**)(void*))((char*)*(void**)p + o))(p); }
inline void  vc1(void* p, int o, int a) { (*(void(__thiscall**)(void*, int))((char*)*(void**)p + o))(p, a); }
inline void  vc2(void* p, int o, int a, int b) { (*(void(__thiscall**)(void*, int, int))((char*)*(void**)p + o))(p, a, b); }
inline void  vc1p(void* p, int o, void* a) { (*(void(__thiscall**)(void*, void*))((char*)*(void**)p + o))(p, a); }
inline void  vc1f(void* p, int o, float a) { (*(void(__thiscall**)(void*, float))((char*)*(void**)p + o))(p, a); }
inline void  vc2f(void* p, int o, float a, float b) { (*(void(__thiscall**)(void*, float, float))((char*)*(void**)p + o))(p, a, b); }
inline int   vci0(void* p, int o) { return (*(int(__thiscall**)(void*))((char*)*(void**)p + o))(p); }
inline int   vci1(void* p, int o, int a) { return (*(int(__thiscall**)(void*, int))((char*)*(void**)p + o))(p, a); }
inline void* vcp0(void* p, int o) { return (*(void*(__thiscall**)(void*))((char*)*(void**)p + o))(p); }
inline void* vcp2(void* p, int o, int a, int b) { return (*(void*(__thiscall**)(void*, int, int))((char*)*(void**)p + o))(p, a, b); }
inline void* vcp1(void* p, int o, int a) { return (*(void*(__thiscall**)(void*, int))((char*)*(void**)p + o))(p, a); }
inline float* vpf0(void* p, int o) { return (*(float*(__thiscall**)(void*))((char*)*(void**)p + o))(p); }

// AutoRefCount<IWindow>: AddRef slot 0, Release slot 4.
inline void AssignWin(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 0);
        *slot = p;
        if (old) vc0(old, 4);
    }
}
// AutoRefCount<cSPUILayout-like>: AddRef slot 4, Release slot 8.
inline void AssignLayout(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 4);
        *slot = p;
        if (old) vc0(old, 8);
    }
}

// ---------------------------------------------------------------------------
// External callees / globals (all relocations, only the ABI matters).
// ---------------------------------------------------------------------------
struct cSPUILayout {
    void* vf0;
    void* vf1;
    void* vf2;
    void* FindWindowByID(int id, int flag);
    void  Init(const void* key, int a, int id);
    void  Shutdown(int flag);
};

struct cPropertyList { char GetDescription(int key); };
extern cPropertyList* g_pAppProperties;                // 0x15fd918

extern "C" void* __cdecl SP_AssetBrowser();
extern "C" void* __cdecl EA_Audio_GetSystemAT();
extern "C" void  __cdecl SetGlobalProperty(int key, float v);
extern "C" unsigned __cdecl ColorRGBAToU32(const void* c);
extern "C" void  __cdecl FUN_008082f0(void* w, float a, float b);
extern "C" void  __cdecl FUN_00808190(void* w, float a, float b);
extern "C" void  __cdecl FUN_00808230(void* w, void* v);
extern "C" void* __cdecl FUN_00807880(const void* key, float a, float b, void* parent);
extern "C" char  __cdecl FUN_008050b0(void* w);
extern "C" int   __cdecl FUN_00552300(int a);
extern "C" int   __cdecl GetRecorderState();
extern "C" void  __cdecl cSPUISpace_KillSetiEffects(int state, int key);
extern "C" float __cdecl GetPropertyT_f(int obj, int key, float def);
extern "C" char  __cdecl GetTimeString(int a, int b);
extern "C" void* __cdecl EASTL_Alloc(uint32_t size, const char* name, int a, int b, const char* file, int line);
extern "C" void* __fastcall cConnectionDialog_ctor(void* self);

// __thiscall callees modelled as members of an empty helper class.
struct G {
    void FUN_00834930(int a);
    void FUN_006596b0();
    void FUN_00657ad0(int a);
    void FUN_00657e60();
    void FUN_00659ec0();
    unsigned long long Stopwatch_GetElapsed();
    void Stopwatch_Restart();
    void QualifyNameWithGroup();
};

extern int g_sporeMax;   // 0x15f9f40

// ---------------------------------------------------------------------------
// SP::cSPUIAssetView (retail layout; offsets confirmed against the disassembly).
// ---------------------------------------------------------------------------
struct cSPUIAssetView {
    char  b00[0xc];                    // 0x00
    float mTargetX;                    // 0x0c
    float mTargetY;                    // 0x10
    char  f14;                         // 0x14
    char  mFirstUpdate;                // 0x15
    char  mResponds;                   // 0x16
    char  f17;                         // 0x17
    void* mAnimator;                   // 0x18
    void* p1c;                         // 0x1c
    cSPUILayout* mLayout;              // 0x20
    void* mWinRoot;                    // 0x24
    void* mWinShine;                   // 0x28
    void* mWinSelection;               // 0x2c
    void* mWinThumbnail;               // 0x30
    void* mWinThumbnailBackdrop;       // 0x34
    void* mWinName;                    // 0x38
    void* mWinAuthor;                  // 0x3c
    void* mWinTimestamp;               // 0x40
    void* mWinLoading;                 // 0x44
    void* mWinPublished;               // 0x48
    void* mWinLocked;                  // 0x4c
    void* mWinGameplayContainer;       // 0x50
    void* mWinGameplayName;            // 0x54
    void* mWinIdentityColor;           // 0x58
    void* mWinRelationship;            // 0x5c
    void* mWinStatsContainer;          // 0x60
    void* mVerbCollection;             // 0x64
    void* mAssetData;                  // 0x68
    void* mP6c;                        // 0x6c
    void* mP70;                        // 0x70
    void* mP74;                        // 0x74
    void* mP78;                        // 0x78
    void* mP7c;                        // 0x7c
    void* mP80;                        // 0x80
    void* mP84;                        // 0x84
    void* mP88;                        // 0x88
    void* mP8c;                        // 0x8c
    void* mP90;                        // 0x90
    void* mP94;                        // 0x94
    char  b98[0x58];                   // 0x98..0xef
    char  fF0;                         // 0xf0
    char  fF1;                         // 0xf1
    char  fF2;                         // 0xf2
    char  fF3;                         // 0xf3
    char  fF4;                         // 0xf4
    char  fF5;                         // 0xf5
    char  fF6;                         // 0xf6
    char  fF7;                         // 0xf7
    float mDist;                       // 0xf8
    char  fFC;                         // 0xfc
    char  fFD;                         // 0xfd
    char  fFE;                         // 0xfe
    char  fFF;                         // 0xff
    void* mP100;                       // 0x100

    void LoadLayout();
    void Update(unsigned int dt, bool b);
    bool IsAnimTargetDifferent();
    void Hide();
    void Show();
    void SetFirstUpdate(int b);
};

// @ 0x0065a070
void cSPUIAssetView::LoadLayout() {
    if (fF5) return;

    AssignWin(&mWinShine, mLayout->FindWindowByID(0xf3c6dc19, 1));
    if (mWinShine) {
        unsigned u = ColorRGBAToU32((const void*)0x1526280);
        vc1(mWinShine, 0x5c, (int)u);
        FUN_008082f0(mWinShine, 0.0f, 0.0f);
        FUN_00808190(mWinShine, 1.0f, 1.0f);
    }
    if (mWinShine && mWinRoot && fFC) {
        float* r = vpf0(mWinRoot, 0x38);
        vc2f(mWinShine, 0x74, r[2] - r[0], r[3] - r[1]);
    }
    if (mWinShine) {
        if (f17) vc1p(mWinShine, 0x104, this);
        vc2(mWinShine, 0x7c, 2, f17);
        vc2(mWinShine, 0x7c, 0x10, f17 == 0);
        vc2(mWinShine, 0x7c, 0x1000, f17 == 0);
    }

    AssignWin(&mWinSelection, mLayout->FindWindowByID(0x674aa70, 1));
    if (mWinSelection) {
        uint32_t v[4] = {0, 0, 0, 0};
        vc1p(mWinSelection, 0x60, v);
    }

    AssignWin(&mWinThumbnail, mLayout->FindWindowByID(0x6650680, 1));
    AssignWin(&mWinThumbnailBackdrop, mLayout->FindWindowByID(0x548e69a6, 1));
    SetFirstUpdate(mFirstUpdate);
    AssignWin(&mWinAuthor, mLayout->FindWindowByID(0xf3c6d819, 1));
    AssignWin(&mWinTimestamp, mLayout->FindWindowByID(0x13d938db, 1));
    ((G*)this)->FUN_006596b0();

    AssignWin(&mWinLoading, mLayout->FindWindowByID(0x53d6fe29, 1));
    if (mWinLoading) {
        void* x = mP90;
        if (x) {
            const wchar_t* s;
            if (vci0(x, 0xc) == 0) s = (const wchar_t*)0x13ffd4c; // L"<Missing>"
            else s = (const wchar_t*)vcp0(x, 0xc);
            vc1p(mWinLoading, 0x80, (void*)s);
            vc2(mWinLoading, 0x7c, 1, 1);
        }
    }
    AssignWin(&mWinPublished, mLayout->FindWindowByID(0x53d6fe2a, 1));
    if (mWinPublished) {
        void* x = mP90;
        if (x) {
            const wchar_t* s;
            if (vci0(x, 0x10) == 0) s = (const wchar_t*)0x13ffd4c;
            else s = (const wchar_t*)vcp0(x, 0x10);
            vc1p(mWinPublished, 0x80, (void*)s);
        }
    }
    AssignWin(&mWinLocked, mLayout->FindWindowByID(0x5492085e, 1));
    if (mWinLocked) vc1p(mWinLocked, 0x80, (void*)0x13ec468);
    AssignWin(&mWinGameplayContainer, mLayout->FindWindowByID(0x65bd7c8, 1));
    ((G*)this)->FUN_00657ad0(0);

    if (mP90) {
        fF0 = (char)vci0(mP90, 0x74);
        fF1 = (char)vci0(mP90, 0x78);
        fF2 = (char)vci0(mP90, 0x6c);
        fF3 = (char)vci0(mP90, 0x60);
    }

    AssignWin(&mWinName, mLayout->FindWindowByID(0x643e520, 1));
    if (mWinName) {
        int v;
        if (fF2 == 0) v = 0;
        else v = fF6 ? 1 : 0;
        vc2(mWinName, 0x7c, 1, v);
    }

    AssignWin(&mWinRelationship, mLayout->FindWindowByID(0xb497717e, 1));
    AssignWin(&mWinStatsContainer, mLayout->FindWindowByID(0x67c6707, 1));

    uint32_t id = 0x56e3f98;
    if (mWinRelationship && mWinStatsContainer) {
        if (fF1 == 0) {
            vc2(mWinRelationship, 0x7c, 1, 1);
            vc2(mWinStatsContainer, 0x7c, 1, 0);
        }
        else if (fF3 == 0) {
            vc2(mWinRelationship, 0x7c, 1, 0);
            vc2(mWinStatsContainer, 0x7c, 1, 0);
        }
        else if (fF0 != 0) {
            vc2(mWinRelationship, 0x7c, 1, 1);
            vc2(mWinStatsContainer, 0x7c, 1, 0);
        }
        else {
            vc2(mWinRelationship, 0x7c, 1, 0);
            vc2(mWinStatsContainer, 0x7c, 1, 1);
            id = 0x681e037;
        }
    }
    AssignWin(&mWinIdentityColor, mLayout->FindWindowByID((int)id, 1));

    int uv = 0;
    if (mP90) uv = vci0(mP90, 0x70);
    if (mWinIdentityColor) vc2(mWinIdentityColor, 0x7c, 1, uv);

    AssignWin(&mVerbCollection, mLayout->FindWindowByID(0x65be2b8, 1));
    if (mVerbCollection) vc2(mVerbCollection, 0x7c, 1, 0);

    AssignWin(&mP78, mLayout->FindWindowByID(0xf45696c1, 1));
    if (mP78) {
        void* w = vcp2(mP78, 0xf0, 0x3ed7919, 1);
        AssignWin(&mP7c, w);
    }
    else {
        AssignWin(&mP7c, 0);
    }
    AssignWin(&mP80, mLayout->FindWindowByID(0x7c7f748, 1));
    if (mP80) {
        void* w = vcp2(mP80, 0xf0, 0x3ed7919, 1);
        AssignWin(&mP84, w);
    }
    else {
        AssignWin(&mP84, 0);
    }

    if (fFD) {
        bool direct;
        if (mP90 == 0) direct = true;
        else {
            int a = vci0(mP90, 0x40);
            if (FUN_00552300(a) == 1) direct = true;
            else if (vci0(mP90, 0x38) == 0x7fffffff) direct = true;
            else direct = false;
        }
        if (direct) {
            ((G*)this)->FUN_00659ec0();
        }
        else if (g_pAppProperties->GetDescription(0xb4daca6a) != 0) {
            ((G*)this)->FUN_00659ec0();
        }
    }

    if (mP90 == 0 || vci0(mP90, 0x34) == 0) {
        AssignWin(&mAssetData, mLayout->FindWindowByID(0x5dd6448, 1));
        if (mAssetData) vc2(mAssetData, 0x7c, 1, 0);
        fF5 = 1;
        return;
    }

    AssignWin(&mAssetData, mLayout->FindWindowByID(0x5dd6448, 1));
    if (mAssetData) {
        vc2(mAssetData, 0x7c, 1, 1);
        if (mWinLoading) vc2(mWinLoading, 0x7c, 1, 0);
    }
    AssignWin(&mP6c, mLayout->FindWindowByID(0x5dd6760, 1));
    if (mP6c) {
        void* w = vcp0(mP90, 0x30);
        if (w == 0) w = (void*)0x13ec468;
        vc1p(mP6c, 0x80, w);
    }
    AssignWin(&mP70, mLayout->FindWindowByID(0x5dd0da8, 1));
    if (mP70) {
        vc1(mP70, 0x5c, vci0(mP90, 0x34));
    }
    AssignWin(&mP74, mLayout->FindWindowByID(0x5dd2988, 1));
    if (mP74) vc2(mP74, 0x7c, 1, 0);
    ((G*)this)->FUN_00657e60();
    fF5 = 1;
}

// @ 0x0065a990
void cSPUIAssetView::Update(unsigned int dt, bool b) {
    if (mP100) {
        void* a = EA_Audio_GetSystemAT();
        bool keep = false;
        if (a) {
            if (vci1(a, 0x28, (int)mP100) != 0) keep = true;
        }
        if (!keep) {
            mP100 = 0;
            SetGlobalProperty(0x8dff6314, 0.0f);
        }
    }

    if (fF7) {
        if (!IsAnimTargetDifferent()) Hide();
    }

    if (mWinGameplayName == 0 && fF5 == 0 && b) {
        struct { uint32_t a, b, c; } key;
        key.a = 0x2692833b; key.b = 0x2f7d0004; key.c = 0x11c0bde;
        void* w = FUN_00807880(&key, 0.0f, 0.0f, mWinRoot);
        AssignWin(&mWinGameplayName, w);
        vc2(mWinGameplayName, 0x7c, 0x10, 1);
        vc1(mWinGameplayName, 0x5c, (int)0x88ffffff);
    }
    if (mWinGameplayName) {
        vc2f(mWinGameplayName, 0x64, mTargetX, mTargetY);
        unsigned long long el = ((G*)((char*)this + 0xa0))->Stopwatch_GetElapsed();
        float f = (float)(unsigned long long)el * 0.002f;
        float v[4];
        v[0] = 0.0f; v[1] = 0.0f; v[2] = 1.0f; v[3] = -f;
        FUN_00808230(mWinGameplayName, v);
    }

    if (mWinShine && !mResponds) {
        float* cur = vpf0(mWinShine, 0x34);
        float px = cur[0], py = cur[1];
        if (px == mTargetX && py == mTargetY) {
            mDist = 0.0f;
        }
        else {
            float dx = mTargetX - px;
            float dy = mTargetY - py;
            float dist = sqrtf(dx * dx + dy * dy) + 1.5258789e-05f;
            if (mDist == 0.0f) mDist = dist;
            float q = 1.0f - dist / mDist;

            float mult = 4.0f;
            float t2 = 1.0f;
            float t3 = 0.5f;
            void* ab = SP_AssetBrowser();
            if (ab) {
                void* o = *(void**)((char*)ab + 0x18);
                if (o) {
                    mult = GetPropertyT_f((int)o, 0x1c7d9d9d, 4.0f);
                    t2 = GetPropertyT_f((int)o, 0x551398b5, 1.0f);
                    t3 = GetPropertyT_f((int)o, 0x6f7f8ef5, 0.5f);
                }
            }
            float f = (float)dt * mult * 0.001f;
            float cl = 0.0f;
            if (cl < f) cl = f;
            if (cl > 1.0f) cl = 1.0f;
            float nx = (mTargetX - px) * cl + px;
            float ny = (mTargetY - py) * cl + py;
            float rx = nx - mTargetX;
            float ry = ny - mTargetY;
            float rlen = sqrtf(rx * rx + ry * ry);
            if (rlen < t2) { nx = mTargetX; ny = mTargetY; }
            if (FUN_008050b0(mWinShine) && b && fF4 && t3 > q && 1.0f >= t3) {
                cSPUISpace_KillSetiEffects(GetRecorderState(), 0x4e79d7d1);
            }
            vc2f(mWinShine, 0x64, nx, ny);
        }

        if (fF6 && mP94) {
            ((G*)mP94)->FUN_00834930(1);
        }
        if (mP88) {
            vc1(mP88, 0x1c, (int)dt);
        }
        unsigned long long el = ((G*)((char*)this + 0xb8))->Stopwatch_GetElapsed();
        if ((el >> 32) != 0 || (unsigned)el > 1000) {
            ((G*)((char*)this + 0xb8))->Stopwatch_Restart();
        }
        if (mWinLocked) {
            unsigned long long e2 = ((G*)((char*)this + 0xb8))->Stopwatch_GetElapsed();
            if (e2 == 0) {
                if (vci0(mP90, 0x5c) != 0) {
                    int arr[3];
                    arr[0] = 0x1667bac; arr[1] = 0x1667bac; arr[2] = 0x1667bae;
                    int r = vci1(mP90, 0x28, (int)arr);
                    if (GetTimeString(r, 0) != 0) {
                        vc1(mWinLocked, 0x80, arr[0]);
                    }
                    ((G*)((char*)this + 0xb8))->Stopwatch_Restart();
                    ((G*)this)->FUN_00657ad0(arr[0] != arr[1]);
                    ((G*)arr)->QualifyNameWithGroup();
                }
                else {
                    ((G*)this)->FUN_00657ad0(0);
                }
            }
        }
        if (g_pAppProperties->GetDescription(0xb4daca6a) != 0) {
            ((G*)this)->FUN_00659ec0();
        }
    }
    mResponds = 0;
}

// @ 0x0065aeb0
struct SpVec {
    void* begin;
    void* end;
    void* cap;
    void  erase(void* first, void* last);
    void  resize(int n);
};
extern SpVec g_sporeVec;  // 0x15fa018

void SporepediaVecClear() {
    g_sporeVec.erase(g_sporeVec.begin, g_sporeVec.end);
}

// @ 0x0065aed0
void SporepediaVecSetSize(int n) {
    int cur = (int)(((char*)g_sporeVec.end - (char*)g_sporeVec.begin) >> 2);
    if (n != cur && g_sporeMax <= n) {
        g_sporeVec.resize(n);
        for (int i = cur; i < n; ++i) {
            void* p = EASTL_Alloc(0x18, "Sporepedia", 0, 0, 0, 0);
            void* obj = p ? cConnectionDialog_ctor(p) : 0;
            void** slot = (void**)((char*)g_sporeVec.begin + i * 4);
            AssignLayout(slot, obj);
            void* el = *(void**)((char*)g_sporeVec.begin + i * 4);
            ((cSPUILayout*)el)->Init((const void*)0x1526560, 0, 0x5b598fa);
        }
    }
}
