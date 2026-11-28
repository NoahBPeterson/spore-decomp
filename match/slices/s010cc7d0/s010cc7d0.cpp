// 0x010cc7d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s010cbaa0/s010cbaa0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1(int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};


// @ 0x010cc7d0
extern "C" float __fastcall FUN_010cc7d0(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1004;
    int t1005;
    int t1006;
    int t1008;
    int t1009;
    int t1010;
    int t1012;
    int t1013;
    int t1017;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t9;
    int t1031;
    int t1034;
    int t1038;
    t1000 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1005 = (int)(*(signed char*)((char*)(t1000) + 5));
    t1006 = (int)(*(int*)((char*)(t1005) + t1000));
    t1008 = (int)(t1005 + t1000);
    if (t1006 != (int)0) {
        t1009 = (int)(*(int*)((char*)(t1004) + 20));
        if (t1009 != t1008) {
            t1010 = (int)(*(int*)((char*)(t1004) + 8));
            t1012 = (int)((int)&a4);
            t1013 = (int)((il2c_vc0*)(t1010))->s1((int)(t1012), (int)(t1009), (int)(t1008));
            if ((unsigned char)*(unsigned char*)((char*)(t1013)) != (unsigned char)0) {
                t1017 = (int)(t1006);
                t1018 = (int)((il2c_vc1*)(t1017))->s2();
                t1021 = (int)(*(int*)((char*)(t1004) + 24));
                t1022 = (int)(*(int*)((char*)(t1004) + 32));
                t1023 = (int)(t1004 + (int)32);
                t1024 = (int)(t1021 << (int)5);
                t1025 = (int)(t1024 + t1022);
                t1026 = (int)(*(unsigned char*)((char*)(t1025) + t1018 + 400));
                t1027 = (int)(*(int*)((char*)(t1004) + 16));
                t1028 = (int)(*(int*)((char*)(t1004) + 12));
                t1029 = (int)(*(int*)((char*)(t1004) + 20));
                t1030 = (int)(t1026 + (int)123);
                t9 = (int)(t1030 << (int)2);
                t1031 = (int)(t1030 + t9);
                t1013 = (int)((int (__cdecl*)(int, int, int, int, int))(*(int*)((char*)(t1022) + (t1031)*4)))((int)(t1029), (int)(t1008), (int)(t1023), (int)(t1028), (int)(t1027));
            }
            t1034 = (int)(*(int*)((char*)(t1004) + 12));
            return (float)(*(float*)((char*)(t1034) + 4));
        }
    }
    t1038 = (int)(*(int*)((char*)(t1004) + 12));
    return (float)(*(float*)((char*)(t1038) + 4));
}
