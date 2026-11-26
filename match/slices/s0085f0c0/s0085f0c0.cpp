// 0x0085f0c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013cc4a0[];

// @ 0x0085f0c0
extern "C" void __cdecl FUN_0085f0c0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1010;
    unsigned char t1011;
    int t1012;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1027;
    int t1028;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000)));
    t1002 = (int)(*(int*)((char*)(t1001) + 20));
    if (t1002 > (int)0) {
        if (t1002 <= (int)*(int*)((char*)(t1001) + 116)) {
            t1004 = (int)(*(int*)((char*)(t1001) + 112));
            t1005 = (int)(*(int*)((char*)(t1004) + (t1002)*4));
            goto L85f0fa;
        }
    }
    t1006 = (int)(*(int*)((char*)(t1001) + 120));
    if (t1006 == (int)0) goto L85f0fe;
    t1007 = (int)(*(int*)((char*)(t1001) + 124));
    if (t1002 < t1007) goto L85f0fe;
    if (t1002 > (int)*(int*)((char*)(t1001) + 128)) goto L85f0fe;
    t1009 = (int)(t1002);
    t1010 = (int)(t1009 - t1007);
    t1005 = (int)(*(int*)((char*)(t1006) + (t1010)*4));
    L85f0fa:;
    if (t1005 != (int)0) goto L85f106;
    L85f0fe:;
    *(int*)((char*)(t1001) + 24) = (int)(t1002);
    t1002 = (int)(*(int*)((char*)(t1001) + 112));
    t1005 = (int)(*(int*)((char*)(t1002)));
    L85f106:;
    t1011 = (unsigned char)(*(unsigned char*)((char*)(t1005)));
    t1012 = (int)(t1005);
    if (t1011 != (unsigned char)0) {
        do {
            t1012 = (int)(t1012 + (int)1);
            if (t1011 == (unsigned char)37) goto L85f14d;
            t1011 = (unsigned char)(*(unsigned char*)((char*)(t1012)));
        } while (t1011 != (unsigned char)0);
    }
    L85f11c:;
    t1014 = (int)(*(int*)((char*)(t1001) + 52));
    t1015 = (int)(*(int*)((char*)(t1001) + 48));
    t1016 = (int)(*(int*)((char*)(t1001) + 44));
    t1017 = (int)(*(int*)((char*)(t1001) + 40));
    t1018 = (int)(*(int*)((char*)(t1001) + 36));
    t1019 = (int)(*(int*)((char*)(t1001) + 32));
    t1020 = (int)(*(int*)((char*)(t1001) + 28));
    t1021 = (int)(*(int*)((char*)(t1001) + 24));
    t1022 = (int)((int)(a8));
    ((int (__cdecl*)(...))(*(int*)g_013cc4a0))(t1022, t1005, t1021, t1020, t1019, t1018, t1017, t1016, t1015, t1014);
    return;
    L85f14d:;
    if ((unsigned char)*(unsigned char*)((char*)(t1012)) != (unsigned char)115) goto L85f11c;
    t1027 = (int)((int)(a8));
    t1028 = (int)(t1001 + (int)24);
    ((int (__cdecl*)(...))(*(int*)g_013cc4a0))(t1027, t1005, t1028);
    return;
}
