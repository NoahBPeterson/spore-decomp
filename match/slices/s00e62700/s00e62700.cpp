// @ 0x00e62700
// SP::sHandleCellMessage — dispatches a couple of cell-mode message ids.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

extern char* g_CellGame;                           // 0x016b3c04
extern "C" void* __cdecl FUN_00b5b800();           // 0x00b5b800 GetCurrentGameMode

void __cdecl FUN_00e62440();                       // 0x00e62440
void __cdecl FUN_00e53a80();                       // 0x00e53a80
char __cdecl FUN_00e50f30();                       // 0x00e50f30
void __cdecl FUN_00e539c0();                       // 0x00e539c0
char __cdecl FUN_00e00ac0();                       // 0x00e00ac0
void __cdecl FUN_00e53660(int a, int b);           // 0x00e53660

bool __stdcall FUN_00e62700(unsigned int id, unsigned int arg2)
{
    if (id < 0x5120262)
    {
        if (id == 0x4519b5a)
        {
            if (FUN_00b5b800() != (void*)0x1654c00)
                return false;
            FUN_00e53a80();
            return true;
        }
        if (id == 0x47c1d19)
        {
            FUN_00e62440();
            return true;
        }
        return false;
    }

    if (id == 0x5120262)
    {
        if (FUN_00b5b800() == (void*)0x1654c00)
        {
            unsigned int mode = *(unsigned int*)(g_CellGame + 0x515c);
            if ((mode == 0 || mode == 1) && FUN_00e50f30() == 0)
                FUN_00e539c0();
        }
        return true;
    }

    if (id == 0x539a4cf)
    {
        if (FUN_00b5b800() == (void*)0x1654c00)
        {
            if (FUN_00e00ac0() == 0)
                FUN_00e53660(2, 0);
        }
        return true;
    }

    return false;
}
