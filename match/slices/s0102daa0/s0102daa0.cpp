// s0102daa0.cpp -- gold6 batch, worker 25
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Complete reconstruction of FUN_0102daa0 (0x0102daa0, 1138 bytes): rebuild the
// global "requested planets" SPVector<unsigned> at 0x016decac..b4 from the
// star records returned by cStarManager::GetStarRecords around the player's
// nearest city.
//
// The original inlines the eastl rbtree (CivCounterMap) that keeps the closest
// civilization per avatar and the eastl vector<AutoRefCount<...>> used to
// collect the map values.  Those two containers are modelled below with
// explicit local arrays and the same find/insert/release behaviour; every
// gameplay callee is the real engine routine at the annotated address.

#include "types.h"
#include <math.h>

typedef unsigned int uint;

// 0x011e0744 -- the image's memcpy/memmove helper (jmp msvcr90!memcpy).
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n); // 0x011e0744

// 0x016decac: SPVector<unsigned> of requested-planet ids (begin/end/capacity).
struct SPVectorU {
    unsigned* begin;    // +0x00
    unsigned* end;      // +0x04
    unsigned* cap;      // +0x08
    void DoInsertValueI(unsigned* pos, const unsigned& v); // 0x004558a0
};
extern SPVectorU g_requestedPlanets; // 0x016decac

// A small eastl-vector-shaped container (begin / end / capacity).
struct PtrVec {
    void** begin;       // +0x00
    void** end;         // +0x04
    void** cap;         // +0x08
};

// The civilization/avatar object stored in the star-record vector.  Only the
// three fields this routine touches are named.
struct cGameNounManager {
    void*  GetAvatar();     // 0x00b1fdb0  returns [this+0x54] (avatar/civ id)
    float* GetCities();     // 0x005c65e0  returns this+0x3c (a cSPVector3)
    bool   Flag();          // 0x00bb9c00  ([this+0x5c] >> 5) & 1
};

// 0x00c30c60 returns [empire+0xb0] (or 0 when it is -1); the result is the
// object whose +0x5c flags are tested by 0x00bb9af0.
struct cEmpireFlags {
    bool Test(uint mask);   // 0x00bb9af0  ([this+0x5c] & mask) != 0
};

struct cEmpire {
    cEmpireFlags* GetFlags(); // 0x00c30c60
};

struct cStarManager {
    void  GetStarRecords(const float* cities, void* criteria, PtrVec* out); // 0x00bb1080
    void* GetEmpireByID(uint id); // 0x00ba9370
};

// 0x00bba790 returns the vector of star records owned by an object.
struct cRecordOwner {
    PtrVec* GetRecords();   // 0x00bba790
};

// A star-record reference (cStarRecordRef); the two getters read +0x194 and
// +0x184 respectively.
struct cStarRecordRef {
    uint GetKind();         // 0x00b8dab0
    uint GetCommContext();  // 0x00ce6950
};

struct cUFOSimulator {
    float GetMaxTravelDistance(); // 0x00ffbfc0  returns [this+0x48]
};

extern "C" cStarManager* __cdecl StarManager();        // 0x00b3d2a0
extern "C" void*        __cdecl GetUFOSimulator();     // 0x00ffbe50
extern "C" uint         __cdecl GetPlayerEmpireID();   // 0x01021090
extern "C" void __cdecl FUN_01000660(void** begin, void** end,
                                     float x, float y, float z); // 0x01000660
extern "C" void __cdecl FUN_00f47380(void* p);         // 0x00f47380 operator delete

// tStarSearchCriteria as built at esp+0x64 in the original frame.
struct tStarSearchCriteria {
    uint  mFlags;       // +0x00 = 0x1fff
    uint  mMode;        // +0x04 = 0x20
    uint  mPad08;       // +0x08 = 0
    float mZero;        // +0x0c = 0.0f
    float mMaxDistance; // +0x10 = cSPSimulatorPlayerUFO::GetMaxTravelDistance()
    float mMinusOne;    // +0x14 = -1.0f
    uint  mPad18;       // +0x18 = 0
};

// CivCounterMap entry: key = avatar/civ id, value = closest civ seen so far.
struct CivEntry {
    void* key;
    void* val;
};

static float Dist3(const float* a, const float* b)
{
    float dx = a[0] - b[0];
    float dy = a[1] - b[1];
    float dz = a[2] - b[2];
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

static void AddRef(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[0])(p);
    }
}

static void Release(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[1])(p);
    }
}

// @ 0x0102daa0
void FUN_0102daa0(cGameNounManager* param_1)
{
    // ---- Phase 0: erase(begin, end) of the global requested-planets vector.
    FUN_011e0744(g_requestedPlanets.begin, g_requestedPlanets.end, 0);
    g_requestedPlanets.end = g_requestedPlanets.begin;

    // ---- Phase 1: gather the star records around the player's position.
    void* playerAvatar = param_1->GetAvatar();

    tStarSearchCriteria criteria;
    criteria.mFlags = 0x1fff;
    criteria.mMode = 0x20;
    criteria.mPad08 = 0;
    criteria.mZero = 0.0f;
    criteria.mMaxDistance = 0.0f;
    criteria.mMinusOne = -1.0f;
    criteria.mPad18 = 0;

    PtrVec star;
    star.begin = 0;
    star.end = 0;
    star.cap = 0;

    float* cities = param_1->GetCities();
    float maxDistance = ((cUFOSimulator*)GetUFOSimulator())->GetMaxTravelDistance();
    criteria.mMaxDistance = maxDistance;

    cStarManager* starMgr = StarManager();
    starMgr->GetStarRecords(cities, &criteria, &star);

    // ---- Phase 2: pick the closest civilization per avatar.
    CivEntry civMap[512];
    int civMapCount = 0;
    int starCount = (int)(star.end - star.begin);

    for (int i = 0; i < starCount; ++i) {
        cGameNounManager* civ = (cGameNounManager*)star.begin[i];
        void* avatar = civ->GetAvatar();

        cEmpire* empire = (cEmpire*)starMgr->GetEmpireByID((uint)avatar);
        cEmpireFlags* flags = empire->GetFlags();
        bool masked = flags->Test(2);

        if (avatar == playerAvatar)
            continue;
        if (avatar == (void*)GetPlayerEmpireID())
            continue;
        if (!civ->Flag())
            continue;
        if (masked)
            continue;

        int found = -1;
        for (int k = 0; k < civMapCount; ++k) {
            if (civMap[k].key == avatar) {
                found = k;
                break;
            }
        }

        if (found < 0) {
            // CivCounterMap::GetCounter(avatar) on a missing key inserts it.
            void* key = civ->GetAvatar();
            civMap[civMapCount].key = key;
            civMap[civMapCount].val = civ;
            ++civMapCount;
        } else {
            // Keep the civ whose city is closest to the player's city.
            void* prev = civMap[found].val;
            float* base1 = param_1->GetCities();
            float* curPos = civ->GetCities();
            float dCur = Dist3(base1, curPos);
            float* base2 = param_1->GetCities();
            float* prevPos = ((cGameNounManager*)prev)->GetCities();
            float dPrev = Dist3(base2, prevPos);
            if (dPrev > dCur)
                civMap[found].val = civ;
        }
    }

    // The original walks the rbtree in ascending-key order.
    for (int a = 1; a < civMapCount; ++a) {
        CivEntry e = civMap[a];
        int b = a - 1;
        while (b >= 0 && (uint)civMap[b].key > (uint)e.key) {
            civMap[b + 1] = civMap[b];
            --b;
        }
        civMap[b + 1] = e;
    }

    // ---- Phase 3: collect the map values, sort them by proximity, and scan
    // them for the first kind-5 record of each entry.
    void* collected[512];
    int collectedCount = 0;

    if (civMapCount > 0) {
        for (int k = 0; k < civMapCount; ++k) {
            void* value = civMap[k].val;
            AddRef(value);
            collected[collectedCount++] = value;
        }

        float* base = param_1->GetCities();
        FUN_01000660((void**)collected, (void**)collected + collectedCount,
                     base[0], base[1], base[2]);

        for (int i = 0; i < collectedCount; ++i) {
            cRecordOwner* owner = (cRecordOwner*)collected[i];
            PtrVec* records = owner->GetRecords();
            int recordCount = (int)(records->end - records->begin);

            for (int j = 0; j < recordCount; ++j) {
                cStarRecordRef* rec = (cStarRecordRef*)records->begin[j];
                if (rec->GetKind() == 5) {
                    uint context = rec->GetCommContext();
                    if (g_requestedPlanets.end < g_requestedPlanets.cap) {
                        *g_requestedPlanets.end = context;
                        ++g_requestedPlanets.end;
                    } else {
                        g_requestedPlanets.DoInsertValueI(g_requestedPlanets.end,
                                                          context);
                    }
                    break;      // only the first matching record per entry
                }
            }
        }

        // Release the references taken into the collection vector.
        for (int i = 0; i < collectedCount; ++i)
            Release(collected[i]);
    }

    // ---- Phase 4: release the star-record vector and its backing store.
    for (void** p = star.begin; p < star.end; ++p)
        Release(*p);
    if (star.begin)
        FUN_00f47380(star.begin);
}
