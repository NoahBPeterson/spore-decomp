// src/game/SPGonzago/SPGameTimeManager.cpp -- migrated from slice(s) s00b318d0, s00ddf990, s00642530 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameTimeManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPVector3.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cVarListSerializer.h"
#include <xmmintrin.h>
#include <intrin.h>
#include <new>

// ---- items of slice s00642530 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RBNode { RBNode* right; RBNode* left; RBNode* parent; uint32_t color; };
struct Tag {};
struct Iter { RBNode* n; Iter() {} Iter(const Iter& o) : n(o.n) {} };
struct UUNode : RBNode { uint32_t key; uint32_t val; };
struct MapUU { uint32_t first; RBNode anchor; uint32_t size; uint32_t alloc;
    Iter DoInsertValueHint(Iter hint, const uint32_t* kv, Tag);
    uint32_t* operator_idx(const uint32_t* k);
};
// ---- items of slice s00642530 end

// ---- items of slice s00ddf990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gInterfaceValue;
extern float gInterfaceBlend;
extern float gInterfaceAngle;
extern float gInterfaceSpeed;
#define nullptr 0
struct cMethodTable {
    void* mSlots[0x40];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, uint32_t nArg2) {
        return ((void* (*)(void*, uint32_t, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1, nArg2);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (__thiscall*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, void* pArg1, int nArg2) {
        return ((void* (*)(void*, void*, int))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
};
class cInterfaceState {
public:
    cInterfaceState(cDispatchObject* pTarget);
    ~cInterfaceState();
    bool ResetDefaults();
    void PushMatrix(const cSPVector3* pVec);
    void UpdateTransition(unsigned int nElapsed, uint32_t nFlags);
    void UpdateFade(float fDelta);
    void UpdateSequence(int nDelta);
    void UpdateAlpha(int nDelta);
    void BeginSequence(uint8_t bFirst, uint8_t bSecond);
    void ResetSequence();
    void NotifySequence();
    bool IsIdle();

    uint32_t mpVftable;                         // 0x00
    int mnTimer;                                // 0x04
    uint8_t mPad08[0x18];                       // 0x08
    float mfValue20;                            // 0x20
    float mfValue24;                            // 0x24
    float mfValue28;                            // 0x28
    float mfValue2c;                            // 0x2c
    float mfValue30;                            // 0x30
    float mfTolerance;                          // 0x34
    float mfStart38;                            // 0x38
    float mfStart3c;                            // 0x3c
    uint8_t mbFlag40;                           // 0x40
    uint8_t mPad41[0x03];                       // 0x41
    float mfTo44;                               // 0x44
    float mfTo48;                               // 0x48
    float mfTo4c;                               // 0x4c
    float mfFrom50;                             // 0x50
    float mfFrom54;                             // 0x54
};
struct cInterfaceDefaults {
    float mfUnknown00;                          // 0x00
    float mfUnknown04;                          // 0x04
    float mfX;                                  // 0x08
    float mfY;                                  // 0x0c
    float mfZ;                                  // 0x10
};
extern cDispatchObject* gInterfaceNotifier;
extern cInterfaceDefaults gInterfaceFrom;
extern uint8_t gInterfaceStarted;

// The camera controller object (0x015a30b8) and the identity transform it is reset from.
// Its Init is defined here (as it was in the retail translation unit): the caller's code keeps the
// object address in ecx across the call, which cl only does when it can see the callee's body.
struct cCameraCtl {
    int32_t mPad00;                                              // 0x00
    int32_t m04;                                                 // 0x04
    int32_t m08;                                                 // 0x08
    float   m0c;                                                 // 0x0c
    rw::math::fpu::Vector3Template<float, 0> m10;                // 0x10
    float   m1c;                                                 // 0x1c
    float   m20;                                                 // 0x20
    float   m24;                                                 // 0x24
    float   m28;                                                 // 0x28
    float   m2c;                                                 // 0x2c
    float   m30;                                                 // 0x30
    rw::math::fpu::Vector3Template<float, 0> m34;                // 0x34
    rw::math::fpu::Vector3Template<float, 0> m40;                // 0x40
    rw::math::fpu::Vector3Template<float, 0> m4c;                // 0x4c
    void init(void* pArg, const rw::math::fpu::Vector3Template<float, 0>* pVec);
};
extern cCameraCtl gCameraCtl;                                        // 0x015a30b8
extern rw::math::fpu::Vector3Template<float, 0> gZeroTranslation;    // 0x016a10cc
extern rw::math::fpu::Matrix33Template<float, 0> gIdentityRotation;  // 0x016a10e0
extern float gCamStep30;                                             // 0x015a308c
extern float gCamStep1c;                                             // 0x015a3090
extern float gCamValue24;                                            // 0x015a3094
extern rw::math::fpu::Vector3Template<float, 0> gCamTranslation;     // 0x015a3048

// ---- items of slice s00b318d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned int u32;
#define VT(p) (*(void***)(p))
#define VFN(p, off, T) ((T)(VT(p)[(off) / 4]))
void  __cdecl operator_delete__(void* p);                    // 00f47380
struct Stopwatch {
    unsigned __int64 mnStartTime;          // 0167e908
    unsigned __int64 mnTotalElapsedTime;   // 0167e910
    int   mnUnits;                         // 0167e918
    float mfCoeff;                         // 0167e91c
    __int64 GetElapsedTimeFloat();         // 0093a3a0
    void SetUnits(int units);              // 0093a1a0
    void Stop();                           // 0093a2e0
    __forceinline void StartIfStopped()
    {
        if (mnStartTime == 0) {
            if (mnUnits == 1) {
                unsigned __int64 t = __rdtsc();
                ((u32*)&mnStartTime)[1] = (u32)(t >> 32);
                ((u32*)&mnStartTime)[0] = (u32)t;
            } else {
                __int64 t;
                QueryPerformanceCounter(&t);
                mnStartTime = t;
            }
        }
    }
    __forceinline void RestartIfRunning()
    {
        if (mnStartTime != 0) {
            if (mnUnits == 1) {
                mnStartTime = __rdtsc();
                mnTotalElapsedTime = 0;
                return;
            }
            __int64 counter;
            QueryPerformanceCounter(&counter);
            mnStartTime = (unsigned __int64)counter;
            mnTotalElapsedTime = 0;
            return;
        }
        mnStartTime = 0;
        mnTotalElapsedTime = 0;
    }
    __forceinline void Restart()
    {
        if (mnUnits == 1) {
            unsigned __int64 t = __rdtsc();
            ((u32*)&mnStartTime)[1] = (u32)(t >> 32);
            ((u32*)&mnStartTime)[0] = (u32)t;
        } else {
            __int64 t;
            QueryPerformanceCounter(&t);
            mnStartTime = t;
        }
        mnTotalElapsedTime = 0;
    }
};
extern Stopwatch sBaseTimer;                                  // 0167e908
struct cGonzagoSubsystemBase {
    virtual int  AddRef();                  // 0x00c6a960
    virtual int  Release();                 // 0x007b86e0
    virtual void s02();                     // 0x00b31bc0
    virtual void s03();                     // 0x00c2e4e0
    virtual void s04();                     // 0x00b31f30
    virtual void s05();                     // 0x00b5b930
    virtual void s06();                     // 0x00b5b900
    virtual void s07();                     // 0x00fc7e50
    virtual void s08();                     // 0x007f54d0
    virtual void s09();                     // 0x00b5b840
    virtual void s10();                     // 0x00b31ae0
    virtual void s11();                     // 0x00b31740
    virtual void s12();                     // 0x010829f0
    virtual void s13();                     // 0x00b31f40
    virtual void s14();                     // 0x00b267f0
    virtual void s15();                     // 0x00b267f0
    virtual void s16();                     // 0x00b5b880
    virtual void s17();                     // 0x00b5b8a0
    virtual void s18();                     // 0x00b5b8c0
    virtual void s19();                     // 0x00b5b8e0
};
struct cRefCountBase { virtual ~cRefCountBase(); int mnRefCount; };
struct cGonzagoSubsystem : cGonzagoSubsystemBase, cRefCountBase {
    int mPre, mPost, mCurTrans, mPhase;
    cGonzagoSubsystem();                    // 00b5b960
    ~cGonzagoSubsystem();                   // 00b5b9a0
};
struct MessageServer { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
                       virtual void Post(unsigned msgId, int data, int flag); };
MessageServer* __cdecl GetMessageServer();                    // 00883860
struct AppSystemObj;
AppSystemObj* __cdecl SP_AppSystem();                         // 0067dd00
struct MapNode { MapNode* right; MapNode* left; MapNode* parent; char color; unsigned key; unsigned val; };
struct MapIter { MapNode* mpNode; MapIter(const MapIter& o) : mpNode(o.mpNode) {} };
struct PauseMap {
    int       mpad4c;
    MapNode*  mRight;
    MapNode*  mLeft;
    MapNode*  mParent;
    union { char mColor; int mColorDw; };
    int       mnSize;
    int       mpad64;
    PauseMap() : mLeft(0), mParent(0), mColorDw(0) { mRight = (MapNode*)&mRight; mLeft = (MapNode*)&mRight; mParent = 0; mColor = 0; mnSize = 0; }
    ~PauseMap() { DoNuke(mParent); }
    MapIter   find(const unsigned& key);                // 00e5c780
    unsigned& operator[](const unsigned& key);          // 00643a40
    void      DoNuke(MapNode* n);                       // 009a9600
    MapNode*  anchor() { return (MapNode*)&mRight; }
};
struct tPauseGate {
    int      count;
    unsigned bits;
};
struct PauseGateVec {
    tPauseGate* mpBegin; tPauseGate* mpEnd; tPauseGate* mpCap;
    PauseGateVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~PauseGateVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    unsigned size() const { return mpEnd - mpBegin; }
    tPauseGate& operator[](unsigned n) { return mpBegin[n]; }
    void Realloc(tPauseGate* at, const unsigned* v);     // 00b534c0
    void push_back_zero()
    {
        if (mpEnd < mpCap) {
            tPauseGate* p = mpEnd++;
            if (p) p->bits = 0;
        } else {
            unsigned z = 0;
            Realloc(mpEnd, &z);
        }
    }
};
struct cGameTimeManager : cGonzagoSubsystem {
    float             mTimeFlowRates[4];                    // +0x1c
    unsigned __int64  mBaseTimeElapsed;                     // +0x30
    unsigned __int64  mTimeAtStartOfFrame;                  // +0x38
    float             mTimeFlowRate;                        // +0x40
    int               mTimeFlowSetting;                     // +0x44
    unsigned          mCachedPauseState;                    // +0x48
    PauseMap          mPauseGateIndexMap;                   // +0x4c
    PauseGateVec      mPauseGates;                          // +0x68

    cGameTimeManager();
    virtual ~cGameTimeManager() {}
    void   UpdateTimeAtStartOfFrame();
    void   Serialize(void* stream);
    unsigned CeilScaledTime(unsigned v);
    void   UpdatePauseState();
    int    GetPauseGateCount(unsigned id);
    void   ClearPauseGates();
    void   RegisterPauseGate(unsigned id, unsigned bits, const char* name);
    int    IncPauseGate(unsigned id);
    int    DecPauseGate(unsigned id);
    bool   TogglePauseGate(unsigned id);
    void   SetTimeFlowRate(float rate);
    void   RegisterDefaultPauseGates();
    void   SetTimeFlowSetting(int idx);
};
// ---- items of slice s00b318d0 end

// @ 0x00643a40
uint32_t* MapUU::operator_idx(const uint32_t* k)
{
    RBNode* pNode = anchor.parent;
    RBNode* pEnd = &anchor;
    while (pNode) {
        if (!(((UUNode*)pNode)->key < *k)) { pEnd = pNode; pNode = pNode->left; }
        else pNode = pNode->right;
    }
    if (pEnd == &anchor || *k < ((UUNode*)pEnd)->key) {
        uint32_t kv[2];
        kv[0] = *k; kv[1] = 0;
        Iter hi; hi.n = pEnd;
        Iter it = DoInsertValueHint(hi, kv, Tag());
        pEnd = it.n;
    }
    return &((UUNode*)pEnd)->val;
}

// @ 0x00b31fa0
void cGameTimeManager::UpdatePauseState()
{
    unsigned old = mCachedPauseState;
    mCachedPauseState = 0;
    tPauseGate* g = mPauseGates.mpBegin;
    tPauseGate* e = mPauseGates.mpEnd;
    for (; g != e; ++g) {
        if (g->count > 0) {
            mCachedPauseState = g->bits;
            break;
        }
    }
    bool nb0 = (mCachedPauseState & 1) != 0;
    if (nb0 != ((old & 1) != 0)) {
        if (nb0)
            sBaseTimer.Stop();
        else
            sBaseTimer.StartIfStopped();
        MessageServer* srv = GetMessageServer();
        if (srv)
            srv->Post(0x03867294, nb0 ? 1 : 0, 0);
    }
    bool nb2 = ((mCachedPauseState >> 2) & 1) != 0;
    if (nb2 != (((old >> 2) & 1) != 0)) {
        MessageServer* srv = GetMessageServer();
        if (srv)
            srv->Post(0x0546bbb8, nb2 ? 1 : 0, 0);
    }
    bool nb1 = ((mCachedPauseState >> 1) & 1) != 0;
    if (nb1 != (((old >> 1) & 1) != 0)) {
        AppSystemObj* app = SP_AppSystem();
        if (nb1)
            VFN(app, 0x2c, void(__thiscall*)(void*))(app);
        else
            VFN(app, 0x30, void(__thiscall*)(void*))(app);
    }
}

// @ 0x00b32110
void cGameTimeManager::ClearPauseGates()
{
    tPauseGate* g = mPauseGates.mpBegin;
    tPauseGate* e = mPauseGates.mpEnd;
    for (; g != e; ++g)
        g->count = 0;
    UpdatePauseState();
}

// @ 0x00b32140
void ForceGTMDtor(cGameTimeManager* p)
{ delete p; }

// @ 0x00b32190
void cGameTimeManager::RegisterPauseGate(unsigned id, unsigned bits, const char* name)
{
    (void)name;
    if (mPauseGateIndexMap.find(id).mpNode == mPauseGateIndexMap.anchor()) {
        unsigned idx = mPauseGates.size();
        mPauseGates.push_back_zero();
        tPauseGate* g = mPauseGates.mpEnd - 1;
        g->count = 0;
        g->bits = bits;
        mPauseGateIndexMap[id] = idx;
    }
}

// @ 0x00b32220
int cGameTimeManager::IncPauseGate(unsigned id)
{
    tPauseGate* g = &mPauseGates[mPauseGateIndexMap[id]];
    g->count++;
    UpdatePauseState();
    return g->count;
}

// @ 0x00dde2b0
void cCameraCtl::init(void* pArg, const rw::math::fpu::Vector3Template<float, 0>* pVec)
{
    m30 = gCamStep30;
    m1c = gCamStep1c;
    m10 = *pVec;
    m24 = gCamValue24;
    m2c = 100.0f;
    m40 = *pVec;
    m34 = gCamTranslation;
    m4c = m34;
    m04 = 0;
    m08 = 500;
    *(int32_t*)&m0c = 0;
    (void)pArg;
}

// The 0x38-byte transform handed to the notifier: RenderWare's cTransform layout.  Its rotation
// assignment is out of line (Matrix3::Assign, 0x0041cb40), so the type declares it without a body.
struct cXformMatrix : public rw::math::fpu::Matrix33Template<float, 0> {
    cXformMatrix& operator=(const rw::math::fpu::Matrix33Template<float, 0>&);
};
struct cXform {
    uint16_t mFlags;                                             // 0x00
    uint16_t mModificationCount;                                 // 0x02
    rw::math::fpu::Vector3Template<float, 0> mTranslation;       // 0x04
    float mScale;                                                // 0x10
    cXformMatrix mRotation;                                      // 0x14
};
typedef char sizeof_check_cXform[(sizeof(cXform) == 0x38) ? 1 : -1];
// ---- items of slice s00ddf990 end

// @ 0x00ddfb50
void cInterfaceState::PushMatrix(const cSPVector3* pVec)
{
    cXform xform;
    xform.mFlags = 0;
    xform.mModificationCount = 0;
    xform.mTranslation.x = gZeroTranslation.x;
    xform.mTranslation.y = gZeroTranslation.y;
    xform.mTranslation.z = gZeroTranslation.z;
    xform.mScale = 1.0f;
    xform.mRotation = gIdentityRotation;

    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04, (void*)&xform);

    gCameraCtl.init(&xform.mTranslation, pVec);
    gInterfaceNotifier = (cDispatchObject*)&gCameraCtl;
}
