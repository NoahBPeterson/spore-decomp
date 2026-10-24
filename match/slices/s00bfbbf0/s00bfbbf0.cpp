// Slice s00bfbbf0 -- cCivilization per-update tick (0x00bfbbf0, 1928 bytes; this = a civilization).
//
// Layout (retail, verified against the disassembly; matches the ModAPI cCivilization layout):
//   +0x4c vtable slot GetPoliticalID, +0x40 an int id, +0x6c cCultureSet, +0x8a mIsNeutral,
//   +0x8c mCommNotifiedWarning, +0x8d mHasDeveloped, +0x9c/+0xa0 mCities, +0xb0/+0xb4 mVehicles,
//   +0xc4..+0xcc mPrimaryColor (r,g,b), +0x274 mCityMusic, +0x2a0 mCurrentCommEventId,
//   +0x450 (last relationship level), +0x454 (music city), +0x460 (diplomatic-attack city).
//
// Flow: (1) fixed sub-ticks; (2) the player's civ occasionally buys a vehicle for its first city;
// (3) an AI civ updates relationships with every other civ, ticks its cities and subsystems, and,
// in game mode 0x1654c04, reacts to a changed relationship level toward the player (effect call);
// (4) every civ re-evaluates mHasDeveloped from the terrain stage and its size; (5) city music.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

struct Vec3 { float x, y, z; };
struct Color4 { float r, g, b, a; };
struct Triple {
    uint32_t a, b, c;
    Triple() { a = 0; b = 0; c = 0; }
};

struct Pos {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual Vec3* GetPosition();       // slot 11 (+0x2c): lea eax,[ecx+4]; ret
};

struct CityMusic {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual void Start(Vec3* pos);     // slot 9 (+0x24)
    virtual void Stop();               // slot 10
    virtual void Pause(bool pause);    // slot 11 (+0x2c)
    virtual void SetPosition(Vec3*);   // slot 12
    virtual int  IsPlaying();          // slot 13 (+0x34)
};

struct City {
    virtual void AddRef();             // slot 0
    virtual void Release();            // slot 1 (+4)
    char pad04[0x120 - 4];
    Pos pos120;                        // +0x120 (cSpatialObject base)

    int  GetVehicleSpecialty();        // 0xbd81d0
    void SetupVehicle(int specialty, int zero, Triple t, bool flag);   // 0xbddda0, ret 0x18
    void Tick1();                      // 0xbe5740
    void Tick2();                      // 0xbde4a0
    bool IsMusicActive();              // 0xbd9fa0
};

struct CultureSet {
    char pad[0x1c];
    Triple* LookupColor(int specialty);   // 0xbf9700, ret 4
};

struct Civ;
struct GameData {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual int GetPoliticalID();      // slot 19 (+0x4c)
    void AddRelated(int id);           // 0xbdf9e0, ret 4
};

struct Civ {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual int GetPoliticalID();      // slot 19 (+0x4c)
    char pad04[0x40 - 4];
    int  mId40;                        // +0x40
    char pad44[0x6c - 0x44];
    CultureSet mCultureSet;            // +0x6c
    char pad88[0x8a - 0x88];
    bool mIsNeutral;                   // +0x8a
    char pad8b;
    bool mCommNotifiedWarning;         // +0x8c
    bool mHasDeveloped;                // +0x8d
    char pad8e[0x9c - 0x8e];
    City** mCitiesBegin;               // +0x9c
    City** mCitiesEnd;                 // +0xa0
    char pada4[0xb0 - 0xa4];
    void** mVehiclesBegin;             // +0xb0
    void** mVehiclesEnd;               // +0xb4
    char padb8[0xc4 - 0xb8];
    float mColorR, mColorG, mColorB;   // +0xc4
    char padd0[0x274 - 0xd0];
    CityMusic* mCityMusic;             // +0x274
    char pad278[0x2a0 - 0x278];
    int  mCommEventId;                 // +0x2a0
    char pad2a4[0x450 - 0x2a4];
    int  mLastRelation;                // +0x450
    City* mMusicCity;                  // +0x454
    char pad458[0x460 - 0x458];
    City* mAttackCity;                 // +0x460

    void SubTick1();                   // 0xbfb930
    void SubTick2();                   // 0xbf1070
    void SubTick3();                   // 0xbf71d0
    void SubTick4();                   // 0xbf8440
    float GetMoney();                  // 0xbef6d0
    float GetFloat6fa0(int a);         // 0xbf6fa0, ret 4
    void Step7230();                   // 0xbf7230
    void ChooseUFOAndBuyVehicle();     // 0xbf9820
    void Step();                       // 0xbf9e70
    void Step_a660(int a);             // 0xbfa660, ret 4
    void Step8710();                   // 0xbf8710
    void UpdateCivAI();                // 0xbfb020
    void Step5cb0();                   // 0xbf5cb0
    void Step7390();                   // 0xbf7390
    void Step1170();                   // 0xbf1170
    void Step08b0();                   // 0xbf08b0
    void Step0710(int a, Civ* c, int b);   // 0xbf0710, ret 0xc
    void Step07c0();                   // 0xbf07c0
    void Step74a0();                   // 0xbf74a0
    void Step1270();                   // 0xbf1270
    void Step14b0();                   // 0xbf14b0
    void Step3180();                   // 0xbf3180
    int  GetSize0f10();                // 0xbf0f10
    float GetSize2ae0();               // 0xbf2ae0
    int  GetLevel7150();               // 0xbf7150
    char* GetBlock();                  // 0xbef950 (callers add 0x504)

    void Update();                     // @ 0x00bfbbf0
};

struct Sphere { int GetKind(); };      // 0xc75420
struct PairVec { Civ** begin; Civ** end; };
struct GdVec { GameData** begin; GameData** end; };
struct VecHolder { int pad; GdVec vec; };

struct NounMgr {
    PairVec* GetCivilizations();       // 0xb25ca0
    Civ* GetPlayerCivilization();      // 0xb25fb0
    int GetPlayerEmpireOrMinus1();     // 0xb1f9d0
    VecHolder* GetGameDataVector(void* a, void* b, void* c, void* d, unsigned int typeTag);  // 0xb21340, ret 0x14
    Sphere* GetCurrentTerrainSphere(); // 0xf67d90
};
struct RelMgr {
    int GetRelation(int a, int b, int c);   // 0xd00a70, ret 0xc
};
struct Rand { unsigned RandomUint32Uniform(unsigned n); };   // 0xa68fb0, ret 4
struct StrategyMgr {
    int Apply(Civ* civ, int tableEntry, unsigned key, Vec3* pos, Color4* color, int zero, int pid);   // 0xcf90a0, ret 0x1c
};

extern unsigned GetCurrentGameMode();          // 0xb5b800
extern NounMgr* NounManager();                 // 0xb3d300
extern RelMgr* RelationshipManager();          // 0xb3d2c0
extern StrategyMgr* GetStrategyMgr();          // 0xcf74c0 (returns a singleton)
extern int  Lookup_c9e6d0(int specialty, int zero);   // cdecl
extern void Notify_e3c7c0(unsigned key, void* a, void* b, const Triple& zero, int p1, int p2, int p3);   // cdecl
extern void Final_ba5d30(Civ* civ);            // cdecl
extern Rand sMathRandom;                       // 0x1601760
extern int gStrategyTable[];                   // 0x01469284
void FnA();   // 0xb1e500
void FnB();   // 0xacdff0
void FnC();   // 0xd3d420
void FnD();   // 0xcd7d10

// @ 0x00bfbbf0
void Civ::Update()
{
    if (GetCurrentGameMode() == 0x1654c05)
        SubTick1();
    SubTick2();
    SubTick3();
    SubTick4();

    if (this == NounManager()->GetPlayerCivilization()) {
        // The player's own civ: sometimes buy a vehicle for the first city.
        if (GetCurrentGameMode() != 0x1654c05 && sMathRandom.RandomUint32Uniform(10) == 0) {
            if (NounManager()->GetCurrentTerrainSphere()->GetKind() <= 0
                && ((int)mVehiclesEnd - (int)mVehiclesBegin & ~3) == 0
                && GetMoney() < 1000.0f
                && GetFloat6fa0(0) == 0.0f) {
                City* city = *mCitiesBegin;
                if (city) {
                    int spec = Lookup_c9e6d0(city->GetVehicleSpecialty(), 0);
                    Triple* color = mCultureSet.LookupColor(spec);
                    city->SetupVehicle(city->GetVehicleSpecialty(), 0, *color,
                                       GetCurrentGameMode() == 0x1654c05);
                }
            }
        }
    } else {
        PairVec* civs = NounManager()->GetCivilizations();
        NounMgr* nm = NounManager();
        GdVec& gd = nm->GetGameDataVector(FnD, FnC, FnB, FnA, 0x18c43e8)->vec;
        int nGameData = (int)(gd.end - gd.begin);
        int nCivs = (int)(civs->end - civs->begin);
        for (int i = 0; i < nCivs; i++) {
            Civ* other = civs->begin[i];
            if (other != this) {
                int otherId = other->GetPoliticalID();
                int myId = GetPoliticalID();
                if (RelationshipManager()->GetRelation(myId, otherId, 1) <= 1) {
                    for (int j = 0; j < nGameData; j++) {
                        GameData* item = gd.begin[j];
                        if (item->GetPoliticalID() == GetPoliticalID())
                            item->AddRelated(other->GetPoliticalID());
                    }
                }
            }
        }

        Step7230();
        int n = (int)(mCitiesEnd - mCitiesBegin);
        for (int i = 0; i < n; i++)
            mCitiesBegin[i]->Tick1();
        n = (int)(mCitiesEnd - mCitiesBegin);
        for (int i = 0; i < n; i++)
            mCitiesBegin[i]->Tick2();
        ChooseUFOAndBuyVehicle();
        Step();
        Step_a660(0);
        Step_a660(1);
        Step8710();
        UpdateCivAI();
        Step5cb0();
        Step7390();
        Step1170();

        if (GetCurrentGameMode() == 0x1654c04) {
            Step08b0();
            if (!mIsNeutral) {
                int playerEmpire = NounManager()->GetPlayerEmpireOrMinus1();
                int myId = GetPoliticalID();
                if (RelationshipManager()->GetRelation(myId, playerEmpire, 1) <= 1) {
                    if (!mCommNotifiedWarning && mCommEventId == -1) {
                        mCommNotifiedWarning = true;
                        Step0710(1, this, 0);
                    }
                } else {
                    if (mCommEventId == 1)
                        Step07c0();
                    if (mCommNotifiedWarning)
                        mCommNotifiedWarning = false;
                }
            }
            if (sMathRandom.RandomUint32Uniform(1000) == 0) {
                City* c = mAttackCity;
                if (c != 0) {
                    mAttackCity = 0;
                    c->Release();
                }
            }
            Step74a0();
            Step1270();
            Step14b0();
            int playerEmpire = NounManager()->GetPlayerEmpireOrMinus1();
            int myId = GetPoliticalID();
            int rel = RelationshipManager()->GetRelation(myId, playerEmpire, 1);
            if (!mIsNeutral && mHasDeveloped && mLastRelation != rel && mLastRelation != -1) {
                int cur = mLastRelation;
                int idx = -1;
                if (rel == 4) {
                    if (cur < 4) idx = 4;
                } else if (rel < 4 && cur == 4) {
                    idx = 3;
                }
                if (rel > 1) {
                    if (cur < 2) idx = 2;
                } else {
                    if (cur > 1) idx = 1;
                }
                if (idx != -1) {
                    City* city = *mCitiesBegin;
                    Color4 color;
                    color.r = mColorR;
                    color.g = mColorG;
                    color.b = mColorB;
                    color.a = 1.0f;
                    GetStrategyMgr()->Apply(this, gStrategyTable[idx], 0xaa9a8ed7,
                                            city->pos120.GetPosition(), &color, 0, GetPoliticalID());
                    if (idx == 1) {
                        int id40 = mId40;
                        Civ* player = NounManager()->GetPlayerCivilization();
                        Notify_e3c7c0(0xf0963675, NounManager()->GetPlayerCivilization()->GetBlock() + 0x504,
                                      GetBlock() + 0x504, Triple(), player->mId40, id40, 0);
                    } else if (idx == 2) {
                        int id40 = mId40;
                        Civ* player = NounManager()->GetPlayerCivilization();
                        Notify_e3c7c0(0x27d48cfb, NounManager()->GetPlayerCivilization()->GetBlock() + 0x504,
                                      GetBlock() + 0x504, Triple(), player->mId40, id40, 0);
                    }
                }
            }
            mLastRelation = rel;
            Step3180();
            Final_ba5d30(this);
        }
    }

    // Re-evaluate mHasDeveloped from the terrain stage and the civ's size.
    if (!mHasDeveloped) {
        int cityBytes = (int)mCitiesEnd - (int)mCitiesBegin & ~3;
        int vehBytes = (int)mVehiclesEnd - (int)mVehiclesBegin & ~3;
        int stage = NounManager()->GetCurrentTerrainSphere()->GetKind();
        if (stage == 0) {
            if (!(cityBytes <= 8 && vehBytes <= 0x18 && GetSize0f10() <= 0x3c
                  && GetSize2ae0() <= 40000.0f && GetLevel7150() <= 4))
                mHasDeveloped = true;
        } else if (stage == 1) {
            if (!(cityBytes <= 4 && vehBytes <= 0xc && GetSize0f10() <= 0x1e
                  && GetSize2ae0() <= 20000.0f && GetLevel7150() <= 2))
                mHasDeveloped = true;
        } else if (stage == 2) {
            if (!(cityBytes <= 4 && vehBytes <= 8 && GetSize0f10() <= 0x14
                  && GetSize2ae0() <= 10000.0f && GetLevel7150() <= 1))
                mHasDeveloped = true;
        }
    }

    // City music follows the civ's music city while it owns cities.
    if (mCityMusic && mMusicCity && ((int)mCitiesEnd - (int)mCitiesBegin & ~3) != 0) {
        if (mCityMusic->IsPlaying() == 0)
            mCityMusic->Start(mMusicCity->pos120.GetPosition());
        mCityMusic->Pause(mMusicCity->IsMusicActive());
    }
}

// =============================================================================================
// Game-data / combatant / timer helpers of the same unit (0x00bfc3a0 .. 0x00bfcc40).
// Names below are invented; the retail offsets, vtable slots and call shapes are what matter.
// =============================================================================================

extern void  FUN_00b69930(void* obj, float value, int extra);        // 0x00b69930, cdecl, 3 args
extern float FUN_00b685e0(void* obj);                                // 0x00b685e0, cdecl
extern void  EA_IO_WriteUint32(void* s, const void* data, int n, int f);   // 0x0093aa70
extern void  EA_IO_ReadInt32(void* s, void* data, int n, int f);           // 0x0093a780
struct Opaque {                                // __thiscall callees (bodies elsewhere)
    int   F_b18530();                          // 0x00b18530
    bool  F_f25330();                          // 0x00f25330
    int   F_f3f950(void* arg);                 // 0x00f3f950, ret 4
    void* F_bddd10();                          // 0x00bddd10
};
extern double F_eec5c0(void* obj);                                   // 0x00eec5c0, cdecl
extern bool  F_b673c0(void* obj);                                    // 0x00b673c0, cdecl
extern bool  F_b18850(void* obj);                                    // 0x00b18850, cdecl
extern bool  F_b187b0(void* obj);                                    // 0x00b187b0, cdecl
extern bool  F_b18810(void* obj);                                    // 0x00b18810, cdecl
extern bool  F_b187d0(void* obj);                                    // 0x00b187d0, cdecl
extern bool  F_b18830(void* obj);                                    // 0x00b18830, cdecl
extern bool  F_b18760(void* obj);                                    // 0x00b18760, cdecl
extern bool  F_b18870(void* obj);                                    // 0x00b18870, cdecl
extern void* F_bc96a0(void* self, unsigned a, int b);                // 0x00bc96a0, thiscall, ret 8
extern void* F_d999d0(void* obj);                                    // 0x00d999d0, cdecl
extern int   GetPlayerEmpireID();                                    // 0x01021090
extern void* GetUFOSimulator();                                      // 0x00ffbe50
extern float g_defPoint[3];                                          // 0x0168cb6c, 0x0168cb70, 0x0168cb74
#include <math.h>

struct Timer {
    char body[0x20];                                   // +0x000 (only the head is addressed)
    bool IsRunning();                                  // 0x00feba90
    unsigned long long GetElapsedTime();               // 0x00bc3190, edx:eax
    void Restart();                                    // 0x00bc3130
    void Stop();                                       // 0x00bc3110
};

struct VarListSerializer {
    char body[0xa00];
    void Init(void* owner, void* table, int key);      // 0x00692f90 (ctor), ret 0xc
    void Serialize(void* stream);                      // 0x00692900, ret 4
    void Read(void* stream);                           // 0x00693e10, ret 4
};

struct VtObj {
    void** vt;                                         // +0x000
    bool NodePresent();                                // 0x00bfc3a0
    bool NodePresentArg(int unused);                   // 0x00bfc3d0
    float NodeValue();                                 // 0x00bfc400
    bool GateCheck(VtObj* other);                      // 0x00bfc7a0
    void GameDataCenter(Vec3* out);                    // 0x00bfc8a0
    bool TrikeCheck(int arg);                          // 0x00bfc900
};

// Clear *slot and drop the object's second vtable entry (the shared release tail).
static __forceinline void ReleaseSlotPtr(void** slot)
{
    void* p = *slot;
    *slot = 0;
    if (p)
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
}

// Sim: the shared body of the 0x00bfc540..0x00bfcc40 range (vtable, timers, small pointer slots).
struct Sim {
    void** vt;                                         // +0x000
    char pad_004[0x028 - 0x004];
    void* p_028;                                       // +0x028
    float m_02c;                                       // +0x02c
    void* p_030;                                       // +0x030
    int   m_034;                                       // +0x034
    float m_038;                                       // +0x038
    int   m_03c;                                       // +0x03c
    char pad_040[0x044 - 0x040];
    void* p_044;                                       // +0x044
    void* p_048;                                       // +0x048
    char pad_04c[0x074 - 0x04c];
    float m_074;                                       // +0x074
    float m_078;                                       // +0x078
    float m_07c;                                       // +0x07c
    char pad_080[0x084 - 0x080];
    char* p_084;                                       // +0x084
    char* p_088;                                       // +0x088
    char pad_08c[0x098 - 0x08c];
    Timer timer_98;                                    // +0x098
    unsigned int m_0b8;                                // +0x0b8
    void* arr_bc[3];                                   // +0x0bc
    void NodeApply(int value);                         // 0x00bfc430
    float NodeRatio();                                 // 0x00bfc490
    void CombatantWrite(VtObj* stream);                // 0x00bfc4a0
    void CombatantRead(VtObj* stream);                 // 0x00bfc540
    int TimedExpired();                                // 0x00bfc600
    void TimedAdd(unsigned int amount);                // 0x00bfc640
    void TimedStop();                                  // 0x00bfc6a0
    void ReleaseSlots();                               // 0x00bfc720
    void DetachSlot();                                 // 0x00bfcac0
    void DetachOther();                                // 0x00bfcae0
    double SimValue();                                 // 0x00bfcb10
    bool TakeDefaultPoint(Vec3* out);                  // 0x00bfcb90
    void TickSlotArray();                              // 0x00bfcc00
    bool EntryAvailable(int id);                       // 0x00bfcc40
};

struct Node0x14 {
    void** vt;                                         // +0x000
    bool  Fn104fff0();                                 // 0x0104fff0, thiscall, no stack args
    float Fn104be30();                                 // 0x0104be30, thiscall, no stack args
};

struct AnimObj {                                       // 0x00bfc900 target object
    char pad_000[0xb4c];
    void* p_b4c;                                       // +0xb4c
    char pad_b50[0x0b58 - 0x0b50];
    unsigned int flags;                                // +0xb58
};

// @ 0x00bfc3a0
bool VtObj::NodePresent()
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return false;
    return ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104fff0();
}

// @ 0x00bfc3d0
bool VtObj::NodePresentArg(int unused)
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return false;
    return ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104fff0();
}

// @ 0x00bfc400
float VtObj::NodeValue()
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return 0.0f;
    return ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104be30();
}

// @ 0x00bfc430
void Sim::NodeApply(int value)
{
    void* p = ((void* (__thiscall*)(void*, int))this->vt[3])(this, value);
    float f = FUN_00b685e0(p);
    FUN_00b69930(((void* (__thiscall*)(void*, float))this->vt[3])(this, f), f, value);
}

// @ 0x00bfc490
float Sim::NodeRatio()
{
    return this->m_038 / ((float (__thiscall*)(void*))this->vt[22])(this);
}

// @ 0x00bfc4a0
void Sim::CombatantWrite(VtObj* stream)
{
    unsigned int value = 0x013f94d4;
    void* sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    void* writer = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_WriteUint32(writer, &value, 1, 0);
    value = (unsigned int)this->m_034;
    sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    writer = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_WriteUint32(writer, &value, 1, 0);
    VarListSerializer s;
    s.Init(this, (void*)0x01570858, 0x01a80d26);
    s.Serialize(stream);
}

// @ 0x00bfc540
void Sim::CombatantRead(VtObj* stream)
{
    int first = 0;
    int second = 0;
    void* sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    void* reader = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_ReadInt32(reader, &first, 1, 0);
    sync = ((void* (__thiscall*)(void*))stream->vt[8])(stream);
    reader = ((void* (__thiscall*)(void*))((VtObj*)sync)->vt[6])(sync);
    EA_IO_ReadInt32(reader, &second, 1, 0);
    this->m_034 = second;
    VarListSerializer s;
    s.Init(this, (void*)0x01570858, 0x01a80d26);
    s.Read(stream);
}

// @ 0x00bfc600
int Sim::TimedExpired()
{
    if (this->timer_98.IsRunning()) {
        unsigned long long elapsed = this->timer_98.GetElapsedTime();
        if (elapsed < (unsigned long long)this->m_0b8)
            return 1;
    }
    return 0;
}

// @ 0x00bfc640
void Sim::TimedAdd(unsigned int amount)
{
    if (this->timer_98.IsRunning()) {
        unsigned int cap = this->m_0b8;
        unsigned long long elapsed = this->timer_98.GetElapsedTime();
        if (elapsed < (unsigned long long)cap) {
            this->m_0b8 = cap + amount;
            return;
        }
    }
    this->m_0b8 = amount;
    this->timer_98.Restart();
}

// @ 0x00bfc6a0
void Sim::TimedStop()
{
    this->m_0b8 = 0;
    this->timer_98.Stop();
}

// @ 0x00bfc720
void Sim::ReleaseSlots()
{
    if (this->p_028) {
        void* p = this->p_028;
        this->p_028 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
    if (this->p_030) {
        void* p = this->p_030;
        this->p_030 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
    }
    if (this->p_044) {
        void* p = this->p_044;
        this->p_044 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
    if (this->p_048) {
        void* p = this->p_048;
        this->p_048 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
    for (int i = 0; i < 3; i++) {
        if (this->arr_bc[i])
            ReleaseSlotPtr(&this->arr_bc[i]);
    }
}

// @ 0x00bfc7a0
bool VtObj::GateCheck(VtObj* other)
{
    if (((void* (__thiscall*)(void*))this->vt[5])(this) == 0)
        return false;
    float reach = ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104be30();
    if (reach != -1.0f) {
        VtObj* mine = ((VtObj* (__thiscall*)(void*))this->vt[2])(this);
        VtObj* theirs = ((VtObj* (__thiscall*)(void*))other->vt[2])(other);
        Vec3* pa = ((Vec3* (__thiscall*)(void*))mine->vt[11])(mine);
        Vec3* pb = ((Vec3* (__thiscall*)(void*))theirs->vt[11])(theirs);
        float dx = pb->x - pa->x;
        float dy = pb->y - pa->y;
        float dz = pb->z - pa->z;
        float dist = sqrtf(dx * dx + dz * dz + dy * dy);
        float limit = ((Node0x14* (__thiscall*)(void*))this->vt[5])(this)->Fn104be30();
        return dist <= limit;
    }
    return true;
}

// @ 0x00bfc8a0
void VtObj::GameDataCenter(Vec3* out)
{
    float bounds[6];
    VtObj* owner = ((VtObj* (__thiscall*)(void*))this->vt[2])(this);
    const float* src = (const float*)((float* (__thiscall*)(void*, float*))owner->vt[27])(owner, bounds);
    float x = (src[0] + src[3]) * 0.5f;
    float y = (src[4] + src[1]) * 0.5f;
    float z = (src[5] + src[2]) * 0.5f;
    out->x = x;
    out->y = y;
    out->z = z;
}

// @ 0x00bfc900
bool VtObj::TrikeCheck(int arg)
{
    switch (GetCurrentGameMode()) {
    case 0x1654c01:
    case 0x1654c10: {
        if (this == 0)
            return false;
        AnimObj* o = (AnimObj*)((void* (__thiscall*)(void*, int))this->vt[3])(this, 0xce9f6639);
        if (o == 0)
            return false;
        if (o->flags & 0x200)
            return true;
        if (o->flags & 0x100)
            return true;
        void* anim = F_bc96a0((char*)o->p_b4c + 8, 0x400, 0);
        if (anim == 0)
            return false;
        AnimObj* w = (AnimObj*)F_d999d0(anim);
        if (w == 0)
            return false;
        if (w->flags & 0x100)
            return true;
        if (w->flags & 0x200)
            return true;
        return false;
    }
    case 0x1654c02:
        if (F_b18850(this))
            return true;
        if (F_b187b0(this))
            return true;
        return false;
    case 0x1654c04:
        if (F_b18810(this))
            return true;
        if (F_b187d0(this))
            return true;
        if (F_b18830(this))
            return true;
        if (F_b18760(this))
            return true;
        return false;
    case 0x1654c05: {
        if (this == 0)
            return false;
        AnimObj* o = (AnimObj*)((void* (__thiscall*)(void*, void*))this->vt[3])(this, (void*)0x013f94d4);
        if (o == 0)
            return false;
        if (!F_b187d0(this) && !F_b18870(this) && !F_b18760(this))
            return false;
        int empire = GetPlayerEmpireID();
        if (arg != empire) {
            if (o != (AnimObj*)((Opaque*)GetUFOSimulator())->F_bddd10())
                return false;
        }
        return true;
    }
    }
    return false;
}

// @ 0x00bfca80
void TrikeNotify(void* obj, void* owner, int extra)
{
    if (((VtObj*)obj)->TrikeCheck((int)owner) && F_b673c0(obj))
        FUN_00b69930(obj, FUN_00b685e0(obj), extra);
}

// @ 0x00bfcac0
void Sim::DetachSlot()
{
    void* p = this->p_028;
    this->m_03c = -1;
    if (p) {
        this->p_028 = 0;
        ((void (__thiscall*)(void*))((VtObj*)p)->vt[25])(p);
    }
}

// @ 0x00bfcae0
void Sim::DetachOther()
{
    if (this->p_030) {
        void* p = this->p_030;
        ((void (__thiscall*)(void*, int))((VtObj*)p)->vt[3])(p, 0);
        p = this->p_030;
        if (p) {
            this->p_030 = 0;
            ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
        }
    }
}

// @ 0x00bfcb10
double Sim::SimValue()
{
    float saved = this->m_02c;
    if (GetCurrentGameMode() == 0x1654c10) {
        int mode = *(int*)(*(char**)0x016c7aa4 + 0xcc);
        if (mode == 2) {
            void* o = ((void* (__thiscall*)(void*))this->vt[3])(this);
            int g = ((Opaque*)o)->F_b18530();
            if (!g)
                return saved;
            if (!((Opaque*)g)->F_f25330())
                return saved;
            if (!((Opaque*)*(void**)(*(char**)0x016c7aa4 + 0x74))->F_f3f950(o))
                return saved;
            return F_eec5c0(o);
        }
        if (mode == 1)
            return this->m_038;
    }
    return saved;
}

// @ 0x00bfcb90
bool Sim::TakeDefaultPoint(Vec3* out)
{
    if (this->m_074 != g_defPoint[0] || this->m_078 != g_defPoint[1] || this->m_07c != g_defPoint[2]) {
        out->x = this->m_074;
        out->y = this->m_078;
        out->z = this->m_07c;
        this->m_074 = g_defPoint[0];
        this->m_078 = g_defPoint[1];
        this->m_07c = g_defPoint[2];
        return true;
    }
    return false;
}

// @ 0x00bfcc00
void Sim::TickSlotArray()
{
    for (int i = 0; i < 3; i++) {
        void* p = this->arr_bc[i];
        if (p) {
            if (!((bool (__thiscall*)(void*))((VtObj*)p)->vt[4])(p)) {
                p = this->arr_bc[i];
                this->arr_bc[i] = 0;
                if (p)
                    ((void (__thiscall*)(void*))((VtObj*)p)->vt[1])(p);
            }
        }
    }
}

// @ 0x00bfcc40
bool Sim::EntryAvailable(int id)
{
    for (char* p = this->p_084; p != this->p_088; p += 0x28) {
        if (*(int*)(p + 0x20) == id) {
            unsigned long long elapsed = ((Timer*)p)->GetElapsedTime();
            if (elapsed < 0x4e20)
                return true;
            return false;
        }
    }
    return false;
}



