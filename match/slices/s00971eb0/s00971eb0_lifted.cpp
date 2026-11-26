// 0x00971eb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Grid.cpp, match/slices/s00971eb0/s00971eb0.cpp.

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
    virtual int s31(int, int);
};


// @ 0x00971eb0
extern "C" bool __fastcall FUN_00971eb0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1003;
    int t1005;
    int t1010;
    bool t1017;
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    t1005 = (int)(t1003 + (int)584);
    memcpy((void*)(t1005), (const void*)(t1001), (unsigned int)((int)48));
    t1010 = (int)(t1003 + (int)(-520));
    *(unsigned char*)((char*)(t1003) + 8) = (unsigned char)((int)1);
    ((il2c_vc0*)(t1010))->s31((int)((int)8), (int)((int)1));
    t1017 = true;
    return (bool)(t1017);
}
