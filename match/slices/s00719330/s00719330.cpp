// 0x00719330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00718640/s00718640.cpp, src/game/SPEngine/_at_00710000.cpp.

struct C_007146c0 { void FUN_007146c0(); };
extern "C" int __cdecl FUN_00717a90(...);

// @ 0x00719330
extern "C" int __fastcall FUN_00719330(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00717a90((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((C_007146c0*)cursor)->FUN_007146c0();
            cursor += 208;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    *(int*)((char*)(int)value + 4) += (value3 - value2) / -208 * 208;
    return value2;
}
