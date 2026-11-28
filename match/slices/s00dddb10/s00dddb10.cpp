// 0x00dddb10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00ddcdc0/s00ddcdc0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};
struct il2c_gm1 { void m(unsigned int, unsigned int); };
typedef void (il2c_gm1::*il2c_gp1)(unsigned int, unsigned int);

extern "C" unsigned char g_016a1344[];
struct C_0067caa0 { int FUN_0067caa0(); };
extern "C" int __cdecl FUN_0067caa0(...);
struct C_00de44a0 { int FUN_00de44a0(unsigned int, float, float, unsigned int); };

// @ 0x00dddb10
// @ 0x00dddb10
extern "C" bool __stdcall FUN_00dddb10(int a4, float a8, float a12, int a16)
{
    int t1000;
    int t1002;
    int t1003;
    int t1004;
    bool t1007;
    int t1011;
    int t1014;
    int t1015;
    int t1019;
    int t1020;
    int t1022;
    int t1023;
    int t1024;
    int t1028;
    bool t1034;
    t1000 = (int)((int)(*(int*)g_016a1344));
    t1002 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1003 = (int)((int)(a16));
        t1004 = (int)((C_00de44a0*)(t1000))->FUN_00de44a0((unsigned int)(t1002), (float)((float)(a8)), (float)((float)(a12)), (unsigned int)(t1003));
        t1000 = (int)((int)(*(int*)g_016a1344));
    }
    if ((int)*(int*)((char*)(t1000) + 264) == (int)4) {
        t1007 = true;
        return (bool)(t1007);
    }
    if (t1002 == (int)1002) {
        t1011 = (int)((C_0067caa0*)(t1000))->FUN_0067caa0();
        t1014 = (int)(t1011);
        t1015 = (int)FUN_0067caa0();
        t1019 = (int)(t1015);
        t1020 = (int)(*(int*)((char*)(t1019)));
        t1022 = (int)(t1014);
        t1023 = (int)(t1020 + (int)88);
        t1024 = (int)((il2c_vc0*)(t1022))->s1();
        t1028 = (int)(t1019);
        (((il2c_gm1*)(t1028))->*(*(il2c_gp1*)&(*(int*)((char*)(t1023)))))((unsigned int)((int)1), (unsigned int)(t1024));
        t1004 = (int)((int)(*(int*)g_016a1344));
        *(unsigned char*)((char*)(t1004) + 380) = (unsigned char)((int)1);
    }
    t1034 = false;
    return (bool)(t1034);
}
