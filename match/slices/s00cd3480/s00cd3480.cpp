// Slice s00cd3480 -- tribe-mission manager / tribe-mode strategy / terrain helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- globals / vtables (addresses for equivalence mapping) -------------------
extern void* g_vt147734c[];    // 0x0147734c
extern void* g_vt1477328[];    // 0x01477328
extern void* g_vt1477318[];    // 0x01477318
extern void* g_vt154df28[];    // 0x0154df28
extern void* g_vt14774b0[];    // 0x014774b0
extern void* g_appProps;       // 0x015fd918
extern void* g_1581288;        // 0x01581288
extern uint32_t g_169b27c;     // 0x0169b27c
extern const float g_fltmax;   // 0x01477430
extern const char g_StrTRGMac[];    // 0x01477468
extern const char g_StrTRG[];       // 0x01477458
extern const char g_StrTRGBegin[];  // 0x014774a4
extern const float g_fltOne;        // 0x01485720
extern const float g_fltTwo;        // 0x01470f1c

// ---- shared stand-ins -------------------------------------------------------
struct WString {                    // eastl::basic_string<wchar_t>, 12 bytes
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCap;
    void F_0056e2d0(const WString* src);   // copy ctor
    void F_00579a90(const wchar_t* s);     // range_initialize
};
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
struct InsertOut { HashNode* mNode; int mPad; unsigned char mSecond; };
struct MissionPair { uint32_t mKey; void* mValue; };
struct MissionMgrBase {
    unsigned char Write(void* stream);                      // 0xb6f570
    unsigned char Read(void* stream);                       // 0xb6f5e0
};
struct cVarListSerializer {
    char mData[0xa14];
    void Ctor(void* obj, void* list, unsigned int sig);     // 0x692f90 (ret 0xc)
    bool Serialize(void* stream);                           // 0x692900
    bool Read(void* stream);                                // 0x693e10
};
struct TribeMissionMgr {
    unsigned char Write(void* stream);                      // 0x00cd3480
    unsigned char Read(void* stream);                       // 0x00cd3530
};

// ---- cdecl external callees --------------------------------------------------
void*         FUN_00b3d400(void);                            // 0x00b3d400
void*         NounManager();                                 // 0x00b3d300
void*         GetGameTerrainCursor();                        // 0x00b30d70
void*         GetGameInputManager();                         // 0x00b3d250
void          FUN_00adf390(int a);                           // 0x00adf390
void*         GetTriggerMgr();                               // 0x00b3d4d0
void          FUN_00c77380(void*, int);                      // unused
void          FUN_00c79f00(void*, int, int);                 // unused
void          FUN_00e18200(void* a, void* b, int c, int d, int e); // 0x00e18200
int           FNV1_String8(const char* s, uint32_t h, int a); // 0x00932e80
unsigned char GetPropertyAsUint32Array(void* a, int b, void* c, void* d); // 0x006a0840
void          WriteUint32(void* s, void* p, int a, int b);   // 0x0093aa70
int           ReadInt32(void* s, void* p, int c, int f);     // 0x0093a780
void*         FUN_00401010();                                // 0x00401010
void*         GetCursorTable();                              // 0x0067cab0
void*         AchievementsController();                      // 0x00675250
void          F_00f47380(void* p);                           // 0x00f47380
unsigned char ToXml_00ac8050(void* s, int a, void* value);   // 0x00ac8050
WString*      F_0093c5a0(WString* out, const char* s, int n); // 0x0093c5a0
struct CActTarget {
    int mA, mB, mC, mD, mE, mF, mG, mH, mI, mJ, mK, mL;  // 0x30 bytes
    void Ctor(void* t);                                            // 0xad7a30 (ret 4)
    void Dtor();                                                   // 0xad7ad0
};
struct CTerrain {
    char pad[0x1150];
    int mCityHallPos[3];                                         // +0x1150
    unsigned char F772c0(int key);       // 0x00c772c0
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
struct CUnk { virtual void AddRef(); virtual void Release(); };
// SP::cLocalInputState is embedded at cTribeModeStrategy+0x1e0; these are *direct* (non-virtual)
// calls in the original, unlike the GameInputManager vtable calls that follow them.
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
struct CTool {
    char mPad[0x34];
    void* mTarget;                                                // +0x34
};

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
    void M_b6f4e0(void* a);
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
    void F_cd43c0(int a);
    bool F_cd4490();
    unsigned int F_cd4460(int a);
    unsigned int F_cd44a0();
    unsigned int F_cd44e0(void* a, void* b);
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

// @ 0x00cd35c0
void TM::F_cd35c0(int a, int b)
{
    M_b6f7d0();
    if (*(unsigned char*)((char*)this + 0x70) != 0) {
        int p = *(int*)((char*)this + 0x68);
        if (p) ((void(__thiscall*)(void*))(*(void***)p)[0x80 / 4])((void*)p);
        int q = *(int*)((char*)this + 0x74);
        if (q) ((void(__thiscall*)(void*))(*(void***)q)[0x80 / 4])((void*)q);
        M_b6f650(a, b);
        *(unsigned char*)((char*)this + 0x70) = 0;
    }
}

// @ 0x00cd3610
void TM::F_cd3610()
{
    M_b6f760();
    void* panel = FUN_00b3d400();
    if (panel != 0 && *(int*)((char*)this + 0x74) != 0) {
        if (!((CPanel*)panel)->HasMissionCard(*(void**)((char*)this + 0x74)))
            ((CPanel*)panel)->AddMissionCard(*(void**)((char*)this + 0x74), 0, 1, 0);
    }
}

// @ 0x00cd3650
void TM::F_cd3650()
{
    void* p = *(void**)((char*)this + 0x74);
    if (p != 0) {
        *(void**)((char*)this + 0x74) = 0;
        ((CUnk*)p)->Release();
    }
    M_b70070();
}

// @ 0x00cd3670
void TM::F_cd3670(void* a)
{
    M_b6f820(a);
    if (a == *(void**)((char*)this + 0x74)) {
        if (FUN_00b3d400() != 0) {
            ((CPanel*)FUN_00b3d400())->RemoveMissionCard(*(void**)((char*)this + 0x74));
        }
        void* p = *(void**)((char*)this + 0x74);
        if (p != 0) {
            *(void**)((char*)this + 0x74) = 0;
            ((CUnk*)p)->Release();
        }
    }
}

// @ 0x00cd3760
void TM::F_cd3760(int a)
{
    M_b6f4e0((void*)a);
    if (a != 0) {
        HashTable* t = (HashTable*)((char*)this + 0x78);
        HashIter it;
        t->find(&it, (const uint32_t*)&a);
        if (it.mNode != (HashNode*)t->mppBuckets[t->mnBucketCount]) {
            void* p = *(void**)((char*)it.mNode + 4);
            ((void(__thiscall*)(void*))(*(void***)p)[0x80 / 4])((void*)p);
        }
    }
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

// ============================================================ 0x00cd40c0
unsigned int F_cd40c0(void* tribe)
{
    if (((CMgr*)NounManager())->GetPlayerTribe() != tribe) {
        if (((CTribe*)tribe)->GetAdultPopulation() > 0)
            return 1;
    }
    return 0;
}

// @ 0x00cd4160
unsigned char TM::F_cd4160(void* p)
{
    void* base = (char*)p + 0x34;
    void* o = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    return ((unsigned char(__thiscall*)(void*))(*(void***)o)[0x50 / 4])(o);
}

// @ 0x00cd40f0
void TM::F_cd40f0(void* p)
{
    void* base = (char*)p + 0x34;
    void* o = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    if (!((unsigned char(__thiscall*)(void*))(*(void***)o)[0x50 / 4])(o))
        ((void(__thiscall*)(void*, int))(*(void***)this)[0xf0 / 4])(this, 0x29b);
    void* o2 = ((void*(__thiscall*)(void*))(*(void***)base)[0x34 / 4])(base);
    ((void(__thiscall*)(void*, int))(*(void***)o2)[0x54 / 4])(o2, 1);
    void* cur = GetGameTerrainCursor();
    ((void(__thiscall*)(void*))(*(void***)cur)[0x74 / 4])(cur);
    cur = GetGameTerrainCursor();
    ((void(__thiscall*)(void*))(*(void***)cur)[0xc8 / 4])(cur);
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

// @ 0x00cd43c0
void TM::F_cd43c0(int a)
{
    void* o = ((void*(__thiscall*)(void*, int))(*(void***)this)[0x6c / 4])(this, a);
    ((C9630*)o)->M();
    (void)o;
    (void)a;
}

// @ 0x00cd4460
unsigned int TM::F_cd4460(int a)
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        if (s->F772c0(a))
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
unsigned int TM::F_cd44a0()
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        if (s->F772c0(0x056d1871))
            return 0;
    }
    return 1;
}

// @ 0x00cd44e0
unsigned int TM::F_cd44e0(void* a, void* b)
{
    uint32_t v = *(uint32_t*)b;
    void* p = ((void*(__thiscall*)(void*))(*(void***)a)[0x20 / 4])(a);
    void* s = ((void*(__thiscall*)(void*))(*(void***)p)[0x18 / 4])(p);
    WriteUint32(s, &v, 1, 0);
    return 1;
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
        CTerrain* te = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
        int v = *(int*)(local_8 + (int)idx * 4);
        int local_4 = 0;
        te->F77380(0x055d6335, &local_4);
        te->F79f00(0x055d6335, local_4 + v);
    }
}

// @ 0x00cd3fb0
void F_cd3fb0(int a)
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
    if (s != 0) {
        s->F77bf0(a);
        return;
    }
}

// @ 0x00cd3fd0
void F_cd3fd0(int a)
{
    CTerrain* s = ((CMgr*)NounManager())->GetCurrentTerrainSphere();
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
    t.Ctor(tgt);
    CTrig* mgr = (CTrig*)GetTriggerMgr();
    mgr->PostAction(id, &t, 0);
    t.Dtor();
}

// @ 0x00cd4580
struct ThemeMgr { char pad[0x100]; ThemeMgr(); };
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

// @ 0x00cd3480
unsigned char TM::WriteTribe(void* stream)
{
    uint32_t sig = 0xf4336f3c;
    {
        void* o = ((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
        void* s = ((void*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
        WriteUint32(s, &sig, 1, 0);
    }
    unsigned char b = ((MissionMgrBase*)this)->Write(stream);
    if (*(void**)((char*)this + 0x6c) != 0) {
        void* o = *(void**)((char*)this + 0x6c);
        if (((unsigned int(__thiscall*)(void*))(*(void***)o)[0x60 / 4])(o) == 5)
            ((void(__thiscall*)(void*, void*))(*(void***)((char*)this - 8))[0x30 / 4])((char*)this - 8, o);
    }
    cVarListSerializer ser;
    ser.Ctor((char*)this - 8, (void*)0x0157ee90, 0x1a80d26);
    if (b) {
        if (ser.Serialize(stream))
            return 1;
    }
    return 0;
}

// @ 0x00cd3530
unsigned char TM::ReadTribe(void* stream)
{
    {
        void* o = ((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
        void* s = ((void*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
        uint32_t sig = 0;
        ReadInt32(s, &sig, 1, 0);
    }
    unsigned char b = ((MissionMgrBase*)this)->Read(stream);
    cVarListSerializer ser;
    ser.Ctor((char*)this - 8, (void*)0x0157ee90, 0x1a80d26);
    if (b) {
        if (ser.Read(stream))
            return 1;
    }
    return 0;
}

// @ 0x00cd36f0
bool ForEachStructure(void* visitor, HashTable* t)
{
    HashNode* i = *(HashNode**)t->mppBuckets;
    HashNode** slot = t->mppBuckets;
    if (i == 0) {
        if (*slot != 0) {
            ++slot;
        } else {
            do { ++slot; } while (*slot == 0);
        }
        i = *slot;
    }
    HashNode* end = t->mppBuckets[t->mnBucketCount];
    while (i != end) {
        void* v = i->mValue;
        if (v != 0)
            ((void(__thiscall*)(void*, void*))(*(void***)v)[0x1c / 4])(v, visitor);
        i = i->mNext;
        if (i == 0) {
            do { i = *++slot; } while (i == 0);
        }
    }
    return 1;
}

// @ 0x00cd37b0
void ReadSTLMapT(void* stream, HashTable* map)
{
    map->F_00961d60(map->mppBuckets, map->mnBucketCount);
    int count = 0;
    map->mnElementCount = 0;
    {
        void* o = ((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
        void* s = ((void*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
        ReadInt32(s, &count, 1, 0);
    }
    for (int n = 0; n < count; ++n) {
        void* node = 0;
        uint32_t key = 0;
        {
            void* o = ((void*(__thiscall*)(void*))(*(void***)stream)[0x20 / 4])(stream);
            void* s = ((void*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
            ReadInt32(s, &key, 1, 0);
        }
        ((void(__thiscall*)(void*))(*(void***)stream)[0x1c / 4])(stream);
        if (node != 0) {
            node = 0;
            ((void(__thiscall*)(void*))(*(void***)node)[0x4 / 4])(node);
        }
        void* val = 0;
        ((void(__thiscall*)(void*, unsigned int, void**, int))(*(void***)stream)[0x28 / 4])(
            stream, 0x34364118, &val, 0);
        ((void(__thiscall*)(void*))(*(void***)stream)[0x1c / 4])(stream);
        MissionPair pair;
        pair.mKey = key;
        pair.mValue = val;
        if (val != 0)
            ((void(__thiscall*)(void*))(*(void***)val)[0])(val);
        InsertOut out;
        out.mSecond = 0;
        map->insert(&out, &pair, 0);
        if (pair.mValue != 0) {
            ((void(__thiscall*)(void*))(*(void***)pair.mValue)[0x4 / 4])(pair.mValue);
        }
        if (out.mSecond == 0) {
            void** slot = (void**)((char*)out.mNode + 4);
            void* old = *slot;
            if (val != old) {
                if (val != 0)
                    ((void(__thiscall*)(void*))(*(void***)val)[0])(val);
                *slot = val;
                if (old != 0)
                    ((void(__thiscall*)(void*))(*(void***)old)[0x4 / 4])(old);
            }
        }
        if (val != 0)
            ((void(__thiscall*)(void*))(*(void***)val)[0x4 / 4])(val);
    }
    ((void(__thiscall*)(void*))(*(void***)stream)[0x1c / 4])(stream);
}

// @ 0x00cd3920
bool WriteSTLMapT(void* stream, const char* name, HashTable* map)
{
    uint32_t flags = 0;
    bool ok = true;
    if (map->mnElementCount == 0)
        return ok;
    WString wname;
    uint32_t fb = 1;
    if (name != 0) {
        F_0093c5a0(&wname, name, -1);
        fb = 3;
    } else {
        wname.mBegin = 0; wname.mEnd = 0; wname.mCap = 0;
        wname.F_00579a90(0);
        fb = 2;
    }
    WString key;
    key.F_0056e2d0(&wname);
    if (fb & 2) {
        if (((unsigned)((char*)wname.mEnd - (char*)wname.mBegin) & 0xfffffffe) > 2 && wname.mBegin != 0)
            F_00f47380(wname.mBegin);
    }
    if (fb & 1) {
        if (((unsigned)((char*)key.mEnd - (char*)key.mBegin) & 0xfffffffe) > 2 && key.mBegin != 0)
            F_00f47380(key.mBegin);
    }
    {
        void* a = key.mBegin;
        if (a == key.mEnd)
            a = (void*)0x013f6254;
        ((void(__thiscall*)(void*, void*))(*(void***)stream)[0])(stream, a);
    }
    HashNode* i = *(HashNode**)map->mppBuckets;
    HashNode** slot = map->mppBuckets;
    if (i == 0) {
        if (*slot != 0) {
            ++slot;
        } else {
            do { ++slot; } while (*slot == 0);
        }
        i = *slot;
    }
    HashNode* end = map->mppBuckets[map->mnBucketCount];
    bool flag = ok;
    while (i != end) {
        if (flag) {
            if (!ToXml_00ac8050(stream, 0, &i->mValue))
                flag = false;
            else
                flag = true;
        } else {
            flag = false;
        }
        i = i->mNext;
        if (i == 0) {
            do { i = *++slot; } while (i == 0);
        }
    }
    {
        void* a = key.mBegin;
        if (a == key.mEnd)
            a = (void*)0x013f6254;
        ((void(__thiscall*)(void*, void*))(*(void***)stream)[0x4 / 4])(stream, a);
    }
    if (((unsigned)((char*)key.mEnd - (char*)key.mBegin) & 0xfffffffe) > 2 && key.mBegin != 0)
        F_00f47380(key.mBegin);
    return ok;
}

// @ 0x00cd3ab0
TM::~TM()
{
    *(void**)this = g_vt147734c;
    *(void**)((char*)this + 8) = g_vt1477328;
    *(void**)((char*)this + 0x10) = g_vt1477318;
    HashTable* t = (HashTable*)((char*)this + 0x78);
    g_169b27c = 0;
    t->F_00961d60(t->mppBuckets, t->mnBucketCount);
    t->mnElementCount = 0;
    if (t->mnBucketCount > 1)
        F_00f47380(t->mppBuckets);
    void* p = *(void**)((char*)this + 0x74);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0x4 / 4])(p);
    M_b705a0();
}

// @ 0x00cd3b60
TM::TM()
{
    M_b70820();
    *(void**)this = g_vt147734c;
    *(void**)((char*)this + 8) = g_vt1477328;
    *(void**)((char*)this + 0x10) = g_vt1477318;
    *(int*)((char*)this + 0x74) = 0;
    *(float*)((char*)this + 0x88) = g_fltOne;
    *(float*)((char*)this + 0x8c) = g_fltTwo;
    *(int*)((char*)this + 0x84) = 0;
    *(int*)((char*)this + 0x90) = 0;
    *(int*)((char*)this + 0x80) = 1;
    *(void**)((char*)this + 0x7c) = g_vt154df28;
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

// @ 0x00cd4280
void TM::StartTribe()
{
    ((CTrig*)GetTriggerMgr())->SetEnabled(1);
    void* tribe = ((CMgr*)NounManager())->GetPlayerTribe();
    void* obj = ((void*(__thiscall*)(void*))(*(void***)tribe)[0xac / 4])(tribe);
    void* tool = ((CTribe*)tribe)->GetToolOfType(10);
    void* trig = ((CTrig*)GetTriggerMgr())->PostTrigger(g_StrTRGBegin, 1, 1, 0, 0, 0);
    {
        CActTarget t;
        t.Ctor((char*)tribe + 0x120);
        ((CTrig*)GetTriggerMgr())->PostAction(0x3d7f90a, &t, trig);
        t.Dtor();
    }
    {
        CActTarget t;
        t.Ctor(obj != 0 ? (char*)obj + 0x34 : 0);
        ((CTrig*)GetTriggerMgr())->PostAction(0xaa227986, &t, trig);
        t.Dtor();
    }
    {
        CActTarget t;
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
