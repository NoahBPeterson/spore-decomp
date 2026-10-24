// Slice s00c7b120: SP::cPlayer war-state helpers and the eastl war maps (flag setters, war
// start/end bookkeeping, the war-data map operator[] and the timer-vector push).
// The six tiny setters OR/AND a single bit in the war-flag map reached at this+0x11d8.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s00c7b120.h"

namespace SP {

void*  FUN_01021300();                                                          // 0x01021300 GetPlayerEmpire
void*  GetCurrentGameMode();                                                    // 0x00B5B800
void   FUN_00c77bf0(int a);                                                     // 0x00C77BF0
int*   FUN_00c308d0(void* empire);                                              // 0x00C308D0 cEmpire::GetStars
void*  StarManager();                                                           // 0x00B3D2A0
void   FUN_00c76f10(void* timer);                                               // 0x00C76F10
void   FUN_00c7aa40(void* end, const void* key);                                // 0x00C7AA40
void   FUN_00c7ad40(void* player, int starRecord);                              // 0x00C7AD40

// ===========================================================================
// 0x00c7bb60  set war-flag bit 1
// ===========================================================================
// @ 0x00c7bb60
void cPlayer::SetWarFlag1(int key)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    *p |= 1u;
}

// ===========================================================================
// 0x00c7bb80  set war-flag bit 2
// ===========================================================================
// @ 0x00c7bb80
void cPlayer::SetWarFlag2(int key)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    *p |= 2u;
}

// ===========================================================================
// 0x00c7bba0  set war-flag bit 4
// ===========================================================================
// @ 0x00c7bba0
void cPlayer::SetWarFlag4(int key)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    *p |= 4u;
}

// ===========================================================================
// 0x00c7bbc0  set/clear war-flag bit 8
// ===========================================================================
// @ 0x00c7bbc0
void cPlayer::SetWarFlag8(int key, char value)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    if (value != 0)
        *p |= 8u;
    else
        *p &= 0xfffffff7u;
}

// ===========================================================================
// 0x00c7bbf0  set/clear war-flag bit 0x10
// ===========================================================================
// @ 0x00c7bbf0
void cPlayer::SetWarFlag10(int key, char value)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    if (value != 0)
        *p |= 0x10u;
    else
        *p &= 0xffffffefu;
}

// ===========================================================================
// 0x00c7bc20  set/clear war-flag bit 0x20
// ===========================================================================
// @ 0x00c7bc20
void cPlayer::SetWarFlag20(int key, char value)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    if (value != 0)
        *p |= 0x20u;
    else
        *p &= 0xffffffdfu;
}

// ===========================================================================
// 0x00c7bc50  WarDataMap::operator[] (eastl::map<unsigned, cSpacePlayerWarData>)
// ===========================================================================
// @ 0x00c7bc50
cSpacePlayerWarData* cPlayer::WarDataAt(const uint32_t* key)
{
    (void)key;
    return 0;
}

// ===========================================================================
// 0x00c7bd40  NoteWarStartedWithPlayer: record the start of a war
// ===========================================================================
// @ 0x00c7bd40
void cPlayer::NoteWarStartedWithPlayer(int otherPlayer)
{
    int enemyEmpire = *(int*)(otherPlayer + 0x84);
    uint32_t key = (uint32_t)enemyEmpire;
    cSpacePlayerWarData* rec = mWarData.operator[](&key);
    rec->mEnemyEmpireID = (uint32_t)enemyEmpire;
    rec->mEnemyCaptured = 0;
    rec->mPlayerCaptured = 0;
    int* stars = FUN_00c308d0((void*)otherPlayer);
    rec->mEnemyStartStars = (uint32_t)((stars[1] - stars[0]) >> 2);
    void* me = FUN_01021300();
    int* myStars = FUN_00c308d0(me);
    rec->mPlayerStartStars = (uint32_t)((myStars[1] - myStars[0]) >> 2);
    rec->mTimer.Restart();
    FUN_00c77bf0(0x5763207);
}

// ===========================================================================
// 0x00c7be30  ResetWarDataWithPlayer: end then restart the war record
// ===========================================================================
// @ 0x00c7be30
void cPlayer::ResetWarDataWithPlayer(int otherPlayer)
{
    NoteWarEndedWithPlayer(otherPlayer);
    NoteWarStartedWithPlayer(otherPlayer);
}

// ===========================================================================
// 0x00c7ba90  start the war timer for a star record
// ===========================================================================
// @ 0x00c7ba90
void cPlayer::FUN_00c7ba90(int starRecord)
{
    FUN_00c7ad40(this, starRecord);
    int enemyEmpire = *(int*)(starRecord + 0x70);

    // Build a cGonzagoTimer, copy its timer state into a standalone cSPTimer, then start it
    // and push the record (key = enemyEmpire, timer) onto the war-timer vector at 0x1214.
    cGonzagoTimer gonzago;                                  // local_48
    cSPTimer local;
    local.mpVftblBase = 0;
    local.mRefCount = 0;
    local.mElapsedLo = gonzago.mTimer.mElapsedLo;
    local.mElapsedHi = gonzago.mTimer.mElapsedHi;
    local.mBaseLo = gonzago.mTimer.mBaseLo;
    local.mBaseHi = gonzago.mTimer.mBaseHi;
    local.mbRunning = gonzago.mTimer.mbRunning;
    local.mpFn = gonzago.mTimer.mpFn;
    uint32_t key = (uint32_t)enemyEmpire;
    (void)key;
    local.Start();

    uint32_t end = mTimerEnd;
    if (end < mTimerCapEnd) {
        mTimerEnd = end + 0x28;
        if (end != 0) {
            FUN_00c76f10(&key);
        }
    } else {
        FUN_00c7aa40((void*)end, &key);
    }
}

// ===========================================================================
// 0x00c7b120
// ===========================================================================
// @ 0x00c7b120
void FUN_00c7b120()
{
}

// ===========================================================================
// 0x00c7b390
// ===========================================================================
// @ 0x00c7b390
void FUN_00c7b390()
{
}

// ===========================================================================
// 0x00c7b510
// ===========================================================================
// @ 0x00c7b510
void FUN_00c7b510()
{
}

// ===========================================================================
// 0x00c7b670
// ===========================================================================
// @ 0x00c7b670
void FUN_00c7b670()
{
}

// ===========================================================================
// 0x00c7b790
// ===========================================================================
// @ 0x00c7b790
void FUN_00c7b790()
{
}

// ===========================================================================
// 0x00c7bea0
// ===========================================================================
// @ 0x00c7bea0
void FUN_00c7bea0()
{
}

} // namespace SP
