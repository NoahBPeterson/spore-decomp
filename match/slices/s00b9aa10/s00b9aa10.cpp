// Slice s00b9aa10: FUN_00b9aa10 (~1.6 KB, __cdecl), places the sub-spawn items of a species
// archetype around a centre position (recursive: an archetype's own sub-item list at +0x3b0
// calls this function again around the newly placed spot).
//
// For every archetype id in `ids` it fetches the species archetype, checks that the editor's
// species manager can match something for it (FUN_004dfff0), rolls a count between the
// archetype's min/max (+0x300/+0x304), a chance (0x4934caca scaled by a Vector3 property),
// then for each placement asks FUN_00b97720 for a position, records the placement in the
// 16-byte-entry table at 0x0168890c (outside game mode), places the object (FUN_00b93f40),
// nudges it on the spot grid, places its spawn definitions (PlaceSpawnDefinitionsOnPlanet)
// and recurses for its own sub-items.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00b9b090).
#include "types.h"

struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

class RandomLinearCongruential {
public:
    double   RandomDoubleUniform();           // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t n); // 0x00a68fb0
};
extern RandomLinearCongruential g_Random;   // 0x016888e8
float RandomFloatRange(float lo, float hi); // 0x00b906a0

void operator delete[](void* p);   // 0x00f47380

class PropertyList;
float GetPropertyFloat(PropertyList* list, uint32_t id, float defaultValue);              // 0x004e1c70
Vector3* GetVector3(Vector3* out, PropertyList* list, uint32_t id, Vector3 def);          // 0x00b938d0
bool  GetBoolProperty(PropertyList* list, uint32_t id, bool* out);                        // 0x00407190
bool  GetPropertyAsUint32Array(PropertyList* list, uint32_t id, int* count, uint32_t** data);  // 0x006a0840

// SP::SimpleVector<unsigned> with a 5-element inline buffer
struct FixedVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    uint32_t  pad0, pad1;
    uint32_t  mnHeapFlag;
    uint32_t  mBuffer[5];
    __forceinline FixedVec()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCap = mBuffer + 5;
        mnHeapFlag = 0;
    }
    void resize(uint32_t n);   // 0x004cd3c0
    __forceinline ~FixedVec()
    {
        if (mpBegin && mpBegin[-1])
            delete[] mpBegin;
    }
};

struct Archetype {
    uint32_t pad00[4];
    uint32_t mnInstanceID;         // +0x10
    uint32_t mnKey;                // +0x14
    uint32_t pad18[(0x2d4 - 0x18) / 4];
    float    mfBoundsA[3];         // +0x2d4
    float    mfHeightLo;           // +0x2e0
    float    mfHeightHi;           // +0x2e4
    float    mfBoundsB[2];         // +0x2e8
    float    mfSpacing[2];         // +0x2f0
    uint32_t pad2f8[2];
    float    mfCountMin;           // +0x300
    float    mfCountMax;           // +0x304
    float    mfAdjust[3];          // +0x308
    uint32_t pad314[(0x334 - 0x314) / 4];
    uint8_t  mbFlag334;            // +0x334
    uint8_t  pad335[3];
    uint32_t pad338[(0x39c - 0x338) / 4];
    float*   mpPointsBegin;        // +0x39c
    float*   mpPointsEnd;          // +0x3a0
    uint32_t pad3a4[(0x3b0 - 0x3a4) / 4];
    uint32_t* mpSubBegin;          // +0x3b0
    uint32_t* mpSubEnd;            // +0x3b4
    uint32_t pad3b8[(0x43c - 0x3b8) / 4];
    PropertyList* mpProps;         // +0x43c
};

class cSPEditorSpeciesManager {
public:
    uint32_t  GetAvatarProfile();                                   // 0x004df420
    Archetype* GetSpeciesArchetype(uint32_t id, int level);         // 0x004e0050
    int       FUN_004dfff0(FixedVec* out, Archetype* a, int count, int unused, bool useAll);  // 0x004dfff0
};
cSPEditorSpeciesManager* GetSetting9();   // 0x00401090

class cPlanetModel {
public:
    float GetWaterHeight();   // 0x00b7e390
};
class cSpotGrid {
public:
    int mnAxis;
    void AdjustPosition(Vector3& pos, float a, float b, float c);   // 0x00b90ea0
};
extern cSpotGrid g_SpotGrid;   // 0x0156c060

void*         NounManager();            // 0x00b3d300
cPlanetModel* PlanetModel();            // 0x00b3d350
void*         GetCurrentGameMode();     // 0x00b5b800
void*         ObjectTemplateDB();       // 0x0067cb40

extern Vector3  g_DefaultChance;   // 0x0156bfc4
extern Vector3  g_DefaultCount;    // 0x01688890
extern uint32_t g_SpawnCounter;    // 0x016895a4

struct Key { uint32_t a, b; };
struct Entry { uint32_t k0, k1, v2, v3; };
struct IterPair { Entry* first; Entry* second; };
struct InsertResult { Entry* it; bool inserted; };
class cSpawnTable {
public:
    Entry*   mpBegin;       // 0x0168890c
    Entry*   mpEnd;         // 0x01688910
    uint32_t pad[3];
    bool     mbFlag;        // 0x01688920
    uint32_t Count(const Key* key);                           // 0x00b970c0
    IterPair* EqualRange(IterPair* out, const Key* key);      // 0x00b965d0
    InsertResult* Insert(InsertResult* out, const Entry* e);  // 0x00b98230
};
extern cSpawnTable g_SpawnTable;   // 0x0168890c
IterPair* FUN_00b96220(IterPair* out, Entry* begin, Entry* end, const Key* key, bool flag);   // 0x00b96220

bool FUN_00b97720(Vector3* outPos, const void* context, uint8_t flag,
                  float a0, float a1, float b0, float b1, float c, float waterLo, float waterHi,
                  float d0, float d1, float e, int flags, FixedVec* constraint, uint32_t count,
                  bool flag2);
void FUN_00b93f40(Vector3* pos, Archetype* a, uint32_t id, uint32_t seed, uint32_t extra);
int  PlaceSpawnDefinitionsOnPlanet(const void* context, uint32_t* ids, uint32_t count,
                                   uint32_t instanceOverride, uint32_t extra);   // 0x00b9b090

// @ 0x00B9AA10
void FUN_00b9aa10(const void* context, uint32_t* ids, uint32_t count, uint32_t extra)
{
    NounManager();
    cPlanetModel* planet = PlanetModel();
    cSPEditorSpeciesManager* mgr = GetSetting9();
    mgr->GetAvatarProfile();
    bool gameMode = GetCurrentGameMode() == (void*)0x1654c01;
    if (!ObjectTemplateDB())
        return;

    FixedVec constraint;
    constraint.resize(1);
    float waterHeight = planet->GetWaterHeight();

    for (uint32_t i = 0; i < count; i++) {
        uint32_t id = ids[i];
        Archetype* a = mgr->GetSpeciesArchetype(id, 0);
        if (!a)
            continue;
        if (mgr->FUN_004dfff0(&constraint, a, 1, 0, false) <= 0) {
            if (GetSetting9()->FUN_004dfff0(&constraint, a, 1, 0, true) <= 0)
                continue;
        }

        double lo = a->mfCountMin;
        double hi = a->mfCountMax;
        double v = g_Random.RandomDoubleUniform() * (hi - lo) + lo;
        if (v < hi) {
            if (v < lo)
                v = lo;
        } else
            v = hi;
        float fcount = (float)v;
        int num = RoundToInt(fcount);

        float chance = GetPropertyFloat(a->mpProps, 0x4934caca, 1.0f);
        Vector3 chanceVec;
        GetVector3(&chanceVec, a->mpProps, 0x1ee4cafd, g_DefaultChance);
        chance = (&chanceVec.x)[g_SpotGrid.mnAxis] * chance;
        float roll = (float)g_Random.RandomDoubleUniform();
        if (num <= 0 || !(roll <= chance))
            continue;

        uint32_t seed = ++g_SpawnCounter;
        Vector3 countVec;
        GetVector3(&countVec, a->mpProps, 0x6b152f47, g_DefaultCount);
        float modulusF = (&countVec.x)[g_SpotGrid.mnAxis];
        if ((int)modulusF > 0)
            seed = g_SpawnCounter % (uint32_t)(int)modulusF + 1;

        float heightLo = a->mfHeightLo + waterHeight;
        float heightHi = a->mfHeightHi + waterHeight;
        bool hasPoints = (uint32_t)(a->mpPointsEnd - a->mpPointsBegin) >= 2;
        bool b10 = true;
        bool b20 = gameMode;
        bool b40 = false;
        GetBoolProperty(a->mpProps, 0x80cd38c6, &b10);
        GetBoolProperty(a->mpProps, 0x3a509d24, &b20);
        GetBoolProperty(a->mpProps, 0x835025da, &b40);
        int flags = 0;
        if (b10) flags = 0x10;
        if (b20) flags |= 0x20;
        if (b40) flags |= 0x40;

        uint32_t idx = 0;
        int remaining = num;
        for (;;) {
            float a0, a1;
            if (hasPoints) {
                a0 = a->mpPointsBegin[idx];
                a1 = a->mpPointsBegin[idx + 1];
            } else {
                a0 = 100.0f;
                a1 = 1000.0f;
            }
            uint32_t next = (idx + 2) % (uint32_t)(a->mpPointsEnd - a->mpPointsBegin);
            Vector3 pos;
            if (FUN_00b97720(&pos, context, a->mbFlag334, a0, a1,
                             a->mfBoundsA[0], a->mfBoundsA[1], a->mfBoundsA[2],
                             heightLo, heightHi, a->mfBoundsB[0], a->mfBoundsB[1], 0.0f, flags,
                             &constraint, 0, false)) {
                if (!gameMode) {
                    uint32_t field = GetSetting9()->GetSpeciesArchetype(id, 0)->mnKey;
                    Key key;
                    key.a = seed;
                    key.b = field;
                    IterPair found;
                    FUN_00b96220(&found, g_SpawnTable.mpBegin, g_SpawnTable.mpEnd, &key,
                                 g_SpawnTable.mbFlag);
                    if (found.first == found.second || found.first == g_SpawnTable.mpEnd) {
                        Key key2;
                        key2.a = 0;
                        key2.b = field;
                        uint32_t n = g_SpawnTable.Count(&key2);
                        if (n) {
                            IterPair range;
                            g_SpawnTable.EqualRange(&range, &key2);
                            uint32_t r = g_Random.RandomUint32Uniform(n);
                            Entry e = range.first[r];
                            e.k0 = seed;
                            e.k1 = field;
                            InsertResult res;
                            g_SpawnTable.Insert(&res, &e);
                        }
                    }
                }
                float spacing = RandomFloatRange(a->mfSpacing[0], a->mfSpacing[1]);
                RoundToInt(spacing);
                FUN_00b93f40(&pos, a, id, seed, extra);
                g_SpotGrid.AdjustPosition(pos, a->mfAdjust[0], a->mfAdjust[1], a->mfAdjust[2]);
                int defCount = 0;
                uint32_t* defs = 0;
                if (GetPropertyAsUint32Array(a->mpProps, 0xdb9bfc2c, &defCount, &defs) &&
                    defCount > 0)
                    PlaceSpawnDefinitionsOnPlanet(&pos, defs, defCount, a->mnInstanceID, 0);
                uint32_t subCount = (uint32_t)(a->mpSubEnd - a->mpSubBegin);
                if (subCount)
                    FUN_00b9aa10(&pos, a->mpSubBegin, subCount, id);
            }
            if (--remaining == 0)
                break;
            idx = next;
        }
    }
}
