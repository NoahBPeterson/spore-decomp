// 0x00b23940: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGameNounManager.cpp, match/slices/s00b230b0/s00b230b0.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
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
};
struct il2c_vc3 {
    virtual void s0();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_01654c01[];
extern "C" unsigned char g_01654c02[];
struct C_00b20c60 { int FUN_00b20c60(unsigned int); };
struct C_00b20e40 { int FUN_00b20e40(unsigned int, unsigned int); };
struct C_00b23510 { void FUN_00b23510(); };
extern "C" int __cdecl FUN_00b5b800(...);
struct C_00c6ace0 { void FUN_00c6ace0(unsigned int); };

// @ 0x00b23940
extern "C" int __fastcall FUN_00b23940(char* self, int edx_unused, int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1001;
    int t1002;
    int t1005;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    unsigned char t1017;
    int t1019;
    int t1022;
    int t1023;
    int t1024;
    int t1027;
    int t1033;
    int t1040;
    int t1044;
    int t1048;
    int t1051;
    int t1057;
    int t1063;
    int t1064;
    t1001 = (int)((int)(a8));
    t1002 = (int)((int)0);
    t1005 = (int)((int)(self));
    if (t1001 != (int)0) {
        t1009 = (int)((C_00b20c60*)((int)(self)))->FUN_00b20c60((unsigned int)((int)29245838));
        t1010 = (int)((int)(a20));
        t1011 = (int)(t1009);
        t1012 = (int)((int)(a12));
        *(int*)((char*)(t1011) + 244) = (int)(t1012);
        t1013 = (int)((int)(a4));
        *(int*)((char*)(t1011) + 348) = (int)(t1010);
        *(int*)((char*)(t1011) + 164) = (int)(t1001);
        t1014 = (int)(*(int*)((char*)(t1013)));
        *(int*)((char*)(t1011) + 52) = (int)(t1014);
        t1015 = (int)(*(int*)((char*)(t1013) + 4));
        *(int*)((char*)(t1011) + 56) = (int)(t1015);
        t1016 = (int)(*(int*)((char*)(t1013) + 8));
        t1017 = (unsigned char)((unsigned char)(a16));
        *(int*)((char*)(t1011) + 60) = (int)(t1016);
        *(unsigned char*)((char*)(t1011) + 132) = (unsigned char)(t1017);
        if ((unsigned char)(a24) != (unsigned char)0) {
            t1019 = (int)(t1005);
            t1022 = (int)((C_00b20e40*)(t1019))->FUN_00b20e40((unsigned int)(t1013), (unsigned int)(t1011));
            t1023 = (int)(*(int*)((char*)(t1011) + 352));
            t1024 = (int)(t1022);
            if (t1024 != t1023) {
                if (t1024 != (int)0) {
                    t1027 = (int)(t1024);
                    ((il2c_vc0*)(t1027))->s0();
                }
                *(int*)((char*)(t1011) + 352) = (int)(t1024);
                if (t1023 != (int)0) {
                    t1033 = (int)(t1023);
                    ((il2c_vc1*)(t1033))->s1();
                }
            }
        }
        t1040 = (int)(t1011);
        ((il2c_vc2*)(t1040))->s21();
        if ((unsigned char)(a16) != (unsigned char)0) {
            if ((int)*(int*)((char*)(t1005) + 88) != (int)0) {
                t1044 = (int)(t1005);
                ((C_00b23510*)(t1044))->FUN_00b23510();
            }
            t1048 = (int)(*(int*)((char*)(t1005) + 88));
            if (t1011 != t1048) {
                t1051 = (int)(t1011);
                ((il2c_vc3*)(t1051))->s0();
                *(int*)((char*)(t1005) + 88) = (int)(t1011);
                if (t1048 != (int)0) {
                    t1057 = (int)(t1048);
                    ((il2c_vc4*)(t1057))->s1();
                }
            }
        }
        t1063 = (int)FUN_00b5b800();
        if (t1063 != (int)g_01654c01) {
            if (t1063 != (int)g_01654c02) goto Lb23a2e;
        }
        t1064 = (int)(t1011);
        ((C_00c6ace0*)(t1064))->FUN_00c6ace0((unsigned int)((int)0));
        Lb23a2e:;
        t1002 = (int)(t1011);
    }
    return (int)(t1002);
}
