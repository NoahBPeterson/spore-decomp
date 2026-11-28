// 0x007f8540: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s007f8540/s007f8540.cpp.

struct VObject {
    virtual void Unk_00(int);
};

extern "C" int __cdecl FUN_007f7a60(...);

// @ 0x007f8540
extern "C" int __fastcall FUN_007f8540(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_007f7a60((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((VObject*)cursor)->Unk_00(0);
            cursor += 140;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    *(int*)((char*)(int)value + 4) += (value3 - value2) / -140 * 140;
    return value2;
}
