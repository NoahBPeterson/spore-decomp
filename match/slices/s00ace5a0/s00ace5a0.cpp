// 0x00ace5a0: per-tick update of a noun streaming / visibility manager (class name is a guess).
// Throttled by an accumulated timer (dt in ms * 0.001), then three passes over cGameNounManager data vectors:
//  1. objects of type 0x36be27e: bind/unbind the spawned noun (mpNoun) against the manager's position test
//  2. objects of type 0x18eb45e (skipped in game modes 1 and 2): call vtable slot 50 (activate) when not tracked
//  3. objects of type 0x1be418e: LOD switch by distance against this->mSpheres (5-float entries) and a global point
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (the unsigned->float conversion of dt stays x87).

#include "types.h"

struct Vec3 { float x, y, z; };
struct Quat4 { float x, y, z, w; };
struct Sphere { float x, y, z, r2a, r2b; };   // 0x14 bytes

#define PV(n) virtual void s##n();

struct Ref {   // refcounted noun handle
    PV(0)
    virtual void Release();          // slot 1
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsDead();           // slot 11 (0x2c)
};

struct Placement {   // returned by FUN_00ad7360; slot 11 = position, slot 12 = rotation
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();
    virtual const Quat4* GetRotation();
};

struct SubLock {     // embedded at +0xC0 of the type-2 objects
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();   // 0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool IsLocked();             // 0x58
};

struct SubHidden {   // embedded at +0x34 of the LOD object's helper
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual bool IsHidden();             // 0x48
};

struct LodHelper {
    char pad[0x34];
    SubHidden mSub;
    char pad2[0x120 - 0x38];
    uint8_t mbFlag;
};

struct NounObj1 {      // type 0x36be27e
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsRemoved();                // 0x2c
    char pad04[0x84 - 4]; uint32_t mFlags;
    char pad88[0xa9 - 0x88]; uint8_t mbSpawned;
    char padaa[0x10c - 0xaa]; uint32_t mTypeID; uint32_t mField110;
    char pad114[0x1a4 - 0x114]; Ref* mpNoun; Vec3 mPos; Quat4 mRot; uint8_t mbDone;
};

struct NounObj2 {      // type 0x18eb45e
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsRemoved();                // 0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual int GetOwnerID();                // 0x4c
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    virtual void Activate(bool b);           // 0xc8
    bool Func_c0c0e0();   // 0x00c0c0e0
    char pad04[0x24 - 4]; uint32_t mKey;
    char pad28[0xc0 - 0x28]; SubLock mSub;
    char padc4[0x135 - 0xc4]; uint8_t mbFlag135;
    char pad136[0xb67 - 0x136]; uint8_t mbFlagB67;
};

struct NounObj3 {      // type 0x1be418e
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsRemoved();                // 0x2c
    char pad04[0x84 - 4]; uint8_t mbFlag84;
    char pad85[0x120 - 0x85]; int mRangeMin; int mRangeMax; uint8_t mbNear;
    char pad129[0x160 - 0x129]; LodHelper* mpHelper;
    bool Func_c6a020();
    void Func_c6ace0(bool b);
    const Vec3* Func_c6acc0();
    bool Func_c6a030();
    void Func_c6b540();
};

struct Tribe {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual int GetID();   // 0x4c
};

template<class T> struct PtrVec { T** mpBegin; T** mpEnd; T** begin() const { return mpBegin; } T** end() const { return mpEnd; } };
template<class T> struct VecOut { char pad[4]; PtrVec<T> mVec; };

class NounVisibility;
struct NounManager {
    Tribe* GetPlayerTribe();                                       // 0x00bfc5f0
    void* GetGameDataVector(void (*)(), void (*)(), void (*)(), void (*)(), uint32_t);   // 0x00b21340
    void RemoveNoun(Ref* pNoun);                                   // 0x00b225d0
};

struct HIter { void* mpNode; void** mpBucket; HIter() {} HIter(const HIter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {} };
struct HTable {
    char pad[4]; void** mpBucketArray; uint32_t mnBucketCount;
    void* End() const { return mpBucketArray[mnBucketCount]; }
    HIter find(const uint32_t& key);                               // 0x00645ed0
};

struct ModeInfo { char pad[0x2c]; int mMode; };

NounManager* GetNounManager();            // 0x00b3d300
uint32_t GetCurrentGameMode();            // 0x00b5b800
ModeInfo* GetModeInfo();                  // 0x00b3d4d0
Placement* FindPlacement(Ref** ppNoun);   // 0x00ad7360 (cdecl)
void ActivateObj(NounObj1* p, int a, int b);   // 0x00b931c0 (cdecl)

void F_cd7d10(); void F_d3d420(); void F_b1e500(); void F_ace070(); void F_ace0f0(); void F_accc30();

extern float gTimer;       // 0x0167a490
extern float gThreshold;   // 0x01565ce0
extern int gStat0, gStat1, gStat2;   // 0x0167a37c, 0x0167a380, 0x0167a384
extern int gCurrentID;     // 0x0169e370
extern int gMaxPerTick;    // 0x01565d04
extern Vec3 gPoint;        // 0x0167ea30

class NounVisibility {
public:
    char pad00[0x20];
    Sphere* mpSpheresBegin;      // 0x20
    Sphere* mpSpheresEnd;        // 0x24
    char pad28[0xe0 - 0x28];
    HTable mTable;               // 0xe0
    bool Func_ac8d80(const Vec3* p);   // 0x00ac8d80
    bool Func_ac8df0(const Vec3* p);   // 0x00ac8df0
    void Update(int unused, uint32_t dt);
};

static inline void ReleaseNoun(Ref*& r)
{
    Ref* p = r;
    if (p) { r = 0; p->Release(); }
}

// @ 0x00ace5a0
void NounVisibility::Update(int unused, uint32_t dt)
{
    if (dt > 0) {
        gTimer += (float)dt * 0.001f;
        if (gTimer < gThreshold)
            return;
        gTimer = 0.0f;
    }
    NounManager* pMgr = GetNounManager();
    gStat2 = 0;
    gStat1 = 0;
    gStat0 = 0;
    bool bModeA = GetCurrentGameMode() == 0x1654c01;
    bool bModeB = GetCurrentGameMode() == 0x1654c01;
    int playerID;
    if (pMgr->GetPlayerTribe())
        playerID = pMgr->GetPlayerTribe()->GetID();
    else
        playerID = -1;

    // pass 1
    {
        VecOut<NounObj1>* pVec = (VecOut<NounObj1>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_ace070, F_b1e500, 0x36be27e);
        const PtrVec<NounObj1>& vec = pVec->mVec;
        NounObj1** it = vec.begin();
        NounObj1** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj1* p = *it;
            if (p->IsRemoved() || p->mTypeID == 0 || p->mField110 == 0 || p->mbDone != 0)
                continue;
            Ref** ppNoun = &p->mpNoun;
            if (*ppNoun && (*ppNoun)->IsDead()) {
                p->mbDone = 1;
                ReleaseNoun(*ppNoun);
                continue;
            }
            if (p->mTypeID == 0x1be418e) {
                if (*ppNoun == 0)
                    ActivateObj(p, -1, -1);
                continue;
            }
            if (p->mFlags & 0x100)
                continue;
            if (p->mbSpawned != 0) {
                Placement* pPlace = FindPlacement(ppNoun);
                const Vec3* pPos;
                if (pPlace)
                    pPos = pPlace->GetPosition();
                else
                    pPos = &p->mPos;
                if (Func_ac8d80(pPos)) {
                    if (*ppNoun) {
                        if (pPlace) {
                            const Vec3* v = pPlace->GetPosition();
                            p->mPos = *v;
                            const Quat4* q = pPlace->GetRotation();
                            p->mRot = *q;
                        }
                        pMgr->RemoveNoun(*ppNoun);
                        ReleaseNoun(*ppNoun);
                    }
                    p->mbSpawned = 0;
                } else if (*ppNoun == 0) {
                    if (Func_ac8df0(&p->mPos))
                        ActivateObj(p, -1, -1);
                }
            } else {
                if (Func_ac8df0(&p->mPos)) {
                    p->mbSpawned = 1;
                    if (*ppNoun == 0)
                        ActivateObj(p, -1, -1);
                }
            }
        }
    }

    // pass 2
    ModeInfo* pMode = GetModeInfo();
    int mode = pMode->mMode;
    if (mode != 1 && mode != 2) {
        VecOut<NounObj2>* pVec = (VecOut<NounObj2>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_ace0f0, F_b1e500, 0x18eb45e);
        const PtrVec<NounObj2>& vec = pVec->mVec;
        NounObj2** it = vec.begin();
        NounObj2** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj2* p = *it;
            if (p->IsRemoved() || p->mbFlag135 == 0 || p->mbFlagB67 == 0)
                continue;
            if (!(bModeB == 1 || !p->Func_c0c0e0()))
                continue;
            HTable& tbl = mTable;
            uint32_t key = p->mKey;
            void* pEnd = tbl.End();
            if (tbl.find(key).mpNode != pEnd)
                continue;
            if (p->mSub.IsLocked())
                continue;
            int id = p->GetOwnerID();
            if (id != -1 && id == playerID)
                continue;
            if (Func_ac8d80(p->mSub.GetPosition()))
                p->Activate(true);
        }
    }

    // pass 3
    {
        int nCount = 0;
        VecOut<NounObj3>* pVec = (VecOut<NounObj3>*)pMgr->GetGameDataVector(F_cd7d10, F_d3d420, F_accc30, F_b1e500, 0x1be418e);
        const PtrVec<NounObj3>& vec = pVec->mVec;
        NounObj3** it = vec.begin();
        NounObj3** itEnd = vec.end();
        for (; it != itEnd; ++it) {
            NounObj3* p = *it;
            if (p->IsRemoved())
                continue;
            if (p->mbFlag84 == 0 && bModeA && gCurrentID >= 0 && (gCurrentID < p->mRangeMin || gCurrentID > p->mRangeMax)) {
                p->Func_c6ace0(false);
                if (p->mpHelper)
                    p->mpHelper->mbFlag = 1;
                continue;
            }
            bool bActivate = false;
            if (p->Func_c6a020()) {
                bool bInside = false;
                if (p->mbFlag84 == 0) {
                    const Vec3* pPos = p->Func_c6acc0();
                    for (Sphere* s = mpSpheresBegin; s != mpSpheresEnd; ++s) {
                        float dx = pPos->x - s->x, dy = pPos->y - s->y, dz = pPos->z - s->z;
                        if (s->r2b > dz * dz + dy * dy + dx * dx) { bInside = true; break; }
                    }
                } else {
                    bInside = true;
                }
                if (!bInside) {
                    p->Func_c6ace0(false);
                } else {
                    const Vec3* pPos = p->Func_c6acc0();
                    float dx = pPos->x - gPoint.x, dy = pPos->y - gPoint.y, dz = pPos->z - gPoint.z;
                    bool bNear = 400.0f > dz * dz + dy * dy + dx * dx;
                    if (p->mpHelper)
                        bNear = p->mpHelper->mSub.IsHidden();
                    p->mbNear = !bNear;
                }
            } else {
                if (p->mbFlag84 != 0) {
                    bActivate = true;
                } else if (nCount < gMaxPerTick) {
                    const Vec3* pPos = p->Func_c6acc0();
                    for (Sphere* s = mpSpheresBegin; s != mpSpheresEnd; ++s) {
                        float dx = pPos->x - s->x, dy = pPos->y - s->y, dz = pPos->z - s->z;
                        if (s->r2a >= dz * dz + dy * dy + dx * dx) {
                            if (p->Func_c6a030())
                                bActivate = true;
                            break;
                        }
                    }
                }
                if (bActivate) {
                    p->Func_c6ace0(true);
                    if (p->mpHelper)
                        p->mpHelper->mbFlag = 1;
                    p->Func_c6b540();
                    ++nCount;
                }
            }
        }
    }
}
