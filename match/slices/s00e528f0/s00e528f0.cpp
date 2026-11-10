// slice s00e528f0 -- SPCellGame.obj: store a float into a pool element.
// FUN_00e528f0 (0x00e528f0, 32 bytes): the command pool (gspCellGame + 0x54) hands out the
//   element for `handle` (cObjectPool::Get, 0x00b72210) and the float is written to its float
//   array at +0x0c.  The handle arrives in EAX (static register ABI); the index and value are
//   the two stack arguments.  The element pointer is unknown until the call returns, so retail
//   reads both arguments back from their homes after it (`mov ecx,[esp+4]`,
//   `movss xmm0,[esp+8]`) instead of pinning the index in a callee-saved register, and the
//   result goes through an unaligned `movss` store (this TU is /arch:SSE).
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

typedef uint32_t uint32;

// gspCellGame (SP::cCellGame*), global at 0x016b3c04; the command pool sits at +0x54.
extern char* gspCellGame;

struct cObjectPool {
    // 0x00b72210: handle -> element pointer (assumes live). thiscall, `ret 4`.
    void* Get(uint32 handle);
};

// @ 0x00e528f0
static void SetCellValue(int handle, int index, float value)
{
    cObjectPool* pool = (cObjectPool*)(gspCellGame + 0x54);
    float* f = (float*)&((char*)pool->Get(handle))[0x0c];
    f[index] = value;
}

// Same-TU caller so the static helper keeps its register convention.
void FUN_00e528f0(int handle, int index, float value)
{
    SetCellValue(handle, index, value);
}
