// 0x00ae7e10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00ae73e0/guicomm.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual int Unk_02(int, int);
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int, int);
};
struct VObject3 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06(int);
};
struct VObject4 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual int Unk_02(int, int);
};
struct VObject5 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int, int);
};
struct VObject6 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04(int, int);
};
struct VObject7 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06(int);
};
struct VObject8 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual void Unk_07();
    virtual void Unk_08(int, int);
};
struct VObject9 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual void Unk_07();
    virtual void Unk_08();
    virtual int Unk_09(int, float);
};

extern "C" float DAT_013eb1bc;
struct C_00a02ab0 { void FUN_00a02ab0(unsigned int); };
struct C_00a02b20 { int FUN_00a02b20(unsigned int); };

// @ 0x00ae7e10
extern "C" void __fastcall FUN_00ae7e10(char* value, int unused, int value2, int value3, int value4, int value5)
{
    int ptr;
    int value6;
    int value7;
    int value8;
    int ptr2;
    int value9;
    int ptr3;
    ptr = *(int*)((char*)(int)value + value4 * 4 + 44);
    if (ptr != 0) {
        if ((unsigned char)value5 == 0) {
            value6 = *(int*)((char*)(int)value + value4 * 4 + 68);
            if (value6 != 0) {
                value7 = (int)((C_00a02b20*)ptr)->FUN_00a02b20((unsigned int)value6);
                if ((unsigned char)value7 == 0) goto done;
            }
        }
        ((C_00a02ab0*)*(int*)((char*)(int)value + value4 * 4 + 44))->FUN_00a02ab0((unsigned int)0);
        if (value2 != 0) {
            value8 = ((VObject*)*(int*)((char*)(int)value + value4 * 4 + 44))->Unk_02(value2, 0);
            ptr2 = *(int*)((char*)(int)value + value4 * 4 + 44);
            *(int*)((char*)(int)value + value4 * 4 + 60) = value8;
            ((VObject2*)ptr2)->Unk_03(value8, 1);
            ((VObject3*)*(int*)((char*)(int)value + value4 * 4 + 44))->Unk_06(*(int*)((char*)(int)value + value4 * 4 + 60));
        }
        value7 = value3;
        if (value7 != 0) {
            value9 = ((VObject4*)*(int*)((char*)(int)value + value4 * 4 + 44))->Unk_02(value7, 0);
            ptr3 = *(int*)((char*)(int)value + value4 * 4 + 44);
            *(int*)((char*)(int)value + value4 * 4 + 68) = value9;
            ((VObject5*)ptr3)->Unk_03(value9, 0);
            ((VObject6*)*(int*)((char*)(int)value + value4 * 4 + 44))->Unk_04(*(int*)((char*)(int)value + value4 * 4 + 68), 1);
            ((VObject7*)*(int*)((char*)(int)value + value4 * 4 + 44))->Unk_06(*(int*)((char*)(int)value + value4 * 4 + 68));
            ((VObject8*)*(int*)((char*)(int)value + value4 * 4 + 44))->Unk_08(*(int*)((char*)(int)value + value4 * 4 + 68), 1);
            value7 = ((VObject9*)*(int*)((char*)(int)value + value4 * 4 + 44))->Unk_09(*(int*)((char*)(int)value + value4 * 4 + 68), DAT_013eb1bc);
        }
    }
    done:
    return;
}
