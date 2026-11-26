// 0x007f6170: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIAnimation.cpp, match/slices/s007f5300/s007f5300.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013f63fc[];
extern "C" unsigned char g_01415404[];
struct C_007fd610 { int FUN_007fd610(unsigned int); };
struct C_007fd650 { void FUN_007fd650(float, float, float, float, float, unsigned int); };
extern "C" int __cdecl FUN_009512c0(...);
extern "C" int __cdecl FUN_009512d0(...);

// @ 0x007f6170
extern "C" int __cdecl FUN_007f6170(int a4, float a8, float a12, float a16, int a20, int a24, float a28, float a32)
{
    int t1003;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    int t1026;
    int t1030;
    int t1031;
    int t1035;
    t1003 = (int)((int)(a4));
    *(int*)((char*)(t1003)) = (int)((int)g_013f63fc);
    *(int*)((char*)(t1003) + 4) = (int)((int)0);
    t1007 = (int)FUN_009512c0();
    t1010 = (int)FUN_009512d0((unsigned int)((int)80), (unsigned int)((int)4), (unsigned int)((int)g_01415404), (unsigned int)(t1007));
    if (t1010 != (int)0) {
        t1011 = (int)((int)(a20));
        t1012 = (int)(t1010);
        t1015 = (int)((C_007fd610*)(t1012))->FUN_007fd610((unsigned int)(t1011));
        t1016 = (int)(t1015);
    } else {
        t1016 = (int)((int)0);
    }
    t1017 = (int)(*(int*)((char*)(t1003) + 4));
    if (t1016 != t1017) {
        if (t1016 != (int)0) {
            t1020 = (int)(t1016);
            ((il2c_vc0*)(t1020))->s0();
        }
        *(int*)((char*)(t1003) + 4) = (int)(t1016);
        if (t1017 != (int)0) {
            t1026 = (int)(t1017);
            ((il2c_vc1*)(t1026))->s1();
        }
    }
    t1030 = (int)((int)(a24));
    t1031 = (int)(t1016);
    ((C_007fd650*)(t1031))->FUN_007fd650((float)((float)(a8)), (float)((float)(a28)), (float)((float)(a32)), (float)((float)(a12)), (float)((float)(a16)), (unsigned int)(t1030));
    t1035 = (int)(t1003);
    return (int)(t1035);
}
