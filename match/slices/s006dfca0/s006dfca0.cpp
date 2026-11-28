// 0x006dfca0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsChartPacker.cpp, match/slices/s006deee0/s006deee0.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
};

extern "C" int __cdecl FUN_006df2d0(...);

// @ 0x006dfca0
extern "C" int __fastcall FUN_006dfca0(char* value, int unused, int value2, int value3)
{
    int value6;
    int cursor;
    int count;
    int ptr2;
    int result = value2;
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_006df2d0((unsigned int)value3, (unsigned int)value4, (unsigned int)result);
    int value5 = *(int*)((char*)(int)value + 4);
    if ((unsigned int)ptr < (unsigned int)value5) {
        value6 = (int)((unsigned int)(value5 - ptr - 1) >> 4) + 1;
        cursor = ptr + 12;
        count = value6;
        do {
            ptr2 = *(int*)cursor;
            if (ptr2 != 0) {
                ((VObject*)ptr2)->Unk_01();
            }
            cursor += 16;
            --count;
        } while (count != 0);
        result = value2;
    }
    *(int*)((char*)(int)value + 4) += -((value3 - result) >> 4) << 4;
    return result;
}
