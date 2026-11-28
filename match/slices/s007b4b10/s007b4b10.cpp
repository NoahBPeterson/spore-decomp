// 0x007b4b10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsThumbnailManager.cpp, match/slices/s007b49f0/s007b49f0.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int, int, int, int);
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int, int, int, int);
};
struct VObject3 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual int Unk_03(int, int, int, int);
};

// @ 0x007b4b10
extern "C" void __fastcall FUN_007b4b10(char* value, int unused, int obj, int obj2, int obj3, int value2)
{
    int v_l16[4];
    int ptr;
    int ptr2;
    int value3;
    int ptr3;
    int ptr4;
    int ptr5;
    int ptr6;
    if (*(unsigned char*)((char*)(int)value + 0x10d1) != 0) {
        *(int*)&v_l16[0] = *(int*)((char*)(int)value + 0x10e0);
        *(int*)&v_l16[1] = 0;
        *(int*)&v_l16[2] = 0;
        *(int*)&v_l16[3] = 0;
        ptr = *(int*)((char*)(int)value + 0x10d4);
        *(int*)((char*)ptr + 0x10) = *(int*)obj;
        *(int*)((char*)ptr + 0x14) = *(int*)((char*)obj + 4);
        ptr2 = *(int*)((char*)(int)value + 0x10d4);
        *(int*)((char*)ptr2 + 0x1c) = *(int*)obj2;
        *(int*)((char*)ptr2 + 0x20) = *(int*)((char*)obj2 + 4);
        ((VObject*)*(int*)((char*)(int)value + 0x10d4))->Unk_03(0, 0, (int)&v_l16, value2);
        value3 = *(int*)obj2;
        ptr3 = *(int*)((char*)(int)value + 0x10d8);
        *(int*)((char*)ptr3 + 0x10) = value3;
        *(int*)((char*)ptr3 + 0x14) = *(int*)((char*)obj2 + 4);
        ptr4 = *(int*)((char*)(int)value + 0x10d8);
        *(int*)((char*)ptr4 + 0x1c) = *(int*)obj3;
        *(int*)((char*)ptr4 + 0x20) = *(int*)((char*)obj3 + 4);
        ((VObject2*)*(int*)((char*)(int)value + 0x10d8))->Unk_03(0, 0, (int)&v_l16, value2);
        ptr5 = *(int*)((char*)(int)value + 0x10dc);
        *(int*)((char*)ptr5 + 0x10) = *(int*)obj3;
        *(int*)((char*)ptr5 + 0x14) = *(int*)((char*)obj3 + 4);
        ptr6 = *(int*)((char*)(int)value + 0x10dc);
        *(int*)((char*)ptr6 + 0x1c) = *(int*)obj;
        *(int*)((char*)ptr6 + 0x20) = *(int*)((char*)obj + 4);
        ((VObject3*)*(int*)((char*)(int)value + 0x10dc))->Unk_03(0, 0, (int)&v_l16, value2);
    }
    return;
}
