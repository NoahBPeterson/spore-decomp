// 0x0089ed40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int, int);
};


// @ 0x0089ed40
extern "C" void __cdecl FUN_0089ed40(int a4, int a8)
{
    int t1000;
    int t1002;
    t1000 = (int)((int)(a8));
    t1002 = (int)((int)(a4));
    ((il2c_vc0*)(t1000))->s3((int)(t1002), (int)((int)0));
    return;
}
