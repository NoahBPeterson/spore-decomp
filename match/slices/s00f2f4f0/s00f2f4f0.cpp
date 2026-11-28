// 0x00f2f4f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00f2e7d0/s00f2e7d0.cpp.

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

extern "C" unsigned char DAT_015af358[];
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { void FUN_00693e10(unsigned int); };
extern "C" void __cdecl FUN_0093a780(...);
struct C_00dfce40 { void FUN_00dfce40(); };
struct C_00dff130 { void FUN_00dff130(unsigned int); };
struct C_00f2d330 { void FUN_00f2d330(); };
struct C_00f2ef10 { void FUN_00f2ef10(unsigned int); };
struct C_00f2efe0 { void FUN_00f2efe0(unsigned int, unsigned int); };
struct C_00f2f050 { void FUN_00f2f050(unsigned int, unsigned int); };

// @ 0x00f2f4f0
extern "C" void __cdecl FUN_00f2f4f0(int obj, int obj2)
{
    int v_l3912[333];
    int v_l2580[645];
    int value;
    int value2;
    int value3;
    int ptr;
    int value4;
    int index;
    int ptr2;
    value = *(int*)((char*)obj2 + 4);
    value2 = *(int*)obj2;
    ((C_00f2efe0*)obj2)->FUN_00f2efe0((unsigned int)value2, (unsigned int)value);
    value3 = 0;
    ptr = ((VObject*)obj)->Unk_08();
    value4 = ((VObject2*)ptr)->Unk_06();
    FUN_0093a780((unsigned int)value4, (unsigned int)(int)&value3, (unsigned int)1, (unsigned int)0);
    ((C_00f2ef10*)obj2)->FUN_00f2ef10((unsigned int)value3);
    index = 0;
    if ((unsigned int)value3 > (unsigned int)index) {
        do {
            ((C_00f2d330*)(int)&v_l3912)->FUN_00f2d330();
            ((C_00692f90*)(int)&v_l2580)->FUN_00692f90((unsigned int)(int)&v_l3912, (unsigned int)(int)DAT_015af358, (unsigned int)27790630);
            ((C_00693e10*)(int)&v_l2580)->FUN_00693e10((unsigned int)obj);
            ptr2 = *(int*)((char*)obj2 + 4);
            if ((unsigned int)ptr2 < (unsigned int)*(int*)((char*)obj2 + 8)) {
                *(int*)((char*)obj2 + 4) = ptr2 + 1332;
                if (ptr2 == 0) goto done;
                ((C_00dff130*)ptr2)->FUN_00dff130((unsigned int)(int)&v_l3912);
                goto done;
            }
            ((C_00f2f050*)obj2)->FUN_00f2f050((unsigned int)ptr2, (unsigned int)(int)&v_l3912);
            done:
            ((C_00dfce40*)(int)&v_l3912)->FUN_00dfce40();
            ++index;
        } while ((unsigned int)index < (unsigned int)value3);
    }
    ((VObject3*)obj)->Unk_07();
    return;
}
