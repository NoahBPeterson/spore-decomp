// 0x00c144e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c14350/s00c14350.cpp.

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00c144e0
extern "C" int __fastcall FUN_00c144e0(char* value, int unused, int obj)
{
    int value2;
    int result = *(int*)((char*)(int)value + 0x1c);
    if (result != 0) {
        *(int*)((char*)(int)value + 0x1c) = *(int*)result;
    } else {
        value2 = *(int*)((char*)(int)value + 0x2c);
        result = (int)FUN_00f473a0((unsigned int)value2, (unsigned int)(int)DAT_013f09b4, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
    }
    if (result != 0) {
        *(int*)result = *(int*)obj;
        *(int*)((char*)result + 4) = *(int*)((char*)obj + 4);
    }
    *(int*)((char*)result + 8) = 0;
    return result;
}
