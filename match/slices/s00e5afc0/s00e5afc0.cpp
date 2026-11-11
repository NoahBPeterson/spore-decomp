// @ 0x00e5afc0
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct Sub_00e5afc0 { char pad[0x10]; int mId; };   // mId at +0x10

struct CellGame_00e5afc0 {
    char           pad_000[0x0fc];              // +0x000
    int            mId;                         // +0x0fc
    char           pad_100[0x411c - 0x100];     // +0x100
    int            mGlobalId;                   // +0x411c
    char           pad_420[0x5190 - 0x4120];    // +0x4120
    Sub_00e5afc0*  mSub;                        // +0x5190
};

extern CellGame_00e5afc0* gspCellGame;          // 0x016b3c04

struct Obj_00e5afc0 {
    int mId;                                    // +0x000
    char pad_04[0xfc - 0x04];                   // +0x004
    int mId2;                                   // +0x0fc
};

// @ 0x00e5afc0
unsigned char __cdecl FUN_00e5afc0(Obj_00e5afc0* obj)
{
    if (obj->mId == gspCellGame->mGlobalId)
        return 0;
    return obj->mId2 == gspCellGame->mSub->mId;
}
