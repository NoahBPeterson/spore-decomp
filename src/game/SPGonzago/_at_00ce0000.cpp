// src/game/SPGonzago/_at_00ce0000.cpp -- migrated from slice(s) s00cec6d0, s00ce90c0, s00ce8160, s00ce60c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00ce0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "cSPUILayout.h"
#include "SP/cGameData.h"
#include "SP/cPlanetModel.h"
#include "SP/cGameNounManager.h"
#include "SP/cString.h"

// ---- items of slice s00ce60c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
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
}
namespace SP {
struct cMassArg {
    uint8_t mPad00[0x554];                                   // +0x00 .. +0x553
    float   mValue554;                                       // +0x554
    float   mValue558;                                       // +0x558
};
}
// ---- items of slice s00ce60c0 end

// ---- items of slice s00ce8160 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s00ce8160 end

// ---- items of slice s00ce90c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Vec4 { float x, y, z, w; };
struct CIcon {
    void  Refresh();          // 0x00e21960
    void  RefreshAlt();       // 0x00e21980
    void  SetEnabled(u8);     // 0x00e215d0
    void* GetTaskSource();    // 0x00ca71d0
    void* FindItem(void*);    // 0x00e24c90
};
struct cSPUIPosse {
    char   pad00[0xa4];
    void** mpItemBegin;   // +0xa4
    void** mpItemEnd;     // +0xa8
    char   pad_ac[0x1e4 - 0xac];
    u8     mbFlag;        // +0x1e4

    int ItemCount() { return (int)((char*)mpItemEnd - (char*)mpItemBegin) >> 3; }
    void Refresh() { ((CIcon*)this)->Refresh(); }        // 0x00e21960
    void RefreshAlt() { ((CIcon*)this)->RefreshAlt(); }  // 0x00e21980
    void* FindItem(void* key) { return ((CIcon*)this)->FindItem(key); } // 0x00e24c90
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

    // map anchor / node accessors for mVehiclePosseMaps[i]
    // anchor is at +0x80 + i*0x1c ; node key at node+0x14, value at node+0x10.
    char* MapAnchor(int i) { return (char*)this + 0x80 + i * 0x1c; }
    char* MapEnd(int i)    { return (char*)this + 0x80 + i * 0x1c; }

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
// ---- items of slice s00ce90c0 end

// ---- items of slice s00cec6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s00cec6d0 end

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

// @ 0x00ce8d80
void __fastcall FUN_00ce8d80(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  char* m = (char*)FUN_0067ddd0();
  char* a = (char*)((void*(__thiscall*)(void*))(*(void***)m)[0x5c / 4])(m);
  char* b = (char*)((void*(__thiscall*)(void*))(*(void***)a)[0x20 / 4])(a);
  ((void(__thiscall*)(void*, void*))(*(void***)b)[0x1c / 4])(
      b, *(void**)(p + 4));
}

// @ 0x00ce8db0
void* __fastcall FUN_00ce8db0(void* self, void* /*edx*/)
{
  char* p = (char*)self;
  void* g = *(void**)(p + 0x64);
  if (g != 0) {
    return ((void*(__thiscall*)(void*, u32))FUN_00e012b0)(g, 0x5e66e88);
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
      bool doCall = cnt > 0 || visible == 0;
      if (doCall) {
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
  char* p = (char*)self;
  void* win = *(void**)(p + 0xf0);
  if (win != 0) {
    FUN_00ce8f70(obj, win);
  }
}

// @ 0x00ce9380
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
