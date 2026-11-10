// Slice s008912d0: serialization of the manager object from s00891220 (it owns the
// critical section at +0x28 and the pointer at +0x10): under the lock, copy the
// 0x74-byte record at +0x48 into the caller's buffer when the object exists.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// The critical-section helpers are called through their IAT slots: `push &cs;
// call dword ptr [0x13cc2d8]` with no `add esp`, so the callee pops the argument.
typedef void (__stdcall* CsFn)(void*);
extern CsFn g_EnterCS_013cc2d8;   // 0x013cc2d8, ret 4
extern CsFn g_LeaveCS_013cc2dc;   // 0x013cc2dc, ret 4

struct Rec8912D0 { int v[0x1d]; };          // 0x74-byte serialized record

struct S8912D0 {
    char  pad_00[0x10];
    void* m10;                              // +0x010 payload, absent for an empty record
    char  pad_14[0x28 - 0x14];
    char  cs28[0x18];                       // +0x028 critical section
    char  pad_40[0x48 - 0x40];
    Rec8912D0 m48;                          // +0x048 0x74-byte record

    bool serialize(Rec8912D0* out);         // @ 0x008912d0
};

// @ 0x008912d0
bool S8912D0::serialize(Rec8912D0* out)
{
    g_EnterCS_013cc2d8(cs28);
    if (m10) {
        *out = m48;
        g_LeaveCS_013cc2dc(cs28);
        return true;
    }
    g_LeaveCS_013cc2dc(cs28);
    return false;
}
