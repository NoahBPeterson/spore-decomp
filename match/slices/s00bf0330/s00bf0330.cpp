// 0x00bf0330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bf0000.cpp, match/slices/s00befc40/s00befc40.cpp.

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
    virtual int s22();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};

extern "C" unsigned char g_017f243b[];
struct C_00aeb760 { int FUN_00aeb760(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00b3d4a0(...);
struct C_00bd92d0 { int FUN_00bd92d0(unsigned int); };
struct C_00ce6950 { int FUN_00ce6950(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_01021260(...);

// @ 0x00bf0330
extern "C" void __fastcall FUN_00bf0330(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1006;
    int t1008;
    int t1013;
    int t1016;
    int t1017;
    int t1018;
    int t1022;
    int t1024;
    int t1027;
    int t1030;
    int t1031;
    int t1034;
    int t1037;
    int t1038;
    int t1039;
    int t1042;
    t1001 = (int)((int)(a4));
    t1006 = (int)((int)(self));
    t1008 = (int)((il2c_vc0*)((t1001 + (int)(288))))->s22();
    if ((unsigned char)(t1008) != (unsigned char)0) {
        if ((unsigned int)*(int*)((char*)(t1006) + 1076) > (unsigned int)4) {
            if ((int)*(int*)((char*)(t1006) + 1080) == (int)0) {
                t1013 = (int)FUN_00b3d4a0();
                t1016 = (int)(t1001);
                t1017 = (int)(t1013);
                *(int*)((char*)(t1006) + 1076) = (int)((int)0);
                *(int*)((char*)(t1006) + 1080) = (int)(t1001);
                t1018 = (int)((C_00bd92d0*)(t1016))->FUN_00bd92d0((unsigned int)(t1006));
                if (t1018 != (int)0) {
                    t1022 = (int)(t1018);
                    t1024 = (int)((il2c_vc1*)(t1022))->s3((int)((int)g_017f243b));
                    t1027 = (int)(t1024);
                    if (t1027 != (int)0) goto Lbf03ac;
                }
                t1030 = (int)(t1006);
                t1031 = (int)((il2c_vc2*)(t1030))->s3((int)((int)g_017f243b));
                t1027 = (int)(t1031);
                Lbf03ac:;
                t1034 = (int)FUN_01021260();
                t1037 = (int)(*(int*)((char*)(t1034) + 316));
                t1038 = (int)(t1037);
                t1039 = (int)((C_00ce6950*)(t1038))->FUN_00ce6950((unsigned int)((int)(-604797505)), (unsigned int)((int)(-2094318940)), (unsigned int)((int)0));
                t1042 = (int)(t1017);
                t1008 = (int)((C_00aeb760*)(t1042))->FUN_00aeb760((unsigned int)(t1027), (unsigned int)(t1001), (unsigned int)(t1039));
            }
        }
    }
    return;
}
