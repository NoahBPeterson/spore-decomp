// 0x00621f50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00621830/s00621830.cpp, src/game/SPEditors/SPXHTMLControlAppearance.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
};

extern "C" int __cdecl FUN_00a35070(...);

// @ 0x00621f50
extern "C" int __fastcall FUN_00621f50(char* value, int unused, int value2, int value3)
{
    int value6;
    int cursor;
    int count;
    int ptr2;
    int result = value2;
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00a35070((unsigned int)value3, (unsigned int)value4, (unsigned int)result);
    int value5 = *(int*)((char*)(int)value + 4);
    if ((unsigned int)ptr < (unsigned int)value5) {
        value6 = (int)((unsigned int)(value5 - ptr - 1) >> 3) + 1;
        cursor = ptr + 4;
        count = value6;
        do {
            ptr2 = *(int*)cursor;
            if (ptr2 != 0) {
                ((VObject*)ptr2)->Unk_01();
            }
            cursor += 8;
            --count;
        } while (count != 0);
        result = value2;
    }
    int value7 = -((value3 - result) >> 3);
    int value8 = value7 + value7;
    int value9 = value8 + value8;
    *(int*)((char*)(int)value + 4) += value9 + value9;
    return result;
}
