// Slice s00bb4f30: SP::cStarManager::TestIfAllStarsAreReachable (0x00BB4F30, name from the 2008 dev
// PDB; layout from the ModAPI cStarManager: mStarRecordGrid at +0xc8, elements are 0x14-byte vectors).
//
// Signature (from ret 0xc and the stack uses): void (uint startArg, float maxJump, bool flag).
// What it does: if maxJump <= 0 it takes the UFO simulator's max travel distance.  Then, repeatedly:
//   1. clears the "visited" flag (0x40000000, record flags at +0x5c) on every record of the grid;
//   2. flood-fills (a list used as a queue) from the record found by FindStar(startArg, criteria)
//      across neighbours within maxJump (GetStarRecords with a search criteria record);
//   3. for every grid record that was not reached, collects its neighbours within 3*maxJump, splits
//      them by flag, and measures the distance the jump limit would have to grow by (nearest
//      visited-side record, else nearest neighbour, else the 3x limit);  the flag is cleared again;
//   4. if everything was reached it stops, otherwise maxJump = max(maxJump, farthest gap) + epsilon
//      (and it also stops after a single pass when `flag` is false).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0
void operator delete[](void* p);                                         // 0x00f47380

struct Vector3 { float x, y, z; };

struct RefObj {
    virtual int AddRef();       // 0x00
    virtual int Release();      // 0x04
};

struct cStarRecord : RefObj {
    uint8_t  pad04[0x38];
    Vector3  mPosition;         // +0x3c
    uint8_t  pad48[0x14];
    uint32_t mFlags;            // +0x5c

    const Vector3& GetPosition();                          // 0x005c65e0
    uint32_t GetFlags();                                   // 0x00c87040
    void SetFlag(uint32_t mask, bool on);                  // 0x00bb9b00 (ret 8)
};

template <class T> struct AutoRefCount {
    T* mpObject;
    __forceinline AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    __forceinline AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    __forceinline ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

struct sp_vector_allocator { uint32_t mData[2]; };
__forceinline void SpFree(void* p)
{
    if (((uint32_t*)p)[-1] != 0)
        operator delete[](p);
}

typedef AutoRefCount<cStarRecord> StarRef;

struct StarVector {
    StarRef* mpBegin;
    StarRef* mpEnd;
    StarRef* mpCapacity;
    sp_vector_allocator mAllocator;

    __forceinline StarVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~StarVector()
    {
        for (StarRef* p = mpBegin; p < mpEnd; ++p)
            p->~StarRef();
        if (mpBegin)
            SpFree(mpBegin);
    }
    void DoInsertValue(StarRef* position, const StarRef& value);       // 0x00aea5d0 (ret 8)
    __forceinline void insert(StarRef* position, const StarRef& value)
    {
        DoInsertValue(position, value);
    }
    __forceinline void push_back(const StarRef& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) StarRef(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

StarRef* DoCopy(StarRef* first, StarRef* last, StarRef* dest);      // 0x006782c0 (cdecl)

struct StarRecordRow {          // eastl::vector<AutoRefCount<cStarRecord>, sp allocator>, 0x14 bytes
    StarRef* mpBegin;
    StarRef* mpEnd;
    StarRef* mpCapacity;
    sp_vector_allocator mAllocator;
};

// SP::cStarManager::tStarSearchCriteria (retail: 0x1c bytes)
struct StarSearchCriteria {
    uint32_t acceptableStarTypes;   // 0x1fff
    uint32_t acceptableSolarTech;   // 0x3f
    uint32_t miscFilters;
    float    f0c;
    float    maxRadius;             // +0x10
    float    f14;
    uint32_t f18;
};

struct ListNode {
    ListNode*    mpNext;
    ListNode*    mpPrev;
    cStarRecord* mValue;
};

// eastl::list<cStarRecord*> with the default eastl allocator (EASTL/allocator.h:0xd1)
struct StarList {
    ListNode mAnchor;
    __forceinline StarList() { mAnchor.mpNext = &mAnchor; mAnchor.mpPrev = &mAnchor; }
    __forceinline ~StarList()
    {
        ListNode* n = mAnchor.mpNext;
        while (n != &mAnchor) {
            ListNode* next = n->mpNext;
            operator delete[](n);
            n = next;
        }
    }
    __forceinline void push_back(cStarRecord* v)
    {
        ListNode* n = (ListNode*)operator new(sizeof(ListNode), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        if (&n->mValue)
            n->mValue = v;
        n->mpNext = &mAnchor;
        n->mpPrev = mAnchor.mpPrev;
        mAnchor.mpPrev->mpNext = n;
        mAnchor.mpPrev = n;
    }
    __forceinline cStarRecord* pop_front()
    {
        ListNode* n = mAnchor.mpNext;
        cStarRecord* v = n->mValue;
        n->mpPrev->mpNext = n->mpNext;
        n->mpNext->mpPrev = n->mpPrev;
        operator delete[](n);
        return v;
    }
};

struct cUFOSimulator {
    float GetMaxTravelDistance();      // 0x00ffbfc0
};
cUFOSimulator* GetUFOSimulator();                                    // 0x00ffbe50 (cdecl)
float Distance2D(const Vector3* a, const Vector3* b);                // 0x010434e0 (cdecl)

extern float g_Three;       // 0x01465ea8
extern float g_NegOne;      // 0x013eb1bc
extern float g_FltMax;      // 0x01465eb8
extern float g_Epsilon;     // 0x01485720

class cStarManager {
public:
    uint8_t pad00[0xc8];
    StarRecordRow* mpGridBegin;                 // +0xc8
    StarRecordRow* mpGridEnd;                   // +0xcc

    cStarRecord* FindStar(uint32_t arg, const StarSearchCriteria* c);                   // 0x00bb0e90 (ret 8)
    void GetStarRecords(const Vector3& pos, const StarSearchCriteria& c, StarVector& out);   // 0x00bb1080 (ret 0xc)
    cStarRecord* FindNearest(const Vector3& pos, const StarVector& v);                  // 0x00ba71b0 (ret 8)

    void TestIfAllStarsAreReachable(uint32_t startArg, float maxJump, bool flag);       // 0x00bb4f30
};

// @ 0x00bb4f30
void cStarManager::TestIfAllStarsAreReachable(uint32_t startArg, float maxJump, bool flag)
{
    bool done = false;
    if (maxJump <= 0.0f) {
        maxJump = GetUFOSimulator()->GetMaxTravelDistance();
        if (maxJump <= 0.0f)
            return;
    }
    do {
        const float limit = maxJump * g_Three;

        for (StarRecordRow* row = mpGridBegin; row != mpGridEnd; ++row)
            for (StarRef* it = row->mpBegin; it != row->mpEnd; ++it)
                it->mpObject->SetFlag(0x40000000, false);

        StarSearchCriteria crit;
        crit.acceptableStarTypes = 0x1fff;
        crit.acceptableSolarTech = 0x3f;
        crit.miscFilters = 0;
        crit.f0c = g_NegOne;
        crit.maxRadius = g_NegOne;
        crit.f14 = g_NegOne;
        crit.f18 = 0;
        cStarRecord* start = FindStar(startArg, &crit);

        StarList queue;
        queue.push_back(start);
        start->SetFlag(0x40000000, true);
        while (queue.mAnchor.mpNext != &queue.mAnchor) {
            cStarRecord* cur = queue.pop_front();
            StarVector neighbors;
            crit.maxRadius = maxJump;
            GetStarRecords(cur->GetPosition(), crit, neighbors);
            for (ListNode* n = queue.mAnchor.mpNext; n != &queue.mAnchor; n = n->mpNext) {}
            for (StarRef* it = neighbors.mpBegin; it != neighbors.mpEnd; ++it) {
                cStarRecord* nb = it->mpObject;
                if (!(nb->GetFlags() & 0x40000000)) {
                    nb->SetFlag(0x40000000, true);
                    queue.push_back(nb);
                }
            }
        }

        bool allReached = true;
        float farthest = 0.0f;
        for (StarRecordRow* row = mpGridBegin; row != mpGridEnd; ++row) {
            for (StarRef* it = row->mpBegin; it != row->mpEnd; ++it) {
                cStarRecord* rec = it->mpObject;
                if (!(rec->GetFlags() & 0x40000000)) {
                    allReached = false;
                    StarVector near;
                    crit.maxRadius = limit;
                    GetStarRecords(rec->GetPosition(), crit, near);
                    for (StarRef* p = near.mpBegin; p != near.mpEnd; ++p) {
                        if (p->mpObject == rec) {
                            // near.erase(p)
                            if (p + 1 < near.mpEnd)
                                DoCopy(p + 1, near.mpEnd, p);
                            --near.mpEnd;
                            near.mpEnd->~StarRef();
                            break;
                        }
                    }

                    StarVector reached;
                    StarVector unreached;
                    unreached.insert(unreached.mpBegin, StarRef(rec));
                    for (StarRef* p = near.mpBegin; p != near.mpEnd; ++p) {
                        cStarRecord* nb = p->mpObject;
                        if (rec->GetFlags() & 0x40000000)
                            reached.push_back(StarRef(nb));
                        else
                            unreached.push_back(StarRef(nb));
                    }

                    if (reached.mpBegin != reached.mpEnd) {
                        float minDist = g_FltMax;
                        for (StarRef* p = reached.mpBegin; p != reached.mpEnd; ++p) {
                            cStarRecord* r = p->mpObject;
                            cStarRecord* nearest = FindNearest(r->GetPosition(), unreached);
                            float d = Distance2D(&nearest->GetPosition(), &r->GetPosition());
                            if (d < minDist)
                                minDist = d;
                        }
                        if (minDist > farthest)
                            farthest = minDist;
                    } else {
                        cStarRecord* nearest = FindNearest(rec->GetPosition(), near);
                        if (nearest) {
                            float d = Distance2D(&nearest->GetPosition(), &rec->GetPosition());
                            if (d > farthest)
                                farthest = d;
                        } else {
                            farthest = limit;
                        }
                    }
                }
                rec->SetFlag(0x40000000, false);
            }
        }

        if (allReached) {
            done = true;
        } else {
            const float a = maxJump + g_Epsilon;
            const float b = farthest + g_Epsilon;
            maxJump = (a < b) ? b : a;
        }
        if (!flag)
            done = true;
    } while (!done);
}
