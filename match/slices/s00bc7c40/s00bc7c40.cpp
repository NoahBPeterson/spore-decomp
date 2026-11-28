// 0x00bc7c40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bc74d0/s00bc74d0.cpp.

struct C_00bc78d0 { void FUN_00bc78d0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00bc79f0(...);

// @ 0x00bc7c40
extern "C" int __fastcall FUN_00bc7c40(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1016;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1032;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(a8));
    t1006 = (int)((int)(self));
    t1007 = (int)(*(int*)((char*)(t1006) + 4));
    t1008 = (int)FUN_00bc79f0((unsigned int)(t1004), (unsigned int)(t1007), (unsigned int)(t1001));
    t1011 = (int)(*(int*)((char*)(t1006) + 4));
    t1012 = (int)(t1006);
    ((C_00bc78d0*)(t1012))->FUN_00bc78d0((unsigned int)(t1008), (unsigned int)(t1011));
    t1016 = (int)(t1004 - t1001);
    t1024 = (int)(t1016 / (int)(-60));
    t1025 = (int)(t1024);
    t1026 = (int)(t1025 << (int)4);
    t1027 = (int)(t1026 - t1024);
    t1028 = (int)(t1027 + t1027);
    t1029 = (int)(t1028 + t1028);
    *(int*)((char*)(t1006) + 4) += t1029;
    t1032 = (int)(t1001);
    return (int)(t1032);
}
