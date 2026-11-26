// 0x00694210: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPLoadSaveHelp.cpp, match/slices/s00694210/s00694210.cpp.

#include <string.h>

// @ 0x00694210
extern "C" int __cdecl FUN_00694210(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1001;
    int t1003;
    int t1006;
    int t1008;
    int t1012;
    int t1014;
    int t1019;
    int t1020;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(a16));
    L694220:;
    if ((unsigned int)*(int*)((char*)(t1001) + 4) < (unsigned int)(t1003)) {
        t1001 = (int)(t1001 + (int)60);
        goto L694220;
    }
    t1000 = (int)(t1000 - (int)60);
    if ((unsigned int)(t1003) < (unsigned int)*(int*)((char*)(t1000) + 4)) {
        do {
            t1000 = (int)(t1000 - (int)60);
        } while ((unsigned int)(t1003) < (unsigned int)*(int*)((char*)(t1000) + 4));
    }
    if ((unsigned int)(t1001) < (unsigned int)(t1000)) {
        t1006 = (int)(t1001);
        t1008 = (int)((int)&a12);
        memcpy((void*)(t1008), (const void*)(t1006), (unsigned int)((int)60));
        t1012 = (int)(t1001);
        t1014 = (int)(t1000);
        memcpy((void*)(t1012), (const void*)(t1014), (unsigned int)((int)60));
        t1019 = (int)((int)&a12);
        t1020 = (int)(t1000);
        memcpy((void*)(t1020), (const void*)(t1019), (unsigned int)((int)60));
        t1001 = (int)(t1001 + (int)60);
        goto L694220;
    }
    return (int)(t1001);
}
