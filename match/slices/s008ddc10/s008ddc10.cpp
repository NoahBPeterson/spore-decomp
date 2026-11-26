// 0x008ddc10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/DatabaseUtil.cpp, match/slices/s008dd0d0/s008dd0d0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3();
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
    virtual int s25(int, int);
};

struct C_005c3d90 { int FUN_005c3d90(unsigned int); };

// @ 0x008ddc10
extern "C" bool __cdecl FUN_008ddc10(int a4, int a8, int a12)
{
    int t1001;
    int t1004;
    int t1007;
    int t1009;
    int t1011;
    int v_l520[130];
    int t1012;
    int t1015;
    int t1016;
    bool t1020;
    bool t1022;
    t1001 = (int)((int)(a12));
    if (t1001 != (int)0) {
        t1004 = (int)(t1001);
        t1007 = (int)((il2c_vc0*)(t1004))->s3();
        if (t1007 == (int)879920274) {
            t1009 = (int)((int)(a4));
            t1011 = (int)((int)&v_l520);
            t1012 = (int)(t1001);
            t1007 = (int)((il2c_vc1*)(t1012))->s25((int)(t1009), (int)(t1011));
            if ((unsigned char)(t1007) != (unsigned char)0) {
                t1015 = (int)((int)&v_l520);
                t1016 = (int)((int)(a8));
                ((C_005c3d90*)(t1016))->FUN_005c3d90((unsigned int)(t1015));
                t1020 = true;
                return (bool)(t1020);
            }
        }
    }
    t1022 = false;
    return (bool)(t1022);
}
