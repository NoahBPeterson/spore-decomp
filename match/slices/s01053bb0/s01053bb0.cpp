// 0x01053bb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s010527f0/s010527f0.cpp, src/game/SPGonzago/SPToolStrategies.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};

extern "C" int __stdcall FUN_00b3d390(unsigned int);
struct C_0104fa90 { int FUN_0104fa90(); };

// @ 0x01053bb0
extern "C" void __stdcall FUN_01053bb0(int a4, int a8)
{
    int t1001;
    int t1002;
    int t1007;
    int t1010;
    int t1011;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001) + 320));
    if (t1002 != (int)0) {
        t1007 = (int)((il2c_vc0*)(t1002))->s4();
        if ((unsigned char)(t1007) == (unsigned char)0) {
            t1010 = (int)FUN_00b3d390((unsigned int)(t1001));
            t1011 = (int)(t1010);
            t1007 = (int)((C_0104fa90*)(t1011))->FUN_0104fa90();
        }
    }
    return;
}
