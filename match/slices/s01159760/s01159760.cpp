// 0x01159760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s01159630/s01159630.cpp.

extern "C" void __cdecl FUN_0116b6c0(...);
extern "C" void __cdecl FUN_0116b7c0(...);
extern "C" void __cdecl FUN_0116b920(...);
extern "C" int DAT_016e80a0;
extern "C" int DAT_016e80a4;
extern "C" int DAT_016e80a8;
extern "C" int DAT_016e80ac;
extern "C" int DAT_016e80b0;
extern "C" int DAT_016e80b4;
extern "C" int DAT_016e80e8;
extern "C" int DAT_016e80ec;
extern "C" int DAT_016e80f0;
extern "C" int DAT_016e80f4;
extern "C" int DAT_016e80f8;
extern "C" int DAT_016e80fc;

// @ 0x01159760
extern "C" int __cdecl FUN_01159760(void)
{
    int value = (int)&FUN_0116b920;
    DAT_016e80a0 = (int)&FUN_0116b7c0;
    DAT_016e80e8 = 44;
    DAT_016e80a8 = (int)&FUN_0116b6c0;
    DAT_016e80f0 = 60;
    DAT_016e80a4 = value;
    DAT_016e80ec = 48;
    DAT_016e80ac = (int)&FUN_0116b7c0;
    DAT_016e80f4 = 44;
    DAT_016e80b4 = (int)&FUN_0116b6c0;
    DAT_016e80fc = 60;
    DAT_016e80b0 = value;
    DAT_016e80f8 = 48;
    return 48;
}
