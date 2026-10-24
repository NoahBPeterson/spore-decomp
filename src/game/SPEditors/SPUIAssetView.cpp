// src/game/SPEditors/SPUIAssetView.cpp -- migrated from slice(s) s0065af90, s0065a070, s006596b0, s006589d0, s00657ad0, s00656c70, s00656310, s004bafc0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIAssetView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "SP/cSPUIAssetView.h"
#include "cSPUILayout.h"
#include "SP/cPropertyList.h"
#include <math.h>

// ---- items of slice s00656310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_operator_new(int size, const char* name, int a, int b, int c, int d);
extern "C" void __cdecl SPUIHelpers_UpdateMouseFocus(int v);
extern "C" void* __cdecl SP_AssetBrowser();
extern "C" void* __cdecl SP_ConfigManager();
extern "C" void* __cdecl SP_AuthManager();
extern "C" void* __cdecl SP_PropertyManager();
extern "C" void* __cdecl SP_MessageServer();
extern "C" bool __fastcall FUN_006418e0(void* p);
extern "C" void* __fastcall FUN_00656240(void* a, void* b);
extern "C" void FUN_00654e20();
extern "C" void  __cdecl FUN_004e5410(int, int, int, void*, void*, float);
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
inline void AssignWin(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 0);
        *slot = p;
        if (old) vc0(old, 4);
    }
}
struct cSPUIAnimator_s0065_6310 {
    bool HasAnimation(void* win, int id);  // 0x007f62c0 (cSPUIAnimator::HasAnimation)
};
struct cSPUIAssetView {
    char  b0[0xc];        // 0x00..0x0b
    float mTargetX;       // 0x0c
    float mTargetY;       // 0x10
    char  b14[0x1];       // 0x14
    unsigned char mFirstUpdate;   // 0x15
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
// ---- items of slice s00656310 end

// ---- items of slice s00656c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_15f9f40;
struct ITelemetry {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual int GetValue();                                // 0x20
  virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void BeginEvent(uint32_t id);                  // 0x38
  virtual void v15();
  virtual void AddUInt32(uint32_t key, uint32_t value);  // 0x40
  virtual void v17(); virtual void v18(); virtual void v19();
  virtual void AddUInt32b(uint32_t key, uint32_t value); // 0x50
  virtual void v21();
  virtual void EndEvent();                               // 0x58
};
ITelemetry* GetTelemetry();  // FUN_00a206f0
struct Vec3 { float x, y, z; };
extern Vec3 g_1526560;
struct Vec3Holder { Vec3 Get(); };
struct VObj {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void Enable(); virtual void Disable();
};
struct ISub { virtual void a(); virtual void b(); virtual void c(); virtual void* Cast(uint32_t); };
struct Outer { char pad[0x10]; ISub sub; };
// ---- items of slice s00656c70 end

// ---- items of slice s00657ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00657930(void*, int);           // 0x00657930
struct cSPUILayout_s0065_7ad0 {
    void SetReloadCallback(void* fn, void* self);   // 0x00810090 (thiscall)
};
void FUN_00657e20(void* obj, int arg);              // 0x00657e20 (cdecl)
struct AssetView {
    void SetWindowArea(char animate);   // 0x00657ad0
    char IsReady();                     // 0x00657dd0
    void OnDetach();                    // 0x00657e00
    void UpdateVerbIcon();              // 0x00657e60
};
// ---- items of slice s00657ad0 end

// ---- items of slice s006589d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00657810(void*);   // 0x00657810 (Show)
struct AssetViewS68 {
    void SetPos(float x, float y, char snap);   // 0x00658e00 (ret 0xc)
};
// ---- items of slice s006589d0 end


// ---- items of slice s0065a070 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
inline void  vc0_s0065_a070(void* p, int o) { (*(void(__thiscall**)(void*))((char*)*(void**)p + o))(p); }
inline void  vc1_s0065_a070(void* p, int o, int a) { (*(void(__thiscall**)(void*, int))((char*)*(void**)p + o))(p, a); }
inline void  vc2_s0065_a070(void* p, int o, int a, int b) { (*(void(__thiscall**)(void*, int, int))((char*)*(void**)p + o))(p, a, b); }
inline void  vc1p_s0065_a070(void* p, int o, void* a) { (*(void(__thiscall**)(void*, void*))((char*)*(void**)p + o))(p, a); }
inline void  vc2f(void* p, int o, float a, float b) { (*(void(__thiscall**)(void*, float, float))((char*)*(void**)p + o))(p, a, b); }
inline int   vci0(void* p, int o) { return (*(int(__thiscall**)(void*))((char*)*(void**)p + o))(p); }
inline int   vci1(void* p, int o, int a) { return (*(int(__thiscall**)(void*, int))((char*)*(void**)p + o))(p, a); }
inline void* vcp0_s0065_a070(void* p, int o) { return (*(void*(__thiscall**)(void*))((char*)*(void**)p + o))(p); }
inline void* vcp2_s0065_a070(void* p, int o, int a, int b) { return (*(void*(__thiscall**)(void*, int, int))((char*)*(void**)p + o))(p, a, b); }
inline float* vpf0(void* p, int o) { return (*(float*(__thiscall**)(void*))((char*)*(void**)p + o))(p); }
inline void AssignWin_s0065_a070(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0_s0065_a070(p, 0);
        *slot = p;
        if (old) vc0_s0065_a070(old, 4);
    }
}
struct cSPUILayout_s0065_a070 {
    void* vf0;
    void* vf1;
    void* vf2;
    void* FindWindowByID(int id, int flag);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void  Init(const void* key, int a, int id);  // 0x008120d0 (cSPUILayout::Init)
    void  Shutdown(int flag);  // 0x00811ad0 (cSPUILayout::Shutdown)
};
struct cPropertyList { char GetDescription(int key); };
extern cPropertyList* g_pAppProperties;                // 0x15fd918
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
struct cSPUIAssetView_s0065_a070 {
    char  b00[0xc];                    // 0x00
    float mTargetX;                    // 0x0c
    float mTargetY;                    // 0x10
    char  f14;                         // 0x14
    unsigned char mFirstUpdate;                // 0x15
    char  mResponds;                   // 0x16
    char  f17;                         // 0x17
    void* mAnimator;                   // 0x18
    void* p1c;                         // 0x1c
    cSPUILayout_s0065_a070* mLayout;              // 0x20
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

    void LoadLayout();  // 0x0065a070 (cSPUIAssetView::LoadLayout)
    void Update(unsigned int dt, bool b);  // 0x0065a990 (cSPUIAssetView::Update)
    bool IsAnimTargetDifferent();  // 0x006577a0 (cSPUIAssetView::IsAnimTargetDifferent)
    void Hide();  // 0x00657870 (cSPUIAssetView::Hide)
    void Show();  // 0x00657810 (cSPUIAssetView::Show)
    void SetFirstUpdate(int b);  // 0x00657930 (cSPUIAssetView::SetFirstUpdate)
};
// ---- items of slice s0065a070 end

// ---- items of slice s0065af90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* operator_new_ea(unsigned int size, const char* tag, int, int, int, int);
extern void** g_15fa018;
extern void** g_15fa01c;
struct ResourceKey {
  uint32_t a, b, c;
};
extern ResourceKey g_key_1526560;
struct ILayoutObj {
  virtual void a0(); virtual void a1(); virtual void a2(); virtual void* a3();
  virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
  virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
  virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
  virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
  virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
  virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
  virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
  virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
  virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
  virtual void a40(); virtual void a41(); virtual void a42(); virtual int a43();  // 0xac?
  virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
  virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51();
  virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55();
  virtual void a56();  // 0xe0
  virtual void a57(); virtual void a58(); virtual void a59(); virtual void a60();
  virtual void a61(); virtual void a62(); virtual void a63();
  virtual void a64();  // 0x100
  virtual void a65(void*);  // 0x104
  virtual void a66(void*);  // 0x108
};
void FUN_00657420();
void* LayoutCtor18();  // 0x810000
struct SiblingWin {
  void** vt;
  char pad[0x13];
  bool m17;
  char pad18[4];
  int m1c;             // +0x1c
  ILayoutObj* mpLayout;  // +0x20
  void* mpParent;      // +0x24
  char pad28[0x2c];
  void* m54;           // +0x54
  char pad58[0x9c];
  bool mf4;            // +0xf4
  void v38(bool);
  void v3c(ResourceKey*);
  void v40();
  // @ 0x0065af90
  void FUN_0065af90(bool active, int unused);
};
extern uint32_t g_15f9f40_s0065_af90;
void FUN_0065aed0(int n);
// ---- items of slice s0065af90 end

// @ 0x004bb860
uint32_t FUN_004bb860(uint32_t type)
{
    switch (type) {
    case 0xdfad9f51: return 0x3d97a8e4;
    case 0x4178b8e8:
    case 0x372e2c04:
    case 0xccc35c46:
    case 0x9ea3031a:
    case 0x65672ade: return 0x2b978c46;
    case 0x72c49181:
    case 0x47c10953:
    case 0x4e3f7777:
    case 0xbdd15f3d:
    case 0x99e92f05: return 0x2399be55;
    case 0x2a5147a9:
    case 0x1a4e0708:
    case 0x1f2a25b6:
    case 0x2090a11b:
    case 0x441cd3e6:
    case 0x449c040f:
    case 0x7d433fad:
    case 0x8f963dcb:
    case 0x9ad7d4aa:
    case 0xc0b74287:
    case 0xf670aa43:
    case 0xbc1041e6:
    case 0xc15695da: return 0x24682294;
    case 0x98e03c0d: return 0x476a98c7;
    case 0x37148141:
    case 0xb8669ec9:
    case 0xbcd73e89: return 0x438f6347;
    default: return 0;
    }
}








// @ 0x00657340
void * SP::cSPUIAssetView::AsInterface(EA::COM::InterfaceId id)
{
  if (id == 0xee3f516e) return this;
  if (id == 0x2f009dd0) return this;
  if (id == 0x73cc339e) return this;
  return 0;
}







// @ 0x00657370
bool LogEvent_4e79d7d1()
{
  ITelemetry* t0 = GetTelemetry();
  int v = t0 ? t0->GetValue() : 0;
  ITelemetry* t = GetTelemetry();
  if (t) {
    t->BeginEvent(0x3475365);
    t->AddUInt32(0x3475381, 0x4e79d7d1);
    t->AddUInt32(0x3475385, v);
    t->EndEvent();
  }
  return false;
}







// @ 0x006573e0
int GetGlobal_15f9f40()
{ return g_15f9f40; }







// @ 0x006573f0
Vec3 Vec3Holder::Get()
{ return g_1526560; }







// @ 0x00657420
void SetEnabled(VObj* o, int, bool b)
{
  if (!b) o->Disable();
  else o->Enable();
}







// @ 0x00657440
void* CastSub(Outer** p)
{
  if (*p) return (*p)->sub.Cast(0x13d55dc8);
  return 0;
}







// @ 0x00657460
void cSPUIAssetView::m57460(bool b)
{
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
void cSPUIAssetView::m57640(void* a, void* b, void* c, int d, void* e, void* f, void** out)
{
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








// @ 0x006577a0
int cSPUIAssetView::IsAnimTargetDifferent()
{
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
    if (anim && mWinShine && ((cSPUIAnimator_s0065_6310*)anim)->HasAnimation(mWinShine, 4)) return 1;
    return 0;
}








// @ 0x00657810
void cSPUIAssetView::Show()
{
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
void cSPUIAssetView::Hide()
{
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
float cSPUIAssetView::GetHeight()
{
    if (mWinShine) {
        float* p = vcfp(mWinShine, 0x34);
        return p[3] - p[1];
    }
    return 0.0f;
}








// @ 0x006578f0
float cSPUIAssetView::GetWidth()
{
    if (mWinShine) {
        float* p = vcfp(mWinShine, 0x34);
        return p[2] - p[0];
    }
    return 0.0f;
}








// @ 0x00657930
void cSPUIAssetView::SetFirstUpdate(int b)
{
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








// @ 0x00657a30
void cSPUIAssetView::SelectAsset(int a, char b, int c, char d, char e)
{
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






// @ 0x00657ad0
void AssetView::SetWindowArea(char animate)
{
    char* s = (char*)this;
    if (!*(void**)(s + 0x4c) || !*(void**)(s + 0x50))
        return;
    {
        void* w = *(void**)(s + 0x4c);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x7c))(w, 1, animate);
    }
    {
        void* w = *(void**)(s + 0x50);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x7c))(w, 1, animate);
    }
    FUN_00657930(this, s[0x15]);
    if (!*(void**)(s + 0x28) || !*(void**)(s + 0x24) || !s[0xfc])
        return;
    void* target = *(void**)(s + 0x24);
    float* r = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)target + 0x38))(target);
    float x0 = r[0], y0 = r[1], x1 = r[2], y1 = r[3];
    if (!animate) {
        void* src = *(void**)(s + 0x4c);
        float* r2 = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)src + 0x34))(src);
        y1 = (r2[3] - r2[1]) + y1;
    }
    void* dst = *(void**)(s + 0x28);
    (*(void(__thiscall**)(void*, float, float))((char*)*(void**)dst + 0x74))(dst, x1 - x0,
                                                                             y1 - y0);
}






// @ 0x00657bc0
char FUN_00657bc0(void* self, void* ev)
{
    char* s = (char*)self;
    if (!s[0xf5])
        return 0;
    int key = *(int*)((char*)ev + 8);
    if (key == 0x1b)
        return 1;
    if (key == 6) {
        void* w = *(void**)(s + 0x28);
        (void)w;
        return 1;
    }
    if (key == 7) {
        void* w = *(void**)(s + 0x28);
        (void)w;
        return 1;
    }
    if (key == 8) {
        void* w = *(void**)(s + 0x28);
        (void)w;
        return 1;
    }
    return 0;
}






// @ 0x00657dd0
char AssetView::IsReady()
{
    char* s = (char*)this;
    void* p = *(void**)(s + 0x98);
    if (!p || !(*(unsigned char*)((char*)p + 4) & 1))
        return 0;
    void* q = *(void**)(s + 0x9c);
    if (!q || !(*(unsigned char*)((char*)q + 4) & 1))
        return 0;
    return 1;
}






// @ 0x00657e00
void AssetView::OnDetach()
{
    char* s = (char*)this;
    void* layout = *(void**)(s + 0x20);
    if (layout)
        ((cSPUILayout_s0065_7ad0*)layout)->SetReloadCallback(0, 0);
    (*(void(__thiscall**)(void*))((char*)*(void**)s + 0x44))(s);
}






// @ 0x00657e20
void FUN_00657e20(void* obj, int arg)
{
    if (!obj)
        return;
    void* r = (*(void*(__thiscall**)(void*, int))((char*)*(void**)obj + 0xc))(obj, 0x105a93d);
    if (!r)
        return;
    (*(void(__thiscall**)(void*, int))((char*)*(void**)r + 0x14))(r, arg);
    (*(void(__thiscall**)(void*, int, int))((char*)*(void**)obj + 0x7c))(obj, 1, 1);
}






// @ 0x00657e60
void AssetView::UpdateVerbIcon()
{
    char* s = (char*)this;
    void* p = *(void**)(s + 0x90);
    if (!p)
        return;
    int v = (*(int(__thiscall**)(void*))((char*)*(void**)p + 0x38))(p);
    if (v > 0x7fffffff)
        return;
    void* obj = *(void**)(s + 0x74);
    switch (v) {
    case -2: FUN_00657e20(obj, 6); return;
    case -1: return;
    case 0:  FUN_00657e20(obj, 0); return;
    case 1:  FUN_00657e20(obj, 1); return;
    case 2:  FUN_00657e20(obj, 5); return;
    case 3:  FUN_00657e20(obj, 2); return;
    case 4:  FUN_00657e20(obj, 3); return;
    case 5:  FUN_00657e20(obj, 4); return;
    default: return;
    }
}






// @ 0x00657f70
void* FUN_00657f70(void* self, void* parent)
{
    (void)parent;
    return self;
}






// @ 0x006580b0
void FUN_006580b0(void* self)
{ (void)self; }






// @ 0x006582f0
void FUN_006582f0(void* self)
{ (void)self; }






// @ 0x00658440
void FUN_00658440(void* self)
{ (void)self; }





// @ 0x006589d0
void FUN_006589d0(void* self, void* ev)
{ (void)self; (void)ev; }





// @ 0x00658c70
void FUN_00658c70(void* self)
{ (void)self; }





// @ 0x00658e00
void AssetViewS68::SetPos(float x, float y, char snap)
{
    char* s = (char*)this;
    *(float*)(s + 0xc) = x;
    *(float*)(s + 0x10) = y;
    void* w = *(void**)(s + 0x28);
    if (w && !snap) {
        (*(void(__thiscall**)(void*, float, float))((char*)*(void**)w + 0x64))(w, x, y);
    }
    w = *(void**)(s + 0x28);
    if (w) {
        float* p = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)w + 0x34))(w);
        if (p[0] != *(float*)(s + 0xc) || p[1] != *(float*)(s + 0x10))
            ((void(__thiscall*)(void*))FUN_00657810)(s);
    }
}





// @ 0x00658e80
void FUN_00658e80(void* self, void* a, void* b, void* c)
{ (void)self; (void)a; (void)b; (void)c; }





// @ 0x00659270
void FUN_00659270(void* self)
{ (void)self; }





// @ 0x00659340
void FUN_00659340(void* self)
{ (void)self; }





// @ 0x006593c0
void FUN_006593c0(void* self)
{ (void)self; }




// @ 0x006596b0
void FUN_006596b0(void* self)
{ (void)self; }

// @ 0x00659a20
void FUN_00659a20(void* self, void* ev)
{ (void)self; (void)ev; }

// @ 0x00659ec0
void FUN_00659ec0(void* self)
{ (void)self; }

// @ 0x0065a070
void cSPUIAssetView_s0065_a070::LoadLayout()
{
    if (fF5) return;

    AssignWin_s0065_a070(&mWinShine, mLayout->FindWindowByID(0xf3c6dc19, 1));
    if (mWinShine) {
        unsigned u = ColorRGBAToU32((const void*)0x1526280);
        vc1_s0065_a070(mWinShine, 0x5c, (int)u);
        FUN_008082f0(mWinShine, 0.0f, 0.0f);
        FUN_00808190(mWinShine, 1.0f, 1.0f);
    }
    if (mWinShine && mWinRoot && fFC) {
        float* r = vpf0(mWinRoot, 0x38);
        vc2f(mWinShine, 0x74, r[2] - r[0], r[3] - r[1]);
    }
    if (mWinShine) {
        if (f17) vc1p_s0065_a070(mWinShine, 0x104, this);
        vc2_s0065_a070(mWinShine, 0x7c, 2, f17);
        vc2_s0065_a070(mWinShine, 0x7c, 0x10, f17 == 0);
        vc2_s0065_a070(mWinShine, 0x7c, 0x1000, f17 == 0);
    }

    AssignWin_s0065_a070(&mWinSelection, mLayout->FindWindowByID(0x674aa70, 1));
    if (mWinSelection) {
        uint32_t v[4] = {0, 0, 0, 0};
        vc1p_s0065_a070(mWinSelection, 0x60, v);
    }

    AssignWin_s0065_a070(&mWinThumbnail, mLayout->FindWindowByID(0x6650680, 1));
    AssignWin_s0065_a070(&mWinThumbnailBackdrop, mLayout->FindWindowByID(0x548e69a6, 1));
    SetFirstUpdate(mFirstUpdate);
    AssignWin_s0065_a070(&mWinAuthor, mLayout->FindWindowByID(0xf3c6d819, 1));
    AssignWin_s0065_a070(&mWinTimestamp, mLayout->FindWindowByID(0x13d938db, 1));
    ((G*)this)->FUN_006596b0();

    AssignWin_s0065_a070(&mWinLoading, mLayout->FindWindowByID(0x53d6fe29, 1));
    if (mWinLoading) {
        void* x = mP90;
        if (x) {
            const wchar_t* s;
            if (vci0(x, 0xc) == 0) s = (const wchar_t*)0x13ffd4c; // L"<Missing>"
            else s = (const wchar_t*)vcp0_s0065_a070(x, 0xc);
            vc1p_s0065_a070(mWinLoading, 0x80, (void*)s);
            vc2_s0065_a070(mWinLoading, 0x7c, 1, 1);
        }
    }
    AssignWin_s0065_a070(&mWinPublished, mLayout->FindWindowByID(0x53d6fe2a, 1));
    if (mWinPublished) {
        void* x = mP90;
        if (x) {
            const wchar_t* s;
            if (vci0(x, 0x10) == 0) s = (const wchar_t*)0x13ffd4c;
            else s = (const wchar_t*)vcp0_s0065_a070(x, 0x10);
            vc1p_s0065_a070(mWinPublished, 0x80, (void*)s);
        }
    }
    AssignWin_s0065_a070(&mWinLocked, mLayout->FindWindowByID(0x5492085e, 1));
    if (mWinLocked) vc1p_s0065_a070(mWinLocked, 0x80, (void*)0x13ec468);
    AssignWin_s0065_a070(&mWinGameplayContainer, mLayout->FindWindowByID(0x65bd7c8, 1));
    ((G*)this)->FUN_00657ad0(0);

    if (mP90) {
        fF0 = (char)vci0(mP90, 0x74);
        fF1 = (char)vci0(mP90, 0x78);
        fF2 = (char)vci0(mP90, 0x6c);
        fF3 = (char)vci0(mP90, 0x60);
    }

    AssignWin_s0065_a070(&mWinName, mLayout->FindWindowByID(0x643e520, 1));
    if (mWinName) {
        int v;
        if (fF2 == 0) v = 0;
        else v = fF6 ? 1 : 0;
        vc2_s0065_a070(mWinName, 0x7c, 1, v);
    }

    AssignWin_s0065_a070(&mWinRelationship, mLayout->FindWindowByID(0xb497717e, 1));
    AssignWin_s0065_a070(&mWinStatsContainer, mLayout->FindWindowByID(0x67c6707, 1));

    uint32_t id = 0x56e3f98;
    if (mWinRelationship && mWinStatsContainer) {
        if (fF1 == 0) {
            vc2_s0065_a070(mWinRelationship, 0x7c, 1, 1);
            vc2_s0065_a070(mWinStatsContainer, 0x7c, 1, 0);
        }
        else if (fF3 == 0) {
            vc2_s0065_a070(mWinRelationship, 0x7c, 1, 0);
            vc2_s0065_a070(mWinStatsContainer, 0x7c, 1, 0);
        }
        else if (fF0 != 0) {
            vc2_s0065_a070(mWinRelationship, 0x7c, 1, 1);
            vc2_s0065_a070(mWinStatsContainer, 0x7c, 1, 0);
        }
        else {
            vc2_s0065_a070(mWinRelationship, 0x7c, 1, 0);
            vc2_s0065_a070(mWinStatsContainer, 0x7c, 1, 1);
            id = 0x681e037;
        }
    }
    AssignWin_s0065_a070(&mWinIdentityColor, mLayout->FindWindowByID((int)id, 1));

    int uv = 0;
    if (mP90) uv = vci0(mP90, 0x70);
    if (mWinIdentityColor) vc2_s0065_a070(mWinIdentityColor, 0x7c, 1, uv);

    AssignWin_s0065_a070(&mVerbCollection, mLayout->FindWindowByID(0x65be2b8, 1));
    if (mVerbCollection) vc2_s0065_a070(mVerbCollection, 0x7c, 1, 0);

    AssignWin_s0065_a070(&mP78, mLayout->FindWindowByID(0xf45696c1, 1));
    if (mP78) {
        void* w = vcp2_s0065_a070(mP78, 0xf0, 0x3ed7919, 1);
        AssignWin_s0065_a070(&mP7c, w);
    }
    else {
        AssignWin_s0065_a070(&mP7c, 0);
    }
    AssignWin_s0065_a070(&mP80, mLayout->FindWindowByID(0x7c7f748, 1));
    if (mP80) {
        void* w = vcp2_s0065_a070(mP80, 0xf0, 0x3ed7919, 1);
        AssignWin_s0065_a070(&mP84, w);
    }
    else {
        AssignWin_s0065_a070(&mP84, 0);
    }

    if (fFD) {
        bool direct = false;
        if (mP90 != 0) {
            int a = vci0(mP90, 0x40);
            if (FUN_00552300(a) == 1) direct = true;
            else if (vci0(mP90, 0x38) == 0x7fffffff) direct = true;
        }
        if (direct) {
            ((G*)this)->FUN_00659ec0();
        }
        else if (g_pAppProperties->GetDescription(0xb4daca6a) != 0) {
            ((G*)this)->FUN_00659ec0();
        }
    }

    if (mP90 == 0 || vci0(mP90, 0x34) == 0) {
        AssignWin_s0065_a070(&mAssetData, mLayout->FindWindowByID(0x5dd6448, 1));
        if (mAssetData) vc2_s0065_a070(mAssetData, 0x7c, 1, 0);
        fF5 = 1;
        return;
    }

    AssignWin_s0065_a070(&mAssetData, mLayout->FindWindowByID(0x5dd6448, 1));
    if (mAssetData) {
        vc2_s0065_a070(mAssetData, 0x7c, 1, 1);
        if (mWinLoading) vc2_s0065_a070(mWinLoading, 0x7c, 1, 0);
    }
    AssignWin_s0065_a070(&mP6c, mLayout->FindWindowByID(0x5dd6760, 1));
    if (mP6c) {
        void* w = vcp0_s0065_a070(mP90, 0x30);
        if (w == 0) w = (void*)0x13ec468;
        vc1p_s0065_a070(mP6c, 0x80, w);
    }
    AssignWin_s0065_a070(&mP70, mLayout->FindWindowByID(0x5dd0da8, 1));
    if (mP70) {
        vc1_s0065_a070(mP70, 0x5c, vci0(mP90, 0x34));
    }
    AssignWin_s0065_a070(&mP74, mLayout->FindWindowByID(0x5dd2988, 1));
    if (mP74) vc2_s0065_a070(mP74, 0x7c, 1, 0);
    ((G*)this)->FUN_00657e60();
    fF5 = 1;
}



// @ 0x0065a990
void cSPUIAssetView_s0065_a070::Update(unsigned int dt, bool b)
{
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
        AssignWin_s0065_a070(&mWinGameplayName, w);
        vc2_s0065_a070(mWinGameplayName, 0x7c, 0x10, 1);
        vc1_s0065_a070(mWinGameplayName, 0x5c, (int)0x88ffffff);
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
            vc1_s0065_a070(mP88, 0x1c, (int)dt);
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
                        vc1_s0065_a070(mWinLocked, 0x80, arr[0]);
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


// @ 0x0065af90
void SiblingWin::FUN_0065af90(bool active, int)
{
  m17 = active;
  ResourceKey k;
  v3c(&k);
  if (k.a == g_key_1526560.a && k.b == g_key_1526560.b && k.c == g_key_1526560.c && active) {
    if ((int)(((int*)g_15fa01c - (int*)g_15fa018)) <= (int)g_15f9f40_s0065_af90)
      FUN_0065aed0((int)g_15f9f40_s0065_af90 + 1);
    ILayoutObj* pNew = (ILayoutObj*)g_15fa018[g_15f9f40_s0065_af90];
    ILayoutObj* pOld = mpLayout;
    g_15f9f40_s0065_af90 = g_15f9f40_s0065_af90 + 1;
    if (pNew != pOld) {
      if (pNew)
        pNew->a1();
      mpLayout = pNew;
      if (pOld)
        pOld->a2();
    }
    m1c = 1;
  } else {
    void* obj = operator_new_ea(0x18, "Sporepedia", 0, 0, 0, 0);
    ILayoutObj* pNew = obj ? (ILayoutObj*)LayoutCtor18() : 0;
    ILayoutObj* pOld = mpLayout;
    if (pNew != pOld) {
      if (pNew)
        pNew->a1();
      mpLayout = pNew;
      if (pOld)
        pOld->a2();
    }
    mpLayout->a43();  // placeholder for Init
    m1c = 0;
  }
  mpLayout->a65(mpParent);
  mpLayout->a66((void*)&FUN_00657420);
  v40();
  if (m54) {
    ILayoutObj* p = (ILayoutObj*)m54;
    int v = p->a43();  // 0x10 slot accessor stand-in
    (void)v;
    if (p->a43()) {
      ILayoutObj* q = (ILayoutObj*)p->a43();
      q->a56();
      ILayoutObj* r = (ILayoutObj*)m54;
      m54 = 0;
      r->a1();
    }
  }
  v38(mf4);
}
