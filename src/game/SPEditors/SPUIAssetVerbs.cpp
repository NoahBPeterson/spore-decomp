// src/game/SPEditors/SPUIAssetVerbs.cpp -- migrated from slice(s) s00656310 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIAssetVerbs.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIAssetVerbs.h"
#include "SP/cSPUIAssetView.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __fastcall cSPUILayout_Ctor(void* self);
extern "C" void* __cdecl EA_operator_new(int size, const char* name, int a, int b, int c, int d);
extern "C" void __cdecl RemoveHandler5(void* a, void* b, void* c, void* d, void* e);
extern "C" void __cdecl SPUIHelpers_SetWindowAreaToParent(void* w);
extern int gVtA, gVtB, gVtC, gVtD, gVtE, gVtF, gVtG, gVtH, gVtI;
#include <intrin.h>

// ---- items of slice s00656310 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void  vc0(void* p, int off) { ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void  vc1(void* p, int off, int a) { ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline void  vc2(void* p, int off, int a, int b) { ((void(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline int   vcr0(void* p, int off) { return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void* vcp0(void* p, int off) { return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void* vcp2(void* p, int off, int a, int b) { return ((void*(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline void  vc1p(void* p, int off, void* a) { ((void(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline float* vcfp(void* p, int off) { return ((float*(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void  vc2f(void* p, int off, float a, float b) { ((void(__thiscall*)(void*, float, float))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline void AssignWin(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 0);
        *slot = p;
        if (old) vc0(old, 4);
    }
}
inline void AssignLayout(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 4);
        *slot = p;
        if (old) vc0(old, 8);
    }
}
struct cSPUILayout_s0065_6310 {
    void* vf0;  // +0
    void* vf1;  // +4
    void* vf2;  // +8
    void* FindWindowByID(int id, int flag);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void  Shutdown(int flag);  // 0x00811ad0 (cSPUILayout::Shutdown)
    void  SetParentWin(void* parent, int a, int id);  // 0x008121b0 (cSPUILayout::SetParentWin)
    void  SetReloadCallback(void* fn, void* self);  // 0x00810090 (cSPUILayout::SetReloadCallback)
    void  Init(void* key, int a, int id);  // 0x008120d0 (cSPUILayout::Init)
};
extern "C" void* __fastcall cSPUILayout_Ctor(void* self);
extern "C" void* __cdecl EA_operator_new(int size, const char* name, int a, int b, int c, int d);
extern "C" void __cdecl RemoveHandler5(void* a, void* b, void* c, void* d, void* e);
extern "C" void __cdecl SPUIHelpers_SetWindowAreaToParent(void* w);
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
extern int gVtA, gVtB, gVtC, gVtD, gVtE, gVtF, gVtG, gVtH, gVtI;
// ---- items of slice s00656310 end

// @ 0x00656410
void __fastcall cSPUIAssetVerbs_dtor(cSPUIAssetVerbs* self)
{
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

// @ 0x00656510
void cSPUIAssetVerbs::UpdatePos(void* p)
{
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
        void* w1 = ((cSPUILayout_s0065_6310*)mLayout)->FindWindowByID(ids1[i], 1);
        void* w2 = ((cSPUILayout_s0065_6310*)mLayout)->FindWindowByID(ids2[i], 1);
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
        float* rect = vcfp(mWin3, 0x38);
        float r = rect[2] - rect[0];
        v[0] = v[0] - r * (float)(n - 5);
        vc1p(mWinRoot, 0x6c, v);
    }
    if (mWin6 && mWin5) {
        float px = vcfp(mWin5, 0x38)[0];
        float py = vcfp(mWin5, 0x38)[1];
        vc2f(mWin6, 0x70, px, py);
    }
}

// @ 0x006566f0
void cSPUIAssetVerbs::Shutdown()
{
    if (mLayout) {
        ((cSPUILayout_s0065_6310*)mLayout)->Shutdown(1);
        AssignLayout(&mLayout, 0);
    }
    int h0 = mAutoh[0];
    if (h0) {
        mAutoh[0] = 0;
        RemoveHandler5((void*)h0, (void*)mAutoh[1], (void*)mAutoh[2], (void*)mAutoh[3], (void*)mAutoh[4]);
    }
}

// @ 0x00656740
bool cSPUIAssetVerbs::IsVerb(int idx)
{
    void* w = ((cSPUILayout_s0065_6310*)mLayout)->FindWindowByID(((int*)0x13ffc00)[idx], 1);
    if (w) return (vcr0(w, 0x28) & 1);
    return false;
}

// @ 0x00656770
void SP::cSPUIAssetVerbs::Update(unsigned int p)
{
    int* ids1 = (int*)0x13ffc00;
    int* ids2 = (int*)0x13ffc18;
    for (int i = 0; i < 6; ++i) {
        void* w1 = ((cSPUILayout*)mLayout.mpObject)->FindWindowByID(ids1[i], 1);
        void* w2 = ((cSPUILayout*)mLayout.mpObject)->FindWindowByID(ids2[i], 1);
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
    if (mAutoMsgHandler.mpServer) vc2(mAutoMsgHandler.mpServer, 0x7c, 1, 0);
    if (mAutoMsgHandler.mpIdArray) vc2(mAutoMsgHandler.mpIdArray, 0x7c, 1, 0);
}

// @ 0x00656890
void __cdecl ReloadCallback(cSPUIAssetVerbs* self, void* layout, bool reload)
{
    if (!reload) {
        AssignWin(&self->mWin7, 0);
        AssignWin(&self->mWinRoot, 0);
        AssignWin(&self->mWin3, 0);
        AssignWin(&self->mWin4, 0);
        AssignWin(&self->mWin6, 0);
        AssignWin(&self->mWin5, 0);
        return;
    }
    void* w = ((cSPUILayout_s0065_6310*)self->mLayout)->FindWindowByID(0x149371c4, 1);
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
        void* w4 = ((cSPUILayout_s0065_6310*)self->mLayout)->FindWindowByID(0x67a32d0, 1);
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

// @ 0x00656b00
cSPUIAssetVerbs* __fastcall cSPUIAssetVerbs_ctor(cSPUIAssetVerbs* self)
{
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

// @ 0x00656b80
void cSPUIAssetVerbs::Init(void* parent)
{
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
    ((cSPUILayout_s0065_6310*)mLayout)->Init(key, 1, 0x5b598fa);
    ((cSPUILayout_s0065_6310*)mLayout)->SetParentWin(mWinParent, 1, 0x5b598fa);
    ((cSPUILayout_s0065_6310*)mLayout)->SetReloadCallback((void*)&ReloadCallback, this);
    ReloadCallback(this, mLayout, true);
}
