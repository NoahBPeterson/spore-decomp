// 0x00f57ba0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPAppCloudDescription.cpp, match/slices/s00f57590/s00f57590.cpp.

#include <string.h>
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
    virtual int s35(int);
};

struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
struct C_00838020 { int FUN_00838020(unsigned int, unsigned int, unsigned int); };
struct C_00a6f090 { int FUN_00a6f090(unsigned int, unsigned int, unsigned int); };
struct C_00f53420 { void FUN_00f53420(); };
struct C_00f53590 { int FUN_00f53590(); };
struct C_00f57590 { void FUN_00f57590(unsigned int); };

// @ 0x00f57ba0
extern "C" void __fastcall FUN_00f57ba0(char* self, int edx_unused, int a4)
{
    int t1003;
    int v_l620;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1016;
    int t1017;
    int t1018;
    int t1022;
    int v_l616[154];
    int t1023;
    int t1026;
    int t1027;
    int t1031;
    int t1035;
    int t1036;
    int t1039;
    int t1040;
    int t1044;
    t1003 = (int)((int)&v_l620);
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a4));
    t1009 = (int)((C_00838020*)(t1006))->FUN_00838020((unsigned int)(t1003), (unsigned int)((int)1), (unsigned int)((int)3));
    t1010 = (int)(t1009);
    t1011 = (int)(*(int*)((char*)(t1010)));
    t1012 = (int)(t1011);
    t1016 = (int)strlen((const char*)(t1012));
    t1017 = (int)(t1016 + t1011);
    t1018 = (int)(t1005 + (int)688);
    ((C_00454cb0*)(t1018))->FUN_00454cb0((unsigned int)(t1011), (unsigned int)(t1017));
    t1022 = (int)((int)&v_l616);
    t1023 = (int)(t1005 + (int)64);
    t1026 = (int)((C_00f53590*)(t1022))->FUN_00f53590();
    t1027 = (int)(t1023);
    ((C_00f57590*)(t1027))->FUN_00f57590((unsigned int)(t1026));
    t1031 = (int)((int)&v_l616);
    ((C_00f53420*)(t1031))->FUN_00f53420();
    t1035 = (int)(v_l620);
    *(unsigned char*)((char*)(t1005) + 704) = (unsigned char)((int)0);
    *(unsigned char*)((char*)(t1005) + 705) = (unsigned char)((int)0);
    if (t1035 > (int)1) {
        t1036 = (int)(*(int*)((char*)(t1005) + 48));
        t1039 = (int)((C_00a6f090*)(t1036))->FUN_00a6f090((unsigned int)(t1010), (unsigned int)(t1035), (unsigned int)((int)43));
        if (t1039 != (int)0) {
            t1040 = (int)(t1023);
            ((C_00f57590*)(t1040))->FUN_00f57590((unsigned int)(t1039));
        }
    }
    t1044 = (int)(*(int*)((char*)(t1005) + 4));
    ((il2c_vc0*)(t1044))->s35((int)(t1005));
    return;
}
