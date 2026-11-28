// 0x00828e30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00828c30/s00828c30.cpp, src/game/Spui/_at_00820000.cpp.

struct il2c_vc0 {
    virtual void s0();
};

extern "C" unsigned char g_013f6b3c[];
struct C_00828d40 { int FUN_00828d40(unsigned int, unsigned int); };
struct C_0095bb20 { void FUN_0095bb20(); };
struct C_0095bc10 { int FUN_0095bc10(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00828e30
extern "C" int __cdecl FUN_00828e30(int a4, int a8, int a12)
{
    int t1002;
    int t1003;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1015;
    int t1017;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1028;
    int t1029;
    int t1030;
    t1002 = (int)((int)(a4));
    t1003 = (int)(t1002);
    ((C_0095bb20*)(t1003))->FUN_0095bb20();
    t1007 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_013f6b3c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1007 != (int)0) {
        t1010 = (int)((int)(a8));
        t1011 = (int)(t1007);
        t1012 = (int)((C_00828d40*)(t1011))->FUN_00828d40((unsigned int)(t1010), (unsigned int)((int)0));
    } else {
        t1012 = (int)((int)0);
    }
    t1015 = (int)((int)(a12));
    *(int*)((char*)(t1015)) = (int)(t1012);
    t1017 = (int)(t1012);
    ((il2c_vc0*)(t1017))->s0();
    t1022 = (int)(*(int*)((char*)(t1015)));
    t1023 = (int)(*(int*)((char*)(t1022) + 12));
    t1024 = (int)(t1002);
    t1025 = (int)((C_0095bc10*)(t1024))->FUN_0095bc10((unsigned int)(t1023));
    t1028 = (int)(*(int*)((char*)(t1015)));
    *(int*)((char*)(t1028) + 20) = (int)(t1025);
    t1029 = (int)(*(int*)((char*)(t1015)));
    t1030 = (int)(*(int*)((char*)(t1029) + 20));
    return (int)(t1030);
}
