// 0x011c9300: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

#include <string.h>
extern "C" unsigned char g_013cc410[];

// @ 0x011c9300
extern "C" int __cdecl FUN_011c9300(int a4, int a8)
{
    int t1000;
    int t1004;
    int t1007;
    int t1008;
    int t1010;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int (__cdecl*)(...))(*(int*)g_013cc410))(t1000);
    if (t1004 == (int)0) {
        return 0;
    }
    t1007 = (int)(t1004);
    t1008 = (int)((int)(a8));
    t1010 = (int)(t1008);
    memcpy((void*)(t1010), (const void*)(t1007), (unsigned int)((int)36));
    return (int)(t1008);
}
