// 0x00c9db70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPTribeTool.cpp, match/slices/s00c9d230/s00c9d230.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual void Unk_07();
    virtual int Unk_08();
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual int Unk_06();
};
struct VObject3 {
    virtual void Unk_00();
    virtual void Unk_01();
};
struct VObject4 {
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
    virtual int Unk_0A(int, int, int);
};
struct VObject5 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual void Unk_07();
    virtual int Unk_08();
};
struct VObject6 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual int Unk_06();
};
struct VObject7 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual void Unk_07();
    virtual int Unk_08();
};
struct VObject8 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual int Unk_06();
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
    virtual int Unk_08();
};
struct VObject10 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual int Unk_06();
};

extern "C" unsigned char DAT_0157c5d0[];
struct C_00692f90 { int FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { int FUN_00693e10(unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00b18600 { int FUN_00b18600(unsigned int); };
struct C_00bfc540 { int FUN_00bfc540(unsigned int); };
struct C_00c88b00 { int FUN_00c88b00(unsigned int); };

// @ 0x00c9db70
extern "C" bool __fastcall FUN_00c9db70(char* value, int unused, int obj)
{
    int v_l2580[645];
    int ptr;
    int value2;
    int value3;
    int ptr2;
    int ptr3;
    unsigned char flag;
    int ptr4;
    int value4;
    int ptr5;
    int value5;
    int ptr6;
    int value6;
    int value7;
    ptr = ((VObject*)obj)->Unk_08();
    value2 = ((VObject2*)ptr)->Unk_06();
    FUN_0093a780((unsigned int)value2, (unsigned int)(int)&value3, (unsigned int)1, (unsigned int)0);
    if ((unsigned char)(int)((C_00b18600*)(int)value)->FUN_00b18600((unsigned int)obj) != 0) {
        if ((unsigned char)(int)((C_00c88b00*)((int)value + 52))->FUN_00c88b00((unsigned int)obj) != 0) {
            if ((unsigned char)(int)((C_00bfc540*)((int)value + 288))->FUN_00bfc540((unsigned int)obj) != 0) {
                ptr2 = *(int*)((char*)(int)value + 0x1f8);
                ptr3 = (int)value + 504;
                if (ptr2 != 0) {
                    *(int*)ptr3 = 0;
                    ((VObject3*)ptr2)->Unk_01();
                }
                if ((unsigned char)((VObject4*)obj)->Unk_0A(1329162854, ptr3, 0) != 0) {
                    flag = 1;
                    goto done;
                }
            }
        }
    }
    flag = 0;
    done:
    ptr4 = ((VObject5*)obj)->Unk_08();
    value4 = ((VObject6*)ptr4)->Unk_06();
    FUN_0093a780((unsigned int)value4, (unsigned int)((int)value + 204), (unsigned int)1, (unsigned int)0);
    ptr5 = ((VObject7*)obj)->Unk_08();
    value5 = ((VObject8*)ptr5)->Unk_06();
    FUN_0093a780((unsigned int)value5, (unsigned int)((int)value + 196), (unsigned int)1, (unsigned int)0);
    ptr6 = ((VObject9*)obj)->Unk_08();
    value6 = ((VObject10*)ptr6)->Unk_06();
    FUN_0093a780((unsigned int)value6, (unsigned int)((int)value + 200), (unsigned int)1, (unsigned int)0);
    value7 = (int)((C_00692f90*)(int)&v_l2580)->FUN_00692f90((unsigned int)(int)value, (unsigned int)(int)DAT_0157c5d0, (unsigned int)27790630);
    if (flag != 0) {
        value7 = (int)((C_00693e10*)(int)&v_l2580)->FUN_00693e10((unsigned int)obj);
        if ((unsigned char)value7 != 0) {
            return (bool)true;
        }
    }
    return (bool)false;
}
