// 0x006a2b20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPPropertyList.cpp, match/slices/s006a22a0/s006a22a0.cpp.

extern "C" int __cdecl FUN_00612b20(...);
struct C_00685a30 { void FUN_00685a30(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0092cb00(...);

// @ 0x006a2b20
extern "C" int __fastcall FUN_006a2b20(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1012;
    int t1010;
    int t1011;
    int t1013;
    int t1016;
    int t1017;
    int t1021;
    int t1028;
    int t10;
    int t1029;
    int t1030;
    int t1031;
    int t1032;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 56));
    t1005 = (int)(*(int*)((char*)(t1003) + 60));
    FUN_0092cb00((unsigned int)(t1005), (unsigned int)((int)0), (unsigned int)(t1004));
    t1012 = (int)(t1003 + (int)24);
    t1010 = (int)(*(int*)((char*)(t1012)));
    t1011 = (int)(*(int*)((char*)(t1012) + 4));
    t1013 = (int)FUN_00612b20((unsigned int)(t1011), (unsigned int)(t1011), (unsigned int)(t1010));
    t1016 = (int)(*(int*)((char*)(t1012) + 4));
    t1017 = (int)(t1012);
    ((C_00685a30*)(t1017))->FUN_00685a30((unsigned int)(t1013), (unsigned int)(t1016));
    t1021 = (int)(t1011 - t1010);
    t1028 = (int)(t1021 / (int)(-24));
    t10 = (int)(t1028 << (int)1);
    t1029 = (int)(t1028 + t10);
    t1030 = (int)(t1029 + t1029);
    t1031 = (int)(t1030 + t1030);
    t1032 = (int)(t1031 + t1031);
    *(int*)((char*)(t1012) + 4) += t1032;
    return (int)(t1032);
}
