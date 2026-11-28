// 0x00d07770: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00d00000.cpp, match/slices/s00d07770/s00d07770.cpp.

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
    virtual void Unk_20(int);
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
    virtual void Unk_20(int);
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
    virtual int Unk_20(int);
};

extern "C" unsigned char DAT_013f01bc[];
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_009399c0(...);
struct C_00b25f40 { int FUN_00b25f40(); };
struct C_00b3d300 { int FUN_00b3d300(unsigned int); };
struct C_00bf0c60 { int FUN_00bf0c60(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x00d07770
extern "C" void __fastcall FUN_00d07770(char* value, int unused)
{
    int v_l64[16];
    int value3;
    int ptr4;
    int value4;
    int value5;
    int ptr5;
    int value6;
    int value7;
    int ptr6;
    int value8;
    int ptr7;
    int ptr8;
    int ptr9;
    int ptr10;
    int ptr11;
    int value2 = *(int*)((char*)*(int*)((char*)(int)value + 8) + 0x84);
    int ptr = (int)((C_00b3d300*)(int)value)->FUN_00b3d300((unsigned int)value2);
    int ptr2 = (int)((C_00b25f40*)ptr)->FUN_00b25f40();
    int ptr3 = ptr2;
    if (ptr3 != 0) {
        value3 = (int)((C_00bf0c60*)ptr3)->FUN_00bf0c60((unsigned int)2, (unsigned int)-1, (unsigned int)0, (unsigned int)0);
        ptr4 = ptr3;
        value4 = value3;
        value5 = (int)((C_00bf0c60*)ptr4)->FUN_00bf0c60((unsigned int)2, (unsigned int)-1, (unsigned int)1, (unsigned int)0);
        ptr5 = ptr3;
        value6 = value5;
        value7 = (int)((C_00bf0c60*)ptr5)->FUN_00bf0c60((unsigned int)2, (unsigned int)-1, (unsigned int)2, (unsigned int)0);
        ptr6 = *(int*)((char*)(int)value + 4);
        value8 = value7;
        ptr7 = (int)((C_008105b0*)ptr6)->FUN_008105b0((unsigned int)103248109, (unsigned int)1);
        if (ptr7 != 0) {
            FUN_009399c0((unsigned int)(int)&v_l64, (unsigned int)(int)DAT_013f01bc, (unsigned int)value4);
            ((VObject*)ptr7)->Unk_20((int)&v_l64);
        }
        ptr8 = *(int*)((char*)(int)value + 4);
        ptr9 = (int)((C_008105b0*)ptr8)->FUN_008105b0((unsigned int)103248110, (unsigned int)1);
        if (ptr9 != 0) {
            FUN_009399c0((unsigned int)(int)&v_l64, (unsigned int)(int)DAT_013f01bc, (unsigned int)value6);
            ((VObject2*)ptr9)->Unk_20((int)&v_l64);
        }
        ptr10 = *(int*)((char*)(int)value + 4);
        ptr2 = (int)((C_008105b0*)ptr10)->FUN_008105b0((unsigned int)103248111, (unsigned int)1);
        ptr11 = ptr2;
        if (ptr11 != 0) {
            FUN_009399c0((unsigned int)(int)&v_l64, (unsigned int)(int)DAT_013f01bc, (unsigned int)value8);
            ptr2 = ((VObject3*)ptr11)->Unk_20((int)&v_l64);
        }
    }
    return;
}
