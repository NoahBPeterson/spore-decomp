// 0x00f6bc10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainEditor.cpp, match/slices/s00f6b9a0/s00f6b9a0.cpp.

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
    virtual int Unk_0C();
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
};

extern "C" unsigned char DAT_015b0e48[];
extern "C" int DAT_015b0e4c;
struct C_00f6b7c0 { int FUN_00f6b7c0(); };

// @ 0x00f6bc10
extern "C" void __fastcall FUN_00f6bc10(char* value, int unused)
{
    int ptr = *(int*)((char*)(int)value + 0x74);
    if (ptr != 0) {
        ((VObject*)ptr)->Unk_0D();
        if ((unsigned char)((VObject2*)*(int*)((char*)(int)value + 0x74))->Unk_0C() == 0) {
            ((VObject3*)*(int*)((char*)(int)value + 0x74))->Unk_0F();
        }
    }
    ((C_00f6b7c0*)(int)DAT_015b0e48)->FUN_00f6b7c0();
    *(int*)DAT_015b0e48 = (int)DAT_015b0e48;
    DAT_015b0e4c = (int)DAT_015b0e48;
    *(float*)((char*)(int)value + 0xe0) = (float)0;
    *(float*)((char*)(int)value + 0xe4) = (float)0;
    *(float*)((char*)(int)value + 0xe8) = (float)0;
    *(float*)((char*)(int)value + 0xec) = (float)0;
    *(float*)((char*)(int)value + 0xf0) = (float)0;
    *(float*)((char*)(int)value + 0xf4) = (float)0;
    *(float*)((char*)(int)value + 0xf8) = (float)0;
    *(float*)((char*)(int)value + 0xfc) = (float)0;
    *(float*)((char*)(int)value + 0x100) = (float)0;
    *(float*)((char*)(int)value + 0x104) = (float)0;
    *(float*)((char*)(int)value + 0x108) = (float)0;
    *(float*)((char*)(int)value + 0x10c) = (float)0;
    *(float*)((char*)(int)value + 0x110) = (float)0;
    *(float*)((char*)(int)value + 0x114) = (float)0;
    *(float*)((char*)(int)value + 0x118) = (float)0;
    *(float*)((char*)(int)value + 0x11c) = (float)0;
    *(float*)((char*)(int)value + 0x120) = (float)0;
    *(float*)((char*)(int)value + 0x124) = (float)0;
    *(float*)((char*)(int)value + 0x128) = (float)0;
    *(float*)((char*)(int)value + 0x12c) = (float)0;
    *(float*)((char*)(int)value + 0x130) = (float)0;
    *(float*)((char*)(int)value + 0x134) = (float)0;
    *(float*)((char*)(int)value + 0x138) = (float)0;
    *(float*)((char*)(int)value + 0x13c) = (float)0;
    return;
}
