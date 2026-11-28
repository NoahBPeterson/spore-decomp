// 0x00aeefc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPAnimalBehaviorTrees.cpp, match/slices/s00aee680/s00aee680.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int, int, int, int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};

struct C_0067dcd0 { int FUN_0067dcd0(); };
struct C_00684610 { int FUN_00684610(unsigned int); };
struct C_00aed580 { int FUN_00aed580(unsigned int, unsigned int); };
struct C_00aee290 { void FUN_00aee290(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_00e39fb0 { int FUN_00e39fb0(unsigned int, unsigned int); };

// @ 0x00aeefc0
extern "C" int __fastcall FUN_00aeefc0(char* self, int edx_unused, int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1000;
    int t1004;
    int t1007;
    int v_l16;
    int v_l12[3];
    int t1008;
    int t1013;
    int t1014;
    int t1015;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1033;
    int t1034;
    int t1035;
    int t1036;
    int t1037;
    int t1040;
    int t1041;
    int t1044;
    int t1048;
    int t1053;
    int t1054;
    int t1055;
    int t1056;
    int t1060;
    int t1061;
    int t1062;
    int t1063;
    int t1064;
    int t1070;
    t1000 = (int)((int)(a8));
    t1004 = (int)((int)0);
    t1007 = (int)((int)(self));
    v_l16 = (int)(t1004);
    (*(int*)&v_l12[1]) = (int)((int)89840164);
    (*(int*)&v_l12[2]) = (int)((int)89840163);
    (*(int*)&v_l12[0]) = (int)(t1000);
    t1008 = (int)((C_0067dcd0*)((int)(self)))->FUN_0067dcd0();
    t1013 = (int)((int)&v_l16);
    t1014 = (int)((int)&v_l12);
    t1015 = (int)(t1008);
    ((il2c_vc0*)(t1015))->s3((int)(t1014), (int)(t1013), (int)(t1004), (int)(t1004), (int)(t1004), (int)(t1004));
    t1019 = (int)(v_l16);
    t1020 = (int)((int)&a12);
    t1021 = (int)((int)&a8);
    t1022 = (int)(t1019 + (int)24);
    t1023 = (int)(t1022);
    t1024 = (int)((C_00e39fb0*)(t1023))->FUN_00e39fb0((unsigned int)(t1021), (unsigned int)(t1020));
    t1027 = (int)(t1019 + (int)28);
    if ((int)*(int*)((char*)(t1024)) != t1027) {
        t1028 = (int)((int)&a12);
        t1029 = (int)(t1022);
        t1030 = (int)((C_00684610*)(t1029))->FUN_00684610((unsigned int)(t1028));
        t1033 = (int)(t1030);
        t1034 = (int)(*(int*)((char*)(t1033) + 60));
        if (t1034 != (int)*(int*)((char*)(t1033) + 64)) {
            do {
                t1035 = (int)((int)(a16));
                t1036 = (int)(t1007);
                t1037 = (int)((C_00aed580*)(t1036))->FUN_00aed580((unsigned int)(t1034), (unsigned int)(t1035));
                if ((unsigned char)(t1037) != (unsigned char)0) {
                    if (t1004 == (int)(a20)) goto Laef087;
                    t1004 = (int)(t1004 + (int)1);
                }
                t1034 = (int)(t1034 + (int)196);
            } while (t1034 != (int)*(int*)((char*)(t1033) + 64));
        }
        t1019 = (int)(v_l16);
    }
    t1040 = (int)((int)(a4));
    t1041 = (int)((int)0);
    *(int*)((char*)(t1040) + 4) = (int)(t1041);
    *(int*)((char*)(t1040) + 8) = (int)(t1041);
    *(int*)((char*)(t1040) + 12) = (int)(t1041);
    if (t1019 != t1041) {
        t1044 = (int)(t1019);
        ((il2c_vc1*)(t1044))->s1();
    }
    Laef07b:;
    t1048 = (int)(t1040);
    return (int)(t1048);
    Laef087:;
    t1053 = (int)((int)(a24));
    if (t1053 != (int)0) {
        t1054 = (int)((int)(a16));
        t1055 = (int)(t1034 + (int)96);
        t1056 = (int)(t1007);
        ((C_00aee290*)(t1056))->FUN_00aee290((unsigned int)(t1055), (unsigned int)(t1054), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)(t1053), (unsigned int)((int)0));
    }
    t1060 = (int)(*(int*)((char*)(t1034) + 80));
    t1040 = (int)((int)(a4));
    *(int*)((char*)(t1040)) = (int)(t1060);
    t1061 = (int)(*(int*)((char*)(t1034) + 84));
    *(int*)((char*)(t1040) + 4) = (int)(t1061);
    t1062 = (int)(*(int*)((char*)(t1034) + 88));
    *(int*)((char*)(t1040) + 8) = (int)(t1062);
    t1063 = (int)(*(int*)((char*)(t1034) + 92));
    *(int*)((char*)(t1040) + 12) = (int)(t1063);
    t1064 = (int)(v_l16);
    if (t1064 == (int)0) goto Laef07b;
    ((il2c_vc2*)(t1064))->s1();
    t1070 = (int)(t1040);
    return (int)(t1070);
}
