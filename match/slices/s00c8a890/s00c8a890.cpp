// 0x00c8a890: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c89d60/s00c89d60.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" int __cdecl FUN_00c88d10(...);

// @ 0x00c8a890
extern "C" int __fastcall FUN_00c8a890(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1014;
    int t1015;
    unsigned int t1020;
    int t1021;
    int t1022;
    int t1029;
    int t1030;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1043;
    int t1045;
    t1001 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    t1006 = (int)((int)(self));
    t1007 = (int)(*(int*)((char*)(t1006) + 4));
    t1008 = (int)FUN_00c88d10((unsigned int)(t1001), (unsigned int)(t1007), (unsigned int)(t1003));
    t1011 = (int)(*(int*)((char*)(t1006) + 4));
    if ((unsigned int)(t1008) < (unsigned int)(t1011)) {
        t1012 = (int)(t1011 - t1008);
        t1014 = (int)(t1008 + (int)56);
        t1015 = (int)(t1012 - (int)1);
        t1020 = (unsigned int)((unsigned int)(t1015) / (unsigned int)60);
        t1021 = (int)((int)(t1020) + (int)1);
        do {
            t1022 = (int)(*(int*)((char*)(t1014)));
            if (t1022 != (int)0) {
                ((il2c_vc0*)(t1022))->s1();
            }
            t1014 = (int)(t1014 + (int)60);
            t1021 = (int)(t1021 - (int)1);
        } while (t1021 != (int)0);
        t1003 = (int)((int)(a4));
    }
    t1029 = (int)(t1001 - t1003);
    t1030 = (int)(t1029);
    t1038 = (int)(t1030 / (int)(-60));
    t1039 = (int)(t1038);
    t1040 = (int)(t1039 << (int)4);
    t1041 = (int)(t1040 - t1038);
    t1042 = (int)(t1041 + t1041);
    t1043 = (int)(t1042 + t1042);
    *(int*)((char*)(t1006) + 4) += t1043;
    t1045 = (int)(t1003);
    return (int)(t1045);
}
