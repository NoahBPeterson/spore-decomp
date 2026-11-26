// 0x00bca3d0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bca040/s00bca040.cpp, src/game/SPGonzago/_at_00bc0000.cpp.

// lifted by il2c_lift + l2c_search (ref@t1002); CI scorer MATCH; corpus status nonmatching/residual
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


// @ 0x00bca3d0
extern "C" int __fastcall FUN_00bca3d0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    unsigned short t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1024;
    int t1030;
    int t1034;
    int t1035;
    int t1038;
    int t1044;
    int t1051;
    t1002 = (int)((int)(self));
    int& t1002_r = t1002;
    t1004 = (int)((int)(a4));
    t1008 = (int)(t1004);
    t1009 = (int)(t1002_r);
    memcpy((void*)(t1009), (const void*)(t1008), (unsigned int)((int)32));
    t1014 = (unsigned short)(*(unsigned short*)((char*)(t1004) + 32));
    *(unsigned short*)((char*)(t1002_r) + 32) = (unsigned short)(t1014);
    t1015 = (int)(*(int*)((char*)(t1004) + 36));
    *(int*)((char*)(t1002_r) + 36) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1004) + 40));
    *(int*)((char*)(t1002_r) + 40) = (int)(t1016);
    *(float*)((char*)(t1002_r) + 44) = (float)(*(float*)((char*)(t1004) + 44));
    t1017 = (int)(*(int*)((char*)(t1004) + 48));
    *(int*)((char*)(t1002_r) + 48) = (int)(t1017);
    t1018 = (int)(*(int*)((char*)(t1004) + 52));
    *(int*)((char*)(t1002_r) + 52) = (int)(t1018);
    t1019 = (int)(*(int*)((char*)(t1004) + 56));
    *(int*)((char*)(t1002_r) + 56) = (int)(t1019);
    t1020 = (int)(*(int*)((char*)(t1004) + 60));
    t1021 = (int)(*(int*)((char*)(t1002_r) + 60));
    if (t1020 != t1021) {
        if (t1020 != (int)0) {
            t1024 = (int)(t1020);
            ((il2c_vc0*)(t1024))->s0();
        }
        *(int*)((char*)(t1002_r) + 60) = (int)(t1020);
        if (t1021 != (int)0) {
            t1030 = (int)(t1021);
            ((il2c_vc1*)(t1030))->s1();
        }
    }
    t1034 = (int)(*(int*)((char*)(t1004) + 64));
    t1035 = (int)(*(int*)((char*)(t1002_r) + 64));
    if (t1034 != t1035) {
        if (t1034 != (int)0) {
            t1038 = (int)(t1034);
            ((il2c_vc2*)(t1038))->s0();
        }
        *(int*)((char*)(t1002_r) + 64) = (int)(t1034);
        if (t1035 != (int)0) {
            t1044 = (int)(t1035);
            ((il2c_vc3*)(t1044))->s1();
        }
    }
    t1051 = (int)(t1002_r);
    return (int)(t1051);
}
