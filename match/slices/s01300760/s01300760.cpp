// 0x01300760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s01300280/s01300280.cpp.

extern "C" void __cdecl FUN_013c1150(...);
extern "C" float DAT_01470f1c;
extern "C" float DAT_01485720;
extern "C" unsigned char DAT_0154df28[];
extern "C" int DAT_0166b194;
extern "C" int DAT_0166b198;
extern "C" int DAT_0166b19c;
extern "C" float DAT_0166b1a0;
extern "C" float DAT_0166b1a4;
extern "C" int DAT_0166b1a8;
extern "C" int DAT_0166b1ac;
extern "C" int DAT_0166b1b0;
extern "C" int __cdecl FUN_00925cb0(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x01300760
extern "C" void __cdecl FUN_01300760(void)
{
    int value = (int)FUN_00925cb0();
    float f = DAT_01485720;
    DAT_0166b1ac = value;
    DAT_0166b1a0 = f;
    DAT_0166b1a4 = DAT_01470f1c;
    DAT_0166b1b0 = 0;
    DAT_0166b198 = 1;
    DAT_0166b194 = (int)DAT_0154df28;
    DAT_0166b19c = 0;
    DAT_0166b1a8 = 0;
    FUN_011e07ef((unsigned int)(int)&FUN_013c1150);
    return;
}
