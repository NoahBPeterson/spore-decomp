// 0x0098a270: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/TextEdit.cpp, match/slices/s00989870/s00989870.cpp.

// @ 0x0098a270
extern "C" int __fastcall FUN_0098a270(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 1296));
    t1002 = (int)(t1001 - (int)*(int*)((char*)((int)(self)) + 1292));
    t1003 = (int)((int)(a4));
    t1004 = (int)(t1002 >> (int)2);
    if ((unsigned int)(t1003) >= (unsigned int)(t1004)) {
        t1005 = (int)(*(int*)((char*)((int)(self)) + 1312));
        t1006 = (int)((int)(a8));
        t1007 = (int)((int)(a12));
        *(int*)((char*)(t1006)) = (int)(t1005);
        *(int*)((char*)(t1007)) = (int)((int)0);
        return (int)(t1007);
    }
    t1008 = (int)(*(int*)((char*)((int)(self)) + 1292));
    t1009 = (int)(*(int*)((char*)(t1008) + (t1003)*4));
    t1011 = (int)((int)(a8));
    *(int*)((char*)(t1011)) = (int)(t1009);
    t1012 = (int)(*(int*)((char*)((int)(self)) + 1296));
    t1013 = (int)(t1012 - (int)*(int*)((char*)((int)(self)) + 1292));
    t1014 = (int)(t1013 >> (int)2);
    t1015 = (int)(t1014 - (int)1);
    if ((unsigned int)(t1003) >= (unsigned int)(t1015)) {
        t1017 = (int)(*(int*)((char*)((int)(self)) + 1312));
        t1018 = (int)((int)(a12));
        t1019 = (int)(t1017 - t1009);
        *(int*)((char*)(t1018)) = (int)(t1019);
        return (int)(t1009);
    }
    t1020 = (int)(*(int*)((char*)((int)(self)) + 1292));
    t1021 = (int)(*(int*)((char*)(t1020) + (t1003)*4 + 4));
    t1022 = (int)(t1021 - t1009);
    t1023 = (int)((int)(a12));
    *(int*)((char*)(t1023)) = (int)(t1022);
    return (int)(t1023);
}
