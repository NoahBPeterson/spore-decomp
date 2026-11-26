// 0x010dd1d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Havok/_at_010d0000.cpp, match/slices/s010dcd40/s010dcd40.cpp.

#include <string.h>

// @ 0x010dd1d0
extern "C" int __fastcall FUN_010dd1d0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1015;
    int t1018;
    t1001 = (int)((int)(self));
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002)));
    *(int*)((char*)(t1001)) = (int)(t1003);
    t1004 = (int)(*(int*)((char*)(t1002) + 12340));
    *(int*)((char*)(t1001) + 4144) = (int)(t1004);
    t1005 = (int)(*(int*)((char*)(t1002) + 16));
    *(int*)((char*)(t1001) + 4112) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1002) + 20));
    *(int*)((char*)(t1001) + 4116) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1002) + 24));
    *(int*)((char*)(t1001) + 4120) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1002) + 28));
    *(int*)((char*)(t1001) + 4124) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1002) + 32));
    *(int*)((char*)(t1001) + 4128) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1002) + 36));
    *(int*)((char*)(t1001) + 4132) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1002) + 40));
    *(int*)((char*)(t1001) + 4136) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1002) + 44));
    *(int*)((char*)(t1001) + 4140) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1002) + 12336));
    *(int*)((char*)(t1001) + 4148) = (int)(t1013);
    t1015 = (int)(*(int*)((char*)(t1002) + 12352));
    if (t1015 != (int)0) {
        t1018 = (int)(t1001 + (int)4);
        memcpy((void*)(t1018), (const void*)(t1015), (unsigned int)((int)4104));
    }
    return (int)(t1001);
}
