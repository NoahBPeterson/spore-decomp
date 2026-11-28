// 0x0094d270: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/_at_00940000.cpp, match/slices/s0094cac0/s0094cac0.cpp.

extern "C" unsigned char g_0143f9c4[];
struct C_009221b0 { void FUN_009221b0(unsigned int); };
struct C_00922270 { void FUN_00922270(); };
extern "C" int __cdecl FUN_0094c130(...);
extern "C" int __cdecl FUN_0094c190(...);
extern "C" int __cdecl FUN_0094c1b0(...);
struct C_0094cf60 { void FUN_0094cf60(unsigned int, unsigned int, unsigned int); };
struct C_0094d0e0 { int FUN_0094d0e0(unsigned int); };

// @ 0x0094d270
extern "C" int __fastcall FUN_0094d270(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1008;
    int t1014;
    int t1015;
    int t1019;
    int t1020;
    int t1023;
    int t1024;
    int t1030;
    int t1032;
    int t1034;
    int t1037;
    int t1038;
    int t1042;
    int t1046;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1005 = (int)FUN_0094c190((unsigned int)(t1002));
    if ((unsigned char)(t1005) != (unsigned char)0) {
        t1008 = (int)FUN_0094c130((unsigned int)(t1002));
        return (int)(t1008);
    }
    t1014 = (int)(t1004 + (int)40);
    t1015 = (int)(t1014);
    ((C_009221b0*)(t1015))->FUN_009221b0((unsigned int)((int)g_0143f9c4));
    t1019 = (int)(t1004);
    t1020 = (int)((C_0094d0e0*)(t1019))->FUN_0094d0e0((unsigned int)(t1002));
    if (t1020 != (int)0) {
        t1023 = (int)(*(int*)((char*)(t1020)));
        t1024 = (int)(t1014);
        ((C_00922270*)(t1024))->FUN_00922270();
        t1030 = (int)(t1023);
        return (int)(t1030);
    }
    t1032 = (int)(*(int*)((char*)(t1004) + 4));
    t1034 = (int)FUN_0094c1b0((unsigned int)(t1002), (unsigned int)(t1032));
    t1037 = (int)(t1034);
    if (t1037 != (int)(-1)) {
        t1038 = (int)(t1004);
        ((C_0094cf60*)(t1038))->FUN_0094cf60((unsigned int)(t1002), (unsigned int)(t1037), (unsigned int)((int)0));
    }
    t1042 = (int)(t1014);
    ((C_00922270*)(t1042))->FUN_00922270();
    t1046 = (int)(t1037);
    return (int)(t1046);
}
