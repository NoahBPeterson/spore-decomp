// 0x00b07140: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00b06e10/s00b06e10.cpp, src/game/SPGonzago/SPPlanet.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02(int);
};

extern "C" int __cdecl FUN_00b03f10(...);

// @ 0x00b07140
extern "C" int __fastcall FUN_00b07140(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00b03f10((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int ptr2 = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((VObject*)ptr2)->Unk_02(0);
            ptr2 -= -128;
        } while ((unsigned int)ptr2 < (unsigned int)value5);
    }
    *(int*)((char*)(int)value + 4) += -((value3 - value2) >> 7) << 7;
    return value2;
}
