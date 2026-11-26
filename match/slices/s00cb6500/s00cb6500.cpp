// 0x00cb6500: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00cb5620/s00cb5620.cpp, src/game/SPGonzago/SPWeapons.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};

extern "C" unsigned char g_00cb63c0[];
extern "C" unsigned char g_00cb63e0[];
extern "C" unsigned char g_0169a40c[];
struct C_00b35d30 { int FUN_00b35d30(); };
struct C_00b3d240 { int FUN_00b3d240(unsigned int, float, unsigned int, unsigned int); };

// @ 0x00cb6500
extern "C" int __cdecl FUN_00cb6500(int a4, float a8, int a12, int a16)
{
    int t1003;
    unsigned char t1004;
    int t1006;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1022;
    int t1023;
    t1003 = (int)((int)(a16));
    t1004 = (unsigned char)((int)0);
    t1006 = (int)((int)g_00cb63c0);
    if (t1003 != (int)0) {
        t1004 = (unsigned char)(*(unsigned char*)((char*)(t1003) + 8));
        *(unsigned char*)((char*)(t1003) + 8) = (unsigned char)((int)1);
        if ((unsigned char)*(unsigned char*)((char*)(t1003) + 9) != (unsigned char)0) {
            t1009 = (int)(t1003);
            t1006 = (int)((int)g_00cb63e0);
            t1012 = (int)((il2c_vc0*)(t1009))->s4();
            *(int*)g_0169a40c = (int)(t1012);
        }
    }
    t1013 = (int)((int)(a12));
    t1014 = (int)((int)(a4));
    t1015 = (int)((int)3);
    t1018 = (int)((C_00b3d240*)(t1014))->FUN_00b3d240((unsigned int)(t1014), (float)((float)(a8)), (unsigned int)(t1006), (unsigned int)(t1013));
    t1019 = (int)(t1018);
    t1022 = (int)((C_00b35d30*)(t1019))->FUN_00b35d30();
    if ((unsigned char)(t1022) != (unsigned char)0) {
        t1015 = (int)((int)0);
    }
    t1023 = (int)(t1015);
    if (t1003 != (int)0) {
        *(unsigned char*)((char*)(t1003) + 8) = (unsigned char)(t1004);
    }
    return (int)(t1023);
}
