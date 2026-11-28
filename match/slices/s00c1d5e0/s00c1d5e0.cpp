// 0x00c1d5e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c1c9f0/s00c1c9f0.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual int Unk_04();
};

struct C_00c14e70 { int FUN_00c14e70(unsigned int); };
struct C_00c17350 { void FUN_00c17350(unsigned int, unsigned int); };
struct C_00c1d460 { int FUN_00c1d460(unsigned int, unsigned int); };

// @ 0x00c1d5e0
extern "C" int __fastcall FUN_00c1d5e0(char* value, int unused, int value2, int value3, int value4)
{
    int ptr;
    if ((unsigned char)value2 != 0) {
        ptr = (int)((C_00c14e70*)(int)value)->FUN_00c14e70((unsigned int)value4);
        if (ptr != 0) {
            if ((unsigned char)((VObject*)ptr)->Unk_04() != 0) goto done;
        }
        ((C_00c17350*)(int)value)->FUN_00c17350((unsigned int)value4, (unsigned int)0);
        return (int)((C_00c1d460*)(int)value)->FUN_00c1d460((unsigned int)value3, (unsigned int)value4);
    }
    ((C_00c17350*)(int)value)->FUN_00c17350((unsigned int)value4, (unsigned int)0);
    done:
    return 0;
}
