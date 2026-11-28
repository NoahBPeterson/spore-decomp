// 0x010377f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPSpaceGfx.cpp, match/slices/s010377f0/s010377f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1(int);
};

extern "C" unsigned char g_0149996c[];
extern "C" unsigned char g_015b77b4[];
extern "C" unsigned char g_016df344[];
extern "C" unsigned char g_016e06de[];
extern "C" unsigned char g_016e06e1[];
extern "C" unsigned char g_016e06e2[];
extern "C" unsigned char g_016e06e3[];
extern "C" unsigned char g_016e06e4[];
extern "C" unsigned char g_016e06e8[];
struct C_008414c0 { int FUN_008414c0(); };
struct C_00a6c9f0 { void FUN_00a6c9f0(unsigned int, unsigned int, float, unsigned int); };
extern "C" void __cdecl FUN_00c2e4e0(...);
struct C_01021080 { int FUN_01021080(); };
extern "C" int __cdecl FUN_01021080(...);
extern "C" int __cdecl FUN_01021260(...);
struct C_01034d40 { void FUN_01034d40(unsigned int); };
extern "C" void __cdecl FUN_01036af0(...);
extern "C" void __cdecl FUN_01037760(...);

// @ 0x010377f0
// @ 0x010377f0
extern "C" void __fastcall FUN_010377f0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1011;
    int t1012;
    int t1019;
    int t1022;
    int t1025;
    int t1028;
    int t1032;
    int t1038;
    int t1041;
    int t1042;
    int t1046;
    int t1049;
    int t1050;
    t1002 = (int)((int)(self));
    t1003 = (int)((C_01021080*)((int)(self)))->FUN_01021080();
    switch ((unsigned int)(t1003)) { case 1: goto L1037815; case 2: goto L1037802; default: goto L103781a; }
    goto L1037802;
    goto L1037815;
    goto L103781a;
    L1037802:;
    FUN_01037760();
    t1011 = (int)((int)(a4));
    t1012 = (int)(t1002);
    ((C_01034d40*)(t1012))->FUN_01034d40((unsigned int)(t1011));
    goto L103781a;
    L1037815:;
    FUN_01036af0();
    L103781a:;
    if ((unsigned char)(*(unsigned char*)g_016e06de) != (unsigned char)0) {
        t1019 = (int)FUN_01021080();
        if (t1019 == (int)0) {
            t1022 = (int)FUN_01021260();
            if (t1022 == (int)0) goto L10378e9;
            t1025 = (int)(t1022);
            t1022 = (int)((C_008414c0*)(t1025))->FUN_008414c0();
            if (t1022 == (int)0) goto L10378e9;
            t1028 = (int)(t1022);
            ((C_00a6c9f0*)(t1028))->FUN_00a6c9f0((unsigned int)((int)g_016df344), (unsigned int)((int)g_015b77b4), (float)((float)(*(float*)g_0149996c)), (unsigned int)((int)0));
        }
    }
    if ((unsigned char)(*(unsigned char*)g_016e06e1) != (unsigned char)0) {
        t1032 = (int)FUN_01021080();
        if (t1032 == (int)0) {
            FUN_00c2e4e0();
        }
    }
    if ((unsigned char)(*(unsigned char*)g_016e06e2) != (unsigned char)0) {
        t1038 = (int)FUN_01021080();
        if (t1038 == (int)0) {
            t1041 = (int)((int)(*(int*)g_016e06e8));
            t1042 = (int)((int)(*(int*)g_016e06e4));
            FUN_00c2e4e0((unsigned int)((int)1), (unsigned int)(t1042), (unsigned int)(t1041));
        }
    }
    if ((unsigned char)(*(unsigned char*)g_016e06e3) != (unsigned char)0) {
        t1046 = (int)FUN_01021080();
        if (t1046 == (int)0) {
            t1049 = (int)((int)(*(int*)g_016e06e8));
            t1050 = (int)((int)(*(int*)g_016e06e4));
            FUN_00c2e4e0((unsigned int)((int)0), (unsigned int)(t1050), (unsigned int)(t1049));
        }
    }
    *(int*)&(a4) = (int)((int)0);
    ((il2c_vc0*)((t1002 + (int)(200))))->s1((int)((int)(a4)));
    return;
    L10378e9:;
    return;
}
