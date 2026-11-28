// 0x00ae7e10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ae73e0/guicomm.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual int s2(int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual int s2(int, int);
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int, int);
};
struct il2c_vc5 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4(int, int);
};
struct il2c_vc6 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6(int);
};
struct il2c_vc7 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8(int, int);
};
struct il2c_vc8 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual int s9(int, float);
};

extern "C" unsigned char g_013eb1bc[];
struct C_00a02ab0 { void FUN_00a02ab0(unsigned int); };
struct C_00a02b20 { int FUN_00a02b20(unsigned int); };

// @ 0x00ae7e10
extern "C" void __fastcall FUN_00ae7e10(char* self, int edx_unused, int a4, int a8, int a12, int a16)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1014;
    int t1015;
    int t1018;
    int t1021;
    int t1027;
    int t1029;
    int t1034;
    int t1037;
    int t1040;
    int t1046;
    int t1048;
    int t1053;
    int t1055;
    int t1060;
    int t1062;
    int t1067;
    int t1069;
    t1002 = (int)((int)(a12));
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
    if (t1005 != (int)0) {
        if ((unsigned char)(a16) == (unsigned char)0) {
            t1006 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 68));
            if (t1006 != (int)0) {
                t1007 = (int)((C_00a02b20*)(t1005))->FUN_00a02b20((unsigned int)(t1006));
                if ((unsigned char)(t1007) == (unsigned char)0) goto Lae7efa;
            }
        }
        t1010 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
        ((C_00a02ab0*)(t1010))->FUN_00a02ab0((unsigned int)((int)0));
        t1014 = (int)((int)(a4));
        if (t1014 != (int)0) {
            t1015 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            t1018 = (int)((il2c_vc0*)(t1015))->s2((int)(t1014), (int)((int)0));
            t1021 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            *(int*)((char*)(t1004) + (t1002)*4 + 60) = (int)(t1018);
            ((il2c_vc1*)(t1021))->s3((int)(t1018), (int)((int)1));
            t1027 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            t1029 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 60));
            ((il2c_vc2*)(t1027))->s6((int)(t1029));
        }
        t1007 = (int)((int)(a8));
        if (t1007 != (int)0) {
            t1034 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            t1037 = (int)((il2c_vc3*)(t1034))->s2((int)(t1007), (int)((int)0));
            t1040 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            *(int*)((char*)(t1004) + (t1002)*4 + 68) = (int)(t1037);
            ((il2c_vc4*)(t1040))->s3((int)(t1037), (int)((int)0));
            t1046 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            t1048 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 68));
            ((il2c_vc5*)(t1046))->s4((int)(t1048), (int)((int)1));
            t1053 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            t1055 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 68));
            ((il2c_vc6*)(t1053))->s6((int)(t1055));
            t1060 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            t1062 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 68));
            ((il2c_vc7*)(t1060))->s8((int)(t1062), (int)((int)1));
            t1067 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 44));
            t1069 = (int)(*(int*)((char*)(t1004) + (t1002)*4 + 68));
            t1007 = (int)((il2c_vc8*)(t1067))->s9((int)(t1069), (float)((float)(*(float*)g_013eb1bc)));
        }
    }
    Lae7efa:;
    return;
}
