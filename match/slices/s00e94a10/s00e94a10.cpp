// 0x00e94a10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e93c60/s00e93c60.cpp, src/game/SPGonzago/SPVehicleView.cpp.

struct il2c_vc0 {
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
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual int s31(int, float);
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
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual int s31(int, float);
};

extern "C" unsigned char g_01488874[];
extern "C" unsigned char g_015a8aac[];
struct C_00e948b0 { void FUN_00e948b0(unsigned int, unsigned int); };
struct C_00e94900 { void FUN_00e94900(unsigned int, unsigned int); };

// @ 0x00e94a10
extern "C" void __fastcall FUN_00e94a10(char* self, int edx_unused, int a4, float a8, float a12, int a16, int a20)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    unsigned char t2;
    unsigned char t4;
    float t1008;
    int t1010;
    int t1011;
    float t1014;
    float t1017;
    float t1018;
    float t1019;
    float t1020;
    int t1021;
    int t1028;
    int t1029;
    int t1035;
    t1002 = (int)((int)(a20));
    t1004 = (int)((int)(self));
    if (t1002 != (int)0) {
        t1005 = (int)(*(int*)((char*)(t1002) + 4));
        t1006 = (int)(t1005);
        t1007 = (int)((unsigned int)(t1006) >> (int)14);
        t2 = (unsigned char)((unsigned char)(t1007) & (unsigned char)1);
        if (t2 != (unsigned char)0) {
            t1005 = (int)((unsigned int)(t1005) >> (int)18);
            t4 = (unsigned char)((unsigned char)(t1005) & (unsigned char)1);
            if (t4 == (unsigned char)0) {
                t1008 = (float)((float)(a8));
                if (t1008 > (float)(*(float*)g_01488874)) {
                    t1010 = (int)((int)(a16));
                    if ((unsigned char)*(unsigned char*)((char*)(t1004)) == (unsigned char)0) {
                        t1011 = (int)(t1004);
                        ((C_00e948b0*)(t1011))->FUN_00e948b0((unsigned int)(t1010), (unsigned int)(t1002));
                        t1008 = (float)((float)(a8));
                        *(unsigned char*)((char*)(t1004)) = (unsigned char)((int)1);
                    }
                    t1014 = (float)((float)(a12));
                    t1017 = (float)(t1014);
                    t1018 = (float)(t1017 / (float)(*(float*)g_015a8aac));
                    t1019 = (float)(t1008 / t1014);
                    t1020 = (float)(t1018 * t1019);
                    t1021 = (int)(t1010);
                    ((il2c_vc0*)(t1021))->s31((int)(t1002), (float)(t1020));
                    return;
                }
                if ((unsigned char)*(unsigned char*)((char*)(t1004)) != (unsigned char)0) {
                    t1028 = (int)((int)(a16));
                    t1029 = (int)(t1004);
                    ((C_00e94900*)(t1029))->FUN_00e94900((unsigned int)(t1028), (unsigned int)(t1002));
                    *(unsigned char*)((char*)(t1004)) = (unsigned char)((int)0);
                    t1035 = (int)(t1028);
                    t1005 = (int)((il2c_vc1*)(t1035))->s31((int)(t1002), (float)((float)1));
                }
            }
        }
    }
    return;
}
