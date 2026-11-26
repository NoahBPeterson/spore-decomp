// 0x0112a430: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01129d50/s01129d50.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1(int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3();
};


// @ 0x0112a430
extern "C" int __fastcall FUN_0112a430(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1010;
    int t1011;
    int t1013;
    int t1016;
    int t1017;
    int t1021;
    int t1022;
    int t1023;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1033;
    int t1034;
    int t1035;
    int t1036;
    int t1037;
    int t1038;
    int t1039;
    int t1040;
    int t1044;
    int t1045;
    int t1046;
    int t1047;
    int t1048;
    int t1053;
    int t1058;
    t1003 = (int)((int)(a8));
    if ((unsigned char)*(unsigned char*)((char*)(t1003) + 24) == (unsigned char)1) {
        t1004 = (int)(*(int*)((char*)(t1003) + 16));
        t1005 = (int)(t1004 + t1003);
    } else {
        t1005 = (int)((int)0);
    }
    t1006 = (int)((int)(a12));
    if ((unsigned char)*(unsigned char*)((char*)(t1006) + 24) == (unsigned char)1) {
        t1007 = (int)(*(int*)((char*)(t1006) + 16));
        t1008 = (int)(t1007 + t1006);
    } else {
        t1008 = (int)((int)0);
    }
    t1010 = (int)(*(int*)((char*)((int)(self)) + 16));
    if (t1010 != (int)0) {
        t1011 = (int)(t1010 + (int)8);
        t1013 = (int)((int)&a8);
        t1016 = (int)((il2c_vc0*)(t1011))->s1((int)(t1013), (int)(t1003), (int)(t1006));
        if ((unsigned char)*(unsigned char*)((char*)(t1016)) == (unsigned char)0) {
            t1017 = (int)((int)(a4));
            *(unsigned char*)((char*)(t1017)) = (unsigned char)((int)0);
            return (int)(t1017);
        }
    }
    if (t1005 != (int)0) {
        if (t1008 != (int)0) {
            t1021 = (int)(*(int*)((char*)(t1008) + 128));
            t1022 = (int)(*(int*)((char*)(t1005) + 128));
            t1023 = (int)(*(int*)((char*)(t1005) + 116));
            t1025 = (int)(t1021 + (int)*(int*)((char*)(t1008) + 116));
            t1026 = (int)(t1022 + t1023);
            if (t1026 > t1025) {
                t1027 = (int)(t1008);
                *(int*)&(a12) = (int)(t1005);
            } else {
                t1027 = (int)(t1005);
                *(int*)&(a12) = (int)(t1008);
            }
            t1028 = (int)(*(int*)((char*)(t1027) + 128));
            t1029 = (int)(t1028 + (int)*(int*)((char*)(t1027) + 116));
            t1030 = (int)((int)0);
            if (t1029 > t1030) {
                *(int*)&(a8) = (int)(t1030);
                goto L112a4d0;
                L112a4d0:;
                t1033 = (int)(*(int*)((char*)(t1027) + 116));
                if (t1030 < t1033) {
                    t1034 = (int)(*(int*)((char*)(t1027) + 112));
                    t1035 = (int)((int)(a8));
                    t1036 = (int)(*(int*)((char*)(t1035) + t1034));
                } else {
                    t1037 = (int)(*(int*)((char*)(t1027) + 124));
                    t1038 = (int)(t1030);
                    t1039 = (int)(t1038 - t1033);
                    t1036 = (int)(*(int*)((char*)(t1037) + (t1039)*4));
                }
                if (t1036 != (int)0) {
                    t1040 = (int)(*(int*)((char*)(t1036) + 12));
                    t1044 = (int)((il2c_vc1*)(t1040))->s3();
                    if (t1044 != (int)11) {
                        t1045 = (int)((int)(a12));
                        if ((int)*(int*)((char*)(t1036) + 16) == t1045) goto L112a52a;
                        if ((int)*(int*)((char*)(t1036) + 20) == t1045) goto L112a52a;
                    }
                }
                t1046 = (int)((int)(a8));
                t1030 = (int)(t1030 + (int)1);
                t1047 = (int)(t1046 + (int)28);
                *(int*)&(a8) = (int)(t1047);
                if (t1030 < t1029) goto L112a4d0;
            }
            t1048 = (int)((int)(a4));
            *(unsigned char*)((char*)(t1048)) = (unsigned char)((int)1);
            return (int)(t1048);
            L112a52a:;
            t1053 = (int)((int)(a4));
            *(unsigned char*)((char*)(t1053)) = (unsigned char)((int)0);
            return (int)(t1053);
        }
    }
    t1058 = (int)((int)(a4));
    *(unsigned char*)((char*)(t1058)) = (unsigned char)((int)1);
    return (int)(t1058);
}
