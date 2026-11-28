// 0x00cb8760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPWeapons.cpp, match/slices/s00cb7e50/s00cb7e50.cpp.

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
};
struct VObject3 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual int Unk_02();
};
struct VObject4 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual int Unk_03(int);
};
struct VObject5 {
    virtual void Unk_00();
};
struct VObject6 {
    virtual void Unk_00();
    virtual void Unk_01();
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
    virtual void Unk_08();
    virtual void Unk_09();
    virtual void Unk_0A();
    virtual void Unk_0B();
    virtual void Unk_0C();
    virtual double Unk_0D();
};
struct VObject8 {
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
    virtual int Unk_0B(float);
};

extern "C" unsigned char DAT_0147515c[];
extern "C" unsigned char DAT_01475964[];
extern "C" unsigned char DAT_0157d350[];
extern "C" unsigned char DAT_0169a410[];
struct C_00b20c60 { int FUN_00b20c60(unsigned int); };
extern "C" int __cdecl FUN_00b3d300(...);
struct C_00bc3130 { void FUN_00bc3130(); };
struct C_00c3f160 { void FUN_00c3f160(unsigned int); };
struct C_00c3f1b0 { void FUN_00c3f1b0(float, float); };
struct C_00c3f2d0 { int FUN_00c3f2d0(unsigned int); };
struct C_00c41d40 { double FUN_00c41d40(unsigned int); };
struct C_00c421b0 { void FUN_00c421b0(unsigned int); };
struct C_00cb54a0 { int FUN_00cb54a0(float); };
extern "C" int __cdecl FUN_00f473a0(...);
extern "C" int __cdecl FUN_01021080(...);
struct C_0104be50 { double FUN_0104be50(float); };

// @ 0x00cb8760
extern "C" void __fastcall FUN_00cb8760(char* value, int unused, int obj, int obj2)
{
    int ptr2;
    int ptr5;
    int value2;
    int ptr6;
    double f;
    int ptr7;
    double f2;
    int ptr8;
    int value3;
    int ptr12;
    int ptr13;
    int ptr14;
    int ptr15;
    int ptr16;
    int ptr17;
    int ptr18;
    int ptr19;
    int ptr20;
    int ptr21;
    int ptr22;
    double f3;
    int ptr23;
    int value8;
    int ptr24;
    int ptr25;
    int ptr26;
    int ptr = *(int*)((char*)(int)value + 0x5e4);
    if (obj2 != ptr) {
        if (obj2 != 0) {
            ((VObject*)obj2)->Unk_18();
        }
        *(int*)((char*)(int)value + 0x5e4) = obj2;
        if (ptr != 0) {
            ptr2 = ptr;
            ((VObject2*)ptr2)->Unk_19();
        }
    }
    *(int*)((char*)(int)value + 0x224) = 4;
    int ptr3 = (int)FUN_00f473a0((unsigned int)72, (unsigned int)(int)DAT_01475964, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    int ptr4 = ptr3;
    if (ptr4 != 0) {
        ptr5 = *(int*)((char*)(int)value + 0x5e0);
        value2 = ((VObject3*)obj2)->Unk_02();
        ptr6 = ptr5;
        f = (double)((C_00c41d40*)ptr6)->FUN_00c41d40((unsigned int)value2);
        ptr7 = ptr5;
        f2 = (double)((C_0104be50*)ptr7)->FUN_0104be50((float)f);
        ptr8 = ptr4;
        value3 = (int)((C_00cb54a0*)ptr8)->FUN_00cb54a0((float)f2);
    } else {
        value3 = 0;
    }
    int ptr9 = (int)value + 52;
    int ptr10 = ptr9;
    ((C_00c421b0*)ptr10)->FUN_00c421b0((unsigned int)value3);
    int value4 = *(int*)obj;
    *(int*)((char*)(int)value + 0x1fc) = value4;
    int value5 = *(int*)((char*)obj + 4);
    *(int*)((char*)(int)value + 0x200) = value5;
    int value6 = *(int*)((char*)obj + 8);
    int ptr11 = (int)value + 1512;
    *(int*)((char*)(int)value + 0x204) = value6;
    ((C_00bc3130*)ptr11)->FUN_00bc3130();
    int value7 = (int)FUN_01021080();
    if (value7 == 0) {
        ptr12 = (int)FUN_00b3d300();
        ptr13 = ptr12;
        ptr14 = (int)((C_00b20c60*)ptr13)->FUN_00b20c60((unsigned int)48704686);
        if (ptr14 != 0) {
            ptr15 = ptr14;
            ptr16 = ((VObject4*)ptr15)->Unk_03(48699994);
            ptr17 = ptr16;
        } else {
            ptr17 = 0;
        }
        ptr18 = *(int*)((char*)(int)value + 0x608);
        if (ptr17 != ptr18) {
            if (ptr17 != 0) {
                ptr19 = ptr17;
                ((VObject5*)ptr19)->Unk_00();
            }
            *(int*)((char*)(int)value + 0x608) = ptr17;
            if (ptr18 != 0) {
                ptr20 = ptr18;
                ((VObject6*)ptr20)->Unk_01();
            }
        }
        ptr21 = *(int*)((char*)(int)value + 0x608);
        ptr22 = ptr9;
        f3 = ((VObject7*)ptr22)->Unk_0D();
        ptr23 = ptr9;
        value8 = ((VObject8*)ptr23)->Unk_0B((float)(f3 * *(float*)DAT_0157d350));
        ptr24 = ptr21;
        ((C_00c3f160*)ptr24)->FUN_00c3f160((unsigned int)value8);
        ptr25 = *(int*)((char*)(int)value + 0x608);
        ((C_00c3f1b0*)ptr25)->FUN_00c3f1b0(*(float*)DAT_0169a410, *(float*)DAT_0147515c);
        ptr26 = *(int*)((char*)(int)value + 0x608);
        value7 = (int)((C_00c3f2d0*)ptr26)->FUN_00c3f2d0((unsigned int)(int)value);
    }
    return;
}
