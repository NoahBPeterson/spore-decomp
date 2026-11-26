// 0x010dd260: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Havok/_at_010d0000.cpp, match/slices/s010dcd40/s010dcd40.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
#include <string.h>

// @ 0x010dd260
extern "C" int __fastcall FUN_010dd260(char* self, int edx_unused, int a4)
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
    t1002 = (int)(*(int*)((char*)(t1001)));
    t1003 = (int)((int)(a4));
    int& t1003_r = t1003;
    *(int*)((char*)(t1003_r)) = (int)(t1002);
    t1004 = (int)(*(int*)((char*)(t1001) + 4144));
    *(int*)((char*)(t1003_r) + 12340) = (int)(t1004);
    t1005 = (int)(*(int*)((char*)(t1001) + 4112));
    *(int*)((char*)(t1003_r) + 16) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1001) + 4116));
    *(int*)((char*)(t1003_r) + 20) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1001) + 4120));
    *(int*)((char*)(t1003_r) + 24) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1001) + 4124));
    *(int*)((char*)(t1003_r) + 28) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1001) + 4128));
    *(int*)((char*)(t1003_r) + 32) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1001) + 4132));
    *(int*)((char*)(t1003_r) + 36) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1001) + 4136));
    *(int*)((char*)(t1003_r) + 40) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1001) + 4140));
    *(int*)((char*)(t1003_r) + 44) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1001) + 4148));
    t1015 = (int)(*(int*)((char*)(t1003_r) + 12352));
    *(int*)((char*)(t1003_r) + 12336) = (int)(t1013);
    if (t1015 != (int)0) {
        t1018 = (int)(t1001 + (int)4);
        memcpy((void*)(t1015), (const void*)(t1018), (unsigned int)((int)4104));
    }
    return (int)(t1001);
}
