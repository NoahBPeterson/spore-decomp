// 0x00894280: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

#include <string.h>

// @ 0x00894280
extern "C" int __fastcall FUN_00894280(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1006;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1006 = (int)(t1004);
    memcpy((void*)(t1006), (const void*)(t1001), (unsigned int)((int)632));
    return (int)(t1004);
}
