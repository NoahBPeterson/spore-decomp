// 0x00bc7110: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bc6360/s00bc6360.cpp.

struct C_00bc4730 { void FUN_00bc4730(); };
extern "C" int __cdecl FUN_00bc6570(...);

// @ 0x00bc7110
extern "C" int __fastcall FUN_00bc7110(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00bc6570((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((C_00bc4730*)cursor)->FUN_00bc4730();
            cursor += 1972;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    *(int*)((char*)(int)value + 4) += (value3 - value2) / -1972 * 1972;
    return value2;
}
