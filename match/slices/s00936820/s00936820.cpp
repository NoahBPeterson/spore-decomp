// 0x00936820: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00936090/s00936090.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" unsigned char g_0143e98c[];
struct C_009221b0 { void FUN_009221b0(unsigned int); };
struct C_00922270 { void FUN_00922270(); };

// @ 0x00936820
extern "C" int __fastcall FUN_00936820(char* self, int edx_unused, int a4, int a8)
{
    int t1004;
    int t1005;
    int t1006;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1018;
    int t1022;
    int t1023;
    int v_l8;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int v_l4;
    int t1031;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1038;
    int t1042;
    int t1045;
    int t1049;
    int t1054;
    t1004 = (int)((int)(self));
    if ((int)(a4) == (int)0) {
        t1005 = (int)(t1004 + (int)32);
        t1006 = (int)(t1005);
        ((C_009221b0*)(t1006))->FUN_009221b0((unsigned int)((int)g_0143e98c));
        t1010 = (int)(*(int*)((char*)(t1004) + 12));
        t1011 = (int)(t1010 - (int)*(int*)((char*)(t1004) + 8));
        t1012 = (int)(t1005);
        t1013 = (int)(t1011 >> (int)2);
        ((C_00922270*)(t1012))->FUN_00922270();
        t1018 = (int)(t1013);
        return (int)(t1018);
    }
    t1022 = (int)(t1004 + (int)32);
    t1023 = (int)(t1022);
    v_l8 = (int)(t1022);
    ((C_009221b0*)(t1023))->FUN_009221b0((unsigned int)((int)g_0143e98c));
    t1027 = (int)(*(int*)((char*)(t1004) + 12));
    t1028 = (int)(t1027 - (int)*(int*)((char*)(t1004) + 8));
    t1029 = (int)((int)(a8));
    t1030 = (int)(t1028 >> (int)2);
    v_l4 = (int)(t1030);
    *(int*)&(a8) = (int)(t1030);
    if ((unsigned int)(t1030) >= (unsigned int)(t1029)) {
        *(int*)&(a8) = (int)(t1029);
    }
    t1031 = (int)((int)0);
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1031)) {
        do {
            t1032 = (int)(*(int*)((char*)(t1004) + 8));
            t1033 = (int)((int)(a4));
            t1034 = (int)(*(int*)((char*)(t1032) + (t1031)*4));
            t1035 = (int)(*(int*)((char*)(t1033) + (t1031)*4));
            if (t1034 != t1035) {
                if (t1034 != (int)0) {
                    t1038 = (int)(t1034);
                    ((il2c_vc0*)(t1038))->s1();
                }
                t1042 = (int)((int)(a4));
                *(int*)((char*)(t1042) + (t1031)*4) = (int)(t1034);
                if (t1035 != (int)0) {
                    t1045 = (int)(t1035);
                    ((il2c_vc1*)(t1045))->s2();
                }
            }
            t1031 = (int)(t1031 + (int)1);
        } while ((unsigned int)(t1031) < (unsigned int)((int)(a8)));
        t1022 = (int)(v_l8);
        t1030 = (int)(v_l4);
    }
    t1049 = (int)(t1022);
    ((C_00922270*)(t1049))->FUN_00922270();
    t1054 = (int)(t1030);
    return (int)(t1054);
}
