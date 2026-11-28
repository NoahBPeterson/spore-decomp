// 0x00c8deb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPOrnament.cpp, match/slices/s00c8db30/s00c8db30.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

struct C_005f3680 { void FUN_005f3680(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_005f4e10(...);
struct C_00c8b2e0 { void FUN_00c8b2e0(); };

// @ 0x00c8deb0
// @ 0x00c8deb0
extern "C" void __fastcall FUN_00c8deb0(char* self, int edx_unused)
{
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1031;
    t1005 = (int)((int)(self));
    t1006 = (int)(*(int*)((char*)(t1005) + 264));
    t1007 = (int)(*(int*)((char*)(t1005) + 268));
    t1008 = (int)(t1005 + (int)264);
    t1009 = (int)FUN_005f4e10((unsigned int)(t1007), (unsigned int)(t1007), (unsigned int)(t1006));
    t1012 = (int)(*(int*)((char*)(t1008) + 4));
    t1013 = (int)(t1008);
    ((C_005f3680*)(t1013))->FUN_005f3680((unsigned int)(t1009), (unsigned int)(t1012));
    t1017 = (int)(t1007 - t1006);
    t1018 = (int)(t1017 >> (int)2);
    t1019 = (int)(-t1018);
    t1020 = (int)(t1019 + t1019);
    t1021 = (int)(t1020 + t1020);
    *(int*)((char*)(t1008) + 4) += t1021;
    t1022 = (int)(*(int*)((char*)(t1005) + 44));
    if (t1022 != (int)0) {
        *(int*)((char*)(t1005) + 44) = (int)((int)0);
        ((il2c_vc0*)(t1022))->s1();
    }
    t1031 = (int)(t1005 + (int)52);
    ((C_00c8b2e0*)(t1031))->FUN_00c8b2e0();
    return;
}
