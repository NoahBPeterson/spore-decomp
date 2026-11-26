// 0x008310a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00830c00/s00830c00.cpp, src/game/Spui/SPUIStdDrawable.cpp.

#include <string.h>
struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};


// @ 0x008310a0
extern "C" int __fastcall FUN_008310a0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1006;
    int t1008;
    int t1011;
    int t1017;
    int t1021;
    int t1022;
    int t1025;
    int t1031;
    int t1035;
    int t1036;
    int t1037;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1043;
    int t1047;
    int t1048;
    t1002 = (int)((int)(a4));
    t1004 = (int)(*(int*)((char*)(t1002) + 12));
    t1006 = (int)((int)(self));
    t1008 = (int)(*(int*)((char*)(t1006) + 12));
    if (t1004 != t1008) {
        if (t1004 != (int)0) {
            t1011 = (int)(t1004);
            ((il2c_vc0*)(t1011))->s0();
        }
        *(int*)((char*)(t1006) + 12) = (int)(t1004);
        if (t1008 != (int)0) {
            t1017 = (int)(t1008);
            ((il2c_vc1*)(t1017))->s1();
        }
    }
    t1021 = (int)(*(int*)((char*)(t1002) + 16));
    t1022 = (int)(*(int*)((char*)(t1006) + 16));
    if (t1021 != t1022) {
        if (t1021 != (int)0) {
            t1025 = (int)(t1021);
            ((il2c_vc2*)(t1025))->s0();
        }
        *(int*)((char*)(t1006) + 16) = (int)(t1021);
        if (t1022 != (int)0) {
            t1031 = (int)(t1022);
            ((il2c_vc3*)(t1031))->s1();
        }
    }
    t1035 = (int)(*(int*)((char*)(t1002) + 20));
    *(int*)((char*)(t1006) + 20) = (int)(t1035);
    t1036 = (int)(*(int*)((char*)(t1002) + 24));
    *(int*)((char*)(t1006) + 24) = (int)(t1036);
    t1037 = (int)(*(int*)((char*)(t1002) + 28));
    *(int*)((char*)(t1006) + 28) = (int)(t1037);
    t1038 = (int)(*(int*)((char*)(t1002) + 32));
    *(int*)((char*)(t1006) + 32) = (int)(t1038);
    t1039 = (int)(*(int*)((char*)(t1002) + 36));
    *(int*)((char*)(t1006) + 36) = (int)(t1039);
    *(float*)((char*)(t1006) + 40) = (float)(*(float*)((char*)(t1002) + 40));
    t1040 = (int)(t1002 + (int)72);
    t1041 = (int)(t1006 + (int)72);
    *(float*)((char*)(t1006) + 44) = (float)(*(float*)((char*)(t1002) + 44));
    t1043 = (int)(t1006);
    *(float*)((char*)(t1006) + 48) = (float)(*(float*)((char*)(t1002) + 48));
    *(float*)((char*)(t1006) + 52) = (float)(*(float*)((char*)(t1002) + 52));
    *(float*)((char*)(t1006) + 56) = (float)(*(float*)((char*)(t1002) + 56));
    *(float*)((char*)(t1006) + 60) = (float)(*(float*)((char*)(t1002) + 60));
    *(float*)((char*)(t1006) + 64) = (float)(*(float*)((char*)(t1002) + 64));
    *(float*)((char*)(t1006) + 68) = (float)(*(float*)((char*)(t1002) + 68));
    memcpy((void*)(t1041), (const void*)(t1040), (unsigned int)((int)40));
    t1047 = (int)(t1002 + (int)112);
    t1048 = (int)(t1006 + (int)112);
    memcpy((void*)(t1048), (const void*)(t1047), (unsigned int)((int)40));
    return (int)(t1043);
}
