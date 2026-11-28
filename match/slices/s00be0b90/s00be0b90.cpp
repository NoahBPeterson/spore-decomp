// 0x00be0b90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bdfd30/s00bdfd30.cpp, src/game/SPGonzago/SPCity.cpp.

#include <string.h>
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
};

extern "C" unsigned char g_0156e880[];
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { void FUN_00693e10(unsigned int); };
struct C_00899420 { void FUN_00899420(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00c06c30 { void FUN_00c06c30(unsigned int, unsigned int); };
struct C_00f281f0 { void FUN_00f281f0(unsigned int); };

// @ 0x00be0b90
extern "C" void __cdecl FUN_00be0b90(int a4, int a8)
{
    int t1001;
    int t1002;
    int t1003;
    int t1006;
    int t1010;
    int t1013;
    int t1014;
    int v_l2620[2];
    int t1015;
    int t1019;
    int t1021;
    int t1024;
    int t1028;
    int t1029;
    int t1034;
    int v_l2612[8];
    int t1035;
    int v_l2580[645];
    int t1039;
    int t1043;
    int t1044;
    int t1046;
    int t1050;
    int t1051;
    int t1055;
    int t1056;
    int t1060;
    t1001 = (int)((int)(a8));
    t1002 = (int)(*(int*)((char*)(t1001) + 4));
    t1003 = (int)(*(int*)((char*)(t1001)));
    t1006 = (int)(t1001);
    ((C_00899420*)(t1006))->FUN_00899420((unsigned int)(t1003), (unsigned int)(t1002));
    t1010 = (int)((int)(a4));
    t1013 = (int)((int)0);
    t1014 = (int)(t1010);
    (*(int*)&v_l2620[0]) = (int)(t1013);
    t1015 = (int)((il2c_vc0*)(t1014))->s8();
    t1019 = (int)(t1015);
    t1021 = (int)((il2c_vc1*)(t1019))->s6();
    t1024 = (int)((int)&v_l2620);
    FUN_0093a780((unsigned int)(t1021), (unsigned int)(t1024), (unsigned int)((int)1), (unsigned int)(t1013));
    t1028 = (int)((*(int*)&v_l2620[0]));
    t1029 = (int)(t1001);
    ((C_00f281f0*)(t1029))->FUN_00f281f0((unsigned int)(t1028));
    (*(int*)&v_l2620[1]) = (int)(t1013);
    if ((unsigned int)((*(int*)&v_l2620[0])) > (unsigned int)(t1013)) {
        goto Lbe0c00;
        Lbe0c00:;
        t1034 = (int)((int)&v_l2612);
        t1035 = (int)((int)&v_l2580);
        ((C_00692f90*)(t1035))->FUN_00692f90((unsigned int)(t1034), (unsigned int)((int)g_0156e880), (unsigned int)((int)27790630));
        t1039 = (int)((int)&v_l2580);
        ((C_00693e10*)(t1039))->FUN_00693e10((unsigned int)(t1010));
        t1043 = (int)(*(int*)((char*)(t1001) + 4));
        if ((unsigned int)(t1043) < (unsigned int)*(int*)((char*)(t1001) + 8)) {
            t1044 = (int)(t1043 + (int)32);
            *(int*)((char*)(t1001) + 4) = (int)(t1044);
            if (t1043 == (int)0) goto Lbe0c4e;
            t1046 = (int)((int)&v_l2612);
            memcpy((void*)(t1043), (const void*)(t1046), (unsigned int)((int)32));
            goto Lbe0c4e;
        }
        t1050 = (int)((int)&v_l2612);
        t1051 = (int)(t1001);
        ((C_00c06c30*)(t1051))->FUN_00c06c30((unsigned int)(t1043), (unsigned int)(t1050));
        Lbe0c4e:;
        t1055 = (int)((*(int*)&v_l2620[1]));
        t1056 = (int)(t1055 + (int)1);
        (*(int*)&v_l2620[1]) = (int)(t1056);
        if ((unsigned int)(t1056) < (unsigned int)((*(int*)&v_l2620[0]))) goto Lbe0c00;
    }
    t1060 = (int)(t1010);
    ((il2c_vc2*)(t1060))->s7();
    return;
}
