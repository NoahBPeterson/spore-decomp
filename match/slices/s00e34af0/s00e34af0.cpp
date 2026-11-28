// 0x00e34af0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00e30000.cpp, match/slices/s00e34290/s00e34290.cpp.

struct il2c_bv12 { int d[3]; };
struct il2c_vc1 {
    virtual void s0();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013f6b3c[];
extern "C" int __stdcall FUN_00401020(unsigned int);
struct C_005f0ca0 { int FUN_005f0ca0(); };
extern "C" int __stdcall FUN_00b3d360(il2c_bv12, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
struct C_00b7d440 { int FUN_00b7d440(); };
struct C_00e34220 { int FUN_00e34220(); };
struct C_00e34540 { int FUN_00e34540(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e34af0
extern "C" void __fastcall FUN_00e34af0(char* self, int edx_unused)
{
    int t1004;
    int t1006;
    int t1008;
    int v_l12[3];
    int t1009;
    int v_l24[3];
    int t1;
    int t1013;
    int t1016;
    int t1020;
    int t1023;
    int t1024;
    int t1027;
    int t1030;
    int t1031;
    int t1034;
    int t1035;
    int t1038;
    int t1044;
    int t1048;
    int t1049;
    int t1050;
    int t1051;
    int t1052;
    int t1053;
    t1004 = (int)((int)0);
    t1006 = (int)((int)(self));
    t1008 = (int)((int)&v_l12);
    t1009 = (int)((int)&v_l24);
    (*(int*)&v_l24[0]) = (int)(t1004);
    (*(int*)&v_l24[1]) = (int)(t1004);
    (*(int*)&v_l24[2]) = (int)(t1004);
    (*(int*)&v_l12[0]) = (int)(t1004);
    (*(int*)&v_l12[1]) = (int)(t1004);
    (*(int*)&v_l12[2]) = (int)(t1004);
    t1 = (int)(t1006 + (int)52);
    t1013 = (int)FUN_00b3d360((*(il2c_bv12*)(t1)), (unsigned int)(t1004), (unsigned int)(t1004), (unsigned int)(t1004), (unsigned int)(t1004), (unsigned int)(t1009), (unsigned int)(t1008));
    t1016 = (int)(t1013);
    ((C_00b7d440*)(t1016))->FUN_00b7d440();
    if ((*(int*)&v_l24[0]) != t1004) {
        if ((int)*(int*)((char*)(t1006) + 36) != t1004) {
            t1020 = (int)FUN_00f473a0((unsigned int)((int)404), (unsigned int)((int)g_013f6b3c), (unsigned int)(t1004), (unsigned int)(t1004), (unsigned int)(t1004), (unsigned int)(t1004));
            if (t1020 != t1004) {
                t1023 = (int)(t1020);
                t1024 = (int)((C_00e34220*)(t1023))->FUN_00e34220();
            } else {
                t1024 = (int)((int)0);
            }
            t1027 = (int)FUN_00401020((unsigned int)(t1024));
            t1030 = (int)(t1027);
            t1031 = (int)((C_005f0ca0*)(t1030))->FUN_005f0ca0();
            t1034 = (int)(*(int*)((char*)(t1006) + 48));
            t1035 = (int)(t1031);
            if (t1035 != t1034) {
                if (t1035 != t1004) {
                    t1038 = (int)(t1035);
                    ((il2c_vc1*)(t1038))->s0();
                }
                *(int*)((char*)(t1006) + 48) = (int)(t1035);
                if (t1034 != t1004) {
                    t1044 = (int)(t1034);
                    ((il2c_vc2*)(t1044))->s1();
                }
            }
            t1048 = (int)(*(int*)((char*)(t1006) + 68));
            t1049 = (int)(*(int*)((char*)(t1006) + 64));
            t1050 = (int)(*(int*)((char*)(t1006) + 36));
            t1051 = (int)((int)&v_l12);
            t1052 = (int)((int)&v_l24);
            t1053 = (int)(*(int*)((char*)(t1006) + 48));
            ((C_00e34540*)(t1053))->FUN_00e34540((unsigned int)(t1052), (unsigned int)(t1051), (unsigned int)(t1050), (unsigned int)(t1049), (unsigned int)(t1048));
        }
    }
    return;
}
