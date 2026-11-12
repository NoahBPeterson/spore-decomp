// src/game/SPGonzago/SPTribeMissionManager.cpp -- migrated from slice(s) s00cd3480, s0135d100 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeMissionManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "SP/cTribe.h"
#include "SP/cLocalInputState.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00cd36c0();
extern "C" void fn_00bca960();
extern "C" void fn_00b6f550();
extern "C" void fn_00cd37b0();
extern "C" void fn_00b6fc90();
extern "C" void fn_00cd36f0();
extern "C" void fn_00cd3920();

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
extern T g_0157ee90, g_0157eecc;
extern "C" void fn_00692ca0();
extern "C" void fn_00ac8050();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00cd36c0();
extern "C" void fn_00bca960();
extern "C" void fn_00b6f550();
extern "C" void fn_00cd37b0();
extern "C" void fn_00b6fc90();
extern "C" void fn_00cd36f0();
extern "C" void fn_00cd3920();
// ---- items of slice s0135d100 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern T g_0157ee90, g_0157eecc;

// ---- items of slice s00cd3480 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vt147734c[];    // 0x0147734c
extern void* g_vt1477328[];    // 0x01477328
extern void* g_vt1477318[];    // 0x01477318
extern uint32_t g_169b27c;     // 0x0169b27c
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
void*         FUN_00b3d400(void);                            // 0x00b3d400
void          WriteUint32(void* s, void* p, int a, int b);   // 0x0093aa70
int           ReadInt32(void* s, void* p, int c, int f);     // 0x0093a780
void          F_00f47380(void* p);                           // 0x00f47380
unsigned char ToXml_00ac8050(void* s, int a, void* value);   // 0x00ac8050
WString*      F_0093c5a0(WString* out, const char* s, int n); // 0x0093c5a0
struct CUnk { virtual void AddRef(); virtual void Release(); };
struct LocalInputState {
    char mPad[0x10];                                             // +0x1e0 .. +0x1ef
    void OnMouseDown(int button, float x, float y, int state);   // 0x00697ab0
    void OnMouseUp(int button, float x, float y, int state);     // 0x00697af0
    void OnMouseWheel(float x, float y, int button);             // 0x00697b20
};
struct CPanel {
    unsigned char HasMissionCard(void* card);   // 0x00e15cd0 thiscall ret 4
    void RemoveMissionCard(void* card);          // 0x00e17fb0 thiscall ret 4
    void ExpandMissionCard(void* card);          // 0x00e15b90 thiscall ret 4
    void AddMissionCard(void* card, int a, int b, int c); // 0x00e18200 thiscall ret 0x10
    void SetupMissionCard(void* card, int a, int b, int c); // 0x00e18200 thiscall ret 0x10
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
// ---- items of slice s00cd3480 end

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
            typedef void (__thiscall* ReleaseFunction)(void*);
            void** table = *(void***)p;
            _ReadWriteBarrier();
            ReleaseFunction release = (ReleaseFunction)table[1];
            release(p);
        }
    }
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

// @ 0x0135d720
void FUN_0135d720()
{
    g_0157ee90 = T("mpTribeToTribeMission", 0xb43c938eu, 0x74, fn_00692ca0, fn_00cd36c0, fn_00bca960, fn_00c2e4e0, fn_00692fb0, fn_00b6f550, fn_00ac8050);
    g_0157eecc = T("mTribeToTribeMissionMap", 0x743c9504u, 0x78, fn_00692ca0, fn_00cd37b0, fn_00b6fc90, fn_00c2e4e0, fn_00692fb0, fn_00cd36f0, fn_00cd3920);
}
