// 0x00a77020: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/Swarm/_at_00a70000.cpp, match/slices/s00a76cf0/s00a76cf0.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual int Unk_06(int);
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual int Unk_06(int);
};
struct VObject3 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual int Unk_06(int);
};

// @ 0x00a77020
extern "C" int __fastcall FUN_00a77020(char* value, int unused, int obj)
{
    int ptr;
    int ptr2;
    int ptr3;
    float f;
    float f2;
    ptr = *(int*)((char*)(int)value + 0x70);
    if (ptr != 0) {
        if ((unsigned char)((VObject*)ptr)->Unk_06(obj) == 0) goto done;
    }
    ptr2 = *(int*)((char*)(int)value + 0x74);
    if (ptr2 != 0) {
        if ((unsigned char)((VObject2*)ptr2)->Unk_06(obj) == 0) goto done;
    }
    ptr3 = *(int*)((char*)(int)value + 0x78);
    if (ptr3 != 0) {
        if ((unsigned char)((VObject3*)ptr3)->Unk_06(obj) == 0) goto done;
    }
    f = *(float*)obj;
    if (f >= *(float*)((char*)(int)value + 0x18)) {
        if (*(float*)((char*)(int)value + 0x20) > f) {
            f2 = *(float*)((char*)obj + 4);
            if (f2 >= *(float*)((char*)(int)value + 0x1c)) {
                if (*(float*)((char*)(int)value + 0x24) > f2) {
                    return 1;
                }
            }
        }
    }
    done:
    return 0;
}
