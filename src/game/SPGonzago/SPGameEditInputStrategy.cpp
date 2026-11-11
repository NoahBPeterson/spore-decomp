// src/game/SPGonzago/SPGameEditInputStrategy.cpp -- migrated from slice(s) s00d1afe0, s00d197a0, s00d18df0, s00d178a0, s00d1a2b0, s00d16f40, s00d160c0, s00d15440, s00d14460, s00cd16a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameEditInputStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include <stddef.h>
#include "SP/cGameEditInputStrategy.h"
#include "cSPUILayout.h"
#include <math.h>
#include "SP/cPropertyManager.h"
#include <stdlib.h>
#include "EA/UTFWinControls/IWinComboBox.h"
#include "EA/UTFWinControls/IWinScrollbar.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/ResourceMan/Key.h"
#include "cSPVector3.h"
#include "SP/cHerd.h"
#include "SP/cPropertyList.h"
#include "SP/cGonzagoTimer.h"
#include "EA/UTFWinControls/IWinGrid.h"
#include "SP/cITerrainSphere.h"
#include "EA/UTFWinControls/IWinTextEdit.h"
#include <intrin.h>
#include "EA/DateTime/DateTime.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void operator_delete(void* p);                    // 0x00f47380

// ---- items of slice s00cd16a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
struct cNested1c {
    uint32_t mPad00[3];                                      // +0x00 .. +0x0b
    void*    mpValue0c;                                      // +0x0c

    void Release(void* value);                               // 0x00e4b990
};
}
namespace Simulator {
struct cSub04 {
    uint32_t  mPad00[3];                                     // +0x00 .. +0x0b
    void*     mpValue0c;                                     // +0x0c
    uint32_t  mPad10[3];                                     // +0x10 .. +0x1b
    cNested1c mNested1c;                                     // +0x1c

    void Release(void* value);                               // 0x00b1b830
};
}
namespace Simulator {
struct cScenarioEditModeInputStrategy {
    void*    mpVtable;                                       // +0x00
    cSub04   mSub;                                           // +0x04

    void* Destroy(uint8_t flags);
};
}
extern "C" void operator_delete(void* p);                    // 0x00f47380
// ---- items of slice s00cd16a0 end

// ---- items of slice s00d14460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) uint32_t __cdecl wide_to_ulong(const wchar_t* pText, wchar_t** ppEnd, int32_t nBase);   // msvcr90!wcstoul
extern "C" __declspec(dllimport) int __cdecl wide_compare(const wchar_t* pA, const wchar_t* pB);  // msvcr90!wcscmp
extern "C" __declspec(dllimport) double __cdecl wide_to_double(const wchar_t* pText, wchar_t** ppEnd);   // msvcr90!wcstod
extern const char* kTemplateName;                           // 0x015825e4
struct cVec3 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
};
struct cVec4 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
    float w;                                                // +0x0c
};
struct cSpatial {
    virtual void  p000();                                   // +0x00
    virtual void  p004();                                   // +0x04
    virtual void  p008();                                   // +0x08
    virtual void  p00c();                                   // +0x0c
    virtual void  p010();                                   // +0x10
    virtual void  p014();                                   // +0x14
    virtual void  p018();                                   // +0x18
    virtual void  p01c();                                   // +0x1c
    virtual void  p020();                                   // +0x20
    virtual void  p024();                                   // +0x24
    virtual void  p028();                                   // +0x28
    virtual void* GetPosition();                            // +0x2c
    virtual void  p030();                                   // +0x30
    virtual void  p034();                                   // +0x34
    virtual void  SetPosition(const void* pPosition);       // +0x38
    virtual void  SetOrientation(const void* pMatrix);      // +0x3c
};
struct cNoun {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04 (release)
    virtual void* v008();                                   // +0x08
    virtual void* v00c(uint32_t nType);                     // +0x0c (cast)
    virtual void  v010();                                   // +0x10
    virtual void  v014();                                   // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void  v038();                                   // +0x38
    virtual void  v03c();                                   // +0x3c
    virtual void  v040();                                   // +0x40
    virtual void  v044();                                   // +0x44
    virtual void  v048();                                   // +0x48
    virtual void  v04c();                                   // +0x4c
    virtual void  v050();                                   // +0x50
    virtual void  v054();                                   // +0x54
    virtual void  v058();                                   // +0x58
    virtual void  v05c();                                   // +0x5c
    virtual void  v060();                                   // +0x60
    virtual void  v064();                                   // +0x64
    virtual void  v068();                                   // +0x68
    virtual void  v06c();                                   // +0x6c
    virtual void  v070();                                   // +0x70
    virtual void  v074();                                   // +0x74
    virtual void  v078();                                   // +0x78
    uint8_t       mPad004[0x30];                            // +0x04 .. +0x33
    cSpatial      mSpatial;                                 // +0x34
    uint8_t       mPad038[0xd0];                            // +0x38 .. +0x107
    int32_t       mDefA;                                    // +0x108
    int32_t       mDefB;                                    // +0x10c
    int32_t       mDefC;                                    // +0x110
    int32_t       mDefD;                                    // +0x114
    int32_t       mValueCount;                              // +0x118
    int32_t       mValues[64];                              // +0x11c
};
struct cTerrainCursor {
    virtual void  t000();                                   // +0x00
    virtual void  t004();                                   // +0x04
    virtual void  t008();                                   // +0x08
    virtual void  t00c();                                   // +0x0c
    virtual void  t010();                                   // +0x10
    virtual void  t014();                                   // +0x14
    virtual void  t018();                                   // +0x18
    virtual void  t01c();                                   // +0x1c
    virtual void  t020();                                   // +0x20
    virtual void  t024();                                   // +0x24
    virtual void  t028();                                   // +0x28
    virtual void  t02c();                                   // +0x2c
    virtual void  t030();                                   // +0x30
    virtual void  t034();                                   // +0x34
    virtual void  t038();                                   // +0x38
    virtual void  t03c();                                   // +0x3c
    virtual void  t040();                                   // +0x40
    virtual void  t044();                                   // +0x44
    virtual void  t048();                                   // +0x48
    virtual void  t04c();                                   // +0x4c
    virtual void  t050();                                   // +0x50
    virtual void  t054();                                   // +0x54
    virtual void  t058();                                   // +0x58
    virtual void  t05c();                                   // +0x5c
    virtual void  t060();                                   // +0x60
    virtual void  t064();                                   // +0x64
    virtual void  t068();                                   // +0x68
    virtual void  t06c();                                   // +0x6c
    virtual int32_t t070();                                 // +0x70
    virtual void  t074();                                   // +0x74
    virtual void  t078();                                   // +0x78
    virtual void  t07c();                                   // +0x7c
    virtual void  t080();                                   // +0x80
    virtual void  t084();                                   // +0x84
    virtual void  t088();                                   // +0x88
    virtual void  t08c();                                   // +0x8c
    virtual void  t090();                                   // +0x90
    virtual void  t094();                                   // +0x94
    virtual void  t098();                                   // +0x98
    virtual void  t09c();                                   // +0x9c
    virtual void  t0a0();                                   // +0xa0
    virtual void  t0a4();                                   // +0xa4
    virtual void  t0a8();                                   // +0xa8
    virtual void  t0ac(float fValue);                       // +0xac
    virtual void  t0b0(float fValue);                       // +0xb0
    virtual void  t0b4();                                   // +0xb4
    virtual void  t0b8(int32_t nMode);                      // +0xb8
};
struct cParser;
struct cArguments;
struct cArgumentSpec {
    uint8_t mPad00[0xc8];                                   // +0x00 .. +0xc7

    void  Init(bool bFlag);                                 // 0x0083a9f0
    void  Parse(cArguments* pArguments, cParser* pParser);   // 0x0083b9d0
    void  Done();                                           // 0x00405050
    const char* HelpString(const char* pName, int32_t nFlags);   // 0x0083a2f0
};
struct cArguments {
    uint8_t mPad00[0x40];                                   // +0x00 .. +0x3f

    void  Init();                                           // 0x00837ff0
    void  Done();                                           // 0x00837fa0
    void  SplitIntoArguments(const wchar_t* pText);         // 0x008383c0
    void* MainArguments(int32_t nMin);                      // 0x00838320
    void* MainArguments(void** ppOut, int32_t nA, int32_t nB);   // 0x00838020
};
struct cParser {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04
    virtual void  v008();                                   // +0x08
    virtual void  v00c();                                   // +0x0c
    virtual void  v010();                                   // +0x10
    virtual void* v014(void* pKey, void* pValue);           // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void* v038();                                   // +0x38
    virtual void  v03c(void* pArg);                         // +0x3c
    virtual void  v040();                                   // +0x40
    virtual void  v044();                                   // +0x44
    virtual void  v048();                                   // +0x48
    virtual void  v04c();                                   // +0x4c
    virtual void  v050();                                   // +0x50
    virtual void  v054();                                   // +0x54
    virtual void  v058();                                   // +0x58
    virtual void  v05c();                                   // +0x5c
    virtual void  v060();                                   // +0x60
    virtual void  v064();                                   // +0x64
    virtual void  v068();                                   // +0x68
    virtual void  v06c();                                   // +0x6c
    virtual void  v070();                                   // +0x70
    virtual void  v074();                                   // +0x74
    virtual void  v078();                                   // +0x78
    virtual void  v07c();                                   // +0x7c
    virtual void  v080();                                   // +0x80
    virtual void  v084();                                   // +0x84
    virtual void  v088();                                   // +0x88
    virtual void  v08c();                                   // +0x8c
    virtual void* v090(const void* pArg, const char* pText);   // +0x90
    virtual bool  v094(const wchar_t* pArg);                // +0x94
    virtual float v098(const wchar_t* pArg);                // +0x98
    virtual void* v09c(const wchar_t* pArg);                // +0x9c
    virtual void  v0a0();                                   // +0xa0
    virtual void  v0a4();                                   // +0xa4
    virtual void* v0a8(void* pOut, const void* pArg);       // +0xa8
    virtual void* v0ac(void* pOut, const void* pArg);       // +0xac
    virtual void  v0b0();                                   // +0xb0
    virtual void  v0b4();                                   // +0xb4
    virtual void  v0b8();                                   // +0xb8
    virtual void  v0bc(const wchar_t* pName);               // +0xbc
    virtual void  v0c0();                                   // +0xc0
    virtual void* v0c4();                                   // +0xc4
};
struct cCameraCtl {
    virtual void  v000();                                   // +0x00
    virtual void  v004();                                   // +0x04
    virtual void  v008();                                   // +0x08
    virtual void  v00c();                                   // +0x0c
    virtual void  v010();                                   // +0x10
    virtual void  v014();                                   // +0x14
    virtual void  v018();                                   // +0x18
    virtual void  v01c();                                   // +0x1c
    virtual void  v020();                                   // +0x20
    virtual void  v024();                                   // +0x24
    virtual void  v028();                                   // +0x28
    virtual void  v02c();                                   // +0x2c
    virtual void  v030();                                   // +0x30
    virtual void  v034();                                   // +0x34
    virtual void  v038();                                   // +0x38

    void  GetForward(cVec3* pForward);                      // 0x00b13a10
    void  BlendTo(const void* pBlend, int32_t nFlag);       // 0x00b12dd0
    void  LookAt(float x, float y, float z);                // 0x00b10760
};
struct cCurMgr {
    bool FindLocal(uint32_t nID);                           // 0x00801bb0
};
struct cTerraformingManager {
    void SetMode(int32_t nMode);                            // 0x00bc08d0
};
void* __cdecl operator_new(uint32_t nSize, const char* pFile, int32_t a, int32_t b,
                           const char* pAlloc, int32_t nLine);      // 0x00f473a0
cCameraCtl* __cdecl GetCameraCtl();                         // 0x00b3d280
void* __cdecl SP_GetGameTerrainCursor_s00d1_4460();                    // 0x00b30d70
void* __cdecl SP_TerraformingManager();                     // 0x00b3d430
void* __cdecl SP_CheatManager();                            // 0x0067de20
void* __cdecl SP_ResourceManager();                         // 0x0067dcd0
int32_t __cdecl SP_OpenRecordAsStream(const void* pKey, int32_t* pOut);   // 0x00686490
void  __cdecl SP_EraseEntry(int32_t nRecord);               // 0x006861d0
void* __cdecl ArgScript_CreateParser();                     // 0x008408d0
int32_t __cdecl FUN_00b99530(int32_t nA, int32_t nB, int32_t nC);   // 0x00b99530
void   __cdecl FUN_00ba1280();                              // 0x00ba1280
void*  __cdecl FUN_0067cab0();                               // 0x0067cab0
struct cCommandGameplayMarker_s00d1_4460 {
    void*          mpVTable;                                // +0x000
    cParser*       mpParser;                                // +0x004
    uint8_t        mPad008[0x08];                           // +0x008 .. +0x00f
    cArgumentSpec  mArgSpec;                                // +0x010
    cArguments     mArguments;                              // +0x0d8
    int32_t        mValueCount;                             // +0x118
    int32_t        mType;                                   // +0x11c
    int32_t        mID;                                     // +0x120
    int32_t        mDefinitionID;                           // +0x124
    int32_t        mGroupID;                                // +0x128
    cVec3          mPosition;                               // +0x12c
    cVec4          mOrientation;                            // +0x138
    cNoun*         mpGameplayMarker;                        // +0x148

    void* Init();                                           // 0x00d14e50
    void* Destroy(uint8_t nFlags);                          // 0x00d14f00
    const char* Description(int32_t nFlags);                // 0x00d14460
    void  SetFromArguments(cArguments* pArguments);         // 0x00d144d0
    void  OnEndParse(bool bCommit);                         // 0x00d14650
    void  SpawnMarker(cArguments* pArguments);              // 0x00d14830

    static void* ParseTypeEnum(const char* pName);          // 0x00d14600
};
struct cCommandGameplayMarkerTemplate : cCommandGameplayMarker_s00d1_4460 {
    cVec3  mAlphaVector;                                    // +0x14c
    cVec3  mBetaVector;                                     // +0x158
    float  mAlpha;                                          // +0x164
    float  mBeta;                                           // +0x168

    void* Init(const cVec3* pAlpha, const cVec3* pBeta);    // 0x00d14f70
    bool  Parse(const wchar_t** ppArguments);               // 0x00d14690
    void  UpdateMarker(cArguments* pArguments);             // 0x00d14a60
};
// ---- items of slice s00d14460 end

// ---- items of slice s00d15440 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" wchar_t DAT_01479b30[] = L"LevelEditor";// 0x01479b30  tuning set name
extern "C" void* SP_cPlanetModel_DirectionToSurfacePosition(void* pModel, void* pOut, void* pDir);
extern "C" void* SP_cPlanetModel_BuildSurfaceOrientation(void* pModel, void* pOut, void* pPos);
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct Vec3 { float x, y, z; };
struct Obj;
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pi)(void*, int);
typedef void  (__thiscall *Fn_v_pii)(void*, int, int);
typedef void  (__thiscall *Fn_v_piii)(void*, int, int, int);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_ppb)(void*, bool, void*);
typedef void  (__thiscall *Fn_v_pff)(void*, float, float);
typedef Obj* (__thiscall *Fn_p_p)(void*);
typedef Obj* (__thiscall *Fn_p_pi)(void*, int);
typedef bool  (__thiscall *Fn_b_p)(void*);
typedef bool  (__thiscall *Fn_b_pui)(void*, u32, void**);
extern "C" float DAT_0169dc28 = 0.0f;              // 0x0169dc28  selection anchor (x)
extern "C" float DAT_0169dc2c = 0.0f;              // 0x0169dc2c  selection anchor (y)
extern "C" float DAT_0169dc30 = 0.0f;              // 0x0169dc30  selection anchor (z)
extern "C" void* DAT_0169dc64 = 0;                 // 0x0169dc64  current marker owner
extern "C" int*  DAT_0169dc68 = 0;                 // 0x0169dc68  marker entry vector begin
extern "C" int*  DAT_0169dc6c = 0;                 // 0x0169dc6c  marker entry vector end
extern "C" float DAT_013ec4b8 = 1e-08f;            // 0x013ec4b8  normalisation epsilon
extern "C" float DAT_013ec478 = 0.05f;             // 0x013ec478  spin step (radians)
extern "C" float DAT_01470f1c = 2.0f;              // 0x01470f1c  squared-scale constant
extern "C" float DAT_014763b8 = 0.0f;              // 0x014763b8  label area (w)
extern "C" float DAT_013ebc4c = 0.0f;              // 0x013ebc4c  label area (h)
extern "C" float DAT_013f08e8 = 160.0f;            // 0x013f08e8  label x advance
extern "C" float DAT_01486ebc = 250.0f;            // 0x01486ebc  combo box width
extern "C" float DAT_013eecd8 = 20.0f;             // 0x013eecd8  combo box height
extern "C" float DAT_01479c0c = 270.0f;            // 0x01479c0c  combo box y advance
struct Obj {
    void* m_slot30();                       // vftable slot 0x30
    Vec3* m_position();                     // vftable slot 0x2c
};
struct cSPUILayout_s00d1_5440 {
    u8    mPad00[0x24];
    Obj*  FindWindowByID(int id, int flag); // 0x008105b0
    void  SetVisibility(int v);             // 0x00810590
};
struct cGameNounManager_s00d1_5440 {
    void RemoveNoun(Obj* p);                // 0x00b225d0
};
Obj*  __cdecl SP_PlanetModel();                       // 0x00b3d350
Obj*  __cdecl SP_PropertyManager();                   // 0x0067de30
Obj*  __cdecl SP_GetGameTerrainCursor();              // 0x00b30d70
cGameNounManager_s00d1_5440* __cdecl SP_NounManager(void* pNoun); // 0x00b3d300
void* __cdecl FUN_00d1bf00();                         // 0x00d1bf00  GetEditSelection
u32   __cdecl EA_Hash_FNV1_String16(const wchar_t* p, u32 seed, int flag); // 0x00932f30
void  __cdecl EA_Messaging_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
void* __cdecl FUN_009512c0();                         // 0x009512c0
void* __cdecl FUN_009512d0(int size, int align, const char* name, void* pPool); // 0x009512d0
Obj*  __cdecl WinText_CreateDefault(int a, u32 b);    // 0x00989130  WinText::CreateDefault
Obj*  __cdecl ComboBoxDrawable_ctor(Obj* pThis);      // 0x00969000  UI::ComboBoxDrawable::c
Obj*  __cdecl ScrollbarDrawable_ctor(Obj* pThis);     // 0x009838a0  UI::ScrollbarDrawable::c
Obj*  __cdecl WinComboBox_ctor(Obj* pThis);           // 0x00969450  WinComboBox::c
namespace SP {
struct cGameEditInputStrategy_s00d1_5440 {
    u8    mPad00[0x40];
    u8    mSub40[0x0c];              // +0x040  sub-object handed to window slot 0x108
    void* mpField4C;                 // +0x04c
    u8    mPad50[0x54 - 0x50];
    void* mpNoun;                    // +0x054  noun (vftable slot 0x58 query)
    u8    mPad58[0x88 - 0x58];
    void* mpField88;                 // +0x088  slot 0x1c0 target
    u8    mPad8c[0xa4 - 0x8c];
    void* mpFieldA4;                 // +0x0a4
    void* mpFieldA8;                 // +0x0a8  slot 0xd8 marker-list owner
    u8    mPadAc[0xc4 - 0xac];
    Vec3  mVecC4;                    // +0x0c4
    float mQuatD0[4];                // +0x0d0
    cSPUILayout_s00d1_5440 mLayout;             // +0x0e0
    void* mpHandler;                 // +0x104
    void* mHandlerArgs[6];           // +0x108

    void  FUN_00d15440(Vec3* pTarget);
    void  FUN_00d15550();
    void  FUN_00d15600();  // 0x00d15600 (SP::cGameEditInputStrategy::FUN_00d15600)
    void  FUN_00d15630(void* a1, float* pX, float* pY);
    float FUN_00d15780(void* a1, float* pX, float* pY);
    void  FUN_00d15980(void* a1, void* pObj);
    void  FUN_00d15a10(void* p);
    u32   StartSelection(void* p, u8 flag, u32 a3);  // 0x00d15ab0 (SP::cGameEditInputStrategy::StartSelection)
    u32   FUN_00d15af0(void* p, u8 flag, u32 a3);  // 0x00d15af0 (SP::cGameEditInputStrategy::FUN_00d15af0)
    u32   GetGameplayMarkerTypeFromUI();  // 0x00d15fb0 (SP::cGameEditInputStrategy::GetGameplayMarkerTypeFromUI)
};
}
u32 __cdecl GetGameplayMarkerClassId(u32 classId);
// ---- items of slice s00d15440 end

// ---- items of slice s00d160c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVec3i {
    int x;                              // 0x00
    int y;                              // 0x04
    int z;                              // 0x08
};
struct cWString {
    void* mpBegin;                      // 0x00
    void* mpEnd;                        // 0x04
    void* mpCap;                        // 0x08
    void* mpField0c;                    // 0x0c
};
struct cConvertArg {
    void* mpValue;                      // 0x00
    void* mpTag04;                      // 0x04
    void* mpScratch08;                  // 0x08
};
struct cStrCmp {
    void*    mpField00;                 // 0x00
    void*    mpConv04;                  // 0x04
    cWString mStr08;                    // 0x08
    cWString mStr18;                    // 0x18

    bool operator()(u32 a, u32 b);      // 0x00d16760
};
struct cGameEditInputStrategy;
void __fastcall cStrCmp_Destroy(cStrCmp* p);                                   // 0x00d167e0
int  __cdecl StringCompare(const void* b1, const void* e1,
                           const void* b2, const void* e2);                    // 0x00576970
void* __cdecl ObjectError();                                                   // 0x008de1a0
void __cdecl operator delete[](void* p);                                       // 0x00f47380
static inline void VT_7C_2(void* p, void* a, void* b)
{
    ((void (__thiscall*)(void*, void*, void*))(*(void***)p)[0x1f])(p, a, b);
}
static inline void VT_60_1(void* p, void* a, int b)
{
    ((void (__thiscall*)(void*, void*, int))(*(void***)p)[0x18])(p, a, b);
}
static inline void cStrCmp_FreeStrings(cStrCmp& comp)
{
    if ((int)(((char*)comp.mStr18.mpCap - (char*)comp.mStr18.mpBegin) & 0xfffffffe) > 2
        && comp.mStr18.mpBegin != 0)
        operator delete[](comp.mStr18.mpBegin);
    if ((int)(((char*)comp.mStr08.mpCap - (char*)comp.mStr08.mpBegin) & 0xfffffffe) > 2
        && comp.mStr08.mpBegin != 0)
        operator delete[](comp.mStr08.mpBegin);
}
struct cGameEditInputStrategy {
    u8      mPad0000[0x7c];
    void*   mpField7c;                  // 0x7c  planet-name text edit object
    u8      mPad0080[0xf8 - 0x80];
    cVec3i  mPlanetF8;                  // 0xf8  selected planet

    void SetPlanet(const cVec3i* planet);   // 0x00d16b90
};
// ---- items of slice s00d160c0 end

// ---- items of slice s00d16f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_01479b60[];                 // 0x01479b60  handler id table (0x23 entries)
extern void*    g_01440aec;                   // 0x01440aec  element container base
extern uint32_t FNV1_String16(const wchar_t* text, uint32_t seed, int mode);  // 0x00932f30
extern uint32_t FUN_00d15b30(uint32_t markerType);            // 0x00d15b30 GetGameplayMarkerClassId
extern char     FUN_00d16620(uint32_t markerType, int* out);  // 0x00d16620 GetGameplayMarkerTypes
#pragma pack(push, 4)
struct Vector3    { float x, y, z; };
struct Quaternion { float x, y, z, w; };
class cUiObject {
public:
    virtual void v00();                                       // 0x00
    virtual void v04();                                       // 0x04  Release
    virtual void v08();                                       // 0x08
    virtual cUiObject* v0c(uint32_t id);                      // 0x0c  GetWindowByID
    virtual cUiObject* v10();                                 // 0x10  sub-object getter
    virtual void v14();                                       // 0x14
    virtual void v18(uint32_t text);                          // 0x18
    virtual uint32_t v1c();                                   // 0x1c
    virtual void v20(uint32_t text);                          // 0x20
    virtual void v24(cUiObject* target, uint32_t id);         // 0x24  register message handler
    virtual void v28();                                       // 0x28
    virtual void* v2c();                                      // 0x2c
    virtual void* v30();                                      // 0x30
    virtual void v34();                                       // 0x34
    virtual void v38();                                       // 0x38
    virtual void v3c(void* transform);                        // 0x3c
    virtual void* v40();                                      // 0x40
    virtual void v44(int a, int b);                           // 0x44
    virtual void v48();                                       // 0x48
    virtual void v4c();                                       // 0x4c
    virtual void v50(uint32_t color);                         // 0x50
    virtual const wchar_t* v54();                             // 0x54
    virtual cUiObject* v58();                                 // 0x58
    virtual void v5c();                                       // 0x5c
    virtual void v60(const float* rect);                      // 0x60
    virtual void v64(float a, float b);                       // 0x64
    virtual void v68();                                       // 0x68
    virtual void v6c();                                       // 0x6c
    virtual void v70();                                       // 0x70
    virtual void v74();                                       // 0x74
    virtual void v78();                                       // 0x78
    virtual void v7c(int a, int b);                           // 0x7c
    virtual void v80(const wchar_t* text);                    // 0x80
    virtual void v84();                                       // 0x84
    virtual void v88();                                       // 0x88
    virtual void v8c();                                       // 0x8c
    virtual void v90();                                       // 0x90
    virtual void v94(int a, int b);                           // 0x94
    virtual void v98();                                       // 0x98
    virtual void v9c();                                       // 0x9c
    virtual void va0();                                       // 0xa0
    virtual void va4();                                       // 0xa4
    virtual void va8();                                       // 0xa8
    virtual void vac();                                       // 0xac
    virtual void vb0();                                       // 0xb0
    virtual void vb4();                                       // 0xb4
    virtual cUiObject* vb8(uint32_t id);                      // 0xb8
    virtual void vbc();                                       // 0xbc
    virtual void vc0(int count);                              // 0xc0
    virtual void vc4();                                       // 0xc4
    virtual void vc8();                                       // 0xc8
    virtual void vcc(void* out);                              // 0xcc
    virtual void vd0(void* out);                              // 0xd0
    virtual void vd4();                                       // 0xd4
    virtual void vd8(void* item);                             // 0xd8
    virtual void vdc();                                       // 0xdc
    virtual void ve0();                                       // 0xe0
    virtual void ve4();                                       // 0xe4
};
class cUiObjectB {
public:
    virtual void v00();                                       // 0x00
    virtual void v04();                                       // 0x04  Release
    virtual void v08();                                       // 0x08
    virtual cUiObjectB* v0c(uint32_t id);                     // 0x0c
    virtual cUiObjectB* v10();                                // 0x10
    virtual void v14();                                       // 0x14
    virtual void v18(uint32_t text);                          // 0x18
    virtual uint32_t v1c();                                   // 0x1c
    virtual void v20(uint32_t index, uint32_t color);         // 0x20
    virtual void v24(cUiObjectB* target, uint32_t id);        // 0x24
    virtual void v28();                                       // 0x28
    virtual void* v2c(void* arg);                             // 0x2c
    virtual void* v30(float value);                           // 0x30
    virtual void v34();                                       // 0x34
    virtual void v38();                                       // 0x38
    virtual void v3c(void* transform);                        // 0x3c
    virtual void* v40(int arg);                               // 0x40
    virtual void v44(int a, int b);                           // 0x44
    virtual void v48();                                       // 0x48
    virtual void v4c();                                       // 0x4c
    virtual void v50(uint32_t color);                         // 0x50
    virtual const wchar_t* v54(uint32_t color);               // 0x54
    virtual cUiObjectB* v58();                                // 0x58
    virtual void v5c();                                       // 0x5c
    virtual void v60(const float* rect);                      // 0x60
    virtual void v64(float a, float b);                       // 0x64
    virtual void v68();                                       // 0x68
    virtual void v6c();                                       // 0x6c
    virtual void v70();                                       // 0x70
    virtual void v74();                                       // 0x74
    virtual void v78();                                       // 0x78
    virtual void v7c(int a, int b);                           // 0x7c
    virtual void v80(const wchar_t* text);                    // 0x80
    virtual void v84();                                       // 0x84
    virtual void v88();                                       // 0x88
    virtual void v8c();                                       // 0x8c
    virtual void v90();                                       // 0x90
    virtual void v94(int a, int b);                           // 0x94
    virtual void v98();                                       // 0x98
    virtual void v9c();                                       // 0x9c
    virtual void va0();                                       // 0xa0
    virtual void va4();                                       // 0xa4
    virtual void va8();                                       // 0xa8
    virtual void vac();                                       // 0xac
    virtual void vb0();                                       // 0xb0
    virtual void vb4();                                       // 0xb4
    virtual cUiObjectB* vb8(uint32_t id);                     // 0xb8
    virtual void vbc();                                       // 0xbc
    virtual void vc0(int count);                              // 0xc0
    virtual void vc4();                                       // 0xc4
    virtual void vc8();                                       // 0xc8
    virtual void vcc(void* out);                              // 0xcc
    virtual void vd0(void* out);                              // 0xd0
    virtual void vd4();                                       // 0xd4
    virtual void vd8(void* item);                             // 0xd8
    virtual void vdc();                                       // 0xdc
    virtual void ve0();                                       // 0xe0
    virtual void ve4();                                       // 0xe4
};
class cPropertyManager_s00d1_6f40 {
public:
    virtual void p00();                                       // 0x00
    virtual void p04();                                       // 0x04
    virtual void p08();                                       // 0x08
    virtual void p0c();                                       // 0x0c
    virtual void p10();                                       // 0x10
    virtual void p14();                                       // 0x14
    virtual void p18();                                       // 0x18
    virtual void p1c();                                       // 0x1c
    virtual void p20();                                       // 0x20
    virtual void p24();                                       // 0x24
    virtual void p28();                                       // 0x28
    virtual void p2c();                                       // 0x2c
    virtual char p30(uint32_t hash, cUiObject** out);         // 0x30
};
struct AutoRefCount {
    cUiObject* mpObject;
    void Assign(cUiObject* value);                            // 0x00b5f950  operator=
};
class cMarkerInfo {
public:
    char      mPad00[0x34];
    cUiObject mSub34;                                         // +0x34
    char      mPad38[0x1a4 - 0x38];
    cUiObject* mpField1a4;                                    // +0x1a4
};
namespace SP {
    class cPlanetModel_s00d1_6f40 {
    public:
        uint32_t GetPlanetKey();                              // 0x00b7e380
        void*    FUN_00b7f1f0(const void* ctx, void* a2, void* a3);  // 0x00b7f1f0
    };
}
namespace SP {
    cPlanetModel_s00d1_6f40* PlanetModel();                              // 0x00b3d350
}
namespace SP {
    cUiObject*    MessageServer();                            // 0x0067dcc0
}
namespace SP {
    cPropertyManager_s00d1_6f40* PropertyManager();                      // 0x0067de30
}
namespace SP {
    void QuaternionFromDirections(Quaternion* out, const Vector3* a,
                                  const Vector3* b);          // 0x00698180
}
class cSPUILayout_s00d1_6f40 {
public:
    cUiObject* FindWindowByID(uint32_t id, int includeChildren);   // 0x008105b0
};
class cGameEditModeStrategy {
public:
    char     mPad00[0x108];
    uint32_t mMarkerType;                                     // +0x108
    uint32_t mMarkerClassId;                                  // +0x10c
    uint32_t mField110;                                       // +0x110
    uint32_t mMarkerValue;                                    // +0x114
    char     mPad118[4];
    int      mMarkerValues[32];                               // +0x11c
    static void LoadScenario(cGameEditModeStrategy* self, int a, int b);   // 0x00b931c0
};
class cGameEditInputStrategy_s00d1_6f40 {
public:
    char        mPad00[0x3c];
    cUiObject   mHandler;                     // +0x3c   message handler target
    char        mPad40[0x54 - 0x40];
    cUiObject*  mpSelectedObjectManipulator;  // +0x54
    char        mPad58[0xa4 - 0x58];
    cUiObject*  mpUIA4;                       // +0xa4
    cUiObject*  mpScrollBarA8;                // +0xa8
    char        mPadAc[0xc4 - 0xac];
    Vector3     mFacing;                      // +0xc4   the marker's current facing
    Vector3     mFrameD0;                     // +0xd0   transform input for FUN_007dcb00
    char        mPadDc[0xe0 - 0xdc];
    cSPUILayout_s00d1_6f40 mLayout;                      // +0xe0
    char        mPadE4[0x104 - 0xe4];
    cUiObject*  mpServer;                     // +0x104  handler registration installed on the server
    cUiObject*  mpHandlerTarget;              // +0x108
    void*       mpHandlerTable;               // +0x10c  the id table at 0x01479b60
    int         mHandlerCount;                // +0x110
    uint32_t    mField114;                    // +0x114

    void FUN_00d16f40(Vector3* target);                       // 0x00d16f40
    void Activate();                                          // 0x00d17250
    void CommitChangesToGameplayMarker(cGameEditModeStrategy* scenario, char apply);  // 0x00d172d0
    void AddGameplayMarkerValue(int type, uint32_t color, int* value,
                                float* posX, float* posY);     // 0x00d17550
    uint32_t GetGameplayMarkerTypeFromUI();                   // 0x00d15fb0
    uint32_t FUN_00d16820();                                  // 0x00d16820
    void SetPlanet(uint32_t key);                             // 0x00d16b90
    void FUN_00d15780(int type, void* a3, void* a4);          // 0x00d15780
};
extern void     FUN_00d15350(cGameEditModeStrategy* scenario, uint32_t index, int value,
                             const wchar_t* text);            // 0x00d15350
extern void*    FUN_007dcb00(void* out, const void* frame, const Quaternion* q);  // 0x007dcb00
const float kMarkerAxisX  = 1.0f;
const float kMarkerAxisY  = 0.0f;
const float kMarkerAxisZ  = 0.0f;
const float kDotThreshold = 0.99f;            // 0x013ef480
// ---- items of slice s00d16f40 end

// ---- items of slice s00d1a2b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern int g_1440aec;
#pragma intrinsic(memcpy)
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);
namespace eastl {
extern char gEmptyString[];   // 0x01667bac
}
namespace eastl {
class allocator_s00d1_a2b0 { public:
    void* allocate(unsigned int n) {
        return operator new[](n, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    void deallocate(void* p, unsigned int) { operator delete[](p); }
};
}
namespace eastl {
template <class T> struct basic_string_s00d1_a2b0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00d1_a2b0 mAllocator;

    basic_string_s00d1_a2b0() { AllocateSelf(); }
    __forceinline basic_string_s00d1_a2b0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p, p + CharStrlen(p)); }
    ~basic_string_s00d1_a2b0() { DeallocateSelf(); }

    static unsigned int CharStrlen(const T* p) {
        const T* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return (unsigned int)(pCurrent - p);
    }
    void AllocateSelf() {
        mpBegin = (T*)gEmptyString;
        mpEnd = (T*)gEmptyString;
        mpCapacity = (T*)gEmptyString + 1;
    }
    void AllocateSelf(unsigned int n) {
        if (n > 1) {
            mpBegin = DoAllocate(n);
            mpEnd = mpBegin;
            mpCapacity = mpBegin + n;
        } else
            AllocateSelf();
    }
    T* DoAllocate(unsigned int n) { return (T*)mAllocator.allocate(n * sizeof(T)); }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void RangeInitialize(const T* pBegin, const T* pEnd) {
        const unsigned int n = (unsigned int)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, n * sizeof(T));
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    const T* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
    basic_string_s00d1_a2b0& assign(const T* pBegin, const T* pEnd);   // 0x00423650 (wchar_t)
    basic_string_s00d1_a2b0& operator=(const basic_string_s00d1_a2b0& x) {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string_s00d1_a2b0& sprintf(const T* pFormat, ...);           // 0x0041e050 (wchar_t)
};
}
namespace eastl {
typedef basic_string_s00d1_a2b0<char> string8_s00d1_a2b0;
}
namespace eastl {
typedef basic_string_s00d1_a2b0<wchar_t> string16_s00d1_a2b0;
}
namespace eastl {
template <class It, class Compare> void sort(It first, It last, Compare compare);
}
struct IdVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    IdVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~IdVector() {
        if (mpBegin && mpBegin[-1] != 0)
            operator delete[](mpBegin);
    }
};
namespace EA {
eastl::string16_s00d1_a2b0 ConvertToString16(const eastl::string8_s00d1_a2b0& s);   // 0x0093c6d0
}
namespace EA {
eastl::string8_s00d1_a2b0 ConvertToString8(const eastl::string16_s00d1_a2b0& s);    // 0x0093c570
}
namespace EA {
namespace Hash {
 uint32_t FNV1_String16(const wchar_t* p, uint32_t seed, int caseMode);   // 0x00932f30
}
}
namespace EA {
namespace IO {
int SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
              wchar_t* pExtension, int flags);                                           // 0x00930180
}
}
namespace EA {
namespace ResourceMan {
class Key_s00d1_a2b0 { public:
    uint32_t instanceID, typeID, groupID;
    Key_s00d1_a2b0(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
}
}
namespace EA {
namespace ResourceMan {
struct IResourceManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
    virtual bool GetFileName(const Key_s00d1_a2b0& key, eastl::string16_s00d1_a2b0& dst);   // +0x7c
};
}
}
namespace EA {
namespace ResourceMan {
IResourceManager* GetManager();   // 0x0067dcd0
}
}
inline uint32_t id(const wchar_t* p) { return EA::Hash::FNV1_String16(p, 0x811c9dc5, 1); }
struct Property {
    union {
        struct { void* mpData; uint32_t mnItemSize; uint32_t mnItemCount; };
        uint32_t mValue[4];
    };
    short mnFlags;     // +0x10
    unsigned short mnType;   // +0x12
    uint32_t GetItemCount() const { return (mnFlags & 0x30) ? mnItemCount : (mnType != 0); }
    void* GetValue() { return (mnFlags & 0x30) ? mpData : (mnType ? (void*)this : 0); }
};
struct PropertyList {
    virtual int AddRef();
    virtual int Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool HasProperty(uint32_t propID);          // +0x1c
virtual void v20();
virtual void v24();
    virtual Property* GetProperty(uint32_t propID);     // +0x28
};
struct IPropertyManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual bool GetPropertyList(uint32_t instanceID, PropertyList** ppList);   // +0x30
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual void GetPropertyListIDs(uint32_t groupID, IdVector& dst);           // +0x48
};
namespace SP {
IPropertyManager* PropertyManager_s00d1_a2b0();   // 0x0067de30
}
namespace SP {
bool GetPropertyAsString8(PropertyList* pList, uint32_t propID, eastl::string8_s00d1_a2b0& dst);   // 0x006a13b0
}
namespace SP {
bool GetPropertyAsUint32Array(PropertyList* pList, uint32_t propID, uint32_t& count, uint32_t*& pArray);   // 0x006a0840
}
namespace SP {
namespace {
struct cPropertyListNameSort {
    cPropertyListNameSort(uint32_t groupID);   // 0x00d196f0
    uint32_t mData[10];
};
uint32_t GetGameplayMarkerClassId(uint32_t typeHash);   // 0x00d15b30
}
}
template <class T> struct AutoRefCount_s00d1_a2b0 {
    T* mpObject;
    AutoRefCount_s00d1_a2b0() : mpObject(0) {}
    AutoRefCount_s00d1_a2b0(T* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount_s00d1_a2b0() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s00d1_a2b0& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** AsPointer() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
struct Rectangle { float x1, y1, x2, y2; };
struct IWindow_s00d1_a2b0 {
    virtual int AddRef();                                         // +0x00
    virtual int Release();                                        // +0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                          // +0x0c
    virtual IWindow_s00d1_a2b0* GetParent();                                 // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual const Rectangle& GetArea();                           // +0x34
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void SetArea(const Rectangle& area);                  // +0x60
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                   // +0x7c
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
    virtual void** GetChildrenBegin(void*** pResult);             // +0xcc (sret)
    virtual void** GetChildrenEnd(void*** pResult);               // +0xd0 (sret)
virtual void vd4();
virtual void vd8();
virtual void vdc();
    virtual void DisposeWindowFamily(IWindow_s00d1_a2b0* pChild);            // +0xe0
};
struct IWinComboBox_s00d1_a2b0 {
    virtual int AddRef();
    virtual int Release();
virtual void v08();
virtual void v0c();
    virtual IWindow_s00d1_a2b0* ToWindow();                                  // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void AddItem(const wchar_t* text);                    // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
    virtual void SetSelection(int index, bool notify);           // +0x44
};
struct IWinScrollbar_s00d1_a2b0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual void SetValue(int value, bool notify);               // +0x24
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual void SetMaxValue(int value, bool notify);            // +0x34
};
class cSPUILayout_s00d1_a2b0 { public:
    IWindow_s00d1_a2b0* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
    uint32_t mData[3];
};
struct NounEntry {
    uint32_t mUnk0, mUnk4;
    uint32_t mClassID;          // +0x08
    uint32_t mInstanceID;       // +0x0c
    uint32_t mUnk10;
    PropertyList* mpPropList;   // +0x14
    NounEntry* mpNext;          // +0x18
};
struct NounEntryIterator {
    NounEntry* mpNode;
    NounEntry** mpBucket;
    NounEntryIterator(NounEntry** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    NounEntryIterator(NounEntry* pNode, NounEntry** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    NounEntryIterator& operator++() { increment(); return *this; }
    NounEntry* operator->() const { return mpNode; }
    bool operator!=(const NounEntryIterator& x) const { return mpNode != x.mpNode; }
};
struct NounEntryTable {
    uint32_t mUnk0;
    NounEntry** mpBucketArray;   // +0x04
    uint32_t mnBucketCount;      // +0x08
    NounEntryIterator begin() {
        NounEntryIterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    NounEntryIterator end() { return NounEntryIterator(mpBucketArray + mnBucketCount); }
};
struct Noun {
    uint32_t mUnk[3];
    PropertyList* mpPropList;   // +0x0c
};
struct cNounManager {
    uint32_t pad[8];
    NounEntryTable mEntries;   // +0x20
    Noun* GetNoun(uint32_t classID, uint32_t instanceID);   // 0x00b21000
};
namespace SP {
 cNounManager* NounManager();   // 0x00b3d300
}
const char* GetNounClassName(uint32_t classID);  // 0x00b21490
struct cCommandGameplayMarker {
    uint32_t pad[0x108 / 4];
    uint32_t mType;             // +0x108 (hash of the type name)
    uint32_t mDefClassID;       // +0x10c
    uint32_t mDefInstanceID;    // +0x110
    uint32_t mGroup;            // +0x114
    uint32_t mValueCount;       // +0x118
    uint32_t mValues[32];       // +0x11c
    static int ParseTypeEnum(const char* p);   // 0x00d14600
};
void SetGameplayMarkerDefaultValue(cCommandGameplayMarker* pMarker, uint32_t index, int type, const wchar_t* pDefault);
namespace SP {
class cGameEditInputStrategy_s00d1_a2b0 {
public:
    void ShowGameplayMarkerProperties(cCommandGameplayMarker* pMarker, bool bReadOnly, bool bSetDefaults);  // 0x00d1a2b0 (SP::cGameEditInputStrategy::ShowGameplayMarkerProperties)
    void AddLabel(const wchar_t* text, float& x, float& y);                                      // 0x00d15630
    void AddComboBox(uint32_t controlID, float& x, float& y);                                    // 0x00d15780
    void AddTextEdit(uint32_t controlID, int type, uint32_t* pValue, float& x, float& y);       // 0x00d17550

    IWinComboBox_s00d1_a2b0* FindComboBox(uint32_t controlID) {
        IWindow_s00d1_a2b0* pWindow = mLayout.FindWindowByID(controlID, true);
        return pWindow ? (IWinComboBox_s00d1_a2b0*)pWindow->Cast(0x2f5528d9) : 0;
    }

    uint32_t pad[0xa4 / 4];
    IWindow_s00d1_a2b0* mGameplayMarkerRoot;              // +0xa4
    IWindow_s00d1_a2b0* mGameplayMarkerArea;              // +0xa8
    IWinScrollbar_s00d1_a2b0* mGameplayMarkerScrollbar;   // +0xac
    uint32_t pad2[(0xe0 - 0xb0) / 4];
    cSPUILayout_s00d1_a2b0 mLayout;                       // +0xe0
};  // namespace SP
}
// ---- items of slice s00d1a2b0 end

// ---- items of slice s00d178a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void operator_delete__(void* p);            // 0x00f47380
extern uint8_t    g_169dc20;                       // 0x0169dc20  "herd needs an update" flag
extern float      g_f169dc94;                      // 0x0169dc94  two pi
extern float      g_f1470f1c;                      // 0x01470f1c  2.0f
extern float      g_f1582664;                      // 0x01582664  half turn
namespace eastl {
class allocator_s00d1_78a0 {
public:
    void deallocate(void* p, unsigned int) { operator_delete__(p); }
};
}
namespace eastl {
template <class T> struct basic_string_s00d1_78a0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00d1_78a0 mAllocator;

    void AllocateSelf(unsigned int n);             // 0x00429760 (out of line)

    basic_string_s00d1_78a0(const basic_string_s00d1_78a0& x) : mpBegin(0), mpEnd(0), mpCapacity(0) {
        RangeInitialize(x.mpBegin, x.mpEnd);
    }
    ~basic_string_s00d1_78a0() { DeallocateSelf(); }

    void RangeInitialize(const T* pBegin, const T* pEnd) {
        const int n = (int)(pEnd - pBegin);
        AllocateSelf(n + 1);
        T* p = mpBegin;
        memcpy(p, pBegin, n * sizeof(T));
        mpEnd = p + n;
        *mpEnd = 0;
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
};
}
namespace eastl {
typedef basic_string_s00d1_78a0<wchar_t> string16_s00d1_78a0;
}
struct Property_s00d1_78a0 {
    union {
        struct { void* mpData; uint32_t mnItemSize; uint32_t mnItemCount; };
        uint32_t mValue[4];
    };
    unsigned short mnFlags;                        // +0x10  (0x30 mask => pointer valued)
    unsigned short mnType;                         // +0x12
    void* GetValue() { return (mnFlags & 0x30) ? mpData : (mnType != 0 ? (void*)this : 0); }
};
namespace EA {
namespace ResourceMan {
class IResourceManager_s00d1_78a0;
}
}
struct cPropertyListNameSort_s00d1_78a0 {
    uint32_t mGroupID;                             // +0x00
    EA::ResourceMan::IResourceManager_s00d1_78a0* mpResMan;   // +0x04
    eastl::string16_s00d1_78a0 mNameA;                        // +0x08
    eastl::string16_s00d1_78a0 mNameB;                        // +0x18

    cPropertyListNameSort_s00d1_78a0(const cPropertyListNameSort_s00d1_78a0& x);      // 0x00d18000
    bool operator()(uint32_t a, uint32_t b) const;              // 0x00d16760
};
void AdjustHeapHole(uint32_t* first, int topIndex, int len, int holeIndex, uint32_t value,
                    cPropertyListNameSort_s00d1_78a0 compare);              // 0x00d180c0
void SiftUp(uint32_t* first, int topIndex, int holeIndex, uint32_t value,
            cPropertyListNameSort_s00d1_78a0 compare);                      // 0x00d16eb0
void AdjustHeap(uint32_t* first, uint32_t* last, cPropertyListNameSort_s00d1_78a0 compare);  // 0x00d18180
class cUiObject_s00d1_78a0;
class cPropertyList;
class cUiObject_s00d1_78a0 {
public:
    virtual void v00();                            // 0x00
    virtual void v04();                            // 0x04
    virtual void v08();                            // 0x08
    virtual cUiObject_s00d1_78a0* v0c(uint32_t id);           // 0x0c  child by id
    virtual cPropertyList* v10();                  // 0x10  property list
    virtual void v14();                            // 0x14
    virtual void v18();                            // 0x18
    virtual Property_s00d1_78a0* v1c(uint32_t index);         // 0x1c
    virtual uint32_t v20();                        // 0x20  class id
    virtual void v24();                            // 0x24
    virtual void v28();                            // 0x28
    virtual void v2c();                            // 0x2c
    virtual void v30();                            // 0x30
    virtual void v34();                            // 0x34
    virtual uint32_t v38();                        // 0x38
    virtual void v3c();                            // 0x3c
    virtual void v40();                            // 0x40
    virtual void v44();                            // 0x44
    virtual void v48();                            // 0x48
    virtual void v4c();                            // 0x4c
    virtual void v50();                            // 0x50
    virtual void v54(cUiObject_s00d1_78a0* obj, int flag);    // 0x54  bind the manipulated object
    virtual cUiObject_s00d1_78a0* v58();                      // 0x58  bound object
    virtual void v5c();                            // 0x5c
    virtual void v60();                            // 0x60
    virtual void v64();                            // 0x64
    virtual void v68();                            // 0x68
    virtual void v6c();                            // 0x6c
    virtual void v70();                            // 0x70
    virtual void v74();                            // 0x74
    virtual void v78();                            // 0x78
    virtual void v7c();                            // 0x7c
    virtual void v80();                            // 0x80
    virtual void v84();                            // 0x84
    virtual void v88();                            // 0x88
    virtual void v8c();                            // 0x8c
    virtual void v90();                            // 0x90
    virtual void v94();                            // 0x94
    virtual void v98();                            // 0x98
    virtual void v9c();                            // 0x9c
    virtual void va0();                            // 0xa0
    virtual void va4();                            // 0xa4
    virtual void va8();                            // 0xa8
    virtual void vac();                            // 0xac
    virtual void vb0();                            // 0xb0
    virtual void vb4();                            // 0xb4
    virtual cUiObject_s00d1_78a0* vb8(uint32_t id);           // 0xb8  handler for a script id
    virtual void vbc();                            // 0xbc
};
class cPropertyList {
public:
    virtual void p00();                            // 0x00
    virtual void p04();                            // 0x04
    virtual void p08();                            // 0x08
    virtual void p0c();                            // 0x0c
    virtual void p10();                            // 0x10
    virtual void p14();                            // 0x14
    virtual void p18();                            // 0x18
    virtual Property_s00d1_78a0* v1c(uint32_t index);         // 0x1c
};
class cSpatial_s00d1_78a0 {
public:
    virtual void s00();                            // 0x00
    virtual void s04();                            // 0x04
    virtual void s08();                            // 0x08
    virtual void s0c();                            // 0x0c
    virtual void s10();                            // 0x10
    virtual void s14();                            // 0x14
    virtual void s18();                            // 0x18
    virtual void s1c();                            // 0x1c
    virtual void s20();                            // 0x20
    virtual void s24();                            // 0x24
    virtual void s28();                            // 0x28
    virtual void* v2c();                           // 0x2c  position
    virtual void* v30();                           // 0x30  rotation
    virtual void s34();                            // 0x34
    virtual void v38(void* position);              // 0x38  set position
    virtual void v3c(void* rotation);              // 0x3c  set rotation
    virtual void s40();                            // 0x40
    virtual void s44();                            // 0x44
    virtual void s48();                            // 0x48
    virtual void s4c();                            // 0x4c
    virtual bool v50();                            // 0x50  movable / editable
};
class cMarkerInfo_s00d1_78a0 {
public:
    char      mPad00[0x34];
    cSpatial_s00d1_78a0  mSub34;                              // +0x34
    char      mPad38[0x1a4 - 0x38];
    cUiObject_s00d1_78a0* mpField1a4;                         // +0x1a4
};
class cHerdMember {
public:
    virtual void h00();                            // 0x00
    virtual void h04();                            // 0x04
    virtual void h08();                            // 0x08
    virtual void h0c();                            // 0x0c
    virtual void h10();                            // 0x10
    virtual void h14();                            // 0x14
    virtual void h18();                            // 0x18
    virtual void h1c();                            // 0x1c
    virtual void h20();                            // 0x20
    virtual void h24();                            // 0x24
    virtual void h28();                            // 0x28
    virtual void h2c();                            // 0x2c
    virtual void h30();                            // 0x30
    virtual void h34();                            // 0x34
    virtual void h38();                            // 0x38
    virtual void h3c();                            // 0x3c
    virtual void h40();                            // 0x40
    virtual void h44();                            // 0x44
    virtual void h48();                            // 0x48
    virtual void h4c();                            // 0x4c
    virtual void h50();                            // 0x50
    virtual void h54();                            // 0x54
    virtual void h58();                            // 0x58
    virtual void h5c();                            // 0x5c
    virtual void h60();                            // 0x60
    virtual void h64();                            // 0x64
    virtual void h68();                            // 0x68
    virtual void v6c(int value);                   // 0x6c
    char      mPad04[0xc0 - 0x70];
    cSpatial_s00d1_78a0  mSpatial;                            // +0xc0
};
class cHerd {
public:
    char          mPad00[0x40];
    cHerdMember** mMembersBegin;                   // +0x40
    cHerdMember** mMembersEnd;                     // +0x44
    char          mPad48[0x160 - 0x48];
    uint32_t      mField160;                       // +0x160
    void SetPosition(Vector3* position);           // 0x00c6ba20
};
struct AutoRefCount_s00d1_78a0 {
    cUiObject_s00d1_78a0* mpObject;
    void Assign(cUiObject_s00d1_78a0* value);                 // 0x00c70110
};
class cPlanetModel {
public:
    Vector3*    DirectionToSurfacePosition(Vector3* out, const Vector3* direction);   // 0xb815a0
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* position);   // 0xb7f190
    Quaternion* BuildSurfaceOrientation2(Quaternion* out, const Vector3* position,
                                         const Vector3* up);                         // 0xb7f250
    Vector3*    GetNormalAt(Vector3* out, const Vector3* position);                  // 0xb7e3b0
};
class IReferencePoint {
public:
    virtual void r00();                            // 0x00
    virtual void r04();                            // 0x04
    virtual void r08();                            // 0x08
    virtual void r0c();                            // 0x0c
    virtual void r10();                            // 0x10
    virtual void r14();                            // 0x14
    virtual void r18();                            // 0x18
    virtual void r1c();                            // 0x1c
    virtual void r20();                            // 0x20
    virtual void r24();                            // 0x24
    virtual void r28();                            // 0x28
    virtual void r2c();                            // 0x2c
    virtual void r30();                            // 0x30
    virtual void r34();                            // 0x34
    virtual Vector3 GetPos(int flag, Vector3 offset);   // 0x38
};
class cTimer {
public:
    uint32_t mPad[8];
    void Restart();                                // 0x00bc3130
};
class cGameNounManager {
public:
    void RemoveNoun(cUiObject_s00d1_78a0* noun);              // 0x00b225d0
    cUiObject_s00d1_78a0* CreateRotationRing();               // 0x00d0a610
};
class cGameEditModeStrategy_s00d1_78a0 {
public:
    char         mPad00[0x40];
    cUiObject_s00d1_78a0**  mSelectedBegin;                   // +0x40
    cUiObject_s00d1_78a0**  mSelectedEnd;                     // +0x44
};
class cGameEditInputStrategy_s00d1_78a0 {
public:
    char         mPad00[0x4c];
    AutoRefCount_s00d1_78a0 mpSelectedObject;                 // +0x4c  the object being manipulated
    AutoRefCount_s00d1_78a0 mpField50;                        // +0x50
    cUiObject_s00d1_78a0*   mpSelectedObjectManipulator;      // +0x54
    cTimer       mHoverTimer;                      // +0x58
    char         mPad5c[0xc4 - 0x78];
    Vector3      mFacing;                          // +0xc4
    Vector3      mFrameD0;                         // +0xd0

    void DoObjectManipulation(uint32_t action, cUiObject_s00d1_78a0* message);   // 0x00d178a0
    void FUN_00d15440(Vector3* target);                               // 0x00d15440
    void FUN_00d16f40(Vector3* target);                               // 0x00d16f40
};
extern Vector3    g_v169dc28;                      // 0x0169dc28  reference point offset
extern Vector3    g_v169dc88;                      // 0x0169dc88  world up
extern Vector3    g_v1582668;                      // 0x01582668  spin axis
extern Vector3    g_v1582674;                      // 0x01582674  spin axis
extern IReferencePoint* FUN_00b3d240();            // 0x00b3d240
extern cPlanetModel*    PlanetModel_s00d1_78a0();             // 0x00b3d350
extern cGameNounManager* NounManager_s00d1_78a0();            // 0x00b3d300
extern cGameEditModeStrategy_s00d1_78a0* GetEditSelection();  // 0x00d1bf00
extern cUiObject_s00d1_78a0* RotateObject(AutoRefCount_s00d1_78a0* object);                  // 0x00d15330
extern cUiObject_s00d1_78a0* FUN_00ad7360(cUiObject_s00d1_78a0** slot);                      // 0x00ad7360
extern void*      FUN_00ac80d0(cUiObject_s00d1_78a0* object, uint32_t classId);   // 0x00ac80d0
extern Vector3*   Vector3_Normalize(Vector3* out, const Vector3* in);  // 0x00436ce0
extern Vector3*   FUN_0059aed0(Vector3* out, const Vector3* v, const Quaternion* q);  // 0x0059aed0
extern Quaternion* FUN_0059b060(Quaternion* out, const Vector3* axis, float angle);   // 0x0059b060
extern void*      FUN_007dcb00(void* out, const Quaternion* a, const Quaternion* b);  // 0x007dcb00
extern void       OrthogonalVector(Vector3* out, const Vector3* in);                  // 0x006985b0
extern Quaternion* QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing,
                                             const Vector3* up);                      // 0x0069b600
// ---- items of slice s00d178a0 end

// ---- items of slice s00d18df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void* p);   // 0x00f47380 (operator delete[])
namespace eastl {
class allocator_s00d1_8df0 { public:
    void deallocate(void* p, unsigned int) { operator delete(p); }
};
}
namespace eastl {
template <class T> struct basic_string_s00d1_8df0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator_s00d1_8df0 mAllocator;

    __forceinline basic_string_s00d1_8df0() { AllocateSelf(); }
    ~basic_string_s00d1_8df0() { DeallocateSelf(); }

    void AllocateSelf() {
        mpBegin = (T*)gEmptyString;
        mpEnd = (T*)gEmptyString;
        mpCapacity = (T*)gEmptyString + 1;
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    const T* c_str() const { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }

    void sprintf(const T* fmt, ...);                        // 0x00472fe0 (char) / 0x0041e050 (wchar_t)
    void append_sprintf(const T* fmt, ...);                 // 0x005f9450 (char)
    void append(const T* pBegin, const T* pEnd);            // 0x00455d60 (char)
};
}
namespace eastl {
typedef basic_string_s00d1_8df0<wchar_t> string16_s00d1_8df0;
}
namespace eastl {
typedef basic_string_s00d1_8df0<char> string8_s00d1_8df0;
}
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct Vec3c {                       // Vector3 with a user copy ctor (movss member copies)
    float x, y, z;
    Vec3c() {}
    Vec3c(const Vec3c& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vec3c Scale(const Vec3c& v, const float& s)
{
    Vec3c r;
    r.x = v.x * s;
    r.y = v.y * s;
    r.z = v.z * s;
    return r;
}
inline Vec3c& operator-=(Vec3c& a, const Vec3c& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}
struct ResKey { uint32_t instance, type, group; };
struct IWriter {
    PV8 PV4 PV2                                              // +0x00..+0x34
    virtual void Write(const void* pData, uint32_t size);    // +0x38
};
struct IRefCounted {
    PV
    virtual void AddRef();                                    // +0x04
    virtual void Release();                                   // +0x08
};
struct IFileStream : IRefCounted {
    PV2 PV                                                    // +0x0c..+0x14
    virtual IWriter* GetWriter();                             // +0x18
    PV2
    virtual void Close();                                     // +0x24
};
struct IRecordDB {
    PV8 PV4 PV
    virtual bool OpenRecord(ResKey* key, IFileStream** pStream, int mode, int access, int create,
                            int flags);                       // +0x34
};
struct IResourceManager_s00d1_8df0 {
    PV16 PV8 PV4 PV2                                          // +0x00..+0x74
    virtual void GetKey(ResKey* pKey, const wchar_t* pPath, uint32_t typeID, uint32_t groupID);  // +0x78
};
IResourceManager_s00d1_8df0* GetManager_s00d1_8df0();                               // 0x0067dcd0
IRecordDB* FindRecordDB(ResKey* key);                         // 0x00685d40 (cdecl)
struct IMarkerPart {                                          // sub-object at marker +0x34
    PV8 PV2 PV
    virtual const Vec3* GetPosition();                        // +0x2c
    PV4 PV4
    virtual bool IsPlaced();                                  // +0x50
};
struct cGameplayMarkerCmd {                                   // object returned by Cast(0x36be278)
    uint32_t pad00[13];
    IMarkerPart part;                                         // +0x34
    uint32_t pad38[(0x108 - 0x38) / 4];
    uint32_t ids[4];                                          // +0x108
    uint32_t mCount;                                          // +0x118
    int mValues[32];                                          // +0x11c
};
struct ISelectable {
    PV16 PV16 PV8 PV4 PV2                                     // +0x00..+0xb4
    virtual cGameplayMarkerCmd* Cast(uint32_t typeID);        // +0xb8
};
struct SelectionList {
    ISelectable** mpBegin;                                    // +0x00
    ISelectable** mpEnd;                                      // +0x04
};
struct cEditSelection {
    char pad[0x40];
    SelectionList mSelected;                                  // +0x40
};
cEditSelection* GetEditSelection_s00d1_8df0();                           // 0x00d1bf00
struct cPlanetModel_s00d1_8df0 {
    Vec3c* GetNormalAt(Vec3c* pOut, const Vec3c* pPos);          // 0x00b7e3b0 (thiscall, ret 8)
};
cPlanetModel_s00d1_8df0* PlanetModel_s00d1_8df0();                                  // 0x00b3d350
struct cCameraCtl_s00d1_8df0 {
    void GetDirection(Vec3c* pOut);                            // 0x00b13a10 (thiscall, ret 4)
};
cCameraCtl_s00d1_8df0* GetCameraCtl_s00d1_8df0();                                   // 0x00b3d280
bool __cdecl GetGameplayMarkerTypes(uint32_t id, uint32_t* pTypes);   // 0x00d16620
extern Vec3c gZeroVec3;                                        // 0x0169dc28
template <class T> struct AutoRefCount_s00d1_8df0 {
    T* mpObject;
    AutoRefCount_s00d1_8df0() : mpObject(0) {}
    ~AutoRefCount_s00d1_8df0() { if (mpObject) mpObject->Release(); }
    T** operator&() { return &mpObject; }
    T* operator->() const { return mpObject; }
};
namespace SP {
class cGameEditInputStrategy_s00d1_8df0 { public:
    void DoSaveSelectedFile(eastl::string16_s00d1_8df0* pName);          // 0x00d18df0
};
}
// ---- items of slice s00d18df0 end

// ---- items of slice s00d197a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gIgnoreParam;           // 0x0158265c
extern uint32_t gMarkerVisibilityMode;  // 0x0169dc1c
extern uint8_t gEditorFlag20;           // 0x0169dc20
extern uint8_t gEditorFlag21;           // 0x0169dc21
#define VS1(n) virtual void n();
#define VS4(n) VS1(n##0) VS1(n##1) VS1(n##2) VS1(n##3)
#define VS16(n) VS4(n##a) VS4(n##b) VS4(n##c) VS4(n##d)
struct string16_s00d1_97a0 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16_s00d1_97a0()
    {
        mpBegin = (wchar_t*)eastl::gEmptyString;
        mpEnd = (wchar_t*)eastl::gEmptyString;
        mpCapacity = (wchar_t*)eastl::gEmptyString + 1;
    }
    ~string16_s00d1_97a0() { DeallocateSelf(); }
    void DeallocateSelf();   // 0x00933960
};
class IWindow {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual int GetValue();  // +0x28
    virtual void s2c();
    virtual void s30();
    virtual uint32_t GetText(int index);  // +0x34
    virtual void s38();
    virtual void s3c();
    virtual int GetSelection();  // +0x40
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void SetText(const void* p, int v);  // +0x60
    virtual void SetArea(float x, float y);  // +0x64
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void SetFlag(int flag, int value);  // +0x7c
};
class IGrid {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual bool GetSelected(void** ppItem, int* pIndex);  // +0xa4
    virtual void sa8();
    virtual void sac();
    virtual void sb0();
    virtual void sb4();
    virtual void sb8();
    virtual void sbc();
    virtual void sc0();
    virtual void sc4();
    virtual void sc8();
    virtual void scc();
    virtual void sd0();
    virtual void sd4();
    virtual void sd8();
    virtual void sdc();
    virtual void se0();
    virtual void se4();
    virtual void se8();
    virtual void sec();
    virtual void sf0();
    virtual void sf4();
    virtual void sf8();
    virtual void sfc();
    virtual void s100();
    virtual void s104();
    virtual void s108();
    virtual void s10c();
    virtual void s110();
    virtual void s114();
    virtual void s118();
    virtual void s11c();
    virtual void s120();
    virtual void s124();
    virtual void s128();
    virtual void s12c();
    virtual void s130();
    virtual void s134();
    virtual void s138();
    virtual void s13c();
    virtual void s140();
    virtual void s144();
    virtual void s148();
    virtual void s14c();
    virtual void s150();
    virtual void s154();
    virtual void s158();
    virtual void s15c();
    virtual void s160();
    virtual void s164();
    virtual void s168();
    virtual void s16c();
    virtual void s170();
    virtual void s174();
    virtual void s178();
    virtual void s17c();
    virtual void s180();
    virtual void s184();
    virtual void s188();
    virtual void s18c();
    virtual void s190();
    virtual void s194();
    virtual void s198();
    virtual void s19c();
    virtual void GetItemText(int a, int index, wchar_t** ppText);  // +0x1a0
    virtual void s1a4();
    virtual void s1a8();
    virtual void s1ac();
    virtual void s1b0();
    virtual void s1b4();
    virtual void s1b8();
    virtual void s1bc();
    virtual void s1c0();
    virtual int GetItemKey(int a, int index);  // +0x1c4
};
class IGameInput {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void SetCursorMode(uint32_t id, bool b);  // +0x64
};
class IMessageServer {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void Post(uint32_t id, void* pMsg, int a, int b);  // +0x18
};
class IPlanetTerrain {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void SetSomething(uint32_t v);  // +0x8c
};
struct SourceRef {
    IWindow* mp;
    SourceRef(IWindow* p);                         // 0x00572660
    SourceRef(const SourceRef& o) : mp(o.mp) {}
};
struct PlanetKey { uint32_t a, b, c; };
class MessageBasicRC5 {
public:
    virtual void s00();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[(0x8 - 0x4) / 4];
    int mValue;                       // +0x08
    uint32_t pad0c;
    int mFlag;                        // +0x10
    uint32_t pad14[(0x30 - 0x14) / 4];
    uint32_t mMessageID;              // +0x30
    uint32_t pad34[3];
    explicit MessageBasicRC5(int a);  // 0x00421c80
};
void* operator new(unsigned int n, const char* name, int a, int b, int c, int d);   // 0x00f473a0
class cCommandGameplayMarker_s00d1_97a0 {
public:
    uint32_t pad00[0x108 / 4];
    uint32_t mMarkerType;             // +0x108
    uint32_t pad10c[(0x124 - 0x10c) / 4];
    uint32_t mShape;                  // +0x124
    uint32_t pad128[(0x19c - 0x128) / 4];
    void* mpFirst;                    // +0x19c
};
class IReleasable {
public:
    VS16(a) VS16(b) VS16(c)
    virtual void ReleaseRef();        // +0xc0
};
struct SelectedRef {
    IReleasable* mpObject;
};
class cNounManager_s00d1_97a0 {
public:
    void FUN_00b25fe0();                              // 0x00b25fe0
    void RemoveNoun(void* pNoun);                     // 0x00b225d0
    void RemoveNounsOfType(uint32_t typeID);          // 0x00b22650
};
class cPlanetModel_s00d1_97a0 {
public:
    uint32_t pad00[0x24 / 4];
    class IPlanetTerrain* mpTerrain;                  // +0x24
    void FUN_00b8c0f0();                              // 0x00b8c0f0
    void FUN_00b8d8a0(const PlanetKey* pKey, int a, int b);   // 0x00b8d8a0 (ret 0xc)
};
class cEditMode {
public:
    void MarkDirty();                                 // 0x00d1bf10
};
cNounManager_s00d1_97a0* NounManager_s00d1_97a0();                          // 0x00b3d300
cPlanetModel_s00d1_97a0* PlanetModel_s00d1_97a0();                          // 0x00b3d350
IGameInput* GameInputManager();                       // 0x00b3d250
IMessageServer* MessageServer_s00d1_97a0();                      // 0x0067dcc0
cEditMode* GetEditMode();                             // 0x00d1bf00
uint32_t HashName(const wchar_t* pName);              // 0x00572c50
uint32_t GetPlanetThing();                            // 0x0067dd50
void PrepareDialog();                                 // 0x00b908c0
int GetCurrentGameModeAlt();                          // 0x00b5b820
void EnterGameMode(int mode);                         // 0x00ba1c60
void LoadScenario(cCommandGameplayMarker_s00d1_97a0* p, uint32_t classId, uint32_t x);   // 0x00b931c0
void SaveScenario(const wchar_t* pName);              // 0x00d1cb00
void InterfaceCast(uint32_t id, int b);               // 0x00d1c610
uint32_t GetGameplayMarkerClassId(uint32_t type);     // 0x00d15b30
struct UIMessage {
    IWindow* mpSource;                  // +0x00
    uint32_t pad04;
    uint32_t mType;                     // +0x08
    uint32_t mParam;                    // +0x0c
};
class cInputStrategyBase {
public:
    virtual void v00();
    uint32_t pad04[(0x3c - 4) / 4];
};
class IHandlerRC4 {
public:
    virtual void h00();
};
class IWinProc_s00d1_97a0 {
public:
    virtual void w00();
    virtual bool HandleUIMessage(IWindow* pWindow, const UIMessage& msg);
};
class RefCountV {
public:
    virtual void r00();
    int mRefCount;
};
class cGameEditInputStrategy_s00d1_97a0 : public cInputStrategyBase, public IHandlerRC4, public IWinProc_s00d1_97a0, public RefCountV {
public:
    SelectedRef mpSelectedObject;                 // +0x4c
    uint32_t pad50;
    void* mpSelectedObjectManipulator;            // +0x54
    uint32_t pad58[(0x78 - 0x58) / 4];
    IWindow* mLevelNameTextEdit;                  // +0x78
    uint32_t pad7c;
    IWindow* mLoadDialogWindow;                   // +0x80
    IWindow* mLoadPlanetDialogWindow;             // +0x84
    IGrid* mGridFileList;                         // +0x88
    IGrid* mPlanetGridFileList;                   // +0x8c
    PlanetKey* mPlanetKeysBegin;                  // +0x90
    uint32_t pad94[(0xa4 - 0x94) / 4];
    IWindow* mGameplayMarkerRoot;                 // +0xa4
    IWindow* mGameplayMarkerArea;                 // +0xa8
    IWindow* mGameplayMarkerScrollbar;            // +0xac
    IWindow* mVisibilityCombo;                    // +0xb0
    IWindow* mRuleOptionsList;                    // +0xb4
    uint32_t padb8;
    IWindow* mTemplateOptionsList;                // +0xbc

    virtual bool HandleUIMessage(IWindow* pWindow, const UIMessage& msg);  // 0x00d197a0 (cGameEditInputStrategy::HandleUIMessage)

    void SetButtonHighlight(SourceRef arg);                           // 0x00d18860
    uint32_t GetGameplayMarkerTypeFromUI();                           // 0x00d15fb0
    uint32_t FUN_00d16820();                                          // 0x00d16820
    void CommitChangesToGameplayMarker(cCommandGameplayMarker_s00d1_97a0* p, bool b);   // 0x00d172d0
    void PopulateLoadDialogGridWithLevels();                          // 0x00d16960
    void PopulateLoadPlanetDialogGrid();                              // 0x00d194c0
    bool GetSaveFileName(string16_s00d1_97a0* pName, int a);                     // 0x00d18b40
    void DoSaveSelectedFile(string16_s00d1_97a0* pName);                         // 0x00d18df0
    void SetPlanet(const PlanetKey* pKey);                            // 0x00d16b90
    void FUN_00d15a10(int v);                                         // 0x00d15a10
    void FUN_00d15600();                                              // 0x00d15600
    static cCommandGameplayMarker_s00d1_97a0* RotateObject(SelectedRef* pSelected);   // 0x00d15330

    void ShowOptionWindows(int templateValue, int ruleValue)
    {
        IWindow* w = mGameplayMarkerRoot;
        if (w)
            w->SetFlag(1, 0);
        w = mTemplateOptionsList;
        if (w)
            w->SetFlag(1, templateValue);
        w = mRuleOptionsList;
        if (w)
            w->SetFlag(1, ruleValue);
    }
};
namespace eastl {
extern void FreeNode(void* p);                       // 0x00F47380
}
namespace eastl {
class allocator_s00d1_97a0 {
public:
    void deallocate(void* p, unsigned int) { FreeNode(p); }
};
}
namespace eastl {
template <class T> struct basic_string_s00d1_97a0 {
    T* mpBegin;                                      // +0x00
    T* mpEnd;                                        // +0x04
    T* mpCapacity;                                   // +0x08
    allocator_s00d1_97a0 mAllocator;                            // +0x0c
    ~basic_string_s00d1_97a0() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
};
}
namespace eastl {
typedef basic_string_s00d1_97a0<wchar_t> string16_s00d1_97a0;
}
// ---- items of slice s00d197a0 end

// ---- items of slice s00d1afe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00d1_afe0 {
    float x, y, z;
    Vector3_s00d1_afe0() {}
    Vector3_s00d1_afe0(const Vector3_s00d1_afe0& v) : x(v.x), y(v.y), z(v.z) {}
};
bool operator!=(const Vector3_s00d1_afe0& a, const Vector3_s00d1_afe0& b); // 0x0041dd30 (out of line)
class IObject {
public:
    virtual int AddRef();               // +0x00
    virtual int Release();              // +0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID); // +0x0c
};
class IWindow_s00d1_afe0 {
public:
    VS4(a)
    VS4(b)
    VS1(c0)
    virtual void SetValue(int value, bool b); // +0x24
    virtual uint32_t GetFlags();               // +0x28
    VS1(c3)
    VS1(d0)
    virtual uint32_t GetText(int index);       // +0x34
    VS1(d2)
    VS1(d3)
    virtual int GetSelection();                // +0x40
    VS4(e)
    VS4(f)
    virtual void SetArea(float x, float y);    // +0x64
    VS1(g2)
    VS1(g3)
    VS1(h0)
    VS1(h1)
    VS1(h2)
    virtual void SetFlag(int flag, int value); // +0x7c
};
class cSPUILayout_s00d1_afe0 {
public:
    uint8_t mData[0x18];
    void Construct();                                          // 0x00810000
    void Destroy();                                            // 0x00811fe0
    IObject* FindWindowByID(uint32_t controlID, bool recursive); // 0x008105b0
};
class cSpatialPart {
public:
    VS4(a)
    VS4(b)
    VS4(c)
    VS1(d0)
    VS1(d1)
    virtual void SetPosition(const Vector3_s00d1_afe0* pPos);       // +0x38
    virtual void SetOrientation(const Quaternion* pQuat); // +0x3c
};
class cCommandGameplayMarker_s00d1_afe0;
class MarkerRef {
public:
    cCommandGameplayMarker_s00d1_afe0* mpObject;
    MarkerRef& operator=(cCommandGameplayMarker_s00d1_afe0* p); // 0x00b5f950
    void Assign(MarkerRef* other);                   // 0x00ac9480
};
class cCommandGameplayMarker_s00d1_afe0 {
public:
    uint32_t pad00[0x34 / 4];
    cSpatialPart mSpatial;            // +0x34
    uint32_t pad38[(0x108 - 0x38) / 4];
    uint32_t mMarkerType;             // +0x108
    uint32_t mField10c;               // +0x10c
    uint32_t mField110;               // +0x110
    uint32_t mMarkerID;               // +0x114
    uint32_t pad118;
    int mGroupIndex;                  // +0x11c
    float mScale;                     // +0x120
    uint32_t mShape;                  // +0x124
    uint32_t pad128[(0x19c - 0x128) / 4];
    MarkerRef mFirst;                 // +0x19c
    MarkerRef mPrev;                  // +0x1a0

    void AddChild(cCommandGameplayMarker_s00d1_afe0* pChild); // 0x00c3eac0
};
struct HighlightArg {
    int mValue;
    HighlightArg(int v) : mValue(v) {}
    HighlightArg(const HighlightArg& o) : mValue(o.mValue) {}
};
class SelectedRef_s00d1_afe0 {
public:
    void* mpObject;
    void SetSelected(cSpatialPart* p); // 0x00c70110
};
class cInputStrategyBase_s00d1_afe0 {
public:
    virtual void v00();
    void SetVtable(void* p) { *reinterpret_cast<void**>(this) = p; }
    uint32_t mField04;
    uint32_t mListHead08;
    uint32_t mListTail0c;
    uint32_t mListCount10;
    uint32_t mListAlloc14;
    uint32_t mListAux18;
    uint32_t mField1c;
    uint32_t mField20;
    IObject* mpEditorMode24;
    IObject* mpEditorAux28;
    uint32_t mField2c;
    uint32_t mField30;
    uint32_t mField34;
    uint32_t mField38;
};
class IMessageHandler {
public:
    virtual void h00();
    virtual void h04();
    virtual void h08();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);
    void SetVtable(void* p) { *reinterpret_cast<void**>(this) = p; }
};
struct cEditSubobject58 {
    uint8_t mData[0x20];
    void Construct();                         // 0x00b63890
    void Destroy();                           // 0x00b638b0
};
void DestroyTransitionHandle(uint32_t handle, uint32_t a, uint32_t b,
                             uint32_t c, uint32_t d);       // 0x00571db0
class cGameEditInputStrategy_s00d1_afe0 : public cInputStrategyBase_s00d1_afe0, public IMessageHandler {
public:
    void* mpVtable40;                      // +0x40
    void* mpVtable44;                      // +0x44
    uint32_t mField48;                     // +0x48
    SelectedRef_s00d1_afe0 mpSelectedObject;          // +0x4c
    IObject* mpField50;                    // +0x50
    uint32_t mField54;                     // +0x54
    cEditSubobject58 mSubobject58;         // +0x58
    IObject* mpField78;                    // +0x78
    IObject* mpField7c;                    // +0x7c
    IObject* mpField80;                    // +0x80
    IObject* mpField84;                    // +0x84
    IObject* mpField88;                    // +0x88
    IObject* mpField8c;                    // +0x8c
    IObject* mpField90;                    // +0x90
    IObject* mpField94;                    // +0x94
    IObject* mpField98;                    // +0x98
    uint32_t mField9c;                     // +0x9c
    uint32_t mFieldA0;                     // +0xa0
    IWindow_s00d1_afe0* mGameplayMarkerRoot;          // +0xa4
    IWindow_s00d1_afe0* mGameplayMarkerArea;          // +0xa8
    IWindow_s00d1_afe0* mGameplayMarkerScrollbar;     // +0xac
    uint32_t padb0;
    IWindow_s00d1_afe0* mRuleOptionsList;             // +0xb4
    IWindow_s00d1_afe0* mTemplateOptions;             // +0xb8
    IWindow_s00d1_afe0* mTemplateOptionsList;         // +0xbc
    IWindow_s00d1_afe0* mPlanetNameEdit;              // +0xc0
    uint32_t mFieldC4;                     // +0xc4
    uint32_t mFieldC8;                     // +0xc8
    uint32_t mFieldCC;                     // +0xcc
    uint32_t mFieldD0;                     // +0xd0
    uint32_t mFieldD4;                     // +0xd4
    uint32_t mFieldD8;                     // +0xd8
    uint32_t mFieldDC;                     // +0xdc
    cSPUILayout_s00d1_afe0 mLayout;                   // +0xe0
    uint32_t mTransitionHandle;            // +0x104
    uint32_t mTransition108;               // +0x108
    uint32_t mTransition10c;               // +0x10c
    uint32_t mTransition110;               // +0x110
    uint32_t mTransition114;               // +0x114

    bool HandleMessage(uint32_t messageID, void* pMessage);  // 0x00d1afe0 (cGameEditInputStrategy::HandleMessage)

    void HotloadLevelEditorProp();                                                      // 0x00d160c0
    void CommitChangesToGameplayMarker(IObject* pMarker, bool b);                       // 0x00d172d0
    void ShowGameplayMarkerProperties(IObject* pMarker, bool bReadOnly, bool bDefaults); // 0x00d1a2b0
    void StartSelection(void* pObject, int value, Vector3_s00d1_afe0* pPos);                       // 0x00d15ab0
    void SelectionDrag(void* pObject, int value, Vector3_s00d1_afe0* pPos);                        // 0x00d15af0
    void SelectionEnd(void* pObject, int value, Vector3_s00d1_afe0* pPos);                         // 0x00d15280
    void DoObjectManipulation(uint32_t messageID, void* pMessage);                      // 0x00d178a0
    void HandleRotateMessage(uint32_t messageID, void* pMessage);                       // 0x00d15980
    void DeleteSelected();                                                              // 0x00d164d0
    void SaveLevel(Vector3_s00d1_afe0* pPos, uint32_t name);                                       // 0x00d15160
    void LoadLevel(bool b);                                                             // 0x00d15c00
    void Copy();                                                                        // 0x00d19460
    void SetButtonHighlight(HighlightArg arg);                                          // 0x00d18860
    cGameEditInputStrategy_s00d1_afe0* ConstructFields();                                          // 0x00d1bb60
    void DestroyFields();                                                               // 0x00d1bcc0
    void MarkEditorActive();                                                            // 0x00d1bf10
    bool ActivateEditor();                                                              // 0x00d1bf20

    static cCommandGameplayMarker_s00d1_afe0* RotateObject(SelectedRef_s00d1_afe0* pSelected);                // 0x00d15330
};
// ---- items of slice s00d1afe0 end

// ---- items of slice s00d18df0_b begin (TODO(rewrite): local stubs, replace by canonical classes)
template <class T> inline const T& EastlMax(const T& a, const T& b) { return (a < b) ? b : a; }
namespace eastl {
extern wchar_t gEmptyString16[];                         // 0x01667bac
}
namespace eastl {
class allocator_s00d1_8df0__b {
public:
    void deallocate(void* p, unsigned int) { operator delete(p); }
};
}
namespace eastl {
template <class T> struct basic_string_s00d1_8df0__b {
    T* mpBegin;                                          // +0x0
    T* mpEnd;                                            // +0x4
    T* mpCapacity;                                       // +0x8
    allocator_s00d1_8df0__b mAllocator;                                // +0xc

    basic_string_s00d1_8df0__b() { AllocateSelf(); }
    basic_string_s00d1_8df0__b(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s00d1_8df0__b() { DeallocateSelf(); }

    void AllocateSelf() {
        mpBegin = (T*)gEmptyString16;
        mpEnd = (T*)gEmptyString16;
        mpCapacity = (T*)gEmptyString16 + 1;
    }
    void RangeInitialize(const T* p);                    // 0x00579a90
    void SetCapacity(unsigned int n);                    // 0x0042f360
    void reserve(unsigned int n) {
        unsigned int size = (unsigned int)(mpEnd - mpBegin);
        n = EastlMax(n, size) + 1;
        if (n > (unsigned int)(mpCapacity - mpBegin))
            SetCapacity(n);
    }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, unsigned int n) {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    const T* c_str() const { return mpBegin; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
}
namespace eastl {
typedef basic_string_s00d1_8df0__b<wchar_t> string16_s00d1_8df0__b;
}
namespace EA {
namespace ResourceMan {
class Manager_s00d1_8df0__b;
}
}
namespace EA {
namespace ResourceMan {
struct Key_s00d1_8df0__b {
    uint32_t instance;                                   // +0x00
    uint32_t type;                                       // +0x04
    uint32_t group;                                      // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct KeyVector {
    Key_s00d1_8df0__b* mpBegin;                                        // +0x00
    Key_s00d1_8df0__b* mpEnd;                                          // +0x04
    Key_s00d1_8df0__b* mpCapacity;                                     // +0x08
    uint32_t mAllocator;                                 // +0x0c

    void erase(Key_s00d1_8df0__b* first, Key_s00d1_8df0__b* last);                   // 0x0050f740
    void clear() { erase(mpBegin, mpEnd); }
};
}
}
namespace EA {
namespace ResourceMan {
struct IResourceFilter {                                 // vtable 0x013eb898
    PV
};
}
}
namespace EA {
namespace ResourceMan {
struct PlanetKeyFilter : IResourceFilter {
    uint32_t mInstanceID;                                // +0x04
    uint32_t mGroupID;                                   // +0x08
    uint32_t mTypeID;                                    // +0x0c
    uint32_t mFlags;                                     // +0x10
    PlanetKeyFilter()
    {
        mInstanceID = 0xffffffff;
        mTypeID = 0xb1b104;
        mGroupID = 0x40840000;
        mFlags = 0xdfff0000;
    }
};
}
}
namespace EA {
namespace ResourceMan {
struct IResourceManager_s00d1_8df0__b {
    PV8 PV4 PV2
    virtual int GetResourceKeyList(KeyVector* pKeys, IResourceFilter* pFilter, int flags);  // +0x38
    PV16
    virtual bool GetFileName(const Key_s00d1_8df0__b* pKey, eastl::string16_s00d1_8df0__b* pName);                     // +0x7c
};
}
}
EA::ResourceMan::IResourceManager_s00d1_8df0__b* GetManager_s00d1_8df0__b();         // 0x008de1a0
namespace EA {
namespace UTFWinControls {
class IWinGrid_s00d1_8df0__b {
public:
    PV16 PV16 PV2                                        // +0x00..+0x84
    virtual void v88(int a);                             // +0x88
    virtual void v8c(int a);                             // +0x8c
    PV4 PV2                                              // +0x90..+0xa4
    virtual void va8(int a, int b);                      // +0xa8
    PV16 PV16 PV16                                       // +0xac..+0x168
    virtual void v16c();                                 // +0x16c
    PV8 PV4 PV                                           // +0x170..+0x1a0
    virtual void v1a4(int a, int row, const wchar_t* pName, int b, int c, int d);  // +0x1a4
};
}
}
namespace SP {
class cGameEditInputStrategy_s00d1_8df0__b {
public:
    void Copy();                                                         // 0x00d19460
    void PopulateLoadPlanetDialogGrid();                                 // 0x00d194c0
    void DoSaveSelectedFile(eastl::string16_s00d1_8df0__b* pName);                     // 0x00d18df0

    char pad00[0x8c];
    EA::UTFWinControls::IWinGrid_s00d1_8df0__b* mPlanetGridFileList;                   // +0x8c
    EA::ResourceMan::KeyVector mPlanetKeys;                              // +0x90
};
}
namespace SP {
struct cPropertyListNameSort_s00d1_8df0__b {
    uint32_t mGroupId;                                   // +0x00
    EA::ResourceMan::Manager_s00d1_8df0__b* mpResourceManager;         // +0x04
    eastl::string16_s00d1_8df0__b aName;                               // +0x08
    eastl::string16_s00d1_8df0__b bName;                               // +0x18

    cPropertyListNameSort_s00d1_8df0__b(uint32_t groupID);             // 0x00d196f0
    cPropertyListNameSort_s00d1_8df0__b(const cPropertyListNameSort_s00d1_8df0__b& x);  // 0x00d18000
    bool operator()(uint32_t a, uint32_t b) const;       // 0x00d16760
};
}
namespace eastl {
void make_heap(uint32_t* first, uint32_t* last, SP::cPropertyListNameSort_s00d1_8df0__b compare);            // 0x00d18cd0
}
namespace eastl {
void adjust_heap(uint32_t* first, int top, int count, int hole, uint32_t value,
                 SP::cPropertyListNameSort_s00d1_8df0__b compare);                                            // 0x00d180c0
}
namespace eastl {
void sort_heap(uint32_t* first, uint32_t* last, SP::cPropertyListNameSort_s00d1_8df0__b compare);            // 0x00d18d60
}
// ---- items of slice s00d18df0_b end

// @ 0x00cd1750
void* Simulator::cScenarioEditModeInputStrategy::Destroy(uint8_t flags)
{
    cSub04& sub = mSub;
    cNested1c& nested = sub.mNested1c;
    mpVtable = (void*)0x014771e0;
    nested.Release(nested.mpValue0c);
    sub.Release(sub.mpValue0c);
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00d15100
void __stdcall FUN_00d15100(int32_t nA, int32_t nB)
{
    (void)nA;
    (void)nB;
    if (*(uint8_t*)0x0169dc20) {
        *(uint8_t*)0x0169dc20 = 0;
        cTerraformingManager* pManager = (cTerraformingManager*)SP_TerraformingManager();
        if (pManager)
            pManager->SetMode(1);
    }
}

// @ 0x00d15160
void __stdcall FUN_00d15160(const cVec3* pAlpha, int32_t nUnused)
{
    (void)nUnused;
    cCameraCtl* pCamera = GetCameraCtl();
    if (!pCamera)
        return;

    cVec3 vForward;
    pCamera->GetForward(&vForward);
    if (!SP_ResourceManager())
        return;

    int32_t nHandle = 0;
    struct StreamRequest {
        const cVec3* mpSeed;                                // +0x00
        uint32_t     mGroupID;                              // +0x04
        uint32_t     mTypeID;                               // +0x08
    } request;
    request.mpSeed = pAlpha;
    request.mGroupID = 0xf2b924b3;
    request.mTypeID = 0x72b924b5;
    int32_t nRecord = SP_OpenRecordAsStream(&request, &nHandle);

    if (nRecord != -1) {
        cParser* pParser = (cParser*)ArgScript_CreateParser();
        pParser->v008();
        cCommandGameplayMarkerTemplate* pTemplate =
            (cCommandGameplayMarkerTemplate*)operator_new(0x16c, "App/cCommandGameplayMarkerTemplate",
                                                         0, 0, 0, 0);
        if (pTemplate)
            pTemplate->Init(pAlpha, &vForward);
        else
            pTemplate = 0;
        pParser->v014((void*)kTemplateName, pTemplate);
        cParser* pCheat = (cParser*)SP_CheatManager();
        cParser* pWindow = (cParser*)pCheat->v038();
        pParser->v0bc((const wchar_t*)pWindow->v0c4());
        pParser->v03c(&nHandle);
        SP_EraseEntry(nRecord);
    }

    FUN_00b99530(1, 0, 0);
    FUN_00ba1280();
}

// @ 0x00d15280
bool __stdcall FUN_00d15280(int32_t nA, int32_t nFlags, int32_t nC)
{
    (void)nA;
    (void)nC;
    ((cTerrainCursor*)SP_GetGameTerrainCursor_s00d1_4460())->t0b8(0);
    ((cTerrainCursor*)SP_GetGameTerrainCursor_s00d1_4460())->t0a4();
    ((cTerrainCursor*)SP_GetGameTerrainCursor_s00d1_4460())->t0ac(1.0f);
    ((cTerrainCursor*)SP_GetGameTerrainCursor_s00d1_4460())->t0b0(1.0f);

    cCurMgr* pManager = (cCurMgr*)FUN_0067cab0();
    pManager->FindLocal(0x1002);

    if (nFlags & 1)
        ((cTerrainCursor*)SP_GetGameTerrainCursor_s00d1_4460())->t064();
    ((cTerrainCursor*)SP_GetGameTerrainCursor_s00d1_4460())->t074();
    int32_t nZero = 0;
    return ((cTerrainCursor*)SP_GetGameTerrainCursor_s00d1_4460())->t070() == nZero;
}

// @ 0x00d15350
void FUN_00d15350(cNoun* pNoun, int32_t nIndex, int32_t nType, const wchar_t* pValue)
{
    switch (nType) {
    case 1:
        pNoun->mValues[nIndex] = (wide_compare(pValue, L"true") == 0) ? 1 : 0;
        return;
    case 9:
        pNoun->mValues[nIndex] = (int32_t)wide_to_ulong(pValue, 0, 10);
        return;
    case 13: {
        wchar_t* pEnd;
        float fValue = (float)wide_to_double(pValue, &pEnd);
        *(float*)&pNoun->mValues[nIndex] = fValue;
        return;
    }
    default:
        pNoun->mValues[nIndex] = (int32_t)wide_to_ulong(pValue, 0, 10);
        return;
    }
}

// @ 0x00d15440
void SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15440(Vec3* pTarget)
{
    void* o = ((Fn_p_p)VTSLOT(mpNoun, 0x58))(mpNoun);
    if (o == 0)
        return;

    void* o2 = ((Fn_p_p)VTSLOT(mpNoun, 0x58))(mpNoun);
    Vec3* p = ((Obj*)o2)->m_position();
    float dx = pTarget->x - p->x;
    float dy = pTarget->y - p->y;
    float dz = pTarget->z - p->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    mVecC4.x = inv * dx;
    mVecC4.y = inv * dy;
    mVecC4.z = inv * dz;

    void* o3 = ((Fn_p_p)VTSLOT(mpNoun, 0x58))(mpNoun);
    float* q = (float*)((Obj*)o3)->m_slot30();
    mQuatD0[0] = q[0];
    mQuatD0[1] = q[1];
    mQuatD0[2] = q[2];
    mQuatD0[3] = q[3];
}

// @ 0x00d15550
void SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15550()
{
    Obj* w = mLayout.FindWindowByID(0x30170d2c, 1);
    if (w != 0) {
        ((Fn_v_p)VTSLOT(w, 0))(w);
        void* pSub = (this != 0) ? (void*)&mSub40 : (void*)0;
        ((Fn_v_pp)VTSLOT(w, 0x108))(w, pSub);
    }

    if (mpNoun != 0) {
        cGameNounManager_s00d1_5440* m = SP_NounManager(mpNoun);
        m->RemoveNoun((Obj*)mpNoun);
        mpNoun = 0;
    }

    mLayout.SetVisibility(0);

    if (mpHandler != 0) {
        void* h = mpHandler;
        mpHandler = 0;
        EA_Messaging_RemoveHandler(h, mHandlerArgs[0], mHandlerArgs[1],
                                   mHandlerArgs[2], mHandlerArgs[3]);
    }

    if (w != 0)
        ((Fn_v_p)VTSLOT(w, 4))(w);
}

// @ 0x00d15600
void SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15600()
{
    ((Fn_v_pii)VTSLOT(mpFieldA4, 0x7c))(mpFieldA4, 1, 0);
    ((Fn_v_p)VTSLOT(mpFieldA8, 0xe4))(mpFieldA8);
}

// @ 0x00d15630
void SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15630(void* a1, float* pX, float* pY)
{
    Obj* label = WinText_CreateDefault(-1, 0xacbf4564);
    if (label != 0)
        ((Fn_v_p)VTSLOT(label, 0))(label);

    float area[4];
    area[0] = 0.0f;
    area[1] = 0.0f;
    area[2] = DAT_014763b8;
    area[3] = DAT_013ebc4c;

    Obj* c;
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0x84))(c, 1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pp)VTSLOT(c, 0x60))(c, area);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0xac))(c, (int)0xffbac1b3);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0x5c))(c, -1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pi)VTSLOT(c, 0x80))(c, (int)a1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_p)VTSLOT(c, 0x90))(c);
    ((Fn_v_pi)VTSLOT(label, 0x14))(label, 1);
    c = ((Fn_p_p)VTSLOT(label, 0x10))(label); ((Fn_v_pff)VTSLOT(c, 0x64))(c, *pX, *pY);

    *pX += DAT_013f08e8;

    void* owner = mpFieldA8;
    Obj* t = ((Fn_p_p)VTSLOT(label, 0x10))(label);
    ((Fn_v_pp)VTSLOT(owner, 0xd8))(owner, t);

    ((Fn_v_p)VTSLOT(label, 4))(label);
}

// @ 0x00d15780
float SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15780(void* a1, float* pX, float* pY)
{
    Obj* comboDrawable = 0;
    Obj* scrollbar = 0;
    Obj* combo = 0;

    // Each drawable is allocated through the factory (pool, alignment, class name,
    // pool handle) and then placement-constructed; a +0xc / +0x20c offset yields the
    // window sub-object, which is add-ref'd immediately.
    {
        Obj* p = (Obj*)FUN_009512d0(0x1c, 4, "UI/ComboBoxDrawable", FUN_009512c0());
        if (p != 0) {
            p = ComboBoxDrawable_ctor(p);
            if (p != 0) {
                comboDrawable = (Obj*)((char*)p + 0xc);
                if (comboDrawable != 0)
                    ((Fn_v_p)VTSLOT(comboDrawable, 0))(comboDrawable);
            }
        }
    }
    {
        Obj* p = (Obj*)FUN_009512d0(0x2c, 4, "UI/ScrollbarDrawable", FUN_009512c0());
        if (p != 0) {
            p = ScrollbarDrawable_ctor(p);
            if (p != 0) {
                scrollbar = (Obj*)((char*)p + 0xc);
                if (scrollbar != 0)
                    ((Fn_v_p)VTSLOT(scrollbar, 0))(scrollbar);
            }
        }
    }
    {
        Obj* p = (Obj*)FUN_009512d0(0x2b8, 4, "UI/WinComboBox", FUN_009512c0());
        if (p != 0) {
            p = WinComboBox_ctor(p);
            if (p != 0) {
                combo = (Obj*)((char*)p + 0x20c);
                if (combo != 0)
                    ((Fn_v_p)VTSLOT(combo, 0))(combo);
            }
        }
    }

    ((Fn_v_pp)VTSLOT(combo, 0x68))(combo, comboDrawable);
    ((Fn_v_pp)VTSLOT(combo, 0x60))(combo, scrollbar);
    ((Fn_v_pi)VTSLOT(combo, 0x18))(combo, 1);
    ((Fn_v_pi)VTSLOT(combo, 0x50))(combo, 0xf);

    Obj* c;
    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pp)VTSLOT(c, 0x54))(c, a1);
    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pp)VTSLOT(c, 0x50))(c, a1);
    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pii)VTSLOT(c, 0x7c))(c, 1, 1);

    float rect[4];
    rect[0] = *pX;
    rect[1] = *pY;
    rect[2] = *pX + DAT_01486ebc;
    rect[3] = *pY + DAT_013eecd8;

    c = ((Fn_p_p)VTSLOT(combo, 0x10))(combo); ((Fn_v_pp)VTSLOT(c, 0x60))(c, rect);

    *pX += DAT_01479c0c;

    Obj* t = ((Fn_p_p)VTSLOT(combo, 0x10))(combo);
    ((Fn_v_pp)VTSLOT(mpFieldA8, 0xd8))(mpFieldA8, t);

    ((Fn_v_p)VTSLOT(combo, 4))(combo);
    if (scrollbar != 0)
        ((Fn_v_p)VTSLOT(scrollbar, 4))(scrollbar);
    if (comboDrawable != 0)
        ((Fn_v_p)VTSLOT(comboDrawable, 4))(comboDrawable);

    return rect[1];
}

// @ 0x00d15980
void SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15980(void* a1, void* pObj)
{
    (void)a1;

    Obj* o1 = (Obj*)((Fn_p_p)VTSLOT(pObj, 0x10))(pObj);
    Obj* o2 = (Obj*)((Fn_p_pi)VTSLOT(o1, 0x1c))(o1, 0);

    Obj* p;
    if ((*(u32*)((char*)o2 + 0x10) & 0x30) != 0)
        p = *(Obj**)o2;
    else if (*(u16*)((char*)o2 + 0x12) == 0)
        return;
    else
        p = o2;

    if (p == 0)
        return;

    Obj* q = (Obj*)((Fn_p_pi)VTSLOT(p, 0xc))(p, 0x17f243b);
    if (q != 0) {
        void* id = ((Fn_p_pi)VTSLOT(q, 0xc))(q, (int)0x01186577);
        if (id == mpField4C) {
            Obj* f = (Obj*)mpField4C;
            if (f != 0) {
                mpField4C = 0;
                ((Fn_v_p)VTSLOT(f, 0xc0))(f);
            }
        }
        SP_NounManager(q)->RemoveNoun(q);
        FUN_00ba1280();
    }
}

// @ 0x00d15a10
void SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15a10(void* p)
{
    void* g = DAT_0169dc64;
    if (g != 0) {
        Obj* q = (Obj*)((Fn_p_pi)VTSLOT(g, 0xc))(g, (int)0x01186577);
        if (q != 0)
            ((Fn_v_pp)VTSLOT(q, 0x94))(q, p);
    }

    int* it = DAT_0169dc68;
    int i = 0;
    if (it != DAT_0169dc6c) {
        do {
            ((Fn_v_piii)VTSLOT(mpField88, 0x1c0))(mpField88, 0, i, 0);
            it += 3;
            ++i;
        } while (it != DAT_0169dc6c);
    }

    void* g2 = DAT_0169dc64;
    if (g2 != 0) {
        DAT_0169dc64 = 0;
        ((Fn_v_p)VTSLOT(g2, 4))(g2);
    }
}

// @ 0x00d15ab0
int SP::cGameEditInputStrategy::StartSelection(SP::cGameData * p, int flag, cSPVector3 const & a3)
{
    (void)a3;
    Obj* cursor = SP_GetGameTerrainCursor();
    void* key;
    if (p != 0)
        key = (void*)((Fn_p_pi)VTSLOT(p, 0xc))(p, (int)0x01186577);
    else
        key = (void*)0;
    ((Fn_v_ppb)VTSLOT(cursor, 0x9c))(cursor, flag & 1, key);
    return 0;
}

// @ 0x00d15af0
u32 SP::cGameEditInputStrategy_s00d1_5440::FUN_00d15af0(void* p, u8 flag, u32 a3)
{
    (void)a3;
    Obj* cursor = SP_GetGameTerrainCursor();
    void* key;
    if (p != 0)
        key = (void*)((Fn_p_pi)VTSLOT(p, 0xc))(p, (int)0x01186577);
    else
        key = (void*)0;
    ((Fn_v_ppb)VTSLOT(cursor, 0xa0))(cursor, flag & 1, key);
    return 0;
}

// @ 0x00d15b30
u32 __cdecl GetGameplayMarkerClassId(u32 classId)
{
    void* prop = 0;
    Obj* pm = SP_PropertyManager();
    (void)pm;

    u32 h = EA_Hash_FNV1_String16(DAT_01479b30, 0x811c9dc5, 1);

    if (((Fn_b_pui)VTSLOT(pm, 0x30))(pm, h, &prop)) {
        Obj* table = (Obj*)((Fn_p_pi)VTSLOT(prop, 0x28))(prop, 0x69623444);

        void* base;
        u32 count;
        if ((*(u32*)((char*)table + 0x10) & 0x30) != 0) {
            base = *(void**)table;
            count = *(u32*)((char*)table + 0x08);
        } else {
            count = (u32)(*(u16*)((char*)table + 0x12) != 0);
            base = (*(u16*)((char*)table + 0x12) != 0) ? (void*)table : (void*)0;
        }

        for (u32 i = 0; i < count; i += 2) {
            void* key = *(void**)((char*)base + i * 4);
            u32 val = *(u32*)((char*)base + i * 4 + 4);
            if ((void*)classId == key) {
                if (prop != 0)
                    ((Fn_v_p)VTSLOT(prop, 4))(prop);
                return val;
            }
        }
    }

    if (prop != 0)
        ((Fn_v_p)VTSLOT(prop, 4))(prop);
    return 0;
}

// @ 0x00d15c00
extern "C" void __cdecl FUN_00d15c00(char bForward)
{
    Vec3 avg;
    avg.x = DAT_0169dc28;
    avg.y = DAT_0169dc2c;
    avg.z = DAT_0169dc30;
    int count = 0;

    void* selRaw = FUN_00d1bf00();
    void** begin = *(void***)((char*)selRaw + 0x40);
    void** end = *(void***)((char*)selRaw + 0x44);

    for (void** it = begin; it != end; ++it) {
        if (*it != 0) {
            Obj* m = (Obj*)((Fn_p_pi)VTSLOT(*it, 0xb8))(*it, 0x36be278);
            if (m != 0) {
                Obj* sub = (Obj*)((char*)m + 0x34);
                if (((Fn_b_p)VTSLOT(sub, 0x50))(sub)) {
                    Vec3* p = sub->m_position();
                    avg.x += p->x;
                    avg.y += p->y;
                    avg.z += p->z;
                    ++count;
                }
            }
        }
    }

    float inv = 1.0f / (float)count;
    float spin = bForward ? 1.0f : -1.0f;
    float s = sinf(spin * DAT_013ec478);
    float c = cosf(spin * DAT_013ec478);

    Vec3 dir;
    dir.x = inv * avg.x;
    dir.y = inv * avg.y;
    dir.z = inv * avg.z;

    float n = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + DAT_013ec4b8);
    float qx = n * dir.x;
    float qy = n * dir.y;
    float qz = n * dir.z;

    // rotation components (the original synthesises a quaternion from the spin)
    float r0 = c;
    float r1 = s * qx;
    float r2 = s * qy;
    float r3 = s * qz;

    for (void** it = begin; it != end; ++it) {
        if (*it != 0) {
            Obj* m = (Obj*)((Fn_p_pi)VTSLOT(*it, 0xb8))(*it, 0x36be278);
            if (m != 0) {
                Obj* sub = (Obj*)((char*)m + 0x34);
                if (((Fn_b_p)VTSLOT(sub, 0x50))(sub)) {
                    Vec3* p = sub->m_position();
                    Vec3 out;
                    out.x = (1.0f - (r2 * r2 + r3 * r3) * DAT_01470f1c) * p->x
                          + (r1 * r2 - r0 * r3) * DAT_01470f1c * p->y
                          + (r0 * r2 + r1 * r3) * DAT_01470f1c * p->z;
                    out.y = (r1 * r2 + r0 * r3) * DAT_01470f1c * p->x
                          + (1.0f - (r1 * r1 + r3 * r3) * DAT_01470f1c) * p->y
                          + (r2 * r3 - r0 * r1) * DAT_01470f1c * p->z;
                    out.z = (r1 * r3 - r0 * r2) * DAT_01470f1c * p->x
                          + (r2 * r3 + r0 * r1) * DAT_01470f1c * p->y
                          + (1.0f - (r1 * r1 + r2 * r2) * DAT_01470f1c) * p->z;

                    void* surf = SP_cPlanetModel_DirectionToSurfacePosition(
                        SP_PlanetModel(), &out, &avg);
                    ((Fn_v_pp)VTSLOT(sub, 0x38))(sub, surf);

                    void* orient = SP_cPlanetModel_BuildSurfaceOrientation(
                        SP_PlanetModel(), &avg, sub->m_position());
                    ((Fn_v_pp)VTSLOT(sub, 0x3c))(sub, orient);
                }
            }
        }
    }
}

// @ 0x00d15fb0
u32 SP::cGameEditInputStrategy_s00d1_5440::GetGameplayMarkerTypeFromUI()
{
    void* prop = 0;
    Obj* pm = SP_PropertyManager();
    (void)pm;

    u32 h = EA_Hash_FNV1_String16(DAT_01479b30, 0x811c9dc5, 1);

    if (((Fn_b_pui)VTSLOT(pm, 0x30))(pm, h, &prop)) {
        Obj* win = mLayout.FindWindowByID((int)0xabc0fff8, 1);
        if (win != 0) {
            Obj* combo = (Obj*)((Fn_p_pi)VTSLOT(win, 0xc))(win, 0x2f5528d9);
            if (combo != 0) {
                ((Fn_v_p)VTSLOT(combo, 0))(combo);

                Obj* table = (Obj*)((Fn_p_pi)VTSLOT(prop, 0x28))(prop, 0x185a7a14);
                u32 idx = (u32)((Fn_p_p)VTSLOT(combo, 0x40))(combo);

                void* base;
                if ((*(u32*)((char*)table + 0x10) & 0x30) != 0)
                    base = *(void**)table;
                else
                    base = (*(u16*)((char*)table + 0x12) != 0) ? (void*)table : (void*)0;

                const wchar_t* label = *(const wchar_t**)((char*)base + idx * 16);
                u32 h2 = EA_Hash_FNV1_String16(label, 0x811c9dc5, 1);

                ((Fn_v_p)VTSLOT(combo, 4))(combo);
                if (prop != 0)
                    ((Fn_v_p)VTSLOT(prop, 4))(prop);
                return h2;
            }
        }
    }

    if (prop != 0)
        ((Fn_v_p)VTSLOT(prop, 4))(prop);
    return 0;
}

// Closest attempt. `p += 0x18` is retail's `add esi, 0x18`. The two stack
// stores `mov [esp+0x10], eax` and `mov [esp+0x14], edx` are still swapped.
// @ 0x00d16760
bool cStrCmp::operator()(u32 a, u32 b)
{
    char* p = (char*)this;
    cWString* strA = (cWString*)(p + 8);
    cConvertArg argA = { (void*)a, (void*)0x00b1b104, *(void**)p };
    cConvertArg argB = { (void*)b, (void*)0x00b1b104, *(void**)p };
    VT_7C_2(*(void**)(p + 4), &argA, strA);
    void* conv = *(void**)(p + 4);
    p += 0x18;
    VT_7C_2(conv, &argB, (cWString*)p);
    return StringCompare(strA->mpBegin, strA->mpEnd,
                         ((cWString*)p)->mpBegin, ((cWString*)p)->mpEnd) < 0;
}

// @ 0x00d167e0
void __fastcall cStrCmp_Destroy(cStrCmp* p)
{
    if ((int)(((char*)p->mStr18.mpCap - (char*)p->mStr18.mpBegin) & 0xfffffffe) > 2
        && p->mStr18.mpBegin != 0)
        operator delete[](p->mStr18.mpBegin);
    if ((int)(((char*)p->mStr08.mpCap - (char*)p->mStr08.mpBegin) & 0xfffffffe) > 2
        && p->mStr08.mpBegin != 0)
        operator delete[](p->mStr08.mpBegin);
}

// @ 0x00d16b90
void cGameEditInputStrategy::SetPlanet(const cVec3i* planet)
{
    mPlanetF8 = *planet;
    if (mpField7c != 0) {
        cWString str;
        str.mpBegin = (void*)0x01667bac;
        str.mpEnd = (void*)0x01667bac;
        str.mpCap = (void*)0x01667bae;
        if (planet->y != 0)
            VT_7C_2(ObjectError(), (void*)planet, &str);
        VT_60_1(mpField7c, str.mpBegin, 0);
        if ((int)(((char*)str.mpCap - (char*)str.mpBegin) & 0xfffffffe) > 2
            && str.mpBegin != 0)
            operator delete[](str.mpBegin);
    }
}

// @ 0x00d16c30
void SortInsertBounded(u32* first, u32* last, cStrCmp comp)
{
    if (first != last) {
        for (u32* i = first + 1; i != last; ++i) {
            u32 value = *i;
            u32* j = i;
            while (j != first && comp(value, j[-1])) {
                *j = j[-1];
                --j;
            }
            *j = value;
        }
    }
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16cc0
void SortInsert(u32* first, u32* last, cStrCmp comp)
{
    for (u32* i = first; i != last; ++i) {
        u32 value = *i;
        u32* dst = i;
        u32* src = i - 1;
        while (comp(value, *src)) {
            *dst = *src;
            --dst;
            --src;
        }
        *dst = value;
    }
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16d60
u32* Median3(u32* a, u32* b, u32* c, cStrCmp comp)
{
    if (comp(*a, *b)) {
        if (comp(*b, *c)) {
            cStrCmp_Destroy(&comp);
            return b;
        }
        if (comp(*a, *c)) {
            cStrCmp_Destroy(&comp);
            return c;
        }
        cStrCmp_Destroy(&comp);
        return a;
    } else {
        if (comp(*a, *c)) {
            cStrCmp_Destroy(&comp);
            return a;
        }
        if (!comp(*b, *c)) {
            cStrCmp_Destroy(&comp);
            return b;
        }
        cStrCmp_Destroy(&comp);
        return c;
    }
}

// @ 0x00d16e00
u32* Partition(u32* first, u32* last, u32 pivot, cStrCmp comp)
{
    for (;;) {
        while (comp(*first, pivot))
            ++first;
        while (comp(pivot, *--last))
            ;
        if (first >= last)
            break;
        u32 tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
    cStrCmp_FreeStrings(comp);
    return first;
}

// @ 0x00d16eb0
void SiftUp(u32* arr, int start, int pos, u32 value, cStrCmp comp)
{
    int parent = (pos - 1) >> 1;
    while (pos > start) {
        if (!comp(arr[parent], value))
            break;
        arr[pos] = arr[parent];
        pos = parent;
        parent = (parent - 1) >> 1;
    }
    arr[pos] = value;
    cStrCmp_FreeStrings(comp);
}

// @ 0x00d16f40
void cGameEditInputStrategy_s00d1_6f40::FUN_00d16f40(Vector3* target)
{
    if (mpSelectedObjectManipulator->v58() == 0)
        return;

    Vector3* ringPos = (Vector3*)mpSelectedObjectManipulator->v58()->v2c();
    Vector3 delta;
    delta.x = target->x - ringPos->x;
    delta.y = target->y - ringPos->y;
    delta.z = target->z - ringPos->z;
    float lenInv = 1.0f / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    Vector3 dir;
    dir.x = delta.x * lenInv;
    dir.y = delta.y * lenInv;
    dir.z = delta.z * lenInv;
    if (mFacing.x * dir.x + mFacing.y * dir.y + mFacing.z * dir.z < kDotThreshold) {
        Quaternion fromDir;
        SP::QuaternionFromDirections(&fromDir, &mFacing, &dir);
        float angle = (float)acos(fromDir.w);
        angle = angle + angle;
        Vector3* ringDir = (Vector3*)mpSelectedObjectManipulator->v58()->v2c();
        float turn = ringDir->x * fromDir.x + ringDir->y * fromDir.y + ringDir->z * fromDir.z;
        float half = angle * (turn > 0.0f ? 0.5f : -0.5f);
        float sn = sinf(half);
        float cs = cosf(half);
        Quaternion orient;
        orient.x = sn * kMarkerAxisX;
        orient.y = sn * kMarkerAxisY;
        orient.z = sn * kMarkerAxisZ;
        orient.w = cs;

        cUiObject* marker = mpSelectedObjectManipulator->v58();
        float frame[4];
        marker->v3c(FUN_007dcb00(frame, &mFrameD0, &orient));

        cUiObject* info = marker->vb8(0x36be278);
        if (info == 0)
            return;
        cMarkerInfo* markerInfo = (cMarkerInfo*)info;
        cUiObject* handler = markerInfo->mpField1a4;
        if (handler == 0)
            return;
        cUiObjectB* sub = (cUiObjectB*)handler->v0c(0x1186577);
        if (sub == 0)
            return;
        void* a2 = markerInfo->mSub34.v30();
        void* a3 = sub->v2c(a2);
        SP::cPlanetModel_s00d1_6f40* pm = SP::PlanetModel();
        float ctx[4];
        sub->v3c(pm->FUN_00b7f1f0(ctx, a3, a2));
    }
}

// @ 0x00d17250
void cGameEditInputStrategy_s00d1_6f40::Activate()
{
    mpSelectedObjectManipulator = 0;
    SP::cPlanetModel_s00d1_6f40* pm = SP::PlanetModel();
    SetPlanet(pm->GetPlanetKey());

    cUiObject* handlerTarget = &mHandler;
    cUiObject* server = SP::MessageServer();
    mpServer = server;
    mpHandlerTarget = handlerTarget;
    mpHandlerTable = g_01479b60;
    mHandlerCount = 0x23;
    mField114 = 0;
    if (server != 0 && handlerTarget != 0) {
        for (uint32_t i = 0; i < 0x23; i++)
            server->v24(handlerTarget, g_01479b60[i]);
    }
}

// @ 0x00d172d0
void cGameEditInputStrategy_s00d1_6f40::CommitChangesToGameplayMarker(cGameEditModeStrategy* scenario, char apply)
{
    AutoRefCount selectedText;
    AutoRefCount valueText;
    selectedText.mpObject = 0;
    valueText.mpObject = 0;

    if (scenario != 0) {
        cPropertyManager_s00d1_6f40* pm = SP::PropertyManager();
        if (selectedText.mpObject != 0) {
            selectedText.mpObject = 0;
            selectedText.mpObject->v04();
        }
        uint32_t editorHash = FNV1_String16(L"LevelEditor", 0x811c9dc5, 1);
        if (pm->p30(editorHash, &selectedText.mpObject)) {
            scenario->mMarkerType    = GetGameplayMarkerTypeFromUI();
            scenario->mMarkerClassId = FUN_00d15b30(scenario->mMarkerType);
            scenario->mField110      = FUN_00d16820();

            cUiObject* win = mLayout.FindWindowByID(0xabc0fffa, 1);
            if (win != 0) {
                cUiObject* text = win->v0c(0xcf428691);
                if (text != 0) {
                    text->v00();
                    valueText.mpObject = text;
                    scenario->mMarkerValue = (uint32_t)wcstoul(text->v54(), 0, 10);
                }
            }

            int types[32];
            if (FUN_00d16620(scenario->mMarkerType, types)) {
                void* it = 0;
                void* itEnd = 0;
                mpScrollBarA8->vcc(&it);
                mpScrollBarA8->vd0(&itEnd);
                while (it != itEnd) {
                    // the scrollbar hands back the element address itself; the container base
                    // 0x01440aec is added to it
                    cUiObject* elem = *(cUiObject**)((char*)g_01440aec + (int)it);
                    uint32_t v = elem->v1c();
                    if ((v & 0xfff0) != 0xfff0 && (v & 0xabc00000) == 0xabc00000) {
                        uint32_t index = v & 0x543fffff;
                        valueText.Assign(elem->v0c(0xcf428691));
                        selectedText.Assign(elem->v0c(0x2f5528d9));
                        if (valueText.mpObject != 0) {
                            FUN_00d15350(scenario, index, types[index], valueText.mpObject->v54());
                        } else if (selectedText.mpObject != 0) {
                            scenario->mMarkerValues[index] = (int)selectedText.mpObject->v40();
                        }
                    }
                    it = *(void**)it;
                }
            }
        }
    }

    if (apply != 0 && scenario != 0) {
        cGameEditModeStrategy::LoadScenario(scenario, -1, -1);
        mpUIA4->v7c(1, 0);
        mpScrollBarA8->ve4();
    }
    if (valueText.mpObject != 0)
        valueText.mpObject->v04();
    if (selectedText.mpObject != 0)
        selectedText.mpObject->v04();
}

// @ 0x00d178a0
void cGameEditInputStrategy_s00d1_78a0::DoObjectManipulation(uint32_t action, cUiObject_s00d1_78a0* message)
{
    cPropertyList* list = message->v10();
    Property_s00d1_78a0* valueProperty = list->v1c(0);
    cUiObject_s00d1_78a0* values = (cUiObject_s00d1_78a0*)valueProperty->GetValue();
    cUiObject_s00d1_78a0* targetRef = 0;                      // 0x17f243b
    cUiObject_s00d1_78a0* sourceRef = 0;                      // 0x1186577
    if (values != 0) {
        targetRef = values->v0c(0x17f243b);
        sourceRef = values->v0c(0x1186577);
    }
    uint32_t mode = list->v1c(1)->mValue[0];

    switch (action) {
    case 0x1271936:
        mpSelectedObject.Assign(sourceRef);
        return;

    case 0x1270f6b: {
        if (mpSelectedObject.mpObject == 0)
            return;

        Vector3 refPos = FUN_00b3d240()->GetPos(0, g_v169dc28);
        cUiObject_s00d1_78a0* marker = RotateObject(&mpSelectedObject);
        if (marker == 0)
            return;

        cMarkerInfo_s00d1_78a0* markerInfo = (cMarkerInfo_s00d1_78a0*)marker;
        Vector3* ringPos = (Vector3*)markerInfo->mSub34.v2c();
        Vector3 delta;
        delta.x = refPos.x - ringPos->x;
        delta.y = refPos.y - ringPos->y;
        delta.z = refPos.z - ringPos->z;

        cPlanetModel* pm = PlanetModel_s00d1_78a0();
        cGameEditModeStrategy_s00d1_78a0* selection = GetEditSelection();
        for (cUiObject_s00d1_78a0** it = selection->mSelectedBegin; it != selection->mSelectedEnd; ++it) {
            cUiObject_s00d1_78a0* noun = *it;
            if (noun == 0)
                continue;
            cMarkerInfo_s00d1_78a0* info = (cMarkerInfo_s00d1_78a0*)noun->vb8(0x36be278);
            if (info == 0)
                continue;
            cSpatial_s00d1_78a0* sub = &info->mSub34;
            if (!sub->v50())
                continue;

            Vector3* cur = (Vector3*)sub->v2c();
            Vector3 target;
            target.x = cur->x + delta.x;
            target.y = cur->y + delta.y;
            target.z = cur->z + delta.z;

            Vector3 placed;
            Vector3* position = pm->DirectionToSurfacePosition(&placed, &target);
            sub->v38(position);
            Quaternion orient;
            Quaternion* rotation = pm->BuildSurfaceOrientation(&orient, (Vector3*)sub->v2c());
            sub->v3c(rotation);

            if (mode != 0x29b || info->mpField1a4 == 0)
                continue;

            cSpatial_s00d1_78a0* handler = (cSpatial_s00d1_78a0*)FUN_00ad7360(&info->mpField1a4);
            if (handler == 0) {
                if (info->mpField1a4->v20() != 0x1be418e)
                    continue;
                cHerd* herd = (cHerd*)FUN_00ac80d0(info->mpField1a4, 0x1be418e);
                if (herd == 0)
                    continue;

                if (herd->mField160 != 0)
                    g_169dc20 = 1;
                herd->SetPosition(&placed);

                Vector3 normal;
                Vector3_Normalize(&normal, &placed);
                Quaternion spinA;
                Quaternion spinB;
                FUN_0059b060(&spinA, &g_v1582668, g_f1582664);
                FUN_0059b060(&spinB, &g_v1582674, g_f1582664);
                Quaternion matrix;
                FUN_007dcb00(&matrix, &spinA, &spinB);
                Vector3 facing;
                FUN_0059aed0(&facing, &placed, &matrix);
                Quaternion frame;
                pm->BuildSurfaceOrientation2(&frame, &placed, &facing);
                Vector3 up;
                FUN_0059aed0(&up, &g_v169dc88, &frame);
                Vector3 upDir;
                Vector3_Normalize(&upDir, &up);

                int index = 1;
                int ring = 1;
                int step = 6;
                for (cHerdMember** member = herd->mMembersBegin;
                     member != herd->mMembersEnd; ++member) {
                    cHerdMember* creature = *member;
                    if (step <= index) {
                        ++ring;
                        step += 6;
                        index = 0;
                    }
                    float radius = (float)ring * g_f1470f1c;
                    float angle = ((float)index * g_f169dc94) / (float)step;
                    Quaternion swing;
                    FUN_0059b060(&swing, &upDir, angle);
                    Vector3 offset;
                    FUN_0059aed0(&offset, &upDir, &swing);
                    Vector3 spot;
                    spot.x = offset.x * radius + placed.x;
                    spot.y = offset.y * radius + placed.y;
                    spot.z = offset.z * radius + placed.z;
                    Vector3 home;
                    creature->mSpatial.v38(pm->DirectionToSurfacePosition(&home, &spot));
                    Quaternion creatureFrame;
                    creature->mSpatial.v3c(pm->BuildSurfaceOrientation(
                        &creatureFrame, (Vector3*)creature->mSpatial.v2c()));
                    creature->v6c(100);
                    ++index;
                }
            } else {
                handler->v38(position);
                Vector3 normal;
                pm->GetNormalAt(&normal, position);
                Vector3 tangent;
                OrthogonalVector(&tangent, &normal);
                Quaternion rotation2;
                Quaternion* q = QuaternionFromFacingAndUp(&rotation2, &tangent, &normal);
                handler->v3c(q);
            }
        }
        return;
    }

    case 0x127433b: {
        if (sourceRef == 0)
            return;
        mpField50.Assign(sourceRef);
        if (targetRef->v38() == 0x2ee8eeb)
            return;
        if (targetRef->v38() == 0x7292112)
            return;
        if (targetRef->v20() != 0x36be27e)
            return;
        mHoverTimer.Restart();
        if (mpSelectedObjectManipulator != 0) {
            if (mpSelectedObjectManipulator->v58() == sourceRef)
                return;
            NounManager_s00d1_78a0()->RemoveNoun(mpSelectedObjectManipulator);
        }
        mpSelectedObjectManipulator = NounManager_s00d1_78a0()->CreateRotationRing();
        mpSelectedObjectManipulator->v54(sourceRef, 0);
        return;
    }

    case 0x127e78c: {
        Vector3 pos = FUN_00b3d240()->GetPos(0, g_v169dc28);
        FUN_00d16f40(&pos);
        return;
    }

    case 0x127ec9d: {
        Vector3 pos = FUN_00b3d240()->GetPos(0, g_v169dc28);
        FUN_00d15440(&pos);
        return;
    }
    }
}

// @ 0x00d18000
cPropertyListNameSort_s00d1_78a0::cPropertyListNameSort_s00d1_78a0(const cPropertyListNameSort_s00d1_78a0& x)
: mGroupID(x.mGroupID), mpResMan(x.mpResMan), mNameA(x.mNameA), mNameB(x.mNameB)
{
}

// @ 0x00d180c0
void AdjustHeapHole(uint32_t* first, int topIndex, int len, int holeIndex, uint32_t value, cPropertyListNameSort_s00d1_78a0 compare)
{
    int secondChild = 2 * holeIndex + 2;
    while (secondChild < len) {
        if (compare(first[secondChild], first[secondChild - 1]))
            --secondChild;
        first[holeIndex] = first[secondChild];
        holeIndex = secondChild;
        secondChild = 2 * (secondChild + 1);
    }
    if (secondChild == len) {
        first[holeIndex] = first[secondChild - 1];
        holeIndex = secondChild - 1;
    }
    SiftUp(first, topIndex, holeIndex, value, compare);
}

// @ 0x00d18180
void AdjustHeap(uint32_t* first, uint32_t* last, cPropertyListNameSort_s00d1_78a0 compare)
{
    uint32_t value = *(last - 1);
    *(last - 1) = *first;
    AdjustHeapHole(first, 0, (int)(last - first) - 1, 0, value, compare);
}

// @ 0x00d18df0
void SP::cGameEditInputStrategy_s00d1_8df0::DoSaveSelectedFile(eastl::string16_s00d1_8df0* pName)
{
    SelectionList* pSel = &GetEditSelection_s00d1_8df0()->mSelected;
    ISelectable** pBegin = pSel->mpBegin;
    ISelectable** pEnd = pSel->mpEnd;
    if (pBegin == pEnd)
        return;

    Vec3c sum(gZeroVec3);
    int count = 0;
    for (ISelectable** it = pBegin; it != pEnd; ++it) {
        if (*it) {
            cGameplayMarkerCmd* pMarker = (*it)->Cast(0x36be278);
            if (pMarker && pMarker->part.IsPlaced()) {
                const Vec3* pPos = pMarker->part.GetPosition();
                sum.x = pPos->x + sum.x;
                sum.y = pPos->y + sum.y;
                sum.z = pPos->z + sum.z;
                count++;
            }
        }
    }

    cCameraCtl_s00d1_8df0* pCam = GetCameraCtl_s00d1_8df0();
    if (count == 0 || !pCam)
        return;

    Vec3c centroid(Scale(sum, 1.0f / (float)(uint32_t)count));

    eastl::string16_s00d1_8df0 path;
    path.sprintf(L"%s.%s", pName->c_str(), L"ltp");

    Vec3c n;
    PlanetModel_s00d1_8df0()->GetNormalAt(&n, &centroid);
    Vec3c u;
    pCam->GetDirection(&u);

    // Gram-Schmidt: tangent = normalize(u - n * (n . u)), binormal = tangent x n
    float d = n.x * u.x + n.y * u.y + n.z * u.z;
    u -= Scale(n, d);
    Vec3c t(Scale(u, 1.0f / sqrtf(u.x * u.x + u.y * u.y + u.z * u.z + 1e-8f)));
    Vec3 b;
    b.x = t.y * n.z - t.z * n.y;
    b.y = t.z * n.x - n.z * t.x;
    b.z = n.y * t.x - t.y * n.x;

    IResourceManager_s00d1_8df0* pMgr = GetManager_s00d1_8df0();
    if (!pMgr)
        return;
    ResKey key;
    key.instance = 0;
    key.type = 0;
    key.group = 0;
    pMgr->GetKey(&key, path.c_str(), 0xf2b924b3, 0x72b924b5);
    IRecordDB* pDB = FindRecordDB(&key);
    if (!pDB)
        return;
    AutoRefCount_s00d1_8df0<IFileStream> pStream;
    if (!pDB->OpenRecord(&key, &pStream, 2, 2, 1, 0))
        return;
    IWriter* pWriter = pStream->GetWriter();
    eastl::string8_s00d1_8df0 line;
    for (ISelectable** it = pSel->mpBegin; it != pSel->mpEnd; ++it) {
        if (*it) {
            cGameplayMarkerCmd* pMarker = (*it)->Cast(0x36be278);
            if (pMarker && pMarker->part.IsPlaced()) {
                line.sprintf("GameplayMarkerTemplate %d %d %d %d", pMarker->ids[0], pMarker->ids[1],
                             pMarker->ids[2], pMarker->ids[3]);
                if (count == 1) {
                    line.append_sprintf(" %f %f\n", 0.0, 0.0);
                } else {
                    pMarker->part.GetPosition();
                    const Vec3* pPos = pMarker->part.GetPosition();
                    float dx = pPos->x - centroid.x;
                    float dy = pPos->y - centroid.y;
                    float dz = pPos->z - centroid.z;
                    double tx = dx * t.x + dy * t.y + dz * t.z;
                    double bx = dx * b.x + dy * b.y + dz * b.z;
                    line.append_sprintf(" %f %f\n", bx, tx);
                }
                uint32_t types[32];
                if (GetGameplayMarkerTypes(pMarker->ids[0], types)) {
                    for (uint32_t i = 0; i < pMarker->mCount; i++) {
                        switch (types[i]) {
                        case 1:
                            line.append_sprintf("bool %s\n", pMarker->mValues[i] == 1 ? "true" : "false");
                            break;
                        case 9:
                            line.append_sprintf("int %d\n", pMarker->mValues[i]);
                            break;
                        case 10:
                            line.append_sprintf("uint %d\n", pMarker->mValues[i]);
                            break;
                        case 13:
                            line.append_sprintf("float %f\n", (double)*(float*)&pMarker->mValues[i]);
                            break;
                        default:
                            line.append_sprintf("enum %d\n", pMarker->mValues[i]);
                            break;
                        }
                    }
                }
                line.append("end\n", "end\n" + 4);
                pWriter->Write(line.mpBegin, line.mpEnd - line.mpBegin);
                if (count == 1)
                    break;
            }
        }
    }
    pStream->Close();
}

// @ 0x00d19460
void SP::cGameEditInputStrategy_s00d1_8df0__b::Copy()
{
    eastl::string16_s00d1_8df0__b name(L"Clipboard");
    DoSaveSelectedFile(&name);
}

// @ 0x00d194c0
void SP::cGameEditInputStrategy_s00d1_8df0__b::PopulateLoadPlanetDialogGrid()
{
    mPlanetGridFileList->v16c();
    EA::ResourceMan::IResourceManager_s00d1_8df0__b* pMgr = GetManager_s00d1_8df0__b();
    EA::ResourceMan::KeyVector* pKeys = &mPlanetKeys;
    EA::ResourceMan::PlanetKeyFilter filter;
    pKeys->clear();
    pMgr->GetResourceKeyList(pKeys, &filter, 0);
    int count = (int)(pKeys->mpEnd - pKeys->mpBegin);
    for (int i = 0; i < count; i++) {
        eastl::string16_s00d1_8df0__b name;
        pMgr->GetFileName(&pKeys->mpBegin[i], &name);
        mPlanetGridFileList->v1a4(0, i, name.c_str(), 0, 1, 0);
    }
    mPlanetGridFileList->v8c(0);
    mPlanetGridFileList->v88(0);
    mPlanetGridFileList->va8(0, 0);
}

// @ 0x00d19610
namespace eastl {
void partial_sort(uint32_t* first, uint32_t* middle, uint32_t* last, SP::cPropertyListNameSort_s00d1_8df0__b compare)
{
    make_heap(first, middle, compare);
    for (uint32_t* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            uint32_t value = *i;
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, value, compare);
        }
    }
    sort_heap(first, middle, compare);
}
}  // namespace eastl

// @ 0x00d196f0
SP::cPropertyListNameSort_s00d1_8df0__b::cPropertyListNameSort_s00d1_8df0__b(uint32_t groupID)
{
    mGroupId = groupID;
    aName.reserve(0x104);
    bName.reserve(0x104);
    mpResourceManager = (EA::ResourceMan::Manager_s00d1_8df0__b*)GetManager_s00d1_8df0__b();
}

// @ 0x00d197a0
bool cGameEditInputStrategy_s00d1_97a0::HandleUIMessage(IWindow* pWindow, const UIMessage& msg)
{
    if (msg.mParam == gIgnoreParam)
        return false;

    IGameInput* pInput = GameInputManager();

    if (msg.mType == 0x8ef0c8dd) {
        if (msg.mParam == 0x36c3e74) {
            int v = mGameplayMarkerScrollbar->GetValue();
            mGameplayMarkerArea->SetArea(0.0f, (float)-v);
        }
        return true;
    }

    if (msg.mType == 0x4f5527e8) {
        switch ((int)msg.mParam) {
        case 0xabc0fff8: {
            MessageBasicRC5* pMsg = new("App", 0, 0, 0, 0) MessageBasicRC5(0);
            if (pMsg)
                pMsg->AddRef();
            pMsg->mMessageID = 0x3d0891e;
            pMsg->mValue = mGameplayMarkerScrollbar ? mGameplayMarkerScrollbar->GetValue() : 0;
            pMsg->mFlag = 1;
            MessageServer_s00d1_97a0()->Post(pMsg->mMessageID, pMsg, 0, 0);
            pMsg->Release();
            break;
        }
        case 0xabc0fff9:
            if (RotateObject(&mpSelectedObject)) {
                uint32_t classId = GetGameplayMarkerClassId(GetGameplayMarkerTypeFromUI());
                uint32_t x = FUN_00d16820();
                cCommandGameplayMarker_s00d1_97a0* pMarker = RotateObject(&mpSelectedObject);
                LoadScenario(pMarker, classId, x);
            }
            break;
        case 0x3e0691c:
            if (mVisibilityCombo) {
                int sel = mVisibilityCombo->GetSelection();
                if (sel == 0)
                    gMarkerVisibilityMode = 0;
                else
                    gMarkerVisibilityMode = HashName((const wchar_t*)mVisibilityCombo->GetText(sel));
            }
            break;
        }
    }

    switch ((int)msg.mParam) {
    case 0x135688e:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x137d8fe, true);
        ShowOptionWindows(0, 0);
        return true;
    case 0x92b3c8eb:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x12ba6ae8, true);
        return true;
    case 0x136abf8:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x137c407, true);
        ShowOptionWindows(0, 0);
        return true;
    case 0x13e7786:
        mLoadDialogWindow->SetFlag(1, 1);
        PopulateLoadDialogGridWithLevels();
        return true;
    case 0x13e7736: {
        string16_s00d1_97a0 name;
        if (GetSaveFileName(&name, 0)) {
            GetEditMode();
            SaveScenario(name.mpBegin);
        }
        return true;
    }
    case 0x13e778c: {
        NounManager_s00d1_97a0()->FUN_00b25fe0();
        if (mpSelectedObjectManipulator) {
            NounManager_s00d1_97a0()->RemoveNoun(mpSelectedObjectManipulator);
            mpSelectedObjectManipulator = 0;
        }
        PrepareDialog();
        gEditorFlag20 = 1;
        mGameplayMarkerRoot->SetFlag(1, 0);
        return true;
    }
    case 0x14143be: {
        mLoadDialogWindow->SetFlag(1, 0);
        void* pItem;
        int index;
        wchar_t* pPath;
        int key = 0;
        if (mGridFileList->GetSelected(&pItem, &index)) {
            mGridFileList->GetItemText(0, index, &pPath);
            key = mGridFileList->GetItemKey(0, index);
        }
        if (gEditorFlag21) {
            if (key == 0)
                return true;
            FUN_00d15a10(key);
            return true;
        }
        wchar_t name[256];
        EA::IO::SplitPath(pPath, 0, 0, name, 0, 4);
        NounManager_s00d1_97a0()->RemoveNounsOfType(0x36be27e);
        InterfaceCast(HashName(name), 1);
        mLevelNameTextEdit->SetText(name, 0);
        return true;
    }
    case 0x14143b4:
        mLoadDialogWindow->SetFlag(1, 0);
        mGameplayMarkerRoot->SetFlag(1, 0);
        return true;
    case 0x147c3f6:
        mLoadPlanetDialogWindow->SetFlag(1, 1);
        PopulateLoadPlanetDialogGrid();
        return true;
    case 0x147ccec:
        mLoadPlanetDialogWindow->SetFlag(1, 0);
        return true;
    case 0x147ccf2: {
        mLoadPlanetDialogWindow->SetFlag(1, 0);
        NounManager_s00d1_97a0()->FUN_00b25fe0();
        void* pItem;
        int index;
        if (!mPlanetGridFileList->GetSelected(&pItem, &index))
            return true;
        PlanetKey key = mPlanetKeysBegin[index];
        SetPlanet(&key);
        PlanetModel_s00d1_97a0()->FUN_00b8c0f0();
        PlanetModel_s00d1_97a0()->FUN_00b8d8a0(&key, 0, 1);
        PlanetModel_s00d1_97a0()->mpTerrain->SetSomething(GetPlanetThing());
        GetEditMode()->MarkDirty();
        return true;
    }
    case 0x2afbb64:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x2afab18, true);
        ShowOptionWindows(0, 0);
        return true;
    case 0x29fe4ed:
        PrepareDialog();
        EnterGameMode(GetCurrentGameModeAlt());
        return true;
    case 0x36c46d4:
        CommitChangesToGameplayMarker(RotateObject(&mpSelectedObject), true);
        return false;
    case 0x36c4718: {
        FUN_00d15600();
        cCommandGameplayMarker_s00d1_97a0* p = RotateObject(&mpSelectedObject);
        if (!p)
            return false;
        LoadScenario(p, 0xffffffff, 0xffffffff);
        return false;
    }
    case 0x3a869e8:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x3a86a56, true);
        ShowOptionWindows(1, 0);
        return true;
    case 0x12b933e5:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0x3a86a57, true);
        ShowOptionWindows(0, 1);
        return true;
    case 0x4f65940: {
        cCommandGameplayMarker_s00d1_97a0* p = RotateObject(&mpSelectedObject);
        if (!(p && p->mMarkerType == 0xc012ae1f && p->mShape == 4 && p->mpFirst == 0)) {
            IReleasable* q = mpSelectedObject.mpObject;
            if (q) {
                mpSelectedObject.mpObject = 0;
                q->ReleaseRef();
            }
        }
        pInput->SetCursorMode(0x4f64c5d, true);
        return true;
    }
    case 0x52b3c8d7: {
        string16_s00d1_97a0 name;
        if (GetSaveFileName(&name, 0))
            DoSaveSelectedFile(&name);
        return true;
    }
        case 0x72b3c8e2:
        SetButtonHighlight(SourceRef(msg.mpSource));
        pInput->SetCursorMode(0xb2ba6adb, true);
        return true;
    }
    return false;
}

// @ 0x00d1a080
namespace eastl {
inline int Log2(int n)
{
    int m = n;
    n = 0;
    _ReadWriteBarrier();
    int i = 0;
    if (m != 0) {
        do {
            m >>= 1;
            ++i;
        } while (m != 0);
    }
    return i;
}
}  // namespace eastl

// @ 0x00d1a2b0
namespace SP {
void cGameEditInputStrategy_s00d1_a2b0::ShowGameplayMarkerProperties(cCommandGameplayMarker* pMarker, bool bReadOnly, bool bSetDefaults)
{
    AutoRefCount_s00d1_a2b0<PropertyList> pPropList;
    if (!PropertyManager_s00d1_a2b0()->GetPropertyList(id(L"LevelEditor"), pPropList.AsPointer()))
        return;

    // Clear out the previous controls.
    void** it;
    void** itEnd;
    mGameplayMarkerArea->GetChildrenBegin(&it);
    mGameplayMarkerArea->GetChildrenEnd(&itEnd);
    while (it != itEnd) {
        void** pNode = it;
        it = (void**)*pNode;
        mGameplayMarkerArea->DisposeWindowFamily((IWindow_s00d1_a2b0*)((char*)pNode + g_1440aec));
    }
    mGameplayMarkerRoot->SetFlag(1, true);

    float x, y;
    y = x = 5.0f;
    {
        AddLabel(L"Type", x, y);
        AutoRefCount_s00d1_a2b0<IWinComboBox_s00d1_a2b0> pCombo(FindComboBox(0xabc0fff8));
        if (!pCombo) {
            AddComboBox(0xabc0fff8, x, y);
            pCombo = FindComboBox(0xabc0fff8);
            Property* pTypes = pPropList->GetProperty(0x185a7a14);
            uint32_t count = pTypes->GetItemCount();
            int selection = 0;
            eastl::string16_s00d1_a2b0* pType = (eastl::string16_s00d1_a2b0*)pTypes->GetValue();
            for (uint32_t i = 0; i < count; i++, pType++) {
                pCombo->AddItem(pType->c_str());
                uint32_t hash = id(pType->c_str());
                if (pMarker->mType == 0)
                    pMarker->mType = hash;
                if (hash == pMarker->mType)
                    selection = i;
            }
            pCombo->SetSelection(selection, false);
        }
        pCombo->ToWindow()->SetFlag(2, bReadOnly);
        pCombo->ToWindow()->SetFlag(0x10, !bReadOnly);
        pCombo->ToWindow()->SetFlag(0x1000, !bReadOnly);

        // Definition: every noun of the marker's class.
        x = 5.0f;
        y = 35.0f;
        AddLabel(L"Definition", x, y);
        AddComboBox(0xabc0fff9, x, y);
        uint32_t classID = GetGameplayMarkerClassId(pMarker->mType);
        pCombo = FindComboBox(0xabc0fff9);
        int selection = 0;
        int index = 0;
        NounEntryTable& entries = NounManager()->mEntries;
        for (NounEntryIterator itNoun = entries.begin(); itNoun != entries.end(); ++itNoun) {
            if (itNoun->mClassID == classID) {
                uint32_t instanceID = itNoun->mInstanceID;
                eastl::string16_s00d1_a2b0 name;
                if (itNoun->mpPropList && itNoun->mpPropList->HasProperty(0x2e9c159)) {
                    eastl::string8_s00d1_a2b0 name8;
                    GetPropertyAsString8(itNoun->mpPropList, 0x2e9c159, name8);
                    name = EA::ConvertToString16(name8);
                }
                if (name.empty()) {
                    eastl::string8_s00d1_a2b0 className(GetNounClassName(itNoun->mClassID));
                    name.sprintf(L"%ls 0x%08x", EA::ConvertToString16(className).c_str(), instanceID);
                }
                pCombo->AddItem(name.c_str());
                if (pMarker->mDefClassID == classID && pMarker->mDefInstanceID == instanceID)
                    selection = index;
                index++;
            }
        }
        pCombo->SetSelection(selection, false);

        // Triggers.
        x = 5.0f;
        y = 65.0f;
        Noun* pNoun = NounManager()->GetNoun(pMarker->mDefClassID, pMarker->mDefInstanceID);
        if (pNoun && pNoun->mpPropList) {
            uint32_t triggerCount = 0;
            uint32_t* pTriggers = 0;
            if (GetPropertyAsUint32Array(pNoun->mpPropList, 0x3d03b03, triggerCount, pTriggers)) {
                IdVector ids;
                PropertyManager_s00d1_a2b0()->GetPropertyListIDs(0x3cddc79, ids);
                eastl::sort(ids.mpBegin, ids.mpEnd, cPropertyListNameSort(0x3cddc79));
                eastl::string16_s00d1_a2b0 label;
                eastl::string16_s00d1_a2b0 fileName;
                for (int i = 0; i < (int)triggerCount; i++) {
                    label.sprintf(L"Trigger %d", i);
                    AddLabel(label.c_str(), x, y);
                    uint32_t controlID = i + 0xabc0fff0;
                    AddComboBox(controlID, x, y);
                    pCombo = FindComboBox(controlID);
                    uint32_t current = pTriggers[i];
                    int triggerSel = 0;
                    pCombo->AddItem(L"None");
                    int item = 1;
                    for (uint32_t* pID = ids.mpBegin; pID != ids.mpEnd; pID++) {
                        uint32_t listID = *pID;
                        if (listID != 0x2ea8fb98) {
                            fileName.clear();
                            EA::ResourceMan::GetManager()->GetFileName(
                                EA::ResourceMan::Key_s00d1_a2b0(listID, 0xb1b104, 0x3cddc79), fileName);
                            wchar_t buffer[256];
                            EA::IO::SplitPath(fileName.c_str(), 0, 0, buffer, 0, 4);
                            pCombo->AddItem(buffer);
                            if (listID == current)
                                triggerSel = item;
                            item++;
                        }
                    }
                    pCombo->SetSelection(triggerSel, false);
                    x = 5.0f;
                    y += 30.0f;
                    pCombo->ToWindow()->SetFlag(2, false);
                    pCombo->ToWindow()->SetFlag(0x10, true);
                    pCombo->ToWindow()->SetFlag(0x1000, true);
                }
            }
        }

        AddLabel(L"Group", x, y);
        AddTextEdit(0xabc0fffa, 10, &pMarker->mGroup, x, y);
        x = 5.0f;
        y += 30.0f;
    }

    // Per-type parameters: triples of (label, type, default) strings.
    if (pPropList->HasProperty(pMarker->mType)) {
        Property* pParams = pPropList->GetProperty(pMarker->mType);
        uint32_t count = pParams->GetItemCount();
        if (count <= 0x60) {
            pMarker->mValueCount = count / 3;
            eastl::string16_s00d1_a2b0* pParam = (eastl::string16_s00d1_a2b0*)pParams->GetValue();
            for (uint32_t i = 0; i < count; i += 3, pParam += 3) {
                uint32_t index = i / 3;
                int type = cCommandGameplayMarker::ParseTypeEnum(EA::ConvertToString8(pParam[1]).c_str());
                AddLabel(pParam[0].c_str(), x, y);
                if (bSetDefaults)
                    SetGameplayMarkerDefaultValue(pMarker, index, type, pParam[2].c_str());
                if (type == 1 || type == 9 || type == 10 || type == 13 || !pPropList->HasProperty(type)) {
                    AddTextEdit(index | 0xabc00000, type, &pMarker->mValues[index], x, y);
                } else {
                    AddComboBox(index | 0xabc00000, x, y);
                    AutoRefCount_s00d1_a2b0<IWinComboBox_s00d1_a2b0> pCombo(FindComboBox(index | 0xabc00000));
                    Property* pChoices = pPropList->GetProperty(type);
                    uint32_t n = pChoices->GetItemCount();
                    eastl::string16_s00d1_a2b0* pChoice = (eastl::string16_s00d1_a2b0*)pChoices->GetValue();
                    for (; n; n--, pChoice++)
                        pCombo->AddItem(pChoice->c_str());
                    pCombo->SetSelection(pMarker->mValues[index], false);
                }
                x = 5.0f;
                y += 30.0f;
            }
        }
    }

    Rectangle area = mGameplayMarkerArea->GetArea();
    area.y1 = 0.0f;
    area.y2 = y;
    mGameplayMarkerArea->SetArea(area);
    if (mGameplayMarkerScrollbar) {
        RoundToInt(area.y2);
        mGameplayMarkerScrollbar->SetMaxValue(RoundToInt(y), true);
        mGameplayMarkerScrollbar->SetValue(0, true);
    }
}
}  // namespace SP

// @ 0x00d1bb60
cGameEditInputStrategy_s00d1_afe0* cGameEditInputStrategy_s00d1_afe0::ConstructFields()
{
    const uint32_t base = reinterpret_cast<uint32_t>(this);

    mListCount10 = 0;
    mListAlloc14 = 0;
    mListAux18 = 0;
    mListHead08 = base + 8;
    mListTail0c = mListHead08;
    mListCount10 = 0;
    mListAux18 = 0;

    mpEditorMode24 = (IObject*)(base + 0x24);
    mpEditorAux28 = (IObject*)(base + 0x24);
    mField2c = 0;
    mField30 = 0;
    mField34 = 0;

    // Provisional base/subobject vtables, then the final cGameEditInputStrategy ones.
    IMessageHandler::SetVtable((void*)0x13eb384);
    mpVtable40 = (void*)0x14426a0;
    mpVtable44 = (void*)0x13ec458;
    mField48 = 0;
    cInputStrategyBase_s00d1_afe0::SetVtable((void*)0x1479e0c);
    IMessageHandler::SetVtable((void*)0x1479dfc);
    mpVtable40 = (void*)0x1479de0;
    mpVtable44 = (void*)0x1479dd0;

    mpSelectedObject.mpObject = 0;
    mpField50 = 0;
    mField54 = 0;
    mSubobject58.Construct();

    mpField78 = 0;
    mpField7c = 0;
    mpField80 = 0;
    mpField84 = 0;
    mpField88 = 0;
    mpField8c = 0;
    mpField90 = 0;
    mpField94 = 0;
    mpField98 = 0;

    mGameplayMarkerRoot = 0;
    mGameplayMarkerArea = 0;
    mGameplayMarkerScrollbar = 0;
    padb0 = 0;
    mRuleOptionsList = 0;
    mTemplateOptions = 0;
    mTemplateOptionsList = 0;
    mPlanetNameEdit = 0;

    mLayout.Construct();
    mTransitionHandle = 0;
    mTransition108 = 0;
    mTransition10c = 0;
    mTransition110 = 0;
    mTransition114 = 0;
    return this;
}

// @ 0x00d1bcc0
void cGameEditInputStrategy_s00d1_afe0::DestroyFields()
{
    cInputStrategyBase_s00d1_afe0::SetVtable((void*)0x1479e0c);
    IMessageHandler::SetVtable((void*)0x1479dfc);
    mpVtable40 = (void*)0x1479de0;
    mpVtable44 = (void*)0x1479dd0;

    if (mTransitionHandle != 0) {
        uint32_t handle = mTransitionHandle;
        mTransitionHandle = 0;
        DestroyTransitionHandle(handle, mTransition108, mTransition10c,
                                mTransition110, mTransition114);
    }
    mLayout.Destroy();

    if (mPlanetNameEdit) mPlanetNameEdit->a1();
    if (mTemplateOptionsList) mTemplateOptionsList->a1();
    if (mTemplateOptions) mTemplateOptions->a1();
    if (mRuleOptionsList) mRuleOptionsList->a1();
    if (mGameplayMarkerScrollbar) mGameplayMarkerScrollbar->a1();
    if (mGameplayMarkerArea) mGameplayMarkerArea->a1();
    if (mGameplayMarkerRoot) mGameplayMarkerRoot->a1();
    if (mpField8c) mpField8c->Release();
    if (mpField88) mpField88->Release();
    if (mpField84) mpField84->Release();
    if (mpField80) mpField80->Release();
    if (mpField7c) mpField7c->Release();
    if (mpField78) mpField78->Release();
    mSubobject58.Destroy();
    if (mpField50) mpField50->Release();
    if (mpSelectedObject.mpObject) ((IObject*)mpSelectedObject.mpObject)->Release();

    mpVtable44 = (void*)0x13ec458;
    mpVtable40 = (void*)0x13eb938;
    IMessageHandler::SetVtable((void*)0x13eb394);
    cInputStrategyBase_s00d1_afe0::SetVtable((void*)0x14771e0);
}
