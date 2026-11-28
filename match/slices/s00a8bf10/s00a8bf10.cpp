// 0x00a8bf10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00a8b940/s00a8b940.cpp.

extern "C" void __cdecl FUN_00a8a8b0(...);
extern "C" void __cdecl FUN_00a8aec0(...);
extern "C" void __cdecl FUN_00a8b420(...);
extern "C" void __cdecl FUN_00a8b940(...);
extern "C" unsigned char DAT_016781b0[];
extern "C" int DAT_016781b8;
extern "C" int DAT_016781bc;
extern "C" int DAT_016781c0;
extern "C" int __cdecl FUN_011e073e(...);

// @ 0x00a8bf10
extern "C" void __cdecl FUN_00a8bf10(int value)
{
    if ((unsigned char)value != 0) {
        FUN_011e073e((unsigned int)(int)DAT_016781b0, (unsigned int)0, (unsigned int)128);
        *(int*)DAT_016781b0 = (int)&FUN_00a8a8b0;
        DAT_016781b8 = (int)&FUN_00a8aec0;
        DAT_016781bc = (int)&FUN_00a8b420;
        DAT_016781c0 = (int)&FUN_00a8b940;
    }
    return;
}
