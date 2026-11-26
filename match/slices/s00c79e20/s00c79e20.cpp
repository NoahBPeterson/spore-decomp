// 0x00c79e20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c793e0/s00c793e0.cpp, src/game/SPGonzago/SPPlayer.cpp.

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
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual int s36();
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
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual int s46(int);
};

extern "C" unsigned char g_01654c02[];
extern "C" int __cdecl FUN_00b3d300(...);
extern "C" int __cdecl FUN_00b5b800(...);
struct C_00bfc5f0 { int FUN_00bfc5f0(); };
struct C_00c227d0 { int FUN_00c227d0(unsigned int); };
struct C_00c227e0 { int FUN_00c227e0(); };
struct C_00db5b30 { void FUN_00db5b30(unsigned int); };

// @ 0x00c79e20
extern "C" void __fastcall FUN_00c79e20(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1003;
    int t1006;
    int t2;
    int t1007;
    int t3;
    int t1008;
    int t1012;
    int t1013;
    int t1016;
    int t1019;
    int t1020;
    int t1024;
    int t1029;
    int t1030;
    int t1031;
    int t1036;
    int t1037;
    int t1040;
    int t1044;
    int t1049;
    t1001 = (int)((int)(a4));
    if ((unsigned int)(t1001) <= (unsigned int)9) {
        t1003 = (int)(*(int*)((char*)((int)(self)) + 4412));
        t1006 = (int)((int)(a8));
        t2 = (int)(t1001 << (int)2);
        t1007 = (int)(t1001 + t2);
        t3 = (int)(t1007 << (int)2);
        t1008 = (int)(t1003 + t3);
        ((C_00db5b30*)(t1008))->FUN_00db5b30((unsigned int)(t1006));
        t1012 = (int)(*(int*)((char*)(t1006)));
        t1013 = (int)(*(int*)((char*)(t1006) + 4));
        *(int*)&(a8) = (int)(t1013);
        t1016 = (int)FUN_00b5b800();
        if (t1016 == (int)g_01654c02) {
            t1019 = (int)FUN_00b3d300();
            t1020 = (int)(t1019);
            t1016 = (int)((C_00bfc5f0*)(t1020))->FUN_00bfc5f0();
            if (t1016 != (int)0) {
                t1024 = (int)(t1016);
                t1016 = (int)((il2c_vc0*)(t1024))->s36();
                t1029 = (int)(*(int*)((char*)(t1016)));
                t1030 = (int)(*(int*)((char*)(t1016) + 4));
                if (t1029 != t1030) {
                    do {
                        t1031 = (int)(*(int*)((char*)(t1029)));
                        if (t1031 != (int)0) {
                            t1016 = (int)((il2c_vc1*)(t1031))->s3((int)((int)1326933570));
                            t1036 = (int)(t1016);
                            if (t1036 != (int)0) {
                                t1037 = (int)(t1036);
                                t1016 = (int)((C_00c227e0*)(t1037))->FUN_00c227e0();
                                if (t1016 == (int)(a4)) {
                                    t1040 = (int)(t1036);
                                    t1016 = (int)((C_00c227d0*)(t1040))->FUN_00c227d0((unsigned int)((int)(-1)));
                                }
                            }
                        }
                        t1029 = (int)(t1029 + (int)4);
                    } while (t1029 != t1030);
                    t1013 = (int)((int)(a8));
                }
                t1001 = (int)((int)(a4));
            }
        }
        if (t1012 != t1013) {
            do {
                t1044 = (int)(*(int*)((char*)(t1012)));
                if (t1044 != (int)0) {
                    t1016 = (int)((il2c_vc2*)(t1044))->s46((int)((int)1326933570));
                    if (t1016 != (int)0) {
                        t1049 = (int)(t1016);
                        t1016 = (int)((C_00c227d0*)(t1049))->FUN_00c227d0((unsigned int)(t1001));
                    }
                }
                t1012 = (int)(t1012 + (int)4);
            } while (t1012 != t1013);
        }
    }
    return;
}
