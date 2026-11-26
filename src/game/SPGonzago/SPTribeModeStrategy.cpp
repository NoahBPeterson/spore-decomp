// src/game/SPGonzago/SPTribeModeStrategy.cpp -- migrated from slice(s) s00cd7d90, s00cd7530, s00cd7100, s00cd6f60, s00cd6ef0, s00cd6e40, s00cd6980, s00cd68d0, s00cd6800, s00cdc8b0, s00cdbb10, s00cd9da0, s00cd3480, s00ccefb0, s00ccece0, s00ccdd70, s0135d100, s00cdef00, s00cde2f0, s00cdd500, s00cdab10, s00cd8e70, s00cd75f0, s00cd6680, s00cd5550, s00cd45c0, s00ccfc20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeModeStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" void FUN_00bc36d0();
extern "C" void FUN_00cd45c0();
extern "C" char g_14774c4[];
extern "C" char g_1667bac[];
extern "C" char g_1667bae[];

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
#include "SP/cSPSwatch.h"
#include "EA/Variant.h"
#include "SP/cPlanetRecord.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTribePlanner.h"
#include "SP/cITerrainSphere.h"
#include <intrin.h>

// ---- items of slice s00ccfc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void*  GetGameTerrainCursor();                 // 0x00b30d70
void*  FUN_00b3d240_s00cc_fc20();                         // 0x00b3d240
void*  FUN_00b3d300();                         // 0x00b3d300  SP::NounManager
void*  FUN_00b3d350();                         // 0x00b3d350  SP::PlanetModel
uint32_t FUN_00ccefb0(void*, void*);           // 0x00ccefb0  GetTribeCursorID
void   FUN_00ad92d0(void*);                    // 0x00ad92d0  eastl vector dtor
void*  FUN_00bca2c0();                         // 0x00bca2c0  cAgentOrderManager::FirstPending
void*  FUN_006bb5e0();                         // 0x006bb5e0
void*  FUN_00a206f0();                                      // 0x00a206f0 EA::Audio::GetSystemAT
void*  FUN_00bfc5f0(void*);                                 // 0x00bfc5f0 (thiscall)
void*  FUN_00b82fc0(void*, void*);                          // 0x00b82fc0 (thiscall)
void*  FUN_00b88590(void*, void*);                          // 0x00b88590 (thiscall)
void*  FUN_00c275b0(void*, int, void*, void*);              // 0x00c275b0 (thiscall)
void   FUN_006a3570(void*, void*);                          // 0x006a3570 (thiscall)
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
struct HeapVec {
    void** mpBegin;     // +0x00
    void** mpEnd;       // +0x04
    void** mpCap;       // +0x08
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
extern const float   g_flt_1473c70;    // 0x01473c70
extern const float   g_flt_1486110;    // 0x01486110
extern const float   g_flt_15812dc;    // 0x015812dc
extern float         g_1559bdc[];      // 0x01559bdc float table (stride 2 floats)
extern void*         g_169b054;        // 0x0169b054 SimSingleton
extern unsigned char g_rand_1601760[];  // 0x01601760 random LCG
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
extern const cSPVector3_s00cd_5550 g_v3_169b360;  // 0x0169b360
extern const cSPVector3_s00cd_5550 g_v3_169b36c;  // 0x0169b36c
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
void* FUN_00d1e660();                                // 0x00d1e660
float SP_GetPropertyT_float(void* props, uint32_t hash, float def); // 0x004e1c70
void* FUN_0059aed0(float* out, const void* a, const void* b); // 0x0059aed0
void* FUN_00b3d2b0(int a);                           // 0x00b3d2b0
void* FUN_00ac7ab0(void* self, float f, void* container, int mode); // 0x00ac7ab0
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
void* SP_QuaternionToMatrix(float* out, const void* q); // 0x004a9b40
class cVarListSerializer {
public:
    uint32_t mData[0x26e];
    cVarListSerializer(void* varList, void* a, int b);  // 0x00692f90
    bool Serialize(Stream* s);                          // 0x00692900
};
void* FUN_00ac79d0(void* self);                      // 0x00ac79d0
void  SP_NormalizedSafe(cSPVector3_s00cd_5550* out, const cSPVector3_s00cd_5550* in); // 0x00449c20
void* SP_QuaternionToMatrix(void* out, const void* q); // 0x004a9b40
void* SP_EffectsManager();                           // 0x0067ddd0
struct cTribe {
    uint32_t GetAdultPopulation();   // 0x00c8f3a0  thiscall
    uint32_t GetMaxPopulation();     // 0x00c8eae0  thiscall
};
struct cGameNounManager {
    void* GetPlayerTribe();          // 0x00bfc5f0  thiscall, no args
};
struct cHintMgr;
struct cRefObj_s00cd_68d0;
namespace SP { struct TribeObjectTable; }
struct cLocalInputState_s00cd_7530 {
    char mPad00[0x40];

    void OnMouseWheel(int delta, float x, float y, int flags);   // 0x00697b40
};
struct cSPTimer {
    uint32_t data[8];
    bool IsRunning_00feba90();
    uint64_t GetElapsedTime_00bc3190();
    void Stop_00bc3170();
    void Reset();                       // 0x00bc3170 (s00cd68d0's Teardown)
};
class cTribeModeStrategy {
public:
    uint32_t pad00[1];             // +0x00
    int      mState4;              // +0x04  (read by FUN_00cd6800's switch, s00cd6800)
    uint32_t pad08[6];             // +0x08..+0x1f
    unsigned char* mTribePathsBegin; // +0x20  (vector<path> begin)
    unsigned char* mTribePathsEnd;   // +0x24
    uint32_t pad28[6];             // +0x28..+0x3f
    unsigned char* mPtr_40;        // +0x40
    unsigned char* mPtr_44;        // +0x44
    uint32_t pad48[0x60];          // +0x48..+0x1c7 (the cSPTimer at +0x1a8 is reached by Timer_Reset())
    void* mp_1c8;                  // +0x1c8
    void* mp_1cc;                  // +0x1cc  (first RemoveHandler arg)
    void* mp_1d0;                  // +0x1d0
    void* mp_1d4;                  // +0x1d4
    void* mp_1d8;                  // +0x1d8
    void* mp_1dc;                  // +0x1dc
    uint32_t pad1e0[0x12];         // +0x1e0..+0x227
    unsigned char mb_228;          // +0x228
    unsigned char pad229[0x12];    // +0x229..+0x23a
    void* mp_23c;                  // +0x23c
    void* mp_240;                  // +0x240
    uint32_t pad244[4];            // +0x244..+0x253 (mb_24a at +0x24a, mp_250 at +0x250: see Flag24a()/Obj250())
    void* mp_254;                  // +0x254
    uint32_t pad258[0x4f];         // +0x258..+0x393
    void* mp_394;                  // +0x394  mission manager / next strategy
    void* mp_398;                  // +0x398  effect object (s00cd68d0's Teardown)
    uint32_t pad39c[1];            // +0x39c..+0x39f
    unsigned char pad3a0[3];       // +0x3a0..+0x3a2
    unsigned char mb_3a3;          // +0x3a3  (read by F_cd5e40's GetTribeCursorID path)
    unsigned char pad3a4[4];       // +0x3a4..+0x3a7 (the earlier landing's trailing pad)

    unsigned char F_cd5550();
    bool          Write(Stream* s);
    void          F_cd56e0();
    int           F_cd5750();
    unsigned char TerrainNotHasKey();   // 0x00cd44a0  thiscall (external, other slice)
    bool          F_cd5e40();
    void          F_cd6390(unsigned char enable);
    void          F_cd6130(uint32_t id);
    void          FUN_00cd6800();   // 0x00cd6800
    void          Teardown();       // 0x00cd68d0
    cHintMgr*     GetHintMgr();     // 0x0067caf0
    bool          HasObject(unsigned int id);   // 0x00cd6e40
    bool          IsObjectAllowed(unsigned int id);   // 0x00cd6ef0
    void          OnMouseWheel(int delta, float x, float y, int flags);   // 0x00cd7530
    void          RaiseEvent(uint32_t eventHash);     // 0x00cd6980 (the slice's SignalTribeEvent)

    // the embedded cSPTimer at +0x1a8 (s00cd68d0's Teardown calls Reset); cSPTimer is defined later in this file
    void Timer_Reset() { ((cSPTimer*)((char*)this + 0x1a8))->Reset(); }
    // the ID->object hashtable at +0xa8 (s00cd6e40's HasObject); SP::TribeObjectTable is its slice-defined view
    SP::TribeObjectTable& Objects() { return *(SP::TribeObjectTable*)((char*)this + 0xa8); }
    unsigned char& Flag24a() { return *(unsigned char*)((char*)this + 0x24a); }   // s00cd68d0's Teardown clears it
    void*& Obj250() { return *(void**)((char*)this + 0x250); }                      // s00cd68d0: released and cleared
    bool AllowAllObjects() { return *(bool*)((char*)this + 0x198) != 0; }           // s00cd6ef0's gate at +0x198
    cLocalInputState_s00cd_7530* mInput7530() { return (cLocalInputState_s00cd_7530*)((char*)this + 0x1e0); }  // s00cd7530's input state
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
struct cCommunity {
    void* GetLeader();                       // 0x00c00650  thiscall, returns [this+0x11c]
};
struct LeaderSub {
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
    virtual cSPVector3_s00cd_5550* GetPos();            // +0x2c
    virtual float*      GetQuat();           // +0x30
};
struct LeaderObj { unsigned char mPad00[0xc0]; LeaderSub mSub; };   // sub-object at +0xc0
struct RandLCG  { uint32_t Uniform(uint32_t range); };              // 0x00a68fb0  thiscall
struct SysObj   { unsigned char mPad00[0x24]; void* mp24; };
struct Holder   { unsigned char mPad00[0x130]; void* mp130; };
struct FxSub {
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
    virtual void Apply(cSPVector3_s00cd_5550* v);       // +0x38
};
struct FxObj {
    unsigned char mPad00[0x34];
    FxSub         mSub34;                    // +0x34
    unsigned char mPad38[0x124 - 0x38];      // +0x38..+0x123
    unsigned char mb124;                     // +0x124
    unsigned char mPad125[3];                // +0x125..+0x127
    void*         mp128;                     // +0x128
    uint32_t      mPad12c;                   // +0x12c
    uint32_t      m130;                      // +0x130
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
struct XformMsg {
    uint16_t mFlags;    // +0x00
    uint16_t mCount;    // +0x02
    float    mX, mY, mZ; // +0x04
    uint32_t mPad10;    // +0x10
    float    mMatrix[9]; // +0x14
    void ctor();
};
struct HashElem {
    uint32_t pad0;          // +0x00
    unsigned char* mp4;     // +0x04
    unsigned char* mp8;     // +0x08
    uint32_t m0c;           // +0x0c
    void DoFreeNodes(unsigned char* a, unsigned char* b);  // 0x00a1b6c0 (thiscall)
    void Clear();
};
// ---- items of slice s00cd5550 end

// ---- items of slice s00cd6680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void ReadInt32Stream(void* stream, void* out, int count, int flag);
typedef unsigned char u8;
typedef unsigned int  u32;
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
struct cStream;
struct cEntry {
    virtual void Destroy();      // 0x00
    virtual void Release();      // 0x04
};
struct cInner {
    virtual void v00();          // 0x00
    virtual void v01();          // 0x04
    virtual void v02();          // 0x08
    virtual void v03();          // 0x0c
    virtual void v04();          // 0x10
    virtual void v05();          // 0x14
    virtual cStream* GetStream();// 0x18
    virtual void v07();          // 0x1c
    virtual void v08();          // 0x20
};
struct cOwner {
    virtual void v00();                     // 0x00
    virtual void v01();                     // 0x04
    virtual void v02();                     // 0x08
    virtual void v03();                     // 0x0c
    virtual void v04();                     // 0x10
    virtual void v05();                     // 0x14
    virtual void v06();                     // 0x18
    virtual void v07();                     // 0x1c
    virtual cInner* GetInner();             // 0x20
    virtual void v09();                     // 0x24
    virtual void SetProperty(u32 id, void* value, int flags);  // 0x28
};
static inline const int& MinInt(const int& a, const int& b)
{
    return (b < a) ? b : a;
}
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
struct cGameInputManager_s00cd75f0;
struct cTerrainSphere_s00cd75f0 {
    bool __thiscall Contains(uint32_t key);                  // 0x00c772c0
};
struct cNounManager_s00cd75f0 {
    cTerrainSphere_s00cd75f0* __thiscall GetCurrentTerrainSphere(); // 0x00f67d90
};
struct cGameTimeManager_s00cd75f0 {
    int __thiscall GetTimerState(uint32_t timer);            // 0x00b320d0
};
cGameInputManager_s00cd75f0* __cdecl GameInputManager_s00cd_75f0();      // 0x00b3d250
cGameTimeManager_s00cd75f0*  __cdecl GameTimeManager_s00cd_75f0();       // 0x00b3d380
cNounManager_s00cd75f0*      __cdecl NounManager_s00cd_75f0();           // 0x00b3d300
bool __cdecl IsInputConsumed(int key);                        // 0x00d4a4a0
struct cGameInputManager_s00cd75f0 {
    virtual void v00();                                     // +0x00
    virtual void v01();                                     // +0x04
    virtual void v02();                                     // +0x08
    virtual void v03();                                     // +0x0c
    virtual void v04();                                     // +0x10
    virtual void v05();                                     // +0x14
    virtual bool v06(uint32_t key);                         // +0x18
    virtual void v07();                                     // +0x1c
    virtual void v08();                                     // +0x20
    virtual void v09();                                     // +0x24
    virtual void v10();                                     // +0x28
    virtual void v11();                                     // +0x2c
    virtual void v12();                                     // +0x30
    virtual void v13();                                     // +0x34
    virtual void v14();                                     // +0x38
    virtual void v15();                                     // +0x3c
    virtual void v16();                                     // +0x40
    virtual bool v17(int key, int modifiers);               // +0x44
    virtual void v18();                                     // +0x48
    virtual bool v19(int key, int modifiers);               // +0x4c
};
struct cTribeModeStrategy_s00cd75f0 {
    bool __thiscall HasEvent(uint32_t eventHash);            // 0x00cd4460
    void __thiscall RaiseEvent(uint32_t eventHash);          // 0x00cd6980
    bool __thiscall OnInput(int key, int modifiers);          // 0x00cd75f0
};
// ---- items of slice s00cd75f0 end

// ---- items of slice s00cd8e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vector3_s00cd_8e70 {
    float x, y, z;
    Vector3_s00cd_8e70() {}
    Vector3_s00cd_8e70(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
}
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
struct cSpeciesManager {
    void* GetAvatarProfile();                           // 0x004df420
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
cSpeciesManager*  __cdecl FUN_00401090_s00cd_8e70();               // 0x00401090
}
namespace SP {
void __cdecl FUN_004010a0(void* out, uint32_t id);      // 0x004010a0
}
namespace SP {
void* __cdecl FUN_005ecf80(void* in, uint32_t id);      // 0x005ecf80
}
namespace SP {
void __cdecl FUN_00f47380(void* p);                     // 0x00f47380 operator delete[]
}
namespace SP {
bool __cdecl FUN_0064f350(uint32_t group, uint32_t id, int mode);  // 0x0064f350
}
namespace SP {
bool __cdecl GetPropertyAsUint32Array(uint32_t group, uint32_t id, uint32_t* count, uint32_t* list); // 0x00401100
}
namespace SP {
struct FixedPoolDesc {                                  // fixed_pool_base scratch descriptor
    uint32_t m00[7];
    void Init(void* begin, int blockSize, int count, int align, int pad);   // 0x00921260
};
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
void  __cdecl FUN_00cd5af0(Elem16_s00cd_8e70* a, Elem16_s00cd_8e70* b, Elem16_s00cd_8e70* c);       // 0x00cd5af0
}
namespace SP {
void* __cdecl FUN_00cd5a40(Elem16_s00cd_8e70* a, Elem16_s00cd_8e70* b, Elem16_s00cd_8e70* c);       // 0x00cd5a40
}
namespace SP {
void  __cdecl FUN_00cd4540(Elem16_s00cd_8e70* a, Elem16_s00cd_8e70* b, Elem16_s00cd_8e70* c);       // 0x00cd4540
}
namespace SP {
void* __cdecl FUN_00f40000(uint32_t size);                         // operator new (EASTL)
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
void* __cdecl FUN_00b3d330();                       // 0x00b3d330 SimTicker
void* __cdecl FUN_00b3d4d0_s00cd_ab10();                       // 0x00b3d4d0 GetTriggerMgr
void* __cdecl FUN_00675250(u32, u32);               // 0x00675250 Achievements::Controller
void* __cdecl FUN_0067dcc0();                       // 0x0067dcc0 MessageServer
void  __cdecl FUN_00cd98e0(u32);                    // 0x00cd98e0
void  __cdecl FUN_00cd3f20(u32);                    // 0x00cd3f20 SetTerrainSphereParam
void* __cdecl FUN_00b6f0c0(u32);                    // 0x00b6f0c0
void  __cdecl FUN_00e398e0(u32, void*);             // 0x00e398e0
void* __cdecl FUN_00b3d310(void*, u32);             // 0x00b3d310
void  __cdecl FUN_00cd9660(void*);                  // 0x00cd9660
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
struct Global169b41c {
    u8    pad000[0x1c];
    void* mpObj;          // 0x1c
};
extern Global169b41c* gP_0169b41c;   // 0x0169b41c
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
struct TribeData_s00cd_ab10 {
    u8   mPad000[0x108];
    u32* mpIndexArray;    // 0x108
    u8   mPad10c[0x11c - 0x10c];
    u32* mpBegin;         // 0x11c
    u32* mpEnd;           // 0x120
};
struct GameData {
    u8   mPad000[0x11c];
    u32* mpBegin;         // 0x11c
    u32* mpEnd;           // 0x120
    u8   mPad124[0x234 - 0x124];
    void* mpTribe;        // 0x234
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
extern float gHotSpotDistance;                                   // 0x0158125c
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
void cTribe_SetupHotSpot(const Vec3* pPoint, s32 nKind);         // 0x00c9afb0
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
extern "C" char g_18c6d19[];   // 0x018c6d19
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

// ---- items of slice s00ccdd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <class R> inline R V0(void* o, int off) { return ((R (__thiscall *)(void*))(*(void***)o)[off / 4])(o); }
template <class R, class A> inline R V1(void* o, int off, A a) { return ((R (__thiscall *)(void*, A))(*(void***)o)[off / 4])(o, a); }
template <class R, class A, class B> inline R V2(void* o, int off, A a, B b) { return ((R (__thiscall *)(void*, A, B))(*(void***)o)[off / 4])(o, a, b); }
struct RefA { virtual void AddRef(); virtual void Release(); };                    // slots 0/1
struct ModeStrategy : RefA {
    ModeStrategy* Ctor();                                            // 0xe31320
    void Setup();                                                    // 0xe31670
    void SetFlag(int v);                                             // 0xe31160 ret 4
    u8   GetFlag();                                                  // 0xe31170
};
struct TribeData { void* Fn(int idx); };
struct Tribe { TribeData* GetThing(int); };                          // 0xc8e820 ret 4
struct Orn2 : RefA {
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual int NounType();                                          // slot 8 (0x20)
    char pad[0x84 - 4];
    u32 flags;                                                       // +0x84
    char pad2[0xa5 - 0x88];
    u8 f_a5;
    char pad3[3];
    u8 f_a9;
};
struct NounMgr {
    Orn2* Create(u32 noun, u32 kind, u32 z, const void* pos, const void* q);  // 0xb23650 ret 0x14
    Tribe* GetPlayerTribe();                                         // 0xbfc5f0
};
NounMgr* NounManager_s00cc_dd70();                                              // 0xb3d300
void* __cdecl GetCurrentGameMode();                                  // 0x00b5b800
struct TerrainCursor                                                 // the hovered terrain cursor
{
    void SetMode(int mode);                                          // 0x00b2fba0 (ret 4)
};
TerrainCursor* __cdecl GetGameTerrainCursor_s00cc_dd70();                       // 0x00b30d70
struct CameraCtl                                                     // SP::cTerrainCameraController
{
    char pad00[0x390];
    u8   mMode390;                                                   // +0x390
    void SetToggle(bool on);                                         // 0x00b0f950 (ret 4)
};
CameraCtl* __cdecl GetCameraCtl_s00cc_dd70();                                   // 0x00b3d280
struct CardPanel                                                     // SP::cUIMissionCardPanel
{
    void SetCardsVisibility(int on);                                 // 0x00e14c10 (ret 4)
};
CardPanel* __cdecl GetCards();                                       // 0x00b3d400
struct TcRefObj                                                      // refcounted helper (+0x5c, +0xc0)
{
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    virtual void Slot8();                                            // +0x08
    virtual void Release3();                                         // +0x0c
    void Reset();                                                    // 0x00d12fc0
};
struct Stopwatch                                                     // EA::Stopwatch at +0xa8
{
    u32 mStart;                                                      // +0x00
    u32 mStop;                                                       // +0x04
    u32 mDelta;                                                      // +0x08
    u32 mPad;                                                        // +0x0c
    void Restart();                                                  // 0x00571e80
};
struct TcTerrain                                                     // the planet view at +0x40
{
    bool TerrainHasKey(u32 key);                                     // 0x00cd4460 (ret 4)
};
struct TcModeObject                                                  // result of view->vt[0x6c]
{
    u32 F00cc93b0(u32 v);                                            // 0x00cc93b0 (ret 4)
    char          pad00[0x50];
    ModeStrategy* mpMode;                                            // +0x50
    u8            mFlag54;                                           // +0x54
};
struct PtrVec2 { void** mBegin; void** mEnd; };
class cSPUITCCCursorStrategy
{
public:
    void RegisterCursors();                                          // 0x00cce610 (PDB candidate: ctor)
    void FUN_00cce5b0();                                             // 0x00cce5b0
    void FUN_00cce5e0();                                             // 0x00cce5e0
    void FUN_00cce940();                                             // 0x00cce940
    void FUN_00ccea10(void* obj, bool flag);                         // 0x00ccea10 (ret 8)
    u32  FUN_00cceae0(void* obj, u32 mode, void* arg3);              // 0x00cceae0 (ret 0xc)
    u32  FUN_00ccebd0(void* obj, int flag, void* arg3);              // 0x00ccebd0 (ret 0xc)
    void FUN_00ccec20(u32 flag);                                     // 0x00ccec20 (ret 4)
    u32  FUN_00cceca0(void* a, void* b);                             // 0x00cceca0 (ret 8)

    char       pad00[0x40];
    TcTerrain* mpTerrain;                                            // +0x40
    void*      mpHandler;                                            // +0x44
    u32        mH48;                                                 // +0x48
    u32        mH4c;                                                 // +0x4c
    u32        mH50;                                                 // +0x50
    u32        mH54;                                                 // +0x54
    u32        mPad58;                                               // +0x58
    TcRefObj*  mpRef5c;                                              // +0x5c
    char       pad60[0xa0 - 0x60];
    u32        mMode;                                                // +0xa0
    char       padA4[0xa8 - 0xa4];
    Stopwatch  mStop;                                                // +0xa8
    char       padB8[0xc0 - 0xb8];
    TcRefObj*  mpRefC0;                                              // +0xc0
};
// ---- items of slice s00ccdd70 end

// ---- items of slice s00ccece0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_allocTag[];                 // 0x013ebc58  "App"
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);   // 0xf473a0
#define VSLOT_s00cc_ece0(n) virtual void vslot##n()
struct cMessageData {
    u32 mData08;                                                          // +0x08
    u32 mData0c;                                                          // +0x0c
    u32 mData10;                                                          // +0x10
    u32 mData14;                                                          // +0x14
    u32 mData18;                                                          // +0x18
    u32 mData1c;                                                          // +0x1c
    u32 mData20;                                                          // +0x20
    u32 mData24;                                                          // +0x24
    u32 mData28;                                                          // +0x28
    u32 mData2c;                                                          // +0x2c
    u32 mMessageID;                                                       // +0x30
    cMessageData(u32 id) : mMessageID(id) {}
};
struct RefBase {                              // vtable 0x013eb90c
    virtual void v0();
    virtual int AddRef();                                                 // +0x04
    virtual int Release();                                                // +0x08
    long rc;                                                              // +0x04
    RefBase() { _InterlockedExchange(&rc, 0); }
};
struct cMessage : cMessageData, RefBase {     // vtable 0x013eb844
    u32 mData34;                                                          // +0x34
    u32 mFlags;                                                           // +0x38
    u32 mData3c;                                                          // +0x3c
    cMessage(u32 id) : cMessageData(id), mFlags(0) {}
};
struct cMessagePtr {
    cMessage* mpMessage;
    cMessagePtr(cMessage* p) : mpMessage(p) { if (p) p->AddRef(); }
    ~cMessagePtr() { mpMessage->Release(); }
    cMessage* operator->() const { return mpMessage; }
};
struct cMessageServer_s00cc_ece0 {
VSLOT_s00cc_ece0(0);
VSLOT_s00cc_ece0(1);
VSLOT_s00cc_ece0(2);
VSLOT_s00cc_ece0(3);
VSLOT_s00cc_ece0(4);
    virtual void SendMSG(u32 id, void* data, void* target);               // +0x14
    virtual void PostMSG(u32 id, cMessage* msg, void* a, void* b);        // +0x18
};
cMessageServer_s00cc_ece0* MessageServer();              // 0x0067dcc0
struct cTribeModeController { bool IsPlacing(); };   // 0x00d09660
namespace SP {
struct cTribeInputStrategy {
    char pad[0x5c];
    cTribeModeController* mpModeController;    // +0x5c

    void RestorePlanner(int param_2);
};  // namespace SP
}
// ---- items of slice s00ccece0 end

// ---- items of slice s00ccefb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VPAD(n) virtual void vpad##n()
struct Vector3_s00cc_efb0 {
    float x, y, z;
    Vector3_s00cc_efb0() {}
    Vector3_s00cc_efb0(const Vector3_s00cc_efb0& o) : x(o.x), y(o.y), z(o.z) {}
    static const Vector3_s00cc_efb0 ZERO;                                          // 0169b1c8
};
bool operator!=(const Vector3_s00cc_efb0& a, const Vector3_s00cc_efb0& b);                    // 0041dd30
struct cGameData {
VPAD(0);
VPAD(1);
VPAD(2);
    virtual void* Cast(uint32_t typeID);                                // +0x0c
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
    virtual uint32_t GetNounID();                                       // +0x20
VPAD(9);
VPAD(10);
VPAD(11);
    virtual uint32_t GetModelKey();                                     // +0x30 (ornament model id)
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
    virtual uint32_t GetPoliticalID();                                  // +0x4c
};
struct cSpatialPart {           // +0x34 / +0xc0 / +0x120 sub-objects
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
    virtual const Vector3_s00cc_efb0& GetPosition();                               // +0x2c
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
    virtual bool IsMoving();                                            // +0x50
    VPAD(21);
    virtual bool IsUnderConstruction();                                 // +0x58 (flag/selectable test)
};
struct cCombatant {             // +0x120 of tools/huts
    float GetHealthPercentage();                                        // 00bfc490
    int GetDamageState();                                               // 008e7f80
};
struct cTimerLike {             // +0x5a8 of a citizen
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
    VPAD(21);
    virtual float GetValue();                                           // +0x58
};
struct cHerdInfo { uint32_t pad[0x1d8 / 4]; uint32_t mBehaviorID; };   // +0x1d8
struct cTribe_s00cc_efb0;
struct cCreatureCitizen : cGameData {
    uint32_t pad04[(0xc0 - 4) / 4];
    cSpatialPart mLocomotive;                                           // +0xc0
    uint32_t pad0c4[(0x5a8 - 0xc4) / 4];
    cTimerLike mTimer;                                                  // +0x5a8
    uint32_t pad5ac[(0x5e0 - 0x5ac) / 4];
    float mThreshold;                                                   // +0x5e0
    uint32_t pad5e4[(0xb4c - 0x5e4) / 4];
    cHerdInfo* mpHerd;                                                  // +0xb4c
    uint32_t padb50[(0xb5c - 0xb50) / 4];
    uint8_t mb5c, mb5d;
    uint8_t mbBusy;                                                     // +0xb5e
    cTribe_s00cc_efb0* GetTribe();                                                 // 00c22f50
    int GetActivity();                                                  // 00c22dc0
};
struct cCreatureAnimal : cGameData {
    uint32_t pad04[(0xc0 - 4) / 4];
    cSpatialPart mLocomotive;                                           // +0xc0
    uint32_t pad0c4[(0xb5c - 0xc4) / 4];
    uint8_t mb5c, mb5d;
    uint8_t mbBusy;                                                     // +0xb5e
    bool IsFlagged();                                                   // 00c0c0e0
};
struct cTribe_s00cc_efb0 : cGameData {
    uint32_t pad04[(0x120 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x120
    uint32_t pad124[(0x20c - 0x124) / 4];
    uint32_t mFood[1];                                                  // +0x20c
    uint32_t pad210[(0x554 - 0x210) / 4];
    uint8_t mb554, mb555;
    uint8_t mbDefeated;                                                 // +0x556
    bool HasToolA();                                                    // 00c8e850
    bool HasToolB();                                                    // 00c8e870
    bool IsRaided();                                                    // 00c8eb90
    bool IsAllied();                                                    // 00b1fbf0
    cCreatureCitizen* GetLeader();                                      // 00c00650
};
struct cFoodStore { float GetAmount(); };                               // 00cee380
struct cTribeTool : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
    uint32_t pad038[(0x120 - 0x38) / 4];
    cCombatant mCombatant;                                              // +0x120
VPAD(20);
VPAD(21);
    virtual int GetToolType();                                          // +0x58
    cTribe_s00cc_efb0* GetTribe();                                                 // 00c9d9e0
};
struct cTribeHut : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
    uint32_t pad038[(0x120 - 0x38) / 4];
    cCombatant mCombatant;                                              // +0x120
VPAD(20);
VPAD(21);
    virtual cTribe_s00cc_efb0* GetTribe();                                         // +0x58
};
struct cTribeFoodMat : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
    uint32_t pad038[(0x10c - 0x38) / 4];
    cTribe_s00cc_efb0* mpTribe;                                                    // +0x10c
};
struct cFruit : cGameData {
    uint32_t pad04[(0x34 - 4) / 4];
    cSpatialPart mSpatial;                                              // +0x34
};
struct cGameBundle : cGameData {
    uint32_t pad04[(0x128 - 4) / 4];
    uint32_t mOwnerID;                                                  // +0x128
};
struct cOrnament : cGameData {
    uint32_t pad04[(0x228 - 4) / 4];
    uint32_t mOrnamentType;                                             // +0x228
};
struct cOrnamentModel { uint32_t pad[0x2c0 / 4]; float mHeight; };    // +0x2c0
void* object_cast(cGameData* p, uint32_t nounID);                       // 00ac80d0
cGameData* ToGameData(cGameData* p);                                    // 00c9f060
struct cPickInfo { uint32_t pad[4]; Vector3_s00cc_efb0 mPosition; };               // +0x10
cPickInfo* GetPickInfo(cGameData* p);                                   // 00c22df0
cTribe_s00cc_efb0* GetTribeByPoliticalID(uint32_t id);                            // 00ac7880
cOrnamentModel* GetOrnamentModel(uint32_t key);                         // 00ac8730
bool CanUseToolA(cGameData* p);                                         // 00dd18b0
bool CanUseToolB(cGameData* p);                                         // 00e09ad0
bool IsCitizenIdle(cCreatureCitizen* p);                                // 00da81f0
enum {
    kGameData = 0x17f243b, kTribeTool = 0x18c8f0c, kGameDataUFO = 0x18ebadc, kCreatureAnimal = 0x18eb45e,
    kCreatureCitizen = 0x18eb4b7, kGameBundle = 0x18c431c, kOrnament = 0x18c88e4, kFruit = 0x2c9cc91,
    kTribeHut = 0x1e4daae, kEgg = 0x2a034cd, kTribeFoodMat = 0x629bafe
};
struct SpatialRef { void* mpObject; };
cCreatureCitizen* ToCitizen(const SpatialRef& r);                       // 00c9f000
struct SpatialVector {          // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
    SpatialRef* mpBegin;
    SpatialRef* mpEnd;
    SpatialRef* mpCapacity;
    uint32_t mAllocator[2];
    ~SpatialVector();                                                   // 00ad92d0
};
template <int N>
struct SpatialFixedVector : SpatialVector {
    uint32_t mHeapFlag;
    SpatialRef mBuffer[N];
    SpatialFixedVector() {
        mHeapFlag = 0;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
    }
};
struct cTribeInputStrategy_s00cc_efb0 {
    uint32_t pad[0x5c / 4];
    cTribeModeController* mpController;                                 // +0x5c
    uint32_t pad60[(0xa0 - 0x60) / 4];
    int mToolMode;                                                      // +0xa0
    uint32_t pada4;
    uint64_t mPendingAction;                                            // +0xa8
};
struct cTribeModeStrategy_s00cc_efb0 {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
VPAD(23);
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
    virtual cTribeInputStrategy_s00cc_efb0* GetInputStrategy();                    // +0x70
    uint32_t pad[(0x390 - 4) / 4];
    int mDifficulty;                                                    // +0x390
    static cTribeModeStrategy_s00cc_efb0* Instance();                              // 00cd40b0 0x00cd40b0
};
struct cGameTerrainCursor {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
VPAD(18);
VPAD(19);
VPAD(20);
VPAD(21);
VPAD(22);
    virtual void GetSelection(SpatialVector& out);                      // +0x5c
VPAD(24);
VPAD(25);
VPAD(26);
VPAD(27);
    virtual int GetSelectionCount();                                    // +0x70
VPAD(29);
VPAD(30);
VPAD(31);
VPAD(32);
VPAD(33);
VPAD(34);
VPAD(35);
VPAD(36);
VPAD(37);
VPAD(38);
VPAD(39);
VPAD(40);
VPAD(41);
    virtual bool IsRectangleSelecting();                                // +0xa8
};
cGameTerrainCursor* GetGameTerrainCursor_s00cc_efb0();                             // 00b30d70
struct IWindow {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
    virtual uint32_t GetControlID();                                    // +0x1c
};
struct IWindowManager {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
VPAD(14);
VPAD(15);
VPAD(16);
VPAD(17);
    virtual IWindow* GetMouseWindow(int);                               // +0x48
};
IWindowManager* WindowManager();                                        // 0067caa0
struct cGameModeState_s00cc_efb0 { uint32_t pad[0x2c / 4]; int mState; };          // +0x2c
cGameModeState_s00cc_efb0* GameModeState();                                        // 00b3d4d0
struct cUIState { char IsMouseOverUI(); };                              // 00b5ca60
cUIState* UIState();                                                    // 00b3d230
struct cListLink { cListLink* mpNext; cListLink* mpPrev; };
struct cTestSystem { uint32_t pad[0x70 / 4]; cListLink mTests; };       // +0x70
extern cTestSystem* sTestSystem;                                        // 015fd928
struct cViewer {
VPAD(0);
VPAD(1);
VPAD(2);
VPAD(3);
VPAD(4);
VPAD(5);
VPAD(6);
VPAD(7);
VPAD(8);
VPAD(9);
VPAD(10);
VPAD(11);
VPAD(12);
VPAD(13);
    virtual Vector3_s00cc_efb0 GetCursorPosition(int, Vector3_s00cc_efb0 offset);             // +0x38
};
cViewer* Viewer();                                                      // 00b3d240
struct cGameNounManager_s00cc_efb0 { cTribe_s00cc_efb0* GetPlayerTribe(); };                  // 00bfc5f0
cGameNounManager_s00cc_efb0* NounManager_s00cc_efb0();                                        // 00b3d300
struct cPlanetModel_s00cc_efb0 {
    int GetRegion(const Vector3_s00cc_efb0& pos);                                  // 00b88590
    bool IsLand(const Vector3_s00cc_efb0& pos);                                    // 00b7e3e0
};
cPlanetModel_s00cc_efb0* PlanetModel_s00cc_efb0();                                            // 00b3d350
struct cRelationshipManager_s00cc_efb0 { int GetRelationship(uint32_t a, uint32_t b, int c); };  // 00d00a70
cRelationshipManager_s00cc_efb0* RelationshipManager();                            // 00b3d2c0
struct cPlayer_s00cc_efb0 { uint32_t GetPoliticalID(); };                          // 00ac79d0
cPlayer_s00cc_efb0* Player();                                                      // 00b3d2b0
void* GetActivePlanet();                                                // 01021260
struct PropertyList;
extern PropertyList* g_TribeProperties;                                 // 0158128c
float GetPropertyFloat(PropertyList* list, uint32_t id, float def);     // 004e1c70
// ---- items of slice s00ccefb0 end

// ---- items of slice s00cd3480 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vt147734c[];    // 0x0147734c
extern void* g_vt1477328[];    // 0x01477328
extern void* g_vt1477318[];    // 0x01477318
extern void* g_vt154df28[];    // 0x0154df28
extern void* g_vt14774b0[];    // 0x014774b0
extern void* g_1581288;        // 0x01581288
extern uint32_t g_169b27c;     // 0x0169b27c
extern const char g_StrTRGMac[];    // 0x01477468
extern const char g_StrTRG[];       // 0x01477458
extern const char g_StrTRGBegin[];  // 0x014774a4
extern const float g_fltOne;        // 0x01485720
extern const float g_fltTwo;        // 0x01470f1c
struct HashNode {
    uint32_t  mKey;     // +0x00
    void*     mValue;   // +0x04
    HashNode* mNext;    // +0x08
};
struct HashIter { HashNode* mNode; void* mBucket; };
struct HashTable {
    void*      mp00;           // +0x00
    HashNode** mppBuckets;     // +0x04
    uint32_t   mnBucketCount;  // +0x08
    uint32_t   mnElementCount; // +0x0c
    void  F_00961d60(HashNode** buckets, uint32_t count);   // 0x961d60
    void  find(HashIter* out, const uint32_t* key);         // 0x645ed0
    void  insert(void* out, void* pair, int flag);          // 0xb6f940
    void** operator[](const uint32_t* key);                 // 0xb6ff20
};
struct SPVector {
    void* mBegin;  // +0x00
    void* mEnd;    // +0x04
    void* mCap;    // +0x08
    void DoInsertPtr(void* pos, void* value);               // 0xaea5d0
};
void*         FUN_00b3d400(void);                            // 0x00b3d400
void*         GetGameInputManager();                         // 0x00b3d250
void*         GetTriggerMgr();                               // 0x00b3d4d0
int           FNV1_String8(const char* s, uint32_t h, int a); // 0x00932e80
unsigned char GetPropertyAsUint32Array(void* a, int b, void* c, void* d); // 0x006a0840
void          WriteUint32(void* s, void* p, int a, int b);   // 0x0093aa70
void*         GetCursorTable();                              // 0x0067cab0
void*         AchievementsController();                      // 0x00675250
struct CActTarget_s00cd_3480 {
    int mA, mB, mC, mD, mE, mF, mG, mH, mI, mJ, mK, mL;  // 0x30 bytes
    void Ctor(void* t);                                            // 0xad7a30 (ret 4)
    void Dtor();                                                   // 0xad7ad0
};
struct CTerrain_s00cd_3480 {
    char pad[0x1150];
    int mCityHallPos[3];                                         // +0x1150
    unsigned char F772c0(int key);       // 0x00c772c0
    void F77300(int a);                  // 0x00c77300
    void F77380(int key, int* out);      // 0x00c77380
    void F77bf0(int a);                  // 0x00c77bf0
    void F79f00(int key, int v);         // 0x00c79f00
};
struct CMgr_s00cd_3480 {
    CTerrain_s00cd_3480* GetCurrentTerrainSphere(); // 0x00f67d90
    void* GetPlayerTribe();              // 0x00bfc5f0
};
struct CActTarget {
    int mA, mB, mC, mD, mE, mF, mG, mH, mI, mJ, mK, mL;  // 0x30 bytes
    CActTarget* Ctor(void* t);                                     // 0xad7a30 (ret 4)
    void Dtor();                                                   // 0xad7ad0
};
struct CTerrain {
    char pad[0x1150];
    int mCityHallPos[3];                                         // +0x1150
    unsigned char HasFlag(int key);       // 0x00c772c0
    void F77300(int a);                  // 0x00c77300
    void F77380(int key, int* out);      // 0x00c77380
    void F77bf0(int a);                  // 0x00c77bf0
    void F79f00(int key, int v);         // 0x00c79f00
};
struct CMgr {
    CTerrain* GetCurrentTerrainSphere(); // 0x00f67d90
    void* GetPlayerTribe();              // 0x00bfc5f0
};
struct CTribe {
    unsigned int GetAdultPopulation();                                    // 0x00c8f370
    void* GetToolOfType(int type);                                        // 0x00c8f6e0
};
struct CProps { unsigned char GetDesc(int id); }; // 0x006a25a0
struct C9630 { void M(); };              // 0x00cc9630
struct LocalInputState {
    char mPad[0x10];                                             // +0x1e0 .. +0x1ef
    void OnMouseDown(int button, float x, float y, int state);   // 0x00697ab0
    void OnMouseUp(int button, float x, float y, int state);     // 0x00697af0
    void OnMouseWheel(float x, float y, int button);             // 0x00697b20
};
struct CTrig {
    void PostAction(int id, void* tgt, void* trigger);            // 0x00ae09b0 (ret 0xc)
    void* PostTrigger(const char* name, int a, int b, int c, int d, int e); // 0x00ae0930 (ret 0x18)
    void SetEnabled(int v);                                      // 0x00adf390
    void ObjectMessage(int id, void* data, void* trigger);        // 0x00adde90 (ret 0xc)
};
struct CPanel {
    unsigned char HasMissionCard(void* card);   // 0x00e15cd0 thiscall ret 4
    void RemoveMissionCard(void* card);          // 0x00e17fb0 thiscall ret 4
    void ExpandMissionCard(void* card);          // 0x00e15b90 thiscall ret 4
    void AddMissionCard(void* card, int a, int b, int c); // 0x00e18200 thiscall ret 0x10
    void SetupMissionCard(void* card, int a, int b, int c); // 0x00e18200 thiscall ret 0x10
};
struct CAch { void F(int a, int b, int c); };   // 0x00676ed0
struct CGameNounMgr { void* CreateNoun(unsigned int id); };       // 0xb20c60
struct CCitizen { void* GetTribe(); };                            // 0xc22f50
struct CMission {
    void* GetTribe();                                             // 0x00c2f680
    void  SetTribe(void* tribe);                                  // 0x00c30270
};
struct Msg3 { int a, b, c; };
struct Msg8 { int a; short b, c; };
struct CursorTable { bool FindLocal(unsigned int id); };          // 0x801bb0
struct TM {
    char pad00[0x14];            // +0x000 .. +0x013
    SPVector mVector;            // +0x014
    char pad20[0x48];            // +0x020 .. +0x067
    void* mp68;                  // +0x068
    void* mp6c;                  // +0x06c
    unsigned char m70;           // +0x070
    char pad71[3];               // +0x071 .. +0x073
    void* mp74;                  // +0x074
    HashTable mTable;            // +0x078 (count @+0x80, elementCount @+0x84)
    float mf88;                  // +0x088
    float mf8c;                  // +0x08c
    int32_t m90;                 // +0x090
    char pad94[0x1e0 - 0x94];    // +0x094 .. +0x1df
    LocalInputState mInput;      // +0x1e0 SP::cLocalInputState
    char pad2[0x3a0 - 0x1f0];    // +0x1f0 .. +0x39f
    unsigned char m3a0;          // +0x3a0

    void M_b6f7d0();
    void M_b6f650(int a, int b);
    void M_b6f760();
    void M_b70070();
    void M_b6f820(void* a);
    void M_b6f4e0(void* a, ...);
    void M_b705a0();
    void M_b70820();

    void F_cd35c0(int a, int b);
    void F_cd3610();
    void F_cd3650();
    void F_cd3670(void* a);
    void F_cd3760(int a);
    TM* F_cd4070(int id);
    void F_cd40f0(void* p);
    unsigned char F_cd4160(void* p);
    void F_cd4180(int a, float f1, float f2, int b);
    void F_cd41d0(float f1, float f2, int a);
    void F_cd4220(int a, float f1, float f2, int b);
    void F_cd43c0(void* a);   // 0x00cd43c0 (TM::F_cd43c0)
    bool F_cd4490();
    unsigned int F_cd4460(int a);
    bool F_cd44a0();
    static bool F_cd44e0(void* a, void* b);
    // PostTerrainAction is a free cdecl function (see below).
    void F_cd3e60();

    // Tribe-mission / strategy members
    unsigned char WriteTribe(void* stream);            // 0x00cd3480
    unsigned char ReadTribe(void* stream);             // 0x00cd3530
    ~TM();                                             // 0x00cd3ab0
    TM();                                              // 0x00cd3b60
    void SetMission(void* a);                          // 0x00cd3bf0
    void StartTribe();                                 // 0x00cd4280
    void RegisterCityHallAndStartCinematic(int* pos);  // 0x00cd43e0
};
void F_cd3f20(uint32_t idx);
void F_cd3fb0(int a);
void F_cd3fd0(int a);
struct ThemeMgr { char pad[0x100]; ThemeMgr(); };
// ---- items of slice s00cd3480 end

// ---- items of slice s00cd9da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gTribeConfigName;                               // 0x0167EA54
extern float    gTribeF0;                                       // 0x01581280
extern uint32_t gTribePropId;                                   // 0x01581288
struct cMotiveTuning;
struct cTribeModeStrategy_s00cd_9da0;
void  cMotiveTuning_Init(cMotiveTuning* t, int hash);           // 0x00B71480
float FUN_00ce68f0(int a);                                      // 0x00CE68F0
void  FUN_00b316d0();                                           // 0x00B316D0
void* GameInputManager_s00cd_9da0();                                       // 0x00B3D250
void* FUN_0067de40();                                           // 0x0067DE40
int   FUN_006ab760(void* /*IMultiLanguage*/, const wchar_t*);   // 0x006AB760
unsigned FNVHash(const char*, unsigned);                        // 0x00932E80
void* FUN_0067ddc0_s00cd_9da0();                                           // 0x0067DDC0
void* ModelManager();                                           // 0x0067DD80
void* FUN_0067de00(int);                                        // 0x0067DE00
void  FUN_00b81720();                                           // 0x00B81720
void* SetGameDataOwner2();                                      // 0x00BFC5F0
void  FUN_00b146a0(void* a, int b, int c, void* d);             // 0x00B146A0
void  FUN_00b10760(void* cam, float a, float b, float c);       // 0x00B10760
void  FUN_00b11870(void* a, int b);                             // 0x00B11870
void  FUN_00b84a60(void* out, int n);                           // 0x00B84A60
void* GetCurrentTerrainSphere();                                // 0x00F67D90
void  FUN_00a1ad10(void* a);                                    // 0x00A1AD10
int   GetPropertyAsUint32Array(void* a, unsigned b, void* c, void* d, void* e); // 0x006A0840
void  FUN_00ff03b0(void* a, int b);                             // 0x00FF03B0
void  FUN_00c79f00(void* a, int b, int c);                      // 0x00C79F00
class cTribeModeStrategy_s00cd_9da0 {
public:
    uint32_t pad_00[0xe8/4];                                    // 0x000..0x0e8
    uint32_t mPosseInfos[0x74/4];                               // 0x0e8..0x15c
    uint32_t pad_15c[0x1490/4 - 0x15c/4];                       // 0x15c..0x1490

    void UpgradePlayerTribe();                                  // 0x00CDA370
};
void FUN_00cd9da0();                                            // 0x00CD9DA0
static void  VC1(void* p, int slot, int a)                { ((void (__thiscall*)(void*, int))(((void**)*(void**)p)[slot/4]))(p, a); }
static void  VC2(void* p, int slot, int a, int b)         { ((void (__thiscall*)(void*, int, int))(((void**)*(void**)p)[slot/4]))(p, a, b); }
static void  VC3(void* p, int slot, int a, int b, int c)  { ((void (__thiscall*)(void*, int, int, int))(((void**)*(void**)p)[slot/4]))(p, a, b, c); }
static void* VC0R(void* p, int slot)                      { return ((void* (__thiscall*)(void*))(((void**)*(void**)p)[slot/4]))(p); }
static void* VC1R(void* p, int slot, int a)               { return ((void* (__thiscall*)(void*, int))(((void**)*(void**)p)[slot/4]))(p, a); }
// ---- items of slice s00cd9da0 end

// ---- items of slice s00cdbb10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_DropFoodAmount_0158133c;
extern const float kFoodEpsilon_01477434;
extern const float kAnimBlend_01486110;
#define VSLOT_s00cd_bb10(n) virtual void _v##n();
struct Vector3_s00cd_bb10 {
    float x, y, z;
    Vector3_s00cd_bb10() {}
    Vector3_s00cd_bb10(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3_s00cd_bb10(const Vector3_s00cd_bb10& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3_s00cd_bb10 operator-(const Vector3_s00cd_bb10& a, const Vector3_s00cd_bb10& b) { return Vector3_s00cd_bb10(a.x - b.x, a.y - b.y, a.z - b.z); }
struct Matrix3_s00cd_bb10 { float m[9]; };
Vector3_s00cd_bb10* normalized_safe(Vector3_s00cd_bb10* out, const Vector3_s00cd_bb10& v);
Matrix3_s00cd_bb10 Matrix3FromFacingAndUp(const Vector3_s00cd_bb10& facing, const Vector3_s00cd_bb10& up);
struct XformMsg_s00cd_bb10 {
    uint16_t flags;
    uint16_t count;
    Vector3_s00cd_bb10  pos;
    float    scale;
    Matrix3_s00cd_bb10  rot;
    XformMsg_s00cd_bb10();
    void SetPosition_00571d40(const Vector3_s00cd_bb10& v);
    void SetRotation(const Matrix3_s00cd_bb10& m) { rot = m; flags |= 2; ++count; }
    void SetScale(float s)             { scale = s; ++count; }
};
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;
    uint16_t mType;
    Variant(void* p);                    // 0x00b19c80
    Variant(const int& v);               // 0x005bf350
    Variant(const uint32_t* key);        // 0x00b19970 (ResourceKey)
    void Destruct(bool reset);           // 0x0093db80
    ~Variant() { if (mFlags & 4) Destruct(false); }
};
struct ResourceKey { uint32_t instance, type, group; };
struct cGameObject {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) VSLOT_s00cd_bb10(10)
    virtual const Vector3_s00cd_bb10& GetPosition();                                   // +0x2c
    VSLOT_s00cd_bb10(12) VSLOT_s00cd_bb10(13) VSLOT_s00cd_bb10(14) VSLOT_s00cd_bb10(15) VSLOT_s00cd_bb10(16) VSLOT_s00cd_bb10(17) VSLOT_s00cd_bb10(18) VSLOT_s00cd_bb10(19) VSLOT_s00cd_bb10(20) VSLOT_s00cd_bb10(21)
    VSLOT_s00cd_bb10(22) VSLOT_s00cd_bb10(23) VSLOT_s00cd_bb10(24) VSLOT_s00cd_bb10(25) VSLOT_s00cd_bb10(26) VSLOT_s00cd_bb10(27) VSLOT_s00cd_bb10(28) VSLOT_s00cd_bb10(29) VSLOT_s00cd_bb10(30) VSLOT_s00cd_bb10(31)
    VSLOT_s00cd_bb10(32) VSLOT_s00cd_bb10(33) VSLOT_s00cd_bb10(34) VSLOT_s00cd_bb10(35) VSLOT_s00cd_bb10(36) VSLOT_s00cd_bb10(37) VSLOT_s00cd_bb10(38) VSLOT_s00cd_bb10(39) VSLOT_s00cd_bb10(40) VSLOT_s00cd_bb10(41)
    VSLOT_s00cd_bb10(42) VSLOT_s00cd_bb10(43) VSLOT_s00cd_bb10(44) VSLOT_s00cd_bb10(45)
    virtual void* Cast(uint32_t typeID);                                     // +0xb8
    virtual int AddRef();                                                    // +0xbc
    virtual int Release();                                                   // +0xc0
};
template <class T> __forceinline T* object_cast_s00cd_bb10(cGameObject* p) { return p ? (T*)p->Cast(T::TYPE) : 0; }
struct cGameObjectPtr {
    cGameObject* mpObject;
    ~cGameObjectPtr() { if (mpObject) mpObject->Release(); }
};
struct sp_vector_allocator {
    uint32_t mData[2];
    void deallocate(void* p) { if (((uint32_t*)p)[-1]) delete[] (char*)p; }
};
template <class T> struct SPVector_s00cd_bb10 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    SPVector_s00cd_bb10() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    static __forceinline void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    __forceinline ~SPVector_s00cd_bb10()
    {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
};
__declspec(align(16)) struct cObjectXform {
    float mData[11];
    cGameObject* mpObject;
    cObjectXform(cGameObject* obj, int flags);
    ~cObjectXform();
};
struct cAnimRequest { uint32_t pad[3]; uint32_t mAnimA; uint32_t mAnimB; };
struct cAnimQueue { cAnimRequest* Play_00bc97f0(int a, int b, float blend, int c); };
struct cAnimatedCreature { uint32_t pad[2]; cAnimQueue mQueue; uint32_t pad2[(0x1d8 - 0xc) / 4]; uint32_t mModelType; };
struct cCreatureSub5a8 {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) VSLOT_s00cd_bb10(10)
    virtual void SetEnabled(int);                                            // +0x2c
};
struct cCreatureBase0 { virtual void _c0(); uint32_t pad[(0x5a8 - 4) / 4]; };
struct cCreature : cCreatureBase0, cCreatureSub5a8 {
    enum { TYPE = 0x4f176642 };
    uint32_t pad5ac[(0xb4c - 0x5ac) / 4];
    cAnimatedCreature* mpAnimatedCreature;                                   // +0xb4c
    bool IsIdle_00c24560();
    void f_00c26d10();
    void f_00c0b950();
    void f_00c0ba10();
};
void FUN_00c0d3a0(cCreature* c);
struct cTerrainCursor {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) VSLOT_s00cd_bb10(10)
    VSLOT_s00cd_bb10(11) VSLOT_s00cd_bb10(12) VSLOT_s00cd_bb10(13) VSLOT_s00cd_bb10(14) VSLOT_s00cd_bb10(15) VSLOT_s00cd_bb10(16) VSLOT_s00cd_bb10(17) VSLOT_s00cd_bb10(18) VSLOT_s00cd_bb10(19) VSLOT_s00cd_bb10(20)
    VSLOT_s00cd_bb10(21)
    virtual void SetSelectionTarget(uint32_t target);                        // +0x58
    virtual void GetSelection(SPVector_s00cd_bb10<cGameObjectPtr>& out);                // +0x5c
};
cTerrainCursor* GetGameTerrainCursor_s00cd_bb10();                                      // 0x00b30d70
struct cAudioSystem { VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) virtual int GetState(); };
cAudioSystem* GetAudioSystem();                                              // 0x00a206f0
void KillSetiEffects(uint32_t id, int state);                                // 0x00435ed0
int GetRecorderState();                                                      // 0x00435e90
struct cPlanetRecord_s00cd_bb10 { uint32_t pad[0x504 / 4]; uint32_t mData504; };
struct cHutBase0 { virtual void _h0(); uint32_t pad[12]; };
struct cHut : cHutBase0, cGameObject {};
struct cTribe_s00cd_bb10 {
    virtual int AddRef();                                                    // +0x00
    virtual int Release();                                                   // +0x04
    VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) VSLOT_s00cd_bb10(10)
    VSLOT_s00cd_bb10(11) VSLOT_s00cd_bb10(12) VSLOT_s00cd_bb10(13) VSLOT_s00cd_bb10(14) VSLOT_s00cd_bb10(15) VSLOT_s00cd_bb10(16) VSLOT_s00cd_bb10(17) VSLOT_s00cd_bb10(18) VSLOT_s00cd_bb10(19) VSLOT_s00cd_bb10(20)
    VSLOT_s00cd_bb10(21) VSLOT_s00cd_bb10(22) VSLOT_s00cd_bb10(23) VSLOT_s00cd_bb10(24)
    virtual const Vector3_s00cd_bb10& GetPosition();                                    // +0x64
    VSLOT_s00cd_bb10(26) VSLOT_s00cd_bb10(27) VSLOT_s00cd_bb10(28) VSLOT_s00cd_bb10(29) VSLOT_s00cd_bb10(30) VSLOT_s00cd_bb10(31) VSLOT_s00cd_bb10(32) VSLOT_s00cd_bb10(33) VSLOT_s00cd_bb10(34) VSLOT_s00cd_bb10(35)
    VSLOT_s00cd_bb10(36)
    virtual uint32_t GetSelectedThing();                                     // +0x94
    VSLOT_s00cd_bb10(38) VSLOT_s00cd_bb10(39) VSLOT_s00cd_bb10(40)
    virtual int GetFoodAmount();                                             // +0xa4
    VSLOT_s00cd_bb10(42)
    virtual cHut* GetTribeHut();                                             // +0xac

    uint32_t pad04[(0x120 - 4) / 4];
    cGameObject mObject120;                                                  // +0x120
    uint32_t pad124[(0x20c - 0x124) / 4];
    uint32_t mTimer20c[9];                                                   // +0x20c
    struct Sub230 { uint32_t mData0; uint32_t mData4; } mSub230;            // +0x230
    Sub230* GetSub230() { return &mSub230; }

    cPlanetRecord_s00cd_bb10* GetRecord_00c8e820(int index);
    bool GetSpawnInfo_00c8eb50(ResourceKey* out);
    cHut* GetToolOfType(int type);                                           // 0x00c8f6e0
    cCreature* GetChieftain();                                               // 0x00c8fd30
    uint32_t GetPopulation_00c8f3a0();
    uint32_t GetMaxPopulation();                                             // 0x00c8eae0
    void AddFood_00c94b50(float amount);
};
struct ISimBase {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6)
    virtual void v7();                                                       // +0x1c
};
struct ISimTicker {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9)
    VSLOT_s00cd_bb10(10) VSLOT_s00cd_bb10(11) VSLOT_s00cd_bb10(12) VSLOT_s00cd_bb10(13) VSLOT_s00cd_bb10(14) VSLOT_s00cd_bb10(15) VSLOT_s00cd_bb10(16) VSLOT_s00cd_bb10(17) VSLOT_s00cd_bb10(18) VSLOT_s00cd_bb10(19)
    virtual void v20(void* obj);                                             // +0x50
};
struct IStrategyVtbl {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9)
    VSLOT_s00cd_bb10(10) VSLOT_s00cd_bb10(11) VSLOT_s00cd_bb10(12) VSLOT_s00cd_bb10(13) VSLOT_s00cd_bb10(14) VSLOT_s00cd_bb10(15) VSLOT_s00cd_bb10(16) VSLOT_s00cd_bb10(17) VSLOT_s00cd_bb10(18) VSLOT_s00cd_bb10(19)
    VSLOT_s00cd_bb10(20)
    virtual void DispatchTribe(cTribe_s00cd_bb10* tribe);                               // +0x54
};
namespace Simulator {
class SimSingleton100 {                                                      // 0x100-byte simulator singleton
public:
    SimSingleton100();                                                       // 0x00cc5a70
    char mData[0x100];
};
}
class cCitySimulator_s00cd_bb10 {
public:
    cCitySimulator_s00cd_bb10();                                                        // 0x00ae6a70
    void AttachSubsystems();                                                 // 0x00ae7350
    char mData[0x40];
};
void* operator new(size_t, const char*, int, int, int, int);                 // 0x00f473a0
extern Simulator::SimSingleton100* g_pSimSingleton_0169b054;                 // 0x0169b054
extern cCitySimulator_s00cd_bb10*             g_pCitySimulator_0167a690;               // 0x0167a690
ISimBase* FUN_00d51660_s00cd_bb10();                                                    // 0x00d51660
struct cTerrainSphere_s00cd_bb10 {
    uint32_t pad[0x10f0 / 4];
    float mf10f0;
    float mf10f4;
    uint32_t mKey10f8;
    uint32_t pad10fc[2];
    uint32_t mResult1104;                                                    // +0x1104
    int GetState_00c75420();
};
struct NounVector {
    cTribe_s00cd_bb10** mpBegin;                                                        // +0x00
    cTribe_s00cd_bb10** mpEnd;                                                          // +0x04
    cTribe_s00cd_bb10** mpCapacity;                                                     // +0x08
};
struct NounManagerData {
    void*       mpUnused;                                                    // +0x00
    NounVector  mVector;                                                     // +0x04
};
struct cGameNounManager_s00cd_bb10 {
    cTerrainSphere_s00cd_bb10* GetCurrentTerrainSphere();                               // 0x00f67d90
    cTribe_s00cd_bb10* GetPlayerTribe();                                                // 0x00bfc5f0
    NounManagerData* GetGameDataVector(uint32_t, uint32_t, uint32_t,
                                       uint32_t, uint32_t);                  // 0x00b21340
};
cTribe_s00cd_bb10* FindClosestNPC(NounVector* vec, uint32_t param,
                       bool (__cdecl* filter)(cTribe_s00cd_bb10*));                     // 0x00cd5810
cGameNounManager_s00cd_bb10* NounManager_s00cd_bb10();                                             // 0x00b3d300
class cUIHints_s00cd_bb10 { public:
    void UpdateHints(int a, int b);                                          // 0x0067c350
    void ShowHint_0067c830(uint32_t id);
};
cUIHints_s00cd_bb10* UIHints();                                                         // 0x0067cac0
struct cHintsB { void Set_0060d860(uint32_t id, ResourceKey* key); };
cHintsB* GetHintsB();                                                        // 0x0067cb30
struct cLayoutScripts {
    void SetObject_00ae09b0(uint32_t id, const cObjectXform& obj);
    void Run_00ae0930(const char* name, int a, int b, int c, int d, int e);
    void Reset_00adf390(int a);
};
cLayoutScripts* LayoutScripts();                                             // 0x00b3d4d0
struct cFoodSource { float Consume_00ac7d10(float amount, void* timer, int flags); };
cFoodSource* GetFoodSource();                                                // 0x00b3d2b0
struct cTerrainSource {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) VSLOT_s00cd_bb10(10)
    VSLOT_s00cd_bb10(11) VSLOT_s00cd_bb10(12)
    virtual void* GetTerrainObject();                                        // +0x34
    VSLOT_s00cd_bb10(14)
    virtual void GetKey(ResourceKey* out, int flags);                        // +0x3c
};
cTerrainSource* GetTerrainSource();                                          // 0x00b3d240
struct cPropertyList_s00cd_bb10 {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7)
    virtual void SetValue(int index, const Variant& v);                      // +0x20
};
struct cPropListFactory {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5)
    virtual void Create(cPropertyList_s00cd_bb10** out);                                // +0x18
    VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) VSLOT_s00cd_bb10(10) VSLOT_s00cd_bb10(11) VSLOT_s00cd_bb10(12) VSLOT_s00cd_bb10(13) VSLOT_s00cd_bb10(14) VSLOT_s00cd_bb10(15) VSLOT_s00cd_bb10(16)
    VSLOT_s00cd_bb10(17) VSLOT_s00cd_bb10(18) VSLOT_s00cd_bb10(19) VSLOT_s00cd_bb10(20)
    virtual void Submit(uint32_t id, cPropertyList_s00cd_bb10* list, int flags);        // +0x54
};
cPropListFactory* PropListFactory();                                         // 0x006895b0
struct cMessage_s00cd_bb10 {
    VSLOT_s00cd_bb10(0)
    virtual int AddRef();                                                    // +0x04
    virtual int Release();                                                   // +0x08
    uint32_t pad04;
    uint32_t mData08;                                                        // +0x08
    uint32_t pad0c[(0x30 - 0xc) / 4];
    uint32_t mMessageID;                                                     // +0x30
    uint32_t pad34[3];
    cMessage_s00cd_bb10(int a);                                                         // 0x00421c80
    void* operator new(size_t n, const char* name, int a, int b, int c, int d);
};
struct cMessagePtr_s00cd_bb10 {
    cMessage_s00cd_bb10* mpMessage;
    cMessagePtr_s00cd_bb10(cMessage_s00cd_bb10* p);                                                // 0x0061df40
    ~cMessagePtr_s00cd_bb10() { mpMessage->Release(); }
    cMessage_s00cd_bb10* operator->() const { return mpMessage; }
};
struct cMessageServer_s00cd_bb10 {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4)
    virtual void SendMSG(uint32_t id, void* data, void* target);             // +0x14
    virtual void PostMSG(uint32_t id, cMessage_s00cd_bb10* msg, void* a, void* b);      // +0x18
};
cMessageServer_s00cd_bb10* MessageServer_s00cd_bb10();                                             // 0x0067dcc0
struct IVisualEffect {
    VSLOT_s00cd_bb10(0)
    virtual int Release();                                                   // +0x04
    virtual void Start(int flags);                                           // +0x08
    VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5)
    virtual void SetTransform(const XformMsg_s00cd_bb10& xf);                           // +0x18
};
template <class T> struct AutoRefCount_s00cd_bb10 {
    T* mpObject;
    AutoRefCount_s00cd_bb10() : mpObject(0) {}
    ~AutoRefCount_s00cd_bb10() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam();                                                     // 0x00a16f40
    T* operator->() const { return mpObject; }
};
struct cEffectsManager_s00cd_bb10 {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) VSLOT_s00cd_bb10(10)
    virtual bool CreateVisualEffect(uint32_t id, int flags, IVisualEffect** out);  // +0x2c
};
cEffectsManager_s00cd_bb10* EffectsManager();                                           // 0x0067ddd0
struct InsertResult { void* node; void* bucket; bool second; };
struct uint_hash_set {
    InsertResult insert_00675b60(const uint32_t& key);
    void clear();                                                            // 0x00675770
};
struct cAchievementData { uint32_t pad[0x60 / 4]; uint_hash_set mVisited; };
struct cAchievementsController {
    bool IsLocked_006766f0(uint32_t id);
    void AwardAchievement(uint32_t id);                                      // 0x00676710
    cAchievementData* GetData_00675370();
    bool Has_00675e80(uint32_t id);
    void AutoTest(uint32_t id, uint32_t value);                              // 0x00676e90
};
cAchievementsController* AchievementsController_s00cd_bb10();                           // 0x00675250
struct cTribeCamera { void PlayIntro_00cd52e0(int kind, Vector3_s00cd_bb10 pos); };
extern cTribeCamera* g_TribeCamera_0169b2c8;
extern Vector3_s00cd_bb10 g_TribeCameraPos_0169b2cc;
struct cTribePlanner_s00cd_bb10 {
    void f_00cc8aa0(int);
    void f_00cc93b0(int);
};
struct cToggleable { VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2) VSLOT_s00cd_bb10(3) VSLOT_s00cd_bb10(4) VSLOT_s00cd_bb10(5) VSLOT_s00cd_bb10(6) VSLOT_s00cd_bb10(7) VSLOT_s00cd_bb10(8) VSLOT_s00cd_bb10(9) virtual void SetActive(int); };
bool IsVerbTrayCommand_00d49820(int cmd);
bool VerbTray_HandleRebuild(void* window, uint32_t data);                    // 0x00d4a570
void sToggleMinimap();                                                       // 0x00cd5200
int GetTribeOutcome_00cdba50();
void PlayEndSequence_00e398e0(uint32_t id, uint32_t* record, ResourceKey* pos, ResourceKey* dir, uint32_t data, int b, int c);
bool IsValidKey_006419f0(ResourceKey* key);
void SummarizeVehicle_00555f70(ResourceKey* key, uint32_t data);
struct UTFWinMessage {
    uint32_t pad[2];
    uint32_t mEventType;                                                     // +0x08
    int mCommandID;                                                          // +0x0c
    uint32_t pad10[2];
    uint32_t mData18;                                                        // +0x18
};
struct IWinProc {
    VSLOT_s00cd_bb10(0) VSLOT_s00cd_bb10(1) VSLOT_s00cd_bb10(2)
    virtual bool HandleUIMessage(void* window, const UTFWinMessage& message) = 0;
};
struct cStrategyBase0 { virtual void _s0(); };
namespace SP {
class cTribeModeStrategy_s00cd_bb10 : public cStrategyBase0, public IWinProc {
public:
    // offsets below are absolute (subobject IWinProc at +4)
    uint32_t pad08[(0x78 - 8) / 4];
    uint32_t mData78;                                                        // +0x78  (IWinProc +0x74)
    uint32_t pad7c[(0x1a8 - 0x7c) / 4];
    struct Timer { uint32_t d[8]; void Stop(); } mTimer;                    // +0x1a8  (IWinProc +0x1a4)
    uint32_t pad1c8[(0x240 - 0x1c8) / 4];
    cTribePlanner_s00cd_bb10* mpPlanner;                                                // +0x240  (IWinProc +0x23c)
    uint32_t pad244[(0x390 - 0x244) / 4];
    int mToolMode;                                                           // +0x390  (IWinProc +0x38c)
    cToggleable* mpToolUI;                                                   // +0x394  (IWinProc +0x390)
    uint32_t pad398[2];
    uint8_t pad3a0[3];
    bool mbFlag3a3;                                                          // +0x3a3  (IWinProc +0x39f)

    void SetMode_00cd6390(int);
    bool IsToolActive_00cd4460(uint32_t id);
    bool HandleUIMessage(void* window, const UTFWinMessage& message);
    int FUN_00cdbb10();
    cHut* FindClosestNPCHut(uint32_t param);  // 0x00cdbcc0 (cTribeModeStrategy::FindClosestNPCHut)
};
}
namespace SP {
ISimTicker* SimTicker_s00cd_bb10();                                                     // 0x00b3d330
}
namespace SP {
bool IsNonEmptyNPCTribe(cTribe_s00cd_bb10* tribe);                                      // 0x00cd40c0
}
using SP::cTribeModeStrategy_s00cd_bb10;
static __forceinline int GetAudioState()
{
    cAudioSystem* audio = GetAudioSystem();
    return audio ? audio->GetState() : 0;
}
// ---- items of slice s00cdbb10 end

// ---- items of slice s00cdc8b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CvgRec {                                        // 0x1c-byte timeline record
    uint32_t mX;                                       // +0x00
    uint32_t mY;                                       // +0x04
    uint32_t mZ;                                       // +0x08
    uint32_t mPad0c;                                   // +0x0c
    float    mF10;                                     // +0x10 (only set for list entries)
    void*    mHandle;                                  // +0x14
    uint32_t mId;                                      // +0x18
};
struct CvgVec {                                        // begin/end of the 0x1c-stride vector
    CvgRec* mpBegin;                                   // +0x00
    CvgRec* mpEnd;                                     // +0x04
    void InsertRange(CvgRec* first, CvgRec* last);     // 0x00cdb190
    void Append();                                     // 0x00cdb430
};
struct CvgObj {
    void**   mpVtbl;                                   // +0x000
    char     mPad04[0x300];                            // +0x004
    CvgVec   mTargets;                                 // +0x304
    char     mPad30c[0x814];                           // +0x30c
    uint32_t mB20;                                     // +0xb20
    char     mPadB24[0x14];                            // +0xb24
    uint32_t mB38;                                     // +0xb38
    uint32_t mB3c;                                     // +0xb3c
    uint32_t mB40;                                     // +0xb40
};
struct PtrVec_s00cd_c8b0 {
    void** mpBegin;                                    // +0x00
    void** mpEnd;                                      // +0x04
};
void* __fastcall FUN_00c0c1a0(CvgObj* o);                                                // 0x00c0c1a0
typedef float (__fastcall* CvgSlot80)(CvgObj* o, int unused, int arg);
static void cvg_swap(CvgRec* r, CvgObj* o)
{
    uint32_t t0 = r->mX;
    r->mX = o->mB38;
    o->mB38 = t0;
    uint32_t t1 = r->mY;
    r->mY = o->mB3c;
    o->mB3c = t1;
    uint32_t t2 = r->mZ;
    r->mZ = o->mB40;
    o->mB40 = t2;
}
// ---- items of slice s00cdc8b0 end

// ---- items of slice s00cd6800 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTimer_s00cd_6800 {
    void Restart();                         // 0x00bc3130
};
struct cGameTimeManager_s00cd_6800 {
    void DecPauseGate(u32 id);              // 0x00b32250
};
struct cGameInputManager_s00cd_6800 {
    u8  mPad000[0x110];
    int mField110;                          // 0x110
};
struct cCameraCtl {
    u8   mPad000[0x390];
    bool mFlag390;                          // 0x390
};
struct cConfigManager_s00cd_6800 {
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
    virtual void SetConfigU32(u32 id, char value);  // +0x2c
    virtual u32  GetConfigU32(u32 id);              // +0x30
};
struct cUIHints_s00cd_6800 {
    void UpdateHints(u32 id);               // 0x0067c830
};
struct cUIWindow {
    void FUN_00e2f270();                    // 0x00e2f270
};
struct cModeObject {
    u8       mPad000[4];                    // 0x00 vtable
    void F_cd6390(unsigned char enable);    // 0x00cd6390
    u8       mPad004[0x1a8 - 4];
    cSPTimer_s00cd_6800 mTimer;                        // 0x1a8
};
extern "C" cGameTimeManager_s00cd_6800*   GameTimeManager_s00cd_6800();          // 0x00b3d380
extern "C" cGameInputManager_s00cd_6800*  GameInputManager_s00cd_6800();         // 0x00b3d250
extern "C" cCameraCtl*         GetCameraCtl_s00cd_6800();             // 0x00b3d280
extern "C" cConfigManager_s00cd_6800*     ConfigManager();            // 0x0067dd30
extern "C" cUIHints_s00cd_6800*           FUN_0067cac0_s00cd_6800();             // 0x0067cac0
extern "C" cUIWindow* __stdcall FUN_00b3d4f0_s00cd_6800(int flag);    // 0x00b3d4f0
extern "C" cModeObject*        DAT_0169b2c8;               // 0x0169b2c8
// ---- items of slice s00cd6800 end

// ---- items of slice s00cd68d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cRefObj_s00cd_68d0 {           // the slice's view of the +0x250/+0x398 object (slot +0xc = ReleaseWith)
    virtual void v00();                 // 0x00
    virtual void Release();             // 0x04
    virtual void v02();                 // 0x08
    virtual void ReleaseWith(int flags); // 0x0c
};
struct cHintMgr {
    void Shutdown();                    // 0x0067a120
};
struct cAimSource {
    void Stop(int);                     // 0x00b33ce0
    void Clear(int);                    // 0x00b33cf0
};
extern "C" cCameraCtl*  GetCameraCtl_s00cd_68d0();     // 0x00b3d280
extern "C" cAimSource*  GetAimSource();     // 0x00b3d240
// ---- items of slice s00cd68d0 end

// ---- items of slice s00cd6980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned char g_0157f174[];
extern "C" unsigned char g_0157f184[];
namespace Simulator {
struct ResourceKey_s00cd_6980 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
}
namespace Simulator {
extern ResourceKey_s00cd_6980 g_hintKeys[3];                            // 0x0157f138 (12 bytes each)
}
namespace Simulator {
extern const float g_hintOffset;                             // 0x013eb1bc
}
namespace Simulator {
struct cTerrainSphere_s00cd6980 {
    bool __thiscall Contains(uint32_t key);                  // 0x00c772c0
    void __thiscall Remove(uint32_t key);                    // 0x00c77300
    bool __thiscall HasFlagOrInsert(uint32_t key);           // 0x00c77bf0
};
}
namespace Simulator {
struct cNounManager_s00cd6980 {
    cTerrainSphere_s00cd6980* __thiscall GetCurrentTerrainSphere(); // 0x00f67d90
};
}
namespace Simulator {
struct cGameTimeManager_s00cd6980 {
    void __thiscall IncPauseGate(uint32_t timer);            // 0x00b32220
    void __thiscall DecPauseGate(uint32_t timer);            // 0x00b32250
    bool __thiscall IsPaused();                              // 0x00cce590 (ecx = manager)
};
}
namespace Simulator {
struct cGameInputManager_s00cd6980 {
    uint8_t pad000[0x110];                                   // +0x000
    int32_t m110;                                            // +0x110
};
}
namespace Simulator {
struct cRelationsStrip_s00cd6980 {
    void __thiscall Reset();                                 // 0x00e2f270
};
}
namespace Simulator {
struct cCameraCtl_s00cd6980 {
    uint8_t pad000[0x390];                                   // +0x000
    uint8_t m390;                                            // +0x390
};
}
namespace Simulator {
struct cMissionMgr_s00cd6980 {
    uint32_t __thiscall HintClear(uint32_t hint);            // 0x00b707a0
};
}
namespace Simulator {
struct cHintManager_s00cd6980 {
    void __thiscall ShowHint(ResourceKey_s00cd_6980 key, void* handler, int a,
                             float x, float y, float z, int b, int c); // 0x0067aaf0
};
}
namespace Simulator {
struct cResourceFinder_s00cd6980 {
    virtual void v00();                                      // +0x00
    virtual void v01();                                      // +0x04
    virtual void v02();                                      // +0x08
    virtual void v03();                                      // +0x0c
    virtual void v04();                                      // +0x10
    virtual void v05();                                      // +0x14
    virtual void v06();                                      // +0x18
    virtual void v07();                                      // +0x1c
    virtual void v08();                                      // +0x20
    virtual void v09();                                      // +0x24
    virtual void v10();                                      // +0x28
    virtual void v11();                                      // +0x2c
    virtual void* Find(uint32_t id);                         // +0x30
};
}
Simulator::cNounManager_s00cd6980*      __cdecl NounManager_s00cd_6980();      // 0x00b3d300
Simulator::cGameTimeManager_s00cd6980*  __cdecl GameTimeManager_s00cd_6980();  // 0x00b3d380
Simulator::cGameInputManager_s00cd6980* __cdecl GameInputManager_s00cd_6980(); // 0x00b3d250
Simulator::cCameraCtl_s00cd6980* __cdecl GetCameraCtl_s00cd_6980();     // 0x00b3d280
Simulator::cResourceFinder_s00cd6980* __cdecl Function_0067dd30(); // 0x0067dd30
Simulator::cRelationsStrip_s00cd6980* __stdcall Function_00b3d4f0(int); // 0x00b3d4f0
Simulator::cHintManager_s00cd6980* __cdecl GetHintManager();  // 0x0067caf0
void __cdecl Function_00cd3fb0(int eventHash);               // 0x00cd3fb0
void __cdecl Function_00cd3fd0(int eventHash);               // 0x00cd3fd0
struct cTribeModeStrategy_s00cd6980 {
    uint8_t pad000[0x1a4];                                   // +0x000
    uint8_t m1a4;                                            // +0x1a4
    uint8_t pad1a5[0x394 - 0x1a5];                           // +0x1a5
    Simulator::cMissionMgr_s00cd6980* mp394;                 // +0x394

    bool __thiscall HasEvent(uint32_t eventHash);            // 0x00cd4460
    void __thiscall RaiseEvent(uint32_t eventHash);          // 0x00cd6980
    void __thiscall Notify(uint32_t eventHash);              // 0x00cd6130
};
// ---- items of slice s00cd6980 end

// ---- items of slice s00cd6e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct TribeObjectNode {
    unsigned int mKey;
    void* mValue;
    TribeObjectNode* mpNext;
};
}
namespace SP {
struct TribeObjectIterator {
    TribeObjectNode* mpNode;
    TribeObjectNode** mpBucket;
};
}
namespace SP {
struct TribeObjectTable {
    void* mpPolicy;
    TribeObjectNode** mpBuckets;
    unsigned int mnBucketCount;
    unsigned int mnElementCount;
    TribeObjectIterator* find(TribeObjectIterator* result, const unsigned int* key); // 0x00645ed0 (returns its argument)
    TribeObjectNode* End() { return mpBuckets[mnBucketCount]; }      // s00cd6ef0: the end sentinel
};
}
// ---- items of slice s00cd6e40 end

// ---- items of slice s00cd6ef0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gTribeStrategyProperties; // 0x01581288
unsigned char __cdecl GetTribeProperty(void* object, int property, unsigned char defaultValue); // 0x0064f350
namespace SP {
struct TribeObjectTable_s00cd_6ef0 {
    void* mpPolicy;
    TribeObjectNode** mpBuckets;
    unsigned int mnBucketCount;
    unsigned int mnElementCount;
    TribeObjectIterator* find(TribeObjectIterator* result, const unsigned int* key); // 0x00645ed0
    TribeObjectNode* End() { return mpBuckets[mnBucketCount]; }
};
}

// ---- items of slice s00cd6ef0 end

// ---- items of slice s00cd6f60 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace IO {
class IStream_s00cd_6f60;
}
}
namespace EA {
namespace IO {
bool __cdecl WriteUint32(IStream_s00cd_6f60*, const unsigned int*, int, int); // 0x0093aa70
}
}
// ---- items of slice s00cd6f60 end

// ---- items of slice s00cd7100 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTribeModeStrategy_s00cd_7100 {
    bool Has(int id);                       // 0x00cd6ef0
};
struct cEventLog_s00cd_7100 {
    void PostFeedbackEvent(u32 event, u32 category, int a, int b, int c, int d);  // 0x00dd8640
};
extern cTribeModeStrategy_s00cd_7100* gTribeModeStrategy_0169b2c8;   // 0x0169b2c8
cEventLog_s00cd_7100* EventLog_00b3d3e0_s00cd_7100();                           // 0x00b3d3e0
// ---- items of slice s00cd7100 end

// ---- items of slice s00cd7530 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTerrainSphere_s00cd_7530 {
    bool Contains(uint32_t key);                                 // 0x00c772c0
};
struct cGameNounManager_s00cd_7530 {
    cTerrainSphere_s00cd_7530* GetCurrentTerrainSphere();                   // 0x00f67d90
};
cGameNounManager_s00cd_7530* NounManager_s00cd_7530();                                 // 0x00b3d300
struct cGameInputManager_s00cd_7530 {
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
    virtual void OnMouseWheel(int delta, float x, float y, int flags);   // +0x60
};
cGameInputManager_s00cd_7530* GameInputManager_s00cd_7530();                           // 0x00b3d250
// ---- items of slice s00cd7530 end

// ---- items of slice s00cd7d90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char VT_1477668[];
extern char VT_1477648[];
extern char VT_1477640[];
extern char VT_14775f0[];
extern char VT_14775e8[];
extern char VT_13eb938[];
extern char VT_13eb394[];
void __cdecl operator_delete_00f47380(void* p);
void __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e);
inline void Release1(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[1])(p);
}
inline void Release2(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[2])(p);
}
struct cGonzagoTimer {
    uint32_t m[8];                      // 0x20 bytes
    void dtor_00b638b0();
};
struct Obj40 {
    uint32_t m[6];
    void dtor_00cd57d0();
};
struct Obj94 {
    uint32_t m[5];
    void dtor_00ae6970();
};
struct Obj0c {
    uint32_t m[0x34 / 4];
    void dtor_00b5b9a0();
};
struct PoolContainer {
    uint32_t m00;                       // +0x00
    void*    mpBegin;                   // +0x04
    uint32_t mCapacity;                 // +0x08
    uint32_t mSize;                     // +0x0c
    uint32_t mPad10[3];                 // +0x10..+0x1b
    void*    mpFreeList;                // +0x1c
    uint32_t mPad20;                    // +0x20
    void*    mpPoolBegin;               // +0x24
    void*    mpPoolEnd;                 // +0x28
    uint32_t mPad2c;                    // +0x2c
    void*    mpInline;                  // +0x30
    uint32_t mPad34[0xbc / 4];          // +0x34..+0xef

    void DestroyRange_00a1b6c0(void* first, uint32_t capacity);
};
struct Vector2c {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void DestroyRange_01023030(void* first, void* last);
};
struct Vector304 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void DestroyRange_00cd6fd0(void* first, void* last);
};
// ---- items of slice s00cd7d90 end

// @ 0x00cceae0
u32 cSPUITCCCursorStrategy::FUN_00cceae0(void* obj, u32 mode, void* arg3)
{
    bool flag = false;
    switch (mode) {
    case 0:
        flag = true;
        break;
    case 1:
        GetGameTerrainCursor_s00cc_dd70()->SetMode(2);
        break;
    case 2:
        GetGameTerrainCursor_s00cc_dd70()->SetMode(0);
        break;
    case 3:
        GetGameTerrainCursor_s00cc_dd70()->SetMode(1);
        break;
    }
    if (!mpTerrain->TerrainHasKey(0x56d1871)) {
        if (mpTerrain->TerrainHasKey(0x64be5ff)) {
            void* tribe = NounManager_s00cc_dd70()->GetPlayerTribe();
            if (tribe) {
                PtrVec2* v = (PtrVec2*)V0<void*>(tribe, 0x94);
                u32 n = (u32)(v->mEnd - v->mBegin);
                for (u32 i = 0; i < n; ++i)
                    V1<void>(v->mBegin[i], 0x54, 0);
            }
        }
    }
    TerrainCursor* cur = GetGameTerrainCursor_s00cc_dd70();
    void* v = obj ? V1<void*>(obj, 0xc, (void*)0x1186577) : 0;
    V2<void>(cur, 0xa0, flag, v);
    return 0;
}

// @ 0x00ccec20
void cSPUITCCCursorStrategy::FUN_00ccec20(u32 flag)
{    if (GetCurrentGameMode() != (void*)0x1654c02)
        return;
    TcModeObject* mode = (TcModeObject*)V0<void*>(mpTerrain, 0x6c);
    mode->F00cc93b0(flag);
    if (GetCards())
        GetCards()->SetCardsVisibility((int)flag);
    if (mode->mpMode) {
        if ((u8)flag != 0) {
            if (mode->mFlag54)
                mode->mpMode->SetFlag(1);
        } else {
            mode->mFlag54 = mode->mpMode->GetFlag();
            mode->mpMode->SetFlag(0);
        }
    }
}

// @ 0x00cceca0
u32 cSPUITCCCursorStrategy::FUN_00cceca0(void* a, void* b)
{
    CameraCtl* cam = GetCameraCtl_s00cc_dd70();
    if (cam == 0)
        return 0;
    if ((mStop.mStart | mStop.mStop) != 0) {
        cam->SetToggle(true);
        return 0;
    }
    cam->SetToggle(false);
    return 0;
}

// @ 0x00ccef10
namespace SP {
void cTribeInputStrategy::RestorePlanner(int param_2)
{
    cTribeModeController* c = mpModeController;
    if (!c)
        return;
    if (c->IsPlacing())
        return;
    if (param_2 == -1)
        return;
    cMessagePtr msg(new (g_allocTag, 0, 0, 0, 0) cMessage(0));
    msg->mMessageID = 0xb2699146;
    msg->mData08 = param_2;
    MessageServer()->PostMSG(msg->mMessageID, msg.mpMessage, 0, 0);
}
}  // namespace SP

// @ 0x00ccefb0
int GetTribeCursorID(cGameData* pObject, const Vector3_s00cc_efb0* pPickPos)
{
    cTribeInputStrategy_s00cc_efb0* input = cTribeModeStrategy_s00cc_efb0::Instance()->GetInputStrategy();
    if (!input)
        return 0;

    int modeState = GameModeState()->mState;
    if (modeState == 1 || modeState == 2)
        return 2;

    if (UIState()->IsMouseOverUI() == 1 &&
        (!sTestSystem || sTestSystem->mTests.mpNext == &sTestSystem->mTests)) {
        IWindow* window = WindowManager()->GetMouseWindow(1);
        if (!window)
            return 0;
        if (window->GetControlID() == 0x36ad4a4 || window->GetControlID() == 0x625cd52)
            return 0x26;
        return 0;
    }

    if (input->mpController->IsPlacing()) {
        if (!pObject)
            return 0;
        cGameData* data = (cGameData*)pObject->Cast(kGameData);
        if (!data)
            return 0;
        if (data->GetNounID() != kTribeTool)
            return 0;
        cTribeTool* tool = (cTribeTool*)object_cast(data, kTribeTool);
        if (!tool->mSpatial.IsUnderConstruction())
            return 0;
        if (tool->GetToolType() == 10)
            return 0;
        return 0x2f;
    }

    cGameTerrainCursor* cursor = GetGameTerrainCursor_s00cc_efb0();
    if (cursor && cursor->IsRectangleSelecting())
        return 0;

    if (cTribeModeStrategy_s00cc_efb0::Instance()->GetInputStrategy()->mPendingAction != 0)
        return 8;

    if (input->mToolMode == 1) {
        cGameData* data = ToGameData(pObject);
        if (data && CanUseToolA(data))
            return 4;
        return 3;
    }
    if (input->mToolMode == 2) {
        cGameData* data = ToGameData(pObject);
        if (data && CanUseToolB(data))
            return 6;
        return 5;
    }

    if (cursor->GetSelectionCount() == 0) {
        cGameData* data = ToGameData(pObject);
        if (!data)
            return 0;
        uint32_t noun = data->GetNounID();
        if (noun == kGameDataUFO)
            return 0x30;
        if (noun != kTribeHut)
            return 0;
        cTribeHut* hut = (cTribeHut*)object_cast(data, kTribeHut);
        if (!hut->mSpatial.IsUnderConstruction())
            return 0;
        return 0x26;
    }

    cTribe_s00cc_efb0* tribe = NounManager_s00cc_efb0()->GetPlayerTribe();
    cPlanetModel_s00cc_efb0* planet = PlanetModel_s00cc_efb0();
    int tribeRegion = planet->GetRegion(tribe->mSpatial.GetPosition());

    Vector3_s00cc_efb0 pos = pPickPos ? *pPickPos : Viewer()->GetCursorPosition(0, Vector3_s00cc_efb0::ZERO);
    bool sameRegion = true;
    if (pos != Vector3_s00cc_efb0::ZERO)
        sameRegion = PlanetModel_s00cc_efb0()->GetRegion(pos) == tribeRegion;

    cGameData* data = ToGameData(pObject);
    if (!data) {
        cPickInfo* pick = GetPickInfo(pObject);
        if (pick) {
            if (planet->GetRegion(pick->mPosition) != tribeRegion)
                return 7;
            if (tribe->HasToolA())
                return 0x25;
        }
    } else {
        GetActivePlanet();
        switch (data->GetNounID()) {
        case kGameDataUFO:
            return 0x30;

        case kOrnament: {
            cOrnament* ornament = (cOrnament*)object_cast(data, kOrnament);
            if (ornament->mOrnamentType == 0x356eb8a) {
                if (pos != Vector3_s00cc_efb0::ZERO) {
                    if (!PlanetModel_s00cc_efb0()->IsLand(pos))
                        return 1;
                    return tribe->IsAllied() ? 0x22 : 7;
                }
            } else if (ornament->mOrnamentType == 0x5b9a06e) {
                float minHeight = GetPropertyFloat(g_TribeProperties, 0xd2078a9b, 10.0f);
                cOrnamentModel* model = GetOrnamentModel(ornament->GetModelKey());
                if (model && model->mHeight > minHeight)
                    return 0x23;
            }
            break;
        }

        case kGameBundle: {
            cGameBundle* bundle = (cGameBundle*)object_cast(data, kGameBundle);
            uint32_t owner = bundle->mOwnerID;
            if (owner == Player()->GetPoliticalID())
                return 0x1b;
            cTribe_s00cc_efb0* other = GetTribeByPoliticalID(bundle->mOwnerID);
            if (!other)
                break;
            if (other == NounManager_s00cc_efb0()->GetPlayerTribe()) {
                if (!other->HasToolB())
                    return 0x1e;
                return other->HasToolA() + 0x1f;
            }
            if (other->mbDefeated)
                return 0x1b;
            switch (cTribeModeStrategy_s00cc_efb0::Instance()->mDifficulty) {
            case 0:
                return (RelationshipManager()->GetRelationship(other->GetPoliticalID(), tribe->GetPoliticalID(), 1) >= 2) + 0xe;
            case 1:
                if (RelationshipManager()->GetRelationship(other->GetPoliticalID(), tribe->GetPoliticalID(), 1) < 4)
                    return 0x21;
                break;
            }
            break;
        }

        case kTribeTool: {
            cTribeTool* tool = (cTribeTool*)object_cast(data, kTribeTool);
            tool->GetTribe()->GetPoliticalID();
            if (tool->mSpatial.IsUnderConstruction()) {
                if (tool->mCombatant.GetHealthPercentage() < 1.0f) {
                    if (tool->mCombatant.GetHealthPercentage() <= 0.0f)
                        return 0;
                    return 9;
                }
                switch (tool->GetToolType()) {
                case 8:  return 0x11;
                case 7:  return 0x12;
                case 1:  return 0x13;
                case 2:  return 0x14;
                case 3:  return 0x15;
                case 4:  return 0x16;
                case 5:  return 0x17;
                case 6:  return 0x18;
                case 9:  return 0x19;
                case 10: return 0x1a;
                }
                return 0;
            }
            if (cTribeModeStrategy_s00cc_efb0::Instance()->mDifficulty != 1)
                return 0;
            if (tool->GetToolType() == 10)
                return 0;
            if (tool->mCombatant.GetDamageState() == 2)
                return 0;
            return tool->GetTribe()->IsRaided() ? 0xc : 0x2a;
        }

        case kCreatureAnimal: {
            cCreatureAnimal* animal = (cCreatureAnimal*)object_cast(data, kCreatureAnimal);
            if (tribeRegion != planet->GetRegion(animal->mLocomotive.GetPosition()))
                return 7;
            if (!animal->mbBusy) {
                switch (cTribeModeStrategy_s00cc_efb0::Instance()->mDifficulty) {
                case 0:
                    if (animal->IsFlagged())
                        return 0;
                    if (animal->GetPoliticalID() == tribe->GetPoliticalID())
                        return 0;
                    return 0x29;
                case 1:
                    return 0xb;
                }
            }
            if (tribe->HasToolB())
                return 0x1c;
            break;
        }

        case kCreatureCitizen: {
            cCreatureCitizen* citizen = (cCreatureCitizen*)object_cast(data, kCreatureCitizen);
            if (citizen->mbBusy == 1)
                return 0;
            if (citizen->mLocomotive.IsUnderConstruction()) {
                float threshold = citizen->mThreshold;
                if (citizen->mTimer.GetValue() > threshold) {
                    SpatialFixedVector<16> selection;
                    GetGameTerrainCursor_s00cc_efb0()->GetSelection(selection);
                    for (SpatialRef* it = selection.mpBegin; it != selection.mpEnd; ++it) {
                        cCreatureCitizen* other = ToCitizen(*it);
                        if (other && other != citizen && other->GetActivity() == 9)
                            return 0x28;
                    }
                }
                return 0x2e;
            }
            switch (cTribeModeStrategy_s00cc_efb0::Instance()->mDifficulty) {
            case 0: {
                if (citizen->GetTribe()->mbDefeated)
                    return 0;
                cTribe_s00cc_efb0* other = citizen->GetTribe();
                if (RelationshipManager()->GetRelationship(other->GetPoliticalID(), tribe->GetPoliticalID(), 1) < 2)
                    return IsCitizenIdle(citizen) ? 0x10 : 0xd;
                if (citizen->mpHerd->mBehaviorID == 0x546e8804)
                    return 0x2d;
                cCreatureCitizen* leader = tribe->GetLeader();
                if (leader && (!leader->mLocomotive.IsMoving() || leader->mbBusy))
                    return 0x2b;
                return 0x27;
            }
            case 1:
                return citizen->GetTribe()->IsRaided() ? 0xa : 0x2a;
            }
            return 0;
        }

        case kFruit: {
            cFruit* fruit = (cFruit*)object_cast(data, kFruit);
            if (tribe->HasToolA() && planet->GetRegion(fruit->mSpatial.GetPosition()) == tribeRegion)
                return 0x24;
            break;
        }

        case kTribeHut: {
            cTribeHut* hut = (cTribeHut*)object_cast(data, kTribeHut);
            cTribe_s00cc_efb0* owner = hut->GetTribe();
            owner->GetPoliticalID();
            if (hut->mSpatial.IsUnderConstruction()) {
                if (hut->mCombatant.GetHealthPercentage() < 1.0f) {
                    if (hut->mCombatant.GetHealthPercentage() > 0.0f)
                        return 9;
                }
                return 0x26;
            }
            if (owner->mbDefeated)
                return 0;
            if (hut->mCombatant.GetDamageState() == 2)
                return 0;
            switch (cTribeModeStrategy_s00cc_efb0::Instance()->mDifficulty) {
            case 0:
                return (RelationshipManager()->GetRelationship(owner->GetPoliticalID(), tribe->GetPoliticalID(), 1) >= 2) + 0xe;
            case 1:
                return hut->GetTribe()->IsRaided() ? 0xc : 0x2a;
            }
            break;
        }

        case kEgg:
            if (cTribeModeStrategy_s00cc_efb0::Instance()->mDifficulty == 1)
                return 0x1d;
            break;

        case kTribeFoodMat: {
            cTribeFoodMat* mat = (cTribeFoodMat*)object_cast(data, kTribeFoodMat);
            cTribe_s00cc_efb0* owner = mat->mpTribe;
            mat->GetPoliticalID();
            if (mat->mSpatial.IsUnderConstruction()) {
                if (!tribe->HasToolB())
                    return 0x1e;
                return tribe->HasToolA() + 0x1f;
            }
            if (((cFoodStore*)owner->mFood)->GetAmount() <= 0.0f)
                return 0;
            switch (cTribeModeStrategy_s00cc_efb0::Instance()->mDifficulty) {
            case 0:
                if (owner->mbDefeated)
                    return 0;
                return (RelationshipManager()->GetRelationship(owner->GetPoliticalID(), tribe->GetPoliticalID(), 1) >= 2) + 0xe;
            case 1:
                if (RelationshipManager()->GetRelationship(owner->GetPoliticalID(), tribe->GetPoliticalID(), 1) < 4)
                    return 0x21;
                break;
            }
            break;
        }
        }
    }
    return sameRegion ? 0 : 7;
}

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

// @ 0x00cd02d0
void CInput::F_cd02d0(void* posf)
{
    float* pos = (float*)posf;
    void* auth = FUN_00a206f0();
    uint32_t uSound = 0;
    if (auth != 0)
        uSound = (uint32_t)((void*(__thiscall*)(void*)) (*(void***)auth)[0x20 / 4])(auth);

    void* au = FUN_00a206f0();
    if (au != 0) {
        ((void(__thiscall*)(void*, uint32_t)) (*(void***)au)[0x38 / 4])(au, 0x3475365);
        ((void(__thiscall*)(void*, uint32_t, uint32_t)) (*(void***)au)[0x40 / 4])(au, 0x3475381, 0xc45c1574);
        ((void(__thiscall*)(void*, uint32_t, uint32_t)) (*(void***)au)[0x40 / 4])(au, 0x3475385, uSound);
        ((void(__thiscall*)(void*)) (*(void***)au)[0x58 / 4])(au);
    }

    void* planet   = FUN_00b3d350();
    void* someObj  = ((void*(__thiscall*)(void*, void*)) FUN_00b82fc0)(planet, posf);
    void* someObj2 = ((void*(__thiscall*)(void*, void*)) FUN_00b88590)(planet, posf);
    void* tribe    = ((void*(__thiscall*)(void*)) FUN_00bfc5f0)(FUN_00b3d300());
    void* inner0   = (char*)tribe + 0x120;
    void* id       = ((void*(__thiscall*)(void*)) (*(void***)inner0)[0x2c / 4])(inner0);
    void* plr      = ((void*(__thiscall*)(void*, void*)) FUN_00b88590)(planet, id);

    if (someObj == 0) {
        if (FUN_00ccefb0(0, posf) != 7) {
            HeapVec vec;
            vec.mpBegin = 0;
            vec.mpEnd = 0;
            vec.mpCap = 0;
            void* tc = GetGameTerrainCursor();
            ((void(__thiscall*)(void*, void*)) (*(void***)tc)[0x5c / 4])(tc, &vec);

            char first = 1;
            for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
                void* citizen = 0;
                if (*it != 0)
                    citizen = ((void*(__thiscall*)(void*, uint32_t)) (*(void***)*it)[0xb8 / 4])(*it, 0x4f176642);

                void* inner = (char*)citizen + 0xc0;
                void* cid = ((void*(__thiscall*)(void*)) (*(void***)inner)[0x2c / 4])(inner);
                void* cobj = ((void*(__thiscall*)(void*, void*)) FUN_00b88590)(planet, cid);

                if (someObj == cobj
                 || *((char*)cobj + *(int*)((char*)planet + 100)) == 0
                 || someObj == someObj2) {
                    if (first) {
                        first = 0;
                        void* m = FUN_00b3d240_s00cc_fc20();
                        ((void(__thiscall*)(void*, uint32_t, void*)) (*(void***)m)[0x6c / 4])(m, 0x1d110a0, posf);
                    }
                    void* ord = FUN_00bca2c0();
                    if (ord == 0 || *(int*)ord != 4 || *(short*)((char*)ord + 0x4b) != 0x31) {
                        void* ord2 = ((void*(__thiscall*)(void*, int, void*, void*)) FUN_00c275b0)(citizen, 4, 0, 0);
                        ((void(__thiscall*)(void*, void*)) FUN_006a3570)((char*)ord2 + 0x39, posf);
                    } else {
                        float* pf;
                        short s = *(short*)((char*)ord + 0x4b);
                        if (s == 0x31 || s == 0x10) {
                            if ((*(unsigned char*)((char*)ord + 0x49) & 0x30) == 0)
                                pf = (float*)((char*)ord + 0x39);
                            else
                                pf = *(float**)((char*)ord + 0x39);
                        } else {
                            pf = (float*)FUN_006bb5e0();
                        }
                        float dx = pf[0] - pos[0];
                        float dy = pf[1] - pos[1];
                        float dz = pf[2] - pos[2];
                        if (dx*dx + dy*dy + dz*dz > 1.0f) {
                            void* ord2 = ((void*(__thiscall*)(void*, int, void*, void*)) FUN_00c275b0)(citizen, 4, 0, 0);
                            ((void(__thiscall*)(void*, void*)) FUN_006a3570)((char*)ord2 + 0x39, posf);
                        }
                    }
                    ((void(__thiscall*)(void*, int)) (*(void***)citizen)[0xf0 / 4])(citizen, 4);
                } else {
                    void* m = FUN_00b3d240_s00cc_fc20();
                    ((void(__thiscall*)(void*, uint32_t, void*)) (*(void***)m)[0x6c / 4])(m, 0xb062b167, posf);
                }
            }
            ((void(__thiscall*)(void*)) FUN_00ad92d0)(&vec);
            return;
        }
    }
    void* m = FUN_00b3d240_s00cc_fc20();
    ((void(__thiscall*)(void*, uint32_t, void*)) (*(void***)m)[0x6c / 4])(m, 0xb062b167, posf);
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

// @ 0x00cd3b60
TM::TM()
{
    M_b70820();
    float one = g_fltOne;
    *(void* volatile*)this = g_vt147734c;
    *(void* volatile*)((char*)this + 8) = g_vt1477328;
    *(void* volatile*)((char*)this + 0x10) = g_vt1477318;
    *(volatile int*)((char*)this + 0x74) = 0;
    *(volatile float*)((char*)this + 0x88) = one;
    *(volatile float*)((char*)this + 0x8c) = g_fltTwo;
    *(volatile int*)((char*)this + 0x84) = 0;
    *(volatile int*)((char*)this + 0x90) = 0;
    *(volatile int*)((char*)this + 0x80) = 1;
    *(void* volatile*)((char*)this + 0x7c) = g_vt154df28;
    g_169b27c = (uint32_t)this;
}

// @ 0x00cd3bf0
void TM::SetMission(void* a)
{
    void* panel = FUN_00b3d400();
    if (a == 0) {
        ((void(__thiscall*)(void*, int))(*(void***)this)[0x28 / 4])(this, 0);
        return;
    }
    void* citizen = ((void*(__thiscall*)(void*, unsigned int))(*(void***)a)[0xc / 4])(a, 0xd0036e08);
    void* c2 = ((void*(__thiscall*)(void*, unsigned int))(*(void***)a)[0xc / 4])(a, 0x4f176642);
    void* tribe = ((void*(__thiscall*)(void*, unsigned int))(*(void***)a)[0xc / 4])(a, 0x4f396a66);
    if (tribe == 0) {
        if (c2 == 0) { ((void(__thiscall*)(void*, int))(*(void***)this)[0x28 / 4])(this, 0); return; }
        tribe = ((CCitizen*)c2)->GetTribe();
        if (tribe == 0) { ((void(__thiscall*)(void*, int))(*(void***)this)[0x28 / 4])(this, 0); return; }
    }
    uint32_t key = ((unsigned int(__thiscall*)(void*))(*(void***)tribe)[0x4c / 4])(tribe);
    HashTable* t = (HashTable*)((char*)this + 0x78);
    HashIter it;
    t->find(&it, &key);
    if (it.mNode == (HashNode*)t->mppBuckets[t->mnBucketCount]) {
        void* noun = ((CGameNounMgr*)NounManager())->CreateNoun(0x5436411a);
        ((CMission*)noun)->SetTribe(tribe);
        void** slot = t->operator[](&key);
        void* old = *slot;
        if (noun != old) {
            if (noun != 0)
                ((void(__thiscall*)(void*))(*(void***)noun)[0])(noun);
            *slot = noun;
            if (old != 0)
                ((void(__thiscall*)(void*))(*(void***)old)[0x4 / 4])(old);
        }
        void* ref = noun;
        if (noun != 0)
            ((void(__thiscall*)(void*))(*(void***)noun)[0])(noun);
        {
            SPVector* vec = (SPVector*)((char*)this + 0x14);
            if ((char*)vec->mEnd >= (char*)vec->mCap) {
                vec->DoInsertPtr(vec->mEnd, &ref);
            } else {
                char* pos = (char*)vec->mEnd;
                vec->mEnd = pos + 4;
                if (pos != 0) {
                    *(void**)pos = ref;
                    if (ref != 0)
                        ((void(__thiscall*)(void*))(*(void***)ref)[0])(ref);
                }
            }
        }
        if (ref != 0)
            ((void(__thiscall*)(void*))(*(void***)ref)[0x4 / 4])(ref);
    }
    if (*(void**)((char*)this + 0x74) != 0) {
        void* r = ((CMission*)*(void**)((char*)this + 0x74))->GetTribe();
        if (r == tribe)
            goto tail;
    }
    if (*(void**)((char*)this + 0x74) != 0) {
        if (panel != 0)
            ((CPanel*)panel)->RemoveMissionCard(*(void**)((char*)this + 0x74));
        void* p = *(void**)((char*)this + 0x74);
        if (p != 0) {
            *(void**)((char*)this + 0x74) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[0x4 / 4])(p);
        }
    }
    {
        void** slot = t->operator[](&key);
        void* nv = *slot;
        void* old = *(void**)((char*)this + 0x74);
        if (nv != old) {
            if (nv != 0)
                ((void(__thiscall*)(void*))(*(void***)nv)[0])(nv);
            *(void**)((char*)this + 0x74) = nv;
            if (old != 0)
                ((void(__thiscall*)(void*))(*(void***)old)[0x4 / 4])(old);
        }
    }
    {
        void* m = *(void**)((char*)this + 0x74);
        if (((unsigned int(__thiscall*)(void*))(*(void***)m)[0x60 / 4])(m) == 5)
            goto tail;
    }
    if (panel != 0) {
        if (!((CPanel*)panel)->HasMissionCard(*(void**)((char*)this + 0x74))) {
            ((CPanel*)panel)->SetupMissionCard(*(void**)((char*)this + 0x74), 0, 1, 0);
            ((CPanel*)panel)->ExpandMissionCard(*(void**)((char*)this + 0x74));
        }
    }
tail:
    ((void(__thiscall*)(void*, int))(*(void***)this)[0x28 / 4])(this, 0);
}

// @ 0x00cd3e60
void TM::F_cd3e60()
{
    unsigned int r;
    if (((CProps*)g_appProps)->GetDesc(0x061b67b6) != 0)
        r = (unsigned int)FNV1_String8(g_StrTRGMac, 0x811c9dc5, 1);
    else
        r = (unsigned int)FNV1_String8(g_StrTRG, 0x811c9dc5, 1);
    (void)r;
}

// @ 0x00cd3f20
void F_cd3f20(uint32_t idx)
{
    int local_c = 0;
    int local_8 = 0;
    if (GetPropertyAsUint32Array(g_1581288, 0xf5bf4d8e, &local_c, &local_8)
        && local_c > 0 && (uint32_t)local_c > idx) {
        CTerrain_s00cd_3480* te = ((CMgr_s00cd_3480*)NounManager())->GetCurrentTerrainSphere();
        int v = *(int*)(local_8 + (int)idx * 4);
        int local_4 = 0;
        te->F77380(0x055d6335, &local_4);
        te->F79f00(0x055d6335, local_4 + v);
    }
}

// @ 0x00cd3fb0
void F_cd3fb0(int a)
{
    CTerrain_s00cd_3480* s = ((CMgr_s00cd_3480*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        s->F77bf0(a);
        return;
    }
}

// @ 0x00cd3fd0
void F_cd3fd0(int a)
{
    CTerrain_s00cd_3480* s = ((CMgr_s00cd_3480*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        s->F77300(a);
        return;
    }
}

// @ 0x00cd3ff0
void PostTerrainAction(int kind, void* tgt)
{
    int id;
    switch (kind) {
    case 0: id = 0x4dbdc67d; break;
    case 1: id = 0x4dbdc67e; break;
    case 2: id = 0x4dbdc67f; break;
    case 3: id = 0x4dbdc678; break;
    case 4: id = 0x4dbdc679; break;
    default: return;
    }
    CActTarget t;
    ((CTrig*)GetTriggerMgr())->PostAction(id, t.Ctor(tgt), 0);
    t.Dtor();
}

// @ 0x00cd4070
TM* TM::F_cd4070(int id)
{
    TM* r = this;
    if (id <= 0x116dd1b) {
        if (id == 0x116dd1b)
            return r;
        if (id == (int)0xee3f516e)
            goto tail;
        if (id != 0x116d389)
            r = 0;
        return r;
    }
    if (id != 0x2f009dd0)
        return 0;
tail:
    if (r == 0)
        return 0;
    return (TM*)((char*)r + 4);
}

// @ 0x00cd40f0
void TM::F_cd40f0(void* p)
{
    void* base = (char*)p + 0x34;
    void* o = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    if (!((unsigned char(__thiscall*)(void*))(*(void***)o)[0x50 / 4])(o))
        ((void(__thiscall*)(void*, int))(*(void***)p)[0xf0 / 4])(p, 0x29b);
    void* o2 = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    ((void(__thiscall*)(void*, int))(*(void***)o2)[0x54 / 4])(o2, 1);
    void* cur = GetGameTerrainCursor();
    ((void(__thiscall*)(void*))(*(void***)cur)[0x74 / 4])(cur);
    cur = GetGameTerrainCursor();
    ((void(__thiscall*)(void*))(*(void***)cur)[0xc8 / 4])(cur);
}

// @ 0x00cd4160
unsigned char TM::F_cd4160(void* p)
{
    void* base = (char*)p + 0x34;
    void* o = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    return ((unsigned char(__thiscall*)(void*))(*(void***)o)[0x50 / 4])(o);
}

// @ 0x00cd4180
void TM::F_cd4180(int a, float f1, float f2, int b)
{
    mInput.OnMouseDown(a, f1, f2, b);
    void* m = GetGameInputManager();
    ((void(__thiscall*)(void*, int, float, float, int))(*(void***)m)[0x54 / 4])(m, a, f1, f2, b);
}

// @ 0x00cd41d0
void TM::F_cd41d0(float f1, float f2, int a)
{
    mInput.OnMouseWheel(f1, f2, a);
    void* m = GetGameInputManager();
    ((void(__thiscall*)(void*, float, float, int))(*(void***)m)[0x5c / 4])(m, f1, f2, a);
}

// @ 0x00cd4220
void TM::F_cd4220(int a, float f1, float f2, int b)
{
    mInput.OnMouseUp(a, f1, f2, b);
    void* m = GetGameInputManager();
    ((void(__thiscall*)(void*, int, float, float, int))(*(void***)m)[0x58 / 4])(m, a, f1, f2, b);
}

// @ 0x00cd4280
void TM::StartTribe()
{
    ((CTrig*)GetTriggerMgr())->SetEnabled(1);
    void* tribe = ((CMgr_s00cd_3480*)NounManager())->GetPlayerTribe();
    void* obj = ((void*(__thiscall*)(void*))(*(void***)tribe)[0xac / 4])(tribe);
    void* tool = ((CTribe*)tribe)->GetToolOfType(10);
    void* trig = ((CTrig*)GetTriggerMgr())->PostTrigger(g_StrTRGBegin, 1, 1, 0, 0, 0);
    {
        CActTarget_s00cd_3480 t;
        t.Ctor((char*)tribe + 0x120);
        ((CTrig*)GetTriggerMgr())->PostAction(0x3d7f90a, &t, trig);
        t.Dtor();
    }
    {
        CActTarget_s00cd_3480 t;
        t.Ctor(obj != 0 ? (char*)obj + 0x34 : 0);
        ((CTrig*)GetTriggerMgr())->PostAction(0xaa227986, &t, trig);
        t.Dtor();
    }
    {
        CActTarget_s00cd_3480 t;
        t.Ctor(tool != 0 ? (char*)tool + 0x34 : 0);
        ((CTrig*)GetTriggerMgr())->PostAction(0x60ed02ef, &t, trig);
        t.Dtor();
    }
    {
        Msg3 msg;
        msg.a = 0x200; msg.b = 0; msg.c = 0x934dcce7;
        ((CTrig*)GetTriggerMgr())->ObjectMessage(0xe6311d5a, &msg, trig);
    }
    ((CAch*)AchievementsController())->F(0xd082675a, 4, 1);
}

// @ 0x00cd43c0
void TM::F_cd43c0(void* a)
{
    void* argument = *(void* volatile*)&a;
    C9630* o = ((C9630*(__thiscall*)(void*, void*))(*(void***)this)[0x6c / 4])(this, argument);
    o->M();
}

// @ 0x00cd43e0
void TM::RegisterCityHallAndStartCinematic(int* pos)
{
    CTerrain* te = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    te->mCityHallPos[0] = pos[0];
    te->mCityHallPos[1] = pos[1];
    te->mCityHallPos[2] = pos[2];
    Msg8 msg;
    msg.a = 0x2ea8fb98; msg.b = 0; msg.c = 0;
    void* o = FUN_00401010();
    ((void(__thiscall*)(void*, int*, void*))(*(void***)o)[0x4c / 4])(o, pos, &msg);
    ((CursorTable*)GetCursorTable())->FindLocal(0x1003);
    *(unsigned char*)((char*)this + 0x3a0) = 1;
}

// @ 0x00cd4460
unsigned int TM::F_cd4460(int a)
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        if (s->HasFlag(a))
            return 1;
    }
    return 0;
}

// @ 0x00cd4490
bool TM::F_cd4490()
{
    return *(int*)((char*)this + 0x22c) != 0xb;
}

// @ 0x00cd44a0
bool TM::F_cd44a0()
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    int hasKey = s != 0 && s->HasFlag(0x056d1871);
    return (char)hasKey == 0;
}

struct IStreamHolder_cd44e0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void* GetStream();   // +0x18
};
struct ISerializer_cd44e0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void* GetHolder();   // +0x20
};
static __forceinline void WriteUint32Value_cd44e0(void* s, uint32_t value)
{
    WriteUint32(s, &value, 1, 0);
}

// @ 0x00cd44e0
bool TM::F_cd44e0(void* a, void* b)
{
    uint32_t v = *(uint32_t*)b;
    void* p = ((ISerializer_cd44e0*)a)->GetHolder();
    WriteUint32Value_cd44e0(((IStreamHolder_cd44e0*)p)->GetStream(), v);
    return true;
}

// @ 0x00cd4580
ThemeMgr::ThemeMgr()
{
    float m = g_fltmax;
    *(int*)((char*)this + 4) = 0;
    *(void**)this = g_vt14774b0;
    int* p = (int*)((char*)this + 8);
    int n = 0x17;
    do {
        *p = 0;
        *(float*)(p + 1) = m;
        p += 2;
        --n;
    } while (n >= 0);
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
    ((TC2v)VSLOT(app, 0x20))(app, 0x4c6a8d6, (void*)FUN_00bc36d0);
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
    void* c = FUN_00b3d240((int)FUN_00cd45c0);
    ((CExt33ce0*)c)->call();
    void* d = FUN_00b3d240((int)&FUN_00cd46d0);
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
    RefMgr* p = new ("Simulator", 0, 0, 0, 0) RefMgr;   // the tag is a string literal (0x013f09b4)
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

// @ 0x00cd5980
void WritePairsT(Stream* s, unsigned char* vec)
{
    unsigned char* begin = *(unsigned char**)vec;
    unsigned char* end = *(unsigned char**)(vec + 4);
    uint32_t n = (uint32_t)((end - begin) >> 3);
    StreamInner* inner = s->Get_20();
    EA_IO_WriteUint32(inner->Write_18(), &n, 1, 0);
    unsigned char* p = begin;
    while (p != end) {
        inner = s->Get_20();
        EA_IO_WriteUint32(inner->Write_18(), (const uint32_t*)p, 1, 0);
        s->End_1c();
        inner = s->Get_20();
        EA_IO_WriteUint32(inner->Write_18(), (const uint32_t*)(p + 4), 1, 0);
        s->End_1c();
        p += 8;
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

// @ 0x00cd5b80
void FUN_00cd5b80()
{
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    void* leader = ((cCommunity*)tribe)->GetLeader();
    if (!leader)
        return;
    LeaderSub* leaderSub = &((LeaderObj*)leader)->mSub;
    cSPVector3_s00cd_5550 pos = *leaderSub->GetPos();
    float* qp = leaderSub->GetQuat();
    float q[4];
    q[0] = qp[0]; q[1] = qp[1]; q[2] = qp[2]; q[3] = qp[3];
    unsigned char* sys = (unsigned char*)FUN_00d1e660();
    void* holder = ((SysObj*)sys)->mp24;
    void* props = ((Holder*)holder)->mp130;
    float cnt = SP_GetPropertyT_float(props, 0xb2aa8e19, g_flt_1473c70);
    float scale = SP_GetPropertyT_float(props, 0xed219018, g_flt_1486110);
    int icnt = (int)cnt;
    uint32_t r = ((RandLCG*)g_rand_1601760)->Uniform((uint32_t)(0x400 - icnt));
    float v1[3], v2[3];
    FUN_0059aed0(v1, &g_v3_169b360, q);
    FUN_0059aed0(v2, &g_v3_169b36c, q);
    if (cnt > 0.0f) {
        float* tbl = &g_1559bdc[r * 2];      // g_1559bdc + r*8 bytes (stride 2 floats)
        int i = 0;                           // loop index (doubles each pass: i = 2i+1)
        do {
            void* container = FUN_00ac79d0(FUN_00b3d2b0(3));
            FxObj* obj = (FxObj*)FUN_00ac7ab0(FUN_00b3d2b0(3), g_flt_15812dc, container, 3);
            if (obj) {
                float ox = tbl[-1];
                float oy = tbl[0];
                cSPVector3_s00cd_5550 v;
                v.x = oy * (v2[0] * scale) + (ox * (v1[0] * scale) + pos.x);
                v.y = oy * (v2[1] * scale) + (ox * (v1[1] * scale) + pos.y);
                v.z = oy * (v2[2] * scale) + (ox * (v1[2] * scale) + pos.z);
                obj->mSub34.Apply(&v);
                ((void(__thiscall*)(void*, FxObj*)) (*(void***)obj->mp128)[0x30 / 4])(obj->mp128, obj);
                obj->m130 = (uint32_t)(i + 1);
                obj->mb124 = (unsigned char)(i + 1);
            }
            i += i + 1;
            tbl += 2;
        } while ((float)i < cnt);
    }
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

// @ 0x00cd6390
void cTribeModeStrategy::F_cd6390(unsigned char enable)
{
    if (enable == 0) {
        if (mp_398 != 0) {
            ((void(__thiscall*)(void*)) (*(void***)mp_398)[0xc / 4])(mp_398);
            if (mp_398 != 0) {
                RefObj* p = (RefObj*)mp_398;
                mp_398 = 0;
                p->AddRef();
                return;
            }
        }
        return;
    }
    if (mp_398 != 0)
        F_cd6390(0);
    void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
    if (tribe == 0)
        return;
    unsigned char* squad = (unsigned char*)((void*(__thiscall*)(void*)) (*(void***)tribe)[0xac / 4])(tribe);
    if (squad == 0)
        return;
    void* fx = SP_EffectsManager();
    if (mp_398 != 0) {
        RefObj* p = (RefObj*)mp_398;
        mp_398 = 0;
        p->AddRef();
    }
    unsigned char ok = ((unsigned char(__thiscall*)(void*, uint32_t, int, void**)) (*(void***)fx)[0x2c / 4])(fx, 0x1a2cc3f0, 0, &mp_398);
    if (!ok)
        return;
    unsigned char* base = squad + 0x34;
    float* pos = (float*)((void*(__thiscall*)(void*)) (*(void***)base)[0x2c / 4])(base);
    float px = pos[0], py = pos[1], pz = pos[2];
    float* q = (float*)((void*(__thiscall*)(void*)) (*(void***)base)[0x68 / 4])(base);
    float qw = q[0x14 / 4];
    unsigned char* tmp = (unsigned char*)base;   // keep base live
    (void)tmp;
    cSPVector3_s00cd_5550 in, out;
    in.x = px; in.y = py; in.z = pz;
    in.z = qw;
    SP_NormalizedSafe(&out, &in);
    (void)qw;
    XformMsg msg;
    msg.ctor();
    msg.mFlags |= 4;
    msg.mCount++;
    msg.mX = px;
    msg.mY = py;
    msg.mZ = pz;
    void* qq = ((void*(__thiscall*)(void*)) (*(void***)base)[0x30 / 4])(base);
    SP_QuaternionToMatrix(msg.mMatrix, qq);
    msg.mFlags |= 2;
    msg.mCount++;
    ((void(__thiscall*)(void*, void*)) (*(void***)mp_398)[0x18 / 4])(mp_398, &msg);
    ((void(__thiscall*)(void*, int)) (*(void***)mp_398)[8 / 4])(mp_398, 0);
}

// @ 0x00cd6610
void HashElem::Clear()
{
    DoFreeNodes(mp4, mp8);
    m0c = 0;
}

// @ 0x00cd6680
bool ClearEntryBlock(cOwner* owner, cEntry** entries)
{
    cInner*  inner  = owner->GetInner();
    cStream* stream = inner->GetStream();

    int count;
    ReadInt32Stream(stream, &count, 1, 0);

    const int maxEntries = 20;
    int n = MinInt(count, maxEntries);

    cEntry** p = entries;
    for (int i = 0; i < n; ++i, ++p)
    {
        if (*p)
        {
            cEntry* entry = *p;
            *p = 0;
            entry->Release();
        }
        owner->SetProperty(0x03A25119u, p, 0);
    }

    return true;
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

// @ 0x00cd6800
void cTribeModeStrategy::FUN_00cd6800()
{
    cGameTimeManager_s00cd_6800* time = GameTimeManager_s00cd_6800();
    time->DecPauseGate(0x4bf38a7u);

    switch (mState4) {
    case 1:
        if (ConfigManager()->GetConfigU32(0x4ea96cbu) != 0) {
            if (ConfigManager()->GetConfigU32(0x5b5bb5eu) != 0) {
                DAT_0169b2c8->F_cd6390(1);
                FUN_00b3d4f0_s00cd_6800(1)->FUN_00e2f270();
                cGameInputManager_s00cd_6800* input = GameInputManager_s00cd_6800();
                input->mField110++;
                if (GetCameraCtl_s00cd_6800() != 0)
                    GetCameraCtl_s00cd_6800()->mFlag390 = true;
                DAT_0169b2c8->mTimer.Restart();
            }
        }
        break;
    case 2:
        if (ConfigManager()->GetConfigU32(0x5b5bb5eu) != 0)
            FUN_0067cac0_s00cd_6800()->UpdateHints(0x508fccb5u);
        break;
    }
}

// @ 0x00cd68d0
void cTribeModeStrategy::Teardown()
{
    GetHintMgr()->Shutdown();
    Timer_Reset();

    if (GetCameraCtl_s00cd_68d0())
        GetCameraCtl_s00cd_68d0()->mFlag390 = false;

    if (mp_398 != 0) {
        ((cRefObj_s00cd_68d0*)mp_398)->ReleaseWith(1);

        if (mp_398 != 0) {
            cRefObj_s00cd_68d0* p = (cRefObj_s00cd_68d0*)mp_398;
            mp_398 = 0;
            p->Release();
        }
    }

    GetAimSource()->Stop(0);
    GetAimSource()->Clear(0);

    if (GetCameraCtl_s00cd_68d0())
        GetCameraCtl_s00cd_68d0();

    Flag24a() = 0;
    _ReadWriteBarrier();            // keep the flag store ahead of the +0x250 object load

    // the refcounted object at +0x250 (inside the earlier landing's pad244[4]) released and cleared, as s00cd68d0 did
    if (Obj250()) {
        cRefObj_s00cd_68d0* q = (cRefObj_s00cd_68d0*)Obj250();
        Obj250() = 0;
        q->Release();
    }
}

// @ 0x00cd6980
void cTribeModeStrategy_s00cd6980::RaiseEvent(uint32_t eventHash)
{
    Simulator::cTerrainSphere_s00cd6980* sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();

    if (sphere != 0 && sphere->Contains(eventHash))
        return;

    sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();
    if (sphere != 0)
        sphere->HasFlagOrInsert(eventHash);

    switch (eventHash)
    {
    case 0x064c010f:
        Function_00cd3fd0(0x53203528);
        // fall through
    case 0x53203528:
        sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x83861976);
        // fall through
    case 0x83861976:
        sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x064d44f9);
        // fall through
    case 0x064d44f9:
        sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x064e70b3);
        // fall through
    case 0x064e70b3:
        sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x5ac72d7c);
        // fall through
    case 0x5ac72d7c:
        sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x14363974);

        sphere = NounManager_s00cd_6980()->GetCurrentTerrainSphere();
        if (sphere != 0 && sphere->Contains(0x056d1871))
            break;
        if (!HasEvent(0x064c010f))
            break;
        if (!HasEvent(0x83861976))
            break;
        if (!HasEvent(0x53203528))
            break;
        if (!HasEvent(0x064d44f9))
            break;
        if (!HasEvent(0x064e70b3))
            break;
        if (!HasEvent(0x5ac72d7c))
            break;

        Function_00cd3fb0(0x056d1871);
        m1a4 = 0;

        if (GameTimeManager_s00cd_6980()->IsPaused())
        {
            Simulator::cGameTimeManager_s00cd6980* time = GameTimeManager_s00cd_6980();
            time->DecPauseGate(0x064beb65);
            Simulator::cGameInputManager_s00cd6980* input = GameInputManager_s00cd_6980();
            input->m110--;
        }

        Function_00b3d4f0(0)->Reset();

        if (GetCameraCtl_s00cd_6980() != 0)
            GetCameraCtl_s00cd_6980()->m390 = 0;

        if (Function_0067dd30()->Find(0x04ea96cb) != 0 &&
            Function_0067dd30()->Find(0x05b5bb5e) != 0)
        {
            Simulator::cGameTimeManager_s00cd6980* time = GameTimeManager_s00cd_6980();
            time->IncPauseGate(0x04bf38a7);

            GetHintManager()->ShowHint(Simulator::g_hintKeys[1], (void*)g_0157f174, 0,
                                       Simulator::g_hintOffset, Simulator::g_hintOffset,
                                       0.0f, 0, 0);
        }
        break;

    case 0x064be5ff:
    {
        if (HasEvent(0x056d1871))
            break;
        if (Function_0067dd30()->Find(0x04ea96cb) == 0)
            break;
        if (Function_0067dd30()->Find(0x05b5bb5e) == 0)
            break;

        if (GetCameraCtl_s00cd_6980() != 0)
            GetCameraCtl_s00cd_6980()->m390 = 0;

        Simulator::cGameTimeManager_s00cd6980* pauseTime = GameTimeManager_s00cd_6980();
        pauseTime->IncPauseGate(0x04bf38a7);

        GetHintManager()->ShowHint(Simulator::g_hintKeys[0], 0, 0,
                                   Simulator::g_hintOffset, Simulator::g_hintOffset,
                                   0.0f, 0, 0);

        GetHintManager()->ShowHint(Simulator::g_hintKeys[2], (void*)g_0157f184, 0,
                                   Simulator::g_hintOffset, Simulator::g_hintOffset,
                                   0.0f, 0, 0);

        if (GameTimeManager_s00cd_6980()->IsPaused())
            break;
        Simulator::cGameTimeManager_s00cd6980* resumeTime = GameTimeManager_s00cd_6980();
        resumeTime->IncPauseGate(0x064beb65);
        break;
    }

    case 0x14363974:
        mp394->HintClear(0x0391c432);
        mp394->HintClear(0x69ba7f0d);
        mp394->HintClear(0x02d99d0b);
        break;

    case 0x11ade9ce:
    case 0x5312da01:
    case 0x84f037b0:
    case 0x7d7315c8:
    case 0x9a44d4ab:
    case 0xdcdf2f2f:
        mp394->HintClear(eventHash);
        break;
    }

    if (Function_0067dd30()->Find(0x04ea96cb) != 0 &&
        Function_0067dd30()->Find(0x05b5bb5e) != 0)
        Notify(eventHash);
}

// @ 0x00cd6e40
bool cTribeModeStrategy::HasObject(unsigned int id)
{
    SP::TribeObjectTable& table = Objects();
    SP::TribeObjectIterator it;
    unsigned int key = id;
    table.find(&it, &key);
    if (it.mpNode != table.mpBuckets[table.mnBucketCount])
        return it.mpNode->mValue != 0;
    return false;
}

// @ 0x00cd6ef0
bool cTribeModeStrategy::IsObjectAllowed(unsigned int id)
{
    if (!AllowAllObjects() && GetTribeProperty(gTribeStrategyProperties, 0x1ccfdbe6, 0)) {
        unsigned int key = id;
        SP::TribeObjectIterator it;
        SP::TribeObjectNode* end = Objects().End();
        unsigned char found = Objects().find(&it, &key)->mpNode != end;
        return found != 0;
    }
    return true;
}

// @ 0x00cd6f60
bool __cdecl WriteTribeObjectArray(SP::cIObjectDatabaseOStream* stream, void* const* objects)
{
    void* record = ((void* (__thiscall*)(void*))(*(void***)stream)[8])(stream);
    void** recordVtable = *(void***)record;
    EA::IO::IStream_s00cd_6f60* output;
    {
        unsigned int count = 20;
        output = ((EA::IO::IStream_s00cd_6f60* (__thiscall*)(void*))recordVtable[6])(record);
        EA::IO::WriteUint32(output, &count, 1, 0);
    }
    unsigned int remaining = 20;
    do {
        void* object = *objects;
        void* serializable = 0;
        if (object)
            serializable = ((void* (__thiscall*)(void*, unsigned int))
                (*(void***)object)[3])(object, 0x0179c807);
        ((bool (__thiscall*)(void*, void*))(*(void***)stream)[11])(stream, serializable);
        ++objects;
    } while (--remaining);
    return true;
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

// @ 0x00cd7100
void FUN_00cd7100(int relationship)
{
    u32 event;
    switch (relationship) {
    case 1: event = 0x1f530f73u; break;
    case 2: event = 0x87257c01u; break;
    case 3: event = 0xcbaf7ee2u; break;
    case 4: event = 0xd3a34498u; break;
    case 5: event = 0xbd7ce41eu; break;
    case 6: event = 0xeb39fbd9u; break;
    case 7: event = 0xa0d49e3au; break;
    case 8: event = 0x666686efu; break;
    case 9: event = 0x97ada627u; break;
    default:
        return;
    }

    if (!gTribeModeStrategy_0169b2c8->Has(relationship))
        EventLog_00b3d3e0_s00cd_7100()->PostFeedbackEvent(event, 0x182cd6ceu, 0, 0, 1, 0);
}

// 0x00cd6980: the event entry point the slice calls SignalTribeEvent; its body is the next function (slice text)
void cTribeModeStrategy::RaiseEvent(uint32_t eventHash)
{
    ((cTribeModeStrategy_s00cd6980*)this)->RaiseEvent(eventHash);
}

// @ 0x00cd7530
void cTribeModeStrategy::OnMouseWheel(int delta, float x, float y, int flags)
{
    mInput7530()->OnMouseWheel(delta, x, y, flags);

    // Camera-rotate trigger: not while key 0x56d1871 is set, only with 0x64be5ff,
    // and only when 0x64c010f is not already active.
    cTerrainSphere_s00cd_7530* sphere = NounManager_s00cd_7530()->GetCurrentTerrainSphere();
    if (sphere == 0 || !sphere->Contains(0x56d1871u)) {
        cTerrainSphere_s00cd_7530* sphere2 = NounManager_s00cd_7530()->GetCurrentTerrainSphere();
        if (sphere2 != 0 && sphere2->Contains(0x64be5ffu)) {
            cTerrainSphere_s00cd_7530* sphere3 = NounManager_s00cd_7530()->GetCurrentTerrainSphere();
            if (sphere3 == 0 || !sphere3->Contains(0x64c010fu))
                RaiseEvent(0x64c010fu);   // the slice's SignalTribeEvent (0x00cd6980)
        }
    }

    GameInputManager_s00cd_7530()->OnMouseWheel(delta, x, y, flags);
}

// @ 0x00cd75f0
bool cTribeModeStrategy_s00cd75f0::OnInput(int key, int modifiers)
{
    if (GameInputManager_s00cd_75f0()->v17(key, modifiers))
        return true;

    cGameTimeManager_s00cd75f0* timeManager = GameTimeManager_s00cd_75f0();
    if (timeManager->GetTimerState(0x04bf38a9) > 0)
        return true;

    if (modifiers == 0 && IsInputConsumed(key))
        return true;

    bool result = GameInputManager_s00cd_75f0()->v19(key, modifiers);

    cTerrainSphere_s00cd75f0* sphere = NounManager_s00cd_75f0()->GetCurrentTerrainSphere();
    if (sphere != 0 && sphere->Contains(0x056d1871))
        return result;

    if (!HasEvent(0x064be5ff))
        return result;

    cGameInputManager_s00cd75f0* input = GameInputManager_s00cd_75f0();
    if (!HasEvent(0x53203528) && (input->v06(0x12) || input->v06(0x11)))
        RaiseEvent(0x53203528);

    if (!HasEvent(0x83861976) && (input->v06(1) || input->v06(2) ||
                                  input->v06(3) || input->v06(4)))
        RaiseEvent(0x83861976);

    if (!HasEvent(0x064c010f) && (input->v06(9) || input->v06(0x10)))
        RaiseEvent(0x064c010f);

    return result;
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

struct cTribeModeStrategy_s00cd_7d90 {
    void*    mpVtbl0;                   // +0x00
    void*    mpVtbl1;                   // +0x04
    void*    mpVtbl2;                   // +0x08
    void*    mpVtbl3;                   // +0x0c
    void*    mpVtbl4;                   // +0x10
    uint32_t m14[6];                    // +0x14..+0x2b
    Vector2c mVec2c;                    // +0x2c
    uint32_t m38[2];                    // +0x38..+0x3f
    Obj40    mObj40;                    // +0x40..+0x57
    cGonzagoTimer mTimer;               // +0x58..+0x77
    uint32_t m78;                       // +0x78
    void*    mp7c;                      // +0x7c
    uint32_t m80[5];                    // +0x80..+0x93
    Obj94    mObj94;                    // +0x94..+0xa7
    PoolContainer mContA8;              // +0xa8..+0x197
    uint8_t  mb198;                     // +0x198
    uint8_t  m199[3];                   // +0x199..+0x19b
    void*    mp19c;                     // +0x19c
    float    m1a0;                      // +0x1a0
    uint8_t  mb1a4;                     // +0x1a4
    uint8_t  m1a5[3];                   // +0x1a5..+0x1a7
    cGonzagoTimer mTimer2;              // +0x1a8..+0x1c7
    void*    mp1c8;                     // +0x1c8
    void*    mp1cc;                     // +0x1cc
    void*    mp1d0;                     // +0x1d0
    void*    mp1d4;                     // +0x1d4
    void*    mp1d8;                     // +0x1d8
    void*    mp1dc;                     // +0x1dc
    uint32_t m1e0[0x48 / 4];            // +0x1e0..+0x227
    uint8_t  mb228;                     // +0x228
    uint8_t  m229[3];                   // +0x229..+0x22b
    uint32_t m22c;                      // +0x22c
    uint32_t m230;                      // +0x230
    uint32_t m234;                      // +0x234
    uint32_t m238;                      // +0x238
    uint32_t m23c;                      // +0x23c
    void*    mp240;                     // +0x240
    uint32_t m244;                      // +0x244
    uint32_t m248;                      // +0x248
    uint32_t m24c;                      // +0x24c
    void*    mp250;                     // +0x250
    void*    mp254;                     // +0x254
    void*    ma258[20];                 // +0x258..+0x2a7
    void*    ma2a8[20];                 // +0x2a8..+0x2f7
    void*    mp2f8;                     // +0x2f8
    uint32_t m2fc;                      // +0x2fc
    uint32_t m300;                      // +0x300 (untouched by the destructor)
    Vector304 mVec304;                  // +0x304..+0x30f
    uint32_t m310[0x21];                // +0x310..+0x393
    void*    mp394;                     // +0x394
    void*    mp398;                     // +0x398
    void* volatile mp39c;               // +0x39c
    uint8_t  mb3a0;                     // +0x3a0
    uint8_t  m3a1;                      // +0x3a1
    uint8_t  m3a2;                      // +0x3a2
    uint8_t  mb3a3;                     // +0x3a3

    ~cTribeModeStrategy_s00cd_7d90();
};

// @ 0x00cd7d90
cTribeModeStrategy_s00cd_7d90::~cTribeModeStrategy_s00cd_7d90()
{
    // volatile prologue stores: the retail destructor writes all five vtables
    // before it starts loading members (a plain store pair lets cl sink the
    // later base-vtable stores below them)
    *(void* volatile*)&mpVtbl0 = (void*)VT_1477668;
    *(void* volatile*)&mpVtbl1 = (void*)VT_1477648;
    *(void* volatile*)&mpVtbl2 = (void*)VT_1477640;
    *(void* volatile*)&mpVtbl3 = (void*)VT_14775f0;
    *(void* volatile*)&mpVtbl4 = (void*)VT_14775e8;

    void* first = mp39c;
    if (first) Release1(first);
    if (mp398) Release1(mp398);
    if (mp394) Release2(mp394);

    // record vector at +0x304: destroy the elements, then release its storage
    mVec304.DestroyRange_00cd6fd0(mVec304.mpBegin, mVec304.mpEnd);
    {
        void* p = mVec304.mpBegin;
        if (p && ((uint32_t*)p)[-1] != 0)
            operator_delete_00f47380(p);
    }

    // the two twenty-slot arrays of refcounted pointers; the second one starts
    // exactly where the first ends (+0x2a8), so both walks begin one past their
    // array and pre-decrement
    void** pEnd = ma2a8 + 20;
    if (mp2f8) Release2(mp2f8);
    for (int i = 19; i >= 0; --i) {
        --pEnd;
        if (*pEnd) Release1(*pEnd);
    }
    void** qEnd = ma258 + 20;
    for (int i = 19; i >= 0; --i) {
        --qEnd;
        if (*qEnd) Release1(*qEnd);
    }

    if (mp254) Release1(mp254);
    if (mp250) Release1(mp250);

    if (mp240) {
        void* sub = (char*)mp240 + 0x3c;
        Release1(sub);
    }

    if (mp1cc) {
        void* h = mp1cc;
        mp1cc = 0;
        FUN_00571db0(h, mp1d0, mp1d4, mp1d8, mp1dc);
    }

    if (mp1c8) Release2(mp1c8);

    mTimer2.dtor_00b638b0();

    if (mp19c) Release1(mp19c);

    // allocator-backed container at +0xa8
    PoolContainer* container = &mContA8;
    container->DestroyRange_00a1b6c0(container->mpBegin, container->mCapacity);
    {
        void* p = container->mpBegin;
        container->mSize = 0;
        if (container->mCapacity > 1 && p != container->mpInline) {
            if ((uint32_t)p < (uint32_t)container->mpPoolBegin || (uint32_t)p >= (uint32_t)container->mpPoolEnd) {
                operator_delete_00f47380(p);
            } else {
                *(void**)p = container->mpFreeList;
                container->mpFreeList = p;
            }
        }
    }

    mObj94.dtor_00ae6970();

    if (mp7c) operator_delete_00f47380(mp7c);

    mTimer.dtor_00b638b0();

    mObj40.dtor_00cd57d0();

    // vector at +0x2c
    mVec2c.DestroyRange_01023030(mVec2c.mpBegin, mVec2c.mpEnd);
    {
        void* p = mVec2c.mpBegin;
        if (p && ((uint32_t*)p)[-1] != 0)
            operator_delete_00f47380(p);
    }

    ((Obj0c*)((char*)this + 0x0c))->dtor_00b5b9a0();

    mpVtbl2 = VT_13eb394;
    mpVtbl1 = VT_13eb938;
    mpVtbl0 = VT_13eb938;
}

// @ 0x00cd8e70
namespace SP {
void __fastcall FUN_00cd8e70(cTribeModeStrategy_s00cd_8e70* self)
{
    cTribe_s00cd_8e70* tribe = NounManager_s00cd_8e70()->GetPlayerTribe();
    void* profile = FUN_00401090_s00cd_8e70()->GetAvatarProfile();
    uint32_t recordCount = (uint32_t)(self->mpRecordEnd - self->mpRecordBegin);
    uint32_t found = 0;
    CreatureList* list = ((CreatureList* (__thiscall*)(cTribe_s00cd_8e70*))
        ((void**)tribe->mpVtable)[0x90 / 4])(tribe);
    CreatureList* listEnd = ((CreatureList* (__thiscall*)(cTribe_s00cd_8e70*))
        ((void**)tribe->mpVtable)[0x90 / 4])(tribe);
    uint32_t creatureCount = (uint32_t)(listEnd->mpEnd - listEnd->mpBegin);
    for (uint32_t i = 0; i < creatureCount; ++i) {
        cSPCreatureBase_s00cd_8e70* c = list->mpBegin[i];
        if (found < recordCount) {
            TribeRecord* rec = self->mpRecordBegin + found;
            while (found < recordCount) {
                if (rec->mpProfile == profile) {
                    uint32_t t;
                    t = c->mNameBegin;    c->mNameBegin = rec->mNameBegin;    rec->mNameBegin = t;
                    t = c->mNameEnd;      c->mNameEnd = rec->mNameEnd;        rec->mNameEnd = t;
                    t = c->mNameCapacity; c->mNameCapacity = rec->mNameCapacity; rec->mNameCapacity = t;
                    break;
                }
                ++found;
                ++rec;
            }
        }
        if (c->mNameBegin == c->mNameEnd) {
            uint32_t tmp[3] = { 0, 0, 0 };
            FUN_004010a0(tmp, 0x51aa76bb);
            uint32_t* s = (uint32_t*)FUN_005ecf80(tmp, 0x51aa76bb);
            s[1] = s[0];                       // eastl::wstring::assign(begin, end)
            if (tmp[0] != 0) FUN_00f47380((void*)tmp[0]);
        }
    }

    SelSet set;
    set.Initialize();
    {
        void* pos = ((void* (__thiscall*)(cTribe_s00cd_8e70*))
            ((void**)tribe->mpVtable)[0x4c / 4])(tribe);
        Vector3_s00cd_8e70* v = ((Vector3_s00cd_8e70* (__thiscall*)(void*))
            (*(void***)*(void**)pos)[0]) (pos);
        (void)v;
    }
    TribeRecord* rec = self->mpRecordBegin;
    uint32_t remaining = recordCount;
    while (remaining != 0) {
        --remaining;
        if (rec->mpProfile != profile) {
            cSPCreatureBase_s00cd_8e70* c = (cSPCreatureBase_s00cd_8e70*)0;
            (void)c;
        }
        ++rec;
    }
    (void)set;
}
}  // namespace SP

// @ 0x00cd91b0
namespace SP {
uint32_t cTribeModeStrategy_s00cd_8e70::GetSelectedCreatureCount()
{
    SelSet set;
    GetSelectedCreatureSet(&set);
    return set.mCount;
}
}  // namespace SP

// @ 0x00cd91e0
namespace SP {
TribeSub* TribeSub::Init(int arg1, int arg2)
{
    FixedPoolDesc desc;
    desc.m00[0] = 0;
    desc.Init(&mPoolBegin, 0x60, 0xc, 4, 0);
    Configure(arg1, arg2, arg2, arg2, arg2, this);
    m10 = 10000.0f;
    m14 = 2.0f;
    m18 = 0;
    uint32_t n = PoolSize(m0c);
    if (m08 < n) GrowTo(n);
    return this;
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

// @ 0x00cd92f0
namespace SP {
uint8_t __fastcall FUN_00cd92f0(void** self, void* range, const uint32_t* str)
{
    uint8_t ok = 1;
    if (str[0] != str[1]) {
        uint32_t tmp[3];
        if (range == 0) {
            tmp[0] = tmp[1] = tmp[2] = 0;
        } else {
            FUN_005ecf80(tmp, (uint32_t)range);
        }
        void* text = (tmp[0] != 0) ? (void*)tmp[0] : (void*)0x013f6254;
        ((void (__thiscall*)(void*, void*))(*(void***)self)[0])(self, text);
        for (uint8_t* it = (uint8_t*)str[0]; it != (uint8_t*)str[1]; it += 8) {
            ok = 0;
        }
        ((void (__thiscall*)(void*, void*))(*(void***)self)[1])(self, text);
        if (tmp[0] != 0) FUN_00f47380((void*)tmp[0]);
    }
    return ok;
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

// @ 0x00cd9490
namespace SP {
void Vec16::InsertOne(Elem16_s00cd_8e70* pos, Elem16_s00cd_8e70* v)
{
    if (mpEnd != mpCapacity) {
        if (pos <= v && v < mpEnd) v += 1;
        if (mpEnd) {
            mpEnd->mpVtable = (void*)0x014774c4;
            mpEnd->mp04 = mpEnd[-1].mp04;
            mpEnd->mp08 = mpEnd[-1].mp08;
            if (mpEnd->mp08) ((void (__thiscall*)(void*))(*(void***)mpEnd->mp08)[0])(mpEnd->mp08);
            mpEnd->mb0c = mpEnd[-1].mb0c;
        }
        FUN_00cd5af0(pos, mpEnd - 1, mpEnd);
        pos->mp04 = v->mp04;
        if (v->mp08 != pos->mp08) {
            if (v->mp08) ((void (__thiscall*)(void*))(*(void***)v->mp08)[0])(v->mp08);
            pos->mp08 = v->mp08;
        }
        pos->mb0c = v->mb0c;
        mpEnd += 1;
        return;
    }
    uint32_t n = (uint32_t)(mpEnd - mpBegin);
    uint32_t cap = (n == 0) ? 1 : n * 2;
    Elem16_s00cd_8e70* buf = (Elem16_s00cd_8e70*)FUN_00f40000(cap * 0x10);
    Elem16_s00cd_8e70* p = (Elem16_s00cd_8e70*)FUN_00cd5a40((Elem16_s00cd_8e70*)mpBegin, pos, buf);
    FUN_00cd4540((Elem16_s00cd_8e70*)mpBegin, pos, buf);
    if (p) {
        p->mpVtable = (void*)0x014774c4;
        p->mp04 = v->mp04;
        p->mp08 = v->mp08;
        if (p->mp08) ((void (__thiscall*)(void*))(*(void***)p->mp08)[0])(p->mp08);
        p->mb0c = v->mb0c;
    }
    Elem16_s00cd_8e70* q = (Elem16_s00cd_8e70*)FUN_00cd5a40(pos, mpEnd, p + 1);
    FUN_00cd4540(pos, mpEnd, p + 1);
    if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
    mpBegin = buf;
    mpEnd = q;
    mpCapacity = buf + cap;
}
}  // namespace SP

// @ 0x00cd9660
namespace SP {
void __fastcall FUN_00cd9660(int arg1)
{
    cTribe_s00cd_8e70* tribe = NounManager_s00cd_8e70()->GetPlayerTribe();
    cTribeModeStrategy_s00cd_8e70* self = gpTribeModeStrategy;
    TribeSub* sub = &self->mSub;
    (void)sub;
    if (arg1 == 0) return;
    if (!FUN_0064f350(0x01581288, 0x1ccfdbe6, 0)) return;
}
}  // namespace SP

// @ 0x00cd9760
namespace SP {
void FUN_00cd9760()
{
    cTribe_s00cd_8e70* tribe = NounManager_s00cd_8e70()->GetPlayerTribe();
    (void)tribe;
    uint32_t recipe = 0;
    uint32_t count = 0, list = 0;
    GetPropertyAsUint32Array(0x01581288, recipe, &count, &list);
}
}  // namespace SP

// @ 0x00cd98e0
namespace SP {
void __fastcall FUN_00cd98e0(uint32_t index)
{
    uint32_t count = 0;
    uint32_t list = 0;
    if (gpTribeModeStrategy->m19c == 0) return;
    if (!GetPropertyAsUint32Array(0x01581288, 0x895b917a, &count, &list)) return;
    if (count == 0 || index >= count) return;
    for (uint32_t n = *(uint32_t*)(list + index * 4); n != 0; --n) {
        FUN_00f47380((void*)n);
    }
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

// @ 0x00cd9da0
void FUN_00cd9da0()
{
    cMotiveTuning_Init((cMotiveTuning*)0x01687A00, (int)0xF71FA311u);
    for (int i = 0; i < 4; ++i) {
        float v = FUN_00ce68f0(i);
        (void)v;
    }
    void* gtm = GameTimeManager();
    FUN_00b316d0();
    (void)gtm;

    // install the tribe trigger configs
    void* in = GameInputManager_s00cd_9da0();
    VC3(in, 0x10, (int)"TriggerConfigTribeGame", 0, 1);
    const char* wasd = "TriggerConfigWASD";
    void* ml = FUN_0067de40();
    if (FUN_006ab760(ml, L"fr-fr") != 0)
        wasd = "TriggerConfigWASD_fr-fr";
    in = GameInputManager_s00cd_9da0();
    VC3(in, 0x10, (int)wasd, 0, 0);

    unsigned name = FNVHash("Planet_Tribe", 0x811C9DC5u);
    VC1((void*)gTribeConfigName, 0x30, (int)(size_t)name);

    // create + configure the tribe planet model
    void* model = FUN_0067ddc0_s00cd_9da0();
    if (model != 0) {
        VC1(model, 0x10, (int)gTribeConfigName);
        VC2(model, 0x18, (int)GonzagoModelWorld(), 3);
        void* mm = ModelManager();
        void* state = VC1R(mm, 0x1C, (int)0x3FBAE24);
        if (state != 0)
            VC2(model, 0x18, (int)state, 0);
        VC1(model, 0x1C, (int)FUN_0067de00(0x20007));
        VC1(model, 0x28, 1);
    }

    void* cam = GetCameraCtl();
    *(float*)((char*)cam + 0x380) = gTribeF0;
    *(int*)((char*)cam + 0x384) = 0x3E9;
    void* planet = PlanetModel();
    FUN_00b81720();
    (void)planet;

    void* gd = SetGameDataOwner2();
    if (gd != 0) {
        void* v = VC0R((char*)gd + 0x120, 0x2C);
        FUN_00b146a0(cam, 1, 1, v);
    }
    FUN_00b10760(cam, 0.0f, 0.0f, 0.0f);
    FUN_00b11870(cam, (int)0xCF0A771B);
    FUN_00b84a60(0, 0xd);
}

// @ 0x00cda370
void cTribeModeStrategy_s00cd_9da0::UpgradePlayerTribe()
{
    void* sphere = GetCurrentTerrainSphere();
    void* gd = SetGameDataOwner2();
    int tier = 0;
    if (gd != 0) {
        FUN_00a1ad10(gd);
        uint32_t arr = 0, n = 0;
        if (GetPropertyAsUint32Array(gd, gTribePropId, &arr, &n, 0) != 0) {
            int target = (int)*(float*)((char*)sphere + 0x10F0);
            int count = (int)n;
            tier = 0;
            for (int i = 0; i < count; ++i) {
                if ((unsigned)target >= ((unsigned*)arr)[i]) {
                    tier = i;
                    break;
                }
            }
        }
        FUN_00ff03b0(gd, tier);
    }

    if (sphere != 0) {
        if (gd == 0)
            return;
        FUN_00c79f00(sphere, (int)0x575E6E1, 1);
        FUN_00c79f00(sphere, (int)0x575E6E2, 1);
        FUN_00c79f00(sphere, (int)0x575E6E3, 1);
    }
}

// @ 0x00cdab10
void cTribeModeStrategy_s00cd_ab10::FUN_00cdab10()
{
    MOPS((u8*)this + 0x58)->FUN_00bc3110();     // stop the goal timer

    void* noun = FUN_00b3d300();
    void* tribe = MOPS(noun)->FUN_00bfc5f0();
    if (tribe == 0)
        return;

    Rec16* end = mpHistEnd;
    if (mpHistBegin == end)
        return;
    Rec16* last = end - 1;
    if (last->mB_0c != 0)
        return;
    last->mB_0c = 1;

    u32 n = (u32)((u8*)end - (u8*)mpHistBegin) >> 4;
    FUN_00cd98e0(n);
    FUN_00cd3f20(n);

    u32 goalId = (u32)last->mU_04;
    void* tribeObj = last->mpObj;
    GameData* gd = (GameData*)MOPS(tribe)->FUN_00c90460();
    if (gd == 0)
        return;

    gP_0169b41c->mpObj = (tribeObj != 0) ? tribeObj : tribe;

    u32 segCount = (u32)((u8*)gd->mpEnd - (u8*)gd->mpBegin) >> 2;

    if (goalId == 1) {
        void* seg = (tribeObj != 0) ? FUN_00b6f0c0(((u32*)tribeObj)[0x8d]) : (void*)0x0157ef60;
        MOPS(gd)->FUN_00c8dc10(0, seg);
        void* ctrl = FUN_00675250(0x8aa440ab, 1);
        MOPS(ctrl)->FUN_00676e90(0x8aa440ab, 1);
        if (tribeObj != 0) {
            void* msg = FUN_0067dcc0();
            ((void (__thiscall*)(void*, u32, u32, u32))VT(msg)[0x14 / 4])(msg, 0x6579712, 0x2ab05c28, 0);
            void* g = MOPS(FUN_00b3d300())->FUN_00bfc5f0();
            void* slot = MOPS(tribeObj)->FUN_00c8e820();
            FUN_00e398e0(0x2a4cbb17, (u8*)slot + 0x504);
            void* list = ((void* (__thiscall*)(void*))VT(tribeObj)[0xbc / 4])(tribeObj);
            u32* lb = *(u32**)list;
            u32* le = *(u32**)((u8*)list + 4);
            for (u32* it = lb; it != le; it++) {
                void* ent = (void*)*it;
                u32 ds = ((u32 (__thiscall*)(void*))VT(ent)[0x58 / 4])(ent);
                if (ds != 10) {
                    u32 dmg = ((u32 (__thiscall*)(void*))VT(ent)[0x48 / 4])(ent);
                    if (dmg != 2) {
                        // feed the combatant position back into the goal record
                        (void)segCount;
                    }
                }
            }
        }
    } else if (goalId == 2) {
        void* seg = (tribeObj != 0) ? FUN_00b6f0c0(((u32*)tribeObj)[0x8d]) : (void*)0x0157ef6c;
        MOPS(gd)->FUN_00c8dc10(1, seg);
        void* ctrl = FUN_00675250(0x7859c5da, 1);
        MOPS(ctrl)->FUN_00676e90(0x7859c5da, 1);
        if (tribeObj != 0) {
            void* msg = FUN_0067dcc0();
            ((void (__thiscall*)(void*, u32, u32, u32))VT(msg)[0x14 / 4])(msg, 0x6579712, 0x2ab05c28, 0);
            void* g = MOPS(FUN_00b3d300())->FUN_00bfc5f0();
            void* slot = MOPS(tribeObj)->FUN_00c8e820();
            FUN_00e398e0(0xf9f6f3dd, (u8*)slot + 0x504);
        }
    }

    // post the totem-pole trigger / action pair
    void* trig = FUN_00b3d4d0_s00cd_ab10();
    void* handle = MOPS(trig)->FUN_00ae0930(0x14777e4, 1, 1, 0, 0, 0);
    u8 action[0x20];
    MOPS(&action)->FUN_00ad7a30((u8*)tribe + 0x34, handle);
    void* trig2 = FUN_00b3d4d0_s00cd_ab10();
    MOPS(trig2)->FUN_00ae09b0(0xa69cf7a6, &action);
    MOPS(&action)->FUN_00ad7ad0();
    u8 ctx[0x20];
    void* trig3 = FUN_00b3d4d0_s00cd_ab10();
    MOPS(trig3)->FUN_00adde90(0x3468d1e3, &ctx, handle);

    TribeData_s00cd_ab10* td = (TribeData_s00cd_ab10*)tribe;
    if (td->mpBegin != td->mpEnd) {
        u32 cnt = (u32)(td->mpEnd - td->mpBegin);
        u32* item = (u32*)td->mpIndexArray[cnt - 1];
        item[1] &= 0xfffffffe;
    }

    void* t2 = FUN_00b3d310(tribe, 1);
    MOPS(t2)->FUN_00b48770(1);
    FUN_00cd9660(tribeObj);
}

// @ 0x00cdafb0
void cVec16::FUN_00cdafb0(Rec16* src)
{
    Rec16* end = mpEnd;
    if (end < mpCap) {
        mpEnd = end + 1;
        if (end != 0) {
            end->mpVtbl = (void*)g_14774c4;
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
        rec->mpVtbl = (void*)g_14774c4;
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
            end->mpBegin = (void*)g_1667bac;
            end->mpEnd   = (void*)g_1667bac;
            end->mpCap   = (void*)g_1667bae;
            end->mU_14 = 0;
            end->mU_18 = 0;
        }
    } else {
        Rec1c tmp;
        tmp.mpBegin = (void*)g_1667bac;
        tmp.mpEnd   = (void*)g_1667bac;
        tmp.mpCap   = (void*)g_1667bae;
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
struct PtrVecView_s00cd_ba90 {       // the vector at PtrVec+4
    void** mpBegin;
    void** mpEnd;
    u32 size() const { return (u32)(mpEnd - mpBegin); }
    void* operator[](u32 i) const { return mpBegin[i]; }
};
void cTribeModeStrategy_s00cd_ab10::FUN_00cdba90()
{
    void* ticker = FUN_00b3d330();
    void* noun = FUN_00b3d300();
    PtrVec* vec = (PtrVec*)MOPS(noun)->FUN_00b21340((void*)FUN_00cd7d10,
                                                     (void*)FUN_00d3d420,
                                                     (void*)FUN_00accbb0,
                                                     (void*)FUN_00b1e500,
                                                     (void*)g_18c6d19);
    const PtrVecView_s00cd_ba90& items = *(const PtrVecView_s00cd_ba90*)&vec->mpBegin;
    u32 count = items.size();
    for (u32 i = 0; i < count; i++) {
        void* planner = *(void**)((char*)items[i] + 0x290);
        if (planner != 0) {
            ((void (__thiscall*)(void*, void*))VT(ticker)[0x54 / 4])(ticker, planner);
            MOPS(planner)->FUN_00ce0a20();
        }
    }
}

// @ 0x00cdbb10
int SP::cTribeModeStrategy_s00cd_bb10::FUN_00cdbb10()
{
    ISimTicker* ticker = SP::SimTicker_s00cd_bb10();

    Simulator::SimSingleton100* sim = g_pSimSingleton_0169b054;
    if (!sim)
    {
        sim = new ("Simulator/SimSingleton", 0, 0, 0, 0) Simulator::SimSingleton100();
        g_pSimSingleton_0169b054 = sim;
    }
    ((ISimBase*)sim)->v7();

    sim = g_pSimSingleton_0169b054;
    if (!sim)
    {
        sim = new ("Simulator/SimSingleton", 0, 0, 0, 0) Simulator::SimSingleton100();
        g_pSimSingleton_0169b054 = sim;
    }
    ticker->v20(sim);

    cCitySimulator_s00cd_bb10* city = g_pCitySimulator_0167a690;
    if (!city)
    {
        city = new ("Simulator/SimSingleton", 0, 0, 0, 0) cCitySimulator_s00cd_bb10();
        g_pCitySimulator_0167a690 = city;
    }
    city->AttachSubsystems();

    city = g_pCitySimulator_0167a690;
    if (!city)
    {
        city = new ("Simulator/SimSingleton", 0, 0, 0, 0) cCitySimulator_s00cd_bb10();
        g_pCitySimulator_0167a690 = city;
    }
    ticker->v20(city);

    ((ISimBase*)FUN_00d51660_s00cd_bb10())->v7();
    ticker->v20(FUN_00d51660_s00cd_bb10());

    cTribe_s00cd_bb10* tribe = NounManager_s00cd_bb10()->GetPlayerTribe();
    if (tribe)
    {
        tribe->AddRef();

        NounManagerData* data = NounManager_s00cd_bb10()->GetGameDataVector(
            0xcd7d10, 0xd3d420, 0xaccbb0, 0xb1e500, 0x18c6d19);
        NounVector* vec = &data->mVector;
        cTribe_s00cd_bb10** begin = vec->mpBegin;
        cTribe_s00cd_bb10** end = vec->mpEnd;
        for (cTribe_s00cd_bb10** it = begin; it != end; ++it)
        {
            if (*it != tribe)
                ((IStrategyVtbl*)this)->DispatchTribe(*it);
        }

        cTerrainCursor* cursor = GetGameTerrainCursor_s00cd_bb10();
        uint32_t arg = tribe->GetSelectedThing();
        cursor->SetSelectionTarget(arg);
        return tribe->Release();
    }
    return 0;
}

// @ 0x00cdbcc0
cHut* SP::cTribeModeStrategy_s00cd_bb10::FindClosestNPCHut(uint32_t param)
{
    cGameNounManager_s00cd_bb10* nm = NounManager_s00cd_bb10();
    NounManagerData* data = nm->GetGameDataVector(
        (int)&FUN_00cd7d10, (int)&FUN_00d3d420, (int)&FUN_00accbb0, (int)&FUN_00b1e500, 0x18c6d19);
    cTribe_s00cd_bb10* tribe = FindClosestNPC(&data->mVector, param, SP::IsNonEmptyNPCTribe);
    if (tribe)
        return tribe->GetTribeHut();
    return 0;
}

// @ 0x00cdbd20
bool SP::cTribeModeStrategy_s00cd_bb10::HandleUIMessage(void* window, const UTFWinMessage& message)
{
    switch (message.mEventType) {
    case 0xd:
        if (VerbTray_HandleRebuild(window, message.mData18) == true)
            return true;
        break;
    case 0x287259f6:
        if (IsVerbTrayCommand_00d49820(message.mCommandID))
            return true;

    switch (message.mCommandID) {
    case 0x4c61b50: {
        KillSetiEffects(0x381d5506, GetAudioState());
        mToolMode = 0;
        if (mpToolUI)
            mpToolUI->SetActive(0);
        cTerrainCursor* cursor = GetGameTerrainCursor_s00cd_bb10();
        if (cursor) {
            SPVector_s00cd_bb10<cGameObjectPtr> selection;
            cursor->GetSelection(selection);
            for (cGameObjectPtr* it = selection.begin(); it != selection.end(); ++it) {
                cCreature* creature = object_cast_s00cd_bb10<cCreature>(it->mpObject);
                if (creature && creature->IsIdle_00c24560()) {
                    cAnimRequest* req = creature->mpAnimatedCreature->mQueue.Play_00bc97f0(0, 8, kAnimBlend_01486110, 0);
                    req->mAnimA = 0x55bb346;
                    req->mAnimB = 0x55bb34b;
                }
            }
        }
        return true;
    }
    case 0x36ad4a4: {
        mTimer.Stop();
        SetMode_00cd6390(0);
        if (IsToolActive_00cd4460(0x64be5ff) && !IsToolActive_00cd4460(0x56d1871))
            return true;
        cMessagePtr_s00cd_bb10 msg(new("App", 0, 0, 0, 0) cMessage_s00cd_bb10(0));
        msg->mMessageID = 0xb2699146;
        msg->mData08 = 0;
        MessageServer_s00cd_bb10()->PostMSG(msg->mMessageID, msg.mpMessage, 0, 0);
        return true;
    }
    case 0x4c61dd9: {
        KillSetiEffects(0x99a5b10f, GetAudioState());
        mToolMode = 1;
        if (mpToolUI)
            mpToolUI->SetActive(0);
        cTerrainCursor* cursor = GetGameTerrainCursor_s00cd_bb10();
        if (cursor) {
            SPVector_s00cd_bb10<cGameObjectPtr> selection;
            cursor->GetSelection(selection);
            for (cGameObjectPtr* it = selection.begin(); it != selection.end(); ++it) {
                cCreature* creature = object_cast_s00cd_bb10<cCreature>(it->mpObject);
                if (creature && creature->IsIdle_00c24560()) {
                    cAnimRequest* req = creature->mpAnimatedCreature->mQueue.Play_00bc97f0(0, 8, kAnimBlend_01486110, 0);
                    req->mAnimA = 0x55bb337;
                    req->mAnimB = 0x55bb341;
                }
            }
        }
        return true;
    }
    case 0x53f02b8: {
        cPropListFactory* factory = PropListFactory();
        cPropertyList_s00cd_bb10* list;
        factory->Create(&list);
        Variant terrain(GetTerrainSource()->GetTerrainObject());
        list->SetValue(0, terrain);
        int enable = 1;
        list->SetValue(1, Variant(enable));
        ResourceKey key;
        GetTerrainSource()->GetKey(&key, 0);
        list->SetValue(3, Variant(&key.instance));
        factory->Submit(0x1aedf1e, list, 0);
        return true;
    }
    case 0x53f02c0: {
        cPropListFactory* factory = PropListFactory();
        cPropertyList_s00cd_bb10* list;
        factory->Create(&list);
        Variant terrain(GetTerrainSource()->GetTerrainObject());
        list->SetValue(0, terrain);
        int enable = 0;
        list->SetValue(1, Variant(enable));
        ResourceKey key;
        GetTerrainSource()->GetKey(&key, 0);
        list->SetValue(3, Variant(&key.instance));
        factory->Submit(0x1aedf1e, list, 0);
        return true;
    }
    case 0x562a141:
        sToggleMinimap();
        return true;
    case 0x625cd52: {
        float amount = g_DropFoodAmount_0158133c;
        cTribe_s00cd_bb10* tribe = NounManager_s00cd_bb10()->GetPlayerTribe();
        int needed = (int)amount;
        if (tribe->GetFoodAmount() < needed) {
            UIHints()->ShowHint_0067c830(0x41e5e8bf);
            return true;
        }
        if (tribe->GetPopulation_00c8f3a0() >= tribe->GetMaxPopulation())
            return true;
        if (amount > kFoodEpsilon_01477434) {
            GetFoodSource()->Consume_00ac7d10(amount, tribe->mTimer20c, 0);
            tribe->AddFood_00c94b50(-amount);
        }
        cHut* hut = tribe->GetTribeHut();
        AutoRefCount_s00cd_bb10<IVisualEffect> effect;
        cEffectsManager_s00cd_bb10* effects = EffectsManager();
        if (effects->CreateVisualEffect(0xdb6f2233, 0, effect.AsPPTypeParam())) {
            XformMsg_s00cd_bb10 xf;
            xf.SetPosition_00571d40(hut->GetPosition());
            Vector3_s00cd_bb10 up;
            normalized_safe(&up, hut->GetPosition());
            const Vector3_s00cd_bb10& hutPos = hut->GetPosition();
            const Vector3_s00cd_bb10& tribePos = tribe->GetPosition();
            Vector3_s00cd_bb10 facing;
            normalized_safe(&facing, tribePos - hutPos);
            xf.SetRotation(Matrix3FromFacingAndUp(facing, up));
            xf.SetScale(1.0f);
            effect->SetTransform(xf);
            effect->Start(0);
        }
        KillSetiEffects(0x582f38c1, GetRecorderState());
        mbFlag3a3 = false;
        return true;
    }
    case 0x6454b47: {
        cTerrainSphere_s00cd_bb10* sphere = NounManager_s00cd_bb10()->GetCurrentTerrainSphere();
        const float& a = sphere->mf10f0;
        const float& b = sphere->mf10f4;
        const float& lo = (b < a) ? b : a;
        if (!(lo / sphere->mf10f4 >= 1.0f))
            return true;
        UIHints()->UpdateHints(1, 1);

        uint32_t sequence = 0x8133fb2e;
        switch (GetTribeOutcome_00cdba50()) {
        case 0xcac124d:
            sequence = 0x6a9f2620;
            break;
        case 0x60a78928:
            sequence = 0x2cfa39dd;
            break;
        }
        {
            ResourceKey dir = {0, 0, 0};
            ResourceKey pos = {0, 0, 0};
            PlayEndSequence_00e398e0(sequence,
                                     &NounManager_s00cd_bb10()->GetPlayerTribe()->GetRecord_00c8e820(0)->mData504,
                                     &pos, &dir, NounManager_s00cd_bb10()->GetPlayerTribe()->GetSub230()->mData4, 0, 0);
        }

        cAchievementsController* ach = AchievementsController_s00cd_bb10();
        if (ach->IsLocked_006766f0(0xb598f829))
            ach->AwardAchievement(0xb598f829);
        cAchievementData* data = ach->GetData_00675370();
        if (ach->Has_00675e80(0xa6c22573))
            data->mVisited.clear();
        else if (data->mVisited.insert_00675b60(sphere->mKey10f8).second == true)
            ach->AutoTest(0xa6c22573, 1);
        ach->AwardAchievement(0x4a7480ac);
        ach->AutoTest(0xa784ec4a, mData78);
        if (NounManager_s00cd_bb10()->GetCurrentTerrainSphere()->GetState_00c75420() == 2)
            ach->AwardAchievement(0x8d82fac1);

        g_TribeCamera_0169b2c8->PlayIntro_00cd52e0(5, g_TribeCameraPos_0169b2cc);

        ResourceKey spawn = {0, 0, 0};
        NounManager_s00cd_bb10()->GetPlayerTribe()->GetSpawnInfo_00c8eb50(&spawn);
        GetHintsB()->Set_0060d860(0x8fd1273c, &spawn);
        mpPlanner->f_00cc8aa0(0);
        mpPlanner->f_00cc93b0(0);

        cTribe_s00cd_bb10* tribe = NounManager_s00cd_bb10()->GetPlayerTribe();
        cHut* hut = tribe->GetTribeHut();
        cHut* tool = tribe->GetToolOfType(0xa);
        LayoutScripts()->SetObject_00ae09b0(0x3d7f90a, cObjectXform(&tribe->mObject120, 0));
        LayoutScripts()->SetObject_00ae09b0(0xaa227986, cObjectXform(hut, 0));
        LayoutScripts()->SetObject_00ae09b0(0x60ed02ef, cObjectXform(tool, 0));
        LayoutScripts()->Run_00ae0930("TRG2CVG_PreEditor", 1, 0, 0, 0, 0);
        LayoutScripts()->Reset_00adf390(0);

        cCreature* chief = tribe->GetChieftain();
        if (chief->mpAnimatedCreature->mModelType == 0x5ca7fa7) {
            FUN_00c0d3a0(chief);
            chief->f_00c26d10();
        }
        chief->SetEnabled(1);
        chief->f_00c0b950();
        chief->f_00c0ba10();
        sphere->mResult1104 = GetTribeOutcome_00cdba50();

        ResourceKey key = {0, 0, 0};
        if (!tribe->GetSpawnInfo_00c8eb50(&key))
            return true;
        if (!IsValidKey_006419f0(&key))
            return true;
        if (uint32_t result = NounManager_s00cd_bb10()->GetCurrentTerrainSphere()->mResult1104)
            SummarizeVehicle_00555f70(&key, result);
        MessageServer_s00cd_bb10()->SendMSG(0x73e46f6, &key, 0);
        return true;
    }
    }
        break;
    }
    return false;
}

// @ 0x00cdce40
void __fastcall CvgObj_AppendTransitionTargets(CvgObj* self, int unused, PtrVec_s00cd_c8b0* list)
{
    CvgVec* vec = &self->mTargets;
    vec->InsertRange(vec->mpBegin, vec->mpEnd);
    vec->Append();
    CvgRec* rec = vec->mpEnd - 1;
    cvg_swap(rec, self);
    rec->mHandle = FUN_00c0c1a0(self);
    rec->mId = self->mB20;

    int count = (int)(list->mpEnd - list->mpBegin);
    for (int i = 0; i < count; ++i) {
        CvgObj* o = (CvgObj*)list->mpBegin[i];
        vec->Append();
        CvgRec* e = vec->mpEnd - 1;
        cvg_swap(e, o);
        e->mHandle = FUN_00c0c1a0(o);
        e->mId = o->mB20;
        e->mF10 = ((CvgSlot80)o->mpVtbl[0x20])(o, 0, 0);
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
    cGameNounManager_s00cd_d500* pMgr = NounManager_s00cd_d500();
    PtrVec_s00cd_d500<cNoun>* pItems =
        &((NounVecOut<cNoun>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e))->mItems_04;

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

// @ 0x00cddcf0
void FUN_00cddcf0()
{
    struct HotSpotQuery { float mMaxDistance; Vec3 mPoint; };
    HotSpotQuery query;
    query.mMaxDistance = gHotSpotDistance;

    NounVecOut<cNoun>* pVec =
        (NounVecOut<cNoun>*)NounManager_s00cd_d500()->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
    cNoun** pIt = pVec->mItems_04.mpBegin;
    cNoun** const pEnd = pVec->mItems_04.mpEnd;
    while (pIt != pEnd) {
        cNoun* pNoun = *pIt;
        if (pNoun->mNounType_108 == 0x57f09e5e) {
            cPlanetModel* pModel = (cPlanetModel*)GetPlanetModel();
            if (pModel->RayCast(pNoun->mPlacement_034.GetPosition(), query.mMaxDistance,
                                &query.mPoint, 1.0f, 1, 5))
                cTribe_SetupHotSpot(&query.mPoint, 1);
        }
        ++pIt;
    }
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
