// 0x00c17cc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c17350/s00c17350.cpp.

struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual int Unk_04();
};

struct C_009cab60 { int FUN_009cab60(unsigned int); };
struct C_00c14f70 { int FUN_00c14f70(unsigned int, unsigned int, unsigned int); };
struct C_00c15150 { void FUN_00c15150(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00c17420(...);

// @ 0x00c17cc0
extern "C" int __fastcall FUN_00c17cc0(char* value, int unused, int value2, int value3, int value4, int value5, int value6)
{
    int ptr;
    int ptr2;
    int ptr3;
    int ptr4;
    if ((unsigned char)value2 != 0) {
        ptr = *(int*)((char*)(int)value + 0xb54);
        if (ptr != 0) {
            ptr2 = *(int*)((char*)ptr + 0x17c);
            ptr3 = (int)((C_009cab60*)ptr2)->FUN_009cab60((unsigned int)value5);
            if (ptr3 != 0) {
                ptr4 = *(int*)((char*)ptr3 + 0x8c);
                if (ptr4 != 0) {
                    if ((unsigned char)((VObject*)ptr4)->Unk_04() != 0) goto done;
                }
            }
        }
        ((C_00c15150*)(int)value)->FUN_00c15150((unsigned int)value5, (unsigned int)1);
        if ((int)FUN_00c17420((unsigned int)(int)value, (unsigned int)value3, (unsigned int)(int)&value2, (unsigned int)1) == 0) goto done;
        return (int)((C_00c14f70*)(int)value)->FUN_00c14f70((unsigned int)value2, (unsigned int)value4, (unsigned int)value5);
    }
    ((C_00c15150*)(int)value)->FUN_00c15150((unsigned int)value5, (unsigned int)value6);
    done:
    return 0;
}
