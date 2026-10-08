// s0100f3e0: one function, 0x0100f930 (457 bytes), SP::BiosphereCollapseEvent::GetEventFrequency.
// thiscall float(uint64 dtMs) ret 8. Accumulates elapsed time into mTimeSinceLastEvent, then returns
// 1 - 2^(-log10(2) * dt / rate), where rate is a per-second frequency from two properties and two
// game getters; returns 0 when the event is not yet due or the rate is not positive.
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100 4035)

struct Property {
    char pad0[0x12];
    uint16_t mType;                             // +0x12, 0xD = float
    float* GetFloat();                          // 0x0041ea70, thiscall, no args
};

// Property manager at SimUniverse+0x10. Slot +0x24 (index 9) looks up a property by id.
struct cPropertyManager {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24, thiscall ret 8
};

struct cSimUniverse {
    char pad0[0x10];
    cPropertyManager* mpProps;                  // +0x10
};
extern cSimUniverse* gSimUniverse;              // 0x016dc798

// Space list read by the rate formula: count = ((mEnd - mBegin) >> 2) - mOffset.
struct cSpaceList {
    char pad0[0x2c];
    int32_t mBegin;                             // +0x2c
    int32_t mEnd;                               // +0x30
    char pad1[0x100 - 0x34];
    int32_t mOffset;                            // +0x100
};

struct cSpaceGame {
    char pad0[0x30];
    cSpaceList* mpList;                         // +0x30
    char pad1[0xc4 - 0x34];
    uint32_t mFlags;                            // +0xc4
    float Scale(int id);                        // 0x01005c60, thiscall ret 4
};
cSpaceGame* SpaceGameGet();                     // 0x01002bd0, cdecl no args

struct cTerrainSphere {
    float Measure();                            // 0x00c75c30, thiscall no args
};
struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();  // 0x00f67d90, thiscall
};
// SP::NounManager(id) returns the manager object for a noun id (callee pops its arg).
cTerrainEditor* NounManager(uint32_t id);       // 0x00b3d300

struct BiosphereCollapseEvent {
    virtual void s0();
    float mTimeSinceLastEvent;                  // +4
    float GetEventFrequency(uint64_t dtMs);     // 0x0100f930, thiscall ret 8
};

float BiosphereCollapseEvent::GetEventFrequency(uint64_t dtMs)
{
    float dt = (float)dtMs * 0.001f;
    mTimeSinceLastEvent = mTimeSinceLastEvent + dt;

    float threshold = 0.0f;
    Property* prop = 0;
    if (gSimUniverse->mpProps && gSimUniverse->mpProps->GetProperty(0x4488192, &prop) && prop->mType == 0xd)
        threshold = *prop->GetFloat();
    if (mTimeSinceLastEvent <= threshold)
        return 0.0f;

    cSpaceList* list = SpaceGameGet()->mpList;
    int count = ((list->mEnd - list->mBegin) >> 2) - list->mOffset;

    float mult = 0.0f;
    Property* prop2 = 0;
    if (gSimUniverse->mpProps && gSimUniverse->mpProps->GetProperty(0x44881a3, &prop2) && prop2->mType == 0xd)
        mult = *prop2->GetFloat();
    if (SpaceGameGet()->mFlags & 0x800)
        mult = SpaceGameGet()->Scale(0xb) * mult;
    mult = NounManager(0xc42edf05)->GetCurrentTerrainSphere()->Measure() * mult;

    if (count < 1)
        return 0.0f;
    float rate = mult / (float)count;
    if (rate <= 0.0f)
        return 0.0f;

    // 1 - 2^(log2(e) * (dt / rate) * -0.30103) on the x87 stack; the result stays in ST(0).
    static const float kNegLog10Two = -0.30103f;
    float res;
    __asm {
        fld dword ptr [dt]
        fdiv dword ptr [rate]
        fmul dword ptr [kNegLog10Two]
        fldl2e
        fmulp st(1), st
        fld st(0)
        frndint
        fxch st(1)
        fsub st, st(1)
        f2xm1
        fld1
        faddp st(1), st
        fscale
        fstp st(1)
        fld1
        fsubrp st(1), st
        fstp dword ptr [res]
        fld dword ptr [res]
    }
}
