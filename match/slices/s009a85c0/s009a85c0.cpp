// 0x009a85c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/animation_version.cpp, match/slices/s009a7810/s009a7810.cpp.

extern "C" void __cdecl FUN_00801c00(...);
extern "C" unsigned char g_015507a8[];
extern "C" unsigned char g_015507ac[];

// @ 0x009a85c0
// @ 0x009a85c0
extern "C" int __cdecl FUN_009a85c0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1014;
    int t9;
    int t1015;
    int t1016;
    int t1017;
    int t10;
    int t1018;
    int t13;
    int t1019;
    int t1020;
    int t14;
    int t1021;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000)));
    t1002 = (int)(t1001);
    t1003 = (int)(t1002 & (int)1048579);
    switch ((unsigned int)(t1003)) { case 0: goto L9a85df; case 1: goto L9a85d8; default: goto L9a8613; }
    goto L9a85d8;
    goto L9a85df;
    goto L9a8613;
    L9a85d8:;
    t1007 = (int)((int)1953460082);
    goto L9a85e2;
    L9a85df:;
    t1007 = (int)(*(int*)((char*)(t1000) + 4));
    L9a85e2:;
    t1008 = (int)(t1001 & (int)&FUN_00801c00);
    if (t1008 != (int)6144) {
        if (t1008 != (int)7168) goto L9a85fb;
    }
    t1007 = (int)(*(int*)((char*)(t1000) + 8));
    L9a85fb:;
    t1009 = (int)((int)0);
    t1010 = (int)((int)0);
    do {
        if ((int)*(int*)((char*)(t1010) + (int)g_015507a8) == t1007) goto L9a8625;
        t1010 = (int)(t1010 + (int)28);
        t1009 = (int)(t1009 + (int)1);
    } while ((unsigned int)(t1010) < (unsigned int)560);
    L9a8613:;
    t1011 = (int)((int)(a8));
    if (t1011 != (int)0) {
        *(int*)((char*)(t1011)) = (int)((int)0);
    }
    t1012 = (int)((int)0);
    return (int)(t1012);
    L9a8625:;
    t1014 = (int)((int)(a8));
    if (t1014 != (int)0) {
        t9 = (int)(t1009 << (int)3);
        t1015 = (int)(t9);
        t1016 = (int)((int)0);
        t1017 = (int)(t1015 - t1009);
        t10 = (int)(t1017 << (int)2);
        t1018 = (int)(t10 + (int)g_015507ac);
        L9a8640:;
        if ((int)*(int*)((char*)(t1018)) != (int)0) {
            t1016 = (int)(t1016 + (int)1);
            t1018 = (int)(t1018 + (int)4);
            if ((unsigned int)(t1016) < (unsigned int)6) goto L9a8640;
        }
        *(int*)((char*)(t1014)) = (int)(t1016);
    }
    t13 = (int)(t1009 << (int)3);
    t1019 = (int)(t13);
    t1020 = (int)(t1019 - t1009);
    t14 = (int)(t1020 << (int)2);
    t1021 = (int)(t14 + (int)g_015507ac);
    return (int)(t1021);
}
