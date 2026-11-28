// 0x00c0ccc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c0bd70/s00c0bd70.cpp, src/game/SPGonzago/SPCreatureBase.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual int s11();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(float, int, int, int, int);
};

extern "C" unsigned char g_0168d910[];
extern "C" int __cdecl FUN_00c0c320(...);

// @ 0x00c0ccc0
extern "C" bool __cdecl FUN_00c0ccc0(int a4, float a8)
{
    int t1002;
    int t1003;
    int t1007;
    int t1010;
    int t1013;
    int t1014;
    float t1017;
    float t1018;
    float t1019;
    float v_l4;
    int t1021;
    int t1022;
    int t1027;
    int t1028;
    float t1032;
    float t1038;
    bool t1041;
    float t1044;
    bool t1046;
    bool t1050;
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002) + 60));
    if (t1003 != (int)0) {
        t1007 = (int)((il2c_vc0*)(t1003))->s3((int)((int)(-828414407)));
        t1010 = (int)(t1007);
    } else {
        t1010 = (int)((int)0);
    }
    t1013 = (int)(t1010);
    t1014 = (int)((il2c_vc1*)(t1013))->s11();
    if ((unsigned char)(t1014) == (unsigned char)0) {
        if ((unsigned char)*(unsigned char*)((char*)(t1010) + 2910) == (unsigned char)(t1014)) {
            if ((unsigned char)*(unsigned char*)((char*)(t1010) + 309) != (unsigned char)(t1014)) {
                t1017 = (float)(*(float*)((char*)(t1002)));
                t1018 = (float)(*(float*)((char*)(t1002) + 4));
                t1019 = (float)(*(float*)((char*)(t1002) + 8));
                v_l4 = (float)(t1017);
                *(float*)&(a4) = (float)(t1019);
                if (t1018 >= t1017) {
                    t1021 = (int)((int)0);
                    t1022 = (int)(t1002 + (int)64);
                    if ((int)*(int*)((char*)(t1002) + 64) != t1021) {
                        t1022 = (int)FUN_00c0c320((unsigned int)(t1022));
                        t1021 = (int)(t1022);
                        if (t1021 != (int)0) {
                            t1027 = (int)(t1021);
                            t1028 = (int)((il2c_vc2*)(t1027))->s4();
                            t1019 = (float)((*(float*)&a4));
                            goto Lc0cd5c;
                        }
                        t1019 = (float)((*(float*)&a4));
                    }
                    t1028 = (int)(t1022 | (int)(-1));
                    Lc0cd5c:;
                    t1032 = (float)(t1019 * v_l4);
                    ((il2c_vc3*)((t1010 + (int)(1448))))->s6((float)(t1032), (int)(t1028), (int)((int)7), (int)((int)g_0168d910), (int)(t1021));
                    t1038 = (float)((float)0);
                    *(float*)((char*)(t1002) + 4) = (float)(t1038);
                    t1041 = true;
                    return (bool)(t1041);
                }
                t1044 = (float)(t1018 + (float)(a8));
                *(float*)((char*)(t1002) + 4) = (float)(t1044);
                t1046 = true;
                return (bool)(t1046);
            }
        }
    }
    t1050 = false;
    return (bool)(t1050);
}
