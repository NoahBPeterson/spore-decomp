// 0x00de9e20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00de9a00/s00de9a00.cpp.

struct C_00b26d00 { int FUN_00b26d00(); };
struct C_00b26db0 { int FUN_00b26db0(); };
struct C_00de97a0 { int FUN_00de97a0(unsigned int, unsigned int); };
struct C_00de97f0 { void FUN_00de97f0(unsigned int, unsigned int, unsigned int); };

// @ 0x00de9e20
extern "C" void __fastcall FUN_00de9e20(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1018;
    int t1017;
    int t1019;
    int v_l188[47];
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1033;
    int t1034;
    int t1035;
    int t1039;
    int t1047;
    int t1048;
    int t1049;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1006 = (int)(*(int*)((char*)(t1004)));
    t1007 = (int)(t1005);
    t1008 = (int)(t1007 - t1006);
    t1018 = (int)(t1008 / (int)188);
    t1017 = (int)((int)(a4));
    if ((unsigned int)(t1017) > (unsigned int)(t1018)) {
        t1019 = (int)((int)&v_l188);
        t1022 = (int)((C_00b26d00*)(t1019))->FUN_00b26d00();
        t1023 = (int)(*(int*)((char*)(t1004) + 4));
        t1024 = (int)(t1023);
        t1025 = (int)(t1024 - (int)*(int*)((char*)(t1004)));
        t1033 = (int)(t1025 / (int)188);
        t1034 = (int)(t1017 - t1033);
        t1035 = (int)(t1004);
        ((C_00de97f0*)(t1035))->FUN_00de97f0((unsigned int)(t1023), (unsigned int)(t1034), (unsigned int)(t1022));
        t1039 = (int)((int)&v_l188);
        ((C_00b26db0*)(t1039))->FUN_00b26db0();
        return;
    }
    t1047 = (int)(t1017 * (int)188);
    t1048 = (int)(t1047 + t1006);
    t1049 = (int)(t1004);
    ((C_00de97a0*)(t1049))->FUN_00de97a0((unsigned int)(t1048), (unsigned int)(t1005));
    return;
}
