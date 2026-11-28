// 0x01066780: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUISpace.cpp, match/slices/s01065c30/s01065c30.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
};

struct C_00834a00 { int FUN_00834a00(unsigned int); };
struct C_00834c60 { int FUN_00834c60(unsigned int); };

// @ 0x01066780
extern "C" bool __fastcall FUN_01066780(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    int t1011;
    int t1012;
    bool t1016;
    int t1018;
    int t1019;
    bool t1023;
    int t1025;
    bool t1029;
    int t1031;
    int t1033;
    int t1037;
    int t1038;
    int t1039;
    bool t1042;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 600) != (int)0) {
        t1003 = (int)((int)(a8));
        t1004 = (int)(*(int*)((char*)(t1003) + 8));
        if (t1004 == (int)27) {
            if ((int)*(int*)((char*)(t1003) + 12) != (int)1) goto L1066875;
            t1005 = (int)(*(int*)((char*)(t1003) + 24));
            t1007 = (int)(t1005);
            t1003 = (int)((il2c_vc0*)(t1007))->s7();
            if (t1003 == (int)133018088) {
                t1011 = (int)(*(int*)((char*)(t1002) + 1688));
                t1012 = (int)(*(int*)((char*)(t1011)));
                if (t1012 == (int)0) goto L1066875;
                ((C_00834a00*)(t1012))->FUN_00834a00((unsigned int)((int)0));
                t1016 = true;
                return (bool)(t1016);
            }
            if (t1003 == (int)133018089) {
                t1018 = (int)(*(int*)((char*)(t1002) + 1688));
                t1019 = (int)(*(int*)((char*)(t1018) + 4));
                if (t1019 == (int)0) goto L1066875;
                ((C_00834a00*)(t1019))->FUN_00834a00((unsigned int)((int)0));
                t1023 = true;
                return (bool)(t1023);
            }
            if (t1003 != (int)133018090) goto L1066875;
            t1003 = (int)(*(int*)((char*)(t1002) + 1688));
            t1025 = (int)(*(int*)((char*)(t1003) + 8));
            if (t1025 == (int)0) goto L1066875;
            ((C_00834a00*)(t1025))->FUN_00834a00((unsigned int)((int)0));
            t1029 = true;
            return (bool)(t1029);
        }
        if (t1004 == (int)28) {
            if ((int)*(int*)((char*)(t1003) + 12) == (int)1) {
                t1031 = (int)(*(int*)((char*)(t1003) + 24));
                t1033 = (int)(t1031);
                t1003 = (int)((il2c_vc1*)(t1033))->s7();
                if (t1003 == (int)133018088) {
                    t1037 = (int)(*(int*)((char*)(t1002) + 1688));
                    t1038 = (int)(*(int*)((char*)(t1037)));
                    goto L106686a;
                }
                if (t1003 == (int)133018089) {
                    t1039 = (int)(*(int*)((char*)(t1002) + 1688));
                    t1038 = (int)(*(int*)((char*)(t1039) + 4));
                    goto L106686a;
                }
                if (t1003 != (int)133018090) goto L1066875;
                t1003 = (int)(*(int*)((char*)(t1002) + 1688));
                t1038 = (int)(*(int*)((char*)(t1003) + 8));
                L106686a:;
                if (t1038 != (int)0) {
                    t1003 = (int)((C_00834c60*)(t1038))->FUN_00834c60((unsigned int)((int)0));
                }
            }
        }
    }
    L1066875:;
    t1042 = true;
    return (bool)(t1042);
}
