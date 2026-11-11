// Slice s00891360: id conversion loop of the manager object of s00891220/s00891310 (it owns
// the critical section at +0x28).  Each source id is looked up in the dictionary at
// +0x15c (key +0x160); unknown or clashing ids are rewritten (0xfffe), otherwise the
// object's default id (+0x14) is used when asked for.  Returns the first output slot
// past the last one written.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// The critical-section helpers are called through their IAT slots: `push &cs;
// call dword ptr [0x13cc2d8]` with no `add esp`, so the callee pops the argument.
typedef void (__stdcall* CsFn)(void*);
extern CsFn g_EnterCS_013cc2d8;   // 0x013cc2d8, ret 4
extern CsFn g_LeaveCS_013cc2dc;   // 0x013cc2dc, ret 4

typedef unsigned short u16;

extern "C" u16  __cdecl FUN_008c2070(void* dict, u16 id, void* key);            // 0x008c2070 lookup
extern "C" int  __cdecl FUN_008c20d0(void* dict, u16 id, int zero, void* key);  // 0x008c20d0 insert
extern "C" bool __cdecl FUN_00885c20(u16 id);                                    // 0x008885c20 is-text id

struct Obj_00891360 {
    char  pad00[0x14];
    u16   m14;                                      // +0x014 default id
    char  pad16[0x28 - 0x16];
    char  cs28[0x18];                               // +0x028 critical section
    char  pad40[0x15c - 0x40];
    void* m15c;                                     // +0x15c dictionary
    char  m160[4];                                  // +0x160 dictionary key

    u16* Convert(u16* out, const u16* src, int count, int stride, int useDefault); // @ 0x00891360
};

// @ 0x00891360
u16* Obj_00891360::Convert(u16* out, const u16* src, int count, int stride, int useDefault)
{
    g_EnterCS_013cc2d8(cs28);
    u16* cur = out;
    const u16* end = src + count;
    for (; src < end; ++src) {
        u16 lookup = FUN_008c2070(m15c, src[0], m160);
        if (!lookup) {
            if (!FUN_008c20d0(m15c, src[0], 0, m160)) {
                if (FUN_00885c20(src[0]))
                    lookup = 0xfffe;
                else if (useDefault)
                    lookup = m14;
            }
        }
        cur[0] = lookup;
        cur = (u16*)((char*)cur + stride);
    }
    g_LeaveCS_013cc2dc(cs28);
    return cur;
}
