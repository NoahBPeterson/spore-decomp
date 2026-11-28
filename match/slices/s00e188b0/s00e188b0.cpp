// 0x00e188b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00e10000.cpp, match/slices/s00e17c10/s00e17c10.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
};
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
};
struct VObject3 {
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
    virtual void Unk_0A();
    virtual void Unk_0B();
    virtual void Unk_0C();
    virtual void Unk_0D();
    virtual void Unk_0E();
    virtual void Unk_0F();
    virtual void Unk_10();
    virtual void Unk_11();
    virtual void Unk_12();
    virtual void Unk_13();
    virtual void Unk_14();
    virtual void Unk_15();
    virtual void Unk_16();
    virtual void Unk_17();
    virtual void Unk_18();
    virtual void Unk_19();
    virtual void Unk_1A();
    virtual void Unk_1B();
    virtual void Unk_1C();
    virtual void Unk_1D();
    virtual void Unk_1E();
    virtual void Unk_1F();
    virtual void Unk_20();
    virtual void Unk_21();
    virtual void Unk_22();
    virtual void Unk_23();
    virtual void Unk_24();
    virtual void Unk_25();
    virtual void Unk_26();
    virtual void Unk_27();
    virtual void Unk_28();
    virtual void Unk_29();
    virtual void Unk_2A();
    virtual void Unk_2B();
    virtual void Unk_2C();
    virtual void Unk_2D();
    virtual void Unk_2E();
    virtual void Unk_2F();
    virtual void Unk_30();
    virtual void Unk_31();
    virtual void Unk_32();
    virtual void Unk_33();
    virtual void Unk_34();
    virtual void Unk_35();
    virtual void Unk_36();
    virtual void Unk_37();
    virtual void Unk_38();
    virtual void Unk_39();
    virtual void Unk_3A();
    virtual void Unk_3B();
    virtual void Unk_3C();
    virtual void Unk_3D();
    virtual void Unk_3E();
    virtual void Unk_3F();
    virtual void Unk_40();
    virtual int Unk_41(int);
};
struct VObject4 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual int Unk_02();
};

extern "C" unsigned char DAT_013f6b3c[];
struct C_00810000 { int FUN_00810000(); };
struct C_00810590 { void FUN_00810590(unsigned int); };
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_008120d0 { int FUN_008120d0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e188b0
extern "C" void __fastcall FUN_00e188b0(char* value, int unused, int value2)
{
    int v_l12[3];
    int ptr2;
    int ptr = (int)FUN_00f473a0((unsigned int)24, (unsigned int)(int)DAT_013f6b3c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (ptr != 0) {
        ptr2 = (int)((C_00810000*)ptr)->FUN_00810000();
    } else {
        ptr2 = 0;
    }
    int ptr3 = *(int*)((char*)(int)value + 0x30);
    if (ptr2 != ptr3) {
        if (ptr2 != 0) {
            ((VObject*)ptr2)->Unk_01();
        }
        *(int*)((char*)(int)value + 0x30) = ptr2;
        if (ptr3 != 0) {
            ((VObject2*)ptr3)->Unk_02();
        }
    }
    int ptr4 = *(int*)((char*)(int)value + 0x30);
    int value3 = (int)&v_l12;
    *(int*)&v_l12[0] = value2;
    *(int*)&v_l12[1] = 84978011;
    *(int*)&v_l12[2] = 1078345984;
    int value4 = (int)((C_008120d0*)ptr4)->FUN_008120d0((unsigned int)value3, (unsigned int)1, (unsigned int)-1953040299);
    int ptr5 = *(int*)((char*)(int)value + 0x30);
    if ((unsigned char)value4 != 0) {
        ((C_00810590*)ptr5)->FUN_00810590((unsigned int)0);
        ((VObject3*)(int)((C_008105b0*)*(int*)((char*)(int)value + 0x30))->FUN_008105b0((unsigned int)-1, (unsigned int)1))->Unk_41((int)value);
        return;
    }
    if (ptr5 != 0) {
        *(int*)((char*)(int)value + 0x30) = 0;
        value4 = ((VObject4*)ptr5)->Unk_02();
    }
    return;
}
