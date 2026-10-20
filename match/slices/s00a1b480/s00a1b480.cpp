// Slice s00a1b480 -- EA::Audio::Sound lifecycle (StartEmitter, Init, Start, Stop,
// Pause, emitter teardown, distance/gain update) plus the LerpF helper.
// Object file: SPAudio/AudioSound.obj.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned int   u32;
typedef unsigned short u16;

// --- external callees (address-labelled) -----------------------------------
void* GetSystemAT();                                    // 0x00a206f0
extern "C" __declspec(dllimport) int __cdecl rand(void); // msvcr90 IAT

// --- external float/double/pointer constants (masked relocations) ----------
extern float  g_1486110;   // 0x01486110
extern float  g_1485378;   // 0x01485378
extern double g_13f11c0;   // 0x013f11c0
extern float  g_1485720;   // 0x01485720
extern float  g_13eb95c;   // 0x013eb95c
extern float  g_13eb1bc;   // 0x013eb1bc
extern float  g_13f11c8;   // 0x013f11c8
extern float  g_1470f1c;   // 0x01470f1c
extern float  g_140d4f8;   // 0x0140d4f8
extern void*  g_16e61a8;   // 0x016e61a8

// vtable slot fetch: VTSLOT(obj, byte-offset-in-vtable)
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])

struct Vec3 { float x, y, z; };

// LerpF (EA::Audio::LerpT<float>): { mTarget, mCurrent, mRate }
struct LerpF {
    float mTarget;   // +0
    float mCurrent;  // +4
    float mRate;     // +8
    __declspec(noinline) void Set(const float& value, float rate);   // 0x00a1b660
    float Get();                                 // 0x00a1b020
};

// Embedded configuration object at Sound+0xe4 (its own vtable).
struct ConfigObj { void* vptr; };

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
    bool   mbHardStop;                 // 0x9c
    bool   mb9d;                       // 0x9d
    bool   mb9e;                       // 0x9e
    bool   mb9f;                       // 0x9f
    bool   mbDirect;                   // 0xa0
    u8     pad1[3];                    // 0xa1
    u32    mPosHandle;                 // 0xa4
    Vec3   mPos;                       // 0xa8
    Vec3   mVelDelta;                  // 0xb4
    u8     mMode;                      // 0xc0
    u8     pad2[3];                    // 0xc1
    Vec3   mDirectPos;                 // 0xc4
    float  mDirGain0;                  // 0xd0
    float  mDirGain1;                  // 0xd4
    float  mWetLevel2;                 // 0xd8
    int    mStopReason;                // 0xdc
    u32    mEmitterType;               // 0xe0
    ConfigObj mConfig;                 // 0xe4
    u8     pad3[0xfc - 0xe4 - sizeof(ConfigObj)];  // 0xe8
    u8     mProps[0x320 - 0xfc];       // 0xfc (fixed_hash_map)
    u32    m320;                       // 0x320
    float  mStartDelay;                // 0x324
    float  m328;                       // 0x328
    float  mElapsed;                   // 0x32c
    u8     mPrims[0xc38 - 0x330];      // 0x330 (fixed_vector + hash)
    void*  mC38;                       // 0xc38
    u8     pad4[0xc7c - 0xc3c];        // 0xc3c
    u32    mC7c;                       // 0xc7c
    u32    mC80;                       // 0xc80
    u8     pad5[0xc90 - 0xc84];        // 0xc84
    void*  mC90;                       // 0xc90
    float  mC94;                       // 0xc94 (fader target; fader.mCurrent == mC98)
    float  mC98;                       // 0xc98
    u8     pad6[0xca8 - 0xc9c];        // 0xc9c
    float  mCA8;                       // 0xca8
    u32    mCAC;                       // 0xcac
    u8     mCB0;                       // 0xcb0
    u8     pad7[3];                    // 0xcb1
    float  mCB4;                       // 0xcb4
    u8     pad8[0xcc8 - 0xcb8];        // 0xcb8
    double mCC8;                       // 0xcc8
    float  mCD0;                       // 0xcd0
    u8     mCD4;                       // 0xcd4
    u8     mCD5;                       // 0xcd5
    u8     pad9[2];                    // 0xcd6
    u32    mCD8;                       // 0xcd8
    u8     pad10[0xce4 - 0xcdc];       // 0xcdc
    u32    mFlags;                     // 0xce4
    u8     pad11[0x1de0 - 0xce8];      // 0xce8 (response curves)
    int    mPauseCount;                // 0x1de0
    u8     mPauseCounts[8];            // 0x1de4
    u32    mNumPauseCounters;          // 0x1dec
    LerpF  mPauseFader;                // 0x1df0
    u8     pad12[0x1e0c - 0x1dfc];     // 0x1dfc
    int    mCount;                     // 0x1e0c

    // methods in this slice
    bool StartEmitter(float param);                  // 0x00a1b480
    bool Init();                                     // 0x00a1b730
    bool Start(double time);                         // 0x00a1b8a0
    bool Stop(int reason, bool force);               // 0x00a1bba0
    bool ShutdownImpl();                             // 0x00a1be10
    int  Pause(bool pause, u32 index, float fade, bool force); // 0x00a1bf50
    void UpdateGainAndDistance(float param);         // 0x00a1c120
    bool CalculateDistanceToListener();              // 0x00a1c290
    bool CreateEmitter();                            // 0x00a1c2f0
};

struct Emitter {
    void SetCurveGain(float v);                 // 0x00a16fd0
};
struct RCurve {
    u8 mData[0x364];
    float GetOutputValue(float in) const;       // 0x00a1a110
};

// ===========================================================================
// 0x00a1b660  LerpF::Set -- set target, derive fade rate from value/current.
// ===========================================================================
// @ 0x00a1b660
void LerpF::Set(const float& value, float rate)
{
    float v = value;
    mTarget = v;
    float d = (float)fabs(v - mCurrent);
    if (rate != 0.0f && !(1e-06 > d))
        mRate = d / rate;
    else
        mCurrent = value;
}

// ===========================================================================
// 0x00a1b480  Sound::StartEmitter
// ===========================================================================
// @ 0x00a1b480
bool Sound::StartEmitter(float param)
{
    ((void(__thiscall*)(Sound*, float))VTSLOT(this, 0x5c))(this, param);

    u32 f = mFlags;
    if (f & 0x20)
        return true;
    if ((int)f < 0)
        return false;

    if (mb9f != 0) {
        if (((bool(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x20))(this, -1, 0))
            return false;
    }

    if ((mMode & 8) != 0 && mStartDelay > g_1486110 && mb9d == 0) {
        ((void(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x80))(this, 4, 1);
        return false;
    }

    if (mpEmitter == 0) {
        if (!((bool(__thiscall*)(Sound*))VTSLOT(this, 0x6c))(this))
            goto fail;
        if (!((bool(__thiscall*)(void*))VTSLOT(mpEmitter, 0x10))(mpEmitter))
            goto fail;
    }

    if (!((bool(__thiscall*)(void*))VTSLOT(mpEmitter, 0x48))(mpEmitter))
        return false;

    {
        void* em = mpEmitter;
        ((void(__thiscall*)(void*, u32))VTSLOT(em, 0x24))(em, mInstanceId);
        float local;
        if (((bool(__thiscall*)(Sound*, u32, float*))VTSLOT(this, 0xac))(this, 0x98ac8996, &local))
            mC98 = local;
        mCB0 = 1;
        mCB4 = 0.0f;
        mCAC = 1;
        ((void(__thiscall*)(void*, int))VTSLOT(em, 0x3c))(em, 0);
        if (((bool(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x20))(this, -1, 1))
            ((void(__thiscall*)(void*, int))VTSLOT(em, 0x1c))(em, 1);
        ((void(__thiscall*)(Sound*))VTSLOT(this, 0x7c))(this);
        ((void(__thiscall*)(Sound*, float, float, int))VTSLOT(this, 0x9c))(this, 0.0f, 0.0f, 1);
        if (mFlags & 0x80)
            return false;
        if (((bool(__thiscall*)(void*, double))VTSLOT(em, 0x14))(em, mCC8)) {
            float l2;
            if (((bool(__thiscall*)(void*, u32, float*))VTSLOT(em, 0x30))(em, 0xba03d0cd, &l2))
                mCD8 = (u32)(long long)l2;
            mStartDelay = 0.0f;
            mFlags |= 0x20;
            return true;
        }
        goto fail;
    }

fail:
    ((void(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x80))(this, 4, 0);
    return false;
}

// ===========================================================================
// 0x00a1b730  Sound::Init
// ===========================================================================
// @ 0x00a1b730
bool Sound::Init()
{
    void* sys = GetSystemAT();
    if (sys == 0)
        return false;
    if (mFlags & 1)
        return true;
    mFlags |= 1;

    void* local = 0;
    ((void(__thiscall*)(void*, u32, void**, int))VTSLOT(sys, 0x138))(sys, 0x25238ae2, &local, 0x21407ee);
    ((void(__thiscall*)(void*, void*))VTSLOT((char*)this + 0xe4, 0x24))((char*)this + 0xe4, local);

    mPauseFader.mTarget = g_1485720;
    mPauseFader.mCurrent = g_1485720;
    mPauseFader.mRate = 0.0f;
    mPauseCount = 0;
    *(u32*)((char*)this + 0x1de4) = 0;
    *(u32*)((char*)this + 0x1de8) = 0;

    ((void(__thiscall*)(void*, void*, int, int))VTSLOT(sys, 0x184))(sys, (char*)this + 0x1e0c, 0, 0);

    ((void(__thiscall*)(Sound*))VTSLOT(this, 0x34))(this);
    mStartDelay = 0.0f;
    mElapsed = 0.0f;
    mMode = 0;
    mPauseGain = g_13eb1bc;
    if (!((bool(__thiscall*)(Sound*))VTSLOT(this, 0x34))(this)) {
        if (local)
            ((void(__thiscall*)(void*))VTSLOT(local, 4))(local);
        return false;
    }
    if (!(mFlags & 0x2000)) {
        if (!((bool(__thiscall*)(void*, Sound*))VTSLOT(sys, 0x164))(sys, this)) {
            if (local)
                ((void(__thiscall*)(void*))VTSLOT(local, 4))(local);
            return false;
        }
        mFlags |= 0x2000;
    }
    if (local)
        ((void(__thiscall*)(void*))VTSLOT(local, 4))(local);
    return true;
}

// ===========================================================================
// 0x00a1b8a0  Sound::Start
// ===========================================================================
// @ 0x00a1b8a0
bool Sound::Start(double time)
{
    if (mFlags & 0x10) {
        if (mb9d != 0 || mC90 != 0)
            return true;
        mStartDelay = 0.0f;
        mElapsed = 0.0f;
        mPauseGain = g_13eb1bc;
        if (mpEmitter != 0) {
            int a = *(int*)((char*)this + 0x40);
            int b = *(int*)((char*)this + 0xe0);
            struct { int a, b, c; } loc;
            loc.a = a; loc.b = b; loc.c = 0x21407ee;
            ((void(__thiscall*)(void*, void*))VTSLOT(mpEmitter, 0x28))(mpEmitter, &loc);
        }
        mFlags &= ~0xa0u;
    }

    if (mFlags & 0x80)
        return false;

    void* sys = GetSystemAT();
    if (sys == 0) {
        ((void(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x80))(this, 4, 0);
        return false;
    }

    double d = time;
    if (d == 0.0 && g_16e61a8 != 0)
        d = *(double*)((char*)g_16e61a8 + 8);
    mCC8 = d + (double)m328;

    void* local = 0;
    if (mbDirect != 0 && ((bool(__thiscall*)(void*, Sound*, void**))VTSLOT(sys, 0x150))(sys, this, &local)) {
        ((void(__thiscall*)(void*, Sound*))VTSLOT(local, 0xb8))(local, this);
        ((void(__thiscall*)(void*))VTSLOT(local, 4))(local);
        float v;
        if (((bool(__thiscall*)(Sound*, u32, float*))VTSLOT(this, 0xac))(this, 0x98ac8996, &v))
            mC98 = v;
        mCB0 = 1;
        mCB4 = 0.0f;
        mCAC = 1;
        goto started;
    }

    if (mCount >= 2) {
        float v;
        if (((bool(__thiscall*)(Sound*, u32, float*))VTSLOT(this, 0xac))(this, 0x56e7c242, &v)) {
            int r = rand();
            float x = ((float)r * (v * 2.0f)) * g_140d4f8 - v;
            float one = 1.0f;
            ((void(__thiscall*)(Sound*, u32, float*))VTSLOT(this, 0xac))(this, 0x71bc3009, &one);
            mPitch = one + x;
        }
    }

    {
        void* mix = (char*)this + 4;
        if (((bool(__thiscall*)(void*, u32))VTSLOT(mix, 0x14))(mix, 0x66ef9aba)
            && ((bool(__thiscall*)(void*, u32))VTSLOT(mix, 0x14))(mix, 0xe4dd1818)
            && ((bool(__thiscall*)(void*, u32))VTSLOT(mix, 0x14))(mix, 0xcd928a9)) {
            if (!((bool(__thiscall*)(Sound*))VTSLOT(this, 0x90))(this)) {
                ((void(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x80))(this, 4, 0);
                return false;
            }
            if ((mFlags & 0x10) && mpEmitter != 0) {
                float f = (float)*(int*)((char*)this + 0x40);
                int b = *(int*)((char*)this + 0xe0);
                struct { float f; int b, c; } loc2;
                loc2.f = f; loc2.b = b; loc2.c = 0x21407ee;
                ((void(__thiscall*)(void*, void*))VTSLOT(mpEmitter, 0x28))(mpEmitter, &loc2);
            }
        }
    }

    ((void(__thiscall*)(Sound*, int))VTSLOT(this, 0x70))(this, 0);
    if ((int)mFlags < 0)
        return false;
    if (!(mFlags & 8)) {
        ((void(__thiscall*)(void*, Sound*))VTSLOT(sys, 0x70))(sys, this);
        mFlags |= 8;
    }

started:
    if (!(mFlags & 0x10)) {
        ((void(__thiscall*)(Sound*))VTSLOT(this, 0))(this);
        mFlags |= 0x10;
    }
    return true;
}

// ===========================================================================
// 0x00a1bba0  Sound::Stop
// ===========================================================================
// @ 0x00a1bba0
bool Sound::Stop(int reason, bool force)
{
    if (mFlags & 0x200) {
        if (!force)
            return true;
        goto finalstop;
    }

    bool hard = (mbHardStop != 0) || force;
    mStopReason = reason;
    mbHardStop = hard;
    if (!hard && reason == 2 && (mFlags & 0x10)) {
        bool b = false;
        if (((bool(__thiscall*)(void*, u32, bool*))VTSLOT((char*)this + 0xe4, 0x24))((char*)this + 0xe4, 0xaeb34f7, &b)) {
            if (b && mb9d == 0)
                return true;
        }
    }

    mFlags |= 0x280;

    void* sys = GetSystemAT();
    if (sys != 0) {
        if (mStopReason == 0) {
            if (mCD5 != 0) {
                ((void(__thiscall*)(void*, Sound*))VTSLOT(sys, 0x168))(sys, this);
                ((void(__thiscall*)(void*, void*))VTSLOT(sys, 0x170))(sys, (char*)this + 4);
                mFlags &= ~0x2000u;
                void* arc = 0;
                if (((bool(__thiscall*)(void*, u32, u32, u32, void*, void*))VTSLOT(sys, 0x94))
                        (sys, mSoundId, mInstanceId, *(u32*)((char*)this + 0xf0), (char*)this + 0xa8, &arc)) {
                    ((void(__thiscall*)(void*, double))VTSLOT(arc, 0x14))(arc, 0.0);
                }
                if (arc)
                    ((void(__thiscall*)(void*))VTSLOT(arc, 4))(arc);
            }
            if (mStopReason == 0 && mCD5 != 0)
                goto after;
        }
        ((void(__thiscall*)(void*, u32, u32, int, int, int))VTSLOT(sys, 0x128))(sys, 0x3a129e8, mInstanceId, 0, 0, 0);
    }

after:
    if (mFlags & 0x10) {
        if (!((bool(__thiscall*)(Sound*, int, int))VTSLOT(this, 0x20))(this, -1, 1)) {
            float v;
            if (((bool(__thiscall*)(Sound*, u32, float*))VTSLOT(this, 0xac))(this, 0xe8ab99b9, &v)
                && mbHardStop == 0
                && ((mbDirect != 0 && mC90 != 0
                     && ((*(u32*)((char*)mC90 + 0xce4) & 0x20) != 0))
                    || (mFlags & 0x20))) {
                mCA8 = v;
                mCB0 = 1;
                mCB4 = 0.0f;
                mCAC = 5;
                mFlags |= 0x40;
                return true;
            }
        }
    }

finalstop:
    return ((bool(__thiscall*)(Sound*))VTSLOT(this, 0x8c))(this);
}

// ===========================================================================
// 0x00a1be10  Sound::ShutdownImpl (emitter teardown, slot 0x8c)
// ===========================================================================
// @ 0x00a1be10
bool Sound::ShutdownImpl()
{
    if (mbDirect) {
        if (mStopReason == 0 || mStopReason == 4) {
            ((void(__thiscall*)(Sound*))VTSLOT(this, 0xd0))(this);
        } else if (mC7c != mC80) {
            ((void(__thiscall*)(Sound*))VTSLOT(this, 0xcc))(this);
        }
        void* e2 = mC90;
        if (e2 != 0)
            ((void(__thiscall*)(void*, Sound*))VTSLOT(e2, 0xbc))(e2, this);
    }

    if (mpEmitter != 0) {
        ((void(__thiscall*)(void*))VTSLOT(mpEmitter, 0x18))(mpEmitter);
        ((void(__thiscall*)(void*, int))VTSLOT(mpEmitter, 0x38))(mpEmitter, 0);
        void* e = mpEmitter;
        if (e != 0) {
            mpEmitter = 0;
            ((void(__thiscall*)(void*))VTSLOT(e, 4))(e);
        }
        mFlags &= ~0x20u;
    }

    void* sys = GetSystemAT();
    if (sys != 0) {
        if (mFlags & 8) {
            mFlags &= ~8u;
            ((void(__thiscall*)(void*, Sound*))VTSLOT(sys, 0x74))(sys, this);
        }
        ((void(__thiscall*)(void*, void*))VTSLOT(sys, 0x114))(sys, (char*)this + 4);
        if (mFlags & 0x2000) {
            mFlags &= ~0x2000u;
            ((void(__thiscall*)(void*, Sound*))VTSLOT(sys, 0x168))(sys, this);
        }
    }

    ((void(__thiscall*)(Sound*))VTSLOT(this, 0x10))(this);
    if (mStopReason != 0 || mCD5 == 0)
        ((void(__thiscall*)(void*, u32, u32, int, int, int))VTSLOT(sys, 0x128))(sys, 0x3a129ee, mInstanceId, 0, 0, 0);

    if (mFlags & 0x10) {
        mFlags &= ~0x10u;
        ((void(__thiscall*)(Sound*))VTSLOT(this, 4))(this);
    }
    return true;
}

// ===========================================================================
// 0x00a1bf50  Sound::Pause
// ===========================================================================
// @ 0x00a1bf50
int Sound::Pause(bool pause, u32 index, float fade, bool force)
{
    if (index < mNumPauseCounters) {
        if (pause) {
            if (force || mPauseCounts[index] == 0) {
                ++mPauseCount;
                ++mPauseCounts[index];
            }
            if (fade < 0.0f) {
                if (!((bool(__thiscall*)(Sound*, u32, float*))VTSLOT(this, 0xac))(this, 0xe8ab99b9, &fade))
                    fade = g_13eb95c;
            }
            if (mpEmitter == 0 || ((bool(__thiscall*)(void*))VTSLOT(mpEmitter, 0x20))(mpEmitter)) {
                fade = 0.0f;
            } else if (fade != 0.0f) {
                mFlags |= 0x800;
            } else {
                mFlags &= ~0x800u;
                ((void(__thiscall*)(void*, int))VTSLOT(mpEmitter, 0x1c))(mpEmitter, 1);
            }
            float zero = 0.0f;
            mPauseFader.Set(zero, fade);
            return mPauseCount;
        }

        if ((mFlags & 0x80) == 0 && mPauseCounts[index] > 0) {
            --mPauseCount;
            --mPauseCounts[index];
            if (mPauseCount == 0) {
                mFlags &= ~0x800u;
                if (index == 3 || index == 2) {
                    fade = 0.0f;
                } else if (fade < 0.0f) {
                    if (!((bool(__thiscall*)(Sound*, u32, float*))VTSLOT(this, 0xac))(this, 0xe8ab99b9, &fade))
                        fade = g_13eb95c;
                }
                float one = 1.0f;
                mPauseFader.Set(one, fade);
                if (mpEmitter != 0) {
                    ((void(__thiscall*)(void*, int))VTSLOT(mpEmitter, 0x1c))(mpEmitter, 0);
                    ((void(__thiscall*)(Sound*))VTSLOT(this, 0x7c))(this);
                    ((void(__thiscall*)(Sound*, float, float, int))VTSLOT(this, 0x9c))(this, 0.0f, 0.0f, 1);
                }
            }
        }
    }
    return mPauseCount;
}

// ===========================================================================
// 0x00a1c120  Sound::UpdateGainAndDistance (slot 0x5c)
// ===========================================================================
// @ 0x00a1c120
void Sound::UpdateGainAndDistance(float param)
{
    float gain;
    if (mMode == 0xf) {
        if (mbDirect) {
            void* sys = GetSystemAT();
            Vec3* p = (Vec3*)((void*(__thiscall*)(void*, u32))VTSLOT(sys, 0x7c))(sys, mPosHandle);
            ((void(__thiscall*)(Sound*, float, Vec3*))VTSLOT(this, 0xd8))(this, param, p);
            gain = mDirGain1;
            float dx = mDirectPos.x - p->x;
            float dy = mDirectPos.y - p->y;
            float dz = mDirectPos.z - p->z;
            mEffectiveGain = mDirGain0 * gain;
            mDistanceToListener = (float)fabs((float)sqrt(dx * dx + dy * dy + dz * dz));
        } else {
            void* sys = GetSystemAT();
            Vec3* p = (Vec3*)((void*(__thiscall*)(void*, u32))VTSLOT(sys, 0x7c))(sys, mPosHandle);
            float dx = mPos.x - p->x;
            float dy = mPos.y - p->y;
            float dz = mPos.z - p->z;
            mDistanceToListener = (float)fabs((float)sqrt(dx * dx + dy * dy + dz * dz));
            gain = ((float(__thiscall*)(Sound*))VTSLOT(this, 0x68))(this);
            mEffectiveGain = gain * mMaxGainChange;
        }
        if (mDistanceToListener != mLastDistance)
            mb9e = 1;
        mLastDistance = mDistanceToListener;
    } else {
        gain = ((float(__thiscall*)(Sound*))VTSLOT(this, 0x68))(this);
        mEffectiveGain = gain * mMaxGainChange;
    }

    if (mC38 != 0) {
        float fade = mPauseFader.mCurrent;
        float g = ((LerpF*)((char*)this + 0xc94))->Get() * fade * gain;
        float out = ((RCurve*)((char*)this + 0x1a7c))->GetOutputValue(g);
        ((Emitter*)mC38)->SetCurveGain(out);
    }
}

// ===========================================================================
// 0x00a1c290  Sound::CalculateDistanceToListener
// ===========================================================================
// @ 0x00a1c290
bool Sound::CalculateDistanceToListener()
{
    void* e = mC90;
    if (e == 0)
        return false;
    ((void(__thiscall*)(void*, Sound*))VTSLOT(e, 0xbc))(e, this);
    if (!(mFlags & 0x10)) {
        ((void(__thiscall*)(Sound*))VTSLOT(this, 0))(this);
        mFlags |= 0x10;
    }
    if (!(mFlags & 8)) {
        void* sys = GetSystemAT();
        ((void(__thiscall*)(void*, Sound*))VTSLOT(sys, 0x70))(sys, this);
        mFlags |= 8;
    }
    return true;
}

// ===========================================================================
// 0x00a1c2f0  Sound::CreateEmitter
// ===========================================================================
// @ 0x00a1c2f0
bool Sound::CreateEmitter()
{
    void* sys = GetSystemAT();
    if (sys == 0)
        return false;
    u32 id = mSampleId;
    if (id == 0)
        id = mSoundId;

    bool have = ((bool(__thiscall*)(void*, u32, void**))VTSLOT((char*)this + 0xe4, 0x2c))((char*)this + 0xe4, 0x6610c2bd, (void**)&mEmitterType);
    if (!have)
        have = ((bool(__thiscall*)(void*, u32, void**))VTSLOT(sys, 0x178))(sys, id, (void**)&mEmitterType);
    if (have) {
        void* arc = 0;
        if (((bool(__thiscall*)(void*, void*, void**))VTSLOT(sys, 0x180))(sys, (void*)mEmitterType, &arc)) {
            struct { int a, b, c; } loc;
            loc.a = (int)id; loc.b = (int)mEmitterType; loc.c = 0x21407ee;
            ((void(__thiscall*)(void*, void*))VTSLOT(arc, 0x28))(arc, &loc);
            ((void(__thiscall*)(void*, void*))VTSLOT(arc, 0x38))(arc, (char*)this + 0xe4);
            u32 rt = ((u32(__thiscall*)(Sound*))VTSLOT(this, 0x54))(this);
            ((void(__thiscall*)(void*, u32))VTSLOT(arc, 0x24))(arc, rt);
            if (((bool(__thiscall*)(void*))VTSLOT(arc, 8))(arc)) {
                ((void(__thiscall*)(void*, void*))0xac9480)((char*)this + 0x44, &arc);
                return true;
            }
            if (arc)
                ((void(__thiscall*)(void*))VTSLOT(arc, 4))(arc);
        }
    }
    return false;
}
