// FUN_00d896f0 (0x00d896f0, 248 bytes): creature update step. Clears stealth, builds a
// 0x74-byte locomotion request from the creature's default facing vector and the record's
// own defaults, submits it through the embedded body's vtable slot 0x37 (+0xdc). The callee
// fills the record's first word (a vector-style buffer), which is freed here if non-null with
// a non-zero header word. Then the behaviour-tree object (+0xb4c) gets FUN_00bcb430 and the
// creature's Hover(false) runs.
//
// The defaults live in the request's constructor, exactly as the matched
// cLocomotionRequest::cLocomotionRequest (0x00ac9850) writes them: the three vector lanes are
// passed in, 1.0f at +0x20, zeros elsewhere, 2.0f at +0x60, 0.9f at +0x64 and FLT_MAX at
// +0x68 (the +0x68 value is a float literal in the original, so it keeps its own .rdata slot).
// The three lanes at +0x14/+0x18/+0x1c hold the creature's default facing, a writable global
// vector at 0x169f03c.
//
// Free function (cdecl, one stack argument: the creature; the caller pops it).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <float.h>    // FLT_MAX

typedef uint32_t uint32;

// 0x00f47380: operator delete (cdecl, one argument).
void operator_delete__(void* p);

// Default facing vector, three consecutive floats at 0x169f03c (writable .data).
struct Vec3 {
    float x, y, z;
};
extern Vec3 g_defaultFacing;

// Behaviour-tree object at creature +0xb4c. Only FUN_00bcb430 is used here (0x00bcb430, thiscall).
struct cBehaviorTreeObj {
    void FUN_00bcb430();
};

// 0x74-byte request record passed by pointer to the locomotion virtual call.
struct cLocoRequest {
    void*  mpBegin;                 // +0x00 (callee fills; buffer freed by the caller)
    void*  mpEnd;                   // +0x04
    void*  mpCapacity;              // +0x08
    uint32 pad0c[(0x14 - 0x0c) / 4];
    float  mfVec0;                  // +0x14
    float  mfVec1;                  // +0x18
    float  mfVec2;                  // +0x1c
    float  mfScalar;                // +0x20
    uint32 pad24;                   // +0x24
    uint32 pad28[(0x4c - 0x28) / 4];
    uint8_t mbFlag;                 // +0x4c
    uint8_t pad4d[3];
    float  mfZero50;                // +0x50
    float  mfZero54;                // +0x54
    float  mfZero58;                // +0x58
    uint32 mZero5c;                 // +0x5c
    float  mf60;                    // +0x60
    float  mf64;                    // +0x64
    float  mf68;                    // +0x68
    float  mfZero6c;                // +0x6c
    uint32 mZero70;                 // +0x70

    cLocoRequest(float x, float y, float z);
};

// Same statement order as the out-of-line original (0x00ac9850).
inline cLocoRequest::cLocoRequest(float x, float y, float z)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mfVec0 = x;
    mfVec1 = y;
    mfVec2 = z;
    mfScalar = 1.0f;
    pad24 = 0;
    mbFlag = 0;
    mfZero50 = 0.0f;
    mfZero54 = 0.0f;
    mfZero58 = 0.0f;
    mf60 = 2.0f;
    mf64 = 0.9f;
    mZero5c = 0;
    mf68 = FLT_MAX;
    mfZero6c = 0.0f;
    mZero70 = 0;
}

// Embedded locomotion body at creature +0xc0 (its vptr is the first word there). Slot 55
// (vtable byte +0xdc) submits a filled request record.
class cLocoBody {
 public:
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();  virtual void s4();
    virtual void s5();  virtual void s6();  virtual void s7();  virtual void s8();  virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void Submit(cLocoRequest const& req);   // +0xdc (slot 55)
};

// Creature (cSPCreatureBase), only the members this step touches.
struct cSPCreatureBase {
    char pad00[0xc0];
    cLocoBody mBody;                    // +0xc0 (embedded; its vptr is at +0xc0)
    char padC4[0xb4c - 0xc4];
    cBehaviorTreeObj* mpBehavior;       // +0xb4c

    void SetStealthed(bool a, bool b);  // 0x00c1aed0 (thiscall, ret 8)
    void Hover(bool b);                 // 0x00c13a30 (thiscall, ret 4)
};

// @ 0x00d896f0
void FUN_00d896f0(cSPCreatureBase* self)
{
    self->SetStealthed(false, false);

    // Defaults from the request's constructor, facing lanes from the creature's default vector.
    cLocoRequest req(g_defaultFacing.x, g_defaultFacing.y, g_defaultFacing.z);

    // Locomotion body's vtable slot +0xdc, submitted with the filled record.
    self->mBody.Submit(req);

    void* buf = req.mpBegin;
    if (buf != 0 && ((int*)buf)[-1] != 0)
        operator_delete__(buf);

    self->mpBehavior->FUN_00bcb430();
    self->Hover(false);
}
