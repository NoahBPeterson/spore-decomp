// 0x006f41e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/_at_006f0000.cpp, match/slices/s006f3410/s006f3410.cpp.

extern "C" unsigned char g_01619530[];
struct C_007c3c20 { void FUN_007c3c20(unsigned int); };
struct C_007c3c50 { void FUN_007c3c50(unsigned int); };
struct C_007c4be0 { void FUN_007c4be0(unsigned int, unsigned int); };
struct C_007c50b0 { void FUN_007c50b0(unsigned int, unsigned int, unsigned int); };

// @ 0x006f41e0
extern "C" int __fastcall FUN_006f41e0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int t1008;
    int t1010;
    int t1011;
    int t1013;
    int t1015;
    int t1016;
    int t1020;
    int t1021;
    int t9;
    int t1022;
    int t1023;
    int t1027;
    int t1031;
    int t1035;
    t1002 = (int)((int)(self));
    t1003 = (int)((int)0);
    t1004 = (int)(t1002 + (int)436);
    goto L6f41f0;
    L6f41f0:;
    if ((int)*(int*)((char*)(t1004)) >= (int)0) goto L6f4204;
    t1003 = (int)(t1003 + (int)1);
    t1004 = (int)(t1004 + (int)4);
    if ((unsigned int)(t1003) < (unsigned int)2) goto L6f41f0;
    L6f41fe:;
    t1006 = (int)((int)0);
    return (int)(t1006);
    L6f4204:;
    if (t1003 < (int)0) goto L6f41fe;
    t1008 = (int)(*(int*)((char*)(t1002) + 312));
    t1010 = (int)(*(int*)((char*)(t1008) + (t1003)*4));
    t1011 = (int)((int)65535);
    if ((unsigned short)*(unsigned short*)((char*)(t1010) + 8) == (unsigned short)(t1011)) {
        t1013 = (int)((int)0);
        return (int)(t1013);
    }
    t1015 = (int)((int)(a4));
    t1016 = (int)(*(int*)((char*)(t1002) + 372));
    ((C_007c50b0*)(t1016))->FUN_007c50b0((unsigned int)(t1015), (unsigned int)((int)0), (unsigned int)((int)0));
    t1020 = (int)(*(unsigned short*)((char*)(t1010) + 8));
    t1021 = (int)(*(int*)((char*)(t1010) + 76));
    t9 = (int)(t1020 << (int)3);
    t1022 = (int)(t1021 + t9);
    t1023 = (int)(*(int*)((char*)(t1002) + 372));
    ((C_007c4be0*)(t1023))->FUN_007c4be0((unsigned int)(t1022), (unsigned int)((int)1));
    t1027 = (int)(*(int*)((char*)(t1002) + 372));
    ((C_007c3c20*)(t1027))->FUN_007c3c20((unsigned int)((int)g_01619530));
    t1031 = (int)(*(int*)((char*)(t1002) + 372));
    ((C_007c3c50*)(t1031))->FUN_007c3c50((unsigned int)((int)7));
    t1035 = (int)(*(int*)((char*)(t1002) + 372));
    return (int)(t1035);
}
