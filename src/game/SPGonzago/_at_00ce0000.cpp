#include "game/types.h"
#include <math.h>

namespace SP {
struct cMassArg;

struct cTribeTokenTranslator {
    uint8_t mPad00[0x0c];                                    // +0x00 .. +0x0b
    float   mValue0c;                                        // +0x0c
    uint8_t mPad10[0x178];                                   // +0x10 .. +0x187
    float   mValues188[5];                                   // +0x188 .. +0x19b
    float   mValues19c[1];                                   // +0x19c .. +0x19f

    double GetValue188(int index);
    double GetValue19c(int index);
    double ComputeMass(struct cMassArg* arg);
};

struct cTokenTranslatorFields {
    void*     mpVtable0;                                     // +0x00
    uint32_t  mPad04;                                        // +0x04
    uint32_t  mPad08;                                        // +0x08
    uint32_t  mValue0c;                                      // +0x0c
    uint32_t  mValue10;                                      // +0x10
    uint32_t  mValue14;                                      // +0x14
    uint32_t  mValue18;                                      // +0x18
};

struct cMassArg {
    uint8_t mPad00[0x554];                                   // +0x00 .. +0x553
    float   mValue554;                                       // +0x554
    float   mValue558;                                       // +0x558
};

extern "C" void BaseCivTokenTranslatorCtor();                // 0x00b32470
extern "C" double __cdecl ComputeDensity(SP::cMassArg* arg); // 0x00ce6960
extern "C" float gMassScale;                                 // 0x0150c8f8
extern "C" float gMassHalf;                                  // 0x01471064
extern "C" float gMassThreshold;                             // 0x015d9930
}

extern "C" char g_1477a60[];

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
void* __cdecl SP_EventLog();                         // 0x00b3d3e0 SP::EventLog
void* __cdecl FUN_00b3d400();                        // 0x00b3d400 mission card panel accessor
void  __cdecl FUN_00dd8da0(void* self, u8 v);        // 0x00dd8da0 SP::cSPUIEventLog::SetVisibility
void  __cdecl FUN_00e14c10(void* self, u8 v);        // 0x00e14c10 cUIMissionCardPanel::SetCardsVisibility
void  __cdecl FUN_00e01350(void* self, u8 v);        // 0x00e01350 cSPUIGlobalUI::SetVisibility
void* __cdecl FUN_00e012b0(void* self, u32 id);      // 0x00e012b0 cSPUIGlobalUI::FindWindowByID
void* __cdecl FUN_0067ddd0();                        // 0x0067ddd0 SP::EffectsManager
void  __cdecl FUN_00ce8f70(void* obj, void* win);

// Window id looked up in the global civ UI by FUN_00ce8db0 (name is a guess).
enum { kCivWindowId = 0x5e66e88 };

typedef unsigned int uint;
struct Vec4 { float x, y, z, w; };
struct cSPUIPosse {
    char   pad00[0xa4];
    void** mpItemBegin;   // +0xa4
    void** mpItemEnd;     // +0xa8
    char   pad_ac[0x1e4 - 0xac];
    u8     mbFlag;        // +0x1e4
};
struct cGameData {
    char pad00[0xb1c];
    int  mContinent;   // +0xb1c
    int  mCivIndex;    // +0xb20
    char pad24[0xb68 - 0xb24];
    void* mpField_b68; // +0xb68
    void* mpField_b6c; // +0xb6c
};
struct CDS {
    void*  mpVtbl;                    // +0x00
    char   pad04[0x38 - 4];
    void*  mpIHandlerVtbl;            // +0x38
    u8     mbGodModeActive;           // +0x3c
    int    mGodModeVehiclePurpose;    // +0x40
    int    mGodModeVehicleLocomotion; // +0x44
    uint   mGodModeCiv;               // +0x48
    void*  mAutoHandler0;             // +0x4c
    void*  mAutoHandler4;             // +0x50
    void*  mAutoHandler8;             // +0x54
    void*  mAutoHandlerC;             // +0x58
    void*  mAutoHandler10;            // +0x5c
    void*  mpMode;                    // +0x60
    void*  mpGlobalCivUI;             // +0x64
    int    mDebugAIPage;              // +0x68
    cSPUIPosse* mPosses[4];           // +0x6c
    char   mMaps[4 * 0x1c];           // +0x7c
    void*  mpPosseIconLayout;         // +0xec
    void*  mpMiniMapWin;              // +0xf0
    void*  mpTargetingReticle;        // +0xf4
    void*  mpErrorReticle;            // +0xf8
    void*  mpExtraReticle;            // +0xfc
    void*  mAudioSounds[3];           // +0x100
    void*  mpSelEff0;                 // +0x10c
    void*  mpSelEff1;                 // +0x110
    void*  mpSelEff2;                 // +0x114
    void*  mpSelEff3;                 // +0x118
    void*  mpSelEff4;                 // +0x11c

    void GodModeUpdateReticles();          // 0x00ce90c0
    void AccumulatePosseArea(Vec4* out);   // 0x00ce9380
    void SetVehicleTask(cGameData* data, cGameData* vehicle); // 0x00ce9460
    void ResetPosses();                    // 0x00ce9560
    void UpdateUI(int dummy);              // 0x00ce9590
    void SetReticlesVisible(u8 visible); // 0x00ce96b0
    void ShutdownAll();                    // 0x00ce97e0
    int  HandleMessage(int msgID, void* msg); // 0x00ce9920
    void SelectVehicle(void* vehicle, int flag, int param4); // 0x00ce9b70
    void RefreshVehicleIcons(cGameData* vehicle);   // 0x00ce9c30
    void UpdateVehicleContinent(cGameData* vehicle); // 0x00ce9d30
    void BuildEffectDesc(int type, int variant);     // 0x00ce9e20
};

void  __cdecl operator_delete(void* pBlock);                                        // 0x00f47380
char g_emptyString[2];                  // 0x01667bac ?gEmptyString16@eastl@@3PA_WA
class cTuningString {
public:
    char* mpBegin;                              // +0x00
    char* mpEnd;                                // +0x04
    char* mpEndAlloc;                           // +0x08

    cTuningString()
    {
        mpBegin = g_emptyString;
        mpEnd = g_emptyString;
        mpEndAlloc = g_emptyString + 1;
    }
    ~cTuningString()
    {
        if ((int32_t)mpEndAlloc - (int32_t)mpBegin > 1 && mpBegin != 0)
            operator_delete(mpBegin);
    }
};
namespace SP {
class cBuildingTuning {
public:
    uint8_t       mPad000[0x1c];                // +0x000 .. +0x01b
    cTuningString kSleepBuildingName;           // +0x01c
    uint8_t       mPad028[0x20];                // +0x028 .. +0x047
    cTuningString kEntertainmentBuildingName;   // +0x048
    uint8_t       mPad054[0x14];                // +0x054 .. +0x067
    cTuningString kCulturalBuildingName;        // +0x068
    uint8_t       mPad074[0x24];                // +0x074 .. +0x097
    cTuningString kIndustryBuildingName;        // +0x098
    uint8_t       mPad0a4[0x1c];                // +0x0a4 .. +0x0bf
    cTuningString kFoodBuildingName;            // +0x0c0
    uint8_t       mPad0cc[0x14];                // +0x0cc .. +0x0df
    cTuningString kDiplomaticBuildingName;      // +0x0e0
    uint8_t       mPad0ec[0x3c];                // +0x0ec .. +0x127
    cTuningString kMilitaryBuildingName;        // +0x128
    uint8_t       mPad134[0x0c];                // +0x134 .. +0x13f
    cTuningString kDefenseBuildingName;         // +0x140
    uint8_t       mPad14c[0x08];                // +0x14c .. +0x153
    cTuningString kMissionBuildingName;         // +0x154

    cBuildingTuning();                                                  // 0x00cece70
    ~cBuildingTuning();                                                 // 0x00cecd50
};
}

// ---- items of slice s00ce6a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IFace {
    virtual void AddRef();
    virtual void Release();
};
struct Sub {
    char mPad[0xc];
    int mCount;          // +0x0c, object +0xa8
    void DoNuke(int n);  // 0x009a9600
};
struct Obj {
    char mPad00[0x80];
    IFace* mp80;         // +0x80
    IFace* mp84;         // +0x84
    IFace* mp88;         // +0x88
    IFace* mp8c;         // +0x8c
    char mPad90[0x9c - 0x90];
    Sub mSub;            // +0x9c
    void FUN_00ce6a90();
};
// ---- items of slice s00ce6a90 end

// @ 0x00ce6610
void* __fastcall TribeTokenTranslatorCtor(SP::cTokenTranslatorFields* self)
{
    ((void (__thiscall*)(void*))SP::BaseCivTokenTranslatorCtor)(self);
    self->mValue0c = 0;
    self->mValue10 = 0;
    self->mValue14 = 0;
    self->mValue18 = 0;
    self->mpVtable0 = (void*)g_1477a60;
    return self;
}

// @ 0x00ce68f0
double SP::cTribeTokenTranslator::GetValue188(int index)
{
    return mValues188[index];
}

// @ 0x00ce6910
double SP::cTribeTokenTranslator::GetValue19c(int index)
{
    return mValues19c[index];
}

// @ 0x00ce6a40
// The original was built as one /GL module with its cdecl callee ComputeDensity and linked with /LTCG, which
// lets it keep `this` in ecx and `arg` in edx across that call (the callee provably leaves both alone). A
// single-object compile must preserve both across a cdecl call, so it spills them to esi/edi and cannot be
// byte-exact here; the logic below is the original's.
double __fastcall ComputeMass(SP::cTribeTokenTranslator* self, int, SP::cMassArg* arg)
{
    double density = SP::ComputeDensity(arg);
    const float* pValue = &self->mValue0c;
    if (SP::gMassThreshold > self->mValue0c)
        pValue = &SP::gMassThreshold;
    float a = arg->mValue554;
    float b = arg->mValue558;
    double radial = sqrt(a * a + b * b);
    return ((density * SP::gMassScale) * *pValue) * radial * SP::gMassHalf;
}

// @ 0x00ce6a90
void Obj::FUN_00ce6a90()
{
    Sub* sub = &mSub;
    int count = sub->mCount;
    sub->DoNuke(count);
    IFace* p8c = mp8c;
    if (p8c)
        p8c->Release();
    IFace* p88 = mp88;
    if (p88)
        p88->Release();
    IFace* p84 = mp84;
    if (p84)
        p84->Release();
    IFace* p80 = mp80;
    if (p80)
        p80->Release();
}

// @ 0x00ce8d80
void __fastcall FUN_00ce8d80(void* self, void* /*edx*/)
{
  char* m = (char*)FUN_0067ddd0();
  char* a = (char*)((void*(__thiscall*)(void*))(*(void***)m)[0x5c / 4])(m);
  char* b = (char*)((void*(__thiscall*)(void*))(*(void***)a)[0x20 / 4])(a);
  ((void(__thiscall*)(void*, void*))(*(void***)b)[0x1c / 4])(
      b, *(void**)((char*)self + 4));
}

// @ 0x00ce8db0
void* __fastcall FUN_00ce8db0(void* self, void* /*edx*/)
{
  void* g = *(void**)((char*)self + 0x64);
  if (g != 0) {
    return ((void*(__thiscall*)(void*, u32))FUN_00e012b0)(g, kCivWindowId);
  }
  return 0;
}

// @ 0x00ce8ee0
void __fastcall FUN_00ce8ee0(void* self, void* /*edx*/, u8 visible)
{
  char* p = (char*)self;
  void* gui = *(void**)(p + 0x64);
  if (gui != 0) {
    ((void(__thiscall*)(void*, u8))FUN_00e01350)(gui, visible);
  }
  char* win = *(char**)(p + 0xf0);
  if (win != 0) {
    char* inner = win + 4;
    ((void(__thiscall*)(void*, int, u8))(*(void***)inner)[0x7c / 4])(inner, 1, visible);
  }
  char* it = p + 0x6c;
  int n = 4;
  do {
    char* slot = *(char**)it;
    if (slot != 0) {
      u32 cnt = (u32)((s32)(*(u32*)(slot + 0xa8) - *(u32*)(slot + 0xa4)) >> 3);
      if (cnt > 0 || !visible) {
        ((void(__thiscall*)(void*, u8))(*(void***)slot)[0xc0 / 4])(slot, visible);
      }
    }
    it += 4;
    n--;
  } while (n != 0);
  ((void(__thiscall*)(void*, u8))FUN_00dd8da0)(SP_EventLog(), visible);
  char* pp = (char*)FUN_00b3d400();
  if (pp != 0) {
    ((void(__thiscall*)(void*, u8))FUN_00e14c10)((void*)FUN_00b3d400(), visible);
  }
}

// @ 0x00ce90a0
void __fastcall FUN_00ce90a0(void* self, void* /*edx*/, void* obj)
{
  void* win = *(void**)((char*)self + 0xf0);
  if (win != 0) {
    FUN_00ce8f70(obj, win);
  }
}

// 0x00ce9380: not byte-exact; the byte-exact version is the lifted one in match/slices/s00ce9380/s00ce9380.cpp
void CDS::AccumulatePosseArea(Vec4* out)
{
    int i;
    u8 bFirst = 0;
    for (i = 0; i < 4; i++) {
        cSPUIPosse* p = mPosses[i];
        if (p == 0 || p->mbFlag == 0) continue;
        if (bFirst) {
            Vec4 tmp;
            Vec4* r = ((Vec4*(__thiscall*)(void*, Vec4*))
                       (*(void**)(*(char**)p + 0x9c)))(p, &tmp);
            if (r->x <= out->x) out->x = r->x;
            if (r->y <= out->y) out->y = r->y;
            if (out->z <= r->z) out->z = r->z;
            if (out->w <= r->w) out->w = r->w;
        } else {
            Vec4 tmp;
            Vec4* r = ((Vec4*(__thiscall*)(void*, Vec4*))
                       (*(void**)(*(char**)p + 0x9c)))(p, &tmp);
            out->x = r->x;
            bFirst = 1;
            out->y = r->y;
            out->z = r->z;
            out->w = r->w;
        }
    }
}

// @ 0x00cecd50
namespace SP {
cBuildingTuning::~cBuildingTuning()
{
}
}  // namespace SP

// @ 0x00cece70
namespace SP {
cBuildingTuning::cBuildingTuning()
{
}
}  // namespace SP
