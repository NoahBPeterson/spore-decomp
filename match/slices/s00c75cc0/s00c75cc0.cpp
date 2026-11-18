// Slice s00c75cc0: one game-side player/terrain object method (0x00C75CC0).
//
// The object stores five int properties; this method writes the one selected
// by a property key, then asks the object to refresh when the active game mode
// is Space (0x1654c05).
//
// The object is only used through its retail offsets here: +0x10fc..+0x110c
// are five consecutive dwords, and 0x00c759a0 is a thiscall sibling method.
#include "types.h"

// 0x00b5b800: id of the active game mode (0x1654c05 == Space).
int __cdecl SP_GetCurrentGameMode();

struct cPropertyObject {
    char mPad_0000[0x10fc];
    int  mProperty10fc;                 // +0x10fc
    int  mProperty1100;                 // +0x1100
    int  mProperty1104;                 // +0x1104
    int  mProperty1108;                 // +0x1108
    int  mProperty110c;                 // +0x110c

    void Refresh();                     // 0x00c759a0 (thiscall, no args)
    void FUN_00c75cc0(int key, int value);
};

// @ 0x00c75cc0
void cPropertyObject::FUN_00c75cc0(int key, int value)
{
    switch (key) {
    case 0xad56080c: mProperty1100 = value; break;
    case 0xa426730b: mProperty10fc = value; break;
    case 0xbeb528cb: mProperty1108 = value; break;
    case 0x2db6dad3: mProperty110c = value; break;
    case 0xf71fa311: mProperty1104 = value; break;
    default: break;
    }

    if (SP_GetCurrentGameMode() == 0x1654c05)
        Refresh();
}
