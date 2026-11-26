// 0x013ca7f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s013c31a0/s013c31a0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};

extern "C" unsigned char g_01416f14[];
extern "C" unsigned char g_014996d4[];
extern "C" unsigned char g_015b7648[];
extern "C" unsigned char g_015b7650[];
extern "C" unsigned char g_015b7654[];
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x013ca7f0
extern "C" int __cdecl FUN_013ca7f0(void)
{
    int t1000;
    int t1001;
    int t1007;
    int t1012;
    t1000 = (int)((int)(*(int*)g_015b7650));
    *(int*)g_015b7648 = (int)((int)g_014996d4);
    if (t1000 != (int)0) {
        t1001 = (int)(t1000);
        t1000 = (int)((int)0);
        *(int*)g_015b7650 = (int)(t1000);
        if (t1001 != (int)0) {
            ((il2c_vc0*)(t1001))->s1();
            t1000 = (int)((int)(*(int*)g_015b7650));
        }
    }
    t1007 = (int)((int)(*(int*)g_015b7654));
    if (t1007 != (int)0) {
        if ((int)*(int*)((char*)(t1007) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1007));
            t1000 = (int)((int)(*(int*)g_015b7650));
        }
    }
    if (t1000 != (int)0) {
        t1012 = (int)(t1000);
        t1000 = (int)((il2c_vc1*)(t1012))->s1();
    }
    *(int*)g_015b7648 = (int)((int)g_01416f14);
    return (int)(t1000);
}
