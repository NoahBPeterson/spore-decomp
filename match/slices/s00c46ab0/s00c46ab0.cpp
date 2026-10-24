// Slice s00c46ab0 -- SP mission object (cSPMission): conversation ids, mission ids, planet/species
// export, completed-feedback timer and its star-map/comm helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

class cSPMissionManager;
class cStarMap;
class cSPTimer;

class cSPTimer {
public:
    void Restart();                                     // 0x00bc3130

    uint32_t mStorage;                                  // +0x00
};

// Simulated world object referenced by the mission (planet / creature).
class ISpaceObject {
public:
    virtual void o000(); virtual void o004(); virtual void o008();
    virtual void* QueryInterface(uint32_t interfaceId); // +0x0c
    virtual void o010(); virtual void o014(); virtual void o018(); virtual void o01c();
    virtual void o020(); virtual void o024(); virtual void o028(); virtual void o02c();
    virtual void o030(); virtual void o034(); virtual void o038(); virtual void o03c();
    virtual void o040(); virtual void o044(); virtual void o048(); virtual void o04c();
    virtual void o050(); virtual void o054(); virtual void o058(); virtual void o05c();
    virtual void o060(); virtual void o064(); virtual void o068();
    virtual void OnMissionCompleted();                  // +0x6c
};

// Export target of a species / planet record.
class ISpeciesExport {
public:
    virtual void* Export(int flags, const void* pPayload);  // 0x00c59fd0
};

struct tGridPos {
    uint32_t mA;                                        // +0x00
    uint32_t mB;                                        // +0x04
    uint32_t mC;                                        // +0x08
};

struct cSpeciesData {
    uint8_t pad0000[0x504];                             // +0x0000
    tGridPos mSpeciesKey;                               // +0x0504
};

struct cAudioSystem {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void* GetOutputDevice();                    // +0x20
};

cAudioSystem* __cdecl GetSystemAT();                     // 0x00a206f0
void __cdecl KillSetiEffects(uint32_t effectId, void* pDevice);  // 0x00435ed0

cSPMissionManager* __stdcall GetMissionManager(void* pOwner);                  // 0x00feb9f0
cSPMissionManager* __stdcall GetMissionManagerOf(void* pOwner, void* pUnused); // same routine, extra arg

class cSPMissionManager {
public:
    bool FUN_00febf80();                                // 0x00febf80
    bool IsCompletedFeedbackActive();                   // 0x00febe50
};

class cSPMission {
public:
    virtual void m000(); virtual void m004(); virtual void m008();
    virtual void* QueryInterface(uint32_t interfaceId); // +0x0c
    virtual void m010(); virtual void m014(); virtual void m018(); virtual void m01c();
    virtual void m020(); virtual void m024(); virtual void m028(); virtual void m02c();
    virtual void m030(); virtual void m034(); virtual void m038(); virtual void m03c();
    virtual void m040(); virtual void m044(); virtual void m048(); virtual void m04c();
    virtual void m050(); virtual void m054(); virtual void m058(); virtual void m05c();
    virtual void m060(); virtual void m064(); virtual void m068();
    virtual void OnMissionCompleted();                  // +0x6c

    uint8_t      pad004[0x34];                          // +0x004 .. +0x037 (after the vfptr)
    cSPTimer     mFeedbackTimer;                        // +0x038
    uint8_t      pad03c[0x3c];                          // +0x03c .. +0x077
    uint32_t     mMissionId;                            // +0x078
    uint8_t      pad07c[0x20];                          // +0x07c .. +0x09b
    ISpaceObject* mpPlanet;                             // +0x09c
    uint8_t      pad0a0[0x60];                          // +0x0a0 .. +0x0ff
    void*        mpPlanetVisual;                        // +0x100
    uint8_t      pad104[0x2c];                          // +0x104 .. +0x12f
    uint32_t     mFlags;                                // +0x130
    uint8_t      pad134[0x48];                          // +0x134 .. +0x17b
    cSPMission*  mpMissionManager;                      // +0x17c
    void*        mpMissionKey;                          // +0x180
    uint8_t      pad184[0x380];                         // +0x184 .. +0x503
    cSpeciesData mSpecies;                              // +0x504

    ~cSPMission();
    void FUN_00c46ab0();
    void FUN_00c46b80();
    void GiveOnAcceptItems();
    uint32_t GetConversationFileID();
    void FUN_00c470a0();
    void SetMissionID(uint32_t missionId);
    void FUN_00c47140(uint32_t planetId);
    void FUN_00c47180(uint32_t planetId);
    void FUN_00c471c0();
    void FUN_00c47240();
    bool FUN_00c472c0();
    void FUN_00c472e0();
    void ExportPlanet(uint32_t targetType, void* pOut);
    void ExportSpecies(uint32_t itemType, uint32_t flags);
    void StartCompletedFeedbackTimer();
    void FUN_00c474b0();
    void FUN_00c47610();
    void Update(int deltaMs);
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xc46ab0 FUN_00c46ab0
void __thiscall cSPMission::FUN_00c46ab0()
{
}

// @ 0xc46b80 FUN_00c46b80
void __thiscall cSPMission::FUN_00c46b80()
{
}

// @ 0xc46e20 cSPMission::GiveOnAcceptItems
void __thiscall cSPMission::GiveOnAcceptItems()
{
}

// @ 0xc47040 cSPMission::GetConversationFileID
uint32_t __thiscall cSPMission::GetConversationFileID()
{
    return 0xffffffff;
}

// @ 0xc470a0 FUN_00c470a0
void __thiscall cSPMission::FUN_00c470a0()
{
}

// @ 0xc470f0 cSPMission::SetMissionID
void __thiscall cSPMission::SetMissionID(uint32_t missionId)
{
    mMissionId = missionId;
}

// @ 0xc47140 FUN_00c47140
void __thiscall cSPMission::FUN_00c47140(uint32_t planetId)
{
    (void)planetId;
}

// @ 0xc47180 FUN_00c47180
void __thiscall cSPMission::FUN_00c47180(uint32_t planetId)
{
    (void)planetId;
}

// @ 0xc471c0 FUN_00c471c0
void __thiscall cSPMission::FUN_00c471c0()
{
}

// @ 0xc47240 FUN_00c47240
void __thiscall cSPMission::FUN_00c47240()
{
}

// @ 0xc472e0 FUN_00c472e0
void __thiscall cSPMission::FUN_00c472e0()
{
}

// @ 0xc47350 cSPMission::ExportPlanet
void __thiscall cSPMission::ExportPlanet(uint32_t targetType, void* pOut)
{
    (void)targetType;
    (void)pOut;
}

// @ 0xc474b0 FUN_00c474b0
void __thiscall cSPMission::FUN_00c474b0()
{
}

// @ 0xc47610 FUN_00c47610
void __thiscall cSPMission::FUN_00c47610()
{
}

// @ 0xc47680 cSPMission::~cSPMission
__thiscall cSPMission::~cSPMission()
{
}

// @ 0xc478b0 cSPMission::Update
void __thiscall cSPMission::Update(int deltaMs)
{
    (void)deltaMs;
}

// @ 0xc472c0 FUN_00c472c0
bool __thiscall cSPMission::FUN_00c472c0()
{
    cSPMission* pOwner = mpMissionManager ? mpMissionManager : this;
    return GetMissionManager(pOwner)->FUN_00febf80();
}

// @ 0xc473f0 cSPMission::ExportSpecies
void __thiscall cSPMission::ExportSpecies(uint32_t itemType, uint32_t flags)
{
    if (itemType == 0x29aa9073)
        return;
    if (itemType != 0xd6dc6ff6)
        return;
    cSPMission* pOwner = mpMissionManager;
    if (!pOwner)
        return;
    ISpeciesExport* pExport = (ISpeciesExport*)pOwner->QueryInterface(0x422227c);
    if (!pExport)
        return;
    pExport->Export(0, &mSpecies.mSpeciesKey);
}

// @ 0xc47440 cSPMission::StartCompletedFeedbackTimer
void __thiscall cSPMission::StartCompletedFeedbackTimer()
{
    cSPMission* pManager = mpMissionManager;
    if (pManager) {
        pManager->OnMissionCompleted();
        return;
    }
    mFeedbackTimer.Restart();

    cSPMission* pOwner = mpMissionManager ? mpMissionManager : this;
    if (!GetMissionManagerOf(pOwner, 0)->IsCompletedFeedbackActive())
        return;

    cAudioSystem* pAudio = GetSystemAT();
    if (pAudio) {
        KillSetiEffects(0x0c871d6e, pAudio->GetOutputDevice());
        return;
    }
    KillSetiEffects(0x0c871d6e, (void*)pAudio);
}

} // namespace SP
