// 0x006abe50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s006ab3d0/s006ab3d0.cpp.

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013ebc58[];
struct C_00926650 { int FUN_00926650(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x006abe50
extern "C" int __fastcall FUN_006abe50(char* value, int unused, int value2, int value3)
{
    int result;
    if ((unsigned int)value2 <= 20) {
        again:
        if (*(int*)((char*)(int)value + 0x10) == 0) {
            if ((unsigned char)(int)((C_00926650*)(int)value)->FUN_00926650((unsigned int)0, (unsigned int)0) != 0) goto again;
            return 0;
        }
        result = *(int*)((char*)(int)value + 0x10);
        *(int*)((char*)(int)value + 0x10) = *(int*)result;
        return result;
    }
    return (int)FUN_00f473a0((unsigned int)value2, (unsigned int)(int)DAT_013ebc58, (unsigned int)value3, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
}
