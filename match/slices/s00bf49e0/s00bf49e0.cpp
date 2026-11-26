// 0x00bf49e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bf0000.cpp, match/slices/s00bf4170/s00bf4170.cpp.

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
    virtual int s3(int);
};

extern "C" unsigned char g_0137e8e0[];
extern "C" unsigned char g_01654c05[];
struct C_00b18e40 { int FUN_00b18e40(); };
extern "C" int __cdecl FUN_00b5b800(...);
struct C_00bf3b50 { int FUN_00bf3b50(unsigned int); };
struct C_00bf45f0 { int FUN_00bf45f0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_01002bd0(...);

// @ 0x00bf49e0
extern "C" void __fastcall FUN_00bf49e0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1008;
    int t1011;
    int t1012;
    int t1015;
    int t1018;
    int t1019;
    int t1022;
    int t1023;
    int t1024;
    int t1033;
    int t1036;
    int t1037;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1002 != (int)0) {
        t1008 = (int)(t1002);
        t1011 = (int)((il2c_vc0*)(t1008))->s3((int)((int)(-291823054)));
        t1012 = (int)(t1011);
        if (t1012 != (int)0) {
            *(unsigned char*)&(a4) = (unsigned char)((int)0);
            t1015 = (int)FUN_00b5b800();
            if (t1015 == (int)g_01654c05) {
                t1018 = (int)FUN_01002bd0();
                t1019 = (int)(t1018);
                t1022 = (int)((C_00b18e40*)(t1019))->FUN_00b18e40();
                *(unsigned char*)&(a4) = (unsigned char)((unsigned char)(t1022));
            }
            t1023 = (int)((int)(a4));
            t1024 = (int)(t1004);
            ((C_00bf45f0*)(t1024))->FUN_00bf45f0((unsigned int)(t1012), (unsigned int)(t1023));
            return;
        }
        t1033 = (int)(t1002);
        t1036 = (int)((il2c_vc1*)(t1033))->s3((int)((int)g_0137e8e0));
        if (t1036 != (int)0) {
            t1037 = (int)(t1004);
            t1036 = (int)((C_00bf3b50*)(t1037))->FUN_00bf3b50((unsigned int)(t1036));
        }
    }
    return;
}
