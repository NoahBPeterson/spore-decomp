// 0x00804f80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIHelpers.cpp, match/slices/s00804920/s00804920.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};

extern "C" int __cdecl FUN_0067caa0(...);
struct C_00813040 { int FUN_00813040(float, float, unsigned int, unsigned int); };

// @ 0x00804f80
// @ 0x00804f80
extern "C" void __cdecl FUN_00804f80(float a4, float a8, int a12, int a16)
{
    int t1001;
    int t1005;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    t1001 = (int)FUN_0067caa0();
    t1005 = (int)(t1001);
    t1007 = (int)((il2c_vc0*)(t1005))->s1();
    if (t1007 != (int)0) {
        t1010 = (int)(t1007 + (int)(-4));
    } else {
        t1010 = (int)((int)0);
    }
    t1011 = (int)((int)(a16));
    t1012 = (int)((int)(a12));
    ((C_00813040*)(t1010))->FUN_00813040((float)((float)(a4)), (float)((float)(a8)), (unsigned int)(t1012), (unsigned int)(t1011));
    return;
}
