// Slice s00da2360 -- band performance layout (0x00da2360, code 0xda2360..0xda2fa8 + jump table;
// the function index runs on to 0xda2fd0 because the next function has no index entry).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc: the local fixed_vectors get no EH frame)
//
// Retail name anchor: SP::SOCIAL_BAND_PLAY_Tick (SPCreatureBehaviorTrees.obj). The retail
// function is a cdecl helper taking only the cSocialBand*, so the dev-build signature
// (behavior-tree tick) does not apply; it is the part of the tick that lays the band out.
//
// Sorts the band's members into four instrument sections by the citizen's band role
// (5, 6, 4, anything else; role 11 walks to a free action-circle slot in front of the stage),
// averages each section's position, orders the sections by distance from the band's centre and
// gives each one the free band-section position (1..4) that best matches its direction from the
// centre. Every member of an assigned section then takes the free action-circle slot that best
// matches its direction from the section centre and is sent there facing the stage.
#include <math.h>
#include <stdlib.h>
#include "types.h"

void operator delete[](void* p);   // 0x00f47380

namespace SP {

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    float LengthSquared() const { return x * x + y * y + z * z; }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(inv * x, y * inv, z * inv);
    }
    cSPVector3& operator+=(const cSPVector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    cSPVector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    bool operator==(const cSPVector3& v) const { return x == v.x && y == v.y && z == v.z; }
};
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
inline float Dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

extern const cSPVector3 kZeroVector;   // 0x0169f32c

// fixed_vector<T, N, true> with the sp allocator: the word before the inline buffer is 0, a heap
// block has a non-zero header there.
template<class T, int N> struct FixedVector {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];
    int      mBufferHeader;
    T        mBuffer[N];

    __forceinline FixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mBufferHeader(0) {}
    __forceinline ~FixedVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }

    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    __forceinline bool empty() const { return mpBegin == mpEnd; }
    void DoInsertValue(T* pos, const T& value);   // 0x00b96600
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

class cPlanetModel {
public:
    cSPVector3 DirectionToSurfacePosition(const cSPVector3& dir) const;   // 0x00b815a0
};
cPlanetModel* PlanetModel();   // 0x00b3d350

class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const cSPVector3& GetPosition();   // +0x2c
};

class cGameData {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t GetNounID();   // +0x20
};

class cSPCreatureBase : public cGameData {
public:
    uint32_t pad04[0x2f];
    cSpatialObject mSpatial;        // +0xc0
    uint32_t padc4[0x3a1];
    int mBandRole;                  // +0x102c

    enum eSpeedState { kSpeedRun = 2 };
    void MoveToPointAndFacingAtSpeed(eSpeedState speed, const cSPVector3& point,
                                     const cSPVector3& facing, float f1, float f2);   // 0x00c1c5c0
    const cSPVector3& GetPosition() { return mSpatial.GetPosition(); }
};

class cSPCreatureCitizen : public cSPCreatureBase {
public:
    static const uint32_t NOUN_ID = 0x018eb4b7;
    int GetBandRole();   // 0x00c22dc0 (returns mBandRole, out of line)
};
static const uint32_t kAnimalNounID = 0x018eb45e;

inline cSPCreatureCitizen* CitizenCast(cSPCreatureBase* p)
{
    if (p && p->GetNounID() == cSPCreatureCitizen::NOUN_ID)
        return (cSPCreatureCitizen*)p;
    return 0;
}

class cCommunity {
public:
    cSPCreatureBase* GetLeader() const;   // 0x00c00650
};

struct cBandSkill {
    float GetSkill(int level);   // 0x00ce6a40
};
extern cBandSkill gBandSkill;    // 0x01581208

struct tSlot {                   // cActionCircle::tSlot (0x18 bytes)
    bool mbOccupied;             // +0x0
    uint32_t pad04[2];
    cSPVector3 mPosition;        // +0xc
    void Occupy(cSPCreatureBase* pCreature);   // 0x00afa030
};

class cActionCircle {
public:
    uint32_t pad00[0x14];
    tSlot* mSlotsBegin;          // +0x50 (mSlots)
    tSlot* mSlotsEnd;            // +0x54
    int FindNearestFreeSlot(const cSPVector3& point);   // 0x00afa5d0
    tSlot* GetSlot(int index);                          // 0x00af9ff0
};

struct cSocialBand {
    uint32_t pad00[2];
    cCommunity* mpCommunity;     // +0x8
    uint32_t pad0c;
    cSPVector3 mStageArea;       // +0x10
    cSPVector3 mStageFacing;     // +0x1c
    uint32_t pad28[0xf];
    cSPCreatureBase** mMembersBegin;   // +0x64
    cSPCreatureBase** mMembersEnd;     // +0x68
    uint32_t pad6c[0x22];
    cSPVector3* mBandSectionPositions; // +0xf4 (mpBegin of the 6 section positions)
    uint32_t padf8[0x20];
    cActionCircle mActionCircle;       // +0x178
};

typedef FixedVector<cGameData*, 4> MemberVector;

struct BandSection {
    cSPVector3 mCenter;          // +0x00
    float mDistSq;               // +0x0c
    MemberVector mMembers;       // +0x10

    BandSection() : mCenter(kZeroVector) {}
    __forceinline void Add(cSPCreatureBase* pCreature)
    {
        mMembers.push_back(pCreature);
        mCenter += pCreature->GetPosition();
    }
};

// 0x00da1060: orders a section's members around its centre (cdecl, centre by value)
void SortSectionMembers(cGameData** first, cGameData** last, cSPVector3 center);
// 0x00d9b4e0: qsort comparator on BandSection::mDistSq
int __cdecl CompareSectionDistance(const void* a, const void* b);

static const int kNumSectionPositions = 6;

// @ 0x00da2360
void SOCIAL_BAND_PLAY_Tick(cSocialBand* pBand)
{
    cPlanetModel* pPlanet = PlanetModel();
    float skill = gBandSkill.GetSkill(*(int*)((char*)pBand->mpCommunity->GetLeader() + 0xb20)) + 1.0f;

    BandSection* sorted[4];
    BandSection* assigned[kNumSectionPositions] = { 0 };
    BandSection sections[5];

    cSPVector3 center(kZeroVector);
    for (cSPCreatureBase **it = pBand->mMembersBegin, **end = pBand->mMembersEnd; it != end; ++it) {
        cSPCreatureBase* pCreature = *it;
        cSPCreatureCitizen* pCitizen = CitizenCast(pCreature);
        center += pCreature->GetPosition();
        if (pCitizen) {
            switch (pCitizen->GetBandRole()) {
            case 11: {
                float dist = skill * 2.0f + 3.0f;
                cSPVector3 point = pBand->mStageArea - pBand->mStageFacing * dist;
                int index = pBand->mActionCircle.FindNearestFreeSlot(point);
                if (index != -1) {
                    tSlot* pSlot = pBand->mActionCircle.GetSlot(index);
                    pSlot->Occupy(pCitizen);
                    pCitizen->MoveToPointAndFacingAtSpeed(cSPCreatureBase::kSpeedRun, pSlot->mPosition,
                                                          pBand->mStageFacing, 1.0f, 2.0f);
                }
                break;
            }
            case 5:
                sections[0].Add(pCitizen);
                break;
            case 6:
                sections[1].Add(pCitizen);
                break;
            case 4:
                sections[2].Add(pCitizen);
                break;
            default:
                sections[3].Add(pCitizen);
                break;
            }
        } else if (pCreature->GetNounID() == kAnimalNounID) {
            sections[3].Add(pCreature);
        }
    }

    float invCount = 1.0f / (float)(uint32_t)(pBand->mMembersEnd - pBand->mMembersBegin);
    center.x *= invCount;
    center.y *= invCount;
    center.z = invCount * center.z;

    for (int i = 0; i < 5; ++i) {
        BandSection& section = sections[i];
        section.mDistSq = 3.402823466e+38f;
        uint32_t n = section.mMembers.size();
        if (n > 0) {
            section.mCenter *= 1.0f / (float)n;
            SortSectionMembers(section.mMembers.mpBegin, section.mMembers.mpEnd, section.mCenter);
            section.mDistSq = (section.mCenter - center).LengthSquared();
        }
    }

    sorted[0] = &sections[0];
    sorted[1] = &sections[1];
    sorted[2] = &sections[2];
    sorted[3] = &sections[3];
    qsort(sorted, 4, sizeof(BandSection*), CompareSectionDistance);

    for (uint32_t i = 0; i < 4; ++i) {
        BandSection* pSection = sorted[i];
        cSPVector3 dir = (pSection->mCenter - center).Normalized();
        int best = 0;
        float bestScore = 0.0f;
        for (int j = 1; j < kNumSectionPositions; ++j) {
            if (assigned[j] == 0 && j != 5) {
                cSPVector3 toPos = pBand->mBandSectionPositions[j] - center;
                float inv = 1.0f / (sqrtf(toPos.LengthSquared()) + 1.5258789e-05f);
                float score = (Dot(toPos * inv, dir) + 1.0f) * inv;
                if (score > bestScore) {
                    best = j;
                    bestScore = score;
                }
            }
        }
        assigned[best] = pSection;
    }

    for (int i = 1; i < kNumSectionPositions; ++i) {
        BandSection* pSection = assigned[i];
        if (pSection && !pSection->mMembers.empty()) {
            cSPVector3 surfacePos = pPlanet->DirectionToSurfacePosition(pBand->mBandSectionPositions[i]);
            uint32_t count = pSection->mMembers.size();
            for (uint32_t j = 0; j < count; ++j) {
                cSPCreatureBase* pMember = static_cast<cSPCreatureBase*>(pSection->mMembers.mpBegin[j]);
                const cSPVector3& pos = pMember->GetPosition();
                cSPVector3 dir = (pos - pSection->mCenter).Normalized();
                if (dir == kZeroVector)
                    dir = (pos - surfacePos).Normalized();

                tSlot* pSlots = pBand->mActionCircle.mSlotsBegin;
                int numSlots = pBand->mActionCircle.mSlotsEnd - pSlots;
                int bestSlot = -1;
                float bestScore = 0.0f;
                for (uint32_t k = 0; k < (uint32_t)numSlots; ++k) {
                    if (!pSlots[k].mbOccupied) {
                        cSPVector3 toSlot = pSlots[k].mPosition - surfacePos;
                        float inv = 1.0f / sqrtf(toSlot.LengthSquared());
                        float score = (Dot(toSlot * inv, dir) + 1.0f) * inv;
                        if (score > bestScore) {
                            bestSlot = k;
                            bestScore = score;
                        }
                    }
                }
                if (bestSlot != -1) {
                    tSlot* pSlot = &pSlots[bestSlot];
                    pSlot->Occupy(pMember);
                    pMember->MoveToPointAndFacingAtSpeed(cSPCreatureBase::kSpeedRun, pSlot->mPosition,
                                                         pBand->mStageFacing, 1.0f, 2.0f);
                }
            }
        }
    }
}

}  // namespace SP
