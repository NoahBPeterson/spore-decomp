// 0x00ba6b40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ba6750/s00ba6750.cpp.

struct C_005c65e0 { int FUN_005c65e0(); };
extern "C" double __cdecl FUN_010434c0(...);

// @ 0x00ba6b40
extern "C" int __cdecl FUN_00ba6b40(int a4, int a8, int a12, float a16)
{
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1015;
    double t5;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1026;
    t1003 = (int)((int)(a8));
    t1005 = (int)((int)(a4));
    t1006 = (int)(*(int*)((char*)(t1005) + 4));
    t1007 = (int)(t1006 - (int)*(int*)((char*)(t1005)));
    t1008 = (int)(t1003);
    t1009 = (int)(t1007 >> (int)2);
    if (t1003 < t1009) {
        do {
            t1010 = (int)(*(int*)((char*)(t1005)));
            t1011 = (int)(*(int*)((char*)(t1010) + (t1003)*4));
            t1012 = (int)((C_005c65e0*)(t1011))->FUN_005c65e0();
            t1015 = (int)((int)(a12));
            t5 = (double)FUN_010434c0((unsigned int)(t1015), (unsigned int)(t1012));
            if ((float)(a16) >= (float)(t5)) {
                if (t1008 != t1003) {
                    t1019 = (int)(*(int*)((char*)(t1005)));
                    t1020 = (int)(*(int*)((char*)(t1019) + (t1003)*4));
                    t1021 = (int)(*(int*)((char*)(t1019) + (t1008)*4));
                    *(int*)((char*)(t1019) + (t1008)*4) = (int)(t1020);
                    t1022 = (int)(*(int*)((char*)(t1005)));
                    *(int*)((char*)(t1022) + (t1003)*4) = (int)(t1021);
                }
                t1008 = (int)(t1008 + (int)1);
            }
            t1003 = (int)(t1003 + (int)1);
        } while (t1003 < t1009);
    }
    t1026 = (int)(t1008);
    return (int)(t1026);
}
