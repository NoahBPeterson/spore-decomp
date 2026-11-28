// 0x00be0b90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00bdfd30/s00bdfd30.cpp, src/game/SPGonzago/SPCity.cpp.

#include <string.h>
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
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual int Unk_07();
};

extern "C" unsigned char DAT_0156e880[];
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { void FUN_00693e10(unsigned int); };
struct C_00899420 { void FUN_00899420(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00c06c30 { void FUN_00c06c30(unsigned int, unsigned int); };
struct C_00f281f0 { void FUN_00f281f0(unsigned int); };

// @ 0x00be0b90
extern "C" void __cdecl FUN_00be0b90(int obj, int obj2)
{
    int v_l2620[2];
    int v_l2612[8];
    int v_l2580[645];
    int value;
    int value2;
    int ptr;
    int value3;
    int value4;
    int ptr2;
    int value5;
    value = *(int*)((char*)obj2 + 4);
    value2 = *(int*)obj2;
    ((C_00899420*)obj2)->FUN_00899420((unsigned int)value2, (unsigned int)value);
    *(int*)&v_l2620[0] = 0;
    ptr = ((VObject*)obj)->Unk_08();
    value3 = ((VObject2*)ptr)->Unk_06();
    FUN_0093a780((unsigned int)value3, (unsigned int)(int)&v_l2620, (unsigned int)1, (unsigned int)0);
    value4 = *(int*)&v_l2620[0];
    ((C_00f281f0*)obj2)->FUN_00f281f0((unsigned int)value4);
    *(int*)&v_l2620[1] = 0;
    if ((unsigned int)*(int*)&v_l2620[0] > 0) {
        goto again;
        again:
        ((C_00692f90*)(int)&v_l2580)->FUN_00692f90((unsigned int)(int)&v_l2612, (unsigned int)(int)DAT_0156e880, (unsigned int)27790630);
        ((C_00693e10*)(int)&v_l2580)->FUN_00693e10((unsigned int)obj);
        ptr2 = *(int*)((char*)obj2 + 4);
        if ((unsigned int)ptr2 < (unsigned int)*(int*)((char*)obj2 + 8)) {
            *(int*)((char*)obj2 + 4) = ptr2 + 32;
            if (ptr2 == 0) goto done;
            memcpy((void*)ptr2, (void*)(int)&v_l2612, (unsigned int)32);
            goto done;
        }
        ((C_00c06c30*)obj2)->FUN_00c06c30((unsigned int)ptr2, (unsigned int)(int)&v_l2612);
        done:
        value5 = *(int*)&v_l2620[1] + 1;
        *(int*)&v_l2620[1] = value5;
        if ((unsigned int)value5 < (unsigned int)*(int*)&v_l2620[0]) goto again;
    }
    ((VObject3*)obj)->Unk_07();
    return;
}
