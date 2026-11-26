// 0x009a84f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/parts_caps.cpp, match/slices/s009a7810/s009a7810.cpp.

// @ 0x009a84f0
extern "C" int __cdecl FUN_009a84f0(int a4, int a8, int a12, int a16)
{
    int t1000;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1011;
    int t6;
    int t1012;
    int t1013;
    int t1014;
    int t7;
    int t8;
    int t1015;
    int t11;
    int t1016;
    int t1017;
    int t12;
    int t13;
    int t1018;
    t1000 = (int)((int)(a8));
    t1002 = (int)((int)0);
    if ((unsigned int)(t1000) > (unsigned int)0) {
        t1004 = (int)((int)(a4));
        t1005 = (int)((int)(a12));
        t1006 = (int)(t1004);
        do {
            if ((int)*(int*)((char*)(t1006)) == t1005) goto L9a8525;
            t1002 = (int)(t1002 + (int)1);
            t1006 = (int)(t1006 + (int)28);
        } while ((unsigned int)(t1002) < (unsigned int)(t1000));
    }
    t1007 = (int)((int)(a16));
    if (t1007 != (int)0) {
        *(int*)((char*)(t1007)) = (int)((int)0);
    }
    t1009 = (int)((int)0);
    return (int)(t1009);
    L9a8525:;
    t1011 = (int)((int)(a16));
    if (t1011 != (int)0) {
        t6 = (int)(t1002 << (int)3);
        t1012 = (int)(t6);
        t1013 = (int)((int)0);
        t1014 = (int)(t1012 - t1002);
        t7 = (int)(t1014 << (int)2);
        t8 = (int)(t1004 + t7);
        t1015 = (int)(t8 + (int)4);
        L9a8540:;
        if ((int)*(int*)((char*)(t1015)) != (int)0) {
            t1013 = (int)(t1013 + (int)1);
            t1015 = (int)(t1015 + (int)4);
            if ((unsigned int)(t1013) < (unsigned int)6) goto L9a8540;
        }
        *(int*)((char*)(t1011)) = (int)(t1013);
    }
    t11 = (int)(t1002 << (int)3);
    t1016 = (int)(t11);
    t1017 = (int)(t1016 - t1002);
    t12 = (int)(t1017 << (int)2);
    t13 = (int)(t1004 + t12);
    t1018 = (int)(t13 + (int)4);
    return (int)(t1018);
}
