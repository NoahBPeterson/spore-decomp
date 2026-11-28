// 0x01134ae0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01133a80/s01133a80.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1(int);
};


// @ 0x01134ae0
extern "C" void __cdecl FUN_01134ae0(int a4)
{
    int t1000;
    t1000 = (int)((int)(a4));
    ((il2c_vc0*)(t1000))->s1((int)((int)0));
    return;
}
