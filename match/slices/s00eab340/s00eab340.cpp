// 0x00eab340: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPAudioNPCCityMusic.cpp, match/slices/s00eaa9a0/s00eaa9a0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual int s8();
};

extern "C" int __cdecl FUN_00571f80(unsigned int, unsigned int, float, float, float);
struct C_00a206f0 { int FUN_00a206f0(); };

// @ 0x00eab340
extern "C" void __fastcall FUN_00eab340(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1005;
    int t1007;
    int t1011;
    int t1012;
    int t1013;
    t1002 = (int)((int)(self));
    t1005 = (int)((C_00a206f0*)((int)(self)))->FUN_00a206f0();
    if (t1005 != (int)0) {
        t1007 = (int)(t1005);
        t1011 = (int)((il2c_vc0*)(t1007))->s8();
    } else {
        t1011 = (int)((int)0);
    }
    t1012 = (int)((int)(a4));
    *(int*)((char*)(t1002) + 20) = (int)(t1011);
    t1013 = (int)(*(int*)((char*)(t1002) + 16));
    FUN_00571f80((unsigned int)(t1013), (unsigned int)(t1011), (float)(*(float*)((char*)(t1012))), (float)(*(float*)((char*)(t1012) + 4)), (float)(*(float*)((char*)(t1012) + 8)));
    return;
}
