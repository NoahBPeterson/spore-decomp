// Slice s00cf7dc0 -- SP::cCivModeStrategy sim hand-off / civ-mode cluster
// (0x00cf7dc0..0x00cf8ba0, 8 functions) plus the pre-existing 0x00cf86d0 helper.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Relocations (calls, globals, vtable targets) are masked by the matcher, so a
// callee's symbol identity does not affect byte matching; only the calling
// convention and the argument count/shape do.
#include "types.h"
#include <math.h>
#pragma warning(disable : 4291)

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

struct V3 { float x, y, z; };

// Message handler sub-object at +0x24 of the strategy.
struct MsgSub { uint32_t mPad[(0xe0 - 0x24) / 4]; };

// One 0x64-byte entry of the sim's creature list (cSimMode200).
struct SimElem {
    void*    mpObj_0;
    uint32_t mPad0[(0x20 - 4) / 4];
    int      miField_20;
    uint8_t  mbFlag_24;
    uint8_t  mbFlag_25;
    uint16_t mPad1;
    int      miField_28;
    uint32_t mPad2[(0x64 - 0x2c) / 4];
};

struct Strat;
struct Civ;
struct Noun;
struct Cfg;
struct GTM;
struct TriggerMgr;
struct UIHints;
struct CamTarget;
struct CivList;
struct CivEntry;
struct City;
struct Sphere;
struct Obj;
struct Other;
struct Preload4;
struct App;
struct CProp;
struct PosSub;
struct PosObj;
struct RandomLCG;

// --- accessors -------------------------------------------------------------
Noun*       __cdecl SP_NounManager();        // 0x00b3d300
Cfg*        __cdecl SP_ConfigManager();      // 0x0067dd30
GTM*        __cdecl SP_GameTimeManager();    // 0x00b3d380
TriggerMgr* __cdecl GetTriggerMgr();         // 0x00b3d4d0
void*       __cdecl SP_PlanetModel();        // 0x00b3d350

// --- free helpers ----------------------------------------------------------
void* __cdecl SP_MessageServer();            // 0x0067dcc0
void* __stdcall FUN_0067caf0(V3, void*, int, float, float, float, int, int); // 0x0067caf0
void* __cdecl FUN_00e3c7c0(unsigned, void*, void*, void*, int, int, int);  // 0x00e3c7c0
char  __cdecl FUN_006419f0(void*);           // 0x006419f0
void  __cdecl FUN_00555f70(void*, void*);    // 0x00555f70
void* __cdecl FUN_00b993c0(void*);           // 0x00b993c0
int   __cdecl FUN_00bef920(int);             // 0x00bef920

// --- messaging server (vtable slots 0x14 = Post, 0x20 = Reg) ----------------
struct MsgServerSrv {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04();
    virtual void Post(unsigned, void*, int);   // slot 5 (0x14)
    virtual void m06(); virtual void m07();
    virtual void Reg(void*, unsigned);         // slot 8 (0x20)
};

// --- globals (masked relocations) ------------------------------------------
struct RandomLCG {
    unsigned __thiscall RandomUint32Uniform(unsigned range);   // 0x00a68fb0
    float    __thiscall RandomDouble();                        // 0x009360d0
};

Strat*       DAT_0169d2b8;                   // 0x0169d2b8
void*        DAT_015fd918;                   // 0x015fd918 app-properties pointer
V3           DAT_01581b90;                   // 0x01581b90 (x/y/z at b90/b94/b98)
void*        DAT_01581bd8;                   // 0x01581bd8
float        DAT_013eb1bc;                   // 0x013eb1bc
float        DAT_0169cc48;                   // 0x0169cc48
float        DAT_0169cc4c;                   // 0x0169cc4c
float        DAT_0169cc50;                   // 0x0169cc50
float        DAT_0169cc54;                   // 0x0169cc54
RandomLCG    g_cRandomGlobal;                // 0x01601760

// --- class layouts ---------------------------------------------------------
struct CivList {
    void** mpBegin;                          // +0x00
    void** mpEnd;                            // +0x04
};

struct CivEntry {
    void __thiscall FUN_00bf59d0();          // 0x00bf59d0
};

struct Other {
    void __thiscall FUN_00ceae70(void*);     // 0x00ceae70
};

struct Obj {
    virtual void  v0(); virtual void  v1(); virtual void  v2();
    virtual void* Query(int key);            // slot 3 (0x0c)
    virtual void  v4(); virtual void  v5(); virtual void  v6(); virtual void  v7();
    virtual void  v8(); virtual void  v9(); virtual void  v10(); virtual void  v11();
    virtual void* Get();                     // slot 12 (0x30)
    void __thiscall FUN_00be34e0(void*);     // 0x00be34e0
};

struct Cfg {
    virtual void c0();  virtual void c1();  virtual void c2();  virtual void c3();
    virtual void c4();  virtual void c5();  virtual void c6();  virtual void c7();
    virtual void c8();  virtual void c9();  virtual void c10(); virtual void c11();
    virtual unsigned GetFlag(unsigned int key);  // slot 12 (0x30)
};

struct GTM {
    void __thiscall IncPauseGate(int gate);  // 0x00b32220
};

struct TriggerMgr {
    void __thiscall PostAction(int id, void* target, int a);          // 0x00ae09b0
    void __thiscall PostTrigger(const char* name, int a, int b,
                                int c, int d, int e);                 // 0x00ae0930
};

struct UIHints {
    void __thiscall Apply();                 // 0x0067aaf0
};

struct Sphere {
    uint32_t mPad0[0x1108 / 4];
    int      miField_1108;                   // +0x1108
    int __thiscall FUN_00c75420();           // 0x00c75420
};

struct CivPair { int mFirst; int mSecond; };

struct Civ {
    float __thiscall FUN_00bf1880(int key);  // 0x00bf1880
    void* __thiscall FUN_00bef950();         // 0x00bef950
    void  __thiscall FUN_00bf9790();         // 0x00bf9790
    uint32_t mPad0[0x40 / 4];
    int      miField_0x40;                   // +0x40
    uint32_t mPad1[(0xb0 - 0x44) / 4];
    CivPair  mPair_0xb0;                     // +0xb0
};

struct Noun {
    Civ*     __thiscall GetPlayerCivilization();    // 0x00b25fb0
    Sphere*  __thiscall GetCurrentTerrainSphere();  // 0x00f67d90
    CivList* __thiscall GetCivilizationList();      // 0x00b25ca0
    City*    __thiscall FUN_00b25c30();             // 0x00b25c30
};

struct City {
    void* __thiscall GetCityHall();                            // 0x00bd9b40
    void  __thiscall FUN_00bd7f70(void* outVec, void* outFloat); // 0x00bd7f70
};

struct CamTarget {
    CamTarget() {}
    CamTarget(void* target);                 // 0x00ad7a30
    ~CamTarget();                            // 0x00ad7ad0
    void  __thiscall init(void* v, void* p); // 0x00ad79d0
    void* __thiscall getPtr();               // 0x00ad7b70
    uint32_t mPad[0x24 / 4];
    float    mfField_0x24;                   // +0x24
};

struct Preload4 {
    uint32_t mField;
    Preload4();                              // 0x007cf5d0
};

struct App {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8();
    virtual char Lookup(unsigned key, void** out);   // slot 9 (0x24)
};

struct CProp {
    uint16_t mPad0[0x12 / 2];
    uint16_t mType_0x12;                     // +0x12
    bool* __thiscall GetBool();              // 0x0041e920
};

struct PosSub {
    virtual void p0();  virtual void p1();  virtual void p2();  virtual void p3();
    virtual void p4();  virtual void p5();  virtual void p6();  virtual void p7();
    virtual void p8();  virtual void p9();  virtual void p10();
    virtual float* GetPos();                 // slot 11 (0x2c)
};

struct PosObj {
    uint32_t mPad0[0x34 / 4];
    PosSub   mPos_0x34;                      // +0x34
};

struct PlanetModel2 {
    V3* __thiscall DirectionToSurfacePosition(V3* a, V3* b);  // 0x00b815a0
};

struct Strat {
    Strat* __thiscall ctor();                            // 0x00cee130
    char   __thiscall Shutdown(int a);                   // 0x00cf7dc0
    void   __thiscall OnTechLevelUpgradeButtonPress();   // 0x00cf8160
    char   __thiscall FUN_00cf84a0();                    // 0x00cf84a0
    void   __thiscall FUN_00cf8560();                    // 0x00cf8560
    void   __thiscall NotifyDataDestroyed(void* p);      // 0x00cf8860
    char   __thiscall HasCivTutorialOccurred(int id);    // 0x00cf7830
    void   __thiscall MarkCivEventAsOccurred(int id);    // 0x00cf77f0

    uint32_t  mPad0[0x24 / 4];
    MsgSub    mSub_0x24;                     // +0x24 (message-handler sub-object)
    uint8_t   mbFlag_0xe0;                   // +0xe0
    uint8_t   mPad1[0x0b];                   // +0xe1..0xeb
    Other*    mpOther_0xec;                  // +0xec
    uint32_t  mPad2[0x08 / 4];               // +0xf0..0xf8
    int       miField_0xf8;                  // +0xf8
    uint32_t  mPad3[(0x110 - 0xfc) / 4];
    void*     mpPreload_0x110;               // +0x110
    void*     mpPreload_0x114;               // +0x114
    uint32_t  mPad4[(0x120 - 0x118) / 4];
    uint8_t   mbFlag_0x120;                  // +0x120
    uint8_t   mbFlag_0x121;                  // +0x121
};

// --- sim singletons (shared with 0x00cf86d0) -------------------------------
struct cVehTicker {                          // 0x58 bytes, ctor 0x00dc7d70 (0x01699ab8)
    uint32_t mData[0x58 / 4];
    cVehTicker* __thiscall ctor();           // 0x00dc7d70
    void __thiscall FUN_00dcc2c0();          // 0x00dcc2c0
    void __thiscall FUN_00dced90();          // 0x00dced90
};
cVehTicker* DAT_01699ab8;                    // 0x01699ab8

struct cSimMode200 {                         // 0xc8 bytes, ctor 0x00ae5c30 (0x0167a60c)
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual void Slot1c();                   // slot 7  (0x1c)
    virtual void Slot20();                   // slot 8  (0x20)
    virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19();
    virtual void Slot50(void*);              // slot 20 (0x50)
    virtual void Slot54(void*);              // slot 21 (0x54)
    uint32_t  mPad0[0x0c / 4];               // +0x04..0x10
    uint8_t   mbFlag_0x10;                   // +0x10
    uint8_t   mPad1[0x03];                   // +0x11..0x14
    SimElem*  mpBegin_0x14;                  // +0x14
    SimElem*  mpEnd_0x18;                    // +0x18
    void*     mpCap_0x1c;                    // +0x1c
    uint32_t  mPad2[(0xc8 - 0x20) / 4];
    cSimMode200* __thiscall ctor();          // 0x00ae5c30
};
cSimMode200* DAT_0167a60c;                   // 0x0167a60c

struct cSimMode64 {                          // 0x40 bytes, ctor 0x00ae6a70 (0x0167a690)
    virtual void v0();
    uint32_t mData[(0x40 - 4) / 4];
    cSimMode64* __thiscall ctor();           // 0x00ae6a70
    void __thiscall FUN_00ae6570();          // 0x00ae6570
    void __thiscall AttachSubsystems();      // 0x00ae7350
};
cSimMode64* DAT_0167a690;                    // 0x0167a690

struct cSimTicker {                          // 0x00b3d330
    virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
    virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
    virtual void t08(); virtual void t09(); virtual void t10(); virtual void t11();
    virtual void t12(); virtual void t13(); virtual void t14(); virtual void t15();
    virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19();
    virtual void Slot50(void* p);            // slot 20 (0x50)
    virtual void Slot54(void* p);            // slot 21 (0x54)
};
cSimTicker* __cdecl SP_SimTicker();          // 0x00b3d330

struct cSimModeOwner {                       // the 0x00cf86d0 receiver
    void __thiscall FUN_00cf86d0();          // 0x00cf86d0
    uint32_t pad00[0xe0 / 4];
    bool     mbPending;                      // +0xe0
};

// ===========================================================================
// @ 0x00cf7dc0
// SP::cCivModeStrategy::Shutdown -- register the strategy with every civ-mode
// message id, allocate the effects-preload pair, and read one app property.
char Strat::Shutdown(int)
{
    Strat* raw = (Strat*)operator new(1, "Simulator/cCivModeStrategy", 0, 0, 0, 0);
    DAT_0169d2b8 = raw ? raw->ctor() : 0;

    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x1a0219e);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x164b4eb);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x44f1189);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x56cfe69);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5dbc31e);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5dfb3c8);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5dfb77f);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5dfb782);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5dfb786);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5f4d02a);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x604bf01);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5668f43);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x30c11c7);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5356bb5);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x53836de);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5badd9f);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x5bff9c8);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0xb2699149);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x6270d2f);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x6417958);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x66e0e11);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x670eccd);
    ((MsgServerSrv*)SP_MessageServer())->Reg(this ? (void*)&this->mSub_0x24 : 0, 0x679c40d);

    miField_0xf8 = -1;
    mpPreload_0x110 = new ("Simulator/CivEffectsPreload", 0, 0, 0, 0) Preload4();
    mpPreload_0x114 = new ("Simulator/CivEffectsPreload", 0, 0, 0, 0) Preload4();

    void* app = DAT_015fd918;
    if (app != 0) {
        CProp* prop;
        if (((App*)app)->Lookup(0x64a44a8, (void**)&prop) != 0) {
            if (prop->mType_0x12 == 1)
                mbFlag_0x120 = *prop->GetBool();
        }
    }
    mbFlag_0x121 = 0;
    return 1;
}

// ===========================================================================
// @ 0x00cf8160
// SP::cCivModeStrategy::OnTechLevelUpgradeButtonPress
void Strat::OnTechLevelUpgradeButtonPress()
{
    Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
    if (civ != 0) {
        float f1 = civ->FUN_00bf1880(0xa35d0f5);
        float f2 = civ->FUN_00bf1880(0x3360727f);
        float f3 = civ->FUN_00bf1880(0x6aeb96a1);
        V3 a, b;
        if (f1 > f2 && f1 > f3) {
            ((Noun*)SP_NounManager())->GetCurrentTerrainSphere()->miField_1108 = 0xa35d0f5;
            a.x = a.y = a.z = 0.0f;
            b.x = b.y = b.z = 0.0f;
            FUN_00e3c7c0(0x99f0d1da,
                         (char*)((Noun*)SP_NounManager())->GetPlayerCivilization()->FUN_00bef950() + 0x504,
                         &a, &b,
                         ((Noun*)SP_NounManager())->GetPlayerCivilization()->miField_0x40, 0, 0);
        } else if (f2 > f3 && f2 > f1) {
            ((Noun*)SP_NounManager())->GetCurrentTerrainSphere()->miField_1108 = 0x3360727f;
            a.x = a.y = a.z = 0.0f;
            b.x = b.y = b.z = 0.0f;
            FUN_00e3c7c0(0xaaf6aaac,
                         (char*)((Noun*)SP_NounManager())->GetPlayerCivilization()->FUN_00bef950() + 0x504,
                         &a, &b,
                         ((Noun*)SP_NounManager())->GetPlayerCivilization()->miField_0x40, 0, 0);
        } else {
            ((Noun*)SP_NounManager())->GetCurrentTerrainSphere()->miField_1108 = 0x6aeb96a1;
            a.x = a.y = a.z = 0.0f;
            b.x = b.y = b.z = 0.0f;
            FUN_00e3c7c0(0xdca976d0,
                         (char*)((Noun*)SP_NounManager())->GetPlayerCivilization()->FUN_00bef950() + 0x504,
                         &a, &b,
                         ((Noun*)SP_NounManager())->GetPlayerCivilization()->miField_0x40, 0, 0);
        }

        V3 pos = *(V3*)((char*)civ->FUN_00bef950() + 0x504);
        if (FUN_006419f0(&pos)) {
            Sphere* sph = ((Noun*)SP_NounManager())->GetCurrentTerrainSphere();
            if (sph->miField_1108 != 0)
                FUN_00555f70(&pos, (void*)(uint32_t)sph->miField_1108);
            ((MsgServerSrv*)SP_MessageServer())->Post(0x73e46f6, &pos, 0);
        }
        civ->FUN_00bf9790();
    }

    City* city = ((Noun*)SP_NounManager())->FUN_00b25c30();
    if (city != 0) {
        void* hall = city->GetCityHall();
        CamTarget at(hall ? (void*)((char*)hall + 0x34) : 0);
        GetTriggerMgr()->PostAction(0x115fa309, &at, 0);

        V3 vec;
        float f;
        city->FUN_00bd7f70(&vec, &f);
        V3 dir;
        PlanetModel2* pm = (PlanetModel2*)SP_PlanetModel();
        V3* d = pm->DirectionToSurfacePosition(&dir, &vec);
        dir = *d;

        CamTarget cam;
        cam.init(&dir, at.getPtr());
        cam.mfField_0x24 = f;
        GetTriggerMgr()->PostAction(0xb3393b83, &cam, 0);
        GetTriggerMgr()->PostTrigger("CVG_UnlockUFO", 1, 0, 0, 0, 0);
    }
}

// ===========================================================================
// @ 0x00cf84a0
char Strat::FUN_00cf84a0()
{
    if (((Cfg*)SP_ConfigManager())->GetFlag(0x4ea96cb) > 0) {
        if (!this->HasCivTutorialOccurred(0x627160a)) {
            Civ* civ = ((Noun*)SP_NounManager())->GetPlayerCivilization();
            CivPair* pair = &civ->mPair_0xb0;
            if (pair->mFirst != pair->mSecond) {
                this->MarkCivEventAsOccurred(0x627160a);
                GTM* gtm = SP_GameTimeManager();
                gtm->IncPauseGate(0x4bf38a7);
                ((UIHints*)FUN_0067caf0(DAT_01581b90, &DAT_01581bd8, 0,
                                        DAT_013eb1bc, DAT_013eb1bc, 0.0f, 0, 0))->Apply();
                return 1;
            }
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00cf8560
void Strat::FUN_00cf8560()
{
    cSimTicker* ticker = SP_SimTicker();

    cVehTicker* veh = DAT_01699ab8;
    if (!veh) {
        veh = (cVehTicker*)operator new(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        veh = veh ? veh->ctor() : 0;
        DAT_01699ab8 = veh;
    }
    veh->FUN_00dced90();
    veh = DAT_01699ab8;
    if (!veh) {
        veh = (cVehTicker*)operator new(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        veh = veh ? veh->ctor() : 0;
        DAT_01699ab8 = veh;
    }
    ticker->Slot50(veh);

    cSimMode200* m2 = DAT_0167a60c;
    if (!m2) {
        m2 = (cSimMode200*)operator new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        m2 = m2 ? m2->ctor() : 0;
        DAT_0167a60c = m2;
    }
    m2->Slot1c();
    m2 = DAT_0167a60c;
    if (!m2) {
        m2 = (cSimMode200*)operator new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        m2 = m2 ? m2->ctor() : 0;
        DAT_0167a60c = m2;
    }
    ticker->Slot50(m2);

    cSimMode64* m64 = DAT_0167a690;
    if (!m64) {
        m64 = (cSimMode64*)operator new(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        m64 = m64 ? m64->ctor() : 0;
        DAT_0167a690 = m64;
    }
    m64->AttachSubsystems();
    m64 = DAT_0167a690;
    if (!m64) {
        m64 = (cSimMode64*)operator new(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        m64 = m64 ? m64->ctor() : 0;
        DAT_0167a690 = m64;
    }
    ticker->Slot50(m64);

    mbFlag_0xe0 = 1;
}

// ===========================================================================
// @ 0x00cf8860
// SP::cCivModeStrategy::NotifyDataDestroyed
void Strat::NotifyDataDestroyed(void* p)
{
    if (p == 0)
        return;
    Obj* a = (Obj*)((Obj*)p)->Query(0xe9cb8ba);
    if (a != 0) {
        Obj* b = (Obj*)a->Get();
        if (b != 0) {
            Obj* d = (Obj*)b->Query(0xee9b2232);
            if (d != 0)
                d->FUN_00be34e0(a);
        }
    } else {
        void* c = ((Obj*)p)->Query(0x137e8e0);
        if (c != 0 && mpOther_0xec != 0)
            mpOther_0xec->FUN_00ceae70(c);
    }
}

// ===========================================================================
// @ 0x00cf88e0
void FUN_00cf88e0()
{
    CivList* list = ((Noun*)SP_NounManager())->GetCivilizationList();
    int n = (int)(list->mpEnd - list->mpBegin);
    for (int i = 0; i < n; ++i)
        ((CivEntry*)list->mpBegin[i])->FUN_00bf59d0();
}

// ===========================================================================
// @ 0x00cf8920
void __stdcall FUN_00cf8920(float* p)
{
    cSimMode200* s = DAT_0167a60c;
    if (!s) {
        s = (cSimMode200*)operator new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        s = s ? s->ctor() : 0;
        DAT_0167a60c = s;
    }
    int n = (int)((char*)s->mpEnd_0x18 - (char*)s->mpBegin_0x14) / 0x64;

    int scale = 100;
    int t = ((Noun*)SP_NounManager())->GetCurrentTerrainSphere()->FUN_00c75420();
    if (t == 0) scale = 100;
    else if (t == 1) scale = 150;
    else if (t == 2) scale = 200;

    int repeat = 4;
    do {
        int bestIndex = -1;
        int bestScore = 0;
        if (n > 1) {
            for (int i = 1; i < n; ++i) {
                SimElem* e = DAT_0167a60c->mpBegin_0x14 + i;
                if (e->mbFlag_25 == 0)
                    continue;
                int f20 = e->miField_20;
                int countXX = 0, countX = 0, countY = 0;
                for (int j = 0; j < n; ++j) {
                    if (j == i)
                        continue;
                    SimElem* e2 = DAT_0167a60c->mpBegin_0x14 + j;
                    if (e2->miField_20 != f20)
                        continue;
                    if (e2->mbFlag_25 != 0) {
                        ++countXX;
                    } else {
                        ++countX;
                        if (e2->mbFlag_24 != 0)
                            ++countY;
                    }
                }
                int score = ((countY * scale / 100 + countXX + 1) * 10000) / (countX + 1);
                if (countX == 0)
                    score *= 10;
                PosObj* po = (PosObj*)FUN_00b993c0(e->mpObj_0);
                float* pos = po->mPos_0x34.GetPos();
                float dx = pos[0] - p[0];
                float dy = pos[1] - p[1];
                float dz = pos[2] - p[2];
                float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                score += (int)dist + (int)g_cRandomGlobal.RandomUint32Uniform(100);
                if (score > bestScore) {
                    bestIndex = i;
                    bestScore = score;
                }
            }
        }
        if (bestIndex != -1)
            DAT_0167a60c->mpBegin_0x14[bestIndex].mbFlag_25 = 0;
    } while (--repeat);
}

// ===========================================================================
// @ 0x00cf8ba0
void __stdcall FUN_00cf8ba0(int param)
{
    cSimMode200* s = DAT_0167a60c;
    if (!s) {
        s = (cSimMode200*)operator new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        s = s ? s->ctor() : 0;
        DAT_0167a60c = s;
    }
    int n = (int)((char*)s->mpEnd_0x18 - (char*)s->mpBegin_0x14) / 0x64;

    int iter = 0;
    for (;;) {
        if (n > 0) {
            for (int i = 0; i < n; ++i) {
                SimElem* e = DAT_0167a60c->mpBegin_0x14 + i;
                if (e->mbFlag_24 != 0)
                    continue;
                float f = g_cRandomGlobal.RandomDouble();
                int r;
                if (e->mbFlag_25 == 1) {
                    if (f < DAT_0169cc50)      r = 0;
                    else if (f < DAT_0169cc54) r = 1;
                    else                       r = 2;
                } else {
                    if (f < DAT_0169cc48)      r = 0;
                    else if (f < DAT_0169cc4c) r = 1;
                    else                       r = 2;
                }
                e->miField_28 = FUN_00bef920(r);
            }
        }
        if (++iter >= 30)
            return;
        if (n > 0) {
            for (int i = 0; i < n; ++i) {
                SimElem* e = DAT_0167a60c->mpBegin_0x14 + i;
                if (e->mbFlag_24 == 0 && e->miField_28 == 0 && e->miField_20 == param)
                    return;
            }
        }
    }
}

// ===========================================================================
// @ 0x00cf86d0
void cSimModeOwner::FUN_00cf86d0()
{
    cSimTicker* ticker = SP_SimTicker();
    if (!mbPending)
        return;

    cVehTicker* veh = DAT_01699ab8;
    if (!veh) {
        veh = (cVehTicker*)operator new(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        veh = veh ? veh->ctor() : 0;
        DAT_01699ab8 = veh;
    }
    veh->FUN_00dcc2c0();
    veh = DAT_01699ab8;
    if (!veh) {
        veh = (cVehTicker*)operator new(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        veh = veh ? veh->ctor() : 0;
        DAT_01699ab8 = veh;
    }
    ticker->Slot54(veh);

    cSimMode200* m2 = DAT_0167a60c;
    if (!m2) {
        m2 = (cSimMode200*)operator new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        m2 = m2 ? m2->ctor() : 0;
        DAT_0167a60c = m2;
    }
    m2->Slot20();
    m2 = DAT_0167a60c;
    if (!m2) {
        m2 = (cSimMode200*)operator new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        m2 = m2 ? m2->ctor() : 0;
        DAT_0167a60c = m2;
    }
    ticker->Slot54(m2);

    cSimMode64* m64 = DAT_0167a690;
    if (!m64) {
        m64 = (cSimMode64*)operator new(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        m64 = m64 ? m64->ctor() : 0;
        DAT_0167a690 = m64;
    }
    ticker->Slot54(m64);
    m64 = DAT_0167a690;
    if (!m64) {
        m64 = (cSimMode64*)operator new(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        m64 = m64 ? m64->ctor() : 0;
        DAT_0167a690 = m64;
    }
    m64->FUN_00ae6570();

    mbPending = false;
}
