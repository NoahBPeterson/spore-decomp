// 0x00d473e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureModeStrategy.cpp, match/slices/s00d463a0/s00d463a0.cpp.

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013f09b4[];
struct C_00d47320 { void FUN_00d47320(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00d473e0
extern "C" int __fastcall FUN_00d473e0(char* value, int unused, int value2)
{
    int value3;
    int ptr = *(int*)((char*)(int)value + 0x1c);
    if (ptr != 0) {
        *(int*)((char*)(int)value + 0x1c) = *(int*)ptr;
    } else {
        value3 = *(int*)((char*)(int)value + 0x2c);
        ptr = (int)FUN_00f473a0((unsigned int)value3, (unsigned int)(int)DAT_013f09b4, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
    }
    if (ptr != 0) {
        ((C_00d47320*)ptr)->FUN_00d47320((unsigned int)value2);
    }
    int result = ptr;
    *(int*)((char*)ptr + 0x184) = 0;
    return result;
}
