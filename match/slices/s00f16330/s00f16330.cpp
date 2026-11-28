// 0x00f16330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00f10000.cpp, match/slices/s00f15890/s00f15890.cpp.

struct VObject {
    virtual void Unk_00(int);
};

extern "C" int __cdecl FUN_00f14900(...);

// @ 0x00f16330
extern "C" int __fastcall FUN_00f16330(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00f14900((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((VObject*)cursor)->Unk_00(0);
            cursor += 112;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    *(int*)((char*)(int)value + 4) += (value3 - value2) / -112 * 112;
    return value2;
}
