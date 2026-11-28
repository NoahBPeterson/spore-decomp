// 0x00aeef00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00aee680/s00aee680.cpp, src/game/SPGonzago/SPAnimalBehaviorTrees.cpp.

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

struct C_0067dcd0 { int FUN_0067dcd0(); };
struct C_00684610 { int FUN_00684610(unsigned int); };
struct C_00aed580 { int FUN_00aed580(unsigned int, unsigned int); };
struct C_00e39fb0 { int FUN_00e39fb0(unsigned int, unsigned int); };

// @ 0x00aeef00
extern "C" int __fastcall FUN_00aeef00(char* value, int unused, int value2, int value3, int value4)
{
    int v_l12[3];
    int ptr4;
    int index;
    int result = 0;
    int ptr = result;
    *(int*)&v_l12[1] = 89840164;
    *(int*)&v_l12[2] = 89840163;
    *(int*)&v_l12[0] = value2;
    ((VObject*)(int)((C_0067dcd0*)(int)value)->FUN_0067dcd0())->Unk_03((int)&v_l12, (int)&ptr, result, result, result, result);
    int ptr2 = ptr;
    int value5 = (int)&value3;
    int value6 = (int)&value2;
    int ptr3 = ptr2 + 24;
    if (*(int*)(int)((C_00e39fb0*)ptr3)->FUN_00e39fb0((unsigned int)value6, (unsigned int)value5) != ptr2 + 28) {
        ptr4 = (int)((C_00684610*)ptr3)->FUN_00684610((unsigned int)(int)&value3);
        index = *(int*)((char*)ptr4 + 0x3c);
        if (index != *(int*)((char*)ptr4 + 0x40)) {
            do {
                if ((unsigned char)(int)((C_00aed580*)(int)value)->FUN_00aed580((unsigned int)index, (unsigned int)value4) != 0) {
                    ++result;
                }
                index += 196;
            } while (index != *(int*)((char*)ptr4 + 0x40));
        }
        ptr2 = ptr;
    }
    if (ptr2 != 0) {
        ((VObject2*)ptr2)->Unk_01();
    }
    return result;
}
