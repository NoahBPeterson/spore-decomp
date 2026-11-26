// 0x00b00560: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlanet.cpp, match/slices/s00b00520/s00b00520.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual int s2(int);
};

extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00b00560
extern "C" void __fastcall FUN_00b00560(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1010;
    int t1014;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003)));
    t1006 = (int)(*(int*)((char*)(t1003) + 4));
    if ((unsigned int)(t1004) < (unsigned int)(t1006)) {
        t1007 = (int)(t1006);
        do {
            t1010 = (int)(t1004);
            ((il2c_vc0*)(t1010))->s2((int)((int)0));
            t1004 = (int)(t1004 - (int)(-128));
        } while ((unsigned int)(t1004) < (unsigned int)(t1007));
    }
    t1014 = (int)(*(int*)((char*)(t1003)));
    if (t1014 != (int)0) {
        if ((int)*(int*)((char*)(t1014) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1014));
        }
    }
    return;
}
