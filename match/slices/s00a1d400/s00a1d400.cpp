// Slice s00a1d400 -- EA::Audio::Sound property system (Get/SetPropertyInternal,
// property-hash helpers, primitive connect/route) and small virtual helpers.
// Object file: SPAudio/AudioSound.obj.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// --- external callees (address-labelled) -----------------------------------
void* GetSystemAT();                                   // 0x00a206f0
void  CurveSetGain(void* self, float v);               // 0x00a16fd0 (Emitter::SetCurveGain)
void* AllocObject(u32 size);                           // 0x00a17090
void* CtorHelper(void* obj, void* owner);              // 0x00a17100

// vtable slot fetch
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])

struct Vec3 { float x, y, z; };

extern const u32 g_propKey14527fc;   // 0x014527fc

// eastl hashtable iterator (2 pointers -> returned through a hidden pointer).
struct HTIter { void* node; void* bucket; };

// The eastl fixed_hashtable header fields we touch: bucket buffer at +4,
// bucket count at +8; the sentinel iterator is mpBuckets[mnBuckets].
struct Hashtable {
    u32    pad0;         // +0x00
    void** mpBuckets;    // +0x04
    u32    mnBuckets;    // +0x08
    u32    padC;         // +0x0c
    HTIter find(const u32& key) const;         // 0x00645ed0
    void   insert(void* pair, void* alloc, int flag);  // 0x00a26ce0
    HTIter erase(HTIter it);                   // 0x00d2c9f0
};

// Node of a property map: key + float value (or a pointer in the prim/route maps).
struct PropNode { u32 key; float value; };

struct LerpF {
    float mTarget, mCurrent, mRate;
};

struct Sound {
    void*  vptr;                       // 0x00
    void*  vptrMix;                    // 0x04
    void*  vptrRef;                    // 0x08
    u32    mRefCount;                  // 0x0c
    void*  mNodeNext;                  // 0x10
    void*  mNodePrev;                  // 0x14
    u8     pad00[0x38 - 0x18];         // 0x18
    u32    mSoundId;                   // 0x38
    u32    mInstanceId;                // 0x3c
    u32    mSampleId;                  // 0x40
    void*  mpEmitter;                  // 0x44
    float  mDistanceToListener;        // 0x48
    float  mLastDistance;              // 0x4c
    float  mMinDistance;               // 0x50
    float  mMaxDistance;               // 0x54
    float  mGain;                      // 0x58
    float  mMaxGainChange;             // 0x5c
    float  mAttenuatedGain;            // 0x60
    float  mEffectiveGain;             // 0x64
    float  mPauseGain;                 // 0x68
    float  mPriority;                  // 0x6c
    float  mWetLevel;                  // 0x70
    float  mLowPass;                   // 0x74
    float  mHighPass;                  // 0x78
    float  mDopplerPitch;              // 0x7c
    float  mRandomPitch;               // 0x80
    float  mPitch;                     // 0x84
    float  mAverageSpeed;              // 0x88
    float  mLastPitch;                 // 0x8c
    float  m90;                        // 0x90
    float  m94;                        // 0x94
    float  m98;                        // 0x98
    u8     mb9c;                       // 0x9c
    u8     mb9d;                       // 0x9d
    u8     mb9e;                       // 0x9e
    u8     mb9f;                       // 0x9f
    u8     mbDirect;                   // 0xa0
    u8     pad1[3];                    // 0xa1
    u32    mPosHandle;                 // 0xa4
    Vec3   mPos;                       // 0xa8
    Vec3   mVelDelta;                  // 0xb4
    u8     mMode;                      // 0xc0
    u8     pad2[3];                    // 0xc1
    Vec3   mDirectPos;                 // 0xc4
    u8     pad3[0xf4 - 0xd0];          // 0xd0
    u8     mPropF4[0x14];              // 0xf4 (property hashtable region)
    u8     pad4[0x320 - 0x108];        // 0x108
    u32    m320;                       // 0x320
    float  mStartDelay;                // 0x324
    float  m328;                       // 0x328
    float  mElapsed;                   // 0x32c
    u32    mPrimsCount;                // 0x330
    u8     mMap334[0x14];              // 0x334 (primitive map; +4 bucket, +8 count; 0x338 overlaps)
    u8     pad5[0x514 - 0x348];        // 0x348
    u8     mMap514[0x20];              // 0x514
    u8     pad6[0x888 - 0x534];        // 0x534
    u8     mMap888[0x20];              // 0x888
    u8     pad7a[0xc90 - 0x8a8];       // 0x8a8
    u32    mC90;                       // 0xc90
    u8     pad7b[0xcd0 - 0xc94];       // 0xc94
    float  mCD0;                       // 0xcd0
    u8     mCD4;                       // 0xcd4
    u8     mCD5;                       // 0xcd5
    u8     pad8[0xce4 - 0xcd6];        // 0xcd6
    u32    mFlags;                     // 0xce4
    u8     pad9[0x1e0c - 0xce8];       // 0xce8
    int    mCount;                     // 0x1e0c

    // methods in this slice
    bool GetPropertyInternal(u32 key, float* out);          // 0x00a1d400
    bool HasProperty(u32 key);                              // 0x00a1d6d0
    bool CompareProperties(void* other);                    // 0x00a1d710
    void SetProperty(u32 key, float value, u32 arg);        // 0x00a1d830
    void SetPropertyInternal(u32 key, float value, bool dummy);  // 0x00a1d9c0
    bool ConnectPrimitive(u32 key, void* prim);             // 0x00a1df20
    void DisconnectPrimitive(u32 key, void* prim);          // 0x00a1e140
    void Route(u32 a, u32 b, void* prim);                   // 0x00a1e1d0
};

// ===========================================================================
// 0x00a1d400  Sound::GetPropertyInternal -- hash-keyed property getter.
// ===========================================================================
// @ 0x00a1d400
bool Sound::GetPropertyInternal(u32 key, float* out)
{
    switch (key) {
    case 0x3593710:  *out = mGain;           return true;
    case 0x50c5d66:  *out = mPos.y;          return true;
    case 0x50c5d67:  *out = mPos.x;          return true;
    case 0x50c5d65:  *out = mPos.z;          return true;
    case 0xf616b72:  *out = mMaxDistance;    return true;
    case 0x2406a047: *out = mMinDistance;    return true;
    case 0x25df0108: *out = mMaxGainChange;  return true;
    case 0x49eb68db: *out = mLowPass;        return true;
    case 0x393f7f7d: *out = mWetLevel;       return true;
    case 0x6325c989: *out = mEffectiveGain;  return true;
    case 0x647a7836: *out = mHighPass;       return true;
    case 0x6df5822d: *out = (float)mCount;   return true;
    case 0xb1f42539:
        if (mFlags & 0x400) { *out = mCD0; return true; }
        break;
    case 0xa26a765f: *out = mDopplerPitch;   return true;
    case 0xbaf7f4f9: *out = (float)mPrimsCount; return true;
    case 0xc2d1f579: *out = mPauseGain;      return true;
    case 0x222b8006: *out = mb9c ? 1.0f : 0.0f; return true;
    case 0x12d2a4d4: *out = (mMode & 8) ? 1.0f : 0.0f; return true;
    case 0x29e8b9f8: *out = m328;            return true;
    default: break;
    }

    Hashtable* ht = (Hashtable*)((char*)this + 0xf8);
    HTIter it = ht->find(key);
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        *out = *(float*)((char*)it.node + 4);
        return true;
    }
    return false;
}

// ===========================================================================
// 0x00a1d6d0  Sound::HasProperty -- property-map membership test.
// ===========================================================================
// @ 0x00a1d6d0
bool Sound::HasProperty(u32 key)
{
    Hashtable* ht = (Hashtable*)((char*)this + 0xf4);
    void** buckets = ht->mpBuckets;
    u32 n = ht->mnBuckets;
    void* end = (void*)buckets[n];
    return ht->find(key).node != end;
}

// ===========================================================================
// 0x00a1d830  Sound::SetProperty -- set through the primitive map / emitter.
// ===========================================================================
// @ 0x00a1d830
void Sound::SetProperty(u32 key, float value, u32 arg)
{
    // The original guards against NaN/inf values before doing anything.
    u32 bits = *(u32*)&value;
    if ((bits & 0x7fffffff) != 0) {
        u32 e = (bits + 0xff800000) & 0x7f800000;
        if (e >= 0x7f000000) {
            u32 m = (bits & 0x7fffffff) - 1;
            if (m >= 0x7fffff)
                return;
        }
    }

    void* sys = GetSystemAT();
    void* e = ((void*(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, key);
    if (e == 0) {
        ((void(__thiscall*)(void*, u32, float, u32))VTSLOT((char*)this - 4, 0x98))((char*)this - 4, key, value, arg);
        return;
    }

    Hashtable* ht = (Hashtable*)((char*)this + 0x514);
    HTIter it = ht->find(key);
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* obj = *(void**)((char*)it.node + 4);
        if (obj != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))VTSLOT(obj, 0xc))(obj, 0x4e73a43a);
            if (p != 0) {
                ((void(__thiscall*)(void*, u32))VTSLOT(p, 0x10))(p, key);
                return;
            }
        }
        // fall through: rebuild primitive aggregate
    }
    {
        void* agg = AllocObject(0x6c);
        void* obj = 0;
        if (agg != 0)
            obj = CtorHelper(agg, (char*)this - 4);
        if (obj != 0)
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
        ((void(__thiscall*)(void*, void*))0x00a16a90)(e, obj);
        ((void(__thiscall*)(void*, void*))VTSLOT(*(void**)((char*)obj + 4), 0x10))(*(void**)((char*)obj + 4), e);
        ((void(__thiscall*)(void*, void*))VTSLOT(*(void**)((char*)obj + 4), 0x10))(*(void**)((char*)obj + 4), obj);
        ((void(__thiscall*)(void*))VTSLOT(obj, 0x10))(obj);
        ((void(__thiscall*)(void*, int))VTSLOT(obj, 0x2c))(obj, 1);
        void* old = *(void**)((char*)it.node + 4);
        if (obj != old) {
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
            *(void**)((char*)it.node + 4) = obj;
            if (old != 0)
                ((void(__thiscall*)(void*))VTSLOT(old, 4))(old);
        }
        ((void(__thiscall*)(void*))VTSLOT(obj, 4))(obj);
    }
}

// ===========================================================================
// 0x00a1d710  Sound::CompareProperties -- property/primitive comparison.
// ===========================================================================
// @ 0x00a1d710
bool Sound::CompareProperties(void* other)
{
    if (mFlags & 0x80)
        return false;
    Sound* o = (Sound*)other;
    if (o == 0 || o == this)
        return false;
    if (!(o->mFlags & 0x10))
        return false;
    if (o->mbDirect == 0 || o->mC90 != 0)
        return false;
    if (o->mSoundId != mSoundId)
        return false;

    void* sys = GetSystemAT();
    if (((int(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, 0x71bc3009) == 0) {
        if (fabs(o->mAverageSpeed - mAverageSpeed) > 0.2f)
            return false;
    } else {
        void* p1;
        {
            Hashtable* h1 = (Hashtable*)((char*)this + 0x338);
            HTIter it = h1->find(g_propKey14527fc);
            if (it.node == (void*)h1->mpBuckets[h1->mnBuckets])
                return true;
            p1 = *(void**)((char*)it.node + 4);
        }
        void* p2;
        {
            Hashtable* h2 = (Hashtable*)((char*)o + 0x338);
            HTIter it2 = h2->find(g_propKey14527fc);
            if (it2.node == (void*)h2->mpBuckets[h2->mnBuckets])
                return true;
            p2 = *(void**)((char*)it2.node + 4);
        }
        float f1 = ((float(__thiscall*)(void*))VTSLOT(p1, 0x1c))(p1);
        float f2 = ((float(__thiscall*)(void*))VTSLOT(p2, 0x1c))(p2);
        if (fabs(f1 - f2) > 0.2f)
            return false;
    }
    return true;
}

// ===========================================================================
// 0x00a1d9c0  Sound::SetPropertyInternal -- hash-keyed property setter.
// ===========================================================================
// @ 0x00a1d9c0
void Sound::SetPropertyInternal(u32 key, float value, bool dummy)
{
    {
        Hashtable* ht = (Hashtable*)((char*)this + 0x888);
        HTIter it = ht->find(key);
        if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
            void* obj = *(void**)((char*)it.node + 4);
            ((void(__thiscall*)(void*, float))0x00a16fd0)(obj, value);
        }
    }

    bool changed = true;
    switch (key) {
    case 0x393f7f7d: mWetLevel = value; return;
    case 0x12d2a4d4:
        if (value == 0.0f) mMode &= ~8;
        else               mMode |= 8;
        goto done;
    case 0x50c5d66:  mPos.y = value; mMode |= 2; return;
    case 0x3593710:  mGain = value; goto done;
    case 0x50c5d65:  mPos.z = value; mMode |= 4; return;
    case 0x50c5d67:  mPos.x = value; mMode |= 1; return;
    case 0xf616b72:  mMaxDistance = value; goto done;
    case 0x25df0108: mMaxGainChange = value; return;
    case 0x222b8006: mb9c = (value != 0.0f); return;
    case 0x2406a047: mMinDistance = value; return;
    case 0x26341ede: {
        float prev = m94;
        m94 = value;
        changed = (prev != value);
        goto done;
    }
    case 0x29e8b9f8: m328 = value; return;
    case 0x71bc3009: mAverageSpeed = value; return;
    case 0x6dd08218: mb9d = (value != 0.0f); return;
    case 0x49eb68db: {
        float prev = mLowPass;
        mLowPass = value;
        mFlags |= 0x20000;
        changed = (prev != value);
        if (mMode & 8) return;
        goto done;
    }
    case 0x647a7836: {
        float prev = mHighPass;
        mHighPass = value;
        mFlags |= 0x8000;
        changed = (prev != value);
        if (mMode & 8) return;
        goto done;
    }
    case 0x6df5822d: {
        int iv = (int)value;
        changed = (mCount != iv);
        mCount = iv;
        goto done;
    }
    case 0xba134192: mbDirect = (value != 0.0f); return;
    case 0xa26a765f: {
        float prev = mDopplerPitch;
        mDopplerPitch = value;
        mFlags |= 0x10000;
        changed = (prev != value);
        if (mMode & 8) return;
        goto done;
    }
    case 0xb1f42539: mCD0 = value; mFlags |= 0x400; return;
    case 0xb85523e5: {
        bool b = (value != 0.0f);
        ((int(__thiscall*)(Sound*, bool, u32, float, int))VTSLOT(this, 0x1c))(this, b, 4, 3.0f, 1);
        return;
    }
    case 0xbaf7f4f9: mPrimsCount = (u32)(long long)value; return;
    case 0xc57f4567: {
        float prev = mPos.x;
        mPos.x = value;
        changed = (prev != value);
        goto done;
    }
    default: break;
    }

    {
        Hashtable* ht = (Hashtable*)((char*)this + 0xf8);
        HTIter it = ht->find(key);
        if (it.node == (void*)ht->mpBuckets[ht->mnBuckets]) {
            PropNode pair;
            pair.key = key;
            pair.value = value;
            ht->insert((void*)&pair, 0, 0);
        } else {
            float* pv = (float*)((char*)it.node + 4);
            changed = (*pv != value);
            *pv = value;
        }
    }

done:
    if (mpEmitter != 0 && changed) {
        if (!((bool(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x20))(this, -1, 1)) {
            ((void(__thiscall*)(void*, u32, float, int))VTSLOT(mpEmitter, 0x2c))(mpEmitter, key, value, 1);
        }
    }
}

// ===========================================================================
// 0x00a1df20  Sound::ConnectPrimitive
// ===========================================================================
// @ 0x00a1df20
bool Sound::ConnectPrimitive(u32 key, void* prim)
{
    Hashtable* ht = (Hashtable*)((char*)this + 0x334);
    HTIter it = ht->find(key);
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* e = *(void**)((char*)it.node + 4);
        if (e != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))VTSLOT(e, 0xc))(e, 0x4e73a43a);
            if (p != 0) {
                if (((void*(__thiscall*)(void*))VTSLOT(e, 0x30))(e) == (char*)this - 4) {
                    ((void(__thiscall*)(void*, void*))VTSLOT(p, 0x10))(p, prim);
                    return true;
                }
            }
        }
    }

    void* sys = GetSystemAT();
    void* e = ((void*(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, key);
    if (e == 0)
        return false;

    void* obj = 0;
    if (it.node != (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* old = *(void**)((char*)it.node + 4);
        if (old != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))VTSLOT(old, 0xc))(old, 0x4e73a43a);
            if (p != 0 && ((void*(__thiscall*)(void*))VTSLOT(old, 0x30))(old) == (char*)this - 4) {
                ((void(__thiscall*)(void*, void*))VTSLOT(p, 0x10))(p, prim);
                return true;
            }
        }
    }

    {
        void* agg = AllocObject(0x6c);
        if (agg != 0)
            obj = CtorHelper(agg, (char*)this - 4);
        if (obj != 0)
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
        ((void(__thiscall*)(void*, void*))0x00a16a90)(e, obj);
        ((void(__thiscall*)(void*, void*))VTSLOT(*(void**)((char*)obj + 4), 0x10))(*(void**)((char*)obj + 4), obj);
        ((void(__thiscall*)(void*, void*))VTSLOT(obj, 0x10))(obj, prim);
        ((void(__thiscall*)(void*, int))VTSLOT(obj, 0x2c))(obj, 1);
        void* old = *(void**)((char*)it.node + 4);
        if (obj != old) {
            ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
            *(void**)((char*)it.node + 4) = obj;
            if (old != 0)
                ((void(__thiscall*)(void*))VTSLOT(old, 4))(old);
        }
        ((void(__thiscall*)(void*))VTSLOT(obj, 4))(obj);
    }
    return true;
}

// ===========================================================================
// 0x00a1e140  Sound::DisconnectPrimitive
// ===========================================================================
// @ 0x00a1e140
void Sound::DisconnectPrimitive(u32 key, void* prim)
{
    Hashtable* ht = (Hashtable*)((char*)this + 0x334);
    HTIter it = ht->find(key);
    if (it.node == (void*)ht->mpBuckets[ht->mnBuckets])
        return;
    void* e = *(void**)((char*)it.node + 4);
    if (e != 0) {
        void* p = ((void*(__thiscall*)(void*, u32))VTSLOT(e, 0xc))(e, 0x4e73a43a);
        if (p != 0) {
            ((void(__thiscall*)(void*, void*))VTSLOT(p, 0x14))(p, prim);
            return;
        }
    }
    if (e == prim) {
        it = ht->erase(it);
    }
}

// ===========================================================================
// 0x00a1e1d0  Sound::Route
// ===========================================================================
// @ 0x00a1e1d0
void Sound::Route(u32 a, u32 b, void* prim)
{
    Hashtable* ht = (Hashtable*)((char*)this + 0x888);
    HTIter it = ht->find(b);
    void* slot = 0;
    if (it.node == (void*)ht->mpBuckets[ht->mnBuckets]) {
        void* alloc = AllocObject(0x1c);
        void* obj = 0;
        if (alloc != 0)
            obj = CtorHelper(alloc, this);
        ((void(__thiscall*)(void*, u32))0x00fccdd0)(obj, b);
        float f = 1.0f;
        if (!((bool(__thiscall*)(void*, u32, float*))VTSLOT((char*)this + 4, 0x10))((char*)this + 4, b, &f))
            ((void(__thiscall*)(void*, u32, float*))VTSLOT((char*)this + 4, 0x10))((char*)this + 4, b, &f);
        ((void(__thiscall*)(void*, float))0x00a16fd0)(obj, f);
        ((void(__thiscall*)(void*))VTSLOT(obj, 0))(obj);
        PropNode pair;
        pair.key = b;
        pair.value = *(float*)&obj;
        ht->insert((void*)&pair, 0, 0);
        slot = obj;
    } else {
        slot = *(void**)((char*)it.node + 4);
    }

    if (prim != 0) {
        ((void(__thiscall*)(void*, void*))0x00a37080)(prim, slot);
        ((void(__thiscall*)(void*))VTSLOT(prim, 0x10))(prim);
        slot = prim;
    }
    ((void(__thiscall*)(void*, u32, void*))VTSLOT((char*)this + 4, 0x18))((char*)this + 4, a, slot);
}
