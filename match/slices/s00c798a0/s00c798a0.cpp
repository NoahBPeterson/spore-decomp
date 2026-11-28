// 0x00c798a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPPlayer.cpp, match/slices/s00c793e0/s00c793e0.cpp.

struct C_00b638b0 { void FUN_00b638b0(); };
extern "C" int __cdecl FUN_00c771e0(...);

// @ 0x00c798a0
extern "C" int __fastcall FUN_00c798a0(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00c771e0((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((C_00b638b0*)(cursor + 8))->FUN_00b638b0();
            cursor += 40;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    int value6 = (value3 - value2) / -40;
    int value7 = value6 + (value6 << 2);
    int value8 = value7 + value7;
    int value9 = value8 + value8;
    *(int*)((char*)(int)value + 4) += value9 + value9;
    return value2;
}
