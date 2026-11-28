// 0x0084b260: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/EAIME.cpp, match/slices/s0084af40/s0084af40.cpp.

extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];
struct C_0084aad0 { int FUN_0084aad0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_0084ab40(...);
struct C_0084afc0 { int FUN_0084afc0(unsigned int, unsigned int, unsigned int); };

// @ 0x0084b260
// @ 0x0084b260
extern "C" void __fastcall FUN_0084b260(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int v_l16[4];
    int t1011;
    int t1012;
    int t1013;
    int t1019;
    int t1021;
    int t1022;
    int t1023;
    int t1026;
    int t1027;
    int t1031;
    int t1032;
    int t1033;
    int t1034;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1006 = (int)(*(int*)((char*)(t1004)));
    t1007 = (int)(t1005);
    t1008 = (int)(t1007 - t1006);
    t1009 = (int)(t1008 >> (int)4);
    if ((unsigned int)(t1000) > (unsigned int)(t1009)) {
        t1010 = (int)((int)g_01667bac);
        (*(int*)&v_l16[0]) = (int)(t1010);
        (*(int*)&v_l16[1]) = (int)(t1010);
        t1011 = (int)((int)&v_l16);
        t1012 = (int)(t1000 - t1009);
        t1013 = (int)(t1004);
        (*(int*)&v_l16[2]) = (int)((int)g_01667bae);
        ((C_0084afc0*)(t1013))->FUN_0084afc0((unsigned int)(t1005), (unsigned int)(t1012), (unsigned int)(t1011));
        return;
    }
    t1019 = (int)(t1000 << (int)4);
    t1021 = (int)(t1019 + t1006);
    t1022 = (int)(t1021);
    t1023 = (int)FUN_0084ab40((unsigned int)(t1005), (unsigned int)(t1005), (unsigned int)(t1022));
    t1026 = (int)(*(int*)((char*)(t1004) + 4));
    t1027 = (int)(t1004);
    ((C_0084aad0*)(t1027))->FUN_0084aad0((unsigned int)(t1023), (unsigned int)(t1026));
    t1031 = (int)(t1005 - t1022);
    t1032 = (int)(t1031 >> (int)4);
    t1033 = (int)(-t1032);
    t1034 = (int)(t1033 << (int)4);
    *(int*)((char*)(t1004) + 4) += t1034;
    return;
}
