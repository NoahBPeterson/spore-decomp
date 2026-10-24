// Declarations for slice s00c7b120 (SP::cPlayer war-state helpers and the eastl war maps).
// Callees are external (relocated) in the original; PDB names where known.
#pragma once
#include "types.h"

typedef unsigned int size_t;

namespace eastl {
class allocator { public: allocator() {} };
}

namespace SP {

// A cSPTimer as laid out in this family (vtable, refcount, elapsed (8), base (8), running, fn).
struct cSPTimer {
    uint32_t mpVftblBase;                           // 0x00
    uint32_t mRefCount;                             // 0x04
    uint32_t mElapsedLo;                            // 0x08
    uint32_t mElapsedHi;                            // 0x0c
    uint32_t mBaseLo;                               // 0x10
    uint32_t mBaseHi;                               // 0x14
    bool     mbRunning;                             // 0x18
    uint32_t pad_19[3];                             // 0x19..0x1c
    void*    mpFn;                                  // 0x1c
    void Start();                                   // 0x00BC30F0
    void Restart();                                 // 0x00BC3130
};

// cGonzagoTimer (the resource-timer wrapper) used by the war start path.  It embeds a cSPTimer.
struct cGonzagoTimer {
    cSPTimer mTimer;                                // 0x00 (filled by the ctor)
    uint32_t pad_20[2];                             // 0x20
    cGonzagoTimer();                                // 0x00B63890
    ~cGonzagoTimer();                               // 0x00B638B0
};

// The 0x40-byte war record value of the war map (key payload in an rbtree node).
struct cSpacePlayerWarData {
    uint32_t mpVftbl00;                             // 0x00
    uint32_t mInt04;                                // 0x04
    uint32_t mEnemyEmpireID;                        // 0x08
    uint32_t mInt0c;                                // 0x0c
    cSPTimer mTimer;                                // 0x10
    uint32_t mPlayerStartStars;                     // 0x30
    uint32_t mEnemyStartStars;                      // 0x34
    uint32_t mPlayerCaptured;                       // 0x38
    uint32_t mEnemyCaptured;                        // 0x3c
};

// A fixed-hashtable of war flags (this+0x11d8): operator[] returns a uint32* to the flag word.
struct WarFlagMap {
    uint32_t* __thiscall operator[](const uint32_t* key);   // 0x00F41AA0
};

// eastl::map<unsigned, cSpacePlayerWarData>::operator[] (this+0x11f8).
struct WarDataMap {
    cSpacePlayerWarData* __thiscall operator[](const uint32_t* key); // 0x00C7BC50
};

// SP::cPlayer — the war bookkeeping region.
class cPlayer {
public:
    uint32_t  pad_000[0x84/4];                      // 0x000..0x084
    int       mEmpireID;                            // 0x084
    uint32_t  pad_088[0x11d8/4 - 0x088/4];          // 0x088..0x11d8
    WarFlagMap mWarFlags;                           // 0x11d8
    uint32_t  pad_11dc[0x11f8/4 - 0x11dc/4];        // 0x11dc..0x11f8
    WarDataMap mWarData;                            // 0x11f8
    uint32_t  pad_11fc[0x1214/4 - 0x11fc/4];        // 0x11fc..0x1214
    // a 0x1214-based vector of 0x28-byte elements (the war timers); 0x08 = capacity ptr, 0x04 = end
    uint32_t  mTimerBegin;                          // 0x1214
    uint32_t  mTimerEnd;                            // 0x1218
    uint32_t  mTimerCapEnd;                         // 0x121c

    void NoteWarStartedWithPlayer(int otherPlayer);         // 0x00C7BD40
    void NoteWarEndedWithPlayer(int otherPlayer);           // 0x00C78450
    void ResetWarDataWithPlayer(int otherPlayer);           // 0x00C7BE30
    void FUN_00c7ba90(int starRecord);                      // 0x00C7BA90

    void SetWarFlag1(int key);                              // 0x00C7BB60
    void SetWarFlag2(int key);                              // 0x00C7BB80
    void SetWarFlag4(int key);                              // 0x00C7BBA0
    void SetWarFlag8(int key, char value);                  // 0x00C7BBC0
    void SetWarFlag10(int key, char value);                 // 0x00C7BBF0
    void SetWarFlag20(int key, char value);                 // 0x00C7BC20
    cSpacePlayerWarData* WarDataAt(const uint32_t* key);    // 0x00C7BC50
};

void FUN_00c7b120();                                // 0x00C7B120
void FUN_00c7b390();                                // 0x00C7B390
void FUN_00c7b510();                                // 0x00C7B510
void FUN_00c7b670();                                // 0x00C7B670
void FUN_00c7b790();                                // 0x00C7B790
void FUN_00c7bea0();                                // 0x00C7BEA0
void FUN_00c76f10(void* timer);                     // 0x00C76F10
void FUN_00c7aa40(void* end, void* key);            // 0x00C7AA40
void FUN_00c7ad40(void* player, int starRecord);    // 0x00C7AD40
int* FUN_00c308d0(void* empire);                    // 0x00C308D0 (cEmpire::GetStars)
void FUN_00c77bf0(int a);                           // 0x00C77BF0
void FUN_00c798a0(void* a, int b, int c);           // 0x00C798A0
void FUN_00c79530(int a);                           // 0x00C79530

} // namespace SP
