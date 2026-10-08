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
