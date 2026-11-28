// 0x00a05830: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00a04d20/s00a04d20.cpp, src/game/SPCreatureAnim/SPCreatureAnimManager.cpp.

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013f2150[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00a05830
extern "C" int __fastcall FUN_00a05830(char* value, int unused, int value2, int unused2)
{
    int value3;
    int value4;
    int value5;
    if (value2 != 0) {
        value3 = (value2 << 3) - value2;
        value4 = value3 + value3;
        value5 = (int)FUN_00f473a0((unsigned int)(value4 + value4), (unsigned int)(int)DAT_013f2150, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
    } else {
        value5 = 0;
    }
    int value6 = value5 + (((value2 << 3) - value2) << 2);
    *(int*)(int)value = value5;
    *(int*)((char*)(int)value + 4) = value5;
    *(int*)((char*)(int)value + 8) = value6;
    return (int)value;
}
