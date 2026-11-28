// 0x00b0dec0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00b0d2a0/s00b0d2a0.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual void Unk_07();
    virtual void Unk_08();
    virtual void Unk_09();
    virtual void Unk_0A();
    virtual void Unk_0B();
    virtual void Unk_0C();
    virtual void Unk_0D();
    virtual void Unk_0E();
    virtual void Unk_0F();
    virtual void Unk_10();
    virtual void Unk_11();
    virtual void Unk_12();
    virtual void Unk_13();
    virtual void Unk_14();
    virtual void Unk_15();
    virtual void Unk_16();
    virtual void Unk_17();
};

extern "C" int __cdecl FUN_00b0d0d0(...);

// @ 0x00b0dec0
extern "C" int __fastcall FUN_00b0dec0(char* value, int unused, int value2, int value3)
{
    int ptr2;
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00b0d0d0((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ptr2 = *(int*)cursor;
            if (ptr2 != 0) {
                ((VObject*)ptr2)->Unk_17();
            }
            cursor += 4;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    int value6 = -((value3 - value2) >> 2);
    int value7 = value6 + value6;
    *(int*)((char*)(int)value + 4) += value7 + value7;
    return value2;
}
