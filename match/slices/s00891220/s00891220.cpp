// Slice s00891220: teardown of a manager object: release four owned objects, drop a refcounted
// object, clear a field, all under a critical section.  Returns true.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

// The critical-section helpers are pointers held in globals; the call site is `push &cs;
// call dword ptr [0x13cc2d8]` with no `add esp`, so the callee pops the lock argument.
typedef void (__stdcall* CsFn)(void*);
extern CsFn g_EnterCS_013cc2d8;   // 0x013cc2d8, ret 4
extern CsFn g_LeaveCS_013cc2dc;   // 0x013cc2dc, ret 4

void release_008c1f20(void* p, void* q);    // 0x008c1f20
void release_008cf8d0(void* p, void* q);    // 0x008cf8d0
void release_008cc5d0(void* p, void* q);    // 0x008cc5d0
void release_008d1570(void* p);             // 0x008d1570

struct S891220 {
    char  pad_00[0x10];
    void* m10;                              // +0x010
    char  pad_14[0x28 - 0x14];
    char  cs28[0x18];                       // +0x028 critical section
    char  pad_40[0x14c - 0x40];
    int   m14C;                             // +0x14c
    void* m150;                             // +0x150
    void* m154;                             // +0x154
    void* m158;                             // +0x158
    void* m15C;                             // +0x15c
    void* m160;                             // +0x160

    bool shutdown();
};

// @ 0x00891220
bool S891220::shutdown()
{
    g_EnterCS_013cc2d8(cs28);
    if (m15C) { release_008c1f20(m15C, &m160); m15C = 0; }
    if (m158) { release_008cf8d0(m158, &m160); m158 = 0; }
    if (m154) { release_008cc5d0(m154, &m160); m154 = 0; }
    if (m150) { release_008d1570(m150); m150 = 0; }
    if (m10) {
        (*(void (__thiscall**)(void*))((char*)(*(void***)m10) + 8))(m10);
        m10 = 0;
    }
    m14C = 0;
    g_LeaveCS_013cc2dc(cs28);
    return true;
}
