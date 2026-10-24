// Slice s00c4bc00 -- SP mission variants (eradicate / biosphere): state changes, disease effect ids
// and the property-key lookups they perform.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

struct tGridPos {
    uint32_t mA;                                        // +0x00
    uint32_t mB;                                        // +0x04
    uint32_t mC;                                        // +0x08
};

// property helpers
class IProperty;
bool __cdecl GetPropertyAsKey(IProperty* pProperty, uint32_t keyId, void* pOut); // 0x006a1250

// 16-bit vector (begin/end/end-capacity)
struct tUShortVector {
    uint16_t* mpBegin;                                  // +0x00
    uint16_t* mpEnd;                                    // +0x04
    uint16_t* mpCapacity;                               // +0x08
};

// shared layout and helpers of the mission UI objects
class cSPMissionBase {
public:
    void SetSerializer();                               // 0x00c2e4e0
    void TriggerUIUpdate();                             // 0x00c47d80
    void FUN_00c48db0(tUShortVector* pVector);          // 0x00c48db0

    uint8_t      pad000[0x180];                         // +0x000 .. +0x17f
    IProperty*   mpMissionKey;                          // +0x180
    uint8_t      pad184[0x6c];                          // +0x184 .. +0x1ef
    int32_t      mState;                                // +0x1f0
};

class cSPMissionEradicate : public cSPMissionBase {
public:
    uint32_t GetDiseaseEffectID();
};

class cSPMissionBiosphere : public cSPMissionBase {
public:
    int GetPlanetCount();
    void UpdateEventLog();
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xc4bc00 FUN_00c4bc00
void __fastcall FUN_00c4bc00(cSPMissionBase* this_, int unused, void* pParam)
{
    (void)this_;
    (void)pParam;
}

// @ 0xc4bca0 FUN_00c4bca0
float __fastcall FUN_00c4bca0(cSPMissionBase* this_, int unused, void* pParam)
{
    (void)this_;
    (void)pParam;
    return 0.0f;
}

// @ 0xc4bd00 FUN_00c4bd00
void __fastcall FUN_00c4bd00(cSPMissionBase* this_, int unused)
{
    this_->SetSerializer();
    if (this_->mState != 2) {
        this_->mState = 2;
        this_->TriggerUIUpdate();
    }
}

// @ 0xc4bd30 FUN_00c4bd30
void __fastcall FUN_00c4bd30(cSPMissionBase* this_, int unused, tUShortVector* pVector)
{
    if (this_->mState == 1) {
        if (pVector->mpBegin != pVector->mpEnd) {
            *pVector->mpBegin = 0;
            pVector->mpEnd = pVector->mpBegin;
        }
        return;
    }
    this_->FUN_00c48db0(pVector);
}

// @ 0xc4bd60 cSPMissionEradicate::GetDiseaseEffectID
uint32_t __thiscall cSPMissionEradicate::GetDiseaseEffectID()
{
    uint32_t effectId;
    if (mpMissionKey) {
        tGridPos key = {0, 0, 0};
        GetPropertyAsKey(mpMissionKey, 0x7a2db2dd, &key);
        effectId = key.mA;
    } else {
        effectId = 0xffffffff;
    }
    return effectId;
}

// @ 0xc4bda0 FUN_00c4bda0
void __fastcall FUN_00c4bda0(cSPMissionEradicate* this_, int unused, void* pOut)
{
    GetPropertyAsKey(this_->mpMissionKey, 0xff60c676, pOut);
}

// @ 0xc4bdc0 FUN_00c4bdc0
void __fastcall FUN_00c4bdc0(cSPMissionBase* this_, int unused, void* a, void* b, void* c)
{
    (void)this_; (void)a; (void)b; (void)c;
}

// @ 0xc4bea0 FUN_00c4bea0
void __fastcall FUN_00c4bea0(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4bf10 FUN_00c4bf10
void __fastcall FUN_00c4bf10(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4bf80 cSPMissionBiosphere::GetPlanetCount
int __thiscall cSPMissionBiosphere::GetPlanetCount()
{
    return 0;
}

// @ 0xc4c090 FUN_00c4c090
void __fastcall FUN_00c4c090(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c130 FUN_00c4c130
void __fastcall FUN_00c4c130(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c2f0 Simulator::cMissionBiosphere::cMissionBiosphere
void __fastcall cMissionBiosphere_ctor(void* this_, int unused)
{
    (void)this_; (void)unused;
}

// @ 0xc4c3f0 FUN_00c4c3f0
void __fastcall FUN_00c4c3f0(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c450 FUN_00c4c450
void __fastcall FUN_00c4c450(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c4b0 cSPMissionBiosphere::UpdateEventLog
void __thiscall cSPMissionBiosphere::UpdateEventLog()
{
}

// @ 0xc4c610 FUN_00c4c610
void __fastcall FUN_00c4c610(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c690 FUN_00c4c690
void __fastcall FUN_00c4c690(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c790 FUN_00c4c790
void __fastcall FUN_00c4c790(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c850 FUN_00c4c850
void __fastcall FUN_00c4c850(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

// @ 0xc4c910 FUN_00c4c910
void __fastcall FUN_00c4c910(cSPMissionBase* this_, int unused)
{
    (void)this_;
}

} // namespace SP
