// 0x00e34af0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00e30000.cpp, match/slices/s00e34290/s00e34290.cpp.

struct il2c_bv12 { int d[3]; };
struct VObject {
    virtual void Unk_00();
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
};

extern "C" unsigned char DAT_013f6b3c[];
extern "C" int __stdcall FUN_00401020(unsigned int);
struct C_005f0ca0 { int FUN_005f0ca0(); };
extern "C" int __stdcall FUN_00b3d360(il2c_bv12, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
struct C_00b7d440 { int FUN_00b7d440(); };
struct C_00e34220 { int FUN_00e34220(); };
struct C_00e34540 { int FUN_00e34540(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e34af0
extern "C" void __fastcall FUN_00e34af0(char* value, int unused)
{
    int v_l12[3];
    int v_l24[3];
    int ptr;
    int value4;
    int ptr2;
    int ptr3;
    int ptr4;
    int value2 = (int)&v_l12;
    int value3 = (int)&v_l24;
    *(int*)&v_l24[0] = 0;
    *(int*)&v_l24[1] = 0;
    *(int*)&v_l24[2] = 0;
    *(int*)&v_l12[0] = 0;
    *(int*)&v_l12[1] = 0;
    *(int*)&v_l12[2] = 0;
    ((C_00b7d440*)(int)FUN_00b3d360(*(il2c_bv12*)((int)value + 52), 0, 0, 0, 0, value3, value2))->FUN_00b7d440();
    if (*(int*)&v_l24[0] != 0) {
        if (*(int*)((char*)(int)value + 0x24) != 0) {
            ptr = (int)FUN_00f473a0((unsigned int)404, (unsigned int)(int)DAT_013f6b3c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
            if (ptr != 0) {
                value4 = (int)((C_00e34220*)ptr)->FUN_00e34220();
            } else {
                value4 = 0;
            }
            ptr2 = (int)((C_005f0ca0*)(int)FUN_00401020(value4))->FUN_005f0ca0();
            ptr3 = *(int*)((char*)(int)value + 0x30);
            ptr4 = ptr2;
            if (ptr4 != ptr3) {
                if (ptr4 != 0) {
                    ((VObject*)ptr4)->Unk_00();
                }
                *(int*)((char*)(int)value + 0x30) = ptr4;
                if (ptr3 != 0) {
                    ((VObject2*)ptr3)->Unk_01();
                }
            }
            ((C_00e34540*)*(int*)((char*)(int)value + 0x30))->FUN_00e34540((unsigned int)(int)&v_l24, (unsigned int)(int)&v_l12, (unsigned int)*(int*)((char*)(int)value + 0x24), (unsigned int)*(int*)((char*)(int)value + 0x40), (unsigned int)*(int*)((char*)(int)value + 0x44));
        }
    }
    return;
}
