// 0x00e14c70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPUIMissions.cpp, match/slices/s00e14a30/s00e14a30.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
};

extern "C" unsigned char DAT_013f6b3c[];
struct C_00810000 { int FUN_00810000(); };
struct C_008120d0 { void FUN_008120d0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e14c70
extern "C" int __fastcall FUN_00e14c70(char* value, int unused)
{
    int v_l12[3];
    int ptr;
    int ptr2;
    int ptr3;
    if (*(int*)((char*)(int)value + 0x54) == 0) {
        *(int*)&v_l12[0] = 717448359;
        *(int*)&v_l12[2] = 1078345984;
        *(int*)&v_l12[1] = 84978011;
        ptr = (int)FUN_00f473a0((unsigned int)24, (unsigned int)(int)DAT_013f6b3c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
        if (ptr != 0) {
            ptr2 = (int)((C_00810000*)ptr)->FUN_00810000();
        } else {
            ptr2 = 0;
        }
        ptr3 = *(int*)((char*)(int)value + 0x54);
        if (ptr2 != ptr3) {
            if (ptr2 != 0) {
                ((VObject*)ptr2)->Unk_01();
            }
            *(int*)((char*)(int)value + 0x54) = ptr2;
            if (ptr3 != 0) {
                ((VObject2*)ptr3)->Unk_02();
            }
        }
        ((C_008120d0*)*(int*)((char*)(int)value + 0x54))->FUN_008120d0((unsigned int)(int)&v_l12, (unsigned int)0, (unsigned int)95787258);
    }
    return *(int*)((char*)(int)value + 0x54);
}
