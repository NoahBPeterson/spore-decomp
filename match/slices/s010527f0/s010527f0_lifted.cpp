// 0x010527f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolStrategies.cpp, match/slices/s010527f0/s010527f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8();
};

extern "C" unsigned char g_0149af94[];
extern "C" void __cdecl FUN_00435ed0(...);
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_00a206f0(...);
struct C_00b3d3e0 { int FUN_00b3d3e0(unsigned int, unsigned int, unsigned int); };
extern "C" int __stdcall FUN_00b3d3e0(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
struct C_00dd7620 { void FUN_00dd7620(); };
struct C_00dd8640 { int FUN_00dd8640(); };

// @ 0x010527f0
extern "C" int __cdecl FUN_010527f0(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1003;
    int t1004;
    int t1007;
    int t1011;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1023;
    int t1025;
    t1000 = (int)((int)0);
    if ((unsigned char)(a12) != (unsigned char)(t1000)) {
        t1001 = (int)((int)(a4));
        t1003 = (int)((int)(a8));
        if ((int)*(int*)((char*)(t1001) + 368) != t1003) {
            *(int*)((char*)(t1001) + 368) = (int)(t1003);
            t1004 = (int)((C_00b3d3e0*)(t1001))->FUN_00b3d3e0((unsigned int)(t1003), (unsigned int)(t1000), (unsigned int)(t1000));
            t1007 = (int)(t1004);
            ((C_00dd7620*)(t1007))->FUN_00dd7620();
            t1011 = (int)FUN_00b3d3e0((unsigned int)(t1003), (unsigned int)((int)320511828), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)1), (unsigned int)((int)0));
            t1014 = (int)(t1011);
            t1015 = (int)((C_00dd8640*)(t1014))->FUN_00dd8640();
            t1018 = (int)(t1015);
            t1019 = (int)FUN_00a206f0();
            if (t1019 != (int)0) {
                t1023 = (int)(t1019);
                t1025 = (int)((il2c_vc0*)(t1023))->s8();
            } else {
                t1025 = (int)((int)0);
            }
            FUN_00435ed0((unsigned int)((int)FUN_00932e80((unsigned int)((int)g_0149af94), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1))), (unsigned int)(t1025));
            t1000 = (int)(t1018);
        }
    }
    return (int)(t1000);
}
