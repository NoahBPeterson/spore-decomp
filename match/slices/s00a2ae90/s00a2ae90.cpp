// 0x00a2ae90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPAudio/AudioSystem.cpp, match/slices/s00a2a020/s00a2a020.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
};

extern "C" int __cdecl FUN_00a22730(...);

// @ 0x00a2ae90
extern "C" int __fastcall FUN_00a2ae90(char* value, int unused, int value2, int value3)
{
    int value6;
    int cursor;
    int count;
    int ptr2;
    int result = value2;
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00a22730((unsigned int)value3, (unsigned int)value4, (unsigned int)result);
    int value5 = *(int*)((char*)(int)value + 4);
    if ((unsigned int)ptr < (unsigned int)value5) {
        value6 = value5 - ptr;
        cursor = ptr + 16;
        count = (int)((value6 - 1) / (unsigned int)20) + 1;
        do {
            ptr2 = *(int*)cursor;
            if (ptr2 != 0) {
                ((VObject*)ptr2)->Unk_01();
            }
            cursor += 20;
            --count;
        } while (count != 0);
        result = value2;
    }
    int value7 = (value3 - result) / -20;
    int value8 = value7 + (value7 << 2);
    int value9 = value8 + value8;
    *(int*)((char*)(int)value + 4) += value9 + value9;
    return result;
}
