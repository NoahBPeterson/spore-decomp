// 0x00c6ab90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPNest.cpp, match/slices/s00c6a550/s00c6a550.cpp.

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
    virtual int s21(int, int);
};

struct C_00b3d350 { int FUN_00b3d350(); };
extern "C" int __cdecl FUN_00b3d430(...);
struct C_00bbc3f0 { void FUN_00bbc3f0(); };

// @ 0x00c6ab90
extern "C" void __fastcall FUN_00c6ab90(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1016;
    int t1020;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 300) == (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 208));
        if (t1003 != (int)0) {
            if ((int)*(int*)((char*)(t1003) + 144) != (int)0) {
                t1006 = (int)((C_00b3d350*)((int)(self)))->FUN_00b3d350();
                t1007 = (int)(*(int*)((char*)(t1006) + 36));
                if (t1007 != (int)0) {
                    t1008 = (int)(*(int*)((char*)(t1002) + 208));
                    t1009 = (int)(*(int*)((char*)(t1008) + 144));
                    t1012 = (int)(t1008 + (int)8);
                    t1016 = (int)((il2c_vc0*)(t1007))->s21((int)(t1012), (int)(t1009));
                    *(int*)((char*)(t1002) + 300) = (int)(t1016);
                }
                t1003 = (int)FUN_00b3d430();
                if (t1003 != (int)0) {
                    t1020 = (int)(t1003);
                    ((C_00bbc3f0*)(t1020))->FUN_00bbc3f0();
                    return;
                }
            }
        }
    }
    return;
}
