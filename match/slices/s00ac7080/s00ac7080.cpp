// 0x00ac7080: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ac6b90/s00ac6b90.cpp.

extern "C" void __cdecl FUN_00ac6da0(...);

// @ 0x00ac7080
extern "C" int __fastcall FUN_00ac7080(char* self, int edx_unused)
{
    int t1004;
    int t1005;
    int t1006;
    int t1010;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 68));
    t1006 = (int)(*(int*)((char*)(t1004) + 72));
    FUN_00ac6da0((unsigned int)(t1006), (unsigned int)(t1006), (unsigned int)(t1005));
    t1010 = (int)(t1006 - t1005);
    t1018 = (int)(t1010 / (int)(-60));
    t1019 = (int)(t1018);
    t1020 = (int)(t1019 << (int)4);
    t1021 = (int)(t1020 - t1018);
    t1022 = (int)(t1021 + t1021);
    t1023 = (int)(t1022 + t1022);
    *(int*)((char*)(t1004) + 72) += t1023;
    return (int)(t1018);
}
