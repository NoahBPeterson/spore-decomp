// 0x00f4f000: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00f4ef20/s00f4ef20.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual int Unk_07();
};

extern "C" unsigned char DAT_01412ce0[];
extern "C" float DAT_0142eae0;
extern "C" unsigned char DAT_01452788[];
extern "C" unsigned char DAT_01457f80[];
extern "C" unsigned char DAT_0145cd18[];
extern "C" unsigned char DAT_0145cd28[];
extern "C" unsigned char DAT_0145cd3c[];
extern "C" unsigned char DAT_0145cd50[];
extern "C" unsigned char DAT_0145cd70[];
extern "C" unsigned char DAT_0145cd8c[];
extern "C" unsigned char DAT_0145cda0[];
extern "C" unsigned char DAT_0145cdb4[];
extern "C" unsigned char DAT_0145cdc4[];
extern "C" unsigned char DAT_0145cdd4[];
extern "C" unsigned char DAT_0145cde4[];
extern "C" unsigned char DAT_0145cdf4[];
extern "C" unsigned char DAT_0145ce04[];
extern "C" unsigned char DAT_0145ce14[];
extern "C" unsigned char DAT_0145ce24[];
extern "C" unsigned char DAT_0145ce34[];
extern "C" unsigned char DAT_0145ce38[];
extern "C" unsigned char DAT_0145ce44[];
extern "C" unsigned char DAT_0145ce50[];
extern "C" unsigned char DAT_0145ce64[];
extern "C" unsigned char DAT_0145ce7c[];
extern "C" unsigned char DAT_0145ce94[];
extern "C" unsigned char DAT_0145ceac[];
extern "C" unsigned char DAT_0145cec8[];
extern "C" unsigned char DAT_0145cee4[];
extern "C" unsigned char DAT_0145cefc[];
extern "C" unsigned char DAT_0145cf14[];
extern "C" unsigned char DAT_0145cf2c[];
extern "C" unsigned char DAT_0145cf44[];
extern "C" float DAT_01473c70;
extern "C" float DAT_0147b9f0;
extern "C" float DAT_01485720;
extern "C" float DAT_01485ac0;
extern "C" float DAT_0148e7d8;
extern "C" float DAT_0148e7f0;
extern "C" int DAT_016c9050;
extern "C" int DAT_016c9054;
extern "C" float DAT_016c9074;
extern "C" float DAT_016c9078;
extern "C" unsigned char DAT_016c90d8[];
struct C_0067dd50 { int FUN_0067dd50(); };
struct C_007f2500 { void FUN_007f2500(); };
struct C_007f2590 { double FUN_007f2590(unsigned int); };
struct C_007f25c0 { void FUN_007f25c0(unsigned int, float); };

// @ 0x00f4f000
extern "C" void __fastcall FUN_00f4f000(char* value, int unused, float x, float x2, float x3, float x4, float x5)
{
    float f;
    int ptr = ((VObject*)(int)((C_0067dd50*)(int)value)->FUN_0067dd50())->Unk_07();
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cf44, *(float*)((char*)(int)value + 0x2b8));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cf2c, *(float*)((char*)(int)value + 0x2bc));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cf14, *(float*)((char*)(int)value + 0x2c0));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cefc, *(float*)((char*)(int)value + 0x2c4));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cee4, *(float*)((char*)(int)value + 0x2c8));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cec8, DAT_01485ac0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ceac, DAT_01473c70);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce94, DAT_01485ac0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce7c, DAT_0147b9f0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce64, DAT_0142eae0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce50, *(float*)((char*)(int)value + 0x114));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce44, *(float*)((char*)(int)value + 0x2b0) * DAT_0148e7d8);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce38, *(float*)((char*)(int)value + 0x2ac) * DAT_0148e7d8);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_01412ce0, x3);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_01457f80, *(float*)((char*)(int)value + 0x114));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_01452788, *(float*)((char*)(int)value + 0x138) * DAT_0148e7d8);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce34, *(float*)((char*)(int)value + 0x15c) * DAT_0148e7d8);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce24, DAT_016c9074);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce14, DAT_016c9078);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145ce04, (float)0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cdf4, (float)0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cde4, (float)0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cdd4, (float)DAT_016c9050 / (float)*(int*)ptr);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cdc4, (float)-DAT_016c9054 / (float)*(int*)((char*)ptr + 4));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cdb4, x4);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cda0, x);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cd8c, x2);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cd70, *(float*)((char*)(int)value + 0x298) * DAT_0148e7d8);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cd50, *(float*)((char*)(int)value + 0x29c) * DAT_0148e7f0);
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cd3c, *(float*)((char*)(int)value + 0x274));
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cd28, x5);
    if (*(unsigned char*)((char*)(int)value + 0x169) != 0) {
        f = DAT_01485720;
    } else {
        f = (float)0;
    }
    x3 = f;
    ((C_007f25c0*)(int)DAT_016c90d8)->FUN_007f25c0((unsigned int)(int)DAT_0145cd18, x3);
    ((C_007f2500*)(int)DAT_016c90d8)->FUN_007f2500();
    *(float*)((char*)(int)value + 0x2b8) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145cf44);
    *(float*)((char*)(int)value + 0x2bc) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145cf2c);
    *(float*)((char*)(int)value + 0x2c0) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145cf14);
    *(float*)((char*)(int)value + 0x2c4) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145cefc);
    *(float*)((char*)(int)value + 0x2c8) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145cee4);
    *(float*)((char*)(int)value + 0x368) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145cec8);
    *(float*)((char*)(int)value + 0x36c) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145ceac);
    *(float*)((char*)(int)value + 0x374) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145ce94);
    *(float*)((char*)(int)value + 0x378) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145ce7c);
    *(float*)((char*)(int)value + 0x37c) = (float)(double)((C_007f2590*)(int)DAT_016c90d8)->FUN_007f2590((unsigned int)(int)DAT_0145ce64);
    return;
}
