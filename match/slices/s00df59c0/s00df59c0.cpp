// 0x00df59c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00df5670/s00df5670.cpp.

struct VObject {
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
    virtual void Unk_41(int);
};
struct VObject2 {
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
    virtual int Unk_0D();
};

struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00811ad0 { int FUN_00811ad0(unsigned int); };
struct C_008120d0 { int FUN_008120d0(unsigned int, unsigned int, unsigned int); };
struct C_00b5f950 { void FUN_00b5f950(unsigned int); };
struct C_00df5610 { void FUN_00df5610(float); };

// @ 0x00df59c0
extern "C" bool __fastcall FUN_00df59c0(char* value, int unused, int obj)
{
    int v_l12[3];
    int ptr3;
    int ptr4;
    int ptr5;
    int ptr6;
    int value2 = (int)&v_l12;
    int ptr = (int)value + 84;
    int ptr2 = ptr;
    *(int*)&v_l12[0] = -579956677;
    *(int*)&v_l12[1] = 84978011;
    *(int*)&v_l12[2] = 1078345984;
    int value3 = (int)((C_008120d0*)ptr2)->FUN_008120d0((unsigned int)value2, (unsigned int)1, (unsigned int)95787258);
    if ((unsigned char)value3 != 0) {
        ptr3 = (int)((C_008105b0*)ptr)->FUN_008105b0((unsigned int)70378808, (unsigned int)1);
        if (ptr3 != 0) {
            ((VObject*)ptr3)->Unk_41((int)value);
            ptr4 = (int)((C_008105b0*)ptr)->FUN_008105b0((unsigned int)97947368, (unsigned int)1);
            if (ptr4 != 0) {
                ptr5 = ((VObject2*)ptr4)->Unk_0D();
                *(float*)((char*)(int)value + 0x34) = *(float*)ptr5;
                ptr6 = (int)value + 48;
                *(float*)((char*)(int)value + 0x38) = *(float*)((char*)ptr5 + 4);
                *(float*)((char*)(int)value + 0x3c) = *(float*)((char*)ptr5 + 8);
                *(float*)((char*)(int)value + 0x40) = *(float*)((char*)ptr5 + 0xc);
                ((C_00b5f950*)ptr6)->FUN_00b5f950((unsigned int)ptr4);
                *(float*)((char*)(int)value + 0x44) = (float)0;
                ((C_00df5610*)(int)value)->FUN_00df5610((float)0);
            }
            *(int*)((char*)(int)value + 0x48) = obj;
            *(int*)((char*)(int)value + 0x4c) = *(int*)((char*)obj + 0x58);
            return (bool)true;
        }
        value3 = (int)((C_00811ad0*)ptr)->FUN_00811ad0((unsigned int)1);
    }
    return (bool)false;
}
