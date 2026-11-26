// 0x00de2de0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00de23a0/s00de23a0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_0147dba8[];
struct C_00de2a50 { void FUN_00de2a50(); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x00de2de0
extern "C" int __fastcall FUN_00de2de0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1007;
    unsigned char t4;
    int t1016;
    t1002 = (int)((int)(self));
    t1003 = (int)(t1002 + (int)64);
    ((C_00de2a50*)(t1003))->FUN_00de2a50();
    t1007 = (int)(*(int*)((char*)(t1002) + 52));
    if (t1007 != (int)0) {
        ((il2c_vc0*)(t1007))->s1();
    }
    t4 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002)) = (int)((int)g_0147dba8);
    if (t4 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1002));
    }
    t1016 = (int)(t1002);
    return (int)(t1016);
}
