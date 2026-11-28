// 0x00e2c290: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPUIRolloverCivCity.cpp, match/slices/s00e2b9d0/s00e2b9d0.cpp.

struct C_006b5240 { void FUN_006b5240(); };
extern "C" int __cdecl FUN_00e2a6f0(...);

// @ 0x00e2c290
extern "C" int __fastcall FUN_00e2c290(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00e2a6f0((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((C_006b5240*)cursor)->FUN_006b5240();
            cursor += 20;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    int value6 = (value3 - value2) / -20;
    int value7 = value6 + (value6 << 2);
    int value8 = value7 + value7;
    *(int*)((char*)(int)value + 4) += value8 + value8;
    return value2;
}
