// slice s0059acb0 -- SP::cSPEditorAnimatedEventInfo / cSPEditorAnimatedCreatureData helpers: refcount
// pointer assignment, event-flag setters, orientation quaternion helpers.  Retail layout, offsets
// taken from the disassembly.  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>
#include <intrin.h>

void operator delete(void* p);                                                 // 0x00f47380

namespace Simulator {

class cAnimatingCreature {
public:
    char pad0[0x70];
    uint32_t mFlags;                // +0x70
    char pad74[0x150 - 0x74];
    uint8_t mByte150;               // +0x150
    void AddRef();                  // 0x00a02c30
    void Release();                 // 0x00a05270
    bool IsSomething(int a);        // 0x00a02b20
};

// Reference-counted pointer wrapper: object pointer at +0.
struct AnimatingCreatureRef {
    cAnimatingCreature* mpObject;
    AnimatingCreatureRef& operator=(cAnimatingCreature* p);   // 0x0059acb0
};

// The animated-event/creature data object touched by this slice.
class cAnimatedData {
public:
    virtual void slot0();           // vptr at +0
    int mField04;                   // +0x04
    cAnimatingCreature* mpCreature; // +0x08
    int mField0c;                   // +0x0c
    int mField10, mField14, mField18;   // +0x10..0x18
    int mField1c;                   // +0x1c
    float mVec0[3];                 // +0x20
    float mVec1[3];                 // +0x2c
    float mVec2[3];                 // +0x38
    float mField44, mField48;       // +0x44, +0x48
    float mField4c;                 // +0x4c
    float mField50;                 // +0x50
    bool mField54, mField55;        // +0x54, +0x55
    float mField58, mField5c, mField60;   // +0x58 target
    float mField64, mField68, mField6c;   // +0x64 copy
    bool mField70;                  // +0x70
    float mField74, mField78, mField7c;   // +0x74..0x7c
    float mField80;                 // +0x80
    bool mField84;                  // +0x84

    void FUN_0059ae20(cAnimatingCreature* p, int a);   // 0x0059ae20
    void FUN_0059ae60();                               // 0x0059ae60
    bool FUN_0059ae80();                               // 0x0059ae80
    void FUN_0059aea0(char b);                         // 0x0059aea0
    void* FUN_0059ace0();                              // 0x0059ace0
    void* FUN_0059b0b0(char flags);                    // 0x0059b0b0
    void FUN_0059b2f0(float angle, char update);       // 0x0059b2f0
    void FUN_0059b390();                               // 0x0059b390
    void FUN_0059b420(char b);                         // 0x0059b420
    void FUN_0059aed0(float* out, const float* q, const float* v);  // 0x0059aed0
    void SetTargetPosition(int a, float angle);        // 0x0059b0f0
};

}  // namespace Simulator

using namespace Simulator;

extern char gAnimVtblA[];   // 0x013f64b4
extern char gAnimVtblB[];   // 0x013ef094
extern float gAnimVecX;     // 0x015e590c
extern float gAnimVecY;     // 0x015e5910
extern float gAnimVecZ;     // 0x015e5914
extern float gAnimScale;    // 0x015e5984
extern float gAnimHalf;     // 0x01471064
extern float gAnim2_5;      // 0x013f6488
extern float gAnimB0;       // 0x013f561c
extern float gAnimB1;       // 0x01485720

// @ 0x0059acb0
AnimatingCreatureRef& AnimatingCreatureRef::operator=(cAnimatingCreature* p)
{
    cAnimatingCreature* old = mpObject;
    if (p != old) {
        if (p)
            p->AddRef();
        mpObject = p;
        if (old)
            old->Release();
    }
    return *this;
}

// @ 0x0059ae20
void cAnimatedData::FUN_0059ae20(cAnimatingCreature* p, int a)
{
    mField0c = a;
    cAnimatingCreature* old = mpCreature;
    if (p != old) {
        if (p)
            p->AddRef();
        mpCreature = p;
        if (old)
            old->Release();
    }
    mField1c = 0;
}

// @ 0x0059ae60
void cAnimatedData::FUN_0059ae60()
{
    mField0c = 0;
    _ReadWriteBarrier();
    if (mpCreature) {
        cAnimatingCreature* p = mpCreature;
        mpCreature = 0;
        p->Release();
    }
}

// @ 0x0059ae80
bool cAnimatedData::FUN_0059ae80()
{
    if (mpCreature->IsSomething(0))
        return true;
    return mField70;
}

// @ 0x0059aea0
void cAnimatedData::FUN_0059aea0(char b)
{
    cAnimatingCreature* p = mpCreature;
    if (p) {
        p->mByte150 = b;
        p = mpCreature;
        if (b)
            p->mFlags |= 0x80;
        else
            p->mFlags &= ~0x80u;
    }
}

// @ 0x0059ace0
void* cAnimatedData::FUN_0059ace0()
{
    *(void**)this = (void*)gAnimVtblA;
    mField04 = 0;
    mpCreature = 0;
    mField0c = 0;
    mField10 = 0;
    mField14 = 0;
    mField18 = 0;
    mField1c = 0;
    mVec0[0] = gAnimVecX; mVec0[1] = gAnimVecY; mVec0[2] = gAnimVecZ;
    mVec1[0] = gAnimVecX; mVec1[1] = gAnimVecY; mVec1[2] = gAnimVecZ;
    mVec2[0] = gAnimVecX; mVec2[1] = gAnimVecY; mVec2[2] = gAnimVecZ;
    mField44 = 0.0f;
    mField48 = 0.0f;
    mField4c = gAnim2_5;
    mField50 = gAnimScale;
    mField54 = false;
    mField55 = false;
    mField58 = gAnimVecX; mField5c = gAnimVecY; mField60 = gAnimVecZ;
    mField64 = gAnimVecX; mField68 = gAnimVecY; mField6c = gAnimVecZ;
    mField74 = 0.0f;
    mField78 = 0.0f;
    mField7c = 0.0f;
    mField70 = true;
    mField80 = gAnimHalf;
    mField84 = false;
    return this;
}

// @ 0x0059b0b0
void* cAnimatedData::FUN_0059b0b0(char flags)
{
    *(void**)this = (void*)gAnimVtblA;
    _ReadWriteBarrier();
    if (mpCreature)
        mpCreature->Release();
    *(void**)this = (void*)gAnimVtblB;
    if (flags & 1)
        operator delete(this);
    return this;
}

// @ 0x0059b2f0
void cAnimatedData::FUN_0059b2f0(float angle, char update)
{
    mField44 = angle;
    if (update) {
        cAnimatingCreature* p = mpCreature;
        mField48 = angle;
        float s = sinf(angle * 0.5f);
        float c = cosf(angle * 0.5f);
        *(float*)((char*)p + 0x10) = gAnimVecX * s;
        *(float*)((char*)p + 0x14) = gAnimVecY * s;
        *(float*)((char*)p + 0x18) = gAnimVecZ * s;
        *(float*)((char*)p + 0x1c) = c;
    }
}

// @ 0x0059b390
void cAnimatedData::FUN_0059b390()
{
    cAnimatingCreature* p = mpCreature;
    if (p) {
        float q[3] = { 0.0f, -1.5f, 0.5f };
        float tmp[4];
        FUN_0059aed0(tmp, q, (const float*)((char*)p + 0x10));
        mField58 = tmp[0] + *(float*)((char*)p + 4);
        mField5c = tmp[1] + *(float*)((char*)p + 8);
        mField60 = tmp[2] + *(float*)((char*)p + 0xc);
        mField64 = mField58;
        mField68 = mField5c;
        mField6c = mField60;
    }
}

// @ 0x0059b420
void cAnimatedData::FUN_0059b420(char b)
{
    cAnimatingCreature* p = mpCreature;
    if (p) {
        if (b) {
            *(int*)((char*)p + 0x154) = 2;
            if (!mField55) {
                FUN_0059b390();
                mField55 = b;
                return;
            }
        } else {
            *(int*)((char*)p + 0x154) = 1;
            cAnimatingCreature* q = mpCreature;
            *(float*)((char*)q + 0x164) = 0.0f;
            *(float*)((char*)q + 0x168) = gAnimB0;
            *(float*)((char*)q + 0x16c) = gAnimB1;
        }
        mField55 = b;
    }
}

// @ 0x0059b0f0
// PARTIAL: 503 B target-position/ground clamp; skeleton only.
void cAnimatedData::SetTargetPosition(int a, float angle) { (void)a; (void)angle; }

// @ 0x0059aed0
// PARTIAL: 392 B quaternion/matrix transform; skeleton only.
void cAnimatedData::FUN_0059aed0(float* out, const float* q, const float* v) { (void)out; (void)q; (void)v; }

// @ 0x0059b060
// Axis/angle -> quaternion (free function).
void SetQuaternionFromAxisAngle(float* out, const float* axis, float angle)
{
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    out[0] = axis[0] * s;
    out[1] = axis[1] * s;
    out[2] = axis[2] * s;
    out[3] = c;
}
