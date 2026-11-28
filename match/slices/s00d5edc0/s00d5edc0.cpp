// 0x00d5edc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCityVisualizer.cpp, match/slices/s00d5e730/s00d5e730.cpp.

struct C_00afbad0 { void FUN_00afbad0(); };
extern "C" int __cdecl FUN_00d5d530(...);

// @ 0x00d5edc0
extern "C" int __fastcall FUN_00d5edc0(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00d5d530((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((C_00afbad0*)cursor)->FUN_00afbad0();
            cursor += 100;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    *(int*)((char*)(int)value + 4) += (value3 - value2) / -100 * 100;
    return value2;
}
