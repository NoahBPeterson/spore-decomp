// 0x00e94ad0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
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
    virtual void s29(int, int, float, int);
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
    virtual void s28(int, int, int, float, int);
};
struct il2c_vc2 {
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
    virtual void s29(int, int, float, int);
};
struct il2c_vc3 {
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
    virtual int s28(int, int, int, float, int);
};

extern "C" unsigned char g_015a8a40[];
extern "C" unsigned char g_015a8a44[];

// @ 0x00e94ad0
extern "C" void __stdcall FUN_00e94ad0(int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    unsigned char t3;
    int t1006;
    int t1010;
    int t1012;
    int t1018;
    int t1019;
    int t1025;
    int t1026;
    int t1032;
    int t1033;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1003 = (int)((int)(a8));
        if (t1003 != (int)0) {
            t1004 = (int)(*(int*)((char*)(t1003) + 4));
            t1005 = (int)((unsigned int)(t1004) >> (int)14);
            t3 = (unsigned char)((unsigned char)(t1005) & (unsigned char)1);
            if (t3 != (unsigned char)0) {
                t1006 = (int)((int)(*(int*)g_015a8a44));
                t1010 = (int)((int)(a12));
                t1012 = (int)(t1001);
                ((il2c_vc0*)(t1012))->s29((int)(t1003), (int)(t1006), (float)((float)0), (int)(t1010));
                t1018 = (int)((int)(*(int*)g_015a8a44));
                t1019 = (int)(t1001);
                ((il2c_vc1*)(t1019))->s28((int)(t1003), (int)(t1018), (int)((int)0), (float)((float)0), (int)(t1010));
                t1025 = (int)((int)(*(int*)g_015a8a40));
                t1026 = (int)(t1001);
                ((il2c_vc2*)(t1026))->s29((int)(t1003), (int)(t1025), (float)((float)0), (int)(t1010));
                t1032 = (int)((int)(*(int*)g_015a8a40));
                t1033 = (int)(t1001);
                t1005 = (int)((il2c_vc3*)(t1033))->s28((int)(t1003), (int)(t1032), (int)((int)2), (float)((float)0), (int)(t1010));
            }
        }
    }
    return;
}
