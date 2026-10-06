// Slice s00d522c0: SP::cSpaceInventoryItem / cPosseSimulator helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast
#include "types.h"

// ---- external module entry points ----
extern "C" void* __cdecl NounManager();          // 0xb3d300
extern "C" int*  __cdecl FUN_00b1f9c0();         // GetItemID (thiscall body)
extern "C" int*  __cdecl FUN_00b1fdb0();         // GetAvatar (thiscall body)
extern "C" int   __cdecl FUN_00d52df0();
extern float     g_145c4ac;

// ===========================================================================
// @ 0x00d52c90  __cdecl compare by float at +8
// ===========================================================================
extern "C" int __cdecl F52c90(int a, int b)
{
    return *(float*)(b + 8) > *(float*)(a + 8);
}

// ===========================================================================
// @ 0x00d52cb0  __cdecl heap-sift (adjust) with comparator
// ===========================================================================
typedef char (__cdecl* Cmp)(int, int);

void __cdecl F52cb0(int* arr, int start, int hole, int value, Cmp cmp)
{
    if (hole <= start) {
        arr[hole] = value;
        return;
    }
    int parent;
    do {
        parent = (hole - 1) >> 1;
        if (!cmp(arr[parent], value))
            break;
        arr[hole] = arr[parent];
        hole = parent;
    } while (start < parent);
    arr[hole] = value;
}

// ===========================================================================
// @ 0x00d52d80  SP::cPosseSimulator::Write
// ===========================================================================
void __fastcall F52d80(void* self, int, int* stream)
{
    (void)self; (void)stream;
}

// ===========================================================================
// @ 0x00d52df0  inventory item count
// ===========================================================================
int __fastcall F52df0(void* self)
{
    void* m = NounManager();
    int* v = ((int*(__thiscall*)(void*))FUN_00b1f9c0)(m);
    return ((v[1] - v[0]) >> 2) - *(int*)((char*)self + 0x1c);
}

// ===========================================================================
// @ 0x00d52e10  avatar lookup
// ===========================================================================
int __fastcall F52e10(void* self)
{
    int result = 0;
    void* m = NounManager();
    int r = ((int(__thiscall*)(void*))FUN_00b1fdb0)(m);
    if (r != 0) {
        int* p = (int*)((char*)self + 0x18);
        if (*(unsigned int*)((char*)self + 0x18) > 3)
            p = (int*)&g_145c4ac;
        result = *p;
    }
    return result;
}

// ===========================================================================
// @ 0x00d52e40  notify all inventory items
// ===========================================================================
void __fastcall F52e40(void* self, int, int arg)
{
    (void)self; (void)arg;
}

// ===========================================================================
// @ 0x00d522c0
// ===========================================================================
void __fastcall F522c0(void* self)
{
    (void)self;
}
