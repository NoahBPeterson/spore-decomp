// slice s00656310: SP::cSPUIAssetVerbs / SP::cSPUIAssetView Sporepedia UI helpers.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// Raw virtual-call helpers (vtable slots given in bytes, matching the original).
// ---------------------------------------------------------------------------
inline void  vc0(void* p, int off) { ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void  vc1(void* p, int off, int a) { ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline void  vc2(void* p, int off, int a, int b) { ((void(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline void  vc3(void* p, int off, int a, int b, int c) { ((void(__thiscall*)(void*, int, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b, c); }
inline int   vcr0(void* p, int off) { return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline int   vcr1(void* p, int off, int a) { return ((int(__thiscall*)(void*, int))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline void* vcp0(void* p, int off) { return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void* vcp2(void* p, int off, int a, int b) { return ((void*(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline void* vcp1(void* p, int off, int a) { return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline void  vc1p(void* p, int off, void* a) { ((void(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline float* vcfp(void* p, int off) { return ((float*(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void  vc2f(void* p, int off, float a, float b) { ((void(__thiscall*)(void*, float, float))(*(void**)((char*)*(void**)p + off)))(p, a, b); }

// AutoRefCount<T> assignment semantics. Windows: AddRef slot0 / Release slot4.
inline void AssignWin(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 0);
        *slot = p;
        if (old) vc0(old, 4);
    }
}
// cSPUILayout: AddRef slot4 / Release slot8.
inline void AssignLayout(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 4);
        *slot = p;
        if (old) vc0(old, 8);
    }
}

// ---------------------------------------------------------------------------
// External callees (declarations only; addresses are masked relocations).
// ---------------------------------------------------------------------------
struct cSPUILayout {
    void* vf0;  // +0
    void* vf1;  // +4
    void* vf2;  // +8
    void* FindWindowByID(int id, int flag);
    void  Shutdown(int flag);
    void  SetParentWin(void* parent, int a, int id);
    void  SetReloadCallback(void* fn, void* self);
    void  Init(void* key, int a, int id);
};
extern "C" void* __fastcall cSPUILayout_Ctor(void* self);
extern "C" void* __cdecl EA_operator_new(int size, const char* name, int a, int b, int c, int d);
extern "C" void __cdecl RemoveHandler5(void* a, void* b, void* c, void* d, void* e);
extern "C" void __cdecl SPUIHelpers_UpdateMouseFocus(int v);
extern "C" void __cdecl SPUIHelpers_SetWindowAreaToParent(void* w);
extern "C" void* __cdecl SP_AssetBrowser();
extern "C" void* __cdecl SP_ConfigManager();
extern "C" void* __cdecl SP_AuthManager();
extern "C" void* __cdecl SP_PropertyManager();
extern "C" void* __cdecl SP_MessageServer();
extern "C" bool __fastcall FUN_006418e0(void* p);
extern "C" void* __fastcall FUN_00656240(void* a, void* b);
extern "C" void FUN_00654e20();
extern "C" void  __cdecl FUN_004e5410(int, int, int, void*, void*, float);

// Animator helper: __thiscall at 0x7f62c0 (HasAnimation(IWindow*, int)).
struct cSPUIAnimator {
    bool HasAnimation(void* win, int id);
};

// ---------------------------------------------------------------------------
// SP::cSPUIAssetVerbs  (retail layout; offsets confirmed against the disassembly)
// ---------------------------------------------------------------------------
struct cSPUIAssetVerbs {
    void* vf0;         // 0x00
    void* vf1;         // 0x04
    void* vf2;         // 0x08
    int   mf0c;        // 0x0c
    bool  mIsVisible;  // 0x10
    void* mLayout;     // 0x14
    void* mWinParent;  // 0x18
    void* mWinRoot;    // 0x1c
    void* mWin3;       // 0x20
    void* mWin4;       // 0x24
    void* mWin5;       // 0x28
    void* mWin6;       // 0x2c
    void* mWin7;       // 0x30
    void* mWin8;       // 0x34
    int   mAutoh[5];   // 0x38..0x4b  (AutoHandler)
    float mVec[4];     // 0x4c..0x5b

    void Shutdown();
    bool IsVerb(int idx);
    void Update(void* p);
    void UpdatePos(void* p);
    void SetVerbButtonEnabled(unsigned int idx);
    void Init(void* parent);
};

// Distinct dummy symbols so the vtable stores are real relocations (masked by cmpobj).
extern int gVtA, gVtB, gVtC, gVtD, gVtE, gVtF, gVtG, gVtH, gVtI;

// @ 0x00656b00  cSPUIAssetVerbs constructor
cSPUIAssetVerbs* __fastcall cSPUIAssetVerbs_ctor(cSPUIAssetVerbs* self) {
    *(void* volatile*)&self->vf1 = &gVtA;
    *(void* volatile*)&self->vf2 = &gVtB;
    _ReadWriteBarrier();
    self->mf0c = 0;
    self->vf0 = &gVtC;
    self->vf1 = &gVtD;
    self->vf2 = &gVtE;
    self->mIsVisible = false;
    self->mLayout = 0;
    self->mWinParent = 0;
    self->mWinRoot = 0;
    self->mWin3 = 0;
    self->mWin4 = 0;
    self->mWin5 = 0;
    self->mWin6 = 0;
    self->mWin7 = 0;
    self->mWin8 = 0;
    self->mAutoh[0] = 0;
    self->mAutoh[1] = 0;
    self->mAutoh[2] = 0;
    self->mAutoh[3] = 0;
    self->mAutoh[4] = 0;
    return self;
}

// @ 0x00656410  cSPUIAssetVerbs destructor
void __fastcall cSPUIAssetVerbs_dtor(cSPUIAssetVerbs* self) {
    self->vf0 = &gVtC;
    self->vf1 = &gVtD;
    self->vf2 = &gVtE;
    _ReadWriteBarrier();
    int h0 = self->mAutoh[0];
    if (h0) {
        self->mAutoh[0] = 0;
        RemoveHandler5((void*)h0, (void*)self->mAutoh[1], (void*)self->mAutoh[2], (void*)self->mAutoh[3], (void*)self->mAutoh[4]);
    }
    if (self->mWin8) vc0(self->mWin8, 4);
    if (self->mWin7) vc0(self->mWin7, 4);
    if (self->mWin6) vc0(self->mWin6, 4);
    if (self->mWin5) vc0(self->mWin5, 4);
    if (self->mWin4) vc0(self->mWin4, 4);
    if (self->mWin3) vc0(self->mWin3, 4);
    if (self->mWinRoot) vc0(self->mWinRoot, 4);
    if (self->mWinParent) vc0(self->mWinParent, 4);
    if (self->mLayout) vc0(self->mLayout, 8);
    self->vf2 = &gVtF;
    self->vf1 = &gVtG;
    self->vf0 = &gVtH;
}

// @ 0x006566f0  cSPUIAssetVerbs::Shutdown
void cSPUIAssetVerbs::Shutdown() {
    if (mLayout) {
        ((cSPUILayout*)mLayout)->Shutdown(1);
        AssignLayout(&mLayout, 0);
    }
    int h0 = mAutoh[0];
    if (h0) {
        mAutoh[0] = 0;
        RemoveHandler5((void*)h0, (void*)mAutoh[1], (void*)mAutoh[2], (void*)mAutoh[3], (void*)mAutoh[4]);
    }
}

// @ 0x00656740
bool cSPUIAssetVerbs::IsVerb(int idx) {
    void* w = ((cSPUILayout*)mLayout)->FindWindowByID(((int*)0x13ffc00)[idx], 1);
    if (w) return (vcr0(w, 0x28) & 1);
    return false;
}

// @ 0x00656770
void cSPUIAssetVerbs::Update(void* p) {
    int* ids1 = (int*)0x13ffc00;
    int* ids2 = (int*)0x13ffc18;
    for (int i = 0; i < 6; ++i) {
        void* w1 = ((cSPUILayout*)mLayout)->FindWindowByID(ids1[i], 1);
        void* w2 = ((cSPUILayout*)mLayout)->FindWindowByID(ids2[i], 1);
        if (w1) vc2(w1, 0x7c, 1, 0);
        if (w2) {
            if (i == 5) {
                if (*(int*)p == 0xad0e52) vc2(w2, 0x7c, 1, 1);
                else vc2(w2, 0x7c, 1, 0);
            }
            else if (i == 3) {
                if (*(char*)((char*)p + 0xc)) vc2(w2, 0x7c, 1, 1);
                else vc2(w2, 0x7c, 1, 0);
            }
            else {
                vc2(w2, 0x7c, 1, 1);
            }
            vc2(w2, 0x7c, 0x10, 0);
        }
    }
    if (mWin4) vc2(mWin4, 0x7c, 1, 0);
    if (mWin6) vc2(mWin6, 0x7c, 1, 0);
}

// @ 0x00656510
void cSPUIAssetVerbs::UpdatePos(void* p) {
    float w = 40.0f;
    float x = 0.0f;
    float y = 0.0f;
    if (mWin3) {
        float* r = vcfp(mWin3, 0x38);
        w = r[2] - r[0];
        x = vcfp(mWin3, 0x38)[0];
        y = vcfp(mWin3, 0x38)[1];
    }
    int n = 0;
    int* ids1 = (int*)0x13ffc00;
    int* ids2 = (int*)0x13ffc18;
    for (int i = 0; i < 6; ++i) {
        void* w1 = ((cSPUILayout*)mLayout)->FindWindowByID(ids1[i], 1);
        void* w2 = ((cSPUILayout*)mLayout)->FindWindowByID(ids2[i], 1);
        if (w1) vc2f(w1, 0x70, x, y);
        if (w2) vc2f(w2, 0x70, x, y);
        bool add;
        if (i == 5) add = (*(int*)p == 0xad0e52);
        else if (i == 3) add = (*(char*)((char*)p + 0xc) != 0);
        else add = true;
        if (add) { x += w; ++n; }
    }
    if (mWinRoot && mWin3) {
        float v[4];
        v[0] = mVec[0];
        v[1] = mVec[1];
        v[2] = mVec[2];
        v[3] = mVec[3];
        float r = vcfp(mWin3, 0x38)[2] - vcfp(mWin3, 0x38)[0];
        v[0] = v[0] - r * (float)(n - 5);
        vc1p(mWinRoot, 0x6c, v);
    }
    if (mWin6 && mWin5) {
        float px = vcfp(mWin5, 0x38)[0];
        float py = vcfp(mWin5, 0x38)[1];
        vc2f(mWin6, 0x70, px, py);
    }
}

// @ 0x00656830  cSPUIAssetVerbs::SetVerbButtonEnabled
void cSPUIAssetVerbs::SetVerbButtonEnabled(unsigned int idx) {
    if (idx > 5) return;
    int* ids1 = (int*)0x13ffc00;
    int* ids2 = (int*)0x13ffc18;
    void* w1 = ((cSPUILayout*)mLayout)->FindWindowByID(ids1[idx], 1);
    void* w2 = ((cSPUILayout*)mLayout)->FindWindowByID(ids2[idx], 1);
    if (w1) vc2(w1, 0x7c, 1, 1);
    if (w2) vc2(w2, 0x7c, 0x10, 1);
}

// @ 0x00656890  cSPUIAssetVerbs::ReloadCallback (cdecl: self, layout, reload)
void __cdecl ReloadCallback(cSPUIAssetVerbs* self, void* layout, bool reload) {
    if (!reload) {
        AssignWin(&self->mWin7, 0);
        AssignWin(&self->mWinRoot, 0);
        AssignWin(&self->mWin3, 0);
        AssignWin(&self->mWin4, 0);
        AssignWin(&self->mWin6, 0);
        AssignWin(&self->mWin5, 0);
        return;
    }
    void* w = ((cSPUILayout*)self->mLayout)->FindWindowByID(0x149371c4, 1);
    AssignWin(&self->mWin7, w);
    if (self->mWinParent) {
        void* w1 = vcp2(self->mWinParent, 0xf0, 0x67a3600, 1);
        AssignWin(&self->mWinRoot, w1);
        if (self->mWinRoot) {
            float* r = vcfp(self->mWinRoot, 0x38);
            self->mVec[0] = r[0];
            self->mVec[1] = r[1];
            self->mVec[2] = r[2];
            self->mVec[3] = r[3];
            vc1(self->mWinParent, 0xdc, (int)self->mWin7);
            vc1(self->mWinRoot, 0xd8, (int)self->mWin7);
        }
        void* w2 = vcp2(self->mWinParent, 0xf0, 0x667bf68, 1);
        AssignWin(&self->mWin3, w2);
        void* w3 = vcp2(self->mWinParent, 0xf0, 0x67a3238, 1);
        AssignWin(&self->mWin4, w3);
        void* w4 = ((cSPUILayout*)self->mLayout)->FindWindowByID(0x67a32d0, 1);
        AssignWin(&self->mWin6, w4);
        if (self->mWin6) {
            void* inner = vcp0(self->mWin6, 0x10);
            vc1(inner, 0xdc, (int)self->mWin6);
            if (self->mWin4) vc1(self->mWin4, 0xd8, (int)self->mWin6);
        }
        void* w5 = vcp2(self->mWinParent, 0xf0, 0x67a36c0, 1);
        AssignWin(&self->mWin5, w5);
    }
    if (self->mWin7) SPUIHelpers_SetWindowAreaToParent(self->mWin7);
}

// @ 0x00656b80  cSPUIAssetVerbs::Init
void cSPUIAssetVerbs::Init(void* parent) {
    AssignWin(&mWinParent, parent);
    void* p = EA_operator_new(0x18, "Sporepedia", 0, 0, 0, 0);
    void* layout;
    if (p) layout = cSPUILayout_Ctor(p);
    else layout = 0;
    AssignLayout(&mLayout, layout);
    int g = *(int*)0x15261e4;
    int key[3];
    key[0] = 0xba5ee251;
    key[1] = 0x510a95b;
    key[2] = g;
    ((cSPUILayout*)mLayout)->Init(key, 1, 0x5b598fa);
    ((cSPUILayout*)mLayout)->SetParentWin(mWinParent, 1, 0x5b598fa);
    ((cSPUILayout*)mLayout)->SetReloadCallback((void*)&ReloadCallback, this);
    ReloadCallback(this, mLayout, true);
}

// ---------------------------------------------------------------------------
// SP::cSPUIAssetView
// ---------------------------------------------------------------------------
struct cSPUIAssetView {
    char  b0[0xc];        // 0x00..0x0b
    float mTargetX;       // 0x0c
    float mTargetY;       // 0x10
    char  b14[0x1];       // 0x14
    char  mFirstUpdate;   // 0x15
    char  b16[0x1];       // 0x16
    bool  mResponds;      // 0x17
    char  b18[0x10];      // 0x18..0x27
    void* mWinShine;      // 0x28
    char  b2c[0x4];       // 0x2c..0x2f
    void* mThumb;         // 0x30
    void* mThumbBack;     // 0x34
    void* mName;          // 0x38
    char  b3c[0xc];       // 0x3c..0x47
    void* mPublished;     // 0x48
    void* mLocked;        // 0x4c
    void* mGameplayCont;  // 0x50
    void* mGameplayName;  // 0x54
    char  b58[0x30];      // 0x58..0x87
    void* mP88;           // 0x88
    void* mP8c;           // 0x8c
    void* mP90;           // 0x90
    char  b94[0x60];      // 0x94..0xf3
    bool  mBf4;           // 0xf4
    bool  mBf5;           // 0xf5
    bool  mBf6;           // 0xf6
    bool  mBf7;           // 0xf7

    int   IsAnimTargetDifferent();
    void  Show();
    void  Hide();
    float GetHeight();
    float GetWidth();
    void  SetFirstUpdate(int b);
    void  SelectAsset(int a, char b, int c, char d, char e);
    void  m57460(bool b);
    void  m57640(void* a, void* b, void* c, int d, void* e, void* f, void** out);
};

// @ 0x006577a0
int cSPUIAssetView::IsAnimTargetDifferent() {
    if (mWinShine) {
        float* p = vcfp(mWinShine, 0x34);
        float x = p[0];
        float y = p[1];
        if (x != mTargetX) return 1;
        if (y != mTargetY) return 1;
    }
    void* anim = 0;
    void* ab = SP_AssetBrowser();
    if (ab) anim = *(void**)((char*)ab + 0x14);
    if (anim && mWinShine && ((cSPUIAnimator*)anim)->HasAnimation(mWinShine, 4)) return 1;
    return 0;
}

// @ 0x00657810
void cSPUIAssetView::Show() {
    if (mResponds && !mBf7) {
        mBf7 = true;
        if (mBf6) vc1(this, 0x4c, 1);
        if (mWinShine) {
            vc2(mWinShine, 0x7c, 0x10, 1);
            vc2(mWinShine, 0x7c, 0x1000, 1);
        }
        SPUIHelpers_UpdateMouseFocus(1);
    }
}

// @ 0x00657870
void cSPUIAssetView::Hide() {
    if (mResponds && mBf7) {
        mBf7 = false;
        if (mBf6) vc0(this, 0x48);
        if (mWinShine) {
            vc2(mWinShine, 0x7c, 0x10, 0);
            vc2(mWinShine, 0x7c, 0x1000, 0);
        }
        SPUIHelpers_UpdateMouseFocus(1);
    }
}

// @ 0x006578d0
float cSPUIAssetView::GetHeight() {
    if (mWinShine) {
        float* p = vcfp(mWinShine, 0x34);
        return p[3] - p[1];
    }
    return 0.0f;
}

// @ 0x006578f0
float cSPUIAssetView::GetWidth() {
    if (mWinShine) {
        float* p = vcfp(mWinShine, 0x34);
        return p[2] - p[0];
    }
    return 0.0f;
}

// @ 0x00657930
void cSPUIAssetView::SetFirstUpdate(int b) {
    mFirstUpdate = (char)b;
    if (mThumbBack) vc2(mThumbBack, 0x7c, 1, b);
    if (!mThumb || !mLocked) return;
    float v[4];
    if (mName && (vcr0(mName, 0x28) & 1)) goto zero;
    if (mGameplayCont && (vcr0(mGameplayCont, 0x28) & 1)) goto zero;
    {
        float* p = vcfp(mThumb, 0x34);
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        v[3] = p[3];
        float* q = vcfp(mLocked, 0x34);
        v[3] = -(q[3] - q[1]);
        vc1p(mThumb, 0x60, v);
        return;
    }
zero:
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    vc1p(mThumb, 0x60, v);
}

// @ 0x00657a30  cSPUIAssetView::SelectAsset
struct C64e740 {
    void* vf0;
    void* vf1;
    void* p08;
    void* view;
    char  sa;
    void* sc;
    char  sd;
    char  se;
    C64e740* Construct(void* v, char a, int c, char d, char e);
};

void cSPUIAssetView::SelectAsset(int a, char b, int c, char d, char e) {
    if (b) {
        void* ab = SP_AssetBrowser();
        if (ab) {
            ab = SP_AssetBrowser();
            void* q = *(void**)((char*)ab + 0xbc);
            if (q) ((void(__thiscall*)(void*, void*))&FUN_00654e20)(q, this);
        }
    }
    void* obj = EA_operator_new(0x1c, (const char*)0x13f6b3c, 0, 0, 0, 0);
    C64e740* made;
    if (obj != 0) {
        made = ((C64e740*)obj)->Construct(this, a, c, d, e);
        if (made) vc0(made, 4);
    }
    else {
        made = 0;
    }
    void* srv = SP_MessageServer();
    vc3(srv, 0x14, 0x94174b89, (int)made, 0);
    if (made) vc0(made, 8);
}

// ---------------------------------------------------------------------------
// 0x00657460
// ---------------------------------------------------------------------------
// @ 0x00657460
void cSPUIAssetView::m57460(bool b) {
    cSPUIAssetView* self = this;
    self->mBf4 = b;
    if (self->mPublished) {
        void* res = 0;
        if (self->mP90 == 0) {
            res = 0;
        }
        else {
            res = vcp1((char*)self->mP90 + 0x10, 0xc, 0x13d55dc8);
        }
        bool f1 = false, f2 = false;
        if (res) {
            f1 = FUN_006418e0(res) != 0;
            f2 = ((long long(__thiscall*)(void*))(*(void**)((char*)*(void**)res + 0x54)))(res) != 0;
        }
        void* cfg = SP_ConfigManager();
        bool cfgv = (vcr1(cfg, 0x30, 0x5de7b4a) != 0);
        bool authv = vcr0(SP_AuthManager(), 0x24) != 0;
        bool en;
        if (b && !cfgv && !authv && (f1 == authv) && (f2 != authv)) {
            void* app = *(void**)0x15fd918;
            void* pm = *(void**)((char*)app + 0x3c);
            en = (*(int*)((char*)pm + 0x118) == 0);
        }
        else {
            en = false;
        }
        vc2(self->mPublished, 0x7c, 2, en ? 1 : 0);
        vc2(self->mPublished, 0x7c, 0x10, en ? 0 : 1);
    }
    if (self->mBf6) {
        if (self->mBf4) return;
        vc1(self, 0x4c, 1);
    }
    if (self->mBf4) return;
    if (self->mBf5) {
        vc0(self, 0x34);
    }
    else {
        if (self->mGameplayName) {
            if (vcp0(self->mGameplayName, 0x10) != 0) {
                void* inner = vcp0(self->mGameplayName, 0x10);
                vc1(inner, 0xe0, (int)self->mGameplayName);
                AssignWin(&self->mGameplayName, 0);
            }
        }
    }
    if (self->mP8c) {
        vc0(self->mP8c, 0x18);
        AssignWin(&self->mP8c, 0);
    }
    if (self->mP88) {
        vc0(self->mP88, 0x18);
        AssignWin(&self->mP88, 0);
    }
}

// @ 0x00657640
void cSPUIAssetView::m57640(void* a, void* b, void* c, int d, void* e, void* f, void** out) {
    cSPUIAssetView* self = this;
    if (!out) return;
    if (!a) return;
    if (!self->mP90) return;
    void* v = 0;
    void* x = 0;
    void* y = 0;
    if (d) {
        void* pm = SP_PropertyManager();
        if (v) AssignWin(&v, 0);
        vcp2(pm, 0x2c, d, (int)e);   // (d, e, &v)
        extern void __cdecl vec_reserve(void*, int, void*, void*);
        vec_reserve(v, 0x4aa3838, &x, &y);
    }
    void* obj = EA_operator_new(0x54, "Sporepedia", 0, 0, 0, 0);
    void* made;
    if (obj == 0) made = 0;
    else {
        made = FUN_00656240(obj, (void*)0);
        if (made) vc0(made, 0);
    }
    vc2(made, 0x10, (int)a, (int)b);
    void* m = self->mP90;
    void* pos = vcp0(m, 0x40);
    void* sz = vcp0(m, 0x3c);
    float fv = *(float*)sz;
    FUN_004e5410(*(int*)pos, *(int*)((char*)pos + 4), *(int*)((char*)pos + 8), b, made, fv);
    *out = made;
}

// ---------------------------------------------------------------------------
// Small object at 0x6563c0 (pre-cSPUIAssetVerbs); ctor returns this.
// ---------------------------------------------------------------------------
struct C563c0 {
    int   f0;      // +0x0
    char  f4;      // +0x4
    char  f5;      // +0x5
    char  f6;      // +0x6
    int   f8;      // +0x8
    char  fc;      // +0xc
    C563c0();
};
// @ 0x006563c0
C563c0::C563c0() {
    f0 = 0;
    f4 = 0;
    f5 = 0;
    f6 = 0;
    f8 = 1;
    fc = 0;
}

// @ 0x00656310
struct CBig { char pad[0xe0]; int mE0; void Insert(void* p); };
void CBig::Insert(void* p) {
    // incomplete: template insert/erase; see partial.txt
    (void)p;
}
