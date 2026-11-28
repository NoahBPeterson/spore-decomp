// 0x00a1a500: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPAudio/AudioResponseCurve.cpp, match/slices/s00a196f0/s00a196f0.cpp.

extern "C" void __cdecl FUN_00951bf0(...);
struct C_00a1a2f0 { int FUN_00a1a2f0(unsigned int, unsigned int, unsigned int); };

// @ 0x00a1a500
extern "C" int __fastcall FUN_00a1a500(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1016;
    int t1012;
    int t1017;
    int v_l20[5];
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t6;
    int t1027;
    int t7;
    int t1028;
    int t1032;
    int t1039;
    int t11;
    int t1040;
    int t1041;
    int t1042;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1006 = (int)(*(int*)((char*)(t1004)));
    t1007 = (int)(t1005);
    t1008 = (int)(t1007 - t1006);
    t1016 = (int)(t1008 / (int)20);
    t1012 = (int)((int)(a4));
    if ((unsigned int)(t1012) > (unsigned int)(t1016)) {
        t1017 = (int)((int)0);
        (*(int*)&v_l20[0]) = (int)(t1017);
        (*(int*)&v_l20[1]) = (int)(t1017);
        (*(int*)&v_l20[2]) = (int)(t1017);
        (*(int*)&v_l20[3]) = (int)(t1017);
        (*(int*)&v_l20[4]) = (int)(t1017);
        t1018 = (int)((int)&v_l20);
        t1019 = (int)(t1012 - t1016);
        t1020 = (int)(t1004);
        t1021 = (int)((C_00a1a2f0*)(t1020))->FUN_00a1a2f0((unsigned int)(t1005), (unsigned int)(t1019), (unsigned int)(t1018));
        return (int)(t1021);
    }
    t6 = (int)(t1012 << (int)2);
    t1027 = (int)(t1012 + t6);
    t7 = (int)(t1027 << (int)2);
    t1028 = (int)(t1006 + t7);
    FUN_00951bf0((unsigned int)(t1005), (unsigned int)(t1005), (unsigned int)(t1028));
    t1032 = (int)(t1005 - t1028);
    t1039 = (int)(t1032 / (int)(-20));
    t11 = (int)(t1039 << (int)2);
    t1040 = (int)(t1039 + t11);
    t1041 = (int)(t1040 + t1040);
    t1042 = (int)(t1041 + t1041);
    *(int*)((char*)(t1004) + 4) += t1042;
    return (int)(t1039);
}
