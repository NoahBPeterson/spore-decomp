// 0x00e53580: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00e52d80/s00e52d80.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual int Unk_03(int);
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
    virtual void Unk_0A(int, int);
};
struct VObject3 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int);
};
struct VObject4 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int);
};
struct VObject5 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03(int);
};
struct VObject6 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05(int, int, int);
};
struct VObject7 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual int Unk_05(int, int, int);
};

extern "C" int DAT_016b3c04;
extern "C" int DAT_016b3c08;
extern "C" int DAT_016b3c0c;
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00883860(...);

// @ 0x00e53580
extern "C" int __cdecl FUN_00e53580(void)
{
    int ptr2;
    int result2;
    int ptr = (int)((C_008105b0*)*(int*)((char*)DAT_016b3c0c + 0x90))->FUN_008105b0((unsigned int)-754595196, (unsigned int)1);
    if (ptr != 0) {
        ptr2 = ((VObject*)ptr)->Unk_03(-1898807686);
    } else {
        ptr2 = 0;
    }
    ((VObject2*)ptr2)->Unk_0A(4, 0);
    ((VObject3*)*(int*)((char*)DAT_016b3c08 + 0x161bc))->Unk_03(0);
    ((VObject4*)*(int*)((char*)DAT_016b3c08 + 0x161b4))->Unk_03(0);
    ((VObject5*)*(int*)((char*)DAT_016b3c08 + 0x161c8))->Unk_03(0);
    int ptr3 = (int)FUN_00883860();
    int result = DAT_016b3c04;
    if ((*(unsigned char*)((char*)result + 0x515c) & 2) != 0) {
        ((VObject6*)ptr3)->Unk_05(59142804, 0, 0);
        result = DAT_016b3c04;
    }
    if ((*(unsigned char*)((char*)result + 0x515c) & 1) != 0) {
        result2 = ((VObject7*)ptr3)->Unk_05(88521656, 0, 0);
        *(int*)((char*)DAT_016b3c04 + 0x515c) = 0;
        return result2;
    }
    *(int*)((char*)result + 0x515c) = 0;
    return result;
}
