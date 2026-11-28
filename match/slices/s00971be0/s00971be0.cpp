// 0x00971be0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Grid.cpp, match/slices/s00970f30/s00970f30.cpp.

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
    virtual void s49(int);
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
    virtual int s36();
};


// @ 0x00971be0
// @ 0x00971be0
extern "C" void __fastcall FUN_00971be0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1007;
    int t1008;
    int t4;
    int t6;
    int t1011;
    int v_l16[4];
    int t1012;
    int t1016;
    unsigned char t1019;
    int t1021;
    int t1022;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1002 != (int)*(int*)((char*)(t1004) + 76)) {
        t1005 = (int)(*(int*)((char*)(t1004) + 92));
        t1007 = (int)((int)0);
        t1008 = (int)((int)65536);
        if (t1005 > t1007) {
            if (t1005 != (int)(-1)) goto L971c09;
        }
        t4 = (int)((int)*(int*)((char*)(t1004) + 4) & t1008);
        if (t4 != (int)0) goto L971c3b;
        L971c09:;
        t6 = (int)((int)*(int*)((char*)(t1004) + 4) & t1008);
        if (t6 == (int)0) {
            t1011 = (int)((int)&v_l16);
            t1012 = (int)(t1004);
            (*(int*)&v_l16[0]) = (int)(t1007);
            (*(int*)&v_l16[1]) = (int)(t1007);
            (*(int*)&v_l16[2]) = (int)(t1007);
            (*(int*)&v_l16[3]) = (int)(t1007);
            ((il2c_vc0*)(t1012))->s49((int)(t1011));
            t1016 = (int)((*(int*)&v_l16[3]));
            t1005 = (int)(t1016 + (int)1);
        }
        if (t1002 >= t1005) {
            t1002 = (int)(t1005 + (int)(-1));
        }
        L971c3b:;
        t1019 = (unsigned char)((int)(t1002) <= (int)(t1007));
        t1021 = (int)((int)(t1019) - (int)1);
        t1022 = (int)(t1021 & t1002);
        *(int*)((char*)(t1004) + 76) = (int)(t1022);
        ((il2c_vc1*)((t1004 + (int)(-520))))->s36();
    }
    return;
}
