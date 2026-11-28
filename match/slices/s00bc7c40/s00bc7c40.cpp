// 0x00bc7c40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bc74d0/s00bc74d0.cpp.

struct C_00bc78d0 { void FUN_00bc78d0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00bc79f0(...);

// @ 0x00bc7c40
extern "C" int __fastcall FUN_00bc7c40(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int value5 = (int)FUN_00bc79f0((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value6 = *(int*)((char*)(int)value + 4);
    ((C_00bc78d0*)(int)value)->FUN_00bc78d0((unsigned int)value5, (unsigned int)value6);
    int value7 = (value3 - value2) / -60;
    int value8 = (value7 << 4) - value7;
    int value9 = value8 + value8;
    *(int*)((char*)(int)value + 4) += value9 + value9;
    return value2;
}
