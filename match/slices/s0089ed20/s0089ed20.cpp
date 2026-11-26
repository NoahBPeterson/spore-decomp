// 0x0089ed20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual int s2(int, int, int);
};

extern "C" unsigned char g_0142fde0[];

// @ 0x0089ed20
extern "C" void __cdecl FUN_0089ed20(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    *(int*)((char*)(t1001)) = (int)(t1000);
    t1002 = (int)((int)(a12));
    ((il2c_vc0*)(t1002))->s2((int)(t1000), (int)((int)g_0142fde0), (int)((int)0));
    return;
}
