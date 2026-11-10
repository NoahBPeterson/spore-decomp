// Slice s0137e810 -- CRT one-time initializer driver.
//
//  0x0137e810  __cinit(): run the C initializer (0x83c800) and register the
//              destructor (0x13c7d70) with _atexit.
#include "types.h"

// compile with /vc71 /O2 /MD /Gy /EHsc /TP /GS-

struct InitObj {
    void** m_vtable;            // 0x00
    void* m_field04;            // 0x04
    void* m_field08;            // 0x08

    void Init();
};

extern InitObj g_016b0c3c;                  // 0x16b0c3c
extern void* g_016b0c3cVtable[];            // 0x1482dfc

extern "C" void Func013c7d70();             // 0x13c7d70

int __cdecl atexit(void (__cdecl*)());

// @ 0x0137e810
void InitObject()
{
    g_016b0c3c.Init();
    g_016b0c3c.m_vtable = g_016b0c3cVtable;
    atexit(Func013c7d70);
}
