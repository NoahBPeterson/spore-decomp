// 0x0112ad10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01129d50/s01129d50.cpp.

struct il2c_vc0 {
    virtual int s0(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int, int);
};

extern "C" unsigned char g_016e4178[];
extern "C" void __cdecl FUN_0107f4a0(...);
extern "C" void __cdecl FUN_0107f530(...);

// @ 0x0112ad10
extern "C" int __fastcall FUN_0112ad10(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t2;
    int t1010;
    int t1011;
    int t1012;
    int t1015;
    int t1017;
    int t1016;
    int t1018;
    int t1019;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t9;
    int t1029;
    int t1030;
    int t1031;
    int t1034;
    int t1035;
    int t1037;
    int t1036;
    int t1038;
    int t1039;
    int t1040;
    int t1044;
    int t1047;
    int t1050;
    int t1054;
    t1001 = (int)((int)(a8));
    t1005 = (int)((int)(self));
    if (t1001 == (int)0) {
        t1006 = (int)(*(int*)((char*)(t1005) + 12));
        t1007 = (int)(*(int*)((char*)(t1006) + 20));
        t1008 = (int)((int)(*(int*)g_016e4178));
        t2 = (int)(t1007 << (int)1);
        t1010 = (int)(t1007 + t2);
        t1011 = (int)(t1010 << (int)4);
        t1012 = (int)((il2c_vc0*)(t1008))->s0((int)(t1011), (int)((int)5));
        t1015 = (int)(*(int*)((char*)(t1005) + 8));
        t1017 = (int)(t1015 + (int)8);
        t1016 = (int)(*(int*)((char*)(t1017) + 8));
        t1001 = (int)(t1012);
        t1018 = (int)(*(int*)((char*)(t1017) + 4));
        t1019 = (int)(t1016 & (int)1073741823);
        if (t1018 == t1019) {
            FUN_0107f530((unsigned int)(t1017), (unsigned int)((int)4));
        }
        t1023 = (int)(*(int*)((char*)(t1017) + 4));
        t1024 = (int)(*(int*)((char*)(t1017)));
        *(int*)((char*)(t1024) + (t1023)*4) = (int)(t1001);
        *(int*)((char*)(t1017) + 4) += (int)1;
    }
    t1025 = (int)(*(int*)((char*)(t1005) + 12));
    t1026 = (int)(*(int*)((char*)(t1025) + 20));
    t1027 = (int)((int)(a4));
    t9 = (int)(t1026 << (int)1);
    t1029 = (int)(t1026 + t9);
    t1030 = (int)(t1029 << (int)4);
    t1031 = (int)((il2c_vc1*)(t1027))->s3((int)(t1001), (int)(t1030));
    if (t1031 == t1030) {
        t1034 = (int)(*(int*)((char*)(t1005) + 12));
        *(int*)((char*)(t1005) + 16) = (int)(t1001);
        t1035 = (int)(*(int*)((char*)(t1034) + 20));
        t1037 = (int)(t1005 + (int)20);
        t1036 = (int)(*(int*)((char*)(t1037) + 4));
        if (t1035 > t1036) {
            t1038 = (int)(*(int*)((char*)(t1037) + 8));
            t1039 = (int)(t1038 & (int)1073741823);
            if (t1039 < t1035) {
                t1040 = (int)(t1039 + t1039);
                if (t1035 >= t1040) {
                    t1040 = (int)(t1035);
                }
                FUN_0107f4a0((unsigned int)(t1037), (unsigned int)(t1040), (unsigned int)((int)4));
            }
            t1044 = (int)(t1036);
            if (t1036 < t1035) {
                goto L112adc0;
                L112adc0:;
                t1047 = (int)(*(int*)((char*)(t1037)));
                *(int*)((char*)(t1047) + (t1044)*4) = (int)((int)0);
                t1044 = (int)(t1044 + (int)1);
                if (t1044 < t1035) goto L112adc0;
            }
        }
        *(int*)((char*)(t1037) + 4) = (int)(t1035);
        t1050 = (int)((int)0);
        return (int)(t1050);
    }
    t1054 = (int)((int)1);
    return (int)(t1054);
}
