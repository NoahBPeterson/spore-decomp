// 0x00ae9040: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ae8390/s00ae8390.cpp.

extern "C" unsigned char g_016dc798[];
extern "C" int __stdcall FUN_00b3d2a0(unsigned int);
struct C_00ba6dc0 { int FUN_00ba6dc0(); };
struct C_00ba9370 { int FUN_00ba9370(); };
extern "C" int __stdcall FUN_00feb9f0(unsigned int);
struct C_00fee190 { int FUN_00fee190(); };
struct C_0100e730 { int FUN_0100e730(unsigned int, unsigned int); };

// @ 0x00ae9040
extern "C" bool __stdcall FUN_00ae9040(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1019;
    bool t1020;
    int t1022;
    int t1025;
    int t1026;
    int t1029;
    int t1030;
    int t1033;
    int t1034;
    bool t1035;
    bool t1037;
    t1000 = (int)((int)(a8));
    t1005 = (int)FUN_00b3d2a0((unsigned int)(t1000));
    t1006 = (int)(t1005);
    t1009 = (int)((C_00ba6dc0*)(t1006))->FUN_00ba6dc0();
    t1010 = (int)(t1009);
    t1013 = (int)FUN_00feb9f0((unsigned int)(t1010));
    t1014 = (int)(t1013);
    t1017 = (int)((C_00fee190*)(t1014))->FUN_00fee190();
    if ((unsigned char)(t1017) != (unsigned char)0) {
        t1018 = (int)((int)(a12));
        t1019 = (int)((int)(a16));
        *(int*)((char*)(t1018)) = (int)((int)(-923011113));
        *(int*)((char*)(t1019)) = (int)((int)339485225);
        t1020 = true;
        return (bool)(t1020);
    }
    t1022 = (int)((int)(a4));
    t1025 = (int)FUN_00b3d2a0((unsigned int)(t1022));
    t1026 = (int)(t1025);
    t1029 = (int)((C_00ba9370*)(t1026))->FUN_00ba9370();
    if (t1029 != (int)0) {
        t1030 = (int)((int)(*(int*)g_016dc798));
        t1029 = (int)((C_0100e730*)(t1030))->FUN_0100e730((unsigned int)(t1010), (unsigned int)(t1029));
        if ((unsigned char)(t1029) != (unsigned char)0) {
            t1033 = (int)((int)(a12));
            t1034 = (int)((int)(a16));
            *(int*)((char*)(t1033)) = (int)((int)(-923011113));
            *(int*)((char*)(t1034)) = (int)((int)1473469523);
            t1035 = true;
            return (bool)(t1035);
        }
    }
    t1037 = false;
    return (bool)(t1037);
}
