// 0x008d6410: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008d62f0/s008d62f0.cpp, src/game/UTFSpore_Win32/_at_008d0000.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
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
};

extern "C" unsigned char g_01436624[];
extern "C" int __cdecl FUN_00921580(...);
struct C_009221b0 { void FUN_009221b0(unsigned int); };
struct C_00922270 { int FUN_00922270(); };

// @ 0x008d6410
extern "C" bool __fastcall FUN_008d6410(char* self, int edx_unused)
{
    int t1004;
    int t1006;
    int t1007;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1022;
    int t1023;
    int t1026;
    int t1029;
    unsigned char t9;
    int t1032;
    int t1038;
    int t1039;
    bool t1046;
    t1004 = (int)((int)(self));
    t1006 = (int)(t1004 + (int)312);
    t1007 = (int)(t1006);
    ((C_009221b0*)(t1007))->FUN_009221b0((unsigned int)((int)g_01436624));
    t1011 = (int)(*(int*)((char*)(t1004) + 148));
    t1012 = (int)(t1004 + (int)144);
    if (t1011 != t1012) {
        do {
            t1013 = (int)(*(int*)((char*)(t1011) + 56));
            t1014 = (int)(t1011 + (int)56);
            t1015 = (int)((int)0);
            if (t1013 != t1014) {
                do {
                    t1013 = (int)(*(int*)((char*)(t1013)));
                    t1015 = (int)(t1015 + (int)1);
                } while (t1013 != t1014);
                if (t1015 == (int)1) {
                    t1016 = (int)(*(int*)((char*)(t1014)));
                    t1017 = (int)(*(int*)((char*)(t1016) + 8));
                    t1022 = (int)((il2c_vc0*)(t1017))->s6();
                    t1023 = (int)(t1022);
                    t1026 = (int)(t1023);
                    t1029 = (int)((il2c_vc1*)(t1026))->s4();
                    t9 = (unsigned char)((unsigned char)(t1029) & (unsigned char)2);
                    if (t9 != (unsigned char)0) {
                        t1032 = (int)(t1023);
                        ((il2c_vc2*)(t1032))->s13();
                    }
                }
            }
            t1038 = (int)FUN_00921580((unsigned int)(t1011));
            t1011 = (int)(t1038);
        } while (t1011 != t1012);
    }
    t1039 = (int)(t1006);
    ((C_00922270*)(t1039))->FUN_00922270();
    t1046 = true;
    return (bool)(t1046);
}
