// 0x00a6d730: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a6d020/s00a6d020.cpp, src/game/Swarm/EffectsManager.cpp.

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
    virtual int s15(int, int);
};

struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_008409b0(...);

// @ 0x00a6d730
extern "C" bool __fastcall FUN_00a6d730(char* self, int edx_unused, int a4, int a8)
{
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1017;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1028;
    bool t1034;
    bool t1039;
    t1005 = (int)((int)(self));
    t1006 = (int)((int)(a8));
    t1007 = (int)(t1006);
    t1010 = (int)strlen((const char*)(t1007));
    t1011 = (int)(t1010 + t1006);
    t1012 = (int)(t1005 + (int)584);
    t1013 = (int)(t1012);
    ((C_00454cb0*)(t1013))->FUN_00454cb0((unsigned int)(t1006), (unsigned int)(t1011));
    t1017 = (int)FUN_008409b0((unsigned int)(t1012));
    t1020 = (int)(*(int*)((char*)(t1005) + 48));
    t1021 = (int)(t1020 - (int)*(int*)((char*)(t1005) + 44));
    t1022 = (int)(t1021 >> (int)2);
    t1023 = (int)((int)0);
    if (t1022 > (int)0) {
        do {
            t1017 = (int)(*(int*)((char*)(t1005) + 44));
            t1024 = (int)(*(int*)((char*)(t1017) + (t1023)*4));
            if (t1024 != (int)0) {
                t1025 = (int)(*(int*)((char*)(t1012)));
                t1028 = (int)((int)(a4));
                t1017 = (int)((il2c_vc0*)(t1024))->s15((int)(t1028), (int)(t1025));
                if ((unsigned char)(t1017) != (unsigned char)0) goto La6d79d;
            }
            t1023 = (int)(t1023 + (int)1);
        } while (t1023 < t1022);
    }
    t1034 = false;
    return (bool)(t1034);
    La6d79d:;
    t1039 = true;
    return (bool)(t1039);
}
