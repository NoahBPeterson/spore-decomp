// 0x00e94a10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00e93c60/s00e93c60.cpp, src/game/SPGonzago/SPVehicleView.cpp.

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
    virtual int Unk_1F(int, float);
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
    virtual int Unk_1F(int, float);
};

extern "C" unsigned char DAT_01488874[];
extern "C" unsigned char DAT_015a8aac[];
struct C_00e948b0 { void FUN_00e948b0(unsigned int, unsigned int); };
struct C_00e94900 { void FUN_00e94900(unsigned int, unsigned int); };

// @ 0x00e94a10
extern "C" void __fastcall FUN_00e94a10(char* value, int unused, int unused2, float x, float x2, int obj, int obj2)
{
    int value2;
    int value3;
    int value4;
    unsigned char flag;
    unsigned char flag2;
    float f;
    float f2;
    float f3;
    float f4;
    if (obj2 != 0) {
        value2 = *(int*)((char*)obj2 + 4);
        value3 = value2;
        value4 = (unsigned int)value3 >> 14;
        flag = (unsigned char)((unsigned char)value4 & 1);
        if (flag != 0) {
            value2 = (unsigned int)value2 >> 18;
            flag2 = (unsigned char)((unsigned char)value2 & 1);
            if (flag2 == 0) {
                f = x;
                if (f > *(float*)DAT_01488874) {
                    if (*(unsigned char*)(int)value == 0) {
                        ((C_00e948b0*)(int)value)->FUN_00e948b0((unsigned int)obj, (unsigned int)obj2);
                        f = x;
                        *(unsigned char*)(int)value = 1;
                    }
                    f2 = x2 / *(float*)DAT_015a8aac;
                    f3 = f / x2;
                    f4 = f2 * f3;
                    ((VObject*)obj)->Unk_1F(obj2, f4);
                    return;
                }
                if (*(unsigned char*)(int)value != 0) {
                    ((C_00e94900*)(int)value)->FUN_00e94900((unsigned int)obj, (unsigned int)obj2);
                    *(unsigned char*)(int)value = 0;
                    value2 = ((VObject2*)obj)->Unk_1F(obj2, (float)1);
                }
            }
        }
    }
    return;
}
