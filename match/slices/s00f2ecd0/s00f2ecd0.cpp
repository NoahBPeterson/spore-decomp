// 0x00f2ecd0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f2e7d0/s00f2e7d0.cpp.

struct C_00dfd300 { void FUN_00dfd300(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00dfe9a0(...);

// @ 0x00f2ecd0
extern "C" int __fastcall FUN_00f2ecd0(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    int t1023;
    int t1024;
    int t1025;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003)));
    t1006 = (int)(*(int*)((char*)(t1003) + 4));
    t1009 = (int)FUN_00dfe9a0((unsigned int)(t1006), (unsigned int)(t1006), (unsigned int)(t1004));
    t1010 = (int)(*(int*)((char*)(t1003) + 4));
    t1011 = (int)(t1003);
    ((C_00dfd300*)(t1011))->FUN_00dfd300((unsigned int)(t1009), (unsigned int)(t1010));
    t1015 = (int)(t1006 - t1004);
    t1023 = (int)(t1015 / (int)(-568));
    t1024 = (int)(t1023 * (int)568);
    *(int*)((char*)(t1003) + 4) += t1024;
    t1025 = (int)((int)1073741823);
    *(int*)((char*)(t1003) + 20) = (int)(t1025);
    *(int*)((char*)(t1003) + 24) = (int)(t1025);
    return (int)(t1025);
}
