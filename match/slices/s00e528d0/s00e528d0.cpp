// Slice s00e528d0 -- cell-game helper: fetch an element from the array at
// cCellGame+0x54 and store a value into its +4 field.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern void* g_16b3c04;   // 0x016b3c04 (cCellGame singleton)

// Array object at cCellGame+0x54; Get() is 0x00b72210 (thiscall, ret 4).
struct CellArray54 {
    void* Get(int index);
};

// @ 0x00e528d0
static void FUN_00e528d0(int index, int value)
{
    CellArray54* arr = (CellArray54*)((char*)g_16b3c04 + 0x54);
    int* element = (int*)arr->Get(index);
    element[1] = value;
}

// Stand-in caller: keeps the TU-local helper referenced and pins its register
// convention (first argument in eax, the rest on the stack).
extern "C" void slice_s00e528d0(int index, int value)
{
    FUN_00e528d0(index, value);
}
