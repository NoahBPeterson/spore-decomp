// 0x00957a60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/UTFSpore_Win32/_at_00950000.cpp, match/slices/s009579f0/s009579f0.cpp.

extern "C" unsigned char DAT_0154edf0[];
extern "C" int DAT_0154edfc;
extern "C" int DAT_0154ee00;
extern "C" int DAT_0154ee04;
extern "C" unsigned char DAT_0166b138[];

// @ 0x00957a60
extern "C" int __cdecl FUN_00957a60(int value, int value2)
{
    if ((*(unsigned char*)DAT_0166b138 & 1) == 0) {
        *(int*)DAT_0166b138 = *(int*)DAT_0166b138 | 1;
        DAT_0154edfc = value;
        DAT_0154ee00 = value2;
        DAT_0154ee04 = 0;
    }
    return (int)DAT_0154edf0;
}
