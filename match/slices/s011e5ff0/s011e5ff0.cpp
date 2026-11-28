// 0x011e5ff0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011e5a10/s011e5a10.cpp.

extern "C" int __cdecl FUN_011e58f0(...);
extern "C" int __cdecl FUN_011e8bd0(...);
extern "C" int __cdecl FUN_011e8c60(...);
extern "C" void __cdecl FUN_011ea8f0(...);
extern "C" void __cdecl FUN_011eba20(...);

// @ 0x011e5ff0
extern "C" int __cdecl FUN_011e5ff0(int a4, int a8)
{
    int t1002;
    int t1004;
    int t1007;
    int t1008;
    int v_l16[4];
    int t1012;
    int t1013;
    int t1014;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1029;
    int t1032;
    unsigned char t1034;
    unsigned char t1035;
    int t1036;
    int t1039;
    int t1040;
    int t1043;
    int t1046;
    int t1049;
    int t1052;
    int t1053;
    t1002 = (int)((int)(a4));
    t1004 = (int)FUN_011e8c60((unsigned int)(t1002), (unsigned int)((int)58));
    t1007 = (int)(t1004);
    if (t1007 != (int)0) {
        t1008 = (int)((int)&v_l16);
        FUN_011ea8f0((unsigned int)(t1008), (unsigned int)((int)16));
        t1012 = (int)(t1007 - t1002);
        t1013 = (int)(t1012 + (int)1);
        t1014 = (int)((int)&v_l16);
        FUN_011eba20((unsigned int)(t1014), (unsigned int)(t1002), (unsigned int)(t1013));
        t1018 = (int)FUN_011e58f0();
        t1021 = (int)(*(int*)((char*)(t1018)));
        if (t1021 != (int)0) {
            L11e6033:;
            t1022 = (int)(*(int*)((char*)(t1021) + 288));
            if (t1022 != (int)0) {
                t1023 = (int)((int)&v_l16);
                t1024 = (int)(t1022 + (int)4);
                t1025 = (int)FUN_011e8bd0((unsigned int)(t1024), (unsigned int)(t1023));
                if (t1025 == (int)0) goto L11e6060;
                t1021 = (int)(*(int*)((char*)(t1021)));
                if (t1021 != (int)0) goto L11e6033;
            }
        }
        t1029 = (int)((int)0);
        return (int)(t1029);
        L11e6060:;
        t1032 = (int)(t1021);
        return (int)(t1032);
    }
    t1034 = (unsigned char)(*(unsigned char*)((char*)(t1002)));
    if (t1034 != (unsigned char)47) {
        if (t1034 != (unsigned char)92) {
            t1035 = (unsigned char)((unsigned char)(a8));
            if (t1035 != (unsigned char)0) {
                t1036 = (int)FUN_011e58f0();
                t1039 = (int)(*(int*)((char*)(t1036) + 32));
                t1040 = (int)(*(int*)((char*)(t1039) + 4));
                return (int)(t1040);
            }
            t1043 = (int)FUN_011e58f0();
            t1046 = (int)(*(int*)((char*)(t1043) + 16));
            return (int)(t1046);
        }
    }
    t1049 = (int)FUN_011e58f0();
    t1052 = (int)(*(int*)((char*)(t1049) + 32));
    t1053 = (int)(*(int*)((char*)(t1052) + 4));
    return (int)(t1053);
}
