// Slice s01009df0: SP::cSPSimulatorSpaceGame UFO encounter/notification update.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// The function runs once per space-simulator frame:
//   * bails out while the app is paused or the simulator is in one of two
//     special modes;
//   * retires a pending camera/encounter handle;
//   * looks up the current mode's 0x303154cc object and drives the two timed
//     notification windows (start and end of an encounter); when the first
//     window does not fire it may set up the encounter instead;
//   * while that object exists, runs the per-frame NPC-UFO spawn roll with dt
//     clamped to 100, then the chasing-UFO update.
//
// Layout note: field offsets are taken from this build's disassembly.  The
// class layout in the shipped PDB differs (the NPC-UFO vector is at +0xa8
// there); as in slice s01008910 the disassembly is the authority.
#include "types.h"
#include <intrin.h>

typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;

// ---------------------------------------------------------------------------
// engine / game types, only as much as this function touches
// ---------------------------------------------------------------------------

// The application singleton: one pause/disable flag at +0x48.
struct cApp {
    u8 mPad00[0x48];
    u8 mFlags48;                        // +0x48, bit 0 = update disabled
};

// The application mode holder returned by 0x0067dd10.
struct cMode;
struct cModeObject;

struct cModeHolder {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual cModeObject* GetCurrentMode();  // +0x50
};

// The current mode: virtual Query at +0x0c, virtual 0x38 on the holder's
// result returns the mode object itself.
struct cModeObject {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* Query(u32 id);        // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual cModeObject* GetSelf();     // +0x38 (the object looked up below)
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual float GetTime();            // +0x5c
};

// A mode object: the camera/encounter state carried by the 0x303154cc tag.
struct cModeTag {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* Query(u32 id);        // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual float GetTime();            // +0x5c

    u8 mPad04[0xd5 - 0x04];
    u8 mFlagD5;                         // +0xd5
    u8 mFlagD6;                         // +0xd6
};

// The handle whose virtual +0x10 gates the first half of the update.
struct cPendingHandle {
    virtual void v00();
    virtual void Release();             // +0x04
    virtual void v08();
    virtual void v0c();
    virtual bool IsPending();           // +0x10
};

// A one-pointer owning reference (EA::AutoRefCount) stored at +0x8c of the
// manager; clearing the member releases the old object.
struct cPendingRef {
    cPendingHandle* mpObject;           // +0x00
};

// The manager returned by 0x00b3d470, holding the pending handle at +0x8c.
struct cHandleManager {
    u8 mPad00[0x8c];
    cPendingRef mHandle8c;              // +0x8c
};

// Simulator-wide state (0x010212a0 / 0x01021240).
struct cSimState {
    u8 mPad00[0x28];
    i32 mKind28;                        // +0x28
    i32 GetKind();                      // 0x00801920
    void Notify();                      // 0x01002f30
};

// Player inventory (0x00a1ad60), with the local-player test and one scalar.
struct cPlayerInventory {
    u8 mPad00[0x540];
    float mValue540;                    // +0x540
    bool IsLocalPlayer();               // 0x00c38270
};

struct cPlayer {
    cPlayerInventory* GetPlayerInventory();  // 0x00a1ad60
};

// The game UI singleton (0x00fd9c60).
struct cGameUI {
    void ShowNotifyA();                 // 0x00fdf5b0
    void ShowNotifyB();                 // 0x00fdd4f0
    void ShowNotifyC();                 // 0x00fda5e0
};

// A cached property entry (field +0x4c of the property manager).
struct cPropertyEntry {
    u8 mPad00[0x08];
    u32 mId08;                          // +0x08
};

struct cPropertyManager {
    void* GetOrCreate(u32 id);          // 0x0067c830
    u8 mPad00[0x4c];
    cPropertyEntry* mpEntry4c;          // +0x4c
};

// The message server (0x00b3d3e0).
struct cMessageServer {
    void* Find(u32 id, void* unused);   // 0x00dd5d80
    void Post(u32 id, u32 text, void* a, void* b, int flag, void* c);  // 0x00dd8640
};

// ---------------------------------------------------------------------------
// free functions used by the update
// ---------------------------------------------------------------------------
cApp*             __cdecl GetApp();              // 0x00b3d380
cHandleManager*   __cdecl GetHandleManager();    // 0x00b3d470
cModeHolder*      __cdecl GetModeHolder();       // 0x0067dd10
cSimState*        __cdecl GetSimStateA();        // 0x010212a0
cPlayer*          __cdecl GetPlayerContext();    // 0x00ffbe50
cSimState*        __cdecl GetSimStateB();        // 0x01021240
cGameUI*          __cdecl GetGameUI();           // 0x00fd9c60
cPropertyManager* __cdecl GetPropertyManager();  // 0x0067cac0
cMessageServer*   __cdecl GetMessageServer();    // 0x00b3d3e0

bool  __cdecl GateA();                           // 0x010422e0
bool  __cdecl GateB();                           // 0x010053a0
bool  __cdecl GateC();                           // 0x010423d0
void  __cdecl NotifySpace();                     // 0x01002f30
float __cdecl GetThresholdA(int one);            // 0x01017030
float __cdecl GetThresholdB(int one);            // 0x01017070

extern "C" float gfTimeBias;                     // 0x01495390
extern "C" float gfSpawnScale;                   // 0x013f9428
extern "C" float gfUnsignedFix;                  // 0x013f4fd0

// The reference-returning min used by the chance clamp.  Inlined it selects
// the address of one of its two operands (the retail lea/lea pair) rather
// than a value in a register.
template <class T>
static const T& SelectMin(const T& left, const T& right)
{
    return left < right ? left : right;
}

// ---------------------------------------------------------------------------
// SP::cSPSimulatorSpaceGame
// ---------------------------------------------------------------------------
namespace SP {

class cSPSimulatorSpaceGame {
public:
    void UpdateUFOEvents(u32 nDeltaTime);              // 0x01009df0
    void SolarSystemSpawnNPC_UFOs(float fChance);      // 0x010091d0
    void UpdateChasingUFOs(u32 nDeltaTime);            // 0x01008270

private:
    u8 mPad00[0x50];                    // +0x000
    union {
        u8 mFlags50;                    // +0x050, byte tests
        u32 mFlags50d;                  // +0x050, word clear
    };
};

} // namespace SP

// @ 0x01009df0
// Per-frame space-game update: encounter notification windows followed by the
// NPC-UFO spawn roll and the chasing-UFO update.
void SP::cSPSimulatorSpaceGame::UpdateUFOEvents(u32 nDeltaTime)
{
    if (GetApp()->mFlags48 & 1)
        return;

    if (mFlags50 & 2)
        return;

    _ReadWriteBarrier();

    if (mFlags50 & 4)
        return;

    cPendingRef* pRef = &GetHandleManager()->mHandle8c;
    cPendingHandle* pPending = pRef->mpObject;
    if (pPending != 0) {
        if (pPending->IsPending())
            return;

        mFlags50d &= ~0x20u;

        cPendingRef* pOwners = &GetHandleManager()->mHandle8c;
        cPendingHandle* pOld = pOwners->mpObject;
        if (pOld != 0) {
            pOwners->mpObject = 0;
            pOld->Release();
        }
    }

    cModeObject* pMode = GetModeHolder()->GetCurrentMode()->GetSelf();
    if (pMode != 0) {
        cModeTag* pTag = (cModeTag*)pMode->Query(0x303154cc);
        if (pTag != 0) {
            cSimState* pState = GetSimStateA();
            cPlayerInventory* pInventory = GetPlayerContext()->GetPlayerInventory();

            float fNow = pTag->GetTime();

            // The first window either notifies (and returns) or leaves the
            // encounter-start work to the else branch below; the flag makes
            // that one shared branch instead of a second copy.
            bool bNotify = false;
            if (pTag->mFlagD5) {
                float fStart = fNow - gfTimeBias;

                if (GetThresholdA(1) >= fStart)
                    bNotify = GateA();
            }

            if (bNotify) {
                pState = GetSimStateB();

                if (pInventory->IsLocalPlayer()) {
                    GetGameUI()->ShowNotifyA();
                    return;
                }

                if (pState->GetKind() == 2 && GateB()) {
                    GetGameUI()->ShowNotifyB();
                    return;
                }

                if (pState->GetKind() == 1) {
                    NotifySpace();
                    return;
                }
            } else if (pState != 0 && pTag->mFlagD6 && !pInventory->IsLocalPlayer()) {
                if (pState->mKind28 == 1) {
                    cPropertyManager* pProperties = GetPropertyManager();
                    cPropertyEntry* pEntry = pProperties->mpEntry4c;

                    if (pEntry == 0 || pEntry->mId08 != 0x9a16d07e)
                        pProperties->GetOrCreate(0x9a16d07e);
                } else if (0.0f >= pInventory->mValue540) {
                    cMessageServer* pMessages = GetMessageServer();

                    if (pMessages->Find(0x9d507ccb, 0) == 0)
                        pMessages->Post(0x9d507ccb, 0x131a9f54u, 0, 0, 1, 0);
                }
            }

            if (pTag->mFlagD5) {
                // Retail reloads the stored "now" instead of reusing it from
                // an x87 register (fld [slot]; fadd [bias]); a volatile read is
                // the shape MSVC 2008 /O2 compiles that way.
                float fEnd = *(volatile float*)&fNow + gfTimeBias;

                if (fEnd >= GetThresholdB(1)) {
                    if (GateC()) {
                        GetGameUI()->ShowNotifyC();
                        return;
                    }
                }
            }

            const u32& nChance = SelectMin(nDeltaTime, 100u);
            SolarSystemSpawnNPC_UFOs((float)nChance * gfSpawnScale);
        }
    }

    UpdateChasingUFOs(nDeltaTime);
}
