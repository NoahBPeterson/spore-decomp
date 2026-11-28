// 0x009917f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/TreeView.cpp, match/slices/s009913d0/s009913d0.cpp.

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
    virtual void s31(int, int);
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

struct C_0098fbe0 { void FUN_0098fbe0(); };
struct C_00990ff0 { void FUN_00990ff0(unsigned int); };

// @ 0x009917f0
extern "C" void __fastcall FUN_009917f0(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1003;
    int t1005;
    int t1006;
    int t1010;
    int t1014;
    int t1020;
    int t1021;
    int t1027;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    *(float*)((char*)(t1003) + 88) = (float)(*(float*)((char*)(t1000)));
    t1005 = (int)(t1003 + (int)(-524));
    *(float*)((char*)(t1003) + 92) = (float)(*(float*)((char*)(t1000) + 4));
    t1006 = (int)(t1005);
    *(float*)((char*)(t1003) + 96) = (float)(*(float*)((char*)(t1000) + 8));
    *(float*)((char*)(t1003) + 100) = (float)(*(float*)((char*)(t1000) + 12));
    ((C_00990ff0*)(t1006))->FUN_00990ff0((unsigned int)((int)1));
    t1010 = (int)(t1005);
    ((C_00990ff0*)(t1010))->FUN_00990ff0((unsigned int)((int)0));
    t1014 = (int)(t1005);
    ((C_0098fbe0*)(t1014))->FUN_0098fbe0();
    t1020 = (int)(t1003 + (int)(-520));
    t1021 = (int)(t1020);
    ((il2c_vc0*)(t1021))->s31((int)((int)8), (int)((int)1));
    t1027 = (int)(t1020);
    ((il2c_vc1*)(t1027))->s36();
    return;
}
