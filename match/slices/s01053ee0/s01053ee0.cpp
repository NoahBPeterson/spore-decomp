// 0x01053ee0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolStrategies.cpp, match/slices/s010527f0/s010527f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};

struct C_00cb61d0 { int FUN_00cb61d0(); };

// @ 0x01053ee0
extern "C" bool __stdcall FUN_01053ee0(int a4)
{
    int t1001;
    int t1002;
    int t1006;
    bool t1011;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001) + 288));
    if (t1002 != (int)0) {
        ((C_00cb61d0*)(t1002))->FUN_00cb61d0();
        t1006 = (int)(*(int*)((char*)(t1001) + 288));
        if (t1006 != (int)0) {
            *(int*)((char*)(t1001) + 288) = (int)((int)0);
            ((il2c_vc0*)(t1006))->s1();
        }
    }
    t1011 = true;
    return (bool)(t1011);
}
