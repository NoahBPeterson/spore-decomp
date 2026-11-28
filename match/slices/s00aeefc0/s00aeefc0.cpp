// 0x00aeefc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPAnimalBehaviorTrees.cpp, match/slices/s00aee680/s00aee680.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int, int, int, int, int, int);
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
};
struct VObject3 {
    virtual void Unk_00();
    virtual void Unk_01();
};

struct C_0067dcd0 { int FUN_0067dcd0(); };
struct C_00684610 { int FUN_00684610(unsigned int); };
struct C_00aed580 { int FUN_00aed580(unsigned int, unsigned int); };
struct C_00aee290 { void FUN_00aee290(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_00e39fb0 { int FUN_00e39fb0(unsigned int, unsigned int); };

// @ 0x00aeefc0
extern "C" int __fastcall FUN_00aeefc0(char* value, int unused, int obj, int value2, int value3, int value4, int value5, int value6)
{
    int v_l12[3];
    int cursor;
    int ptr;
    int ptr2;
    int value7;
    int value8;
    int ptr3;
    int ptr4;
    int cursor2;
    int result;
    int value9;
    int ptr5;
    cursor = 0;
    ptr = cursor;
    *(int*)&v_l12[1] = 89840164;
    *(int*)&v_l12[2] = 89840163;
    *(int*)&v_l12[0] = value2;
    ((VObject*)(int)((C_0067dcd0*)(int)value)->FUN_0067dcd0())->Unk_03((int)&v_l12, (int)&ptr, cursor, cursor, cursor, cursor);
    ptr2 = ptr;
    value7 = (int)&value3;
    value8 = (int)&value2;
    ptr3 = ptr2 + 24;
    if (*(int*)(int)((C_00e39fb0*)ptr3)->FUN_00e39fb0((unsigned int)value8, (unsigned int)value7) != ptr2 + 28) {
        ptr4 = (int)((C_00684610*)ptr3)->FUN_00684610((unsigned int)(int)&value3);
        cursor2 = *(int*)((char*)ptr4 + 0x3c);
        if (cursor2 != *(int*)((char*)ptr4 + 0x40)) {
            do {
                if ((unsigned char)(int)((C_00aed580*)(int)value)->FUN_00aed580((unsigned int)cursor2, (unsigned int)value4) != 0) {
                    if (cursor == value5) goto done;
                    ++cursor;
                }
                cursor2 += 196;
            } while (cursor2 != *(int*)((char*)ptr4 + 0x40));
        }
        ptr2 = ptr;
    }
    result = obj;
    *(int*)((char*)result + 4) = 0;
    *(int*)((char*)result + 8) = 0;
    *(int*)((char*)result + 0xc) = 0;
    if (ptr2 != 0) {
        ((VObject2*)ptr2)->Unk_01();
    }
    again:
    return result;
    done:
    if (value6 != 0) {
        ((C_00aee290*)(int)value)->FUN_00aee290((unsigned int)(cursor2 + 96), (unsigned int)value4, (unsigned int)0, (unsigned int)0, (unsigned int)value6, (unsigned int)0);
    }
    value9 = *(int*)((char*)cursor2 + 0x50);
    result = obj;
    *(int*)result = value9;
    *(int*)((char*)result + 4) = *(int*)((char*)cursor2 + 0x54);
    *(int*)((char*)result + 8) = *(int*)((char*)cursor2 + 0x58);
    *(int*)((char*)result + 0xc) = *(int*)((char*)cursor2 + 0x5c);
    ptr5 = ptr;
    if (ptr5 == 0) goto again;
    ((VObject3*)ptr5)->Unk_01();
    return result;
}
