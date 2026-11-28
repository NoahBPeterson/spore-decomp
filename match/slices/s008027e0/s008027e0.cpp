// 0x008027e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s008019f0/s008019f0.cpp, src/game/Spui/SPUICursorManager.cpp.

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
    virtual int Unk_20(int);
};

extern "C" int __cdecl FUN_0067dcf0(...);
struct C_008026e0 { int FUN_008026e0(unsigned int); };

// @ 0x008027e0
extern "C" void __fastcall FUN_008027e0(char* value, int unused)
{
    int value2;
    int ptr;
    int value3;
    if (*(unsigned char*)((char*)(int)value + 0x40) != 0) {
        if (*(int*)((char*)(int)value + 0x58) > 0) {
            value2 = *(int*)((char*)(int)value + 0x3c);
            goto done;
        }
        value2 = *(int*)((char*)(int)value + 0x30);
        if (value2 == 0) {
            if (*(unsigned char*)((char*)(int)value + 0x42) != (unsigned char)value2) {
                value2 = *(int*)((char*)(int)value + 0x2c);
            } else {
                value2 = *(int*)((char*)(int)value + 0x34);
            }
            if (value2 == 0) goto done2;
        }
        done:
        *(int*)((char*)(int)value + 0x38) = value2;
        done2:
        ptr = *(int*)((char*)(int)value + 0x38);
        value3 = 0;
        if (ptr != 0) {
            if (*(int*)((char*)ptr + 0x18) == value3) {
                if (*(int*)ptr == *(int*)((char*)ptr + 4)) goto done3;
                if ((unsigned char)(int)((C_008026e0*)(int)value)->FUN_008026e0((unsigned int)ptr) == 0) goto done3;
            }
            value3 = *(int*)((char*)*(int*)((char*)(int)value + 0x38) + 0x18);
        }
        done3:
        ((VObject*)(int)FUN_0067dcf0())->Unk_20(value3);
    }
    return;
}
