// s00bf1ba0 -- SP::cCivilization / Simulator::cGameData tail block (0x00bf1ba0-0x00bf2cde).
//
// Pieces: the space-telemetry UFO placement helpers that live on a cSPSimulatorSpaceGame
// (+0xb0 vector<AutoRefCount<cSimulatorPlayerUFO>>), the civilization's specialty scoring
// functions (0xbf1ba0-0xbf2266), Simulator::ISimulatorSerializable::Read, the
// cGameData::func40h "notify every data view" pass, the cGameData notification pass, and a
// set of 32-byte StarRecord vector helpers (0xbf2840-0xbf2a10) plus two id->record lookups.
//
// Retail layouts come from the 2017 ModAPI PDB dump (work/ext/Spore-ModAPI) and the
// already-migrated sibling slices s00bf0be0 / s00bf2ce0: cCivilization mCities +0x9c,
// cGameData mpView +0x14 / mpScenarioMarker +0x18 / functor map +0x6c, cCity
// mVehicleSpecialty +0x540, cSimulatorSpaceGame mNPC_UFOs +0xb0, cGameData size 0x34.
//
// Flags: /O2 /MD /Gy /EHsc /TP (defaults).
typedef unsigned char byte;
typedef unsigned int  uint;

// ---------------------------------------------------------------------------
// engine routines (defined elsewhere)
// ---------------------------------------------------------------------------
struct IntVec { int* begin; int* end; int* cap; };

void* __cdecl SP_NounManager();                             // 0x00b3d300
void* __cdecl EAAllocate(uint size, const char* file, int a, int b, const char* alloc, int line); // 0x00f473a0
void  __cdecl operator_delete(void* p);                     // 0x00f47380
void* __cdecl RBTreeIncrement(void* node);                  // 0x00921580
void  __cdecl RBTreeInsert(void* node, void* anchor, void* header, int side); // 0x009216a0
int   __cdecl WriteUint32(void* stream, const void* data, int count, int a);  // 0x0093aa70
int   __cdecl ReadInt32(void* stream, void* data, int count, int a);          // 0x0093a780
int   __cdecl FUN_00555e80(int begin, IntVec* vec);          // 0x00555e80
// eastl rbtree head of the id->star-record map.  'find' is 0x00e39fb0.
// eastl's iterator is a 4-byte pointer wrapper with a user copy ctor (hence the hidden return slot).
struct TreeIter
{
    void* mpNode;                          // +0x00
    TreeIter() {}
    TreeIter(const TreeIter& o) : mpNode(o.mpNode) {}
};
struct StarNode
{
    StarNode* mpLeft;                      // +0x00
    StarNode* mpParent;                    // +0x04
    StarNode* mpRight;                     // +0x08
    int       mField0c;                    // +0x0c
};
struct StarTree
{
    int  mParent;                          // +0x00
    StarNode mAnchor;                      // +0x04
    uint mSize;                            // +0x14
    TreeIter find(const int& key);         // 0x00e39fb0
    bool ContainsMap(int key);             // 0x00bf2c80
};
float __fastcall FUN_041ea70(void* propObj);                 // 0x0041ea70  SP::GetPropertyAsFloat

// The two vtable-style functor addresses stored into a freshly constructed StarRecord.
// They are data (function pointers) but written through a global; keep them as objects.
extern "C" int FUN_01465d54;                                // 0x01465d54
extern "C" int FUN_01464450;                                // 0x01464450
extern "C" int FUN_0102f810;                                // 0x0102f810

// ---------------------------------------------------------------------------
// fixed-address callees modelled as __fastcall free functions (this in ecx)
// ---------------------------------------------------------------------------
int   __fastcall cGameNounManager_CreateNoun(void* self, int typeKey);   // 0x00b20c60
void* __fastcall cGameNounManager_GetCivilizationList(void* self);       // 0x00b25ca0
void* __fastcall cTerrainEditor_GetCurrentTerrainSphere(void* self);     // 0x00f67d90
int   __fastcall cCity_GetHousingAmount(void* self);                     // 0x00bd8960
int   __fastcall cCivilization_CountSpecialty(int self, int spec, int excl); // 0x00bf01f0 (ret 8)
int   __fastcall cCity_UnknownBef980(void* self, int id);                // 0x00bef980 (ret 4)
int   __fastcall cGonzagoTimer_Write(void* self, void* stream);          // 0x00b638d0
int   __fastcall cGameData_Read(void* self, void* stream);               // 0x00b18600
int   __fastcall FUN_00b6e340(void* self, void* stream);                 // 0x00b6e340 (this = civ+0x3c)
void  __fastcall cVarListSerializer_ctor(void* self, void* host, void* attrs, int id); // 0x00692f90
int   __fastcall cVarListSerializer_Serialize(void* self, void* stream); // 0x00693e10
void* __fastcall EA_ResourceMan_GetManager();                            // 0x0067dcd0
void* __fastcall SP_MessageServer();                                     // 0x0067dcc0
void* __fastcall SP_PropertyManager();                                   // 0x0067de30
void  __fastcall SimSingleton_ctor(void* self);                          // 0x00ae5c30
int   __fastcall SP_GetCurrentGameMode();                                // 0x00b5b800
int   __fastcall SP_GetPlayerEmpireID();                                 // 0x01021090
int   __fastcall cSPSpaceEconomyTuning_GetVehicleCost(void* self);       // 0x0102fbb0
float __fastcall FUN_00bcdea0(int pid);                                  // 0x00bcdea0
float __fastcall FUN_00bcde40(int pid);                                  // 0x00bcde40
float __fastcall FUN_00bcde70(int pid);                                  // 0x00bcde70
int   __fastcall FUN_00bf0f40(void* self);                               // 0x00bf0f40
void  __fastcall UpdateCityMusicPosition(void* self);                    // 0x00bf0f90
int   __fastcall FUN_00bf2380(void* map);                                // 0x00bf2380
int   __fastcall FUN_00bf1fd0(void* self, int specialty);               // 0x00bf1fd0
float __fastcall FUN_00bf2170(void* self, int a, int b);                 // 0x00bf2170 (ret 8)
int   __fastcall cTribe_GetMembers(void* self);                          // 0x00c8e810
int   __fastcall cCity_GetVehicleSpecialty(void* self);                  // 0x00bd81d0

extern "C" int  DAT_018c6de8;        // 0x018c6de8  noun type key
extern "C" int  DAT_0137e8e0;        // 0x0137e8e0  cast/type tag
extern "C" int  g_civStarCountScale; // 0x0169cb64
extern "C" int  g_cityHousingDiv;    // 0x0169c088
extern "C" byte DAT_0168bd6c;        // 0x0168bd6c
extern "C" int  DAT_0167a60c;        // 0x0167a60c  Simulator::SimSingleton*
extern "C" int  g_civAttributes;     // 0x0156faa8
extern "C" char DAT_0145f924[];      // 0x0145f924  "Simulator/SimSingleton"
extern "C" int  g_specialtyTable[];  // 0x01469298  int[?][3]

// ---------------------------------------------------------------------------
// a cGameNounManager noun; only the head shared by cities and civilizations.
// ---------------------------------------------------------------------------
class cCity;

class Noun
{
public:
    void**  mvptr;                         // +0x00
    uint    pad04[(0x89 - 0x04) / 4];      // +0x04..0x88
    bool    mField89;                      // +0x89
    bool    mField8a;                      // +0x8a
    byte    pad8b[0x9c - 0x8b];            // +0x8b..0x9b
    Noun**  mListBegin;                    // +0x9c  (mCities / mMembers)
    Noun**  mListEnd;                      // +0xa0
    uint    mListCap;                      // +0xa4

    int   GetVehicleSpecialty();           // 0x00bd81d0
    int   GetHousingAmount();              // 0x00bd8960
    int   GetMemberCount();                // 0x00c8e810 inline: (mListEnd - mListBegin) >> 2
    Noun* GetMember(int i);                // inline: mListBegin[i]
};

// cCity: a community whose 0x340 vector is its member list (cTribe::GetMembers) and whose
// +0x519 byte gates the counter-conversion timer.
class cCity : public Noun
{
public:
    byte  padA8[0x519 - 0xa8];             // +0xa8..0x518
    byte  mCounterConvBusy;                // +0x519
    byte  pad51a[0x540 - 0x51a];           // +0x51a..0x53f
    int   mVehicleSpecialty;               // +0x540
};

// ---------------------------------------------------------------------------
// SP::cSPSimulatorSpaceGame: only the +0xb0 UFO vector is touched here.
// ---------------------------------------------------------------------------
class cSPSimulatorSpaceGame
{
public:
    uint  pad00[0xb0 / 4];                 // +0x00..0xaf
    void** mNPCUFOBegin;                   // +0xb0
    void** mNPCUFOEnd;                     // +0xb4
    int   GetPoliticalID();                // vtable slot 0x4c

    int   SpaceTelemetry_Add(uint species);   // 0x00bf2100
    float FUN_00bf2ae0();                     // 0x00bf2ae0
};

// ---------------------------------------------------------------------------
// cCivilization (retail): the pieces touched by this slice.
// ---------------------------------------------------------------------------
class cCivilization : public Noun
{
public:
    uint   padA8[(0xb0 - 0xa8) / 4];       // +0xa8..0xaf
    Noun** mVehicleBegin;                  // +0xb0
    Noun** mVehicleEnd;                    // +0xb4
    uint   padB8[(0x274 - 0xb8) / 4];      // +0xb8..0x273
    void*  mpCityMusic;                    // +0x274
    uint   pad278[(0x454 - 0x278) / 4];    // +0x278..0x453
    void*  mp454;                          // +0x454
    uint   pad458[(0x4ac - 0x458) / 4];    // +0x458..0x4ab
    float  mField4ac;                      // +0x4ac
    float  mField4b0;                      // +0x4b0
    uint   pad4b4[(0x4c4 - 0x4b4) / 4];    // +0x4b4..0x4c3
    uint   pad4c4[(0x4fc - 0x4c4) / 4];    // +0x4c4..0x4fb
    int    GetPoliticalID();               // vtable slot 0x4c

    int   FUN_00bf1ba0();                                 // 0x00bf1ba0
    void  FUN_00bf1cf0(IntVec* timers);                   // 0x00bf1cf0
    int   FUN_00bf1e20();                                 // 0x00bf1e20
    void  FUN_00bf1f40(void* music);                      // 0x00bf1f40 (ret 4)
    int   FUN_00bf1fd0(int specialty);                    // 0x00bf1fd0 (ret 4)
    float FUN_00bf2170(int a, int b);                     // 0x00bf2170 (ret 8)
};

// ---------------------------------------------------------------------------
// Simulator::cGameData: head only; the derived ISimulatorSerializable methods below
// reuse it. Size 0x34.
// ---------------------------------------------------------------------------
class cGameData
{
public:
    void** mvptr0;                         // +0x00
    void** mvptr1;                         // +0x04
    int    mnRefCount;                     // +0x08
    void*  mpNext;                         // +0x0c
    void*  mpPrev;                         // +0x10
    void*  mpView;                         // +0x14
    void*  mpScenarioMarker;               // +0x18
    int    mScenarioClassIndex;            // +0x1c
    byte   mField20;                       // +0x20
    byte   mIsDestroyed21;                 // +0x21
    byte   pad22[2];                       // +0x22..0x23
    uint   mID;                            // +0x24
    uint   mDefinitionID;                  // +0x28
    void*  mpGameDataOwner;                // +0x2c
    uint   mPoliticalID;                   // +0x30

    // retail cGameData extends past 0x34: its own city/tribe/vehicle lists and markers.
    Noun** mTribeBegin;                    // +0x34
    Noun** mTribeEnd;                      // +0x38
    Noun** mVehicleBegin;                  // +0x3c
    Noun** mVehicleEnd;                    // +0x40
    uint   pad44[(0x9c - 0x44) / 4];       // +0x44..0x9b
    Noun** mListBegin;                     // +0x9c
    Noun** mListEnd;                       // +0xa0
    uint   padA4[(0x484 - 0xa4) / 4];      // +0xa4..0x483

    int   Read(void* stream);              // 0x00b18600
    int   func40h();                       // 0x00bf23d0
    int   FUN_00bf2660(int);               // 0x00bf2660
    bool  StarMapContainsMap2(int value);  // 0x00bf2cb0
    int   FUN_00bf2a60();                  // 0x00bf2a60
};

// Simulator::ISimulatorSerializable : cGameData + the fields read at +0xc4..+0xcc.
class ISimulatorSerializable : public cGameData
{
public:
    uint  pad34[(0x3c - 0x34) / 4];        // +0x34..0x3b
    byte  mSub3c[0xa18];                   // +0x3c  embedded cVarListSerializer host
    int   mFieldC4;                        // +0xc4
    int   mFieldC8;                        // +0xc8
    int   mFieldCC;                        // +0xcc

    byte  ReadSerialized(void* stream);    // 0x00bf2270
};

// cGameData's three marker bytes live past the public head (the retail object extends it)
// hence the free-function spelling of func40h.

// ---------------------------------------------------------------------------
// 32-byte element moved by the 0xbf2840 family (vector<StarRecord>).
// ---------------------------------------------------------------------------
struct StarRecord
{
    int   vptr;                            // +0x00
    int   pad04;                           // +0x04
    int   f08;                             // +0x08
    int   f0c;                             // +0x0c
    int   f10;                             // +0x10
    int   f14;                             // +0x14
    byte  f18;                             // +0x18
    int   f1c;                             // +0x1c
};

struct RanNode                          // eastl rbtree node of the functor map
{
    void* mLeft;                           // +0x00
    RanNode* mParent;                      // +0x04
    void* mRight;                          // +0x08
    void* pad0c;                           // +0x0c
    int   mField14;                        // +0x14 (the resource-man handle in the value)
    void* mField18;                        // +0x18
    int   mField1c;                        // +0x1c
};

// ---------------------------------------------------------------------------
// helper inline: the specialty remap used all over this module.
//   0 -> 0, 1 -> 2, 2 -> 1, anything else -> -1
// ---------------------------------------------------------------------------
static int MapSpecialty(int s)
{
    if (s == 1)
        return 2;
    if (s == 2)
        return 1;
    if (s == 0)
        return 0;
    return -1;
}

// the value stored in a cCity's vehicle-specialty slot, remapped; 0 when the city list
// is empty or its first element is null.  This is the "tag" the original computes before
// every specialty comparison (0xbf0f40's shape, inlined).
static int CitySpecialty(Noun* c)
{
    if (!((*(int*)((char*)c + 0xa0) - *(int*)((char*)c + 0x9c)) & 0xfffffffc))
        return 0;
    if (*(int*)((char*)c + 0x9c) == 0)
        return 0;
    return MapSpecialty(cCity_GetVehicleSpecialty((void*)c));
}

// the number of specialty "slots" a star-record kind needs (the switch at 0xbf249c /
// 0xbf2540); kinds are the values FUN_00bef980 returns.
static int SpecialtySlots(int kind)
{
    switch (kind)
    {
    case 0: case 6: case 0xb: return 2;
    case 1: case 4: case 7: return 4;
    case 2: case 5: case 8: return 6;
    default:                  return 1;
    }
}

// ---------------------------------------------------------------------------
// SP::cSPSimulatorSpaceGame
// ---------------------------------------------------------------------------
// @ 0x00bf2100
int cSPSimulatorSpaceGame::SpaceTelemetry_Add(uint species)
{
    if ((int)((uint)((char*)mNPCUFOEnd - (char*)mNPCUFOBegin) & 0xfffffffc) >= 0x90)
        return 0;

    int already = 0;
    for (void** p = mNPCUFOBegin; p != mNPCUFOEnd; ++p)
    {
        void* ufo = *p;
        if (*(int*)((char*)ufo + 0xb20) == (int)species)
            ++already;
    }

    int want = FUN_00bf1fd0((void*)this, (int)species) - already;
    if (want < 1)
        return 0;
    return (int)species;
}

// @ 0x00bf2170
float cCivilization::FUN_00bf2170(int a, int b)
{
    if (a == 4)
        return 0.0f;

    float value = 0.0f;
    void* propMgr = SP_PropertyManager();
    void* prop = 0;
    if (prop != 0)
    {
        prop = 0;
        (*(void(__fastcall**)(void*))((char*)*(int*)prop + 4))(prop);
    }
    int ok = ((int(__fastcall*)(void*, int, void**))(*(int*)(*(int*)propMgr + 0x30)))(propMgr, 0xb6a5c63d, &prop);
    if (ok)
    {
        int tbl = g_specialtyTable[(a * 3)];
        if (prop != 0)
        {
            if ((*(int(__fastcall**)(void*, int, void**))((char*)*(int*)prop + 0x24))(prop, tbl, &prop))
            {
                if (*(unsigned short*)((char*)prop + 0x12) == 0xd)
                    value = FUN_041ea70(prop);
            }
        }
    }

    if (GetPoliticalID() != SP_GetPlayerEmpireID() || SP_GetCurrentGameMode() != 0x1654c05)
        return value;

    int cost = cSPSpaceEconomyTuning_GetVehicleCost((void*)FUN_0102f810);
    return (float)cost;
}

// @ 0x00bf2ae0
float cSPSimulatorSpaceGame::FUN_00bf2ae0()
{
    float total = *(float*)((char*)this + 0x98);
    if (!*(byte*)((char*)this + 0x89))
    {
        float x = *(float*)((char*)this + 0x4ac);
        total = x + total;
        x = *(float*)((char*)this + 0x4b0);
        total = x + total;
    }

    Noun** uFirst = *(Noun***)((char*)this + 0xb0);
    Noun** uLast = *(Noun***)((char*)this + 0xb4);
    for (Noun** p = uFirst; p != uLast; ++p)
    {
        char* ufo = (char*)*p;
        int b1c = *(int*)(ufo + 0xb1c);
        int b20 = *(int*)(ufo + 0xb20);
        total = FUN_00bf2170((void*)this, b1c, b20) + total;
    }

    Noun** cFirst = *(Noun***)((char*)this + 0x9c);
    Noun** cLast = *(Noun***)((char*)this + 0xa0);
    for (Noun** city = cFirst; city != cLast; ++city)
    {
        Noun* c = *city;
        for (int i = 0; i < c->GetMemberCount(); ++i)
        {
            void* obj = (void*)c->GetMember(i);
            if (obj == 0)
                continue;
            int pid = GetPoliticalID();
            if ((*(int(__fastcall**)(void*, int))((char*)*(int*)obj + 0xc))(obj, 0x1a55e4d))
                total = FUN_00bcdea0(pid) + total;
            else if ((*(int(__fastcall**)(void*, int))((char*)*(int*)obj + 0xc))(obj, 0xecade42))
                total = FUN_00bcde40(pid) + total;
            else if ((*(int(__fastcall**)(void*, int))((char*)*(int*)obj + 0xc))(obj, 0xff10521))
                total = FUN_00bcde70(pid) + total;
        }
    }
    return total;
}

// ---------------------------------------------------------------------------
// cCivilization gameplay helpers
// ---------------------------------------------------------------------------
// @ 0x00bf1ba0
int cCivilization::FUN_00bf1ba0()
{
    int* noun = (int*)cGameNounManager_CreateNoun(SP_NounManager(), (int)&DAT_018c6de8);
    if (noun == 0)
        return 0;
    return (*(int(__fastcall**)(void*, int))((char*)*(int*)noun + 0xc))(noun, (int)&DAT_0137e8e0);
}

// @ 0x00bf1cf0
void cCivilization::FUN_00bf1cf0(IntVec* timers)
{
    void* owner = (*(void*(__fastcall**)(void*))((char*)*(int*)this + 0x20))((void*)this);
    void* writer = (*(void*(__fastcall**)(void*))((char*)*(int*)owner + 0x18))((void*)owner);
    int count = (int)((timers->end - timers->begin) >> 5);
    WriteUint32((void*)writer, &count, 1, 0);

    for (int* p = timers->begin; p != timers->end; p += 8)
        cGonzagoTimer_Write((void*)p, (void*)this);
    (*(void(__fastcall**)(void*))((char*)*(int*)this + 0x1c))((void*)this);
}

// @ 0x00bf1e20
int cCivilization::FUN_00bf1e20()
{
    if (mField89)
        return 0;

    int count = 0;
    IntVec* list = (IntVec*)cGameNounManager_GetCivilizationList(SP_NounManager());
    for (Noun** p = (Noun**)list->begin; p != (Noun**)list->end; ++p)
    {
        Noun* other = *p;
        if (other->mField8a != mField8a)
            continue;
        int specOther = CitySpecialty(other);
        int specThis = CitySpecialty(this);
        if (specOther != specThis)
            continue;
        if (other == (Noun*)this)
            return count;
        ++count;
    }
    return 0;
}

// @ 0x00bf1f40
void cCivilization::FUN_00bf1f40(void* music)
{
    if (mpCityMusic != 0)
        (*(void(__fastcall**)(void*))((char*)*(int*)mpCityMusic + 0x28))(mpCityMusic);

    void* old = mpCityMusic;
    if (music != old)
    {
        if (music != 0)
            (*(void(__fastcall**)(void*))((char*)*(int*)music))(music);
        mpCityMusic = music;
        if (old != 0)
            (*(void(__fastcall**)(void*))((char*)*(int*)old + 4))(old);
    }

    UpdateCityMusicPosition((void*)this);

    if (mpCityMusic != 0 && mp454 != 0)
    {
        int vt = *(int*)mpCityMusic;
        void* sub = (void*)(*(int*)((char*)mp454 + 0x120));
        int arg = (*(int(__fastcall**)(void*))((char*)*(int*)sub + 0x2c))(sub);
        (*(void(__fastcall*)(void*, int))(vt + 0x24))(mpCityMusic, arg);
    }
}

// @ 0x00bf1fd0
int cCivilization::FUN_00bf1fd0(int specialty)
{
    if (specialty == 4)
        return 1;

    int score = 0;
    if (!mField8a && FUN_00bf0f40((void*)this) == MapSpecialty(specialty))
        score = 3;

    score += (cCivilization_CountSpecialty((int)this, specialty, 1) +
              cCivilization_CountSpecialty((int)this, specialty, 0)) * g_civStarCountScale;

    Noun** city = *(Noun***)((char*)this + 0x9c);
    Noun** cityEnd = *(Noun***)((char*)this + 0xa0);
    for (; city != cityEnd; ++city)
    {
        cCity* c = *(cCity**)city;
        if (c->GetVehicleSpecialty() != specialty)
            continue;
        int age = c->GetHousingAmount() / g_cityHousingDiv;
        int chosen;
        if (!c->mCounterConvBusy)
        {
            if (mField89)
                continue;
            chosen = age > 6 ? age : 6;
        }
        else
        {
            if (mField89)
                continue;
            chosen = age > 3 ? age : 3;
        }
        score += chosen;
    }

    return score < 0x25 ? score : specialty;
}

// @ 0x00bf2270
byte ISimulatorSerializable::ReadSerialized(void* stream)
{
    int ok1 = cGameData_Read((void*)this, stream);
    int ok2 = FUN_00b6e340((char*)this + 0x3c, stream);
    bool ok = ok1 != 0 && ok2 != 0;

    void* w = (*(void*(__fastcall**)(void*))((char*)*(int*)stream + 0x20))(stream);
    void* dst = (*(void*(__fastcall**)(void*))((char*)*(int*)w + 0x18))(w);
    ReadInt32(dst, &mFieldC4, 1, 0);

    w = (*(void*(__fastcall**)(void*))((char*)*(int*)stream + 0x20))(stream);
    dst = (*(void*(__fastcall**)(void*))((char*)*(int*)w + 0x18))(w);
    ReadInt32(dst, &mFieldC8, 1, 0);

    w = (*(void*(__fastcall**)(void*))((char*)*(int*)stream + 0x20))(stream);
    dst = (*(void*(__fastcall**)(void*))((char*)*(int*)w + 0x18))(w);
    ReadInt32(dst, &mFieldCC, 1, 0);

    char serializer[0xa18];
    cVarListSerializer_ctor(serializer, (void*)this, (void*)&g_civAttributes, 0x1a80d26);
    int ok3 = cVarListSerializer_Serialize(serializer, stream);
    ok = ok && ok3 != 0;

    void* host = (void*)0;
    if (this != 0)
        host = (char*)this + 0x38;
    void* server = SP_MessageServer();
    (*(void(__fastcall**)(void*, void*, int))((char*)*(int*)server + 0x20))(server, host, 0x20c089c);
    UpdateCityMusicPosition((void*)this);
    return ok ? 1 : 0;
}

// @ 0x00bf2380 -- release every resource handle whose manager no longer knows it.
static int ReleaseDeadResources(void* map)
{
    for (RanNode* n = *(RanNode**)((char*)map + 8); n != (RanNode*)((char*)map + 4);
         n = (RanNode*)RBTreeIncrement(n))
    {
        if (n->mField14 == 0)
            continue;
        void* mgr = EA_ResourceMan_GetManager();
        int ok = (*(int(__fastcall**)(void*, void*, int, int, int, int, int))((char*)*(int*)mgr + 0xc))
                     (mgr, (void*)&n->mField14, 0, 0, 0, 0, 0);
        if (!ok)
        {
            n->mField14 = 0;
            n->mField18 = 0;
            n->mField1c = 0;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// Simulator::cGameData
// ---------------------------------------------------------------------------
// The three specialty marker bytes 0x484/0x486/0x488/0x489/0x48c live past the 0x34-byte
// public head of cGameData; address them through a raw pointer like the original does.
// @ 0x00bf23d0
int cGameData::func40h()
{
    byte* self = (byte*)this;
    *(int*)(self + 0x484) = 0;
    *(int*)(self + 0x488) = 0;
    *(int*)(self + 0x48c) = 0;

    IntVec list = {0, 0, 0};
    void* sphere = cTerrainEditor_GetCurrentTerrainSphere(SP_NounManager());
    if (sphere != 0)
    {
        FUN_00555e80(*(int*)((char*)sphere + 0x10fc), &list);
        FUN_00555e80(*(int*)((char*)sphere + 0x1100), &list);
        FUN_00555e80(*(int*)((char*)sphere + 0x1104), &list);
    }

    bool anyBiped = false;
    int i = 0;
    uint n = (uint)((list.end - list.begin) >> 2);
    if (n != 0)
    {
        do
        {
            int kind = cCity_UnknownBef980((void*)this, list.begin[i]);
            if (kind == 2 || kind == 5 || kind == 8)
                anyBiped = true;
            if (kind != -1)
            {
                int need = SpecialtySlots(kind);
                if (need <= (int)((mListEnd - mListBegin) >> 2) || DAT_0168bd6c != 0)
                    self[0x484 + kind] = 1;
            }
            ++i;
        } while (i < n);

        if (anyBiped)
            goto done;
    }

    {
        int spec = CitySpecialty((Noun*)this);
        int kind;
        if (spec == 0)
            kind = 2;
        else if (spec == 1)
            kind = 8;
        else if (spec == 2)
            kind = 5;
        else
            goto done;

        int need = SpecialtySlots(kind);
        if (need <= (int)((mListEnd - mListBegin) >> 2))
            self[0x484 + kind] = 1;
    }

done:
    int cityCount = (int)((mListEnd - mListBegin) >> 2);
    if (DAT_0167a60c == 0)
    {
        int obj = (int)EAAllocate(200, DAT_0145f924, 0, 0, 0, 0);
        if (obj != 0)
        {
            SimSingleton_ctor((void*)obj);
            DAT_0167a60c = obj;
        }
        else
            DAT_0167a60c = 0;
    }
    if (cityCount == *(int*)(DAT_0167a60c + 0xac))
    {
        self[0x486] = 0;
        self[0x48c] = 0;
        self[0x489] = 0;
    }

    if (list.begin != 0 && *(int*)((char*)list.begin - 4) != 0)
        operator_delete(list.begin);
    return 1;
}

// @ 0x00bf2a60
int cGameData::FUN_00bf2a60()
{
    for (Noun** t = mListBegin; t != mListEnd; ++t)
    {
        IntVec* members = (IntVec*)cTribe_GetMembers(*t);
        for (void** m = (void**)members->begin; m != (void**)members->end; ++m)
            (*(void(__fastcall**)(void*))((char*)*(int*)*m + 0x40))(*m);
    }
    for (Noun** v = mVehicleBegin; v != mVehicleEnd; ++v)
        (*(void(__fastcall**)(void*))((char*)*(int*)*v + 0x40))(*v);
    ReleaseDeadResources((char*)this + 0x6c);
    return 1;
}

// ---------------------------------------------------------------------------
// 32-byte StarRecord vector helpers.  The two vtable pointers are stored as the
// retail image literals (0x1465d54 / 0x14664450).
// ---------------------------------------------------------------------------
// @ 0x00bf2840
StarRecord* StarCopyCtorRange(StarRecord** out, StarRecord* first, StarRecord* last, StarRecord* dst)
{
    *out = dst;
    if (first != last)
    {
        do
        {
            if (dst != 0)
            {
                ((StarRecord*)dst)->vptr = 0x01465d54;
                ((StarRecord*)dst)->pad04 = 0;
                *(int*)((char*)dst + 8) = *(int*)((char*)first + 8);
                *(int*)((char*)dst + 0xc) = *(int*)((char*)first + 0xc);
                *(int*)((char*)dst + 0x10) = *(int*)((char*)first + 0x10);
                *(int*)((char*)dst + 0x14) = *(int*)((char*)first + 0x14);
                *(byte*)((char*)dst + 0x18) = *(byte*)((char*)first + 0x18);
                *(int*)((char*)dst + 0x1c) = *(int*)((char*)first + 0x1c);
                ((StarRecord*)dst)->vptr = 0x01464450;
            }
            first = (StarRecord*)((char*)first + 0x20);
            dst = (StarRecord*)((char*)dst + 0x20);
        } while (first != last);
        *out = dst;
    }
    return (StarRecord*)out;
}

// @ 0x00bf28b0
void StarAssignForward(void* dst, void* last, void* src)
{
    for (; dst != last; dst = (char*)dst + 0x20)
    {
        *(int*)((char*)dst + 8) = *(int*)((char*)src + 8);
        *(int*)((char*)dst + 0xc) = *(int*)((char*)src + 0xc);
        *(int*)((char*)dst + 0x10) = *(int*)((char*)src + 0x10);
        *(int*)((char*)dst + 0x14) = *(int*)((char*)src + 0x14);
        *(byte*)((char*)dst + 0x18) = *(byte*)((char*)src + 0x18);
        *(int*)((char*)dst + 0x1c) = *(int*)((char*)src + 0x1c);
    }
}

// @ 0x00bf28f0
void StarFillN(void* dst, uint n, void* src)
{
    for (; n > 0; --n, dst = (char*)dst + 0x20)
    {
        if (dst != 0)
        {
            ((StarRecord*)dst)->vptr = 0x01465d54;
            ((StarRecord*)dst)->pad04 = 0;
            *(int*)((char*)dst + 8) = *(int*)((char*)src + 8);
            *(int*)((char*)dst + 0xc) = *(int*)((char*)src + 0xc);
            *(int*)((char*)dst + 0x10) = *(int*)((char*)src + 0x10);
            *(int*)((char*)dst + 0x14) = *(int*)((char*)src + 0x14);
            *(byte*)((char*)dst + 0x18) = *(byte*)((char*)src + 0x18);
            *(int*)((char*)dst + 0x1c) = *(int*)((char*)src + 0x1c);
            ((StarRecord*)dst)->vptr = 0x01464450;
        }
    }
}

// @ 0x00bf2960
void StarCopyCtorRange2(StarRecord* first, StarRecord* last, StarRecord* dst)
{
    for (; first != last; first = (StarRecord*)((char*)first + 0x20))
    {
        if (dst != 0)
        {
            ((StarRecord*)dst)->vptr = 0x01465d54;
            ((StarRecord*)dst)->pad04 = 0;
            *(int*)((char*)dst + 8) = *(int*)((char*)first + 8);
            *(int*)((char*)dst + 0xc) = *(int*)((char*)first + 0xc);
            *(int*)((char*)dst + 0x10) = *(int*)((char*)first + 0x10);
            *(int*)((char*)dst + 0x14) = *(int*)((char*)first + 0x14);
            *(byte*)((char*)dst + 0x18) = *(byte*)((char*)first + 0x18);
            *(int*)((char*)dst + 0x1c) = *(int*)((char*)first + 0x1c);
            ((StarRecord*)dst)->vptr = 0x01464450;
        }
        dst = (StarRecord*)((char*)dst + 0x20);
    }
}

// @ 0x00bf29c0
void StarAssignForward2(StarRecord* first, StarRecord* last, StarRecord* dst)
{
    for (; first != last; first = (StarRecord*)((char*)first + 0x20))
    {
        *(int*)((char*)dst + 8) = *(int*)((char*)first + 8);
        *(int*)((char*)dst + 0xc) = *(int*)((char*)first + 0xc);
        *(int*)((char*)dst + 0x10) = *(int*)((char*)first + 0x10);
        *(int*)((char*)dst + 0x14) = *(int*)((char*)first + 0x14);
        *(byte*)((char*)dst + 0x18) = *(byte*)((char*)first + 0x18);
        *(int*)((char*)dst + 0x1c) = *(int*)((char*)first + 0x1c);
        dst = (StarRecord*)((char*)dst + 0x20);
    }
}

// @ 0x00bf2a10
void StarAssignBackward(StarRecord* last, StarRecord* first, StarRecord* dstEnd)
{
    for (; first != last; first = (StarRecord*)((char*)first - 0x20))
    {
        *(int*)((char*)dstEnd - 0x18) = *(int*)((char*)first - 0x18);
        *(int*)((char*)dstEnd - 0x14) = *(int*)((char*)first - 0x14);
        *(int*)((char*)dstEnd - 0x10) = *(int*)((char*)first - 0x10);
        *(int*)((char*)dstEnd - 0xc) = *(int*)((char*)first - 0xc);
        *(byte*)((char*)dstEnd - 8) = *(byte*)((char*)first - 8);
        *(int*)((char*)dstEnd - 4) = *(int*)((char*)first - 4);
        dstEnd = (StarRecord*)((char*)dstEnd - 0x20);
    }
}

// ---------------------------------------------------------------------------
// id -> StarRecord map helpers (eastl::rbtree find; the map head is an anchor node)
// ---------------------------------------------------------------------------
// @ 0x00bf2c60
void __fastcall StarMapInit(StarTree* map)
{
    void* p = map;
    int* nil = (int*)((char*)p + 4);
    *(int*)((char*)p + 8) = 0;
    *(int*)((char*)p + 0xc) = 0;
    *(int*)((char*)p + 0x10) = 0;
    *nil = (int)nil;
    *(int*)((char*)p + 8) = (int)nil;
    *(int*)((char*)p + 0xc) = 0;
    *(char*)((char*)p + 0x10) = 0;
    *(int*)((char*)p + 0x14) = 0;
}

// @ 0x00bf2c80
bool StarTree::ContainsMap(int key)
{
    TreeIter it = find(key);
    return it.mpNode != (void*)((int)this + 4);
}

// @ 0x00bf2cb0
bool cGameData::StarMapContainsMap2(int value)
{
    StarTree* tree = (StarTree*)((char*)this + 0x6c);
    TreeIter it = tree->find(value);
    return it.mpNode != (void*)((int)tree + 4);
}

// ---------------------------------------------------------------------------
// more tree insert helpers / list walks (no marker symbol matched; write them so the
// slice covers every VA).
// ---------------------------------------------------------------------------
struct OtherNode
{
    void* mLeft;                           // +0x00
    OtherNode* mParent;                    // +0x04
    void* mRight;                          // +0x08
    void* pad0c;                           // +0x0c
    int   mField14;                        // +0x14
    void* mField18;                        // +0x18
    int   mField1c;                        // +0x1c
};

// insert helper: node key 0x10 hold a uint32 key, value 4 dwords at 0x10..0x1c (vector<int>)
// @ 0x00bf1d90
void MapInsert4(void* self, void** outIt, void* anchor, int* value, char hint)
{
    int side = 0;
    if (hint == 0 && anchor != (char*)self + 4 && *(int*)((char*)anchor + 0x10) <= *value)
        side = 1;

    int node = (int)EAAllocate(0x20, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (node + 0x10 != 0)
    {
        *(int*)(node + 0x10) = value[0];
        *(int*)(node + 0x14) = value[1];
        *(int*)(node + 0x18) = value[2];
        *(int*)(node + 0x1c) = value[3];
    }
    RBTreeInsert((void*)node, anchor, (char*)self + 4, side);
    ++*(int*)((char*)self + 0x14);
    *outIt = (void*)node;
}

// @ 0x00bf2660
int cGameData::FUN_00bf2660(int)
{
    return func40h();
}

// @ 0x00bf2670
bool CallSlot1cForEach(void* arg, void* map)
{
    for (OtherNode* n = *(OtherNode**)((char*)map + 8); n != (OtherNode*)((char*)map + 4);
         n = (OtherNode*)RBTreeIncrement(n))
    {
        void* obj = *(void**)((char*)n + 0x10);
        if (obj != 0)
            (*(void(__thiscall**)(void*, void*))((char*)*(int*)obj + 0x1c))(obj, arg);
    }
    return true;
}

// value is {ptr, float} at +0x10..+0x17
// @ 0x00bf27a0
void MapInsertPtrFloat(void* self, void** outIt, void* anchor, int* value, char hint)
{
    int side = 0;
    if (hint == 0 && anchor != (char*)self + 4 && *(unsigned*)((char*)anchor + 0x10) <= *(unsigned*)value)
        side = 1;

    int node = (int)EAAllocate(0x18, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* slot = (int*)(node + 0x10);
    if (slot != 0)
    {
        *slot = value[0];
        if (value[0] != 0)
            (*(void(__fastcall**)(void*))((char*)*(int*)value[0]))((void*)value[0]);
        slot[1] = value[1];
    }
    RBTreeInsert((void*)node, anchor, (char*)self + 4, side);
    ++*(int*)((char*)self + 0x14);
    *outIt = (void*)node;
}
