// src/game/SPGonzago/SPTribeModeStrategy.cpp -- migrated from slice(s) s0135d100, s00cdef00, s00cde2f0, s00cdd500, s00cdab10, s00cd8e70, s00cd75f0, s00cd6680, s00cd5550, s00cd45c0, s00ccfc20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeModeStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cTribe.h"
#include "SP/cVarListSerializer.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cLocalInputState.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cPlayer.h"
#include "SP/cPropertyList.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cStarManager.h"
#include "SP/cTribeTool.h"
#include <math.h>
#include "SP/cConfigManager.h"
#include "SP/cHerd.h"
#include "SP/cInputStrategy.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPTimer.h"

// ---- items of slice s00ccfc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void*  GetGameTerrainCursor();                 // 0x00b30d70
uint32_t FUN_00ccefb0(void*, void*);           // 0x00ccefb0  GetTribeCursorID
void   FUN_00ad92d0(void*);                    // 0x00ad92d0  eastl vector dtor
unsigned char FUN_00cd4460(void*, uint32_t);                // 0x00cd4460 (thiscall)
void   FUN_00cd6980(void*, uint32_t);                       // 0x00cd6980 (thiscall)
struct StackVec {
    void**  mpBegin;    // +0x00
    void**  mpEnd;      // +0x04
    void**  mpCap;      // +0x08
    void*   mX0c;       // +0x0c
    void*   mX10;       // +0x10
    void*   mX14;       // +0x14
    void*   mBuf[16];   // +0x18
    void init()
    {
        mX14    = 0;
        mpBegin = &mBuf[0];
        mpEnd   = &mBuf[0];
        mpCap   = &mBuf[16];
    }
};
struct CInput {
    void F_ccfc20(void* arg);                            // 0x00ccfc20
    void F_ccfcf0(void* vec, int key, void* a, void* b); // 0x00ccfcf0
    void F_cd07c0(void* a, void* b, void* c);            // 0x00cd07c0
    int  F_cd0830(void* arg);                            // 0x00cd0830
    void F_cd0950();                                     // 0x00cd0950
    void F_cd02d0(void* pos);                            // 0x00cd02d0
    int  F_cd0660(void* flags, void* pos, void* c);      // 0x00cd0660
};
// ---- items of slice s00ccfc20 end

// ---- items of slice s00cd45c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern void*  g_crew;                                         // 0x0169b2c8  _spInstance_cTribeModeStrategy
struct CActor_s00cd_45c0 {                                               // SP::cNearNoun-ish
    void*  FUN_00c6cbf0();                                    // 0x00c6cbf0
    void*  GetPosition();                                     // 0x00c6acc0
    void*  FUN_00c6bdc0();                                    // 0x00c6bdc0
    void   FUN_00c69ff0(void* p);                             // 0x00c69ff0
    void*  FUN_00c22f50();                                    // 0x00c22f50
    void*  FUN_00c8e820(int idx);                             // 0x00c8e820
    void*  FUN_00c93a40();                                    // 0x00c93a40
    float  FUN_00cee380();                                    // 0x00cee380
    void*  FUN_00ce6260(void* a, int b);                      // 0x00ce6260
    void*  FUN_00bfc5f0();                                    // 0x00bfc5f0 (GetPlayerTribe)
    void   FUN_00b16270();                                    // 0x00b16270
};
extern void*  g_appProps;                                     // 0x015fd918
extern void*  g_propList881288;                               // 0x01581288
extern void*  g_testSystem;                                   // 0x015fd928
extern uint32_t g_arr157f528[];                               // 0x0157f528
extern uint32_t g_arr14774d8[];                               // 0x014774d8
extern uint8_t  g_157f524;                                    // 0x0157f524
extern uint8_t  g_157f525;                                    // 0x0157f525
extern float    g_169b2cc, g_169b2d0, g_169b2d4;              // 0x0169b2cc Vector3
extern const float g_1485548;                                 // 0x01485548  1.5f
extern const float g_14774d0;                                 // 0x014774d0  2500.0f
extern const float g_1485720;                                 // 0x01485720
extern void*  g_vt14774c4;                                    // 0x014774c4
#pragma intrinsic(sqrt)
#define NOINLINE __declspec(noinline)
struct cString {                                              // SP::cString (8 bytes)
    uint32_t mData[2];                                        // +0x00
    cString();                                                // 0x006b5060
    ~cString();                                               // 0x006b5240
    char* Load(int a, int b, int c);                          // 0x006b54b0
    const void* Get(int a, int b);                            // 0x006b55c0
};
void          FUN_00e806de0(void* w);                         // 0x00806de0
void*         NounManager();                                  // 0x00b3d300
void*         GetCameraCtl();                                 // 0x00b3d280
void*         App();                                          // 0x0067dd10
void*         GameTimeManager();                              // 0x00b3d380
void          FUN_00d48ae0();                                 // 0x00d48ae0
void*         __stdcall FUN_00b3d240(int fn);                 // 0x00b3d240
void*         FUN_00b3d3c0();                                 // 0x00b3d3c0
void          FUN_00b16270(void* p);                          // 0x00b16270
void          FUN_00b13bb0(void* a, void* b);                 // 0x00b13bb0
void*         FUN_00b6f0c0(int a);                            // 0x00b6f0c0
void          FUN_00b6e4b0(void* out, float, float, float, float, float); // 0x00b6e4b0
void          FUN_00b6f140(float, float, float);              // 0x00b6f140
void          FUN_00b6f180();                                 // 0x00b6f180
uint32_t      FUN_00b316c0();                                 // 0x00b316c0 (superseded by CTimeMgr)
void*         __stdcall FUN_0067de90(int a, void* b);         // 0x0067de90
struct CExt7ec160 { void* FUN_007ec160(); };                  // 0x007ec160 (thiscall)
struct CTimeMgr  { uint64_t FUN_00b316c0(); };                // 0x00b316c0 (thiscall)
void          FUN_00cd3ff0(int idx, void* p);                 // 0x00cd3ff0
int           FUN_00700c80(float* a, float* b, float* c, float d, int e); // 0x00700c80
float*        __fastcall FUN_0041ea70(void* prop);             // 0x0041ea70
float*        __fastcall FUN_0041e920(void* prop);             // 0x0041e920
uint32_t      FUN_00458a40(void* p);                          // 0x00458a40
void*         FUN_00f473a0(int size, const char* tag, int b, int c, int d, int e); // 0x00f473a0  EAAllocate
struct CWinMgr { void* FindWindowByID(int id); };              // 0x00e012b0
void*         FUN_00920090();                                 // 0x00920090
void*         SimTicker();                                    // 0x00b3d330
void          cTribe_FishingRegister(void* tribe);            // 0x00c9b6d0
uint64_t      __stdcall __aulldiv(uint64_t a, uint64_t b);     // 0x011e0970
void*         FUN_00883860();                                 // 0x00883860  EA::Messaging::GetServer
struct CSub {                                                 // track subobject (own vfptr; vcall slot 0x54/0xac)
    void*    mpVtbl;                                          // +0x00
    uint32_t m04;                                             // +0x04 (state flags)
    uint32_t pad08[(0x5c - 0x08) / 4];
    uint8_t  m5c;                                             // +0x5c (kind)
};
struct CListNode {                                            // list node with an embedded CSub at +0xc0
    uint32_t pad00[0xc0 / 4];
    CSub     mSub;                                            // +0xc0
};
struct CInfoBlock {                                           // result payload (0x1c bytes) of FUN_00cd52e0
    int      m00;                                             // +0x00
    int      m04;                                             // +0x04
    int      m08;                                             // +0x08
    float    m0c;                                             // +0x0c
    float    m10;                                             // +0x10
    float    m14;                                             // +0x14
    int      m18;                                             // +0x18
};
struct CRetObj {                                              // object returned by FUN_007ec160
    uint32_t   pad00[0xc / 4];
    CInfoBlock* mpInfo;                                       // +0x0c
    void       FUN_007eb820(int n);                           // 0x007eb820
};
#define VSLOT(p, off)  ((*(void***)(p))[(off) / 4])
typedef void*  (__thiscall *TC1)(void*, int);
typedef void   (__thiscall *TC1v)(void*, int);
typedef void*  (__thiscall *TC2v)(void*, int, void*);
typedef char   (__thiscall *TC2b)(void*, int, int*);
typedef void   (__thiscall *TCCv)(void*, char*);
typedef void   (__thiscall *TCvi)(void*, void*, int);
typedef void*  (__thiscall *TC4)(void*, int, int, int, int);
struct CTexPreload {                                          // 0x007b07e0
    void*  ctor(int a);                                       // 0x007b07e0
    void   clear();                                           // 0x007b1950
    void   preloadListVoid(void* a);                          // 0x007b1de0
    void   preloadListKey(void* a);                           // 0x007b1e90
};
struct CExt72880 { void* call(); };                           // 0x00b72880
struct CExt33ce0 { void* call(); };                           // 0x00b33ce0
struct cRefBase;
struct CRefHolder {                                           // cTribeViewHolder-ish
    void*     mpVtbl;                                         // +0x00
    void*     mp04;                                           // +0x04
    cRefBase* mp08;                                           // +0x08
    uint8_t   mb0c;                                           // +0x0c
    void* FUN_00cd4720(void* a, cRefBase* p);                 // 0x00cd4720
};
struct CIcon {                                                // tribe icon widget
    void FUN_00b13bb0(void* a);                               // 0x00b13bb0
    void FUN_00b16270();                                      // 0x00b16270
};
struct CTribeMode {
    char FUN_00cd4c70(int a);                                 // 0x00cd4c70
    bool FUN_00cd54f0();                                      // 0x00cd54f0
    void FUN_00cd53e0();                                      // 0x00cd53e0
    void FUN_00cd50b0(int a, void* m);                        // 0x00cd50b0
};
struct CExt33cf0 { void* call(); };                           // 0x00b33cf0
struct CExtBC3170 { void call(); };                           // 0x00bc3170
struct CExtF67D90 { void* call(); };                          // 0x00f67d90
struct CDisplayStrategy {                                     // SP::cTribeDisplayStrategy
    void  attach(void* a);                                    // 0x00ccc400
    void  SetNestIcon(void* icon, int b);                     // 0x00cc9640
    void  detach(void* a);                                    // 0x00ccbb60
};
struct CIdLookup {
    virtual void  v00();                                      // +0x00
    virtual void  v04();                                      // +0x04
    virtual void  v08();                                      // +0x08
    virtual void* get(int id);                                // +0x0c
};
struct cRefBase {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};
// ---- items of slice s00cd45c0 end

// ---- items of slice s00cd5550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float   g_fltmax;         // 0x01477430
extern const float   g_flt_158133c;    // 0x0158133c
extern void*         g_169b054;        // 0x0169b054 SimSingleton
extern void*         g_157f290;        // 0x0157f290
extern const char    g_StrSimulator[];     // 0x013f09b4 "Simulator"
extern const char    g_StrSimSingleton[];  // 0x0145f924 "Simulator/SimSingleton"
struct Stream;                      // EA::IO::IStream-like, slots 0x18/0x1c/0x20
struct StreamInner {                // result of slot 0x20, slot 0x18 gives the write target
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
    virtual void* Write_18();       // 0x18
};
struct Stream {
virtual void k0();
virtual void k1();
virtual void k2();
virtual void k3();
virtual void k4();
virtual void k5();
virtual void k6();
    virtual void End_1c();          // 0x1c
    virtual StreamInner* Get_20();  // 0x20
};
struct RefObj {                     // simple refcounted: AddRef slot 0, Release slot 1
virtual void AddRef();
virtual void Release();
};
struct RefMgr {                     // AddRef slot 1, Release slot 2, Update slot 7(0x1c); size 0x98
    RefMgr();
    void* operator new(size_t n, const char* tag, int a, int b, int c, int d);
virtual void v0();
virtual void AddRef();
virtual void Release();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void Update_1c();       // 0x1c
    virtual void SendMsg_20();      // 0x20
    uint32_t pad[0x25];             // +0x24..+0x97  (vptr 4 + 0x94 = 0x98)
};
struct cSPVector3_s00cd_5550 { float x, y, z; };
extern unsigned char g_vt14774c4_s00cd_5550;      // 0x014774c4 element vtable
bool  EA_IO_WriteUint32(void* inner, const uint32_t* p, int count, int flags); // 0x0093aa70
void* EA_operator_new(uint32_t size, const char* tag, int a, int b, int c, int d); // 0x00f473a0
void  EA_Messaging_RemoveHandler(void* h, void* a, void* b, void* c, void* d);  // 0x00571db0
void* PropertyManager();                             // 0x0067de30
void* GonzagoModelWorld();                           // 0x00b3d520
void* GetSetting9();                                 // 0x00401090
void* FUN_01021260();                                // 0x01021260
void* FUN_01021230();                                // 0x01021230
void* PlanetModel();                                 // 0x00b3d350
void* Property_GetUInt(void* prop);                  // 0x0041ea00
void* interface_cast_0xd1c610(void* p, int a);       // 0x00d1c610
struct SimSingleton { void* Init(); };                  // 0x00cc5a70 ctor helper (returns this)
struct C20Obj { void clear(); };                       // 0x007b1950 ?clear@C20
struct cTribeDisplayStrategy { void Deactivate(); };   // 0x00ccd050
struct Obj1c8 { void Method(); };                       // 0x00bc21c0
void* FUN_0067cac0(void);                            // 0x0067cac0  returns g_15fcc54
void  FUN_0067c830(void* self, uint32_t hash);       // 0x0067c830  thiscall, ret 4
void* SP_GetCamRotateTrigger();                      // 0x00cd3e60
void  FUN_00b706a0(void* self, uint32_t hash);       // 0x00b706a0 (thiscall ret 4)
void* FUN_0067de90(int a);                           // 0x0067de90
void* FUN_007eb100(void* self);                      // 0x007eb100
unsigned char FUN_00c8e850(void* self);              // 0x00c8e850
unsigned char FUN_00c8e870(void* self);              // 0x00c8e870
class cVarListSerializer {
public:
    uint32_t mData[0x26e];
    cVarListSerializer(void* varList, void* a, int b);  // 0x00692f90
    bool Serialize(Stream* s);                          // 0x00692900
};
struct cTribe {
    uint32_t GetAdultPopulation();   // 0x00c8f3a0  thiscall
    uint32_t GetMaxPopulation();     // 0x00c8eae0  thiscall
};
struct cGameNounManager {
    void* GetPlayerTribe();          // 0x00bfc5f0  thiscall, no args
};
class cTribeModeStrategy {
public:
    uint32_t pad00[8];             // +0x00..+0x1f
    unsigned char* mTribePathsBegin; // +0x20  (vector<path> begin)
    unsigned char* mTribePathsEnd;   // +0x24
    uint32_t pad28[6];             // +0x28..+0x3f
    unsigned char* mPtr_40;        // +0x40
    unsigned char* mPtr_44;        // +0x44
    uint32_t pad48[0x60];          // +0x48..+0x1c7
    void* mp_1c8;                  // +0x1c8
    void* mp_1cc;                  // +0x1cc  (first RemoveHandler arg)
    void* mp_1d0;                  // +0x1d0
    void* mp_1d4;                  // +0x1d4
    void* mp_1d8;                  // +0x1d8
    void* mp_1dc;                  // +0x1dc
    uint32_t pad1e0[0x12];         // +0x1e0..+0x227
    unsigned char mb_228;          // +0x228
    unsigned char pad229[0x13];    // +0x229..+0x23b
    void* mp_23c;                  // +0x23c
    void* mp_240;                  // +0x240
    uint32_t pad244[4];            // +0x244..+0x253
    void* mp_254;                  // +0x254
    uint32_t pad258[0x4f];         // +0x258..+0x393
    void* mp_394;                  // +0x394  mission manager / next strategy
    void* mp_398;                  // +0x398  effect object
    uint32_t pad39c[1];            // +0x39c..+0x39f
    unsigned char pad3a0[3];       // +0x3a0..+0x3a2
    unsigned char mb_3a3;          // +0x3a3

    unsigned char F_cd5550();
    bool          Write(Stream* s);
    void          F_cd56e0();
    int           F_cd5750();
    unsigned char TerrainNotHasKey();   // 0x00cd44a0  thiscall (external, other slice)
    bool          F_cd5e40();
    void          F_cd6390(unsigned char enable);
    void          F_cd6130(uint32_t id);
};
struct TribePath {
    unsigned char* mpBegin;  // +0x00
    unsigned char* mpEnd;    // +0x04
    unsigned char* mpCap;    // +0x08
    uint32_t mExtra[2];      // +0x0c
};
struct TribeVec {
    unsigned char* mpBegin;  // +0
    unsigned char* mpEnd;    // +4
    unsigned char* mpCap;    // +8
};
typedef bool (__cdecl *TribePred)(void* elem);
struct Elem16 { virtual void AddRef_0(); virtual void Write_4(Stream* s); virtual void Release_8(); };
struct ElemRef {
    void* mpVtbl;             // +0
    uint32_t m4;              // +4
    RefObj* volatile mp8;     // +8  (volatile reproduces cl's load ordering)
    unsigned char m0c;        // +0xc
};
struct SettingObj { void Method(); };                              // 0x004df420
struct MgrA       { void* Get(uint32_t hash, RefObj** out); };     // 0x00c8b370
struct MgrB       { void* Get_713e0(); };                          // 0x00c713e0
struct PropObj {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual unsigned char GetProp(uint32_t hash, RefObj** out);    // +0x24
};
struct PropValue { unsigned char mPad00[0x12]; uint16_t mType; };
struct PMObj     { void Method_8d8a0(void* e, int a, int b); };     // 0x00b8d8a0
struct cTribeSensors {
    unsigned char Test1();                       // 0x00c8e870  thiscall
    unsigned char Test2();                       // 0x00c8e850  thiscall
};
struct WorldObj {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void Notify(RefObj* p, int v);       // +0x18
};
// ---- items of slice s00cd5550 end

// ---- items of slice s00cd6680 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
void __cdecl operator_delete_array(void* p);   // 0x00f47380
struct cWString {
    void* mpBegin;                 // 0x00
    void* mpEnd;                   // 0x04
    void* mpCap;                   // 0x08
    u8    mPad00c[0x10 - 0x0c];

    void  assign(const void* first, const void* last);  // 0x00423650
};
struct cPosseInfo {
    cWString mName;                // 0x00
    float    mField10;             // 0x10
    int      mField14;             // 0x14
    int      mField18;             // 0x18
};
// ---- items of slice s00cd6680 end

// ---- items of slice s00cd75f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern "C" void GameDataVectorBaseCtor();                    // 0x00b1e540
namespace Simulator {
struct tGameDataVectorT {
    void*    mpVtable;                                       // +0x00
    uint32_t mValue04;                                       // +0x04
    uint32_t mValue08;                                       // +0x08
    uint32_t mValue0c;                                       // +0x0c
};  // namespace Simulator
}
// ---- items of slice s00cd75f0 end

// ---- items of slice s00cd8e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPCreatureBase_s00cd_8e70;
}
namespace SP {
struct cLoco;
}
namespace SP {
struct CreatureList {                                   // eastl::vector<cSPCreatureBase*>
    cSPCreatureBase_s00cd_8e70** mpBegin;                          // +0x00
    cSPCreatureBase_s00cd_8e70** mpEnd;                            // +0x04
    cSPCreatureBase_s00cd_8e70** mpCapacity;                       // +0x08
};
}
namespace SP {
struct cTribe_s00cd_8e70 {
    void* mpVtable;                                     // +0x00
    uint32_t mPad04[0x8c];                              // +0x04 .. +0x233
    uint32_t mTribeId;                                  // +0x234
};
}
namespace SP {
struct cGameNounManager_s00cd_8e70 {
    cTribe_s00cd_8e70* GetPlayerTribe();                           // 0x00bfc5f0
};
}
namespace SP {
struct cLoco {
    void* mpVtable;                                     // +0x00
    bool CanBeSelected() {
        return ((bool (__thiscall*)(cLoco*))((void**)mpVtable)[0x50 / 4])(this);
    }
};
}
namespace SP {
struct cSPCreatureBase_s00cd_8e70 {
    void* mpVtable;                                     // +0x00
    uint32_t mPad04[47];                                // +0x04 .. +0xbf
    cLoco mLoco;                                        // +0xc0
    uint32_t mPadC4[0x29d];                             // +0xc4 .. +0xb37
    uint32_t mNameBegin;                                // +0xb38 (eastl::wstring)
    uint32_t mNameEnd;                                  // +0xb3c
    uint32_t mNameCapacity;                             // +0xb40
};
}
namespace SP {
struct cGonzagoTimer_s00cd_8e70 {
    uint32_t mData[8];                                  // 0x20 bytes
};
}
namespace SP {
struct cLocalInputState_s00cd_8e70 {
    uint32_t mData[0x48 / 4];                           // 0x48 bytes
};
}
namespace SP {
extern char VT_14426a0[];
}
namespace SP {
extern char VT_13eb394[];
}
namespace SP {
extern char VT_14775f0[];
}
namespace SP {
extern char VT_14775e8[];
}
namespace SP {
extern char VT_1477648[];
}
namespace SP {
extern char VT_1477640[];
}
namespace SP {
class cTribeModeStrategy_s00cd_8e70;
}
namespace SP {
extern cTribeModeStrategy_s00cd_8e70* gpTribeModeStrategy;         // 0x0169b2c8
}
namespace SP {
cGameNounManager_s00cd_8e70* __cdecl NounManager_s00cd_8e70();                // 0x00b3d300
}
namespace SP {
void __fastcall cGonzagoSubsystem_ctor(void* p);        // 0x00b5b960
}
namespace SP {
void __fastcall cGonzagoTimer_ctor(void* p);            // 0x00b63890
}
namespace SP {
void __fastcall cLocalInputState_ctor(void* p);         // 0x00697960
}
namespace SP {
struct SelSetIter { void* mp0; void* mp1; };
}
namespace SP {
struct SelSet {
    uint32_t m00;                                       // +0x00
    void*    mpAnchor;                                  // +0x04
    void*    mpAnchorLeft;                              // +0x08
    void*    mpRoot;                                    // +0x0c
    uint32_t mFlags;                                    // +0x10
    uint32_t mCount;                                    // +0x14
    uint32_t m18;                                       // +0x18

    void Initialize();
    ~SelSet() { Nuke(mpRoot); }
    void Nuke(void* root);                              // 0x00eb6280
    void Insert(SelSetIter* out, void* key, bool b);    // 0x00eb62c0
};
}
namespace SP {
inline void SelSet::Initialize()
{
    mpAnchorLeft = 0;
    mpRoot = 0;
    mFlags = 0;
    mpAnchor = &mpAnchor;
    mpAnchorLeft = &mpAnchor;
    mpRoot = 0;
    mFlags = 0;
    mCount = 0;
};
}
namespace SP {
struct TribeRecord {                                    // 0x1c bytes
    uint32_t mNameBegin;                                // +0x00 (eastl::wstring)
    uint32_t mNameEnd;                                  // +0x04
    uint32_t mNameCapacity;                             // +0x08
    uint32_t m0c;                                       // +0x0c
    float    mRadius;                                   // +0x10
    int      mId;                                       // +0x14
    void*    mpProfile;                                 // +0x18
};
}
namespace SP {
struct TribeSub {                                       // lives at strategy + 0xa8
    uint32_t m00;                                       // +0x00
    uint32_t m04;                                       // +0x04
    uint32_t m08;                                       // +0x08
    uint32_t m0c;                                       // +0x0c
    float    m10;                                       // +0x10
    float    m14;                                       // +0x14
    uint32_t m18;                                       // +0x18
    uint32_t mPad1c[6];                                 // +0x1c .. +0x33
    uint32_t m34;                                       // +0x34
    uint32_t mPad38[9];                                 // +0x38 .. +0x5b
    uint32_t mPoolBegin;                                // +0x5c
    uint32_t mPad60[0x16];                              // +0x60 .. +0xbb
    uint32_t mPoolEnd;                                  // +0xbc

    TribeSub* Init(int arg1, int arg2);                 // 0x00cd91e0
    void Configure(int a1, int a2, int a3, int a4, int a5, void* pool);  // 0x00cd6560
    uint32_t PoolSize(uint32_t n);                      // 0x009213c0
    void GrowTo(uint32_t n);                            // 0x00b5d220
};
}
namespace SP {
class cTribeModeStrategy_s00cd_8e70 {
public:
    // Primary vtable: 25 unnamed slots, then the selected-set getter at +0x64.
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual void v24();
    virtual SelSet* GetSelectedCreatureSet(SelSet* out);        // +0x64 0x00cd9ce0

    void*    mpVtbl1;                                   // +0x04
    void*    mpVtbl2;                                   // +0x08
    void*    mpVtbl3;                                   // +0x0c
    void*    mpVtbl4;                                   // +0x10
    uint32_t m14;                                       // +0x14
    uint32_t m18;                                       // +0x18
    uint32_t m1c;                                       // +0x1c
    uint32_t m20;                                       // +0x20
    uint32_t m24;                                       // +0x24
    bool     mbInCityHallEditor;                        // +0x28
    bool     mbInAccessoryEditor;                       // +0x29
    uint16_t m2a;                                       // +0x2a
    uint32_t m2c;                                       // +0x2c
    uint32_t m30;                                       // +0x30
    uint32_t m34;                                       // +0x34
    uint32_t m38;                                       // +0x38
    uint32_t m3c;                                       // +0x3c
    uint32_t m40;                                       // +0x40
    uint32_t m44;                                       // +0x44
    uint32_t m48;                                       // +0x48
    uint32_t m4c;                                       // +0x4c
    uint32_t m50;                                       // +0x50
    uint32_t m54;                                       // +0x54
    cGonzagoTimer_s00cd_8e70 mTimer;                               // +0x58
    uint32_t m78;                                       // +0x78
    uint32_t m7c;                                       // +0x7c
    uint32_t m80;                                       // +0x80
    uint32_t m84;                                       // +0x84
    uint32_t m88;                                       // +0x88
    uint32_t m8c;                                       // +0x8c
    uint32_t m90;                                       // +0x90
    uint32_t m94;                                       // +0x94
    uint32_t m98;                                       // +0x98
    uint32_t m9c;                                       // +0x9c
    uint32_t ma0;                                       // +0xa0
    uint32_t ma4;                                       // +0xa4
    TribeSub mSub;                                      // +0xa8 .. +0x197
    bool     mb198;                                     // +0x198
    uint32_t m19c;                                      // +0x19c
    float    m1a0;                                      // +0x1a0
    bool     mb1a4;                                     // +0x1a4
    cGonzagoTimer_s00cd_8e70 mTimer2;                              // +0x1a8
    uint32_t m1c8;                                      // +0x1c8
    uint32_t m1cc;                                      // +0x1cc
    uint32_t m1d0;                                      // +0x1d0
    uint32_t m1d4;                                      // +0x1d4
    uint32_t m1d8;                                      // +0x1d8
    uint32_t m1dc;                                      // +0x1dc
    cLocalInputState_s00cd_8e70 mInput;                            // +0x1e0
    bool     mb228;                                     // +0x228
    uint32_t m22c;                                      // +0x22c
    int32_t  m230;                                      // +0x230
    int32_t  m234;                                      // +0x234
    uint32_t m238;                                      // +0x238
    uint32_t m23c;                                      // +0x23c
    uint32_t m240;                                      // +0x240
    uint32_t m244;                                      // +0x244
    bool     mb248;                                     // +0x248
    bool     mb249;                                     // +0x249
    bool     mb24a;                                     // +0x24a
    uint32_t m24c;                                      // +0x24c
    uint32_t m250;                                      // +0x250
    uint32_t m254;                                      // +0x254
    uint32_t m258[0x9c / 4];                            // +0x258 .. +0x2f3
    uint32_t m2f8;                                      // +0x2f8
    uint32_t m2fc;                                      // +0x2fc
    TribeRecord* mpRecordBegin;                         // +0x304
    TribeRecord* mpRecordEnd;                           // +0x308
    TribeRecord* mpRecordCapacity;                      // +0x30c
    uint32_t m310;                                      // +0x310
    uint32_t m314;                                      // +0x314
    uint32_t m318;                                      // +0x318
    TribeRecord maRecordBuffer[4];                      // +0x31c .. +0x38b
    uint32_t m38c;                                      // +0x38c
    uint32_t m390;                                      // +0x390
    uint32_t m394;                                      // +0x394
    uint32_t m398;                                      // +0x398
    uint32_t m39c;                                      // +0x39c
    bool     mb3a0;                                     // +0x3a0
    uint8_t  m3a1;                                      // +0x3a1
    uint8_t  m3a2;                                      // +0x3a2
    uint8_t  mb3a3;                                     // +0x3a3

    cTribeModeStrategy_s00cd_8e70();                               // 0x00cd9a10
    void RefreshSelectedCreatures();                    // 0x00cd8e70
    uint32_t GetSelectedCreatureCount();                // 0x00cd91b0
};
}
namespace SP {
struct Elem12 {
    uint32_t m00, m04, m08;
};
}
namespace SP {
void __stdcall GrowVec12(Elem12* end, const Elem12* v); // 0x00b535d0
}
namespace SP {
struct Vec12 {
    Elem12* mpBegin;                                    // +0x00
    Elem12* mpEnd;                                      // +0x04
    Elem12* mpCapacity;                                 // +0x08
    void push_back(const Elem12& v);
};
}
namespace SP {
struct Elem16_s00cd_8e70 {
    void*    mpVtable;                                  // +0x00
    void*    mp04;                                      // +0x04
    void*    mp08;                                      // +0x08
    uint8_t  mb0c;                                      // +0x0c
};
}
namespace SP {
void* __cdecl FUN_00cd5a90(Elem16_s00cd_8e70* a, Elem16_s00cd_8e70* b, Elem16_s00cd_8e70* c);       // 0x00cd5a90
}
namespace SP {
struct Vec16 {
    Elem16_s00cd_8e70* mpBegin;                                    // +0x00
    Elem16_s00cd_8e70* mpEnd;                                      // +0x04
    Elem16_s00cd_8e70* mpCapacity;                                 // +0x08
    void DestroyRange(Elem16_s00cd_8e70* first, Elem16_s00cd_8e70* last);      // 0x00cd9440
    void InsertOne(Elem16_s00cd_8e70* pos, Elem16_s00cd_8e70* v);              // 0x00cd9490
};
}
// ---- items of slice s00cd8e70 end

// ---- items of slice s00cdab10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef int            s32;
typedef float          f32;
#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))
struct COps {
    void  FUN_00bc3110();                          // 0x00bc3110 cSPTimer::Stop
    void  FUN_00bc3130();                          // 0x00bc3130 cSPTimer::Restart
    void* FUN_00bfc5f0();                          // 0x00bfc5f0 GetPlayerTribe
    void* FUN_00c90460();                          // 0x00c90460
    void* FUN_00c8e820();                          // 0x00c8e820 GetSlot0
    void  FUN_00c8dc10(u32, void*);                // 0x00c8dc10 TP_AddSegment
    void* FUN_00f67d90();                          // 0x00f67d90 GetCurrentTerrainSphere
    void* FUN_00b21340(void*, void*, void*, void*, void*); // 0x00b21340 GetGameDataVector
    void  FUN_00676e90(u32, u32);                  // 0x00676e90 AutoTest
    void  FUN_00b48770(u32);                       // 0x00b48770
    f32   FUN_00e3f7a0();                          // 0x00e3f7a0
    f32   FUN_00d05a20(void*, void*, void*);       // 0x00d05a20 CalculateRelationshipAbsolute
    void  FUN_00ad7a30(void*, void*);              // 0x00ad7a30 cActionTarget ctor
    void  FUN_00ad7ad0();                          // 0x00ad7ad0 cActionTarget dtor
    void  FUN_00adde90(u32, void*, void*);         // 0x00adde90 cStringContext
    void* FUN_00ae0930(u32, u32, u32, u32, u32, u32); // 0x00ae0930 PostTrigger
    void  FUN_00ae09b0(u32, void*);                // 0x00ae09b0 PostAction
    void  FUN_00c79f00(u32, void*);                // 0x00c79f00
    void  FUN_00cda370();                          // 0x00cda370 UpgradePlayerTribe
    void  FUN_00cd7c70(u32);                       // 0x00cd7c70
    void  FUN_00cd3ee0();                          // 0x00cd3ee0
    void* FUN_00cd4720(u32, u32);                  // 0x00cd4720 record ctor
    void  FUN_00ce0a20();                          // 0x00ce0a20 cTribePlanner::Shutdown
    u8    FUN_00c744e0(void*);                     // 0x00c744e0
};
void* __cdecl FUN_00b3d300();                       // 0x00b3d300 NounManager
void* __cdecl FUN_00b3d330();                       // 0x00b3d330 SimTicker
void  __cdecl FUN_00f47380(void*);                  // 0x00f47380 operator_delete_array
void* __cdecl FUN_00f473a0(u32, const char*, u32, u32, const char*, u32); // 0x00f473a0 operator_new
void* __cdecl FUN_00b3d2c0();                       // 0x00b3d2c0 RelationshipManager
s32   __cdecl FUN_00ac8fa0(u32, u32, u32);          // 0x00ac8fa0
void  __cdecl FUN_0093a780(void*, void*, u32, u32); // 0x0093a780 ReadInt32
void  __cdecl FUN_00567e70(u32*, void*);            // 0x00567e70
void* __cdecl FUN_011e0744(void*, const void*, u32); // 0x011e0744 memcpy
void  __cdecl FUN_00cd7010(void*);                  // 0x00cd7010
void  __cdecl FUN_00cd67b0(void*, void*, void*);    // 0x00cd67b0
void* __cdecl FUN_00cd70c0(void*, void*, void*);    // 0x00cd70c0
void  __cdecl FUN_00cd6710(void*, void*, void*);    // 0x00cd6710
void  __cdecl FUN_00cd6030(void*, void*);           // 0x00cd6030 eastl::wstring::assign
void  __cdecl FUN_00cd7d60(void*, u32, void*);      // 0x00cd7d60 uninitialized_fill_n
f32   __cdecl FUN_00cdb8b0();                       // 0x00cdb8b0
void* __cdecl FUN_00b3d410(u32);                    // 0x00b3d410
extern f32 gF_013f26dc;   // 0x013f26dc  ( 1/3)
extern f32 gF_0140d0cc;   // 0x0140d0cc  (-1/3)
extern f32 gF_013eb1bc;   // 0x013eb1bc  (-1.0)
extern f32 gF_01485720;   // 0x01485720  ( 1.0)
struct Rec16 {
    void* mpVtbl;         // 0x00
    void* mU_04;          // 0x04
    void* mpObj;          // 0x08
    u8    mB_0c;          // 0x0c
    u8    mPad0d[3];      // 0x0d
};
struct Rec1c {
    void* mpBegin;        // 0x00  eastl::wstring storage
    void* mpEnd;          // 0x04
    void* mpCap;          // 0x08
    u32   mU_0c;          // 0x0c
    u32   mU_10;          // 0x10
    u32   mU_14;          // 0x14
    u32   mU_18;          // 0x18
};
struct cSPVector3_s00cd_ab10 {
    f32 x, y, z;          // 0x00
    f32 mF_0c;            // 0x0c
    f32 mF_10;            // 0x10
};
struct TerrainSphere {
    u8  mPad0000[0x10f0];
    f32 mF_10f0;          // 0x10f0
    f32 mF_10f4;          // 0x10f4
};
struct PtrVec {
    u32    mU_00;         // 0x00
    void** mpBegin;       // 0x04
    void** mpEnd;         // 0x08
};
class cVec16 {
public:
    Rec16* mpBegin;       // 0x00
    Rec16* mpEnd;         // 0x04
    Rec16* mpCap;         // 0x08
    void FUN_00cd9440(Rec16*, Rec16*);  // 0x00cd9440
    void FUN_00cd9490(Rec16*, Rec16*);  // 0x00cd9490
    void FUN_00cd7c70(u32);             // 0x00cd7c70
    void FUN_00cdafb0(Rec16*);          // 0x00cdafb0
};
class cVec1c {
public:
    Rec1c* mpBegin;       // 0x00
    Rec1c* mpEnd;         // 0x04
    Rec1c* mpCap;         // 0x08
    void FUN_00cdb1f0(Rec1c*, Rec1c*);  // 0x00cdb1f0
    void FUN_00cdb430();                // 0x00cdb430
};
class cVec14 {
public:
    cSPVector3_s00cd_ab10* mpBegin;  // 0x00
    cSPVector3_s00cd_ab10* mpEnd;    // 0x04
    cSPVector3_s00cd_ab10* mpCap;    // 0x08
    void FUN_00cdb6a0(cSPVector3_s00cd_ab10*, u32, cSPVector3_s00cd_ab10*); // 0x00cdb6a0
};
class cTribeModeStrategy_s00cd_ab10 {
public:
    u8     mPad000[0x40];
    Rec16* mpHistBegin;   // 0x40
    Rec16* mpHistEnd;     // 0x44
    u8     mPad048[0x10];
    u8     mTimer[8];     // 0x58
public:
    void FUN_00cdab10();                // 0x00cdab10 IncrementGoalProgress
    void FUN_00cdb3a0(u32, u32);        // 0x00cdb3a0
    u32  FUN_00cdba50();                // 0x00cdba50
    void FUN_00cdba90();                // 0x00cdba90 UnregisterTribeSimulators
};
// ---- items of slice s00cdab10 end

// ---- items of slice s00cdd500 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gModelScale;                                        // 0x01485720
extern float gMinTribeRadius;                                    // 0x01581268
typedef unsigned short u16;
struct Vec3 { float x, y, z; };
struct Quat4 { float x, y, z, w; };
struct Mat3 { float m[9]; };
#define VSLOT_s00cd_d500(fnptr, obj, off) ((fnptr)((obj)->mpVtbl_00[(off) / 4]))
void ReadInt32(u32 h, void* pDst, s32 nCount, s32 nFlags);            // 0x0093a780
inline bool BlockIsAllocated(const void* p)
{
    return p != 0 && ((const u32*)p)[-1] != 0;
}
typedef Vec3 Key3;
struct KeyVec {
    Key3* mpBegin;
    Key3* mpEnd;
    Key3* mpCap;

    void Reserve(s32 n);                                        // 0x0041e4d0
    void DoInsertKey(Key3* pSlot, const Key3& value);            // 0x004e3e10
    Key3* Erase(Key3* pFirst, Key3* pLast);                      // 0x0050f740

    void PushBack(const Key3& value)
    {
        if (mpEnd < mpCap) {
            Key3* pSlot = mpEnd;
            ++mpEnd;
            if (pSlot)
                *pSlot = value;
        } else
            DoInsertKey(mpEnd, value);
    }

    void Destroy()
    {
        if (BlockIsAllocated(mpBegin))
            operator_delete_array(mpBegin);
    }
};
void SortKeys(Key3* pFirst, Key3* pLast);                        // 0x004f6b70
Key3* UniqueKeys(Key3* pFirst, Key3* pLast);                     // 0x004f6830
struct cPoly {
    void** mpVtbl_00;
};
void F_cd7d10();
void F_d3d420();
void F_accc30();
void F_ace070();
void F_accbb0();
void F_b1e500();
template <class T>
struct PtrVec_s00cd_d500 {
    T** mpBegin;
    T** mpEnd;
    T** mpCap;
};
template <class T>
struct NounVecOut {
    u32 mHeader_00;
    PtrVec_s00cd_d500<T> mItems_04;
};
struct cGameNounManager_s00cd_d500 {
    void* GetPlayerTribe();                                      // 0x00bfc5f0
    void* GetGameDataVector(void (*)(), void (*)(), void (*)(), void (*)(), u32); // 0x00b21340
};
cGameNounManager_s00cd_d500* NounManager_s00cd_d500();                                 // 0x00b3d300
struct cEffectsManager {
    void** mpVtbl_00;
};
struct cMsgSink {
    void** mpVtbl_00;
    void OnModeChange(u32 previousMode, u32 newMode)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cMsgSink*, u32, u32), this, 0x14)(this, previousMode, newMode);
    }
};
struct cBehaviorManager {
    u32 mPad_00;
    cMsgSink mSink_04;
};
cBehaviorManager* BehaviorManager();                             // 0x00b3d260
cEffectsManager* EffectsManagerPtr();                            // 0x0067ddd0
cPoly* PropertyManager_s00cd_d500();                                        // 0x0067de30
cPoly* GameInputManager();                                       // 0x00b3d250
cPoly* SimTicker_s00cd_d500();                                              // 0x00b3d330
cPoly* GetGameTerrainCursor_s00cd_d500();                                   // 0x00b30d70
cPoly* GetPlanetModel();                                         // 0x00b3d350
cPoly* GetTerraformingManager();                                 // 0x00b3d430
struct cTickerClient {
    void** mpVtbl_00;
    void Activate()
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cTickerClient*), this, 0x20)(this);
    }
};
struct cSimTicker {
    void** mpVtbl_00;
    void QueueFlush(cTickerClient* pObject)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cSimTicker*, cTickerClient*), this, 0x54)(this, pObject);
    }
};
struct cCitySimulator {
    void PostMsg();                                              // 0x00ae6570
};
cTickerClient* FUN_00cc8b10();                                   // 0x00cc8b10
cCitySimulator* FUN_00bd83e0();                                  // 0x00bd83e0
cTickerClient* FUN_00d51660();                                   // 0x00d51660
struct cCommunityEditor {
    void** mpVtbl_00;
    void Deactivate(bool bA, bool bB);                            // 0x00d100b0
};
struct cEditorHost {
    void** mpVtbl_00;
    u8 mPad_04[0x58];
    cCommunityEditor* mpEditor_5c;

    void Shutdown()
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cEditorHost*), this, 0x08)(this);
    }
    void ReleaseOwnership(s32 nMode)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cEditorHost*, s32), this, 0x00)(this, nMode);
    }
};
bool FUN_00d09660(cPoly* pEditor);                               // 0x00d09660
u32 FUN_00d09670(cPoly* pEditor);                                // 0x00d09670
struct RefCounted {
    void** mpVtbl_00;
    void Release()
    {
        VSLOT_s00cd_d500(void (__thiscall*)(RefCounted*), this, 0x04)(this);
    }
    void ReleaseEx()
    {
        VSLOT_s00cd_d500(void (__thiscall*)(RefCounted*), this, 0x08)(this);
    }
};
struct cTribeDisplayStrategy_s00cd_d500 {
    u8 mPad_000[0x3c];
    RefCounted mRef_3c;
    void Deactivate();                                           // 0x00ccd050
};
struct cTribeToolSlot {
    void** mpVtbl_00;
    void SetTool(u32 nToolId)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cTribeToolSlot*, u32), this, 0x00)(this, nToolId);
    }
};
struct cTribeWorkArea {
    void** mpVtbl_00;
    const Vec3* GetCenter()
    {
        return VSLOT_s00cd_d500(const Vec3* (__thiscall*)(cTribeWorkArea*), this, 0x2c)(this);
    }
    void Transform(const Vec3* pPoint)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cTribeWorkArea*, const Vec3*), this, 0x38)(this, pPoint);
    }
    bool IsPrime()
    {
        return VSLOT_s00cd_d500(bool (__thiscall*)(cTribeWorkArea*), this, 0x58)(this);
    }
};
struct ToolNode {
    ToolNode* mpRight_00;
    ToolNode* mpLeft_04;
    ToolNode* mpParent_08;
    u32 mColor_0c;
    u32 mKey_10;
    u32 mValue_14;
};
struct ToolTree {
    u32 mCompare_00;
    ToolNode mAnchor_04;

    ToolNode* Find(u32 key)
    {
        ToolNode* pNode = mAnchor_04.mpParent_08;
        ToolNode* pLower = &mAnchor_04;
        while (pNode != 0) {
            if (pNode->mKey_10 < key)
                pNode = pNode->mpRight_00;
            else {
                pLower = pNode;
                pNode = pNode->mpLeft_04;
            }
        }
        if (pLower == &mAnchor_04 || key < pLower->mKey_10)
            return &mAnchor_04;
        return pLower;
    }
};
struct cNamedInserter {
    void** mpVtbl_00;
};
void FUN_00b6f380(cNamedInserter* pInserter, const void* pName);  // 0x00b6f380
struct cTribe_s00cd_d500 {
    void** mpVtbl_00;
    u8 mPad_004[0x30];
    cTribeToolSlot mToolSlot_034;
    u8 mPad_038[0xe8];
    cTribeWorkArea mWorkArea_120;
    u8 mPad_124[0x10c];
    cNamedInserter mNamedInserter_230;
    cTribeDisplayStrategy_s00cd_d500* mpDisplayStrategy_234;
    ToolTree mToolTree_238;

    void UpdateGridAndHutArea(float fDistance);                  // 0x00c99550
    void ResetToolLayout();                                      // 0x00c951d0
    void ReserveToolsSlots(bool bReserve);                       // 0x00c998c0
};
struct cPlanetTree {
    u8 mPad_000[0xbc];
    Vec3* mpBegin_0bc;
    Vec3* mpEnd_0c0;
};
struct cPlanet {
    u8 mPad_000[0x13c];
    cPlanetTree* mpTree_13c;
};
struct cStarManager {
    void** mpVtbl_00;
    void BuildTribeSites(cPlanetTree* pTree, void* pParams)      // 0x00bb5930
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cStarManager*, cPlanetTree*, void*), this, 0x00)(this, pTree, pParams);
    }
};
cStarManager* StarManager();                                     // 0x00b3d2a0
cPlanet* FUN_01021260_s00cd_d500();                                         // 0x01021260
void FUN_00c71560(cPlanet* pPlanet, s32 nMode);                  // 0x00c71560
void FUN_00c73310(cPlanet* pPlanet);                             // 0x00c73310
void FUN_00c73330(cPlanet* pPlanet);                             // 0x00c73330
bool FUN_00c70c00(cPlanet* pPlanet);                             // 0x00c70c00
void FUN_00c82f80(void* pOwner);                                 // 0x00c82f80
struct PlanetSearchParams {
    u32 mRangeX_00;          // 0x7f
    u32 mRangeY_04;          // 0x3f
    u32 mRangeZ_08;          // 0x3f
    u8  mFlagA_0c;
    u8  mFlagB_0d;
    u8  mFlagC_0e;
    u8  mEnabled_0f;         // 1
    u32 mCountX_10;          // 0xf
    u32 mCountY_14;          // 0xf
    u32 mFlags_18;
    u32 mFlags2_1c;
    KeyVec mKeys_20;
    u8  mUnset_2c[8];        // not touched by the constructor
    KeyVec mPoints_34;

    PlanetSearchParams();                                    // 0x00ba7bd0
};
struct cPlacement {
    void** mpVtbl_00;

    const Vec3* GetPosition()
    {
        return VSLOT_s00cd_d500(const Vec3* (__thiscall*)(cPlacement*), this, 0x2c)(this);
    }
    const Quat4* GetRotation()
    {
        return VSLOT_s00cd_d500(const Quat4* (__thiscall*)(cPlacement*), this, 0x30)(this);
    }
};
struct cNoun {
    void** mpVtbl_00;
    u8 mPad_004[0x30];
    cPlacement mPlacement_034;
    u8 mPad_038[0x6c];
    cPoly* mpCell_a4;
    u8 mPad_0a8[0x60];
    u32 mNounType_108;
    u8 mPad_10c[0x10];
    u32 mTerraformSlot_11c;
    cTribeWorkArea mWorkArea_120;

    bool IsRemoved()
    {
        return VSLOT_s00cd_d500(bool (__thiscall*)(cNoun*), this, 0x2c)(this) != 0;
    }
    void GetLinkedObjects(PtrVec_s00cd_d500<cPoly>* pOut)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cNoun*, PtrVec_s00cd_d500<cPoly>*), this, 0x90)(this, pOut);
    }
};
struct cCell {
    u8 mPad_000[0x504];
    Vec3 mPosition_504;
};
struct cSurfaceCell {
    u8 mData[0x14];
};
struct cSurfaceCellList {
    u8 mPad_00[0x2c];
    cSurfaceCell* mpBegin_2c;
    cSurfaceCell* mpEnd_30;
};
extern cSurfaceCellList* gSurfaceCellList;                       // 0x0169b2c8
struct cTerraformingManager {
    void** mpVtbl_00;
    u32 AddPoke(const Vec3* pPosition, float fRadius)             // 0x00bbf730
    {
        return VSLOT_s00cd_d500(u32 (__thiscall*)(cTerraformingManager*, const Vec3*, float), this, 0x00)(this, pPosition, fRadius);
    }
    void AddSurfacePoint(cSurfaceCell* pCell, s32 nMode)          // 0x00bbd730
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cTerraformingManager*, cSurfaceCell*, s32), this, 0x00)(this, pCell, nMode);
    }
    void Commit()                                                // 0x00bbc400
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cTerraformingManager*), this, 0x00)(this);
    }
};
struct cPropertyList {
    void** mpVtbl_00;
    void Release()
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cPropertyList*), this, 0x04)(this);
    }
};
float GetPropertyFloat(cPropertyList* pList, u32 nKey, float fDefault); // 0x004e1c70
struct ModelInstance {
    u16 mFlags_00;
    u16 mCount_02;
    Vec3 mOrigin_04;
    float mScale_10;
    Mat3 mRotation_14;
};
Mat3 Matrix3FromQuaternion(const Quat4* pQuat);                  // 0x0059c190
struct cRenderEntity {
    void** mpVtbl_00;
    void AddInstance(const ModelInstance* pInstance, cPropertyList* pProperties)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cRenderEntity*, const ModelInstance*, cPropertyList*), this, 0x54)(this, pInstance, pProperties);
    }
};
struct cPlanetModel {
    void** mpVtbl_00;
    u8 mPad_004[0x20];
    cRenderEntity* mpEntity_024;

    bool RayCast(const Vec3* pStart, float fMaxDistance, Vec3* pOut,
                 float fScale, s32 nFlagsA, s32 nFlagsB)         // 0x00b88770
    {
        return VSLOT_s00cd_d500(bool (__thiscall*)(cPlanetModel*, const Vec3*, float, Vec3*, float, s32, s32),
                     this, 0x00)(this, pStart, fMaxDistance, pOut, fScale, nFlagsA, nFlagsB);
    }
};
extern Vec3 gDefaultOrigin;                                      // 0x0169b2cc
extern Mat3 gDefaultRotation;                                    // 0x0169b378
extern const u8 gPrimeToolLabel;                                 // 0x0157ef54
void FUN_00b6c280();                                             // 0x00b6c280
void FUN_00cd49a0();                                             // 0x00cd49a0
void FUN_00cc8940(cTribeDisplayStrategy_s00cd_d500* pStrategy, s32 nMode);   // 0x00cc8940
void FUN_00cc93b0(cTribeDisplayStrategy_s00cd_d500* pStrategy, s32 nMode);   // 0x00cc93b0
cPoly* FUN_0067ddc0();                                           // 0x0067ddc0
void* FUN_00cd4770(void* pNoun, void* pTribe);                   // 0x00cd4770
u32 __fastcall FUN_00b6f0c0(cTribeDisplayStrategy_s00cd_d500* pStrategy, cTribeDisplayStrategy_s00cd_d500* pArg); // 0x00b6f0c0
void FUN_00c0d950(cPoly* pObject, bool bFlag);                    // 0x00c0d950
void FUN_00829110(void*** ppRemovedEnd, void** pFirst, void** pLast, void* pScratch, void* pTribe); // 0x00829110
struct cTribeTuningData {
    void Init();                                                 // 0x00ce6af0
};
extern cTribeTuningData gTribeTuningData;                        // 0x01581208
void LoadTribeToolData();                                        // 0x00c9de50
void LoadTribeArchetypeData();                                   // 0x00c97220
struct String16 {
    u16* mpBegin;
    u16* mpEnd;
    u16* mpCap;

    void SetEmpty()
    {
        extern u16 gEmptyString16[];
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCap = gEmptyString16 + 1;
    }

    ~String16()
    {
        if (mpCap - mpBegin > 1 && mpBegin != 0)
            operator_delete_array(mpBegin);
    }
};
struct cSpeciesProfile {
    void GetUiName(String16* pName);                             // 0x004da330
};
struct cNounScratch {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    void Build(s32 nCount, const void* pExtra);                  // 0x00b93c60
};
struct cTribeModeStrategy_s00cd_d500 {
    void** mpVtbl_00;
    u8 mPad_004[0x22c];
    cEditorHost* mpEditorHost_230;
    cTribeDisplayStrategy_s00cd_d500* mpDisplayStrategy_234;
    cTribeDisplayStrategy_s00cd_d500* mpLoadingStrategy_240;
    u8 mPad_238[0x144];
    u32 mSavedEditorValue_380;
    u32 mPad_384;
    cPoly* mpSaveObject_388;

    u32 GetMode()
    {
        return VSLOT_s00cd_d500(u32 (__thiscall*)(cTribeModeStrategy_s00cd_d500*), this, 0x1c)(this);
    }
    void SetMode(u32 nMode)
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cTribeModeStrategy_s00cd_d500*, u32), this, 0x40)(this, nMode);
    }
    void Refresh()
    {
        VSLOT_s00cd_d500(void (__thiscall*)(cTribeModeStrategy_s00cd_d500*), this, 0x48)(this);
    }

    void PreGameModeTransition(u32 previousMode, u32 newMode);     // 0x00cdd500
    void ContinueLoading();                                        // 0x00cddda0
};
struct cIOReader {
    void** mpVtbl_00;
    u32 GetHandle()
    {
        return VSLOT_s00cd_d500(u32 (__thiscall*)(cIOReader*), this, 0x18)(this);
    }
};
struct cIOStream {
    void** mpVtbl_00;
    cIOReader* GetReader()
    {
        return VSLOT_s00cd_d500(cIOReader* (__thiscall*)(cIOStream*), this, 0x20)(this);
    }
};
inline u32 StreamHandle(cIOStream* pStream)
{
    return pStream->GetReader()->GetHandle();
}
struct cPlayerRow {
    Vec3* mpBegin;
    Vec3* mpEnd;
    Vec3* mpCap;
    u32 mField_0c;
    u32 mField_10;

    void Resize(s32 nCount);                                     // 0x00473810
};
struct cVarListOwner {
    u32 mPad_00;
    u32 mPad_04;
    u32 mPad_08;
};
struct cVarListSerializer_s00cd_d500 {
    u32 mState_0000[0xa01 / 4];                                  // 0xa04-byte serializer state
    cVarListSerializer_s00cd_d500(const cVarListOwner* pOwner, u32 nId, u32 nKey); // 0x00692f90
    bool Serialize(cIOStream* pStream);                          // 0x00693e10
};
struct cSpaceInventory {
    void Configure(u32 nId, u32 nKey, u32 nFlags);               // 0x00599440
};
void ResizePlayerRows(cPlayerRow** ppRows, u32 nCount);          // 0x00cde0e0
struct cPlayer {
    u8 mPad_000[0x20];
    cPlayerRow* mpRows_020;
    u8 mPad_024[0x16c];
    cSpaceInventory* mpInventory_190;

    bool Read(cIOStream* pStream);                               // 0x00cde160
};
extern u32 gSpaceInventoryFlags;                                 // 0x0157f18c
// ---- items of slice s00cdd500 end

// ---- items of slice s00cde2f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  DAT_015fd928;                                 // 0x015fd928
extern float  DAT_014771f8;                                 // 0x014771f8
extern float  DAT_014763b8;                                 // 0x014763b8
extern const char DAT_013ebc58[];                           // 0x013ebc58
void* operator new[](unsigned int n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void* FUN_00b969a0(void* first, void* last, void* dest);   // 0x00b969a0  _Uninitialized_copy
void* FUN_00b3d230();                                       // 0x00b3d230
void* FUN_00b3d320();                                       // 0x00b3d320
void* FUN_00b3d340();                                       // 0x00b3d340
void* FUN_00b3d350();                                       // 0x00b3d350
void* FUN_00b3d380();                                       // 0x00b3d380
void* FUN_00b3d410();                                       // 0x00b3d410
void* FUN_00b3d440();                                       // 0x00b3d440
void* FUN_00b3d480();                                       // 0x00b3d480
void* FUN_00b3d4f0(int);                                    // 0x00b3d4f0
void* FUN_00b3d520();                                       // 0x00b3d520  GetGonzagoModelWorld
void* FUN_0067dcc0();                                       // 0x0067dcc0  MessageServer
void* FUN_0067ddd0();                                       // 0x0067ddd0  EffectsManager
void* FUN_0067dd00();                                       // 0x0067dd00  AppSystem
void* FUN_0067dd50();                                       // 0x0067dd50
void* FUN_00401010();                                       // 0x00401010
void* FUN_00401090();                                       // 0x00401090
void* FUN_00cc8b10_s00cd_e2f0();                                       // 0x00cc8b10
void  FUN_00cd3fb0(int);                                    // 0x00cd3fb0
void  FUN_00cd5f70();                                       // 0x00cd5f70  cTribeModeStrategy::ContinueLoading
void  FUN_00cd4280();                                       // 0x00cd4280
void  FUN_00c9a080();                                       // 0x00c9a080  cTribe::HotSpotsShutdown
void  FUN_00cd6040();                                       // 0x00cd6040
void  FUN_00cd7770();                                       // 0x00cd7770  cTribeDisplayStrategy::ShowTribeUI
void  FUN_00cdc8b0();                                       // 0x00cdc8b0
void  FUN_00cddcf0();                                       // 0x00cddcf0
void  FUN_00b976f0();                                       // 0x00b976f0
struct B00 { virtual void a00() {} };
struct B01 : B00 { virtual void a01() {} };
struct B02 : B01 { virtual void a02() {} };
struct B03 : B02 { virtual void a03() {} };
struct B04 : B03 { virtual void a04() {} };
struct B05 : B04 { virtual void a05() {} };
struct B06 : B05 { virtual void a06() {} };
struct B07 : B06 { virtual void a07() {} };
struct B08 : B07 { virtual void a08() {} };
struct B09 : B08 { virtual void a09() {} };
struct B10 : B09 { virtual void a10() {} };
struct B11 : B10 { virtual void a11() {} };
struct B12 : B11 { virtual void a12() {} };
struct B13 : B12 { virtual void a13() {} };
struct B14 : B13 { virtual void a14() {} };
struct B15 : B14 { virtual void a15() {} };
struct B16 : B15 { virtual void a16() {} };
struct B17 : B16 { virtual void a17() {} };
struct B18 : B17 { virtual void a18() {} };
struct B19 : B18 { virtual void a19() {} };
struct B20 : B19 { virtual void a20() {} };
struct B21 : B20 { virtual void a21() {} };
struct B22 : B21 { virtual void a22() {} };
struct B23 : B22 { virtual void a23() {} };
struct B24 : B23 { virtual void a24() {} };
struct B25 : B24 { virtual void a25() {} };
struct B26 : B25 { virtual void a26() {} };
struct B27 : B26 { virtual void a27() {} };
struct B28 : B27 { virtual void a28() {} };
struct B29 : B28 { virtual void a29() {} };
struct B30 : B29 { virtual void a30() {} };
struct B31 : B30 { virtual void a31() {} };
struct B32 : B31 { virtual void a32() {} };
struct B33 : B32 { virtual void a33() {} };
struct B34 : B33 { virtual void a34() {} };
struct B35 : B34 { virtual void a35() {} };
struct B36 : B35 { virtual void a36() {} };
struct B37 : B36 { virtual void a37() {} };
struct cRowSet2;    // returned by cSelf::FUN_00b21340 (vector with begin/end at +0x04/+0x08)
struct cSelf
{
    void  FUN_00cd56e0();                                    // 0x00cd56e0
    uint8_t FUN_00c744e0(void*);                             // 0x00c744e0
    void* FUN_00ce6950();                                    // 0x00ce6950
    void* FUN_00ba4e60(void*);                               // 0x00ba4e60
    void* FUN_00c735e0(void*);                               // 0x00c735e0
    void* FUN_00c8e820(void*, void*, void*, void*, void*, void*);  // 0x00c8e820
    void  FUN_00bc2f70(int, void*);                          // 0x00bc2f70
    cRowSet2* FUN_00b21340(void*, void*, void*, void*, void*); // 0x00b21340 GetGameDataVector
    void* FUN_00bfc5f0();                                    // 0x00bfc5f0 GetPlayerTribe
    void* FUN_00f67d90();                                    // 0x00f67d90 GetCurrentTerrainSphere
    void* FUN_00c90460();                                    // 0x00c90460
    void  FUN_00cd7c70(int);                                 // 0x00cd7c70
    void  FUN_00cd4e10();                                    // 0x00cd4e10
    void* FUN_00597e00();                                    // 0x00597e00
    void  FUN_00599440(int, int, int);                        // 0x00599440
    void  FUN_01023030(void*, void*);                        // 0x01023030 (destroy range)
    void  FUN_00cd9440(void*, void*);                        // 0x00cd9440
    void  FUN_00530c80(void*, void*);                        // 0x00530c80
    void  FUN_00e25bd0(void*, void*);                        // 0x00e25bd0
    void  FUN_00b9c250();                                    // 0x00b9c250
    void  FUN_00cd6610();                                    // 0x00cd6610
    void  FUN_00cd54c0();                                    // 0x00cd54c0
    void  FUN_00ccec20(int);                                 // 0x00ccec20
    void  FUN_00cdcf70();                                    // 0x00cdcf70
    void  FUN_00cd9da0();                                    // 0x00cd9da0
    void  FUN_00cddda0();                                    // 0x00cddda0
    void  FUN_00cdcb10();                                    // 0x00cdcb10 TransitionToSpaceMode
    void  FUN_00cd53e0();                                    // 0x00cd53e0 SetRolloverHandle
    void  FUN_00cc4fa0();                                    // 0x00cc4fa0
    void  FUN_00b1dfc0();                                    // 0x00b1dfc0
    void  FUN_00b1e410(int);                                 // 0x00b1e410
    void  FUN_00b2a100();                                    // 0x00b2a100
    void  FUN_00b32250(int);                                 // 0x00b32250
    void  FUN_00b32220(int);                                 // 0x00b32220 IncPauseGate
    void  FUN_00c77380(int, void*);                          // 0x00c77380
    void  FUN_00b8c330(int, int, int);                       // 0x00b8c330
    uint8_t FUN_00e36e00();                                  // 0x00e36e00
    uint8_t FUN_00e36dd0();                                  // 0x00e36dd0
    uint8_t FUN_00e36de0();                                  // 0x00e36de0
    uint8_t FUN_00e36e10();                                  // 0x00e36e10
    uint8_t FUN_00e36fa0();                                  // 0x00e36fa0
    void  FUN_00e2f270();                                    // 0x00e2f270
    void  FUN_00e3b1f0();                                    // 0x00e3b1f0
    void  FUN_00e3e350(int, int, int);                       // 0x00e3e350
    void  FUN_00c93a40();                                    // 0x00c93a40
    void  FUN_00acc700(void*);                               // 0x00acc700
    void  FUN_00b5e9a0(int);                                 // 0x00b5e9a0 Shutdown
    uint8_t FUN_007b19c0();                                  // 0x007b19c0
    void* FUN_004df420();                                    // 0x004df420
    void  FUN_00572660(void*);                               // 0x00572660
    void* FUN_00a16f40();                                    // 0x00a16f40 AsPPTypeParam
    void  FUN_00421c80(int);                                 // 0x00421c80 MessageBasicRC<5> ctor
    void  FUN_0061df40(void*);                               // 0x0061df40
};
struct cVtV4   : public B00 { virtual void         v4() {}; };                       // +0x04
struct cVtV10  : public B03 { virtual int          v10() { return 0; }; };            // +0x10
struct cVtV14  : public B04 { virtual void         v14(int, void*) {}; };             // +0x14
struct cVtV18  : public B05 { virtual void         v18(int, int) {}; };               // +0x18
struct cVtV28  : public B09 { virtual int          v28() { return 0; }; };            // +0x28
struct cVtV2c0 : public B10 { virtual void*        v2c() { return 0; }; };            // +0x2c, 0 args
struct cVtV2c1 : public B10 { virtual void         v2c(int) {}; };                    // +0x2c, 1 arg
struct cVtV2c2 : public B10 { virtual void*        v2c(float, float) { return 0; }; };// +0x2c, 2 floats
struct cVtV30  : public B11 { virtual void         v30(int) {}; };                    // +0x30
struct cVtV3c  : public B14 { virtual uint8_t      v3c(void*) { return 0; }; };       // +0x3c
struct cVtV40  : public B15 { virtual void         v40(int) {}; };                    // +0x40
struct cVtV44  : public B16 { virtual uint8_t      v44() { return 0; }; };            // +0x44
struct cVtV50  : public B19 { virtual uint8_t      v50() { return 0; }; };            // +0x50
struct cVtV54  : public B20 { virtual void*        v54(int) { return 0; }; };         // +0x54
struct cVtV5c  : public B22 { virtual void         v5c(int, int) {}; };               // +0x5c
struct cVtV60  : public B23 { virtual void         v60(int, int) {}; };               // +0x60
struct cVtV98  : public B37 { virtual void         v98(int, int) {}; };               // +0x98
struct cObj390 : public B00
{
    virtual void    v4() {};
    virtual uint8_t v8(int) { return 0; };
    virtual void    vc(int) {};
};
struct cObjEp : public B00
{
    virtual uint8_t v4() { return 0; };
    virtual uint8_t v8(void*, int, int) { return 0; };
};
struct cMsgObj : public B01
{
    virtual void v8() {};
    uint8_t  pad04[0x08 - 0x04];
    uint32_t m08;                       // +0x08
    uint32_t m0c;                       // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint8_t  pad1c[0x30 - 0x1c];
    uint32_t m30;                       // +0x30
};
struct cTribeAux { uint8_t pad0[0x24]; void* mp24; };                    // noun-manager +0x24
struct cSphereView                                                   // terrain sphere
{
    uint8_t pad0[0x10f0];
    float   m10f0;      // +0x10f0
    float   m10f4;      // +0x10f4
    uint8_t pad2[0x11c0 - 0x10f8];
    uint8_t m11c0;      // +0x11c0
};
struct cTribeView : public B18                                           // player tribe
{
    virtual void* v4c() { return 0; };  // +0x4c (0 args)
    uint8_t  pad04[0x120 - 0x04];
    cVtV2c0  m120;      // +0x120
    uint8_t  pad2[0x234 - 0x124];
    uint32_t m234;      // +0x234
};
struct cRowSet { uint8_t pad0[0x1e5f0]; uint32_t m1e5f0; uint32_t m1e5f4; };  // 0xb3d440()
struct cRowSet2 { uint32_t m00; uint32_t* pBegin; uint32_t* pEnd; };           // 0xb21340()
struct cStateList { uint8_t pad0[0x70]; void* mp70; };                        // DAT_015fd928
struct cBaby
{
    void*    mp00;                      // +0x00
    uint32_t m04;                       // +0x04
    uint32_t m08;                       // +0x08
    uint32_t m0c;                       // +0x0c
    uint32_t m10;                       // +0x10
};
struct cMode;
struct cModeSub;
struct cModeSub : public B07
{
    virtual uint32_t vOn20() { return 0; };    // +0x20
    virtual void     v24() {};                 // +0x24
    virtual void     v28() {};                 // +0x28
    virtual void     v2c() {};                 // +0x2c
    virtual void     v30() {};                 // +0x30
    virtual void     v34() {};                 // +0x34
    virtual void     v38() {};                 // +0x38
    virtual void     v3c() {};                 // +0x3c
    virtual void     v40() {};                 // +0x40
    virtual void     vOn44(int) {};            // +0x44
    virtual void     v48() {};                 // +0x48
    virtual void     vOn4c() {};               // +0x4c

    uint8_t  pad04[0x1c - 0x04];               // +0x04
    uint8_t  m1c;                              // +0x1c  (cMode+0x28)
    uint8_t  m1d;                              // +0x1d  (cMode+0x29)
    uint8_t  pad1e[0x20 - 0x1e];               // +0x1e
    cBaby*   mpVec1Begin;                      // +0x20  (cMode+0x2c)
    cBaby*   mpVec1End;                        // +0x24  (cMode+0x30)
    cBaby*   mpVec1Cap;                        // +0x28  (cMode+0x34)
    uint8_t  pad2c[0x34 - 0x2c];               // +0x2c
    cBaby*   mpVec2Begin;                      // +0x34  (cMode+0x40)
    cBaby*   mpVec2End;                        // +0x38  (cMode+0x44)
    uint8_t  pad3c[0x6c - 0x3c];               // +0x3c
    uint32_t m6c;                              // +0x6c  (cMode+0x78)
    cBaby*   mpVec3Begin;                      // +0x70  (cMode+0x7c)
    cBaby*   mpVec3End;                        // +0x74  (cMode+0x80)
    uint8_t  pad78[0x88 - 0x78];               // +0x78
    cBaby*   mpVec4Begin;                      // +0x88  (cMode+0x94)
    cBaby*   mpVec4End;                        // +0x8c  (cMode+0x98)
    uint8_t  pad90[0x9c - 0x90];               // +0x90
    uint8_t  m9c;                              // +0x9c  (cMode+0xa8)
    uint8_t  pad9d[0x190 - 0x9d];              // +0x9d
    void*    mp190;                            // +0x190 (cMode+0x19c)
    float    m194;                             // +0x194 (cMode+0x1a0)
    uint8_t  m198;                             // +0x198 (cMode+0x1a4)
    uint8_t  pad199[0x21c - 0x199];            // +0x199
    uint8_t  m21c;                             // +0x21c (cMode+0x228)
    uint32_t m220;                             // +0x220 (cMode+0x22c) state
    uint32_t m224;                             // +0x224 (cMode+0x230) message
    uint32_t m228;                             // +0x228 (cMode+0x234)
    uint32_t m22c;                             // +0x22c (cMode+0x238) counter
    uint32_t m230;                             // +0x230 (cMode+0x23c)
    uint8_t  pad234[0x248 - 0x234];            // +0x234
    void*    mp248;                            // +0x248 (cMode+0x254)
    uint8_t  pad24c[0x390 - 0x24c];            // +0x24c
    void*    mp390;                            // +0x390 (cMode+0x39c)
    uint8_t  m394;                             // +0x394 (cMode+0x3a0)
    uint8_t  m395;                             // +0x395 (cMode+0x3a1)
    uint8_t  m396;                             // +0x396 (cMode+0x3a2)
    uint8_t  m397;                             // +0x397 (cMode+0x3a3)

    void FUN_00cdec80(int msg, int kind);      // 0x00cdec80
};
struct cModeHdr { uint32_t m00, m04, m08; };
struct cMode : public B16
{
    virtual void vOn44() {};                   // +0x44
    virtual void v48() {};                     // +0x48
    virtual void vOn4c() {};                   // +0x4c

    uint32_t pad04;                            // +0x04
    uint32_t pad08;                            // +0x08
    cModeSub mSub;                             // +0x0c

    void FUN_00cde5b0();                       // 0x00cde5b0
    void FUN_00cde600();                       // 0x00cde600
    void FUN_00cde660(int arg1);               // 0x00cde660

    cMode* OwnerOf(cModeSub* sub) { return (cMode*)((cModeHdr*)sub - 1); }
};
void FUN_00cde2f0();
// ---- items of slice s00cde2f0 end

// ---- items of slice s00cdef00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00cd7d10(); extern "C" void FUN_00d3d420(); extern "C" void FUN_00accbb0();
extern "C" void FUN_00b1e500(); extern "C" void FUN_00b1e520(); extern "C" void FUN_00cdb110();
extern "C" void FUN_00accc30(); extern "C" void FUN_00cdb620();
extern char DAT_01654c02;
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
inline float MinF(float a, float b)
{
    __asm {
        movss xmm0, a
        minss xmm0, b
        movss a, xmm0
    }
    return a;
}
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    void Normalize_00fb8db0();
};
struct Vector4 { float x, y, z, w; };
struct Matrix3 { Vector3 r[3]; };
struct BoundingBox { Vector3 lower, upper; };
struct Property {
    uint32_t mData[4];
    uint8_t  mFlags;      // +0x10
    uint8_t  pad11;
    uint16_t mType;       // +0x12
    const char* GetValueBool() const { return (mFlags & 0x30) ? *(const char* const*)mData : (const char*)mData; }
};
struct PropertyList {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
extern PropertyList* gDebugProps_01581288;
extern PropertyList* gTribeTuning_0158128c;
float GetPropertyFloat_004e1c70(PropertyList* list, uint32_t id, float def);   // SP::GetPropertyT<float>
inline bool GetDebugBool(uint32_t id, Property*& prop)
{
    return gDebugProps_01581288 && gDebugProps_01581288->GetProperty(id, prop) &&
           prop->mType == 1 && *prop->GetValueBool();
}
struct cSPTimer {
    uint32_t data[8];
    bool IsRunning_00feba90();
    uint64_t GetElapsedTime_00bc3190();
    void Stop_00bc3170();
};
struct cCitizen {
virtual int AddRef();
virtual int Release();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool IsDead();                    // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
    virtual void v44();
    virtual void SetTarget(int);              // +0x48
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void Update(int ms);              // +0x60

    char pad[0x135 - 4];
    bool mbActive;                            // +0x135
    char pad136[0xb58 - 0x136];
    uint32_t mFlags;                          // +0xb58
    char padb5c[2];
    bool mbBusy;                              // +0xb5e

    void f_00c1d5e0(int, uint32_t, uint32_t);     // 0x00c1d5e0
    void f_00c0b370(int);                         // 0x00c0b370
    void f_00c17350(uint32_t, int);               // 0x00c17350
    void* f_00c04590();                           // 0x00c04590
    void f_00c042e0();                            // 0x00c042e0
    void f_00c14750(int);                         // 0x00c14750
};
void FUN_00c0d3a0(cCitizen* c);
template <class T> struct AutoRefCount {
    T* p;
    void Swap_00ac9480(AutoRefCount& other);
    ~AutoRefCount() { if (p) p->Release(); }
};
struct CitizenVector {   // eastl::vector<AutoRefCount<cCitizen>>
    AutoRefCount<cCitizen>* mpBegin;
    AutoRefCount<cCitizen>* mpEnd;
    AutoRefCount<cCitizen>* mpCapacity;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    void pop_back() { --mpEnd; mpEnd->~AutoRefCount<cCitizen>(); }
    AutoRefCount<cCitizen>* erase_00e25bd0(AutoRefCount<cCitizen>* first, AutoRefCount<cCitizen>* last);
};
template <class T> struct PtrVector {
    T** mpBegin; T** mpEnd; T** mpCapacity;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct cTribeTools { char pad[0x40]; PtrVector<void> mTools; };   // +0x40
struct cTribeSub120 {
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
    virtual void* v2c(float a, float b);      // +0x2c
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
    virtual bool IsDestroyed();               // +0x58
};
struct cSpatialSub {   // object at +0xc0 of a tribe member
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
    virtual Vector3* GetDirection();          // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual bool IsVisible();                 // +0x48
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
    virtual BoundingBox GetBoundingBox();     // +0x6c
    virtual float GetBoundingRadius();        // +0x70
    Vector3* GetVelocity_00d20610();
};
struct cMember { char pad[0xc0]; cSpatialSub mSpatial; };
struct cTribe_s00cd_ef00 {
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
    virtual int GetPoliticalID();             // +0x4c
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
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual PtrVector<cMember>* GetMembers(); // +0x90 0x00c8e810

    char pad04[0x120 - 4];
    cTribeSub120 mSub;                        // +0x120
    char pad124[0x2bc - 0x124];
    int   mRelationship;                      // +0x2bc
    float mFoodAccum;                         // +0x2c0
    char pad2c4[0x556 - 0x2c4];
    bool  mbSkipUpdate;                       // +0x556

    cTribeTools* f_00c8fee0();                    // 0x00c8fee0
    cCitizen* GetLeader_00c00650();
    static void HotSpotsUpdate_00c9b740(float dt);
};
void FUN_00ba58e0(cTribe_s00cd_ef00* tribe, int v);
struct cGameDataVector { void* vt; PtrVector<void> mData; };
struct cGameNounManager_s00cd_ef00 {
    cTribe_s00cd_ef00* GetPlayerTribe_00bfc5f0();
    cGameDataVector* GetGameDataVector_00b21340(void* f0, void* f1, void* f2, void* f3, uint32_t type);
};
cGameNounManager_s00cd_ef00* NounManager_00b3d300();
struct cHerd { bool f_00c6a020(); void Update_00c6d7c0(int ms); };
struct cAnimalTrap { void f_00bcc230(int ms); };
struct cRefObj {
virtual int AddRef();
virtual int Release();
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
    virtual void Update(int ms);              // +0x60
    char pad[0x135 - 4];
    bool mbActive;                            // +0x135
};
struct cMessageServer { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
                        virtual void PostMessage(uint32_t id, void* a, void* b); };   // +0x14
cMessageServer* MessageServer_0067dcc0();
struct cConfigManager {
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
    virtual void* GetSetting(uint32_t id);     // +0x30
};
cConfigManager* ConfigManager_0067dd30();
struct cGameTimeManager {
    char pad[0x48]; uint8_t mFlags;            // +0x48
    void IncPauseGate_00b32220(uint32_t id);
    int  GetPauseGateCount_00b320d0(uint32_t id);
    void DecPauseGate_00b32250(uint32_t id);
    int  f_00b31c60(int ms);                       // 0x00b31c60: scaled game time
};
cGameTimeManager* GameTimeManager_00b3d380();
struct cGameInputManager {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual bool IsMouseButtonDown(int b);     // +0x18
    char pad[0x110 - 4];
    int mPauseCount;                           // +0x110
};
cGameInputManager* GameInputManager_00b3d250();
struct cCameraController {
    char pad[0x390]; bool field_390;
    Vector3* GetAnchorDirection0_00b10200();
    void f_00b14520(Vector3* dir, Vector3* vel);
};
cCameraController* FUN_00b3d280();
float Dot3_004885d0(const Vector3* v);
struct cSimState { char pad[0x28]; bool mbSkip; };
cSimState* FUN_00b3d320_s00cd_ef00();
struct cGameModeState { char pad[0x2c]; int mState; };
cGameModeState* FUN_00b3d4d0();
struct cSubsysB5e { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void Update2c(int ms);
virtual void Update30(int ms);
                    void f_00b5e9a0(int ms); };
cSubsysB5e* FUN_00b3d230_s00cd_ef00();
void* GetCurrentGameMode_00b5b800();
class cUIHints { public: void UpdateHints_0067c350(int a, int b); };
cUIHints* FUN_0067cac0_s00cd_ef00();
struct cMissionLog { void f_00e2f270(int); };
cMissionLog* FUN_00b3d4f0();
struct cMusic { void f_00b700f0(uint32_t id); };
struct cTimeline { void f_00acc700(void* v); };
cTimeline* FUN_00b3d480_s00cd_ef00();
struct cRelationshipManager { int f_00d00a70(int a, int b, int c); };
cRelationshipManager* RelationshipManager_00b3d2c0();
struct cEventLog { void PostFeedbackEvent_00dd8640(uint32_t a, uint32_t b, int c, int d, int e, int f); };
cEventLog* EventLog_00b3d3e0();
struct cTribeHud { char pad[0x1c]; void* mpLastTribe; };
extern cTribeHud* gTribeHud_0169b41c;
void FUN_01022920(int ms);
struct cCastable {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void* Cast(uint32_t id);           // +0x14
};
struct cCastTarget { void f_00c36ae0(float dt); };
struct cB3d2b0 { cCastable* f_00ac79d0(); };
cB3d2b0* FUN_00b3d2b0();
struct cCommunityEditor_s00cd_ef00 {
    void HandleSimulationUpdate_00d124e0(int ms);
    bool f_00d09660();
};
struct cInputStrategy { char pad[0x5c]; cCommunityEditor_s00cd_ef00* mpEditor; void f_00cceca0(int, int); void f_00ccff40(); };
struct cDisplayStrategy { void UpdateUI_00cc99b0(int ms); void f_00ccdc30(int, int, int); void f_00cc9620(); void f_00cc9cd0(int); };
struct cAudioListener {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void Commit();                     // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void SetUp(const Vector3* v);      // +0x30
    virtual void v34();
    virtual void SetOrientation(const Vector3* dir, const Vector3* n);  // +0x38
    virtual void SetTransform(const Vector4* v);   // +0x3c
};
cAudioListener* FUN_0067ddc0_s00cd_ef00();
struct cCameraTransform { uint16_t a, b; Vector4 pos; Matrix3 rot; };
struct cCamera { void f_007c40f0(cCameraTransform* t); };   // 0x007c40f0
struct cCameraObj { char pad[0x54]; Vector3 mDirection; };
struct cCameraLookup { virtual void v00(); virtual void v04(); virtual void v08();
                       virtual cCameraObj* Find(uint32_t id); };           // +0x0c
struct cCameraMgr {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual cCamera* GetActiveCamera();        // +0x1c
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual void v34();
    virtual cCameraLookup* GetActiveController();  // +0x38
    virtual uint32_t GetActiveControllerID();  // +0x3c
};
struct cApp {
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
    virtual cCameraMgr* GetCameraManager();    // +0x50
};
cApp* App_0067dd10();
extern Vector3 gCameraPos_0169b2cc;
extern Matrix3 gCameraRot_0169b378;
struct cPlanetSub { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                    virtual Vector3 GetUp(); };   // +0x10 (sret)
struct cPlanetModel_s00cd_ef00 { char pad[0x24]; cPlanetSub* mpSub; };
cPlanetModel_s00cd_ef00* PlanetModel_00b3d350();
struct cHotSpots { void f_00b76d20(const Vector3* pos, float radius, int a, int b, int c); };
cHotSpots* FUN_00b3d3c0_s00cd_ef00();
struct cTerrainSphere { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
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
                        virtual Vector3 GetCenter(int);   // +0x44 (sret)
};
cTerrainSphere* FUN_00b3d240();
void FUN_00b6dbd0(float dt);
struct cTribeModeStrategy_s00cd_ef00 {
    char pad0[0x58];
    cSPTimer mTimerA;                          // +0x58
    int  mGameTimeMs;                          // +0x78
    char pad7c[0x94 - 0x7c];
    CitizenVector mSelected;                   // +0x94
    char pada0[0x1a0 - 0xa0];
    float mSelectTimer;                        // +0x1a0
    bool  mbTutorialHint;                      // +0x1a4
    char  pad1a5[3];
    cSPTimer mTimerB;                          // +0x1a8
    char pad1c8[0x22c - 0x1c8];
    int   mState;                              // +0x22c
    char pad230[0x238 - 0x230];
    int   mWaitFrames;                         // +0x238
    cInputStrategy*   mpInputStrategy;         // +0x23c
    cDisplayStrategy* mpDisplayStrategy;       // +0x240
    char pad244[0x250 - 0x244];
    cCitizen* mpTracked;                       // +0x250 (vtable +0x2c, spatial at +0xc0)
    char pad254[0x394 - 0x254];
    cMusic* mpMusic;                           // +0x394

    void IncrementGoalProgress_00cdab10();
    bool f_00cd4460(uint32_t id);
    static void f_00cd3fb0(uint32_t id);
    void f_00cd6390(int);
    void f_00cd4b70(int);
    void f_00cde660(int ms);
    void HandleSimulationUpdate(float dtReal, float dtGame);  // 0x00cdef00 (cTribeModeStrategy::HandleSimulationUpdate)
};
// ---- items of slice s00cdef00 end

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00572810();
extern "C" void fn_00572840();
extern "C" void fn_00693090();
extern "C" void fn_00694f00();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00675ca0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00bca960();
extern "C" void fn_00b6f550();
extern "C" void fn_00cdb000();
extern "C" void fn_00cd58d0();
extern "C" void fn_00cd5940();
extern "C" void fn_00ca8710();
extern "C" void fn_00cdb4c0();
extern "C" void fn_00cd5980();
extern "C" void fn_00cd92f0();
extern "C" void fn_00acdf10();
extern "C" void fn_00aca730();
extern "C" void fn_00b6f860();
extern "C" void fn_00c6c390();
extern "C" void fn_00ac88f0();
extern "C" void fn_006930b0();
extern "C" void fn_00694fc0();
extern "C" void fn_00acbb80();
extern "C" void fn_00c78020();
extern "C" void fn_00ac9f70();
extern "C" void fn_00cd6630();
extern "C" void fn_00c78a50();
extern "C" void fn_00ba8250();
extern "C" void fn_00cd6680();
extern "C" void fn_00cd6f60();
extern "C" void fn_00ac8750();
extern "C" void fn_00ac8780();
extern "C" void fn_00694fa0();
extern "C" void fn_0057ce00();
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_0157f290, g_0157f2cc, g_0157f308, g_0157f344, g_0157f380,
         g_0157f3bc, g_0157f3f8, g_0157f434, g_0157f470, g_0157f4ac;
// ---- items of slice s0135d100 end

// @ 0x00cd0260
unsigned char __stdcall FUN_00cd0260(void* arg)
{
    switch (FUN_00ccefb0(arg, 0)) {
    case 4:
    case 6:
    case 9:  case 10: case 11: case 12: case 13: case 14: case 15: case 16:
    case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24:
    case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
    case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40:
    case 41: case 42: case 43: case 45: case 46: case 47: case 48:
        return 1;
    default:
        return 0;
    }
}

// @ 0x00cd0660
int CInput::F_cd0660(void* flags, void* pos, void* c)
{
    void* tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, int)) (*(void***)tc)[0xb8 / 4])(tc, 0);
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*)) (*(void***)tc)[0xa4 / 4])(tc);
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, float)) (*(void***)tc)[0xac / 4])(tc, 1.0f);
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, float)) (*(void***)tc)[0xb0 / 4])(tc, 1.0f);

    StackVec vec;
    vec.init();
    tc = GetGameTerrainCursor();
    ((void(__thiscall*)(void*, void*)) (*(void***)tc)[0x5c / 4])(tc, &vec);

    if (flags == 0 && vec.mpBegin != vec.mpEnd) {
        if (((unsigned char(__thiscall*)(void*, uint32_t)) FUN_00cd4460)(*(void**)((char*)this + 0x40), 0x56d1871))
            goto done0;
        if (!((unsigned char(__thiscall*)(void*, uint32_t)) FUN_00cd4460)(*(void**)((char*)this + 0x40), 0x64be5ff))
            goto done0;
        ((void(__thiscall*)(void*, uint32_t)) FUN_00cd6980)(*(void**)((char*)this + 0x40), 0x5ac72d7c);
        ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
        return 0;
    }

    if (((int)flags & 2) != 0) {
        if (vec.mpBegin == vec.mpEnd) {
            ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
            return 1;
        }
        float* p = (float*)pos;
        if (p[0]*p[0] + p[1]*p[1] + p[2]*p[2] > 0.0f)
            F_cd02d0(pos);
    }

done0:
    ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
    return 0;
}

// @ 0x00cd46d0
NOINLINE bool FUN_00cd46d0(void** self)
{
    int* dp = *(int**)((char*)self[0] + 0x64);
    if (dp) {
        int* child = (int*)((TC1)VSLOT(dp, 0x0c))(dp, 0x17f243b);
        if (child && (*(int(__fastcall**)(int*))(*(int*)child + 0x20))(child) == 0x2e72cae) {
            int* sub = *(int**)((char*)child + 0x24c);
            if (sub && (*(int(__fastcall**)(int*))(*(int*)sub + 0x20))(sub) == 0x18ebadc)
                return false;
        }
    }
    return true;
}

// @ 0x00cd4720
void* CRefHolder::FUN_00cd4720(void* a, cRefBase* p)
{
    mpVtbl = &g_vt14774c4;
    mp08 = 0;
    mp04 = a;
    cRefBase* old = *(cRefBase* volatile*)&mp08;
    if (p != old) {
        if (p)
            p->AddRef();
        mp08 = p;
        if (old)
            old->Release();
    }
    mb0c = 0;
    return this;
}

// @ 0x00cd4770
NOINLINE int FUN_00cd4770(char* self, void* other)
{
    if ((*(char(__fastcall**)(char*))(*(int*)self + 0x2c))(self))
        return 0;
    ((CActor_s00cd_45c0*)self)->FUN_00c6cbf0();
    {
        char* od = (char*)other;
        float f1 = (*(float(__fastcall**)(char*))(*(int*)od + 0x60))(od) * g_1485548;
        float* pf5 = (float*)(*(void*(__fastcall**)(char*))(*(int*)(od + 0x120) + 0x2c))(od + 0x120);
        float* pf6 = (float*)((CActor_s00cd_45c0*)self)->GetPosition();
        float* pf7 = (float*)((CActor_s00cd_45c0*)self)->FUN_00c6bdc0();
        if ((pf7[0] != g_169b2cc || pf7[1] != g_169b2d0 || pf7[2] != g_169b2d4) &&
            FUN_00700c80(pf6, pf7, pf5, f1, 0))
            ((CActor_s00cd_45c0*)self)->FUN_00c69ff0(&g_169b2cc);
        unsigned int kept = 0;
        if (((*(int*)(self + 0x6c) - *(int*)(self + 0x68)) / 0xc) != 0) {
            int off = 0;
            for (;;) {
                float* pp = (float*)(*(int*)(self + 0x68) + off);
                float d0 = pp[0] - pf6[0];
                float d1 = pp[1] - pf6[1];
                float d2 = pp[2] - pf6[2];
                float e0 = pf6[0] - pf5[0];
                float e1 = pf6[1] - pf5[1];
                float e2 = pf6[2] - pf5[2];
                float b = (d0 * e0 + d2 * e2) + d1 * e1;
                float aa = (d0 * d0 + d2 * d2) + d1 * d1;
                float cc = ((e0 * e0 + e2 * e2) + e1 * e1) - f1 * f1;
                float disc = b * b - cc * aa;
                float sq;
                if (disc < 0.0f || (sq = (float)sqrt((double)disc)) - b < 0.0f ||
                    aa < -b - sq) {
                    ++kept;
                    off += 0xc;
                } else {
                    int last = *(int*)(self + 0x6c);
                    pp[0] = *(float*)(last - 0xc);
                    pp[1] = *(float*)(last - 8);
                    pp[2] = *(float*)(last - 4);
                    *(int*)(self + 0x6c) = last - 0xc;
                    *(int*)(self + 0x80) = -1;
                }
                if (kept >= (unsigned int)((*(int*)(self + 0x6c) - *(int*)(self + 0x68)) / 0xc))
                    break;
            }
        }
    }
    return 0;
}

// @ 0x00cd49a0
NOINLINE void FUN_00cd49a0()
{
    FUN_00d48ae0();
    int* pi = *(int**)((char*)g_crew + 0x19c);
    if (pi) {
        *(void**)((char*)g_crew + 0x19c) = 0;
        (*(void(__fastcall**)(int*))(*(int*)pi + 4))(pi);
    }
}

// @ 0x00cd49d0
NOINLINE void FUN_00cd49d0(char* a, char* b, char* src)
{
    if (!src)
        return;
    if (!(*(int(__fastcall**)(char*))(*(int*)src + 8))(src))
        return;
    if (!a) {
        if (!b)
            return;
        int* v = (int*)(b + 0x40);
        int* it = (int*)v[0];
        if (it == (int*)v[1])
            return;
        int n = 0;
        do {
            int obj = *it;
            char* sp = (char*)(*(void*(__fastcall**)(char*))(*(int*)src + 8))(src);
            float* pf5 = (float*)(*(void*(__fastcall**)(char*))(*(int*)sp + 0x2c))(sp);
            float* pf6 = (float*)(*(void*(__fastcall**)(char*))(*(int*)(obj + 0xc0) + 0x2c))((char*)obj + 0xc0);
            float e0 = pf6[0] - pf5[0];
            float e1 = pf6[1] - pf5[1];
            float e2 = pf6[2] - pf5[2];
            float d = (e1 * e1 + e2 * e2) + e0 * e0;
            if (!(d > g_14774d0)) {
                FUN_00cd3ff0(n, (void*)(obj + 0xc0));
                ++n;
            }
            ++it;
        } while (it != (int*)v[1]);
        return;
    }
    {
        int* v = (int*)(*(void*(__fastcall**)(char*))(*(int*)a + 0x90))(a);
        int* it = (int*)v[0];
        if (it == (int*)v[1])
            return;
        int n = 0;
        do {
            int obj = *it;
            char* sp = (char*)(*(void*(__fastcall**)(char*))(*(int*)src + 8))(src);
            float* pf5 = (float*)(*(void*(__fastcall**)(char*))(*(int*)sp + 0x2c))(sp);
            float* pf6 = (float*)(*(void*(__fastcall**)(char*))(*(int*)(obj + 0xc0) + 0x2c))((char*)obj + 0xc0);
            float e0 = pf6[0] - pf5[0];
            float e1 = pf6[1] - pf5[1];
            float e2 = pf6[2] - pf5[2];
            float d = (e1 * e1 + e2 * e2) + e0 * e0;
            if (!(d > g_14774d0)) {
                FUN_00cd3ff0(n, (void*)(obj + 0xc0));
                ++n;
            }
            ++it;
        } while (it != (int*)v[1]);
    }
}

// @ 0x00cd4b70
NOINLINE void __fastcall FUN_00cd4b70(char* self, int, int v)
{
    void* cam = GetCameraCtl();
    char b;
    if (cam && *(char*)((char*)GetCameraCtl() + 0x390))
        b = 0;
    else
        b = (char)v;
    self[0x24a] = b;
    if (!b) {
        cRefBase* p = *(cRefBase**)(self + 0x250);
        if (p) {
            *(void**)(self + 0x250) = 0;
            p->Release();
        }
    }
}

// @ 0x00cd4bc0
NOINLINE void __fastcall FUN_00cd4bc0(char* self, int, char v)
{
    void* cam = GetCameraCtl();
    if (cam && *(char*)((char*)GetCameraCtl() + 0x390))
        v = 0;
    self[0x249] = v;
    if (!v)
        return;
    char* tribe = (char*)((CActor_s00cd_45c0*)NounManager())->FUN_00bfc5f0();
    void* ui = App();
    ui = (*(void*(__fastcall**)(void*))(*(int*)ui + 0x50))(ui);
    ui = ((TC1)VSLOT(ui, 0x40))(ui, 0xe3057616);
    if (!ui)
        return;
    char* icon = (char*)((TC1)VSLOT(ui, 0x0c))(ui, 0x11966ed);
    if (!icon || !tribe)
        return;
    void* sp = ((TC1)VSLOT(tribe + 0x120, 0x2c))(tribe + 0x120, 0);
    ((CIcon*)icon)->FUN_00b13bb0(sp);
    if (g_157f524 && !icon[0x168])
        ((CIcon*)icon)->FUN_00b16270();
}

// @ 0x00cd4c70
char CTribeMode::FUN_00cd4c70(int)
{
    char* self = (char*)this;
    void* app = App();
    app = (*(void*(__fastcall**)(void*))(*(int*)app + 0x50))(app);
    ((TC2v)VSLOT(app, 0x20))(app, 0x4c6a8d6, (void*)0xbc36d0);
    void* server = FUN_00883860();
    void* h = self ? (void*)(self + 8) : 0;
    *(void**)(self + 0x1cc) = server;
    *(void**)(self + 0x1d0) = h;
    *(void**)(self + 0x1d4) = &g_arr14774d8;
    *(uint32_t*)(self + 0x1d8) = 0x15;
    *(uint32_t*)(self + 0x1dc) = 0;
    if (server && h) {
        unsigned int i = 0;
        do {
            int v = *(uint32_t*)((char*)g_arr14774d8 + i);
            ((TCvi)VSLOT(server, 0x24))(server, h, v);
            i += 4;
        } while (i < 0x54);
    }
    if (g_appProps) {
        int st;
        if (((TC2b)VSLOT(g_appProps, 0x24))(g_appProps, 0x64a44a8, &st)) {
            if (*(short*)(st + 0x12) == 1)
                self[0x3a1] = *(char*)FUN_0041e920((void*)st);
        }
    }
    self[0x3a2] = 0;
    return 1;
}

// @ 0x00cd4d50
NOINLINE char __fastcall FUN_00cd4d50(char* self, int)
{
    void* a = FUN_00b3d3c0();
    ((CExt72880*)a)->call();
    void* c = FUN_00b3d240(0xcd45c0);
    ((CExt33ce0*)c)->call();
    void* d = FUN_00b3d240(0xcd46d0);
    ((CExt33cf0*)d)->call();
    ((CExtBC3170*)(self + 0x1a8))->call();
    return 1;
}

// @ 0x00cd4d90
void __stdcall FUN_00cd4d90(void* a)
{
    char* tribe = (char*)a;
    void* o = FUN_00920090();
    char* obj = (char*)((TC4)VSLOT(o, 0x20))(o, 0x3098af98, 0x9098aeb2, 0, 0);
    ((CActor_s00cd_45c0*)obj)->FUN_00ce6260(a, 0);
    char* old = *(char**)(tribe + 0x290);
    if (obj != old) {
        if (obj)
            (*(void(__fastcall**)(char*))(*(int*)obj + 4))(obj);
        *(char**)(tribe + 0x290) = obj;
        if (old)
            (*(void(__fastcall**)(char*))(*(int*)old + 8))(old);
    }
    void* ticker = SimTicker();
    ((TCCv)VSLOT(ticker, 0x50))(ticker, obj);
    cTribe_FishingRegister(tribe);
}

// @ 0x00cd4e10
NOINLINE void FUN_00cd4e10()
{
    char* tribe = (char*)((CActor_s00cd_45c0*)NounManager())->FUN_00bfc5f0();
    if (!tribe)
        return;
    float f1 = 0.0f, f2 = 0.0f;
    if (g_propList881288) {
        int st = 0;
        if ((*(char(__fastcall**)(void*, int, int*))(*(int*)g_propList881288 + 0x24))(g_propList881288, 0xc899522, &st)) {
            if (*(short*)(st + 0x12) == 0xd)
                f1 = *(float*)FUN_0041ea70((void*)st);
        }
    }
    if (g_propList881288) {
        int st = 0;
        if ((*(char(__fastcall**)(void*, int, int*))(*(int*)g_propList881288 + 0x24))(g_propList881288, 0x91d15b, &st)) {
            if (*(short*)(st + 0x12) == 0xd)
                f2 = *(float*)FUN_0041ea70((void*)st);
        }
    }
    char* slot = (char*)((CActor_s00cd_45c0*)tribe)->FUN_00c8e820(0);
    float x = *(float*)(slot + 0x4ec);
    float y = *(float*)(slot + 0x4f0);
    float z = *(float*)(slot + 0x4f4);
    float out[3];
    FUN_00b6e4b0(out, x, y, z, f1, f2);
    FUN_00b6f140(out[0], out[1], out[2]);
    FUN_00b6f180();
    *(uint32_t*)(tribe + 0x234) = 0x53dbcf1;
    ((CActor_s00cd_45c0*)tribe)->FUN_00c93a40();
    *(float*)(tribe + 0x254) = out[0];
    *(float*)(tribe + 0x258) = out[1];
    *(float*)(tribe + 0x25c) = out[2];
}

// @ 0x00cd4f90
NOINLINE void FUN_00cd4f90()
{
    if (!((CActor_s00cd_45c0*)NounManager())->FUN_00bfc5f0())
        return;
    char* tribe = (char*)((CActor_s00cd_45c0*)NounManager())->FUN_00bfc5f0();
    int* v = (int*)(*(void*(__fastcall**)(char*))(*(int*)tribe + 0x90))(tribe);
    int** it = (int**)v[0];
    if (it != (int**)v[1]) {
        do {
            CListNode* a = (CListNode*)*it;
            ((TC1v)VSLOT(&a->mSub, 0x54))(&a->mSub, 0);
            ++it;
        } while (it != (int**)v[1]);
    }
    void* c1 = GetGameTerrainCursor();
    (*(void(__fastcall**)(void*))(*(int*)c1 + 0x74))(c1);
    void* c2 = GetGameTerrainCursor();
    (*(void(__fastcall**)(void*))(*(int*)c2 + 0xc8))(c2);
}

// @ 0x00cd5010
NOINLINE void __fastcall FUN_00cd5010(char* self, int, char* obj)
{
    if (!*(void**)(self + 0x240))
        return;
    if (!obj)
        return;
    char* a = (char*)((CIdLookup*)obj)->get(0x4f176642);
    if (a) {
        ((CDisplayStrategy*)*(void**)(self + 0x240))->attach(a);
        return;
    }
    char* b = (char*)((CIdLookup*)obj)->get(0x1b92b27);
    if (b)
        ((CDisplayStrategy*)*(void**)(self + 0x240))->SetNestIcon(b, 1);
}

// @ 0x00cd5070
NOINLINE void __fastcall FUN_00cd5070(char* self, int, char* obj)
{
    if (!*(void**)(self + 0x240))
        return;
    if (!obj)
        return;
    char* a = (char*)((CIdLookup*)obj)->get(0x4f176642);
    if (a)
        ((CDisplayStrategy*)*(void**)(self + 0x240))->detach(a);
}

// @ 0x00cd50b0
NOINLINE void CTribeMode::FUN_00cd50b0(int, void* memberv)
{
    char* self = (char*)this;
    char* member = (char*)memberv;
    void* cam = GetCameraCtl();
    if (cam && *(char*)((char*)GetCameraCtl() + 0x390))
        return;
    if (!member)
        return;
    if (!((CActor_s00cd_45c0*)member)->FUN_00c22f50())
        return;
    char* tribe = (char*)((CActor_s00cd_45c0*)member)->FUN_00c22f50();
    int* v = (int*)(*(void*(__fastcall**)(char*))(*(int*)tribe + 0x90))(tribe);
    int n = (int)((v[1] - v[0]) >> 2);
    if (n <= 0)
        return;
    for (int i = 0; i < n; ++i) {
        if ((char*)((int*)v[0])[i] != member)
            continue;
        *(uint32_t*)((char*)g_crew + 0x2fc) = (uint32_t)i;
        void* ui = App();
        ui = (*(void*(__fastcall**)(void*))(*(int*)ui + 0x50))(ui);
        ui = ((TC1)VSLOT(ui, 0x40))(ui, 0xe3057616);
        if (ui) {
            char* icon = (char*)((TC1)VSLOT(ui, 0x0c))(ui, 0x11966ed);
            if (icon) {
                void* sp = ((TC1)VSLOT(member + 0xc0, 0x2c))(member + 0xc0, 0);
                ((CIcon*)icon)->FUN_00b13bb0(sp);
                if (g_157f525 && !icon[0x168])
                    ((CIcon*)icon)->FUN_00b16270();
            }
        }
        cRefBase* old = *(cRefBase**)(self + 0x250);
        if ((char*)old != member) {
            (*(void(__fastcall**)(char*))(*(int*)member))(member);
            *(char**)(self + 0x250) = member;
            if (old)
                old->Release();
        }
        FUN_00cd4b70((char*)g_crew, 0, 1);
    }
}

// @ 0x00cd5200
NOINLINE void FUN_00cd5200()
{
    char* ui = (char*)(*(void*(__fastcall**)(void*))(*(int*)g_crew + 0x6c))(g_crew);
    char* w1;
    {
        void* w = ((CWinMgr*)*(void**)(ui + 0x4c))->FindWindowByID(0x562a141);
        w1 = w ? (char*)(*(void*(__thiscall**)(void*, int))(*(int*)w + 0x0c))(w, 0x8ed27e7a) : 0;
    }
    char* w2;
    {
        void* w = ((CWinMgr*)*(void**)(ui + 0x4c))->FindWindowByID(0x562a0f7);
        w2 = w ? (char*)(*(void*(__thiscall**)(void*, int))(*(int*)w + 0x0c))(w, 0x8ed27e7a) : 0;
    }
    cString str;
    char al = (char)(*(int(__thiscall**)(char*))(*(int*)w1 + 0x20))(w1);
    int key;
    if ((al & 4) != 0) {
        (*(void(__thiscall**)(char*, int, int))(*(int*)w2 + 0x28))(w2, 4, 1);
        key = 0x615ffa8;
    } else {
        (*(void(__thiscall**)(char*, int, int))(*(int*)w2 + 0x28))(w2, 4, 0);
        key = 0x615ffa7;
    }
    str.Load(0xc0152a6d, key, 0);
    const void* txt = str.Get(-1, 1);
    char* w = (char*)(*(void*(__thiscall**)(char*, void*))(*(int*)w1 + 0x10))(w1, (void*)txt);
    FUN_00e806de0((void*)w);
}

// @ 0x00cd52e0
NOINLINE void* __stdcall FUN_00cd52e0(void* a, float b, float c, float d)
{
    void* result = 0;
    char* tr = (char*)((CActor_s00cd_45c0*)NounManager())->FUN_00bfc5f0();
    if (tr) {
        CRetObj* r = (CRetObj*)((CExt7ec160*)FUN_0067de90(2, a))->FUN_007ec160();
        result = r;
        if (r) {
            r->FUN_007eb820(7);
            uint64_t t = ((CTimeMgr*)GameTimeManager())->FUN_00b316c0();
            r->mpInfo->m00 = (int)__aulldiv(t, 1000);
            r->mpInfo->m04 = (*(int(__fastcall**)(char*))(*(int*)tr + 0x74))(tr);
            float sp = ((CActor_s00cd_45c0*)(tr + 0x20c))->FUN_00cee380();
            r->mpInfo->m08 = (uint32_t)sp;
            r->mpInfo->m0c = b;
            r->mpInfo->m10 = c;
            r->mpInfo->m14 = d;
            r->mpInfo->m18 = (int)FUN_00458a40(FUN_00b6f0c0(*(int*)(tr + 0x234)));
        }
    }
    return result;
}

// @ 0x00cd53e0
NOINLINE void CTribeMode::FUN_00cd53e0()
{
    char* self = (char*)this;
    if (((!g_testSystem || *(void**)((char*)g_testSystem + 0x70) == (char*)g_testSystem + 0x70) ||
         *(void**)(self + 0x230) != (void*)0x1654c08) &&
        *(void**)(self + 0x254) == 0) {
        void* p = FUN_00f473a0(0x34, "Simulator", 0, 0, 0, 0);
        void* tp = p ? (void*)((CTexPreload*)p)->ctor(-1) : 0;
        void* old = *(void**)(self + 0x254);
        if (tp != old) {
            if (tp)
                (*(void(__fastcall**)(void*))(*(int*)tp))(tp);
            *(void**)(self + 0x254) = tp;
            if (old)
                (*(void(__fastcall**)(void*))(*(int*)old + 4))(old);
        }
        ((CTexPreload*)*(void**)(self + 0x254))->preloadListVoid(g_propList881288);
        uint32_t keybuf[3];
        keybuf[1] = 0xefbda3ff;
        keybuf[2] = 0x40464100;
        uint32_t i = 0;
        do {
            keybuf[0] = *(uint32_t*)((char*)g_arr157f528 + i);
            ((CTexPreload*)*(void**)(self + 0x254))->preloadListKey(keybuf);
            i += 4;
        } while (i < 0x58);
    }
}

// @ 0x00cd54c0
NOINLINE void __fastcall FUN_00cd54c0(char* self, int)
{
    cRefBase* p = *(cRefBase**)(self + 0x254);
    if (!p)
        return;
    ((CTexPreload*)p)->clear();
    p = *(cRefBase**)(self + 0x254);
    if (!p)
        return;
    *(void**)(self + 0x254) = 0;
    p->Release();
}

// @ 0x00cd54f0
NOINLINE bool CTribeMode::FUN_00cd54f0()
{
    char* self = (char*)this;
    char* sp = (char*)((CExtF67D90*)NounManager())->call();
    if (!sp || *(int*)(self + 0x40) == *(int*)(self + 0x44))
        return false;
    float* a = (float*)(sp + 0x10f0);
    float* b = (float*)(sp + 0x10f4);
    float* large = a;
    if (*a > *b)
        large = b;
    if (*large / *b < g_1485720)
        return 0;
    return 1;
}

// @ 0x00cd5550
unsigned char cTribeModeStrategy::F_cd5550()
{
    if (mPtr_40 != mPtr_44)
        return *(mPtr_44 - 4) + 0 * (int)(size_t)mPtr_44;
    return 0;
}

// @ 0x00cd5570
bool cTribeModeStrategy::Write(Stream* s)
{
    unsigned char* w = (unsigned char*)this - 0xc;   // cVarList base subobject (object-0x0c)
    uint32_t tag = 0x116dd1b;
    StreamInner* inner = s->Get_20();
    EA_IO_WriteUint32(inner->Write_18(), &tag, 1, 0);
    cVarListSerializer ser(w, &g_157f290, 0x1a80d26);
    bool ok = ser.Serialize(s);
    if (ok) {
        uint32_t nPaths = (uint32_t)((mTribePathsEnd - mTribePathsBegin) / 0x14);
        inner = s->Get_20();
        EA_IO_WriteUint32(inner->Write_18(), &nPaths, 1, 0);
        if (nPaths != 0) {
            uint32_t off = 0;
            uint32_t cnt = nPaths;
            for (;;) {
                TribePath* path = (TribePath*)(mTribePathsBegin + off);
                uint32_t nPts = (uint32_t)((path->mpEnd - path->mpBegin) / 0xc);
                inner = s->Get_20();
                EA_IO_WriteUint32(inner->Write_18(), &nPts, 1, 0);
                if (nPts != 0) {
                    uint32_t j = 0;
                    uint32_t c = nPts;
                    for (;;) {
                        inner = s->Get_20();
                        EA_IO_WriteUint32(inner->Write_18(),
                                          (const uint32_t*)(path->mpBegin + j), 3, 0);
                        j += 0xc;
                        if (--c == 0) break;
                    }
                }
                off += 0x14;
                if (--cnt == 0) break;
            }
        }
    }
    return ok;
}

// @ 0x00cd56e0
void cTribeModeStrategy::F_cd56e0()
{
    RefMgr* p = new (g_StrSimulator, 0, 0, 0, 0) RefMgr;
    RefMgr* old = (RefMgr*)mp_394;
    if (p != old) {
        if (p) p->AddRef();
        mp_394 = p;
        if (old) old->Release();
    }
    ((RefMgr*)mp_394)->Update_1c();
}

// @ 0x00cd5750
int cTribeModeStrategy::F_cd5750()
{
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    if (!tribe)
        return 0;
    float f = g_flt_158133c;
    if (mb_3a3) {
        unsigned char noKey = TerrainNotHasKey();
        if (!noKey) {
            if ((int)f <= ((int(__thiscall*)(void*))(*(void***)tribe)[0xa4 / 4])(tribe)) {
                uint32_t pop = ((cTribe*)tribe)->GetAdultPopulation();
                uint32_t max = ((cTribe*)tribe)->GetMaxPopulation();
                if (pop < max)
                    return 1;
            }
        }
    }
    return 0;
}

// @ 0x00cd5810
void* SP_FindClosest(const TribeVec* v, const cSPVector3_s00cd_5550* pos, TribePred pred)
{
    unsigned char* it = v->mpBegin;
    unsigned char* end = v->mpEnd;
    void* best = 0;
    float bestDist = g_fltmax;
    if (it == end)
        return best;
    do {
        void* elem = *(void**)it;
        if (pred(elem)) {
            void* sub = (unsigned char*)elem + 0x120;
            cSPVector3_s00cd_5550* p = ((cSPVector3_s00cd_5550* (__thiscall*)(void*))(*(void***)sub)[0x2c / 4])(sub);
            float dx = p->x - pos->x;
            float dy = p->y - pos->y;
            float dz = p->z - pos->z;
            float d = dx * dx + dy * dy + dz * dz;
            if (bestDist > d) {
                best = elem;
                bestDist = d;
            }
        }
        it += 4;
    } while (it != end);
    return best;
}

// @ 0x00cd58d0
void WriteSTLSequenceT(Stream* s, unsigned char* vec)
{
    unsigned char* begin = *(unsigned char**)vec;
    unsigned char* end = *(unsigned char**)(vec + 4);
    uint32_t n = (uint32_t)((end - begin) >> 4);
    StreamInner* inner = s->Get_20();
    EA_IO_WriteUint32(inner->Write_18(), &n, 1, 0);
    unsigned char* p = begin;
    while (p != end) {
        (*(Elem16**)p)->Write_4(s);
        p += 0x10;
    }
    s->End_1c();
}

// @ 0x00cd5a40
ElemRef* CopyCtorRange(ElemRef* first, ElemRef* last, ElemRef* dst)
{
    while (first != last) {
        if (dst) {
            dst->mpVtbl = &g_vt14774c4_s00cd_5550;
            dst->m4 = first->m4;
            RefObj* p = first->mp8;
            dst->mp8 = p;
            if (p)
                p->AddRef();
            dst->m0c = first->m0c;
        }
        first++;
        dst++;
    }
    return dst;
}

// @ 0x00cd5a90
ElemRef* AssignRange(ElemRef* first, ElemRef* last, ElemRef* dst)
{
    while (first != last) {
        dst->m4 = first->m4;
        RefObj* p = first->mp8;
        RefObj* d = dst->mp8;
        if (p != d) {
            if (p)
                p->AddRef();
            dst->mp8 = p;
            if (d)
                d->Release();
        }
        dst->m0c = first->m0c;
        first++;
        dst++;
    }
    return dst;
}

// @ 0x00cd5af0
ElemRef* CopyBackwardRange(ElemRef* first, ElemRef* last, ElemRef* dst)
{
    while (last != first) {
        last--;
        dst--;
        dst->m4 = last->m4;
        RefObj* p = last->mp8;
        RefObj* d = dst->mp8;
        if (p != d) {
            if (p)
                p->AddRef();
            dst->mp8 = p;
            if (d)
                d->Release();
        }
        dst->m0c = last->m0c;
    }
    return dst;
}

// @ 0x00cd5e40
bool cTribeModeStrategy::F_cd5e40()
{
    if (mp_1cc != 0) {
        void* h = mp_1cc;
        void* a0 = mp_1d0;
        void* a1 = mp_1d4;
        void* a2 = mp_1d8;
        void* a3 = mp_1dc;
        mp_1cc = 0;
        EA_Messaging_RemoveHandler(h, a0, a1, a2, a3);
    }
    if (mp_254 != 0) {
        ((C20Obj*)mp_254)->clear();
        if (mp_254 != 0) {
            RefObj* p = (RefObj*)mp_254;
            mp_254 = 0;
            p->Release();
        }
    }
    if (mb_228 != 0) {
        mb_228 = 0;
        if (g_169b054 == 0) {
            void* p = EA_operator_new(0x100, g_StrSimSingleton, 0, 0, 0, 0);
            g_169b054 = p ? ((SimSingleton*)p)->Init() : 0;
        }
        ((void(__thiscall*)(void*)) (*(void***)g_169b054)[0x20 / 4])(g_169b054);
        if (mp_23c != 0) {
            ((void(__thiscall*)(void*)) (*(void***)mp_23c)[8 / 4])(mp_23c);
            if (mp_23c != 0) {
                ((void(__thiscall*)(void*, int)) (*(void***)mp_23c)[0])(mp_23c, 1);
            }
            mp_23c = 0;
        }
        if (mp_240 != 0) {
            ((cTribeDisplayStrategy*)mp_240)->Deactivate();
            if (mp_240 != 0) {
                unsigned char* q = (unsigned char*)mp_240;
                mp_240 = 0;
                ((void(__thiscall*)(void*)) (*(void***)(q + 0x3c))[4 / 4])(q + 0x3c);
            }
        }
        if (mp_1c8 != 0) {
            ((Obj1c8*)mp_1c8)->Method();
            if (mp_1c8 != 0) {
                RefMgr* p = (RefMgr*)mp_1c8;
                mp_1c8 = 0;
                p->Release();
            }
        }
    }
    return true;
}

// @ 0x00cd5f70
void SP_cTribeModeStrategy_ContinueLoading()
{
    ((SettingObj*)GetSetting9())->Method();
    void* b = FUN_01021260();
    void* p = FUN_01021230();
    RefObj* local = 0;
    void* mgr = PropertyManager();
    if (local != 0) {
        RefObj* t = local;
        local = 0;
        t->Release();
    }
    void* id = ((MgrA*)p)->Get(0xe38475d9, &local);
    ((void(__thiscall*)(void*, void*)) (*(void***)mgr)[0x2c / 4])(mgr, id);
    void* e = ((MgrB*)b)->Get_713e0();
    ((PMObj*)PlanetModel())->Method_8d8a0(e, 1, 1);
    void* out = 0;
    if (local != 0) {
        RefObj* prop;
        unsigned char ok = ((PropObj*)local)->GetProp(0x96bf2d79, &prop);
        if (ok && ((PropValue*)prop)->mType == 10) {
            void* v = Property_GetUInt(prop);
            out = *(void**)v;
        }
    }
    interface_cast_0xd1c610(out, 0);
    if (local != 0)
        local->Release();
}

// @ 0x00cd6040
void FUN_00cd6040()
{
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    RefObj* local = 0;
    cTribeSensors* ts = (cTribeSensors*)tribe;
    if (ts->Test1()) {
        if (ts->Test2()) {
            void* pm = PropertyManager();
            if (local != 0) {
                RefObj* t = local;
                local = 0;
                t->Release();
            }
            ((void(__thiscall*)(void*, uint32_t, uint32_t, RefObj**)) (*(void***)pm)[0x2c / 4])(pm, 0x96986124, 0xf71fa311, &local);
        } else {
            void* pm = PropertyManager();
            if (local != 0) {
                RefObj* t = local;
                local = 0;
                t->Release();
            }
            ((void(__thiscall*)(void*, uint32_t, uint32_t, RefObj**)) (*(void***)pm)[0x2c / 4])(pm, 0xed8aab2c, 0xf71fa311, &local);
        }
    } else {
        void* pm = PropertyManager();
        if (local != 0) {
            RefObj* t = local;
            local = 0;
            t->Release();
        }
        ((void(__thiscall*)(void*, uint32_t, uint32_t, RefObj**)) (*(void***)pm)[0x2c / 4])(pm, 0xcb0b8413, 0xf71fa311, &local);
    }
    if (local != 0) {
        void* world = GonzagoModelWorld();
        if (world != 0) {
            WorldObj* w = (WorldObj*)GonzagoModelWorld();
            w->Notify(local, 3);
        }
        if (local != 0)
            local->Release();
    }
}

// @ 0x00cd6130
void cTribeModeStrategy::F_cd6130(uint32_t id)
{
    if (mp_394 == 0)
        return;
    unsigned char* mgr = (unsigned char*)FUN_0067cac0();
    unsigned char* esi = *(unsigned char**)(mgr + 0x4c);

    if (id == 0x64e70b3) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0x2e573ccf)
            return;
        FUN_0067c830(FUN_0067cac0(), 0xb2a3fe9e);
        return;
    }
    if (id == 0x64d44f9) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0xb3009745)
            return;
        FUN_0067c830(FUN_0067cac0(), 0x2e573ccf);
        return;
    }
    if (id == 0x64c010f) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0x508fccb5)
            return;
        FUN_0067c830(FUN_0067cac0(), (uint32_t)SP_GetCamRotateTrigger());
        return;
    }
    if (id == 0x14363974) {
        void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
        if (tribe == 0)
            return;
        uint32_t pop = ((cTribe*)tribe)->GetAdultPopulation();
        uint32_t max = ((cTribe*)tribe)->GetMaxPopulation();
        if (pop >= max)
            return;
        void* ht = FUN_007eb100(FUN_0067de90(0xc));
        if (ht != 0) {
            unsigned char* n = *(unsigned char**)ht;
            while (n != ht) {
                if (*(uint32_t*)(n + 0x10) == 0 &&
                    **(uint32_t**)(n + 0x14) == 0x782e0768)
                    return;
                n = *(unsigned char**)n;
            }
        }
        FUN_00b706a0(mp_394, 0x11ade9ce);
        return;
    }
    if (id == 0x83861976) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0x255c3c16)
            return;
        FUN_0067c830(FUN_0067cac0(), 0xb3009745);
        return;
    }
    if (id == 0x5ac72d7c) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != 0xb2a3fe9e)
            return;
        void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
        if (tribe == 0)
            return;
        unsigned char bl = FUN_00c8e850(tribe);
        unsigned char al = FUN_00c8e870(tribe);
        if (bl) {
            if (al) {
                FUN_00b706a0(mp_394, 0x2d99d0b);
                FUN_0067c830(FUN_0067cac0(), 0xf4ff7b8a);
                return;
            } else {
                FUN_00b706a0(mp_394, 0x391c432);
                FUN_0067c830(FUN_0067cac0(), 0xa15bb8dd);
                return;
            }
        } else {
            if (!al)
                return;
            FUN_00b706a0(mp_394, 0x69ba7f0d);
            FUN_0067c830(FUN_0067cac0(), 0xccb2843a);
            return;
        }
    }
    if (id == 0x53203528) {
        if (esi != 0 && *(uint32_t*)(esi + 8) != (uint32_t)SP_GetCamRotateTrigger())
            return;
        FUN_0067c830(FUN_0067cac0(), 0x255c3c16);
    }
}

// @ 0x00cd6710
cPosseInfo* DestroyRange(cPosseInfo* first, cPosseInfo* last, cPosseInfo* dst)
{
    while (first != last) {
        u8* p = (u8*)first->mName.mpBegin;
        int cap = (int)first->mName.mpCap;
        if (((cap - (int)p) & -2) > 2 && p != 0)
            operator_delete_array(p);
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00cd6760
cPosseInfo* CopyRange(cPosseInfo* first, cPosseInfo* last, cPosseInfo* dst)
{
    while (first != last) {
        if (first != dst)
            dst->mName.assign(first->mName.mpBegin, first->mName.mpEnd);
        dst->mField10 = first->mField10;
        dst->mField14 = first->mField14;
        dst->mField18 = first->mField18;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00cd67b0
cPosseInfo* CopyRangeBackward(cPosseInfo* first, cPosseInfo* last, cPosseInfo* dst)
{
    while (last != first) {
        --last;
        --dst;
        if (last != dst)
            dst->mName.assign(last->mName.mpBegin, last->mName.mpEnd);
        dst->mField10 = last->mField10;
        dst->mField14 = last->mField14;
        dst->mField18 = last->mField18;
    }
    return dst;
}

// @ 0x00cd6fd0
void __stdcall DoDestroyValues(cPosseInfo* first, cPosseInfo* last)
{
    for (; first < last; ++first) {
        u8* p = (u8*)first->mName.mpBegin;
        int cap = (int)first->mName.mpCap;
        if (((cap - (int)p) & -2) > 2 && p != 0)
            operator_delete_array(p);
    }
}

// @ 0x00cd7d10
Simulator::tGameDataVectorT* __cdecl CreateGameDataVector()
{
    Simulator::tGameDataVectorT* p = (Simulator::tGameDataVectorT*)operator_new(
        0x18, "Simulator/tGameDataVectorT", 0, 0, 0, 0);
    if (p) {
        ((void (__thiscall*)(void*))GameDataVectorBaseCtor)(p);
        p->mValue04 = 0;
        p->mValue08 = 0;
        p->mValue0c = 0;
        return p;
    }
    return 0;
}

// @ 0x00cd91b0
namespace SP {
uint32_t cTribeModeStrategy_s00cd_8e70::GetSelectedCreatureCount()
{
    SelSet set;
    GetSelectedCreatureSet(&set);
    return set.mCount;
}
}  // namespace SP

// @ 0x00cd92b0
namespace SP {
void Vec12::push_back(const Elem12& v)
{
    if (mpEnd < mpCapacity) {
        Elem12* p = mpEnd;
        mpEnd = p + 1;
        if (p) *p = v;
    } else {
        GrowVec12(mpEnd, &v);
    }
}
}  // namespace SP

// @ 0x00cd9440
namespace SP {
void Vec16::DestroyRange(Elem16_s00cd_8e70* first, Elem16_s00cd_8e70* last)
{
    Elem16_s00cd_8e70* it = (Elem16_s00cd_8e70*)FUN_00cd5a90(last, mpEnd, first);
    for (; it < mpEnd; ++it) {
        ((void (__thiscall*)(Elem16_s00cd_8e70*, int))(*(void***)it)[0])(it, 0);
    }
    mpEnd -= last - first;
}
}  // namespace SP

// @ 0x00cd9a10
namespace SP {
cTribeModeStrategy_s00cd_8e70::cTribeModeStrategy_s00cd_8e70()
{
    mpVtbl1 = VT_14426a0;
    mpVtbl2 = VT_13eb394;
    cGonzagoSubsystem_ctor(&mpVtbl3);
    mpVtbl1 = VT_1477648;
    mpVtbl2 = VT_1477640;
    mpVtbl3 = VT_14775f0;
    mpVtbl4 = VT_14775e8;
    mbInCityHallEditor = false;
    mbInAccessoryEditor = false;
    m2c = 0; m30 = 0; m34 = 0;
    m40 = 0; m44 = 0; m48 = 0;
    cGonzagoTimer_ctor(&mTimer);
    m78 = 0; m7c = 0; m80 = 0; m84 = 0;
    m94 = 0; m98 = 0; m9c = 0;
    mSub.Init(0, 0);
    mb198 = false;
    m19c = 0;
    m1a0 = 0.0f;
    mb1a4 = false;
    cGonzagoTimer_ctor(&mTimer2);
    m1c8 = 0; m1cc = 0; m1d0 = 0; m1d4 = 0; m1d8 = 0; m1dc = 0;
    cLocalInputState_ctor(&mInput);
    mb228 = false;
    m22c = 0;
    m230 = -1; m234 = -1;
    m238 = 0;
    m23c = 0; m240 = 0; m244 = 0;
    mb248 = false; mb249 = false; mb24a = false;
    m24c = 0; m250 = 0; m254 = 0;
    for (int i = 0; i < (int)(0x9c / 4); ++i) m258[i] = 0;
    m2f8 = 0; m2fc = 0;
    mpRecordBegin = maRecordBuffer;
    mpRecordEnd = maRecordBuffer;
    m318 = 0;
    mpRecordCapacity = maRecordBuffer + 4;
    m38c = 0xffffffffu;
    m390 = 1;
    m394 = 0; m398 = 0; m39c = 0;
    mb3a0 = false;
    mb3a3 = true;
    gpTribeModeStrategy = this;
}
}  // namespace SP

// @ 0x00cd9ce0
namespace SP {
SelSet* cTribeModeStrategy_s00cd_8e70::GetSelectedCreatureSet(SelSet* out)
{
    out->Initialize();
    cTribe_s00cd_8e70* tribe = NounManager_s00cd_8e70()->GetPlayerTribe();
    CreatureList* list = ((CreatureList* (__thiscall*)(cTribe_s00cd_8e70*))
        ((void**)tribe->mpVtable)[0x90 / 4])(tribe);
    for (cSPCreatureBase_s00cd_8e70** it = list->mpBegin; it != list->mpEnd; ++it) {
        cSPCreatureBase_s00cd_8e70* c = *it;
        if (c->mLoco.CanBeSelected()) {
            void* ref = c;
            if (ref) ((void (__thiscall*)(void*))(*(void***)ref)[0])(ref);
            SelSetIter iter; void* key = ref;
            out->Insert(&iter, &key, false);
            if (ref) ((void (__thiscall*)(void*))(*(void***)ref)[1])(ref);
        }
    }
    return out;
}
}  // namespace SP

// @ 0x00cdafb0
void cVec16::FUN_00cdafb0(Rec16* src)
{
    Rec16* end = mpEnd;
    if (end < mpCap) {
        mpEnd = end + 1;
        if (end != 0) {
            end->mpVtbl = (void*)0x14774c4;
            end->mU_04 = src->mU_04;
            void* obj = src->mpObj;
            end->mpObj = obj;
            if (obj != 0)
                ((void (__thiscall*)(void*))VT(obj)[0])(obj);
            end->mB_0c = src->mB_0c;
        }
    } else {
        FUN_00cd9490(end, src);
    }
}

// @ 0x00cdb000
void __cdecl FUN_00cdb000(void* a1, void* a2)
{
    cVec16* v = (cVec16*)a2;
    v->FUN_00cd9440(v->mpBegin, v->mpEnd);

    u32 count = 0;
    void* reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
    void* stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
    FUN_0093a780(stream, &count, 1, 0);
    v->FUN_00cd7c70(count);

    for (u32 i = 0; i < count; i++) {
        Rec16 tmp;
        tmp.mpVtbl = (void*)0x14774c4;
        tmp.mU_04 = 0;
        tmp.mpObj = 0;
        tmp.mB_0c = 0;
        (*(void (__thiscall**)(void*))0x14774cc)(&tmp);
        v->FUN_00cdafb0(&tmp);
        tmp.mpVtbl = (void*)0x14774c4;
        if (tmp.mpObj != 0)
            ((void (__thiscall*)(void*))VT(tmp.mpObj)[1])(tmp.mpObj);
    }
    ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);
}

// @ 0x00cdb1f0
void cVec1c::FUN_00cdb1f0(Rec1c* pos, Rec1c* src)
{
    Rec1c* end = mpEnd;
    if (end != mpCap) {
        if (pos <= src && src < end)
            src += 1;
        if (end != 0)
            FUN_00cd7010(end - 1);
        FUN_00cd67b0(pos, end - 1, end);
        if (src != pos)
            FUN_00cd6030(src->mpBegin, src->mpEnd);
        pos->mU_10 = src->mU_10;
        pos->mU_14 = src->mU_14;
        pos->mU_18 = src->mU_18;
        mpEnd = end + 1;
        return;
    }
    u32 oldCount = (u32)((u8*)end - (u8*)mpBegin) / 0x1c;
    u32 newCap = oldCount == 0 ? 1 : oldCount * 2;
    Rec1c* buf = (Rec1c*)FUN_00f473a0(newCap * 0x1c, "Simulator", 0, 0, "allocator.h", 0xd1);
    Rec1c* mid = (Rec1c*)FUN_00cd70c0(mpBegin, pos, buf);
    FUN_00cd6710(mpBegin, pos, buf);
    if (mid != 0)
        FUN_00cd7010(src);
    Rec1c* newEnd = (Rec1c*)FUN_00cd70c0(pos, end, mid + 1);
    FUN_00cd6710(pos, end, mid + 1);
    if (mpBegin != 0 && *(u32*)((u8*)mpBegin - 4) != 0)
        FUN_00f47380(mpBegin);
    mpEnd = newEnd;
    mpBegin = buf;
    mpCap = (Rec1c*)((u8*)buf + newCap * 0x1c);
}

// @ 0x00cdb3a0
void cTribeModeStrategy_s00cd_ab10::FUN_00cdb3a0(u32 a1, u32 a2)
{
    void* te = FUN_00b3d300();
    TerrainSphere* ts = (TerrainSphere*)MOPS(te)->FUN_00f67d90();
    if (ts->mF_10f4 > ts->mF_10f0) {
        u8 recbuf[0x10];
        ((cVec16*)((u8*)this + 0x40))->FUN_00cdafb0(
            (Rec16*)MOPS(recbuf)->FUN_00cd4720(a1, a2));
        Rec16* rec = (Rec16*)recbuf;
        rec->mpVtbl = (void*)0x14774c4;
        void* obj = rec->mpObj;
        if (obj != 0)
            ((void (__thiscall*)(void*))VT(obj)[1])(obj);
        ts->mF_10f0 += gF_01485720;
        MOPS((u8*)this + 0x58)->FUN_00bc3130();
    }
}

// @ 0x00cdb430
void cVec1c::FUN_00cdb430()
{
    Rec1c* end = mpEnd;
    if (end < mpCap) {
        mpEnd = end + 1;
        if (end != 0) {
            end->mpBegin = (void*)0x1667bac;
            end->mpEnd   = (void*)0x1667bac;
            end->mpCap   = (void*)0x1667bae;
            end->mU_14 = 0;
            end->mU_18 = 0;
        }
    } else {
        Rec1c tmp;
        tmp.mpBegin = (void*)0x1667bac;
        tmp.mpEnd   = (void*)0x1667bac;
        tmp.mpCap   = (void*)0x1667bae;
        tmp.mU_14 = 0;
        tmp.mU_18 = 0;
        FUN_00cdb1f0(end, &tmp);
        s32 rem = (s32)((u32)((u8*)tmp.mpCap - (u8*)tmp.mpBegin) & 0xfffffffe);
        if (rem > 2 && tmp.mpBegin != 0)
            FUN_00f47380(tmp.mpBegin);
    }
}

// @ 0x00cdb4c0
void __cdecl FUN_00cdb4c0(void* a1, void* a2)
{
    cVec16* v = (cVec16*)a2;
    v->FUN_00cd9440(v->mpBegin, v->mpEnd);

    void* reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
    void* stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
    u32 count = 0;
    FUN_0093a780(stream, &count, 1, 0);

    u32* begin = *(u32**)a2;
    for (u32 i = 0; i < count; i++) {
        u32 key = 0, val = 0;
        reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
        stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
        FUN_0093a780(stream, &key, 1, 0);
        ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);

        reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
        stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
        FUN_0093a780(stream, &val, 1, 0);
        ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);

        u32* end = *(u32**)((u8*)a2 + 4);
        u32* lo = begin;
        u32 n = (u32)(end - begin) / 2;
        while (n > 0) {
            u32 half = n >> 1;
            if ((s32)lo[half * 2] < (s32)key) {
                lo += half * 2 + 2;
                n -= half + 1;
            } else {
                n = half;
            }
        }
        if (lo != end && lo[0] == key) {
            lo[1] = val;
        } else if (end == *(u32**)((u8*)a2 + 8)) {
            u32 pair[2];
            pair[0] = key;
            pair[1] = val;
            FUN_00567e70(lo, pair);
        } else {
            u32* p = end;
            while (p > lo) {
                p[0] = p[-2];
                p[1] = p[-1];
                p -= 2;
            }
            lo[0] = key;
            lo[1] = val;
            *(u32**)((u8*)a2 + 4) = end + 2;
        }
        begin = *(u32**)a2;
    }
    ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);
}

// @ 0x00cdb6a0
void cVec14::FUN_00cdb6a0(cSPVector3_s00cd_ab10* pos, u32 count, cSPVector3_s00cd_ab10* value)
{
    u32 cur = (u32)((u8*)mpEnd - (u8*)mpBegin) / 0x14;
    if (cur < count) {
        u32 oldCount = (u32)((u8*)mpEnd - (u8*)mpBegin) / 0x14;
        u32 newCap = oldCount * 2;
        if (oldCount == 0)
            newCap = 1;
        u32 newSize = oldCount + count;
        if (newSize < newCap)
            newSize = newCap;
        cSPVector3_s00cd_ab10* buf = 0;
        if (newSize != 0)
            buf = (cSPVector3_s00cd_ab10*)FUN_00f473a0(newSize * 0x14, "Simulator", 0, 0, "allocator.h", 0xd1);
        u32 pre = (u32)((u8*)pos - (u8*)mpBegin);
        FUN_011e0744(buf, mpBegin, pre);
        cSPVector3_s00cd_ab10* mid = (cSPVector3_s00cd_ab10*)((u8*)buf + pre);
        FUN_00cd7d60(mid, count, value);
        u32 post = (u32)((u8*)mpEnd - (u8*)pos);
        FUN_011e0744((u8*)mid + count * 0x14, pos, post);
        if (mpBegin != 0 && *(u32*)((u8*)mpBegin - 4) != 0)
            FUN_00f47380(mpBegin);
        mpBegin = buf;
        mpEnd = (cSPVector3_s00cd_ab10*)((u8*)mid + post + count * 0x14);
        mpCap = (cSPVector3_s00cd_ab10*)((u8*)buf + newSize * 0x14);
    } else {
        u32 tail = (u32)((u8*)mpEnd - (u8*)pos);
        FUN_011e0744((u8*)pos + count * 0x14, pos, tail);
        FUN_00cd7d60(pos, count, value);
        mpEnd = (cSPVector3_s00cd_ab10*)((u8*)mpEnd + count * 0x14);
    }
}

// @ 0x00cdb8b0
f32 __cdecl FUN_00cdb8b0()
{
    void* rm = FUN_00b3d2c0();
    f32 lo = *(f32*)((u8*)rm + 0x10);
    rm = FUN_00b3d2c0();
    f32 hi = *(f32*)((u8*)rm + 0x1c);

    void* planet = FUN_01021260();
    f32 sum = 0.0f;
    if (planet != 0) {
        s32 total = FUN_00ac8fa0(0x01581288, 0xc9ce093a, 5);
        void* noun = FUN_00b3d300();
        void* tribe = MOPS(noun)->FUN_00bfc5f0();
        noun = FUN_00b3d300();
        PtrVec* vec = (PtrVec*)MOPS(noun)->FUN_00b21340((void*)0x00cd7d10,
                                                         (void*)0x00d3d420,
                                                         (void*)0x00accbb0,
                                                         (void*)0x00b1e500,
                                                         (void*)0x018c6d19);
        void** end = vec->mpEnd;
        for (void** p = vec->mpBegin; p != end; p++) {
            void* other = (void*)*p;
            if (other != tribe) {
                u32 id = 0;
                if (MOPS(other)->FUN_00c744e0(&id)) {
                    void* a = ((void* (__thiscall*)(void*))VT(tribe)[0x4c / 4])(tribe);
                    void* b = ((void* (__thiscall*)(void*))VT(other)[0x4c / 4])(other);
                    f32 rel = MOPS(FUN_00b3d2c0())->FUN_00d05a20(a, b, 0);
                    if (rel < lo)
                        rel = lo;
                    if (rel > hi)
                        rel = hi;
                    sum += rel;
                }
            }
        }
        f32 denom = (f32)(u32)total;
        if (total < 0)
            denom += 4294967296.0f;
        sum = -sum / (denom * hi);
    }

    void* g = FUN_00b3d410(0);
    if (g != 0) {
        void* gm = FUN_00b3d410(0xad56080c);
        sum += MOPS(gm)->FUN_00e3f7a0();
    }

    if (sum < gF_013eb1bc)
        sum = gF_013eb1bc;
    if (sum > gF_01485720)
        sum = gF_01485720;
    return sum;
}

// @ 0x00cdba50
u32 cTribeModeStrategy_s00cd_ab10::FUN_00cdba50()
{
    f32 v = FUN_00cdb8b0();
    if (v >= gF_013f26dc)
        return 0x0cac124d;
    if (v >= gF_0140d0cc)
        return 0xc2ca9495;
    return 0x60a78928;
}

// @ 0x00cdba90
void cTribeModeStrategy_s00cd_ab10::FUN_00cdba90()
{
    void* ticker = FUN_00b3d330();
    void* noun = FUN_00b3d300();
    PtrVec* vec = (PtrVec*)MOPS(noun)->FUN_00b21340((void*)0x00cd7d10,
                                                     (void*)0x00d3d420,
                                                     (void*)0x00accbb0,
                                                     (void*)0x00b1e500,
                                                     (void*)0x018c6d19);
    void*** pbegin = &vec->mpBegin;
    s32 count = (s32)((u8*)vec->mpEnd - (u8*)vec->mpBegin) >> 2;
    for (u32 i = 0; i < (u32)count; i++) {
        u32 item = (u32)(*pbegin)[i];
        void* planner = *(void**)(item + 0x290);
        if (planner != 0) {
            ((void (__thiscall*)(void*, void*))VT(ticker)[0x54 / 4])(ticker, planner);
            MOPS(planner)->FUN_00ce0a20();
        }
    }
}

// @ 0x00cdd500
void cTribeModeStrategy_s00cd_d500::PreGameModeTransition(u32 previousMode, u32 newMode)
{
    if (GetMode() == newMode)
        return;

    SetMode(newMode);
    BehaviorManager()->mSink_04.OnModeChange(previousMode, newMode);

    if (previousMode == 0x1654c02) {
        cEffectsManager* pEffects = EffectsManagerPtr();
        VSLOT_s00cd_d500(void (__thiscall*)(cEffectsManager*, s32, s32), pEffects, 0x98)(pEffects, 9, 0);
        FUN_00b6c280();
        if (newMode != 0xdbdba1 && newMode != 0x1654c06)
            FUN_00cd49a0();

        if (mpEditorHost_230 != 0) {
            if (newMode == 0xdbdba1) {
                cCommunityEditor* pEditor = mpEditorHost_230->mpEditor_5c;
                if (pEditor != 0 && FUN_00d09660((cPoly*)pEditor)) {
                    mSavedEditorValue_380 = FUN_00d09670((cPoly*)pEditor);
                    pEditor->Deactivate(true, true);
                }
            } else {
                mpEditorHost_230->Shutdown();
                if (mpEditorHost_230 != 0)
                    mpEditorHost_230->ReleaseOwnership(1);
                mpEditorHost_230 = 0;
            }
        }

        FUN_00cc8940(mpDisplayStrategy_234, 0);
        FUN_00cc93b0(mpDisplayStrategy_234, 0);

        if (newMode != 0xdbdba1) {
            if (mpDisplayStrategy_234 != 0) {
                mpDisplayStrategy_234->Deactivate();
                if (mpDisplayStrategy_234 != 0) {
                    RefCounted* pRef = &mpDisplayStrategy_234->mRef_3c;
                    mpDisplayStrategy_234 = 0;
                    pRef->Release();
                }
            }

            cSimTicker* pTicker = (cSimTicker*)SimTicker_s00cd_d500();
            FUN_00cc8b10()->Activate();
            pTicker->QueueFlush(FUN_00cc8b10());
            FUN_00bd83e0()->PostMsg();
            pTicker->QueueFlush((cTickerClient*)FUN_00bd83e0());
            FUN_00d51660()->Activate();
            pTicker->QueueFlush(FUN_00d51660());

            VSLOT_s00cd_d500(void (__thiscall*)(cPoly*), mpSaveObject_388, 0x24)(mpSaveObject_388);
            if (mpSaveObject_388 != 0) {
                cPoly* pOld = mpSaveObject_388;
                mpSaveObject_388 = 0;
                VSLOT_s00cd_d500(void (__thiscall*)(cPoly*), pOld, 0x08)(pOld);
            }
        }

        if (FUN_0067ddc0() != 0) {
            cPoly* pObject = FUN_0067ddc0();
            VSLOT_s00cd_d500(void (__thiscall*)(cPoly*, s32), pObject, 0x28)(pObject, 0);
            pObject = FUN_0067ddc0();
            VSLOT_s00cd_d500(void (__thiscall*)(cPoly*), pObject, 0x24)(pObject);
        }

        cPlanet* pPlanet = FUN_01021260_s00cd_d500();
        if (pPlanet != 0 && newMode == 0x1654c04) {
            cPlanetTree* pTree = pPlanet->mpTree_13c;
            PlanetSearchParams params;

            s32 nCount = pTree->mpEnd_0c0 - pTree->mpBegin_0bc;
            params.mKeys_20.Reserve(nCount);
            for (s32 i = 0; i < nCount; ++i)
                params.mKeys_20.PushBack(pTree->mpBegin_0bc[i]);

            NounVecOut<cNoun>* pVec =
                (NounVecOut<cNoun>*)NounManager_s00cd_d500()->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e);
            s32 nSites = (s32)(pVec->mItems_04.mpEnd - pVec->mItems_04.mpBegin);
            params.mPoints_34.Reserve(nSites);
            for (cNoun** pIt = pVec->mItems_04.mpBegin; pIt != pVec->mItems_04.mpEnd; ++pIt) {
                cNoun* pNoun = *pIt;
                if (!pNoun->IsRemoved()) {
                    cCell* pCell = (cCell*)pNoun->mpCell_a4;
                    if (pCell != 0)
                        params.mPoints_34.PushBack(pCell->mPosition_504);
                }
            }

            SortKeys(params.mKeys_20.mpBegin, params.mKeys_20.mpEnd);
            Key3* pNewEnd = UniqueKeys(params.mKeys_20.mpBegin, params.mKeys_20.mpEnd);
            params.mKeys_20.Erase(pNewEnd, params.mKeys_20.mpEnd);

            FUN_00c71560(pPlanet, -9);
            FUN_00c73310(pPlanet);
            FUN_00c73330(pPlanet);
            StarManager()->BuildTribeSites(pTree, &params);
            void* pSiteOwner;
            if (FUN_00c70c00(pPlanet))
                pSiteOwner = pPlanet;
            else
                pSiteOwner = pPlanet;
            FUN_00c82f80(pSiteOwner);

            if (BlockIsAllocated(params.mPoints_34.mpBegin))
                operator_delete_array(params.mPoints_34.mpBegin);
            if (BlockIsAllocated(params.mKeys_20.mpBegin))
                operator_delete_array(params.mKeys_20.mpBegin);
        }
    } else if (newMode == 0x1654c02 && previousMode == 0xdbdba1) {
        cPoly* pInput = GameInputManager();
        --((u32*)pInput)[0x110 / 4];
        FUN_00cc8940(mpDisplayStrategy_234, 1);
        FUN_00cc93b0(mpDisplayStrategy_234, 1);
    }

    switch (newMode) {
    case 0x1654c02:
        break;
    case 0x1654c03:
    case 0x1654c07:
    case 0x1654c08:
        gTribeTuningData.Init();
        LoadTribeToolData();
        LoadTribeArchetypeData();
        break;
    }

    Refresh();
}

// @ 0x00cdd960
s32 FUN_00cdd960()
{
    void* pTribe = NounManager_s00cd_d500()->GetPlayerTribe();
    PtrVec_s00cd_d500<cNoun>* pItems =
        &((NounVecOut<cNoun>*)NounManager_s00cd_d500()->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e))->mItems_04;

    cNoun** pIt = pItems->mpBegin;
    cNoun** const pEnd = pItems->mpEnd;
    s32 nResult = (s32)pItems;
    while (pIt != pEnd) {
        nResult = (s32)FUN_00cd4770(*pIt, pTribe);
        ++pIt;
    }
    return nResult;
}

// @ 0x00cdd9c0
s32 FUN_00cdd9c0(bool bBuildInstances)
{
    cPropertyList* pList = 0;
    cPoly* pPropertyManager = PropertyManager_s00cd_d500();
    VSLOT_s00cd_d500(void (__thiscall*)(cPoly*, u32, u32, cPropertyList**), pPropertyManager, 0x2c)
        (pPropertyManager, 0x535dc193, 0x2be764e2, &pList);

    float fProperty = GetPropertyFloat(pList, 0x49b71de, gMinTribeRadius);
    float fValue = gMinTribeRadius > fProperty ? gMinTribeRadius : fProperty;

    cPlanetModel* pModel = (cPlanetModel*)GetPlanetModel();
    cRenderEntity* pEntity = pModel->mpEntity_024;
    cTerraformingManager* pTerra = (cTerraformingManager*)GetTerraformingManager();

    NounVecOut<cNoun>* pVec =
        (NounVecOut<cNoun>*)NounManager_s00cd_d500()->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
    s32 nCount = 0;
    cNoun** pIt = pVec->mItems_04.mpBegin;
    cNoun** const pEnd = pVec->mItems_04.mpEnd;
    while (pIt != pEnd) {
        cNoun* pNoun = *pIt;
        if (pNoun->mNounType_108 == 0x57f09e5e) {
            ++nCount;
            pNoun->mTerraformSlot_11c = pTerra->AddPoke(pNoun->mPlacement_034.GetPosition(), fValue);

            if (bBuildInstances) {
                ModelInstance instance;
                instance.mFlags_00 = 0;
                instance.mCount_02 = 0;
                instance.mOrigin_04 = gDefaultOrigin;
                instance.mScale_10 = gModelScale;
                instance.mRotation_14 = gDefaultRotation;
                instance.mRotation_14 = Matrix3FromQuaternion(pNoun->mPlacement_034.GetRotation());
                instance.mFlags_00 |= 2;
                ++instance.mCount_02;
                instance.mOrigin_04 = *pNoun->mPlacement_034.GetPosition();
                instance.mFlags_00 |= 4;
                ++instance.mCount_02;
                pEntity->AddInstance(&instance, pList);
            }
        }
        ++pIt;
    }

    cSurfaceCellList* pSurface = gSurfaceCellList;
    s32 nCells = pSurface->mpEnd_30 - pSurface->mpBegin_2c;
    for (s32 i = 0; i < nCells; ++i)
        pTerra->AddSurfacePoint(&pSurface->mpBegin_2c[i], 0);
    pTerra->Commit();

    if (pList != 0)
        pList->Release();
    return nCount;
}

// @ 0x00cddda0
void cTribeModeStrategy_s00cd_d500::ContinueLoading()
{
    if (mpLoadingStrategy_240 != 0) {
        mpLoadingStrategy_240->Deactivate();
        if (mpLoadingStrategy_240 != 0) {
            RefCounted* pRef = &mpLoadingStrategy_240->mRef_3c;
            mpLoadingStrategy_240 = 0;
            pRef->Release();
        }
    }

    cTribe_s00cd_d500* pTribe = (cTribe_s00cd_d500*)NounManager_s00cd_d500()->GetPlayerTribe();
    if (pTribe != 0) {
        cPoly* pCursor = GetGameTerrainCursor_s00cd_d500();
        VSLOT_s00cd_d500(void (__thiscall*)(cPoly*, u32), pCursor, 0x58)
            (pCursor, VSLOT_s00cd_d500(u32 (__thiscall*)(cTribe_s00cd_d500*), pTribe, 0x94)(pTribe));
    }

    String16 name;
    name.SetEmpty();
    cPoly* pProfile = VSLOT_s00cd_d500(cPoly* (__thiscall*)(cTribe_s00cd_d500*, s32), pTribe, 0x00)(pTribe, 0);
    ((cSpeciesProfile*)pProfile)->GetUiName(&name);

    float fDistance = 0.0f;

    NounVecOut<cNoun>* pVec =
        (NounVecOut<cNoun>*)NounManager_s00cd_d500()->GetGameDataVector(F_cd7d10, F_d3d420, F_accbb0, F_b1e500, 0x18c6d19);
    cNounScratch scratch;
    scratch.Build((s32)(pVec->mItems_04.mpEnd - pVec->mItems_04.mpBegin), &pVec->mItems_04.mpCap);

    void** pRemovedEnd = 0;
    FUN_00829110(&pRemovedEnd, (void**)pVec->mItems_04.mpBegin,
                 (void**)pVec->mItems_04.mpEnd, scratch.mpBegin, pTribe);

    for (void** pIt = scratch.mpBegin; pIt != pRemovedEnd; ++pIt) {
        cNoun* pNoun = (cNoun*)*pIt;
        cTribeWorkArea* pArea = &pNoun->mWorkArea_120;
        const Vec3* pCenter = pArea->GetCenter();
        pArea->Transform(pCenter);
        float fSq = pCenter->x * pCenter->x + pCenter->y * pCenter->y + pCenter->z * pCenter->z;
        bool bPrime = pArea->IsPrime();
        if (bPrime)
            fDistance = sqrtf(fSq);

        PtrVec_s00cd_d500<cPoly> linked;
        pNoun->GetLinkedObjects(&linked);
        for (cPoly** pLinked = linked.mpBegin; pLinked != linked.mpEnd; ++pLinked) {
            cPoly* pEntry = *pLinked;
            if (pEntry == 0)
                continue;
            cPoly* pTool = VSLOT_s00cd_d500(cPoly* (__thiscall*)(cPoly*, u32), pEntry, 0x0c)(pEntry, 0x4f176642);
            if (pTool == 0)
                continue;
            if (bPrime)
                VSLOT_s00cd_d500(void (__thiscall*)(cPoly*, const void*), pTool, 0xe4)(pTool, &gPrimeToolLabel);
            else
                VSLOT_s00cd_d500(void (__thiscall*)(cPoly*, const void*), pTool, 0xe4)(pTool,
                    (const void*)FUN_00b6f0c0(pTribe->mpDisplayStrategy_234, pTribe->mpDisplayStrategy_234));
            FUN_00c0d950(pTool, !bPrime);
        }
    }

    for (void** pIt = scratch.mpBegin; pIt != pRemovedEnd; ++pIt) {
        cTribe_s00cd_d500* pLoaded = (cTribe_s00cd_d500*)*pIt;
        pLoaded->UpdateGridAndHutArea(fDistance);
        pLoaded->ResetToolLayout();
        pLoaded->ReserveToolsSlots(true);
        FUN_00b6f380(&pLoaded->mNamedInserter_230, &name);

        ToolNode* pNode;
        if (pLoaded == pTribe)
            pNode = pLoaded->mToolTree_238.Find(0xe);
        else
            pNode = pLoaded->mToolTree_238.Find(0);
        pLoaded->mToolSlot_034.SetTool(pNode->mValue_14);
    }

    FUN_00cdd9c0(false);

    for (void** pIt = scratch.mpBegin; pIt != pRemovedEnd; ++pIt) {
        cPoly* pEntry = (cPoly*)*pIt;
        if (pEntry != 0)
            VSLOT_s00cd_d500(void (__thiscall*)(cPoly*), pEntry, 0x04)(pEntry);
    }
    if (BlockIsAllocated(scratch.mpBegin))
        operator_delete_array(scratch.mpBegin);
}

// @ 0x00cde160
bool cPlayer::Read(cIOStream* pStream)
{
    u32 nVersion = 0;
    ReadInt32(StreamHandle(pStream), &nVersion, 1, 0);

    cVarListSerializer_s00cd_d500 serializer((const cVarListOwner*)this - 1, 0x157f290, 0x1a80d26);
    if (nVersion != 0x116dd1b || !serializer.Serialize(pStream))
        return false;

    u32 nRows = 0;
    ReadInt32(StreamHandle(pStream), &nRows, 1, 0);
    ResizePlayerRows(&mpRows_020, nRows);

    for (u32 i = 0; i < nRows; ++i) {
        cPlayerRow* pRow = mpRows_020 + i;
        u32 nPoints = 0;
        ReadInt32(StreamHandle(pStream), &nPoints, 1, 0);
        pRow->Resize((s32)nPoints);
        for (u32 j = 0; j < nPoints; ++j)
            ReadInt32(StreamHandle(pStream), &pRow->mpBegin[j], 3, 0);
    }

    if (mpInventory_190 != 0)
        mpInventory_190->Configure(0xf71fa311, 0x4a5c4493, gSpaceInventoryFlags);
    return true;
}

// @ 0x00cde5b0
void cMode::FUN_00cde5b0()
{
    cBaby* begin = mSub.mpVec1Begin;
    cBaby* end   = mSub.mpVec1End;

    // release every pooled element, then rewind the pool back to empty
    cBaby* gap = (cBaby*)FUN_00b969a0(end, end, begin);
    ((cSelf*)&mSub.mpVec1Begin)->FUN_01023030(gap, end);

    uint8_t* endB   = (uint8_t*)mSub.mpVec1End;
    uint8_t* beginB = (uint8_t*)begin;
    endB += (beginB - endB) / (int)sizeof(cBaby) * (int)sizeof(cBaby);
    mSub.mpVec1End = (cBaby*)endB;

    FUN_00cde2f0();
}

// @ 0x00cde600
void cMode::FUN_00cde600()
{
    cBaby* begin = mSub.mpVec1Begin;
    cBaby* end   = mSub.mpVec1End;

    // release every pooled element, then rewind the pool back to empty
    cBaby* gap = (cBaby*)FUN_00b969a0(end, end, begin);
    ((cSelf*)&mSub.mpVec1Begin)->FUN_01023030(gap, end);

    uint8_t* endB   = (uint8_t*)mSub.mpVec1End;
    uint8_t* beginB = (uint8_t*)begin;
    endB += (beginB - endB) / (int)sizeof(cBaby) * (int)sizeof(cBaby);
    mSub.mpVec1End = (cBaby*)endB;

    FUN_00cde2f0();
    vOn44();
}

// @ 0x00cde660
void cMode::FUN_00cde660(int arg1)
{
    const uint32_t msg = mSub.m224;
    bool runState8 = false;

    switch (mSub.m220)
    {
    case 0:
        if (((cSelf*)FUN_00b3d410())->FUN_00e36e00())
            mSub.m220 = 1;
        break;

    case 1:
        if (msg == 0xdbdba1 && !mSub.m396 && !mSub.m1c && !mSub.m1d)
        {
            void* res    = ((cVtV54*)FUN_0067ddd0())->v54(0x5e5284a);
            void* objPtr = 0;
            ((cSelf*)&objPtr)->FUN_00572660(res);

            void* ep = objPtr;
            if (ep)
            {
                void* bound = ((cSelf*)&mSub.mp390)->FUN_00a16f40();
                if (((cObjEp*)ep)->v8(bound, 0, 0x14f10872))
                    ((cObj390*)mSub.mp390)->v8(0);
                ((cObjEp*)ep)->v4();
            }
        }

        mSub.m220 = 2;
        mSub.m22c = 0;

        if (msg == 0xffffffffu || msg == 0x2ccd1d2)
            FUN_00cd5f70();
        ((cSelf*)this)->FUN_00cd9da0();

        if (msg == 0x2ccd1d2 || msg == 0xffffffffu || msg == 0x1654c01)
        {
            mSub.m198 = 1;
        }
        else if (msg == 0xdbdba1)
        {
            if (!mSub.m198)
                goto tail;
            ((cSelf*)FUN_00b3d4f0(1))->FUN_00e2f270();
        }
        else
        {
            FUN_00cd3fb0(0x56d1871);
            mSub.m198 = 0;
        }
        break;

    case 2:
    {
        ((cSelf*)FUN_00b3d350())->FUN_00b8c330(arg1, 0, 0);

        cRowSet* s = (cRowSet*)FUN_00b3d440();
        if (s->m1e5f0 == s->m1e5f4 && mSub.m22c <= 0x3e8)
            goto tail;

        mSub.m220 = 3;
        mSub.m22c = 0;

        if (msg > 0x1654c01)
        {
            if (msg == 0x1654c08)
            {
                ((cSelf*)this)->FUN_00cddda0();
                goto tail;
            }
            if (msg == 0x2ccd1d2)
            {
                FUN_00cde5b0();
                goto tail;
            }
        }
        else if (msg == 0x1654c01)
        {
            FUN_00cde600();
            goto tail;
        }
        else if (msg == 0xffffffffu)
        {
            FUN_00cde5b0();
            goto tail;
        }
        else if (msg == 0xdbdba1)
        {
            ((cSelf*)this)->FUN_00cdcb10();
            goto tail;
        }
        break;
    }

    case 3:
        mSub.m220 = 4;
        mSub.m22c = 0;
        FUN_00cd7770();
        break;

    case 4:
        ((cSelf*)FUN_00b3d350())->FUN_00b8c330(arg1, 0, 0);
        if (mSub.m22c <= 5)
            goto tail;
        {
            void* obj = ((cTribeAux*)FUN_00b3d350())->mp24;
            if (!((cVtV50*)obj)->v50())
                goto tail;
        }
        mSub.m220 = 5;
        mSub.m22c = 0;
        FUN_00cdc8b0();
        if (msg == 0x1654c08)
            goto tail;
        FUN_00cddcf0();
        goto tail;

    case 5:
        if (mSub.m22c > 5)
        {
            mSub.m220 = 6;
            FUN_00cd6040();
            ((cSelf*)this)->FUN_00cd53e0();
        }
        {
            cTribeView* tribe = (cTribeView*)((cSelf*)FUN_00b3d300())->FUN_00bfc5f0();
            if (tribe)
            {
                void* p = ((cVtV2c2*)&tribe->m120)->v2c(DAT_014763b8, DAT_014771f8);
                ((cSelf*)FUN_00b3d480())->FUN_00acc700(p);
            }
            ((cVtV2c1*)FUN_00b3d230())->v2c(arg1);
            ((cVtV30*)FUN_00b3d230())->v30(arg1);
        }
        goto tail;

    case 6:
    {
        ((cVtV5c*)FUN_0067dd50())->v5c(0x16, 2);
        int   ebx = ((cVtV28*)FUN_00401010())->v28();
        int   ebp = ((cVtV10*)FUN_00b3d520())->v10();
        void* p   = ((cSelf*)FUN_00401090())->FUN_004df420();
        p = (uint8_t*)p + 0x504;
        uint8_t ok = ((cVtV3c*)FUN_00401010())->v3c(p);

        if (!ok && ebx <= 0 && ebp <= 0 && ((cSelf*)mSub.mp248)->FUN_007b19c0())
        {
            if (((cVtV44*)FUN_0067dd00())->v44() == 1)
                ((cVtV40*)FUN_0067dd00())->v40(0);
        }
        else
        {
            if (((cVtV44*)FUN_0067dd00())->v44())
                goto tail;
            ((cVtV40*)FUN_0067dd00())->v40(1);
            goto tail;
        }
        ((cSelf*)FUN_00cc8b10_s00cd_e2f0())->FUN_00cc4fa0();
        mSub.m220 = 7;
        ((cVtV60*)FUN_0067dd50())->v60(0x16, 2);
        break;
    }

    case 7:
        if (mSub.mp390)
        {
            ((cObj390*)mSub.mp390)->vc(0);
            void* old = mSub.mp390;
            if (old)
            {
                mSub.mp390 = 0;
                ((cVtV4*)old)->v4();
            }
            ((cSelf*)FUN_00b3d320())->FUN_00b1dfc0();
        }

        ((cSelf*)((cSelf*)FUN_00b3d300())->FUN_00bfc5f0())->FUN_00c93a40();

        if (msg == 0x2ccd1d2 || msg == 0xffffffffu || msg == 0x1654c01)
        {
            if (!DAT_015fd928 ||
                ((cStateList*)DAT_015fd928)->mp70 == &((cStateList*)DAT_015fd928)->mp70)
                ((cSelf*)FUN_00b3d340())->FUN_00b2a100();
            FUN_00cd4280();
        }

        if (mSub.m395 && mSub.m396)
        {
            mSub.m396 = 0;
            ((cSelf*)FUN_00b3d320())->FUN_00b1e410(0x1654c04);
            ((cSelf*)FUN_00b3d380())->FUN_00b32250(0x4bf38a7);
        }

        if (mSub.m394)
        {
            ((cSelf*)this)->FUN_00cdcf70();
            mSub.m394 = 0;
        }

        if (mSub.m395 && msg != 0xdbdba1 &&
            ((cSelf*)FUN_00b3d410())->FUN_00e36fa0() &&
            (!DAT_015fd928 ||
             ((cStateList*)DAT_015fd928)->mp70 == &((cStateList*)DAT_015fd928)->mp70))
        {
            ((cSelf*)FUN_00b3d410())->FUN_00e36de0();
            mSub.m220 = 9;
            goto tail;
        }
        runState8 = true;
        break;

    case 8:
        runState8 = true;
        break;

    case 9:
        if (((cSelf*)FUN_00b3d410())->FUN_00e36dd0())
        {
            ((cSelf*)FUN_00b3d410())->FUN_00e3b1f0();
            mSub.m220 = 0xa;
        }
        break;

    case 10:
        if (((cSelf*)FUN_00b3d410())->FUN_00e36e10())
            runState8 = true;
        break;

    default:
        mSub.m220 = 0xb;
        break;
    }

    if (runState8)
    {
        bool listEmpty = !DAT_015fd928 ||
                         ((cStateList*)DAT_015fd928)->mp70 == &((cStateList*)DAT_015fd928)->mp70;
        if (msg != 0xdbdba1 && !listEmpty)
            ((cSelf*)FUN_00b3d410())->FUN_00e3e350(0, 0x1654c02, 1);
        mSub.m220 = 0xb;
        ((cSelf*)FUN_00b3d380())->FUN_00b32250(0x4bf38a7);
    }

tail:
    ((cSelf*)FUN_00b3d230())->FUN_00b5e9a0(arg1);
}

// @ 0x00cdec80
void cModeSub::FUN_00cdec80(int msg, int kind)
{
    if (vOn20() == kind)
        return;

    vOn44(kind);

    if (kind == 0x1654c02)
    {
        ((cVtV98*)FUN_0067ddd0())->v98(9, 1);

        if (m395 && m1d == 1)
        {
            ((cSelf*)FUN_00b3d410())->FUN_00e3e350(1, 0x1654c04, 1);
            m396 = 1;
            m220 = 0;
        }
        else
        {
            m220 = 1;
        }

        m224 = msg;
        m228 = 0x1654c02;
        m22c = 0;
        m21c = 1;
        ((cSelf*)FUN_00b3d380())->FUN_00b32220(0x4bf38a7);

        if (msg == 0xdbdba1)
            ((cSelf*)m230)->FUN_00ccec20(1);

        ((cMode*)((cModeHdr*)this - 1))->FUN_00cde660(0);
        vOn4c();
        return;
    }

    if (msg == 0x1654c02)
    {
        if (kind == 0xdbdba1 && !m1c && !m1d)
        {
            void* server = FUN_0067dcc0();
            if (server)
            {
                cSphereView* sphere = (cSphereView*)((cSelf*)FUN_00b3d300())->FUN_00f67d90();
                uint32_t     stamp  = 0;
                ((cSelf*)sphere)->FUN_00c77380(0x55d6335, &stamp);

                cMsgObj* obj = (cMsgObj*)operator new[](0x40, DAT_013ebc58, 0, 0, 0, 0);
                if (obj)
                    ((cSelf*)obj)->FUN_00421c80(0);
                else
                    obj = 0;

                void* holder = 0;
                ((cSelf*)&holder)->FUN_0061df40(obj);
                obj = (cMsgObj*)holder;

                obj->m30 = 0x90a03fdf;
                obj->m08 = stamp;
                obj->m10 = 5;
                obj->m18 = 1;

                ((cVtV14*)server)->v14((int)obj->m30, obj);
                obj->v8();
                vOn4c();
                return;
            }
        }
        else
        {
            if (FUN_00b3d520())
                ((cVtV18*)FUN_00b3d520())->v18(0, 3);

            cMode* mode = (cMode*)((cModeHdr*)this - 1);
            ((cSelf*)mode)->FUN_00cd54c0();
            FUN_00c9a080();

            ((cSelf*)&mpVec2Begin)->FUN_00cd9440(mpVec2Begin, mpVec2End);
            ((cSelf*)&mpVec1Begin)->FUN_00b9c250();
            ((cSelf*)&mpVec3Begin)->FUN_00530c80(mpVec3Begin, mpVec3End);
            m6c = 0;
            ((cSelf*)&mpVec4Begin)->FUN_00e25bd0(mpVec4Begin, mpVec4End);
            m194 = 0.0f;
            ((cSelf*)&m9c)->FUN_00cd6610();
            mode->vOn4c();

            if (kind == 0x2ccd1d2 || kind == 0xffffffffu || kind == 0x1654c04)
                FUN_00b976f0();
        }
    }

    vOn4c();
}

// @ 0x00cdef00
void cTribeModeStrategy_s00cd_ef00::HandleSimulationUpdate(float dtReal, float dtGame)
{
    int msGame = RoundToInt(dtGame * 1000.0f);
    int msReal = RoundToInt(dtReal * 1000.0f);

    if (FUN_00b3d320_s00cd_ef00()->mbSkip) {
        FUN_00b3d230_s00cd_ef00()->f_00b5e9a0(msGame);
        return;
    }
    if (GetCurrentGameMode_00b5b800() != &DAT_01654c02)
        return;
    if (mState != 0xb) {
        mWaitFrames++;
        f_00cde660(msGame);
        return;
    }

    if (mTimerA.IsRunning_00feba90() && mTimerA.GetElapsedTime_00bc3190() > 60000) {
        MessageServer_0067dcc0()->PostMessage(0x445f729, 0, 0);
        IncrementGoalProgress_00cdab10();
    }
    if (mTimerB.IsRunning_00feba90() && mTimerB.GetElapsedTime_00bc3190() > 1000) {
        mTimerB.Stop_00bc3170();
        if (ConfigManager_0067dd30()->GetSetting(0x4ea96cb) &&
            ConfigManager_0067dd30()->GetSetting(0x5b5bb5e) && !f_00cd4460(0x56d1871))
            { cGameTimeManager* gtm = GameTimeManager_00b3d380(); gtm->IncPauseGate_00b32220(0x64beb65); }
    }
    if (mpDisplayStrategy)
        mpDisplayStrategy->UpdateUI_00cc99b0(msGame);
    mpInputStrategy->f_00cceca0(0, 0);

    if (!f_00cd4460(0x56d1871)) {
        bool noA = ConfigManager_0067dd30()->GetSetting(0x4ea96cb) == 0;
        if (!ConfigManager_0067dd30()->GetSetting(0x5b5bb5e) || noA) {
            f_00cd3fb0(0x56d1871);
            mbTutorialHint = false;
            FUN_0067cac0_s00cd_ef00()->UpdateHints_0067c350(1, 1);
            f_00cd6390(0);
            if (FUN_00b3d280())
                FUN_00b3d280()->field_390 = false;
            cGameTimeManager* gtm = GameTimeManager_00b3d380();
            if (gtm->GetPauseGateCount_00b320d0(0x64beb65) > 0) {
                gtm = GameTimeManager_00b3d380();
                gtm->DecPauseGate_00b32250(0x64beb65);
                GameInputManager_00b3d250()->mPauseCount--;
            }
            FUN_00b3d4f0()->f_00e2f270(0);
            mpMusic->f_00b700f0(0x11ade9ce);
            mpMusic->f_00b700f0(0x69ba7f0d);
            mpMusic->f_00b700f0(0x391c432);
            mpMusic->f_00b700f0(0x2d99d0b);
            mpMusic->f_00b700f0(0x5312da01);
            mpMusic->f_00b700f0(0x9a44d4ab);
            mpMusic->f_00b700f0(0x7d7315c8);
        }
    }

    cGameInputManager* input = GameInputManager_00b3d250();
    if (input && (input->IsMouseButtonDown(1) || input->IsMouseButtonDown(2) ||
                  input->IsMouseButtonDown(3) || input->IsMouseButtonDown(4)))
        f_00cd4b70(0);

    if (mpTracked) {
        if (mpTracked->IsDead()) {
            f_00cd4b70(0);
        } else {
            cCameraController* cam = FUN_00b3d280();
            if (cam) {
                cSpatialSub* sp = &((cMember*)mpTracked)->mSpatial;
                Vector3* dir = sp->GetDirection();
                if (Dot3_004885d0(dir) > 0.0f)
                    cam->f_00b14520(dir, (&((cMember*)mpTracked)->mSpatial)->GetVelocity_00d20610());
            }
        }
    }

    cGameNounManager_s00cd_ef00* nouns = NounManager_00b3d300();
    cTribe_s00cd_ef00* playerTribe = nouns->GetPlayerTribe_00bfc5f0();
    if (playerTribe)
        FUN_00b3d480_s00cd_ef00()->f_00acc700(playerTribe->mSub.v2c(75.0f, 112.5f));

    int gameMs = GameTimeManager_00b3d380()->f_00b31c60(msGame);
    FUN_00b3d230_s00cd_ef00()->Update2c(msGame);
    float dt = (float)(uint32_t)gameMs * 0.001f;
    playerTribe->GetPoliticalID();

    PtrVector<void>& tribes = nouns->GetGameDataVector_00b21340(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00accbb0, (void*)FUN_00b1e500,
        0x18c6d19)->mData;
    for (void** it = tribes.mpBegin; it != tribes.mpEnd; ++it) {
        cTribe_s00cd_ef00* tribe = (cTribe_s00cd_ef00*)*it;
        if (!tribe->mSub.IsDestroyed() && !tribe->mbSkipUpdate) {
            int rel = RelationshipManager_00b3d2c0()->f_00d00a70(
                tribe->GetPoliticalID(), NounManager_00b3d300()->GetPlayerTribe_00bfc5f0()->GetPoliticalID(), 1);
            if (tribe->mRelationship != rel && tribe->mRelationship != -1) {
                switch (rel) {
                case 0:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1217, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 1:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1216, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 2:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1215, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 3:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1214, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                case 4:
                    gTribeHud_0169b41c->mpLastTribe = tribe;
                    EventLog_00b3d3e0()->PostFeedbackEvent_00dd8640(0x507c1213, 0x182cd6ce, 0, 0, 1, 0);
                    break;
                }
                if (!tribe->mbSkipUpdate)
                    FUN_00ba58e0(tribe, 5);
            }
            tribe->mRelationship = rel;
        }
        cTribeTools* tools = tribe->f_00c8fee0();
        if (tools && (uint32_t)gameMs > 0) {
            float rate = GetPropertyFloat_004e1c70(gTribeTuning_0158128c, 0x78dcad72, 0.0125f);
            float cap = GetPropertyFloat_004e1c70(gTribeTuning_0158128c, 0xad06ca38, 20.0f);
            uint32_t n = tools->mTools.size();
            float v = (float)n * rate * dt + tribe->mFoodAccum;
            tribe->mFoodAccum = MinF(v, cap);
        }
    }

    if (!(GameTimeManager_00b3d380()->mFlags & 1)) {
        FUN_01022920(gameMs);
        CitizenVector& sel = mSelected;
        if (sel.mpBegin != sel.mpEnd) {
            mSelectTimer -= dt;
            FUN_00b3d480_s00cd_ef00();
            cCitizen* leader = playerTribe->GetLeader_00c00650();
            if (mSelectTimer > 0.0f && !leader->mbBusy) {
                for (uint32_t i = 0; i < sel.size(); i++) {
                    cCitizen* c = sel.mpBegin[i].p;
                    if (!c->mbBusy && c->mbActive && !c->IsDead()) {
                        c->f_00c1d5e0(1, 0xadff412, 0xadff412);
                    } else {
                        c->SetTarget(-1);
                        c->f_00c0b370(-1);
                        sel.mpBegin[i].Swap_00ac9480(sel.mpBegin[sel.size() - 1]);
                        c->mFlags &= ~0x4000;
                        sel.pop_back();
                        c->f_00c17350(0xadff412, 0);
                    }
                }
                leader->f_00c1d5e0(sel.mpBegin != sel.mpEnd, 0x1d491515, 0x1d491515);
            } else {
                void* home = playerTribe->f_00c8fee0();
                for (uint32_t i = 0; i < sel.size(); i++) {
                    cCitizen* c = sel.mpBegin[i].p;
                    if (c->mbActive && !c->IsDead()) {
                        FUN_00c0d3a0(c);
                        if (c->f_00c04590() != home)
                            c->SetTarget(-1);
                        c->mFlags &= ~0x4000;
                        c->f_00c042e0();
                        c->f_00c0b370(-1);
                        c->f_00c14750(1);
                        c->f_00c17350(0xadff412, 0);
                    }
                }
                leader->f_00c17350(0x1d491515, 0);
                sel.erase_00e25bd0(sel.mpBegin, sel.mpEnd);
            }
        } else {
            mSelectTimer = 0.0f;
        }

        nouns = NounManager_00b3d300();
        PtrVector<void>& objs = nouns->GetGameDataVector_00b21340(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00cdb110, (void*)FUN_00b1e520, 0xce9f6639)->mData;
        uint32_t count = objs.size();
        for (uint32_t i = 0; i < count; i++) {
            cRefObj* o = (cRefObj*)objs.mpBegin[i];
            if (o) {
                o->AddRef();
                if (o->mbActive)
                    o->Update(gameMs);
                o->Release();
            }
        }

        nouns = NounManager_00b3d300();
        PtrVector<void>& herds = nouns->GetGameDataVector_00b21340(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00accc30, (void*)FUN_00b1e500, 0x1be418e)->mData;
        for (void** it = herds.mpBegin; it != herds.mpEnd; ++it) {
            cHerd* h = (cHerd*)*it;
            if (h->f_00c6a020())
                h->Update_00c6d7c0(gameMs);
        }

        nouns = NounManager_00b3d300();
        PtrVector<void>& traps = nouns->GetGameDataVector_00b21340(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00cdb620, (void*)FUN_00b1e500, 0x61494be)->mData;
        for (void** it = traps.mpBegin; it != traps.mpEnd; ++it)
            ((cAnimalTrap*)*it)->f_00bcc230(gameMs);

        if (FUN_00b3d2b0()->f_00ac79d0()) {
            cCastable* c = FUN_00b3d2b0()->f_00ac79d0();
            cCastTarget* t = c ? (cCastTarget*)c->Cast(0xeef202b7) : 0;
            t->f_00c36ae0(dt);
        }
        mGameTimeMs += gameMs;
    }

    cCommunityEditor_s00cd_ef00* editor = mpInputStrategy->mpEditor;
    if (editor && editor->f_00d09660())
        mpInputStrategy->mpEditor->HandleSimulationUpdate_00d124e0(msGame);

    if (FUN_0067ddc0_s00cd_ef00()) {
        Vector3 dir;
        bool have = false;
        cCameraController* cam = FUN_00b3d280();
        if (cam) {
            dir = *cam->GetAnchorDirection0_00b10200();
            have = true;
        } else if (App_0067dd10()->GetCameraManager()->GetActiveControllerID() == 0x8916f92d) {
            cCameraLookup* ctl = App_0067dd10()->GetCameraManager()->GetActiveController();
            if (ctl) {
                cCameraObj* o = ctl->Find(0x7ba6612);
                if (o) {
                    dir = o->mDirection;
                    have = true;
                }
            }
        }
        if (have) {
            float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + 1e-08f);
            Vector3 n(inv * dir.x, dir.y * inv, dir.z * inv);
            FUN_0067ddc0_s00cd_ef00()->SetOrientation(&dir, &n);
        }

        cCamera* camera = App_0067dd10()->GetCameraManager()->GetActiveCamera();
        if (camera) {
            cCameraTransform t;
            t.pos.x = gCameraPos_0169b2cc.x;
            t.pos.y = gCameraPos_0169b2cc.y;
            t.pos.z = gCameraPos_0169b2cc.z;
            t.pos.w = 1.0f;
            t.a = 0;
            t.b = 0;
            t.rot.r[0] = gCameraRot_0169b378.r[0];
            t.rot.r[1] = gCameraRot_0169b378.r[1];
            t.rot.r[2] = gCameraRot_0169b378.r[2];
            camera->f_007c40f0(&t);
            FUN_0067ddc0_s00cd_ef00()->SetTransform(&t.pos);
        }
        Vector3 up = PlanetModel_00b3d350()->mpSub->GetUp();
        up.Normalize_00fb8db0();
        FUN_0067ddc0_s00cd_ef00()->SetUp(&up);
        FUN_0067ddc0_s00cd_ef00()->Commit();
    }

    if (mpDisplayStrategy) {
        mpDisplayStrategy->f_00ccdc30(0, msGame, msReal);
        mpDisplayStrategy->f_00cc9620();
        mpDisplayStrategy->f_00cc9cd0(msGame);
    }

    if (FUN_00b3d3c0_s00cd_ef00()) {
        int st = FUN_00b3d4d0()->mState;
        if (st != 1 && st != 2) {
            cHotSpots* hs = FUN_00b3d3c0_s00cd_ef00();
            Property* prop;
            if (GetDebugBool(0x7a3da342, prop)) {
                PtrVector<cMember>* members = (PtrVector<cMember>*)playerTribe->GetMembers();
                uint32_t n = members->size();
                for (uint32_t i = 0; i < n; i++) {
                    cSpatialSub* sp = &members->mpBegin[i]->mSpatial;
                    if (sp->IsVisible()) {
                        BoundingBox bb = sp->GetBoundingBox();
                        Vector3 c((bb.lower.x + bb.upper.x) * 0.5f, (bb.upper.y + bb.lower.y) * 0.5f,
                                  (bb.upper.z + bb.lower.z) * 0.5f);
                        hs->f_00b76d20(&c, sp->GetBoundingRadius(), 1, 1, 0);
                    }
                }
            }
            Vector3 center = gCameraPos_0169b2cc;
            if (GetDebugBool(0x965f10f9, prop))
                center = *FUN_00b3d280()->GetAnchorDirection0_00b10200();
            else
                center = FUN_00b3d240()->GetCenter(1);
            hs->f_00b76d20(&center, 1.0f, 1, 0, 1);
        }
    }

    cTribe_s00cd_ef00::HotSpotsUpdate_00c9b740(dtReal);
    FUN_00b3d230_s00cd_ef00()->Update30(msGame);
    mpInputStrategy->f_00ccff40();
    FUN_00b6dbd0(dtGame);
    FUN_00b3d230_s00cd_ef00()->f_00b5e9a0(msGame);
}

// @ 0x0135db90
void FUN_0135db90()
{
    g_0157f290 = T("mGoalProgressHistory", 0x55ce8d1u, 0x40, fn_00692ca0, fn_00cdb000, fn_00cd58d0, fn_00c2e4e0, fn_00692fb0, fn_00cd5940, fn_00ca8710);
    g_0157f2cc = T("mFullHealsPerPerTribeMember", 0x5ee744au, 0x7c, fn_00692ca0, fn_00cdb4c0, fn_00cd5980, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00cd92f0);
    g_0157f308 = T("mTotalTimeInTribe", 0x5ee6f2fu, 0x78, fn_00692ca0, fn_00572810, fn_00572840, fn_00693090, fn_00694f00, fn_00b1fbf0, fn_00675ca0);
    g_0157f344 = T("mEnchantedAnimals", 0x608904du, 0x94, fn_00692ca0, fn_00acdf10, fn_00aca730, fn_00c2e4e0, fn_00692fb0, fn_00b6f860, fn_00c6c390);
    g_0157f380 = T("mEnchantedAnimalsTimer", 0x60892b0u, 0x1a0, fn_00692ca0, fn_00572810, fn_00ac88f0, fn_006930b0, fn_00694fc0, fn_00b1fbf0, fn_00acbb80);
    g_0157f3bc = T("mUnlockedTools", 0x68c869au, 0xa8, fn_00692ca0, fn_00c78020, fn_00ac9f70, fn_00c2e4e0, fn_00692fb0, fn_00cd6630, fn_00c78a50);
    g_0157f3f8 = T("mpAccessories", 0x625716fu, 0x19c, fn_00692ca0, fn_00ba8250, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157f434 = T("mPlayerSpearOrnaments", 0x681efbau, 0x258, fn_00692ca0, fn_00cd6680, fn_00cd6f60, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157f470 = T("mNPCSpearOrnaments", 0x681efbbu, 0x2a8, fn_00692ca0, fn_00cd6680, fn_00cd6f60, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157f4ac = T("mbMatingAllowed", 0x68c86b2u, 0x3a3, fn_00692ca0, fn_00ac8750, fn_00ac8780, fn_00693090, fn_00694fa0, fn_00b1fbf0, fn_0057ce00);
}
