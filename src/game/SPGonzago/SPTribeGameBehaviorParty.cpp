// src/game/SPGonzago/SPTribeGameBehaviorParty.cpp -- migrated from slice(s) s00d79470, s00d78ad0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeGameBehaviorParty.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cActionCircle.h"
#include "SP/cInteractionAgent.h"
#include "SP/cInteractionTarget.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include "SP/cTribe.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void FUN_00F47380(void* p);                        // operator delete (cdecl-1)
extern "C" void  FUN_00921580(void* pNode);
extern "C" void  FUN_00921880(void* pNode, void* pHeader);
extern "C" void  FUN_00DA6270(void* pObj, int arg);
extern const char  gSimulatorName[];   // 0x13f09b4  ("Simulator")
extern const char  gAllocFileName;     // 0x13ebb38
extern void* gVTable147BF60;      // 0x147bf60
extern void* gVTable147BF4C;      // 0x147bf4c

// ---- items of slice s00d78ad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char    U8;
typedef unsigned int     U32;
typedef unsigned __int64 U64;
struct VT {
    virtual void  q00();                       // +0x00
    virtual void* q01(int id);                 // +0x04
    virtual void* q02(int id);                 // +0x08
    virtual void  q03();                       // +0x0c
    virtual void  q04();                       // +0x10
    virtual void  q05();                       // +0x14
    virtual void  q06();                       // +0x18
    virtual void  q07();                       // +0x1c
    virtual void  q08();                       // +0x20
    virtual void  q09();                       // +0x24
    virtual void  q10();                       // +0x28
    virtual void* q11();                       // +0x2c  -> Vector3*
    virtual U32   q12();                       // +0x30
    virtual void  q13();                       // +0x34
    virtual void  q14();                       // +0x38
    virtual void  q15();                       // +0x3c
    virtual void  q16();                       // +0x40
    virtual void  q17();                       // +0x44
    virtual void  q18();                       // +0x48
    virtual void  q19();                       // +0x4c
    virtual void  q20();                       // +0x50
    virtual void  q21();                       // +0x54
    virtual void* q22();                       // +0x58
    virtual void  q23();                       // +0x5c
    virtual void  q24();                       // +0x60
    virtual void  q25();                       // +0x64
    virtual void  q26();                       // +0x68
    virtual void  q27();                       // +0x6c
    virtual void  q28();                       // +0x70
    virtual float q29();                       // +0x74
    virtual void  q30();                       // +0x78
    virtual void  q31();                       // +0x7c
    virtual void  q32();                       // +0x80
    virtual void  q33();                       // +0x84
    virtual void  q34();                       // +0x88
    virtual void  q35();                       // +0x8c
    virtual void  q36();                       // +0x90
    virtual void  q37();                       // +0x94
    virtual void  q38();                       // +0x98
    virtual void  q39();                       // +0x9c
    virtual void  q40();                       // +0xa0
    virtual void  q41();                       // +0xa4
    virtual void  q42();                       // +0xa8
    virtual void* q43();                       // +0xac
    virtual void  q44();                       // +0xb0
    virtual void  q45();                       // +0xb4
    virtual void  q46();                       // +0xb8
    virtual void  q47();                       // +0xbc
    virtual void  q48();                       // +0xc0
    virtual void  q49();                       // +0xc4
    virtual void  q50();                       // +0xc8
    virtual void  q51();                       // +0xcc
    virtual void  q52();                       // +0xd0
    virtual void  q53();                       // +0xd4
    virtual void  q54();                       // +0xd8
    virtual void  q55(void* pGoal);            // +0xdc
    virtual void  q56();                       // +0xe0
    virtual void  q57();                       // +0xe4
    virtual void  q58();                       // +0xe8
    virtual void  q59();                       // +0xec
    virtual void  q60();                       // +0xf0
    virtual void  q61();                       // +0xf4
    virtual char  q62();                       // +0xf8
    virtual void  q63();                       // +0xfc
};
struct FnC22F50  { void*  __thiscall f(); };
struct FnC14750  { void   __thiscall f(int); };
struct FnC232C0  { char   __thiscall f(); };
struct FnC8E7C0  { char   __thiscall f(); };
struct FnC9D9E0  { void*  __thiscall f(); };
struct FnC8E7D0  { void   __thiscall f(int); };
struct FnC8F6E0  { void*  __thiscall f(int); };
struct FnD79FD0  { void   __thiscall f(); };
struct FnD7A010  { char   __thiscall f(void* pObj); };
struct FnABF320  { void   __thiscall f(); };
struct FnAFBA10  { void   __thiscall f(); };
struct FnAFBAD0  { void   __thiscall f(); };
struct FnC2E4E0  { void   __thiscall f(); };
struct FnE5C780  { void   __thiscall f(void** ppOut, void** pKey); };
struct AgentArgs {
    void* mpBlocks;          // +0x00
    U32   mIndex;            // +0x04
    U32   m4;                // +0x08
    U32   m8;                // +0x0c
    U32   mC;                // +0x10
    U32   m10;               // +0x14
};
struct FnD7A020  { void   __thiscall f(AgentArgs args); };
extern "C" void FUN_00F47380(void* p);                        // operator delete (cdecl-1)
extern "C" void* FUN_00F473A0(U32 size, const char* pName, int flags,
                              int debugFlags, const char* pFile, int line);
extern "C" void  FUN_009216A0(void* pNode, void* pParent, void* pHeader, U32 side);
extern "C" void  FUN_00921580(void* pNode);
extern "C" void  FUN_00921880(void* pNode, void* pHeader);
extern "C" void  FUN_00572020(void* pObj, U32 arg);
extern "C" void  FUN_00DA6270(void* pObj, int arg);
extern const char  gSimulatorName[];   // 0x13f09b4  ("Simulator")
extern const char  gAllocFileName;     // 0x13ebb38
extern void* gVTable147BF60;      // 0x147bf60
extern void* gVTable147BF4C;      // 0x147bf4c
struct RBNodeBase {
    RBNodeBase* mpLeft;      // +0x00
    RBNodeBase* mpRight;     // +0x04
    RBNodeBase* mpParent;    // +0x08
    U32         mColor;      // +0x0c
};
struct RBTree {
    U32         mHeader;     // +0x00
    RBNodeBase  mAnchor;     // +0x04  (sentinel; mpParent holds the root)
    U32         mSize;       // +0x14
    U32         mField18;    // +0x18

    U32* InsertOrFind(const U32* pKey);
    void DoInsertValue(RBNodeBase** ppOut, RBNodeBase* pParent, const U64* pValue, const U32* pKey);  // 0x0101280
    void DoNukeSubtree(RBNodeBase* pNode);
};
struct RBValue16 {
    U32 mKey;                // +0x00
    U32 mV0;                 // +0x04
    U32 mV1;                 // +0x08
    U32 mV2;                 // +0x0c
};
struct RBNode16 {
    RBNodeBase mBase;        // +0x00
    RBValue16  mPair;        // +0x10
};
struct RBTree16 {
    U32         mHeader;     // +0x00
    RBNodeBase  mAnchor;     // +0x04
    U32         mSize;       // +0x14

    void InsertNode(RBNode16** ppOut, RBNodeBase* pParent,
                    const RBValue16* pValue, char leftmost);
};
struct SegEntry {
    void* mpUnk00;           // +0x00
    void* mpBuffer;          // +0x04
};
struct ActionCircle {
    U8 mPad00[0x64];
};
struct cTribeGameBehaviorParty : VT {
    void*   mpVTable2;               // +0x04
    U32     mPad08;                  // +0x08
    void**  mpBlocks;                // +0x0c  target-list block array
    U32     mPad10;                  // +0x10
    U32     mPad14;                  // +0x14
    U32     mPad18;                  // +0x18
    U32     mPad1C;                  // +0x1c
    U32     mPad20;                  // +0x20
    U32     mFreeChain;              // +0x24  target-list free-chain index
    U8      mPad28[0x74 - 0x28];
    RBTree  mAgentTree;              // +0x74
    void*   mpField90;               // +0x90
    U32     mField94;                // +0x94
    float   mField98;                // +0x98
    ActionCircle mCircle9C;          // +0x9c
    U8      mByte100;                // +0x100

    void* Init();
    cTribeGameBehaviorParty* Destroy(U8 flag);
    char CanJoin(void* pAgent, U32 unused);
    void PreAction();
    void PostAction();
    void RemoveAgent(void** ppBlocks, U32 idx, U32 a3, U32 a4, U32 a5, U32 a6);
    char AddAgent(void* pAgent);
};
struct SpatialObject : VT {};
struct Creature : VT {
    U8            mPad04[0xc0 - 0x04];
    SpatialObject mSpatial;          // +0xc0
    U8            mPadC4[0xb58 - 0xc4];
    U32           mFlagsB58;         // +0xb58
};
struct Comparator {
    char __thiscall FUN_00AC0730(void* pA, void* pB);
};
// ---- items of slice s00d78ad0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* FUN_00F473A0(U32 size, const char* pName, int flags,
                              int debugFlags, const char* pFile, int line);
extern "C" void  FUN_009216A0(void* pNode, void* pParent, void* pHeader, U32 side);
extern "C" void  FUN_00572020(void* pObj, U32 arg);

// ---- items of slice s00d79470 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete[](void* p);   // 0x00f47380
namespace SP {
static const uint32_t kPartyTargetType = 0x0116d858;
}
namespace SP {
static const uint32_t kCreatureType = 0x4f176642;
}
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(inv * x, y * inv, z * inv);
    }
    float LengthSquared() const { return x * x + y * y + z * z; }
    cSPVector3& operator+=(const cSPVector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    bool operator==(const cSPVector3& v) const { return x == v.x && y == v.y && z == v.z; }
};
}
namespace SP {
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace SP {
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
}
namespace SP {
inline float Dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
}
namespace SP {
extern const cSPVector3 kZeroVector;   // 0x0169efec
}
namespace SP {
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace SP {
inline Vector3 Sub(const cSPVector3& a, const cSPVector3& b)
{
    Vector3 r(a.x - b.x, a.y - b.y, a.z - b.z);
    return r;
}
}
namespace SP {
struct cSPVector3Arg : cSPVector3 {
    cSPVector3Arg(const Vector3& v) : cSPVector3(v.x, v.y, v.z) {}
};
}
namespace SP {
cSPVector3 normalized_safe(const cSPVector3Arg& v);   // 0x00449c20
}
namespace SP {
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
}
namespace SP {
class cSpatialObject_s00d7_9470 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const cSPVector3& GetPosition();   // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void v70();
    virtual float GetBoundingRadius();         // +0x74
};
}
namespace SP {
struct cLocomotionState {
    uint32_t pad00[0x17];
    int field_5c;                          // non-zero while a move goal is set
    const cSPVector3& GetGoal();           // 0x00c423c0
};
}
namespace SP {
class cLocomotiveObject_s00d7_9470 : public cSpatialObject_s00d7_9470 {
public:
    cLocomotionState* GetState();          // 0x00c41ec0
    bool IsNearGoal();                     // 0x00c42e20
};
}
namespace SP {
class cInteractionAgent_s00d7_9470 { uint32_t mFirst; };
}
namespace SP {
class cSPCreatureBase_s00d7_9470 {
public:
    virtual void v00();
    uint32_t pad04[0x15];
    cInteractionAgent_s00d7_9470 mAgent;              // +0x58
    uint32_t pad5c[0x19];
    cLocomotiveObject_s00d7_9470 mLocomotion;         // +0xc0

    enum eSpeedState { kSpeedRun = 2 };
    void MoveToPointAndFacingAtSpeed(eSpeedState speed, const cSPVector3& point,
                                     const cSPVector3& facing, float f1, float f2);   // 0x00c1c5c0
    bool IsInSubInteraction();                                     // 0x00c232c0 (field +0x1014 != 0)
    bool IsIdle(int a, int b);                                     // 0x00c25480
    void InterruptAnimation(uint32_t animID, int a, int b);        // 0x00c12310
    bool AnimationFinished(int a);                                 // 0x00c123f0
};
}
namespace SP {
class cTribe_s00d7_9470 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
    virtual class cPartyTarget* GetLeader();  // +0xac
    uint32_t pad04[0x99];
    float mPartyRadius;                    // +0x268
    void SetParty(bool b);                 // 0x00c8e7d0
};
}
namespace SP {
class cPartyTarget {
public:
    virtual void v00();
    uint32_t pad04[0xc];
    cSpatialObject_s00d7_9470 mSpatial;               // +0x34
    cTribe_s00d7_9470* GetTribe();                    // 0x00c9d9e0
};
}
namespace SP {
class cInteractionTarget_s00d7_9470 {
public:
    virtual void v00();
    virtual cPartyTarget* Cast(uint32_t typeID);   // +0x4
};
}
namespace SP {
class cInteractionAgentObject {
public:
virtual void v00();
virtual void v04();
    virtual cSPCreatureBase_s00d7_9470* Cast(uint32_t typeID);   // +0x8
};
}
namespace SP {
struct tSlotEntry { uint32_t mSlotInfo; void* mpData; };
}
namespace SP {
struct AgentDeque {
    tSlotEntry** mpBlocks;
    int Count();                           // 0x00abefd0
};
}
namespace SP {
struct AgentFilter {
    class cTribeGameBehaviorParty_s00d7_9470* mpOwner;
    bool mbFlag;
    AgentFilter(class cTribeGameBehaviorParty_s00d7_9470* pOwner, bool flag) : mpOwner(pOwner), mbFlag(flag) {}
};
}
namespace SP {
struct AgentIterator {
    AgentDeque* mpDeque;
    uint32_t mIndex;
    AgentDeque* mpEndDeque;
    uint32_t mEndIndex;
    AgentFilter mFilter;

    AgentIterator(AgentDeque* pDeque, const AgentFilter& filter);   // 0x00abf010
    void Next();                                                     // 0x00abeb20
    __forceinline bool IsDone() const { return (uint32_t)mpDeque + mIndex == (uint32_t)mpEndDeque + mEndIndex; }
    __forceinline cInteractionAgentObject* Get() const
    {
        return (cInteractionAgentObject*)mpDeque->mpBlocks[mIndex >> 7][mIndex & 0x7f].mpData;
    }
};
}
namespace SP {
struct cAgentInfo {
    int mState;                            // InteractionState
    uint32_t mDanceIndex;
    bool mbSuccess;
};
}
namespace SP {
struct AgentInfoMap {
    uint32_t mData[7];
    cAgentInfo& operator[](cInteractionAgent_s00d7_9470* const& key);   // 0x00d79350
};
}
namespace SP {
struct tSlot_s00d7_9470 {                   // cActionCircle::tSlot (0x18 bytes)
    bool mbOccupied;             // +0x0
    uint32_t pad04[2];
    cSPVector3 mPosition;        // +0xc
    void Occupy(cSPCreatureBase_s00d7_9470* pCreature);   // 0x00afa030
};
}
namespace SP {
class cActionCircle_s00d7_9470 {
public:
    uint32_t pad00[0x14];
    tSlot_s00d7_9470* mSlotsBegin;          // +0x50 (mSlots)
    tSlot_s00d7_9470* mSlotsEnd;            // +0x54
    void SetCenter(const cSPVector3& pos, float radius, const cSPVector3& dir, float altitude);   // 0x00af9cf0
    void SetSlots(int arg, float spacing);                                                    // 0x00afef10
};
}
namespace SP {
void UpdateActionCircle(cActionCircle_s00d7_9470* pCircle);   // 0x00d9aa20
}
namespace SP {
class IBehaviorManager {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual uint32_t GetDeltaTimeMS();   // +0x10
};
}
namespace SP {
IBehaviorManager* BehaviorManager();     // 0x00b3d260
}
namespace SP {
void SortSectionMembers(cSPCreatureBase_s00d7_9470** first, cSPCreatureBase_s00d7_9470** last, cSPVector3 center);
}
namespace SP {
extern const uint32_t kDanceMoves[7];    // 0x0158441c
}
namespace SP {
extern float kPartyWalkSpeedA;           // 0x01572070
}
namespace SP {
extern float kPartyWalkSpeedB;           // 0x0157206c
}
namespace SP {
enum InteractionState {
    kNone = 0,
    kInSubInteraction = 1,
    kMoveToSpotOnCircle = 2,
    kWaitingInCircle = 3,
    kStartDancing = 4,
    kStartDanceMove = 5,
    kDancing = 6,
    kLastDance = 7,
};
}
namespace SP {
class cTribeGameBehaviorParty_s00d7_9470 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual int Action();                                   // +0x18
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
    virtual void AgentFinished(AgentIterator it);           // +0x44

    bool IsActiveAgent(cInteractionAgent_s00d7_9470* pAgent);          // 0x00abea40
    __forceinline cInteractionTarget_s00d7_9470* GetFirstTarget()
    {
        if (mTargetFirst == 0x3fffffff)
            return 0;
        return (cInteractionTarget_s00d7_9470*)mTargetBlocks[mTargetFirst >> 7][mTargetFirst & 0x7f].mpData;
    }
    __forceinline cPartyTarget* GetPartyTarget()
    {
        cInteractionTarget_s00d7_9470* p = GetFirstTarget();
        if (p)
            return p->Cast(kPartyTargetType);
        return 0;
    }
    AgentIterator FindAgent(cInteractionAgent_s00d7_9470* pAgent);     // 0x00abf110

    uint32_t pad04[2];
    tSlotEntry** mTargetBlocks;            // +0x0c mTargetList
    uint32_t pad10[5];
    uint32_t mTargetFirst;                 // +0x24
    uint32_t pad28;
    AgentDeque mAgentList;                 // +0x2c
    uint32_t pad30[0x11];
    AgentInfoMap mAgentInfoMap;            // +0x74
    uint32_t mSoundHandle;                 // +0x90
    int mPartyState;                       // +0x94
    float mTimer;                          // +0x98
    cActionCircle_s00d7_9470 mActionCircle;           // +0x9c
    uint32_t padf4[3];
    bool mUpdateConfiguration;             // +0x100
};
}
namespace SP {
namespace EA_Audio {
class IAudioSystem {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual uint32_t NewHandle();          // +0x20
};
}
}
namespace SP {
namespace EA_Audio {
IAudioSystem* GetSystemAT();               // 0x00a206f0
}
}
namespace SP {
void Start3dSoundByName(uint32_t soundID, uint32_t handle, float x, float y, float z);   // 0x00571f80
}
namespace SP {
class cSub58 {
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
    virtual int Check();                             // +0x20
    uint8_t mData[0x20];
};
}
namespace SP {
class cObjectManager {
public:
    uint32_t mField0;
    uint32_t mField4;
    void* Get(uint32_t mask, uint32_t zero);         // 0x00bc96a0
    void* GetZeroFirst(uint32_t zero, uint32_t mask); // 0x00bc96a0
    void Remove(uint32_t mask, uint32_t zero);       // 0x00bc98f0
};
}
namespace SP {
class cManagerOwner {
public:
    uint8_t mPad00[8];
    cObjectManager mManager;                         // +0x08
    uint8_t mPad18[0x1cc - 0x10];
    uint32_t mField1cc;                              // +0x1cc
    uint8_t mPad1d0[0x1d8 - 0x1d0];
    uint32_t mField1d8;                              // +0x1d8
};
}
namespace SP {
class cC04590Result {
public:
    uint8_t mPad00[0x190];
    uint8_t mFlag190;                                // +0x190
};
}
namespace SP {
class cEditorGameObject {
public:
    void* mpVtable0;
    void* mpVtable4;
    uint8_t mPad08[0x58 - 0x08];
    cSub58 mSub58;                                   // +0x58
    uint8_t mPad7c[0x110 - 0x7c];
    uint32_t mFlags110;                              // +0x110
    uint8_t mPad114[0x5e0 - 0x114];
    float mField5e0;                                 // +0x5e0
    uint8_t mPad5e4[0xb20 - 0x5e4];
    uint32_t mObjectID;                              // +0xb20
    uint8_t mPadB24[0xb4c - 0xb24];
    cManagerOwner* mpB4C;                            // +0xb4c
    uint8_t mPadB50[8];
    uint32_t mFlagsB58;                              // +0xb58
    uint8_t mPadB5C[2];
    uint8_t mByteB5E;                                // +0xb5e
    uint8_t mPadB5F[0x1004 - 0xb5f];
    uint32_t mField1004;                             // +0x1004
    uint8_t mPad1008[0x101c - 0x1008];
    uint32_t mField101c;                             // +0x101c

    void BaseDestroy();                              // 0x00abf190
    void Destroy();                                  // 0x00d79fd0
    cC04590Result* LookupC04590();                   // 0x00c04590
    bool IsEditorActionAvailable();                  // 0x00c0bb90
};
}
// ---- items of slice s00d79470 end

// @ 0x00d78e20
void FUN_00d78e20(void** pFirst, void** pLast, Comparator rComp)
{
    for (void** i = pFirst; i != pLast; ++i) {
        void* value = *i;
        void** j = i;
        void** p = i - 1;
        while (rComp.FUN_00AC0730(value ? (void*)((char*)value + 0xc0) : 0,
                                  *p    ? (void*)((char*)*p    + 0xc0) : 0)) {
            *j = *p;
            --j;
            --p;
        }
        *j = value;
    }
}

// @ 0x00d78e90
char cTribeGameBehaviorParty::CanJoin(void* pAgent, U32 unused)
{
    void* citizen;
    if (pAgent != 0) {
        citizen = ((VT*)pAgent)->q02(0x4f176642);
        if (citizen == 0) goto haveCitizen;
        if (((FnC232C0*)citizen)->f() != 0) goto haveCitizen;
    }
    citizen = 0;
haveCitizen:
    if (mFreeChain != 0x3fffffff) {
        SegEntry* pEntry = (SegEntry*)((char*)mpBlocks[mFreeChain >> 7] + (mFreeChain & 0x7f) * 8);
        void* pBuf = pEntry->mpBuffer;
        if (pBuf != 0) {
            void* pObj = ((VT*)pBuf)->q01(0x116d858);
            if (pObj != 0) {
                if (reinterpret_cast<U32>(((VT*)pObj)->q22()) == 10 && citizen != 0) {
                    if (((FnC22F50*)citizen)->f() != 0) {
                        if (((FnC8E7C0*)((FnC22F50*)citizen)->f())->f() == 0) {
                            void* pA = ((FnC9D9E0*)pObj)->f();
                            void* pB = ((FnC22F50*)citizen)->f();
                            return (pB == pA) ? 1 : 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// @ 0x00d78f50
void cTribeGameBehaviorParty::PreAction()
{
    mField94 = 0;
    mField98 = 0.0f;
    mByte100 = 1;
    ((FnC2E4E0*)this)->f();

    void* pCitizen;
    void* pField = ((VT*)this)->q22();
    if (pField != 0) {
        pCitizen = ((VT*)pField)->q02(0x4f176642);
    } else {
        pCitizen = 0;
    }

    void* pObj;
    if (mFreeChain != 0x3fffffff) {
        SegEntry* pEntry = (SegEntry*)((char*)mpBlocks[mFreeChain >> 7] + (mFreeChain & 0x7f) * 8);
        void* pBuf = pEntry->mpBuffer;
        if (pBuf != 0) {
            pObj = ((VT*)pBuf)->q01(0x116d858);
        } else {
            pObj = 0;
        }
    } else {
        pObj = 0;
    }

    if (pCitizen != 0) {
        if (((FnC232C0*)pCitizen)->f() != 0) {
            void* pTribe = ((FnC22F50*)pCitizen)->f();
            if (pTribe != 0 && pObj == 0) {
                ((FnC8F6E0*)pTribe)->f(10);
            }
        }
    }
}

// @ 0x00d79000
void cTribeGameBehaviorParty::PostAction()
{
    if (mFreeChain != 0x3fffffff) {
        SegEntry* pEntry = (SegEntry*)((char*)mpBlocks[mFreeChain >> 7] + (mFreeChain & 0x7f) * 8);
        void* pBuf = pEntry->mpBuffer;
        if (pBuf != 0) {
            void* pObj = ((VT*)pBuf)->q01(0x116d858);
            if (pObj != 0) {
                void* pRef = ((FnC9D9E0*)pObj)->f();
                if (pRef != 0) {
                    ((FnC8E7D0*)pRef)->f(0);
                }
            }
        }
    }
    ((FnC2E4E0*)this)->f();
    if (mpField90 != 0) {
        FUN_00572020(mpField90, 0);
        mpField90 = 0;
    }
}

// @ 0x00d79080
void RBTree16::InsertNode(RBNode16** ppOut, RBNodeBase* pParent, const RBValue16* pValue, char leftmost)
{
    U32 side;
    if (leftmost == 0 && pParent != &mAnchor &&
        pValue->mKey >= ((RBNode16*)pParent)->mPair.mKey) {
        side = 1;
    } else {
        side = 0;
    }
    RBNode16* pNode = (RBNode16*)FUN_00F473A0(0x20, gSimulatorName, 0, 0, &gAllocFileName, 0xd1);
    RBValue16* pDst = &pNode->mPair;
    if (pDst != 0) {
        *pDst = *pValue;
    }
    FUN_009216A0(pNode, pParent, &mAnchor, side);
    mSize++;
    *ppOut = pNode;
}

// @ 0x00d791a0
void* cTribeGameBehaviorParty::Init()
{
    ((FnABF320*)this)->f();                       // base-class constructor
    *reinterpret_cast<void**>(static_cast<VT*>(this)) = &gVTable147BF60;
    mpVTable2 = &gVTable147BF4C;

    mAgentTree.mAnchor.mpRight  = 0;              // +0x7c
    mAgentTree.mAnchor.mpParent = 0;              // +0x80
    mAgentTree.mAnchor.mColor   = 0;              // +0x84
    mAgentTree.mAnchor.mpParent = 0;              // +0x80
    *reinterpret_cast<U8*>(&mAgentTree.mAnchor.mColor) = 0;   // +0x84
    mAgentTree.mSize            = 0;              // +0x88
    mAgentTree.mAnchor.mpLeft   = &mAgentTree.mAnchor;        // +0x78
    mAgentTree.mAnchor.mpRight  = &mAgentTree.mAnchor;        // +0x7c
    mpField90                   = 0;              // +0x90
    ((FnAFBA10*)&mCircle9C)->f();                 // construct the action circle
    return this;
}

// @ 0x00d791f0
cTribeGameBehaviorParty* cTribeGameBehaviorParty::Destroy(U8 flag)
{
    *reinterpret_cast<void**>(static_cast<VT*>(this)) = &gVTable147BF60;
    mpVTable2 = &gVTable147BF4C;
    ((FnAFBAD0*)&mCircle9C)->f();                 // destroy the action circle
    RBNodeBase* pRoot = mAgentTree.mAnchor.mpParent;
    mAgentTree.DoNukeSubtree(pRoot);
    ((FnD79FD0*)this)->f();
    if ((flag & 1) != 0) {
        FUN_00F47380(this);
    }
    return this;
}

// @ 0x00d79270
void cTribeGameBehaviorParty::RemoveAgent(void** ppBlocks, U32 idx, U32 a3, U32 a4, U32 a5, U32 a6)
{
    SegEntry* pEntry = (SegEntry*)((char*)(((void**)*ppBlocks)[idx >> 7]) + (idx & 0x7f) * 8);
    void* pBuf = pEntry->mpBuffer;
    void* pKey = 0;
    if (pBuf != 0) {
        void* pCitizen = ((VT*)pBuf)->q02(0x4f176642);
        if (pCitizen != 0) {
            ((FnC14750*)pCitizen)->f(0);
            FUN_00DA6270(pCitizen, 0xc);
            pKey = (char*)pCitizen + 0x58;
        }
    }
    RBNodeBase* pFound = 0;
    ((FnE5C780*)&mAgentTree)->f((void**)&pFound, &pKey);
    if (pFound != &mAgentTree.mAnchor) {
        mAgentTree.mSize--;
        FUN_00921580(pFound);
        FUN_00921880(pFound, &mAgentTree.mAnchor);
        FUN_00F47380(pFound);
    }
    ((FnD7A020*)this)->f(*reinterpret_cast<AgentArgs*>(&ppBlocks));
}

// @ 0x00d79350
U32* RBTree::InsertOrFind(const U32* pKey)
{
    RBNodeBase* pNode = mAnchor.mpParent;
    RBNodeBase* pParent = &mAnchor;
    if (pNode != 0) {
        do {
            if (((RBNode16*)pNode)->mPair.mKey < *pKey) {
                pNode = pNode->mpLeft;
            } else {
                pParent = pNode;
                pNode = pNode->mpRight;
            }
        } while (pNode != 0);
    }
    if (pParent != &mAnchor && *pKey >= ((RBNode16*)pParent)->mPair.mKey) {
        return &((RBNode16*)pParent)->mPair.mKey + 1;
    }
    U32 key = *pKey;
    U64 value = 0;
    RBNodeBase* pResult = 0;
    DoInsertValue(&pResult, pParent, &value, pKey);
    return (U32*)((char*)pResult + 0x14);
}

// @ 0x00d793e0
char cTribeGameBehaviorParty::AddAgent(void* pAgent)
{
    char result = 0;
    if (((FnD7A010*)this)->f(pAgent) != 0 && pAgent != 0) {
        void* pCitizen = ((VT*)pAgent)->q02(0x4f176642);
        if (pCitizen != 0 && ((FnC232C0*)pCitizen)->f() != 0) {
            void* pKey = (char*)pCitizen + 0x58;
            U32* pSlot = mAgentTree.InsertOrFind(reinterpret_cast<const U32*>(&pKey));
            *pSlot = 0;
            SpatialObject* pSpatial = &((Creature*)pCitizen)->mSpatial;
            U8 flag = (pSpatial->q62() == 0) ? 1 : 0;
            ((FnC14750*)pCitizen)->f(flag);
            ((VT*)pSpatial)->q59();
        }
    }
    return result;
}

// @ 0x00d79470
namespace SP {
int cTribeGameBehaviorParty_s00d7_9470::Action()
{
    AgentIterator it(&mAgentList, AgentFilter(this, false));
    if (it.IsDone())
        return 1;

    cPartyTarget* pTarget = GetPartyTarget();
    if (!pTarget)
        return 0;

    if (mPartyState == 1) {
        mTimer += (float)BehaviorManager()->GetDeltaTimeMS() * 0.001f;
        if (mTimer > 1.0f) {
            mTimer = 0.0f;
            mUpdateConfiguration = true;
        }
    }

    if (mUpdateConfiguration) {
        // place every participant on the action circle around the party target
        cTribe_s00d7_9470* pTribe = pTarget->GetTribe();
        mUpdateConfiguration = false;
        pTribe->SetParty(true);
        int count = mAgentList.Count();
        float slotRadius = pTribe->mPartyRadius;
        float radius = pTarget->mSpatial.GetBoundingRadius() + slotRadius;
        const cSPVector3& center = pTarget->mSpatial.GetPosition();
        cSPVector3 dir = normalized_safe(Sub(pTribe->GetLeader()->mSpatial.GetPosition(), center));
        mActionCircle.SetCenter(center, sqrtf((float)count * slotRadius * slotRadius + radius * radius), dir, 0.0f);
        mActionCircle.SetSlots(0, slotRadius * 0.5f);
        UpdateActionCircle(&mActionCircle);

        cSPVector3 groupCenter(kZeroVector);
        FixedVector<cSPCreatureBase_s00d7_9470*, 16> creatures;
        for (; !it.IsDone(); it.Next()) {
            cInteractionAgentObject* pAgent = it.Get();
            cSPCreatureBase_s00d7_9470* pCreature;
            if (pAgent && (pCreature = pAgent->Cast(kCreatureType)) != 0 && IsActiveAgent(&pCreature->mAgent)) {
                creatures.push_back(pCreature);
                groupCenter += pCreature->mLocomotion.GetPosition();
            }
        }
        float inv = 1.0f / (float)creatures.size();
        groupCenter = groupCenter * inv;
        SortSectionMembers(creatures.mpBegin, creatures.mpEnd, groupCenter);

        uint32_t n = creatures.size();
        for (uint32_t i = 0; i < n; ++i) {
            cSPCreatureBase_s00d7_9470* pCreature = creatures.mpBegin[i];
            const cSPVector3& pos = pCreature->mLocomotion.GetPosition();
            cSPVector3 dirFromCenter = (pos - groupCenter).Normalized();
            if (dirFromCenter == kZeroVector)
                dirFromCenter = (pos - center).Normalized();

            uint32_t bestSlot = (uint32_t)-1;
            float bestScore = 0.0f;
            uint32_t numSlots = (uint32_t)(mActionCircle.mSlotsEnd - mActionCircle.mSlotsBegin);
            for (uint32_t k = 0; k < numSlots; ++k) {
                if (!mActionCircle.mSlotsBegin[k].mbOccupied) {
                    cSPVector3 toSlot = mActionCircle.mSlotsBegin[k].mPosition - center;
                    float invLen = 1.0f / sqrtf(toSlot.x * toSlot.x + toSlot.y * toSlot.y + toSlot.z * toSlot.z);
                    float score = (Dot(toSlot * invLen, dirFromCenter) + 1.0f) * invLen;
                    if (score > bestScore) {
                        bestSlot = k;
                        bestScore = score;
                    }
                }
            }
            if (bestSlot != (uint32_t)-1) {
                tSlot_s00d7_9470* pSlot = &mActionCircle.mSlotsBegin[bestSlot];
                cSPVector3 facing = (center - pSlot->mPosition).Normalized();
                pSlot->Occupy(pCreature);
                // (re)send the creature unless it is already heading to this slot
                cLocomotionState* pState = pCreature->mLocomotion.GetState();
                if (pState->field_5c == 0 || (pState->GetGoal() - pSlot->mPosition).LengthSquared() > 1.5258789e-05f) {
                    pCreature->MoveToPointAndFacingAtSpeed(cSPCreatureBase_s00d7_9470::kSpeedRun, pSlot->mPosition, facing,
                                                           kPartyWalkSpeedA, kPartyWalkSpeedB);
                    mAgentInfoMap[&pCreature->mAgent].mState = kInSubInteraction;
                }
            } else {
                AgentFinished(FindAgent(&pCreature->mAgent));
            }
        }
        return 1;
    }

    // per-agent dance state machine
    bool anyInSubInteraction = false;
    bool anyWaiting = false;
    for (; !it.IsDone(); it.Next()) {
        cInteractionAgentObject* pAgent = it.Get();
        cSPCreatureBase_s00d7_9470* pCreature;
        if (pAgent && (pCreature = pAgent->Cast(kCreatureType)) != 0 && pCreature->IsInSubInteraction() &&
            IsActiveAgent(&pCreature->mAgent)) {
            cAgentInfo& info = mAgentInfoMap[&pCreature->mAgent];
            switch (info.mState) {
            case kInSubInteraction:
                anyInSubInteraction = true;
                if (pCreature->IsIdle(0, 1) && pCreature->mLocomotion.IsNearGoal())
                    info.mState = kWaitingInCircle;
                break;
            case kWaitingInCircle:
                anyWaiting = true;
                break;
            case kStartDancing:
                info.mState = kStartDanceMove;
                break;
            case kDancing:
                if (!pCreature->AnimationFinished(0))
                    break;
                // fall through
            case kStartDanceMove:
                if (info.mDanceIndex >= 7) {
                    info.mState = kLastDance;
                } else {
                    pCreature->InterruptAnimation(kDanceMoves[info.mDanceIndex % 7], -1, 0);
                    info.mDanceIndex++;
                    info.mState = info.mDanceIndex < 7 ? kDancing : kLastDance;
                }
                break;
            case kLastDance:
                if (pCreature->AnimationFinished(0)) {
                    info.mbSuccess = true;
                    AgentFinished(it);
                }
                break;
            }
        }
    }

    if (anyWaiting) {
        if (anyInSubInteraction) {
            mPartyState = 1;
            return 1;
        }
        // everybody is in the circle: start dancing
        mPartyState = 2;
        AgentIterator it2(&mAgentList, AgentFilter(this, false));
        if (mSoundHandle == 0) {
            EA_Audio::IAudioSystem* pAudio = EA_Audio::GetSystemAT();
            mSoundHandle = pAudio ? pAudio->NewHandle() : 0;
            const cSPVector3& pos = pTarget->mSpatial.GetPosition();
            Start3dSoundByName(0x19dc06df, mSoundHandle, pos.x, pos.y, pos.z);
        }
        for (; !it2.IsDone(); it2.Next()) {
            cInteractionAgentObject* pAgent = it2.Get();
            cSPCreatureBase_s00d7_9470* pCreature;
            if (pAgent && (pCreature = pAgent->Cast(kCreatureType)) != 0 && pCreature->IsInSubInteraction() &&
                IsActiveAgent(&pCreature->mAgent))
                mAgentInfoMap[&pCreature->mAgent].mState = kStartDancing;
        }
    }
    return 1;
}
}  // namespace SP

// @ 0x00d79fd0
namespace SP {
void cEditorGameObject::Destroy()
{
    mpVtable0 = (void*)0x147bdb0;
    mpVtable4 = (void*)0x147bda0;
    BaseDestroy();
}
}  // namespace SP
