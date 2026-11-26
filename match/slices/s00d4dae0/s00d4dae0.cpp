// 0x00d4dae0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPDramaManager.cpp, match/slices/s00d4d5c0/s00d4d5c0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

struct C_00530c80 { void FUN_00530c80(unsigned int, unsigned int); };
struct C_00621f50 { int FUN_00621f50(unsigned int, unsigned int); };
struct C_00b225d0 { void FUN_00b225d0(unsigned int); };
extern "C" int __cdecl FUN_00b3d300(...);

// @ 0x00d4dae0
extern "C" void __fastcall FUN_00d4dae0(char* self, int edx_unused)
{
    int t1005;
    int t1006;
    int t1012;
    int t1013;
    int t1014;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1030;
    int t1031;
    int t1032;
    t1005 = (int)((int)(self));
    t1006 = (int)(*(int*)((char*)(t1005) + 64));
    if (t1006 != (int)0) {
        *(int*)((char*)(t1005) + 64) = (int)((int)0);
        ((il2c_vc0*)(t1006))->s1();
    }
    t1012 = (int)(*(int*)((char*)(t1005) + 72));
    t1013 = (int)(*(int*)((char*)(t1005) + 68));
    t1014 = (int)(t1005 + (int)68);
    ((C_00530c80*)(t1014))->FUN_00530c80((unsigned int)(t1013), (unsigned int)(t1012));
    t1020 = (int)FUN_00b3d300();
    t1021 = (int)(*(int*)((char*)(t1005) + 92));
    t1022 = (int)(t1005 + (int)92);
    t1023 = (int)(*(int*)((char*)(t1005) + 96));
    t1024 = (int)(t1020);
    if (t1021 != t1023) {
        do {
            t1025 = (int)(*(int*)((char*)(t1021) + 4));
            t1026 = (int)(t1024);
            ((C_00b225d0*)(t1026))->FUN_00b225d0((unsigned int)(t1025));
            t1021 = (int)(t1021 + (int)8);
        } while (t1021 != t1023);
    }
    t1030 = (int)(*(int*)((char*)(t1022) + 4));
    t1031 = (int)(*(int*)((char*)(t1022)));
    t1032 = (int)(t1022);
    ((C_00621f50*)(t1032))->FUN_00621f50((unsigned int)(t1031), (unsigned int)(t1030));
    return;
}
