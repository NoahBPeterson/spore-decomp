// slice s00a92d90 (batch gold7, worker 9)
//   0x00a92d90  EA::Swarm::cDistributeEffect::UpdateSamples(int)
//   0x00a934e0  EA::Swarm::cDistributeEffect::ApplyEffect(void*,float,void*)
//   0x00a938d0  EA::Swarm::RegisterMeshStreamers2(bool)
//   0x00a93910  EA::Swarm::cMetaParticlesEffect::~cMetaParticlesEffect()
//   0x00a93980  EA::Swarm::cMetaParticlesEffect::cMetaParticlesEffect()
//   0x00a93c60  sample range Erase (two Vector3s, guard on the first x)
// These VAs are the Swarm/DistributeEffect.obj translation unit; the migrated source
// is src/game/Swarm/DistributeEffect.cpp, so only the pieces the six functions touch
// are repeated here (field names follow the retail layout recovered at 0xa934e0).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef uint32_t u32;
typedef uint8_t  u8;
typedef uint16_t u16;

struct Vector3 { float x, y, z; };

// ---- small value types ----------------------------------------------------------
// eastl::sp_vector_allocator-backed buffer: only begin/end/capacity are used by the
// two functions in this slice (the allocator pair sits behind mpCapacity).
template <class T> struct SpVec { T* mpBegin; T* mpEnd; T* mpCapacity; u32 mAlloc[2]; };
// eastl::vector<EA::Swarm::cDistributeSample, sp_vector_allocator> (retail 0x14 bytes)
struct cDistributeSample;
struct SampleVector {
    cDistributeSample* mpBegin;
    cDistributeSample* mpEnd;
    cDistributeSample* mpCapacity;
    u32 mAlloc[2];
    void swap(SampleVector& other);                       // 0x00a8cf50
    void Free();                                          // 0x00a8cfe0
};
struct FloatVec  { float*    mpBegin; float*    mpEnd; float*    mpCapacity; u32 mAlloc[2]; };
struct Vec3Vec   { Vector3*  mpBegin; Vector3*  mpEnd; Vector3*  mpCapacity; u32 mAlloc[2]; };
struct RawVec    { void*     mpBegin; void*     mpEnd; void*     mpCapacity; };

struct Transform38 { float m[0x38 / 4]; };            // 0x38 aligned transform block

struct cDistributeDescription;                        // [EA/Swarm/cDistributeDescription]
struct cEffectParams;                                 // [EA/Swarm/cEffectParams]
struct cIEffectsWorld;                                // [EA/Swarm/cIEffectsWorld]
struct cIVisualEffect;                                // [EA/Swarm/cIVisualEffect]
struct cSurfaceRec;                                   // [EA/Swarm/cSurfaceRec]
struct cBounds {                                      // 0x18 axis-aligned sample bounds
    float mMinX, mMinY, mMinZ, mMaxX, mMaxY, mMaxZ;
    void Init();                                      // 0x006e9530
};

struct MatchRec { int mField[6]; };                   // 0x18 per-sample effect record
typedef char assert_MatchRec[sizeof(MatchRec) == 0x18 ? 1 : -1];

struct cDistributeSample {                            // 0x4c stride in mSamples
    char    pad00[4];
    Vector3 mPosition;                                // +0x04
    float   mScale;                                   // +0x10
    char    pad14[0x38 - 0x14];
    Vector3 mVec38;                                   // +0x38
    float   mScale44;                                 // +0x44
    char    pad48[0x4c - 0x48];
};
typedef char assert_Sample[sizeof(cDistributeSample) == 0x4c ? 1 : -1];

// stats block handed to ApplyEffect (3rd argument).
struct cDistributeEffectStats {
    int mField00, mField04, mField08, mField0c;
    int mField10, mField14, mField18, mField1c;
    char pad20[0x34 - 0x20];
    int mFirst_34;                                    // +0x34
    int mFirst_38;                                    // +0x38
};
typedef char assert_Stats[sizeof(cDistributeEffectStats) >= 0x3c ? 1 : -1];

// ---- cDistributeDescription -----------------------------------------------------
struct cDistributeDescription {
    int      mField00;                                // +0x00
    int      mField04;                                // +0x04
    u32      mFlags;                                  // +0x08
    int      mField0c;                                // +0x0c
    int      mField10;                                // +0x10
    u8       mField14;                                // +0x14
    u8       pad15[3];
    int      mField18;                                // +0x18
    u8       mField1c;                                // +0x1c
    u8       pad1d[3];
    char     pad20[0x15c - 0x20];
    void*    mpEffectData15c;                         // +0x15c
    int      mField160;                               // +0x160
};

// ---- cIVisualEffect / child effects ---------------------------------------------
struct cIVisualEffect {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08(int);
    virtual void  v0c(int);
    virtual bool  v10();
    virtual bool  v14(void* param, float time, void* stats);
    virtual void  v18(void* sample, void* transform);
    virtual void  v1c(int param, void* data, int count);
    virtual void  v20(int param, void* data, int count);
    virtual void  v24(int param, void* data);
    virtual void  v28(int);
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void  v38();
    bool IsReady();                                   // 0x00a88350, direct call
};

struct cEffectWorldObj {                              // object returned by cIEffectsWorld::v20()
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void SetBounds(int setID, cBounds* bounds, float scale);
    virtual void SetBoundsEx(int setID, int flag);
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(int setID, Vector3* v, float scale);
    virtual void v38(int setID, int flag);
};

struct cIEffectsWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual cEffectWorldObj* v20();
};

struct cSurfaceRec {                                  // 0x18 element kept in mSurfaceRecs
    void* mpObject;                                   // +0x00  object with a vtable
    int   mField04;                                   // +0x04
    int   mField08;                                   // +0x08
    int   mStateDataOffset;                           // +0x0c
    void* mpData;                                     // +0x10
    int   mField14;                                   // +0x14
};
typedef char assert_SurfaceRec[sizeof(cSurfaceRec) == 0x18 ? 1 : -1];

struct cSurfacePayload {                              // built for effect->v24(4, rec)
    void* mpVtbl;                                     // +0x00
    void* mpVtbl2;                                    // +0x04
    int   mField08;                                   // +0x08
    int   mStateDataOffset;                           // +0x0c
    void* mpData;                                     // +0x10
};

// ---- cDistributeEffect (retail offsets, cross-checked at 0xa92d90 / 0xa934e0) ----
struct cDistributeEffect {
    void*   mpVtbl;                                   // +0x00
    void*   mpVtbl04;                                 // +0x04
    int     mField08;                                 // +0x08
    void*   mpVtbl0c;                                 // +0x0c
    void*   mpVtbl10;                                 // +0x10
    cDistributeDescription* mDesc;                    // +0x14
    int     mCollectionIndex;                         // +0x18
    cIEffectsWorld* mWorld;                           // +0x1c
    void*   mGlobalParams;                            // +0x20
    cEffectParams* mChildParams;                      // +0x24
    u32     mFlags;                                   // +0x28
    Transform38 mSourceTransform;                     // +0x2c
    Transform38 mRigidTransform;                      // +0x64
    int     mSubdivCount;                             // +0x9c
    float   mAltitudeRange[2];                        // +0xa0
    SampleVector mRenderSamples;                      // +0xa8
    SampleVector mSamples;                            // +0xbc
    int     mRenderSampleCount;                       // +0xd0
    int     mTargetSampleCount;                       // +0xd4
    SpVec<cIVisualEffect*> mEffects;                  // +0xd8
    int     mSetID;                                   // +0xec
    int     mFieldF0;                                 // +0xf0
    int     mFieldF4;                                 // +0xf4
    char    padF8[8];
    Vector3 mSubdivOffset;                            // +0x100
    Vector3 mSubdivScale;                             // +0x10c
    void*   mField118;                                // +0x118
    SpVec<cSurfaceRec> mSurfaceRecs;                  // +0x11c
    SpVec<u8> mSurfaceStateData;                      // +0x130
    char    pad144[0x158 - 0x144];
    int     mField158;                                // +0x158
    void*   mpEffectData15c;                          // +0x15c
    int     mField160;                                // +0x160
    int     mField164;                                // +0x164
    int     mField168;                                // +0x168
    float   mField16c;                                // +0x16c
    Vector3 mVec170;                                  // +0x170
    float   mCurrentSubdivScale;                      // +0x17c
    float   mField180;                                // +0x180
    float   mField184;                                // +0x184
    float   mField188;                                // +0x188
    float   mField18C;                                // +0x18c
    int     mField190;                                // +0x190
    int     mField194;                                // +0x194

    int  UpdateSamples(int target);
    int  ApplyEffect(void* param, float time, void* stats);

    // out-of-line in other TUs of the same .obj
    void CreateClusteredMatchingSamples2D(RawVec* out);      // 0x00a8f6a0
    void CreateSamples2D(int a, int b, int c);               // 0x00a8d450
    void CreateClusteredSamples2D(int a, int b, int c);      // 0x00a8dea0
    void CreateRandomSamples(int a, int b, int c);           // 0x00a8e7c0
    void PinSamplesToSurface(int first, int last);           // 0x00a91860
    void ApplyColorAndAlpha(int first, int last);            // 0x00a88d50
    void RigidTransformRange(int first, int last);           // 0x00a88800
    void Start(void* param, float time, void* stats);        // 0x00a91e40
    void ClearSamples(int);                                  // 0x00a8d350
};

// ---- helpers implemented in other translation units -----------------------------
struct cAutoRef {                                     // AutoRefCount<cIVisualEffect>
    cIVisualEffect* mpObject;
};
struct RefVec { cAutoRef* mpBegin; cAutoRef* mpEnd; cAutoRef* mpCapacity; };

extern "C" void* __cdecl EAAlloc(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0
extern "C" void  __cdecl operator_delete(void* p);                                       // 0x00f47380
cIVisualEffect* MakeVisualEffect(u8 type, int effectIndex, int collectionIndex, cEffectParams* params); // 0x00a714f0
void EffectPropagateParams(cEffectParams* params, cIVisualEffect* effect);               // 0x00a88640
void PtrVecInsert(void* vec, unsigned count, void** tmp);                                // 0x00a8c690
void PtrVecErase(void* begin, void* end);                                                // 0x00a8c4e0
void VectorPushBack3(FloatVec* vec, float* at, const float& value);                      // 0x00455660
void ScaleCurvePush(Vec3Vec* vec, Vector3* at, const Vector3& value);                    // 0x007ed1b0

namespace EA { namespace Messaging {
struct IServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual bool Post(int msgId, void* msg, int flags);              // +0x14
};
IServer* GetServer();                                                                     // 0x00883860
} }

struct MsgPair { int mLo; int mHi; };
MsgPair GetEffectMessage(cDistributeEffect* self);                                        // 0x00a88220

extern float g16786dc, g16786e0, g16786e4;         // 0x016786dc/e0/e4 colour bases

// The out-of-line grow helpers are __thiscall with the vector passed in ecx.
struct FloatVecGrow : FloatVec {
    void Grow(float* at, const float& value);        // 0x00455660
};
struct Vec3VecGrow  : Vec3Vec  {
    void Grow(Vector3* at, const Vector3& value);    // 0x007ed1b0
};

// push_back fast path for an sp_vector: the slow path calls the out-of-line grow.
static inline void PushBackFloat(FloatVec& v, float value) {
    float* at = v.mpEnd;
    if (at < v.mpCapacity) {
        v.mpEnd = at + 1;
        if (at)
            *at = value;
    } else {
        ((FloatVecGrow*)&v)->Grow(at, value);
    }
}
static inline void PushBackVec3(Vec3Vec& v, const Vector3& value) {
    Vector3* at = v.mpEnd;
    if (at < v.mpCapacity) {
        v.mpEnd = at + 1;
        if (at)
            *at = value;
    } else {
        ((Vec3VecGrow*)&v)->Grow(at, value);
    }
}
// sp_vector_allocator::deallocate: the 4 bytes before the block flag ownership.
struct AllocHeader { int mOwnsBlock; };
static inline void FreeVecBuffer(void* p) {
    if (p && ((AllocHeader*)p)[-1].mOwnsBlock != 0)
        operator_delete(p);
}

// ================================================================================
// @ 0x00a92d90
int cDistributeEffect::UpdateSamples(int target)
{
    RawVec tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;

    int savedRender = mRenderSampleCount;
    int newRender = mTargetSampleCount;
    int oldCount = (int)((char*)mSamples.mpEnd - (char*)mSamples.mpBegin) / 0x4c;

    int limit = 0;
    if (mDesc->mFlags & 1) {
        CreateClusteredMatchingSamples2D(&tmp);
    } else {
        if (target != 0) {
            if (mDesc->mFlags & 0x2000)
                limit = ((savedRender + mDesc->mField18 + target + 0xff) & 0xffffff00) - mDesc->mField18;
            else
                limit = savedRender + target;
            if (newRender > limit)
                newRender = limit;
        }
        if (mDesc->mField1c < 3) {
            if (mDesc->mField160 <= 0)
                CreateSamples2D(mTargetSampleCount, savedRender, newRender);
            else
                CreateClusteredSamples2D(mTargetSampleCount, savedRender, newRender);
        } else {
            CreateRandomSamples(mTargetSampleCount, savedRender, newRender);
        }
    }

    int newCount = (int)((char*)mSamples.mpEnd - (char*)mSamples.mpBegin) / 0x4c;
    if (newCount > oldCount) {
        if (mSurfaceRecs.mpBegin != mSurfaceRecs.mpEnd)
            PinSamplesToSurface(oldCount, newCount);
        if ((mDesc->mFlags & 0x10) || (mDesc->mFlags & 0x40))
            RigidTransformRange(oldCount, newCount);
        if (mDesc->mFlags & 0x20)
            ApplyColorAndAlpha(oldCount, newCount);
    }

    mRenderSampleCount = newRender;

    if (mDesc->mpEffectData15c != 0 && newRender > 0 && newRender == mTargetSampleCount) {
        EA::Messaging::IServer* server = EA::Messaging::GetServer();
        if (server) {
            MsgPair r = GetEffectMessage(this);
            struct EffectMsg {
                int             mSampleCount;            // +0x00
                int             mField04;                // +0x04
                cDistributeSample* mpSampleBegin;        // +0x08
                int   mPad0c;                            // +0x0c
                cDistributeEffect* mpEffect;             // +0x10
                int   mPad14;                            // +0x14
                int   mMsgLo;                            // +0x18
                int   mMsgHi;                            // +0x1c
                int   mField20;                          // +0x20
                int   mPad24;                            // +0x24
                int   mField28;                          // +0x28
                int   mPad2c;                            // +0x2c
                int   mField30;                          // +0x30
                int   mPad34;                            // +0x34
                int   mField38;                          // +0x38
            } msg;
            msg.mSampleCount  = newCount;
            msg.mpSampleBegin = mSamples.mpBegin;
            msg.mpEffect      = this;
            msg.mMsgLo        = r.mLo;
            msg.mMsgHi        = r.mHi;
            msg.mField20      = mField190;
            msg.mField28      = mField194;
            msg.mField30      = 0;
            msg.mField38      = 0;
            server->Post((int)mDesc->mpEffectData15c, &msg, 0);
        }
        if (!((mFlags >> 2) & 1) && !((mFlags >> 0xd) & 1))
            ((void(__thiscall*)(cDistributeEffect*, int))((void**)mpVtbl)[3])(this, 0);
    }

    if (!((mFlags >> 2) & 1)) {
        if (mRenderSampleCount == mTargetSampleCount && mTargetSampleCount > 0) {
            mRenderSamples.swap(mSamples);
            mSamples.Free();
            if (mSetID >= 0) {
                cBounds bounds;
                bounds.Init();
                int count = (int)((char*)mRenderSamples.mpEnd - (char*)mRenderSamples.mpBegin) / 0x4c;
                float maxScale = 0.0f;
                for (int i = 0; i < count; ++i) {
                    cDistributeSample* s = (cDistributeSample*)((char*)mRenderSamples.mpBegin + i * 0x4c);
                    if (s->mPosition.x < bounds.mMinX) bounds.mMinX = s->mPosition.x;
                    if (s->mPosition.x > bounds.mMaxX) bounds.mMaxX = s->mPosition.x;
                    if (s->mPosition.y < bounds.mMinY) bounds.mMinY = s->mPosition.y;
                    if (s->mPosition.y > bounds.mMaxY) bounds.mMaxY = s->mPosition.y;
                    if (s->mPosition.z < bounds.mMinZ) bounds.mMinZ = s->mPosition.z;
                    if (s->mPosition.z > bounds.mMaxZ) bounds.mMaxZ = s->mPosition.z;
                    if (s->mScale > maxScale) maxScale = s->mScale;
                }
                cEffectWorldObj* w = mWorld->v20();
                if (mDesc->mFlags & 0x100) {
                    w->v34(mSetID, &mVec170, mCurrentSubdivScale);
                    w->v38(mSetID, (mFlags >> 1) & 1);
                } else {
                    w->SetBounds(mSetID, (cBounds*)&mVec170, mCurrentSubdivScale);
                    w->SetBoundsEx(mSetID, (mFlags >> 1) & 1);
                }
            }
        }
    } else {
        // resize mEffects to the render sample count, releasing/acquiring the tail
        RefVec* ev = (RefVec*)&mEffects;
        int want = (int)((char*)mSamples.mpEnd - (char*)mSamples.mpBegin) / 0x4c;
        int have = (int)((char*)ev->mpEnd - (char*)ev->mpBegin) >> 2;
        for (int i = want; i < have; ++i)
            ev->mpBegin[i].mpObject->v0c(0);
        if (want < have)
            PtrVecErase(ev->mpBegin + want, ev->mpEnd);
        else {
            void* zero = 0;
            PtrVecInsert(ev->mpEnd, want - have, &zero);
        }
        if (have <= want) {
            for (int i = 0; i < have; ++i)
                ev->mpBegin[i].mpObject->v18((char*)mSamples.mpEnd + i * 0x4c - 0xc, &mRigidTransform);

            int dataOff1 = mField194 ? mField194 * mTargetSampleCount : mTargetSampleCount;
            int dataOff2 = mField190 ? mField190 * mTargetSampleCount : 0;

            while (have < want) {
                cIVisualEffect* fx = MakeVisualEffect(mDesc->mField14, mDesc->mField10,
                                                      mCollectionIndex, mChildParams);
                cIVisualEffect* old = ev->mpBegin[have].mpObject;
                if (fx != old) {
                    if (fx) fx->v34();
                    ev->mpBegin[have].mpObject = fx;
                    if (old) old->v38();
                }
                fx->v28((mFlags >> 1) & 1);
                if (mDesc->mFlags & 0x4000)
                    *(int*)((char*)fx + 0x28) |= 0x800;
                if (mDesc->mField14 != 0 && mChildParams)
                    EffectPropagateParams(mChildParams, fx);

                if (tmp.mpBegin != tmp.mpEnd) {
                    fx->v1c(0x11, (char*)tmp.mpBegin + have * 0x18, 6);
                    cSurfacePayload* rec = (cSurfacePayload*)mField118;
                    if (!rec) {
                        rec = (cSurfacePayload*)EAAlloc(0x14, "Swarm", 0, 0, 0, 0);
                        if (rec) {
                            rec->mpVtbl = (void*)0x014582ec;
                            rec->mpVtbl2 = (void*)0x014188c0;
                            rec->mField08 = 0;
                            rec->mStateDataOffset = mDesc->mField1c;
                            rec->mpData = &mSourceTransform;
                        }
                    }
                    fx->v24(4, rec);
                }

                struct OffPair { int mOff0; int mOff1; } offs;
                offs.mOff0 = dataOff2 + have;
                offs.mOff1 = dataOff1;
                fx->v20(4, &offs, 2);
                fx->v18((char*)mSamples.mpBegin + have * 0x4c, &mRigidTransform);

                cDistributeSample* s = (cDistributeSample*)((char*)mSamples.mpBegin + have * 0x4c);
                float scl = s->mScale44 * mField180;
                Vector3 v3;
                v3.x = s->mVec38.x * mVec170.x;
                v3.y = s->mVec38.y * mVec170.y;
                v3.z = s->mVec38.z * mVec170.z;
                fx->v1c(4, &scl, 1);
                fx->v1c(5, &v3, 3);
                fx->v08(0);
                ++have;
            }
        }
    }

    int result = newRender - savedRender;
    FreeVecBuffer(tmp.mpBegin);
    return result;
}

// ================================================================================
// @ 0x00a934e0
int cDistributeEffect::ApplyEffect(void* param, float time, void* stats)
{
    mCurrentSubdivScale = (mField184 + (mField188 - mField184) * time) * mField180;

    if (mSetID >= 0) {
        cEffectWorldObj* w = mWorld->v20();
        if (mDesc->mFlags & 0x100)
            w->v34(mSetID, &mVec170, mCurrentSubdivScale);
        else
            w->SetBounds(mSetID, (cBounds*)&mVec170, mCurrentSubdivScale);
    }

    if (mSurfaceStateData.mpBegin != mSurfaceStateData.mpEnd && !((mFlags >> 6) & 1)) {
        for (cSurfaceRec* rec = mSurfaceRecs.mpBegin; rec != mSurfaceRecs.mpEnd; ++rec) {
            void* obj = rec->mpObject;
            int state = (int)((char*)mSurfaceStateData.mpBegin + rec->mStateDataOffset);
            ((void(__thiscall*)(void*, int, void*, void*, int))((void**)obj)[8])(
                obj, rec->mField04, &mSourceTransform, &mRigidTransform, state);
        }
        mFlags |= 0x40;
    }
    (void)param;

    if (mpEffectData15c != 0 && !((mFlags >> 0xa) & 1)) {
        int mods = ((int(__thiscall*)(void*))((void**)mpEffectData15c)[4])(mpEffectData15c);
        if (mField168 != mods) {
            mField168 = mods;
            ClearSamples(1);
            mField16c = 0.0f;
        }
    }

    cDistributeEffectStats* st = (cDistributeEffectStats*)stats;
    if (mRenderSampleCount != mTargetSampleCount) {
        if (!(mDesc->mFlags & 0x1000)) {
            if (st->mFirst_38 == 0) {
                st->mFirst_34 += UpdateSamples(mGlobalParams ? *(int*)((char*)mGlobalParams + 0x18) : 0);
            } else {
                int want = st->mFirst_38 - st->mFirst_34;
                if (want > 0) {
                    int cap = *(int*)((char*)mGlobalParams + 0x18);
                    if (want > cap) want = cap;
                    st->mFirst_34 += UpdateSamples(want);
                }
            }
        } else {
            UpdateSamples(0);
        }
    }

    if (mRenderSampleCount == mTargetSampleCount && mDesc->mField10 >= 0) {
        if (mDesc->mField14 >= 1) {
            if (mDesc->mFlags & 0x4000) {
                if (!(mFlags & 0x1000)) {
                    Start(param, time, stats);
                } else if ((*mEffects.mpBegin)->IsReady()) {
                    for (cIVisualEffect** it = mEffects.mpBegin; it != mEffects.mpEnd; ++it)
                        (*it)->v14(param, time, stats);
                    mFlags &= ~0x1000;
                }
            } else {
                for (cIVisualEffect** it = mEffects.mpBegin; it != mEffects.mpEnd; ++it)
                    (*it)->v14(param, time, stats);
                st->mField08 += (int)(mEffects.mpEnd - mEffects.mpBegin);
            }
        } else if (mField168 == 0 || (mDesc->mFlags & 0x800)) {
            for (cIVisualEffect** it = mEffects.mpBegin; it != mEffects.mpEnd; ++it) {
                if ((*it)->v10())
                    goto done;
            }
            ((void(__thiscall*)(cDistributeEffect*, int))((void**)mpVtbl)[3])(this, 0);
        }
    }
done:
    if (stats != 0 && mSetID >= 0) {
        int n = (int)((char*)mRenderSamples.mpEnd - (char*)mRenderSamples.mpBegin) / 0x4c;
        if (mDesc->mFlags & 0x100) {
            st->mField18 += n;
            st->mField1c += n * mSubdivCount;
        } else {
            st->mField10 += n;
            st->mField14 += n * mSubdivCount;
        }
        mSubdivCount = 0;
    }
    return 0;
}

// ================================================================================
// @ 0x00a938d0
struct MeshStreamerTable {
    void* mpRegister;                                 // +0x00
    void* mpPad04;                                    // +0x04
    void* mpCreate;                                   // +0x08
    void* mpField0c;                                  // +0x0c
    void* mpPad10;                                    // +0x10
    void* mpField14;                                  // +0x14
    int   mField18;                                   // +0x18
    int   mField1c;                                   // +0x1c
};
extern MeshStreamerTable gMeshStreamerTable;          // 0x01676050

void RegisterMeshStreamers2(bool)
{
    gMeshStreamerTable.mpRegister = (void*)0x00a8bf10;
    gMeshStreamerTable.mpCreate   = (void*)0x00a8cc00;
    gMeshStreamerTable.mpField0c  = (void*)0x00a93880;
    gMeshStreamerTable.mpField14  = (void*)0x00a89680;
    gMeshStreamerTable.mField18   = 3;
    gMeshStreamerTable.mField1c   = 4;
}

// ================================================================================
// ---- cMetaParticlesEffect (recovered from 0x00a93980 / 0x00a93910) --------------
struct cMetaParticlesEffect {
    void*   mpVtbl;                                   // +0x00
    int     mField04;                                 // +0x04
    int     mField08;                                 // +0x08
    float   mField0c;                                 // +0x0c
    float   mField10;                                 // +0x10
    float   mField14;                                 // +0x14
    float   mScales18[4];                             // +0x18
    float   mField28;                                 // +0x28
    float   mField2c;                                 // +0x2c
    float   mField30;                                 // +0x30
    float   mField34;                                 // +0x34
    float   mField38;                                 // +0x38
    float   mField3c;                                 // +0x3c
    float   mField40;                                 // +0x40
    float   mField44;                                 // +0x44
    float   mField48;                                 // +0x48
    float   mField4c;                                 // +0x4c
    float   mField50;                                 // +0x50
    float   mField54;                                 // +0x54
    float   mField58;                                 // +0x58
    float   mField5c;                                 // +0x5c
    FloatVec mVec60;                                  // +0x60
    float   mField74;                                 // +0x74
    u16     mField78;                                 // +0x78
    u16     mPad7a;
    float   mField7c;                                 // +0x7c
    FloatVec mVec80;                                  // +0x80
    Vec3Vec mVec94;                                   // +0x94
    FloatVec mVecA8;                                  // +0xa8
    int     mPadBc;                                   // +0xbc
    int     mFieldC0;                                 // +0xc0
    int     mFieldC4;                                 // +0xc4
    u8      mFieldC8;                                 // +0xc8
    u8      mFieldC9;                                 // +0xc9
    u8      mFieldCa;                                 // +0xca
    u8      mFieldCb;                                 // +0xcb
    u16     mFieldCc;                                 // +0xcc
    u16     mPadCe;
    float   mFieldD0;                                 // +0xd0
    int     mFieldD4;                                 // +0xd4
    int     mFieldD8;                                 // +0xd8
    int     mFieldDc;                                 // +0xdc
    u8      mFieldE0;                                 // +0xe0
    u8      mPadE1[3];
    float   mFieldE4;                                 // +0xe4
    float   mFieldE8;                                 // +0xe8
    float   mFieldEc;                                 // +0xec
    float   mFieldF0;                                 // +0xf0
    float   mFieldF4;                                 // +0xf4
    float   mFieldF8;                                 // +0xf8
    float   mFieldFc;                                 // +0xfc
    float   mField100;                                // +0x100
    float   mField104;                                // +0x104
    float   mField108;                                // +0x108

    ~cMetaParticlesEffect();
    cMetaParticlesEffect();
};

// @ 0x00a93910
cMetaParticlesEffect::~cMetaParticlesEffect()
{
    FreeVecBuffer(mVecA8.mpBegin);
    FreeVecBuffer(mVec94.mpBegin);
    FreeVecBuffer(mVec80.mpBegin);
    FreeVecBuffer(mVec60.mpBegin);
    mpVtbl = (void*)0x013ef094;
}

// @ 0x00a93980
cMetaParticlesEffect::cMetaParticlesEffect()
{
    mField04 = 0;
    mpVtbl = (void*)0x01458474;
    mField08 = 0;
    mField0c = 2.0f;
    mField10 = 2.0f;
    mField14 = 0.0f;
    mScales18[0] = -1.0f;
    mScales18[1] = -1.0f;
    mScales18[2] = -1.0f;
    mScales18[3] = -1.0f;
    mField28 = 0.0f;
    mField2c = 0.0f;
    mField30 = 1.0f;
    mField34 = 0.0f;
    mField38 = 0.0f;
    mField3c = 1.0f;
    mField40 = 0.0f;
    mField44 = 0.0f;
    mField48 = 0.0f;
    mField4c = 0.0f;
    mField50 = 0.0f;
    mVec60.mpBegin = 0;
    mVec60.mpEnd = 0;
    mVec60.mpCapacity = 0;
    mField54 = 0.0f;
    mField58 = 0.0f;
    mField5c = 0.0f;
    mField74 = 1.0f;
    mField7c = 0.0f;
    mField78 = 0;
    mVec80.mpBegin = 0;
    mVec80.mpEnd = 0;
    mVec80.mpCapacity = 0;
    mVec94.mpBegin = 0;
    mVec94.mpEnd = 0;
    mVec94.mpCapacity = 0;
    mVecA8.mpBegin = 0;
    mVecA8.mpEnd = 0;
    mVecA8.mpCapacity = 0;
    mFieldC8 = 0;
    mFieldC9 = 0;
    mFieldCa = 0;
    mFieldCb = 0;
    mFieldD0 = 0.0f;
    mFieldC0 = -1;
    mFieldC4 = -1;
    mFieldD8 = -1;
    mFieldDc = -1;
    mFieldCc = 0;
    mFieldE0 = 0;
    mFieldE4 = g16786dc;
    mFieldE8 = g16786e0;
    mFieldEc = g16786e4;
    mFieldF0 = 0.0f;
    mFieldF4 = 0.0f;
    mFieldF8 = 0.0f;
    mFieldFc = g16786dc;
    mField100 = g16786e0;
    mField104 = g16786e4;
    mField108 = 0.0f;

    PushBackFloat(mVec60, 30.0f);
    Vector3 one = { 1.0f, 1.0f, 1.0f };
    PushBackVec3(mVec94, one);
    PushBackFloat(mVecA8, 1.0f);
    PushBackFloat(mVec80, 1.0f);
}

// ================================================================================
// @ 0x00a93c60
struct cSampleRange {
    Vector3 mMin;                                     // +0x00
    Vector3 mMax;                                     // +0x0c

    void Erase(const Vector3& v);
};

float gFltMax = 3.4028234663852886e+38f;              // "unset" sample-range sentinel (.rdata)

void cSampleRange::Erase(const Vector3& v)
{
    float x0 = mMin.x;
    if (x0 != gFltMax && x0 != -gFltMax) {
        mMin.y = mMin.y - v.y;
        mMin.z = mMin.z - v.z;
        mMin.x = mMin.x - v.x;
        mMax.z = mMax.z + v.z;
        mMax.x = mMax.x + v.x;
        mMax.y = mMax.y + v.y;
    }
}
