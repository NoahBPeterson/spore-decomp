// 0x00782800: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/_at_00780000.cpp, match/slices/s007819d0/s007819d0.cpp.

struct C_00781b10 { void FUN_00781b10(); };
extern "C" int __cdecl FUN_00782420(...);

// @ 0x00782800
extern "C" int __fastcall FUN_00782800(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00782420((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((C_00781b10*)(cursor + 4))->FUN_00781b10();
            cursor += 36;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    int value6 = (value3 - value2) / -36;
    int value7 = value6 + (value6 << 3);
    int value8 = value7 + value7;
    *(int*)((char*)(int)value + 4) += value8 + value8;
    return value2;
}
