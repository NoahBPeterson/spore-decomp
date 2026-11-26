// 0x011fd990: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011fd3a0/s011fd3a0.cpp.

// @ 0x011fd990
extern "C" int __fastcall FUN_011fd990(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1002;
    int t1004;
    int t1007;
    int t1009;
    int t1010;
    int t1011;
    int t1013;
    int v_l4;
    int v_l8;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1025;
    t1001 = (int)(*(int*)((char*)((int)(self))));
    t1002 = (int)(*(int*)((char*)(t1001) + 8));
    t1004 = (int)((int)(a8));
    if (t1002 == (int)*(int*)((char*)(t1004) + 8)) {
        *(int*)((char*)((int)(self)) + 4) = (int)((int)0);
        t1007 = (int)((int)1);
        return (int)(t1007);
    }
    t1009 = (int)((int)1);
    *(int*)((char*)((int)(self)) + 4) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1001) + 4));
    t1011 = (int)((int)0);
    t1013 = (int)(*(int*)((char*)(t1004) + 4));
    v_l4 = (int)(t1010);
    v_l8 = (int)(t1009);
    if ((unsigned int)(t1010) > (unsigned int)0) {
        t1015 = (int)((int)(a4));
        goto L11fd9e0;
        L11fd9db:;
        t1004 = (int)((int)(a8));
        L11fd9e0:;
        t1016 = (int)((int)0);
        if ((unsigned int)(t1013) > (unsigned int)0) {
            t1017 = (int)(*(int*)((char*)((int)(self))));
            t1018 = (int)(*(int*)((char*)(t1017)));
            t1019 = (int)(*(int*)((char*)(t1018) + (t1011)*4));
            t1020 = (int)(*(int*)((char*)(t1004)));
            L11fd9f0:;
            if ((int)*(int*)((char*)(t1020)) != t1019) {
                t1016 = (int)(t1016 + (int)1);
                t1020 = (int)(t1020 + (int)4);
                if ((unsigned int)(t1016) < (unsigned int)(t1013)) goto L11fd9f0;
                goto L11fda05;
            }
            t1021 = (int)(*(int*)((char*)((int)(self)) + (t1015)*4 + 8));
            *(int*)((char*)(t1021) + (t1011)*4) = (int)(t1016);
        }
        L11fda05:;
        if (t1016 == t1013) {
            t1022 = (int)(*(int*)((char*)((int)(self)) + (t1015)*4 + 8));
            *(int*)((char*)(t1022) + (t1011)*4) = (int)((int)(-1));
            v_l8 = (int)((int)0);
        }
        t1023 = (int)(v_l4);
        t1011 = (int)(t1011 + (int)1);
        if ((unsigned int)(t1011) < (unsigned int)(t1023)) goto L11fd9db;
    }
    t1025 = (int)(v_l8);
    return (int)(t1025);
}
