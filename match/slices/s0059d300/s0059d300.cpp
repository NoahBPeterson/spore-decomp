// Slice s0059d300 -- SP::cSPEditorAnimatedEventInfo messaging / manager events.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (same region as s0059b4b0).
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <math.h>

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }

namespace EA {
template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) { mnRefCount = 1; delete this; return 0; }
        return mnRefCount;
    }
protected:
    T mnRefCount;   // +0x8 when preceded by one vptr
};
}  // namespace EA

struct IMessageRC {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
};

namespace SP {

enum eAnimatedEvent { kAnimatedEvent0 = 0 };
class cSPEditorBlock { public: char pad[0x10]; };
class cSPEditorModel { public: char pad[0x10]; };

class cSPEditorAnimatedEventInfo : public IMessageRC, public EA::RefCountVTemplate<int> {
public:
    cSPEditorAnimatedEventInfo();
    virtual ~cSPEditorAnimatedEventInfo() {}

    void MessagePost(eAnimatedEvent event, cSPEditorBlock* block, cSPEditorModel* model,
                     uint32_t creatureID, bool isBaby, float delayTime, bool doLoop,
                     uint32_t animID, float animSpeed);
    void MessageSend(eAnimatedEvent event, cSPEditorBlock* block, cSPEditorModel* model,
                     uint32_t creatureID, bool isBaby, float delayTime, bool doLoop,
                     uint32_t animID, float animSpeed);

    uint32_t        mAnimatedCreatureID;   // +0xc
    cSPEditorBlock* mSourceBlock;          // +0x10
    cSPEditorModel* mSourceModel;          // +0x14
    eAnimatedEvent  mEvent;                // +0x18
    bool            mIsBaby;               // +0x1c
    float           mDelayTime;            // +0x20
    bool            mDoLoop;               // +0x24
    uint32_t        mAnimID;               // +0x28
    float           mAnimSpeed;            // +0x2c
};

struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void Send(uint32_t msg, void* payload, int a);                  // +0x14
    virtual void Post(uint32_t msg, void* payload, int a, int b);           // +0x18
};

class cSPEditorAnimatedCreatureManager : public EA::RefCountVTemplate<int> {
public:
    void Init(void* pModelWorld, bool flag);          // 0x0059c060
    bool HandleAnimatedEvent(void* e);                // 0x0059d300
    void Update(unsigned int msec);                   // 0x0059d610
    bool IsPlayingAnimation(unsigned int id);         // 0x0059cd20
    char pad_10[0x48 - 0x10];
};

struct AnimRequest;
struct AnimResult;
struct AnimContext;

struct IUnknown32S {
    virtual int AddRef();
    virtual int Release();
    ~IUnknown32S() {}
};
// eastl::vector<AutoRefCount<cPropertyList>, sp_vector_allocator>: three pointers used here; the
// destructor is the out-of-line instance at 0x004b5440.
struct AnimVecS {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    AnimVecS() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~AnimVecS();                                      // 0x004b5440
};

class cSPEditorAnimationManager : public EA::RefCountVTemplate<int>, public IUnknown32S {
public:
    __declspec(noinline) cSPEditorAnimationManager(); // 0x0059dac0
    // scalar deleting destructor ??_G is emitted from this inline destructor
// @ 0x0059db00
    virtual ~cSPEditorAnimationManager() {}
    void Init();                                      // 0x0059db40
    bool GetAnimation(AnimRequest* req, AnimResult* out, AnimContext* ctx);  // 0x0059dc70
    AnimVecS mAnimations;                             // +0xc
};

}  // namespace SP

using namespace SP;

IMessageServer* MessageServer();   // 0x0067dcc0
void* GetManager();                // 0x0067dcd0
void* PropertyManager();           // 0x0067de30

// ===========================================================================
// @ 0x0059d840
void cSPEditorAnimatedEventInfo::MessagePost(eAnimatedEvent event, cSPEditorBlock* block,
                                             cSPEditorModel* model, uint32_t creatureID, bool isBaby,
                                             float delayTime, bool doLoop, uint32_t animID,
                                             float animSpeed)
{
    IMessageServer* server = MessageServer();
    if (server) {
        mAnimatedCreatureID = creatureID;
        mSourceBlock = block;
        mEvent = event;
        mIsBaby = isBaby;
        mSourceModel = model;
        mDelayTime = delayTime;
        mAnimID = animID;
        mDoLoop = doLoop;
        mAnimSpeed = animSpeed;
        server->Post(0xd1511790, this, 0, 0);
    }
}

// ===========================================================================
// @ 0x0059d8b0
void cSPEditorAnimatedEventInfo::MessageSend(eAnimatedEvent event, cSPEditorBlock* block,
                                             cSPEditorModel* model, uint32_t creatureID, bool isBaby,
                                             float delayTime, bool doLoop, uint32_t animID,
                                             float animSpeed)
{
    IMessageServer* server = MessageServer();
    if (server) {
        mAnimatedCreatureID = creatureID;
        mSourceBlock = block;
        mEvent = event;
        mIsBaby = isBaby;
        mSourceModel = model;
        mDelayTime = delayTime;
        mAnimID = animID;
        mDoLoop = doLoop;
        mAnimSpeed = animSpeed;
        server->Send(0xd1511790, this, 0);
    }
}

// ===========================================================================
// @ 0x0059d930
struct AtomicCounter {
    char pad0[4];
    long mnRefCount;   // +0x4
    int GetRefCount();
};

// @ 0x0059d930
int AtomicCounter::GetRefCount()
{
    return _InterlockedExchangeAdd(&mnRefCount, 0);
}

// @ 0x0059da20
struct RefPair {
    char pad0[4];
    int m4;            // +0x4
    int m8;            // +0x8
    bool Equals(const RefPair& o) const;
};

bool RefPair::Equals(const RefPair& o) const
{
    return o.m4 == m4 && o.m8 == m8;
}

// ===========================================================================
// @ 0x0059da80
struct RandomLinearCongruential { double RandomDoubleUniform(); };
extern RandomLinearCongruential sMathRandom;   // 0x1601760
double RandomRange(float range)
{
    double dRange = range;
    double result = sMathRandom.RandomDoubleUniform() * dRange;
    if (result < dRange) {
        if (result > 0.0)
            return result;
        return 0.0;
    }
    return dRange;
}

// ===========================================================================
// @ 0x0059dac0
cSPEditorAnimationManager::cSPEditorAnimationManager() {}

void* g_pForceMgr;
void ForceAnimationManagerCtor() { g_pForceMgr = new cSPEditorAnimationManager(); }

// ===========================================================================
// 0x0059db00: scalar deleting destructor, see cSPEditorAnimationManager::~cSPEditorAnimationManager above

// ===========================================================================
// @ 0x0059d960
cSPEditorAnimatedEventInfo::cSPEditorAnimatedEventInfo()
    : mAnimatedCreatureID(0), mSourceBlock(0), mSourceModel(0), mEvent(kAnimatedEvent0),
      mIsBaby(false), mDelayTime(0.0f), mDoLoop(false), mAnimID(0xffffffff), mAnimSpeed(1.0f)
{
}

// ===========================================================================
// Support types for the three large bodies below (retail layouts).
namespace SP {

// Object stored at CreatureData::mpModelObj (+0x08); the +0x170 field is the
// "current animation sequence" slot written by HandleAnimatedEvent.
struct AnimModelObj {
    virtual void  v0(); virtual void  v1();
    virtual void* v2(unsigned int, int);      // +0x08
    virtual void  v3(void*, int);             // +0x0c
    virtual void  v4(); virtual void  v5();
    virtual void  v6(void*);                  // +0x18
    virtual void  v7();
    virtual void  v8(void*, int);             // +0x20
    virtual void  v9(void*, float);           // +0x24
    virtual void  vA(); virtual void  vB(); virtual void vC(); virtual void vD();
    virtual void  vE(void*, float);           // +0x38
};

// cSPEditorAnimatedCreatureData: the per-creature entry stored in the map.
struct CreatureData {
    char pad0[8];
    AnimModelObj* mpModelObj;                 // +0x08
    char pad0c[0x20 - 0x0c];
    float mTimer;                             // +0x20
    char pad24[0x54 - 0x24];
    int   mField54;                           // +0x54
    char pad58[0x170 - 0x58];
    int   mField170;                          // +0x170
    bool  HasAnyAnimation();                  // 0x0059ae80
    void  SetPlayState(unsigned int);         // 0x0059aca0
    void  SetLastAnimationPlayed(unsigned int); // 0x007cd950
};

// The red-black map living at this+0x08 (its anchor sentinel is this+0x0c).
struct CreatureTree {
    char  pad0[4];
    void* mpAnchor;                           // +0x04
    void** Find(void** outIt, const void* key);   // 0x00e5c780
    void** Index(const void* key);                // 0x0059c740
};

// Output of cSPEditorAnimationManager::GetAnimation.
struct AnimResultOut { unsigned int mID; unsigned int mFourCC; bool mFlag; };

struct RBNode {
    void* mpLeft;   // +0x00
    void* mpParent; // +0x04
    void* mpRight;  // +0x08
    char  mColor;   // +0x0c
    char  pad0d[3];
    void* mpValue;  // +0x10
};

extern bool  IsPlayingAnimationImpl(void* self, unsigned int id);     // 0x0059cd20
extern void  RBTreeIncrement(void* node);                             // 0x00921580
extern void  CopyRange(void* first, void* last, void* dst);           // 0x0062ffd0
extern void  Matrix3FromQuaternion(void* out, const void* quat);      // 0x0059c190
extern void  CreatureDataUpdate(void* c, unsigned int msec);          // 0x0059b4b0
extern float kFOne;       // 0x01485720
extern float kFSlow;      // 0x013f5698
extern float kFNegOne_;   // 0x013eb1bc
extern float kF2Pi;       // 0x0150dff4
extern float kFPi;        // 0x013f64d4
extern float kFMaxDelta;  // 0x013ec480  (0.2f; caps one time step)
extern const double kD2To32;      // 0x013f6050
extern const double kDMilli;      // 0x013f6560
extern float kFMilli;             // 0x013f9428
extern float kF2To32;             // 0x013f4fd0
extern void* GetManagerImpl();                                    // 0x0067dcd0
extern void* PropertyManagerImpl();                               // 0x0067de30
extern void  DoInsertValueImpl(void* end, const void* value);     // 0x004b6000
extern void  FreeAllocImpl(void* p);                              // 0x00f47380
extern unsigned int kResFilterField4;   // 0x00b1b104
extern unsigned int kResFilterGroup;    // 0x0150e79c

}  // namespace SP

// ===========================================================================
// @ 0x0059d300
bool SP::cSPEditorAnimatedCreatureManager::HandleAnimatedEvent(void* e)
{
    unsigned int creatureID = *(unsigned int*)((char*)e + 0x0c);
    CreatureData* cr = 0;

    if (*(void**)((char*)this + 0x38) != 0) {
        CreatureTree* tree = (CreatureTree*)((char*)this + 0x08);
        void* it = 0;
        void** found = tree->Find(&it, &creatureID);
        if (*found != (void*)((char*)this + 0x0c))
            cr = *(CreatureData**)tree->Index(&creatureID);
    }
    if (*(void**)((char*)this + 0x3c) == 0) return false;
    if (cr == 0) return false;
    if (cr->mpModelObj == 0) return false;

    AnimResultOut res;
    res.mID = 0;
    res.mFourCC = 0;
    float speed = SP::kFOne;      // kFOne = 1.0f
    res.mFlag = true;

    unsigned int event = *(unsigned int*)((char*)e + 0x18);
    bool bForced = false;
    switch (event) {
    case 0x0eef6cd0: case 0xb3a731ca: case 0x89d6008b: case 0x8b2f58fe:
    case 0xc1339ba9: case 0xc4b6e6e0: case 0xd0c86c9a: case 0xe646113d:
    case 0xe7782027: case 0xf10ff9fd: case 0xf77c2e23: case 0x06035c10:
    case 0x4f21fc3b: case 0x2949954d: case 0x22b31636: case 0x167d2885:
    case 0x43773b7b: case 0x6820bfd9: case 0x5c4d694c: case 0x622c20c4:
    case 0x70842ef6: case 0x7f034f46:
        speed = SP::kFSlow;
        // fall through: these events also force the animation
    case 0xe12a2ae7: case 0xbd989484: case 0xbac2d74f: case 0xed65cbf6:
    case 0xe5025cd9: case 0x1d9547b2: case 0x248dca26: case 0x3088ceca:
    case 0x3bd9a6f8: case 0x6581b78e: case 0x6df196fd:
        bForced = true;
        break;
    default:
        break;
    }

    bool hasAnim = cr->HasAnyAnimation();
    if (!hasAnim && !bForced) {
        if (IsPlayingAnimation(creatureID)) return false;
    }

    cSPEditorAnimationManager* mgr =
        *(cSPEditorAnimationManager**)((char*)this + 0x3c);
    bool got = mgr->GetAnimation((SP::AnimRequest*)e, (SP::AnimResult*)&res, (SP::AnimContext*)cr);

    bool force =
        (*(unsigned int*)((char*)e + 0x18) == 0x04878ee8) &&
        (*(unsigned int*)((char*)e + 0x28) != 0xffffffff);

    unsigned int animID;
    bool bPlay;
    if (!got) {
        if (!force) return false;
        animID = *(unsigned int*)((char*)e + 0x28);
        bPlay = true;
    } else {
        animID = res.mID;
        bPlay = res.mFlag;
    }

    cr->SetLastAnimationPlayed(animID);
    cr->SetPlayState(bPlay ? 1u : 0u);

    AnimModelObj* obj = cr->mpModelObj;
    cr->mField170 = (int)res.mFourCC;

    void* h = obj->v2(animID, 0);
    obj->v3(h, 1);
    obj->v6(h);
    obj->vE(h, speed);
    if (*(unsigned char*)((char*)e + 0x24) != 0) {
        obj->v8(h, 1);
        obj->v9(h, SP::kFNegOne_);
    }
    return h != 0;
}

// @ 0x0059d610
void SP::cSPEditorAnimatedCreatureManager::Update(unsigned int msec)
{
    // Two independent msec->seconds conversions (float and double) as emitted.
    float step = (float)msec * SP::kFMilli;
    float dt   = (float)((double)msec * SP::kDMilli);
    if (dt > SP::kFMaxDelta) dt = SP::kFMaxDelta;

    if (*(void**)((char*)this + 0x38) == 0) return;

    // --- Phase 1: advance each creature timer; fire + erase when it expires.
    CreatureData** it  = *(CreatureData***)((char*)this + 0x24);
    CreatureData** end = *(CreatureData***)((char*)this + 0x28);
    while (it != end) {
        CreatureData* c = *it;
        float t = c->mTimer - step;
        c->mTimer = t;
        if (t <= 0.0f) {
            c->mTimer = 0.0f;
            HandleAnimatedEvent(c);
            if (it + 1 < end) SP::CopyRange(it + 1, end, it);
            end = (CreatureData**)((char*)end - 4);
            *(CreatureData***)((char*)this + 0x28) = end;
            CreatureData* last = *end;
            if (last != 0) {
                // AutoRefCount<CreatureData>::Release (virtual slot 0x08).
                (*(int(__thiscall**)(void*))((*(char**)last) + 0x08))(last);
            }
        } else {
            ++it;
        }
    }

    // --- Phase 2: step each live creature's inner animation.
    for (SP::RBNode* n = *(SP::RBNode**)((char*)this + 0x10);
         n != (SP::RBNode*)((char*)this + 0x0c);
         SP::RBTreeIncrement(n)) {
        if (n->mpValue == 0) continue;
        CreatureData* c = (CreatureData*)n->mpValue;
        if (c->mpModelObj == 0) continue;
        c->mField54 = 2;
        SP::CreatureDataUpdate(c, msec);
    }

    // --- Phase 3: push the time step into the animation manager.
    {
        void* mgr = *(void**)((char*)this + 0x38);
        (*(void(__thiscall**)(void*, float, int))((*(char**)mgr) + 0x24))(mgr, dt, 0);
    }

    // --- Phase 4: recompute each creature's yaw from its transform.
    for (SP::RBNode* n = *(SP::RBNode**)((char*)this + 0x10);
         n != (SP::RBNode*)((char*)this + 0x0c);
         SP::RBTreeIncrement(n)) {
        if (n->mpValue == 0) continue;
        CreatureData* c = (CreatureData*)n->mpValue;
        if (c->mpModelObj == 0) continue;
        char* x = (char*)c->mpModelObj;
        if (*(void**)(x + 0x08) == 0) continue;

        char* dst = (char*)c;
        *(unsigned int*)(dst + 0x38) = *(unsigned int*)(x + 0x04);
        *(unsigned int*)(dst + 0x3c) = *(unsigned int*)(x + 0x08);
        *(unsigned int*)(dst + 0x40) = *(unsigned int*)(x + 0x0c);

        float m[3];
        SP::Matrix3FromQuaternion(m, x + 0x10);
        float yaw = *(float*)(dst + 0x48);
        float ang = (float)atan2((double)m[0], (double)yaw);
        ang = (float)fmod((double)ang, (double)SP::kF2Pi);
        if (ang >= SP::kFPi) ang -= SP::kF2Pi;
        ang = (float)fmod((double)(ang), (double)SP::kF2Pi);
        if (ang >= SP::kFPi) ang -= SP::kF2Pi;
        *(float*)(dst + 0x48) = ang + yaw;
    }
}

// @ 0x0059db40
void cSPEditorAnimationManager::Init()
{
    void* rm = GetManagerImpl();

    // Output vector of ResourceKeys (12 bytes each) filled by the manager.
    void* outBegin = 0;
    void* outEnd = 0;
    void* outCap = 0;

    // Resource-list filter argument (vptr + two fields).
    struct ResFilter {
        void* mpVtbl;
        unsigned int m4;
        unsigned int m8;
    } filter;
    filter.m8 = SP::kResFilterGroup;
    filter.m4 = SP::kResFilterField4;
    filter.mpVtbl = (void*)&outBegin;   // placeholder; see note below

    // rm->v38(res&, filter&, 0) -- fill outBegin/outEnd.
    typedef void (__thiscall *V38)(void*, void**, void*, int);
    ((V38)(*(void***)rm)[0x38 / 4])(rm, &outBegin, &filter, 0);

    int count = (int)((char*)outEnd - (char*)outBegin) / 0x0c;
    for (int i = 0; i < count; ++i) {
        char* elem = (char*)outBegin + i * 0x0c;
        unsigned int key0 = *(unsigned int*)(elem + 0x00);
        unsigned int key2 = *(unsigned int*)(elem + 0x08);

        void* temp = 0;
        void* pm = PropertyManagerImpl();
        typedef char (__thiscall *V2C)(void*, unsigned int, unsigned int, void**);
        char ok = ((V2C)(*(void***)pm)[0x2c / 4])(pm, key0, key2, &temp);
        if (ok != 0) {
            // mAnimations.push_back(AutoRefCount(temp))
            void** pend = (void**)((char*)this + 0x10);
            if (*pend < *(void**)((char*)this + 0x14)) {
                void** slot = (void**)*pend;
                *(void**)((char*)this + 0x10) =
                    (void*)((char*)slot + 4);
                if (slot != 0) {
                    *slot = temp;
                    if (temp != 0) {
                        (*(int(__thiscall**)(void*))(*(char**)temp))(temp);
                    }
                }
            } else {
                DoInsertValueImpl(*pend, &temp);
            }
        }
        if (temp != 0) {
            (*(int(__thiscall**)(void*))((*(char**)temp) + 0x04))(temp);
        }
    }

    // ~SpVector: free the allocation if it owns one.
    if (outBegin != 0 && *((void**)outBegin - 1) != 0) {
        FreeAllocImpl(outBegin);
    }
}

// ---------------------------------------------------------------------------
// GetAnimation support types (retail layouts, checked against the asm).
namespace SP {
class cPropertyList;
struct Key { uint32_t instance, type, group; };       // ResourceKey, 12 bytes
bool __cdecl KeyMatches(const Key* a, const Key* b);   // 0x004a9a90 (0 in b = wildcard)
bool GetPropertyAsKeyArray(cPropertyList* list, uint32_t id, int* count, Key** keys);   // 0x006a0ae0
bool GetPropertyAsChar8Ptr(cPropertyList* list, uint32_t id, const char** value);       // 0x006a1450
void __cdecl EASTL_allocator_deallocate(void* p);                                        // 0x00f47380
extern const uint32_t kDefaultUIntValue;   // 0x015d1164
extern const bool kDefaultBoolValue;       // 0x015d115d

struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12
    int GetItemCount()
    {
        if (mnFlags & 0x30) return mnItemCount;
        else if (mnType != 0) return 1;
        return 0;
    }
    void* GetItems()
    {
        if (mnFlags & 0x30) return mpData;
        else if (mnType != 0) return this;
        return 0;
    }
    void* GetValuePtr()
    {
        if (mnFlags & 0x30) return mpData;
        return (void*)((-(int)(uint32_t)mnType >> 31) & (int)this);
    }
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
    virtual Property* GetPropertyObject(uint32_t id);            // +0x28
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
};

template <class T> struct SpVector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p) p->~T();
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
    }
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) new (mpEnd) T(v); ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
template <> struct SpVector<float> {
    float* mpBegin; float* mpEnd; float* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin); }
    void DoInsertValue(float* pos, const float& v);   // 0x00455660
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
template <> struct SpVector<char> {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin); }
    void DoInsertValue(char* pos, const char& v);   // 0x00426730
    void push_back(const char& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};

struct Entity {                      // editor block
    bool HasAnyBlockFlag();          // 0x00435d40
    Key* GetKey(Key* out);           // 0x00440b90 (copies 12 bytes at +0x5f8)
    char pad0[0x28];
    struct EditorModel* mpModel;     // +0x28 (when used via the request's block)
};
struct EditorModel {
    int GetBlockCount();             // 0x004accf0
    Entity* GetBlock(uint32_t i);    // 0x004accb0
};
struct AnimRequest {
    char pad0[0x10];
    Entity* mpBlock;                 // +0x10
    EditorModel* mpModel;            // +0x14
    uint32_t mAnimID;                // +0x18
    char pad1c[0x28 - 0x1c];
    uint32_t mForcedAnim;            // +0x28
};
struct AnimResult {
    uint32_t mID;                    // +0
    uint32_t mFourCC;                // +4
    bool mFlag;                      // +8
};
struct AnimContext {
    char pad0[0x1c];
    uint32_t mKey;                   // +0x1c
    bool Matches(uint32_t v);        // 0x0059ac90
};
struct AppPropsInner { char pad[0xdc]; int mFlag; };
struct AppProps { char pad[0x3c]; AppPropsInner* mpInner; };
extern AppProps* gAppProps;          // 0x015fd918

typedef SpVector<AutoRefCount<cPropertyList> > AnimListVec;
struct AnimMgrView { char pad[0xc]; AnimListVec mAnimations; };   // +0xc

static const uint32_t kForcedAnimID = 0x248dca26;
}  // namespace SP

// @ 0x0059dc70
bool SP::cSPEditorAnimationManager::GetAnimation(AnimRequest* req, AnimResult* out, AnimContext* ctx)
{
    AnimListVec& anims = ((AnimMgrView*)this)->mAnimations;

    if ((anims.mpBegin != anims.mpEnd || req->mAnimID == kForcedAnimID) && gAppProps->mpInner->mFlag != 0) {
        if (req->mAnimID == kForcedAnimID) {
            if (req->mForcedAnim != 0) {
                out->mID = req->mForcedAnim;
                out->mFlag = true;
                return true;
            }
        }
        else {
            AnimListVec matches;
            SpVector<float> weights;
            int numAnims = anims.mpEnd - anims.mpBegin;
            for (int i = 0; i < numAnims; i++) {
                AutoRefCount<cPropertyList> list(anims.mpBegin[i]);
                if (!list->HasProperty(0xf150ffb0)) continue;
                Property* prop = list->GetPropertyObject(0xf150ffb0);
                int numIDs = prop->GetItemCount();
                Key* ids = (Key*)prop->GetItems();
                int k = 0;
                for (; k < numIDs; k++) {
                    if (ids[k].instance == req->mAnimID) break;
                }
                if (k >= numIDs) continue;

                bool bAllRequired = true;
                int numReq; Key* reqKeys;
                if (GetPropertyAsKeyArray(list.mpObject, 0xff50f753, &numReq, &reqKeys) && numReq > 0) {
                    bAllRequired = false;
                    SpVector<char> found;
                    for (int j = 0; j < numReq; j++) {
                        char zero = 0;
                        found.push_back(zero);
                    }
                    EditorModel* model = req->mpModel;
                    if (!model && req->mpBlock) model = req->mpBlock->mpModel;
                    if (model) {
                        int numBlocks = model->GetBlockCount();
                        for (int b = 0; b < numBlocks; b++) {
                            Entity* blk = model->GetBlock(b);
                            if (blk->HasAnyBlockFlag()) {
                                Key bk;
                                blk->GetKey(&bk);
                                for (int j = 0; j < numReq; j++) {
                                    if (KeyMatches(&bk, &reqKeys[j])) found.mpBegin[j] = 1;
                                }
                            }
                        }
                        bAllRequired = true;
                        for (int j = 0; j < numReq; j++) {
                            if (!found.mpBegin[j]) { bAllRequired = false; break; }
                        }
                    }
                }

                bool bAnyAllowed = true;
                int numAllow; Key* allowKeys;
                if (GetPropertyAsKeyArray(list.mpObject, 0xe99ed6ff, &numAllow, &allowKeys) && numAllow > 0 && req->mpBlock) {
                    bAnyAllowed = false;
                    for (int j = 0; j < numAllow; j++) {
                        Key bk;
                        if (KeyMatches(req->mpBlock->GetKey(&bk), &allowKeys[j])) { bAnyAllowed = true; break; }
                    }
                }

                if (bAllRequired && bAnyAllowed) {
                    matches.push_back(list);
                    float weight = 1.0f;
                    Property* wp;
                    if (list.mpObject && list->GetProperty(0x029eb123, wp) && wp->mnType == 10) {
                        const uint32_t* pv = (const uint32_t*)wp->GetValuePtr();
                        if (ctx->Matches(*pv)) weight = 0.0f;
                    }
                    weights.push_back(weight);
                }
            }

            if (matches.mpBegin != matches.mpEnd) {
                int numWeights = weights.mpEnd - weights.mpBegin;
                float total = 0.0f;
                for (int i = 0; i < numWeights; i++) total = weights.mpBegin[i] + total;
                if (total == 0.0f && numWeights > 0) {
                    for (int i = 0; i < numWeights; i++) weights.mpBegin[i] = 1.0f;
                    for (int i = 0; i < numWeights; i++) total += 1.0f;
                }
                float r = (float)RandomRange(total);
                float acc = 0.0f;
                int idx = 0;
                for (int i = 0; i < numWeights; i++) {
                    acc = weights.mpBegin[i] + acc;
                    idx = i;
                    if (acc > r) break;
                }
                if (idx >= (int)(matches.mpEnd - matches.mpBegin) || idx < 0) idx = 0;

                AutoRefCount<cPropertyList> chosen(matches.mpBegin[idx]);
                if (chosen->HasProperty(0x029eb123)) {
                    Property* p = chosen->GetPropertyObject(0x029eb123);
                    uint16_t t = p->mnType;
                    const uint32_t* idp = (t == 10 || t == 0x10) ? (const uint32_t*)p->GetValuePtr() : &kDefaultUIntValue;
                    out->mID = *idp;
                    const char* name;
                    if (GetPropertyAsChar8Ptr(chosen.mpObject, 0xf711981f, &name)) {
                        char buf[4] = { 0, 0, 0, 0 };
                        strncpy(buf, name, 4);
                        out->mFourCC = ((((uint32_t)(uint8_t)buf[3] << 8 | (uint8_t)buf[2]) << 8 | (uint8_t)buf[1]) << 8) | (uint8_t)buf[0];
                    }
                    if (chosen->HasProperty(0x654234db)) {
                        Property* q = chosen->GetPropertyObject(0x654234db);
                        uint16_t qt = q->mnType;
                        const bool* bp = (qt == 1 || qt == 0x10) ? (const bool*)q->GetValuePtr() : &kDefaultBoolValue;
                        out->mFlag = *bp;
                    }
                    return true;
                }
            }
        }
    }
    out->mID = 0;
    return false;
}
