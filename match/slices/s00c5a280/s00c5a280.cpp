// 0x00c5a280: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPMissionMultiStep.cpp, match/slices/s00c59540/s00c59540.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual int s24();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual int s62();
};

struct C_00c487d0 { int FUN_00c487d0(unsigned int, unsigned int); };

// @ 0x00c5a280
extern "C" void __fastcall FUN_00c5a280(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int v_l60[15];
    int t1003;
    int t1005;
    int t1008;
    int t1011;
    int t6;
    int t1012;
    int t1013;
    int t1021;
    int t1024;
    int t1025;
    int t12;
    int t1026;
    int t1027;
    int t1033;
    int t16;
    int t1034;
    int t1035;
    t1001 = (int)((int)(a4));
    (*(int*)&v_l60[5]) = (int)((int)2120711838);
    (*(int*)&v_l60[6]) = (int)((int)2120711837);
    (*(int*)&v_l60[7]) = (int)((int)2120711836);
    (*(int*)&v_l60[8]) = (int)((int)2120711835);
    (*(int*)&v_l60[9]) = (int)((int)2120711834);
    (*(int*)&v_l60[10]) = (int)((int)1629086503);
    (*(int*)&v_l60[11]) = (int)((int)1629086500);
    (*(int*)&v_l60[12]) = (int)((int)1629086501);
    (*(int*)&v_l60[13]) = (int)((int)1629086498);
    (*(int*)&v_l60[14]) = (int)((int)1629086499);
    (*(int*)&v_l60[0]) = (int)((int)(-1865584423));
    (*(int*)&v_l60[1]) = (int)((int)(-1865584422));
    (*(int*)&v_l60[2]) = (int)((int)(-1865584421));
    (*(int*)&v_l60[3]) = (int)((int)(-1865584420));
    (*(int*)&v_l60[4]) = (int)((int)(-1865584419));
    if ((unsigned int)(t1001) < (unsigned int)5) {
        t1003 = (int)(*(int*)((char*)((int)(self)) + 496));
        t1005 = (int)(*(int*)((char*)(t1003) + (t1001)*4));
        if (t1005 != (int)0) {
            t1008 = (int)(t1005);
            t1003 = (int)((il2c_vc0*)(t1008))->s24();
            if (t1003 != (int)3) {
                if (t1003 != (int)9) goto Lc5a379;
                t1011 = (int)((int)(a8));
                t6 = (int)((int)&v_l60);
                t1012 = (int)(*(int*)((char*)(t6) + (t1001)*4));
                t1013 = (int)(t1005);
                ((C_00c487d0*)(t1013))->FUN_00c487d0((unsigned int)(t1012), (unsigned int)(t1011));
                return;
            }
            t1021 = (int)(t1005);
            t1024 = (int)((il2c_vc1*)(t1021))->s62();
            if ((unsigned char)(t1024) == (unsigned char)0) {
                t1025 = (int)((int)(a8));
                t12 = (int)((int)&v_l60[5]);
                t1026 = (int)(*(int*)((char*)(t12) + (t1001)*4));
                t1027 = (int)(t1005);
                ((C_00c487d0*)(t1027))->FUN_00c487d0((unsigned int)(t1026), (unsigned int)(t1025));
                return;
            }
            t1033 = (int)((int)(a8));
            t16 = (int)((int)&v_l60[10]);
            t1034 = (int)(*(int*)((char*)(t16) + (t1001)*4));
            t1035 = (int)(t1005);
            t1003 = (int)((C_00c487d0*)(t1035))->FUN_00c487d0((unsigned int)(t1034), (unsigned int)(t1033));
        }
        Lc5a379:;
    }
    return;
}
