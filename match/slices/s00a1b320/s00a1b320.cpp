// 0x00a1b320: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPAudio/AudioSound.cpp, match/slices/s00a1a590/s00a1a590.cpp.

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
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};


// @ 0x00a1b320
extern "C" bool __fastcall FUN_00a1b320(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1005;
    int t1007;
    int t1008;
    bool t1011;
    int t1018;
    int t1019;
    int t1022;
    bool t1028;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 3200));
    t1005 = (int)(*(int*)((char*)(t1002) + 3196));
    if (t1005 != t1003) {
        t1007 = (int)((int)(a4));
        do {
            t1008 = (int)(*(int*)((char*)(t1005)));
            if (t1008 == t1007) goto La1b355;
            t1005 = (int)(t1005 + (int)4);
        } while (t1005 != t1003);
    }
    t1011 = false;
    return (bool)(t1011);
    La1b355:;
    ((il2c_vc0*)(t1007))->s53((int)((int)0));
    t1018 = (int)(*(int*)((char*)(t1002) + 3200));
    t1019 = (int)(*(int*)((char*)(t1018) - 4));
    *(int*)((char*)(t1005)) = (int)(t1019);
    *(int*)((char*)(t1002) + 3200) += (int)(-4);
    t1022 = (int)(t1008);
    ((il2c_vc1*)(t1022))->s1();
    t1028 = true;
    return (bool)(t1028);
}
