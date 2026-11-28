// 0x01066780: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPUISpace.cpp, match/slices/s01065c30/s01065c30.cpp.

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
struct VObject2 {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual int Unk_07();
};

struct C_00834a00 { int FUN_00834a00(unsigned int); };
struct C_00834c60 { int FUN_00834c60(unsigned int); };

// @ 0x01066780
extern "C" bool __fastcall FUN_01066780(char* value, int unused, int unused2, int obj)
{
    int ptr;
    int value2;
    int ptr2;
    int ptr3;
    int ptr4;
    int ptr5;
    if (*(int*)((char*)(int)value + 0x258) != 0) {
        ptr = obj;
        value2 = *(int*)((char*)ptr + 8);
        if (value2 == 27) {
            if (*(int*)((char*)ptr + 0xc) != 1) goto done2;
            ptr = ((VObject*)*(int*)((char*)ptr + 0x18))->Unk_07();
            if (ptr == 133018088) {
                ptr2 = *(int*)*(int*)((char*)(int)value + 0x698);
                if (ptr2 == 0) goto done2;
                ((C_00834a00*)ptr2)->FUN_00834a00((unsigned int)0);
                return (bool)true;
            }
            if (ptr == 133018089) {
                ptr3 = *(int*)((char*)*(int*)((char*)(int)value + 0x698) + 4);
                if (ptr3 == 0) goto done2;
                ((C_00834a00*)ptr3)->FUN_00834a00((unsigned int)0);
                return (bool)true;
            }
            if (ptr != 133018090) goto done2;
            ptr = *(int*)((char*)(int)value + 0x698);
            ptr4 = *(int*)((char*)ptr + 8);
            if (ptr4 == 0) goto done2;
            ((C_00834a00*)ptr4)->FUN_00834a00((unsigned int)0);
            return (bool)true;
        }
        if (value2 == 28) {
            if (*(int*)((char*)ptr + 0xc) == 1) {
                ptr = ((VObject2*)*(int*)((char*)ptr + 0x18))->Unk_07();
                if (ptr == 133018088) {
                    ptr5 = *(int*)*(int*)((char*)(int)value + 0x698);
                    goto done;
                }
                if (ptr == 133018089) {
                    ptr5 = *(int*)((char*)*(int*)((char*)(int)value + 0x698) + 4);
                    goto done;
                }
                if (ptr != 133018090) goto done2;
                ptr = *(int*)((char*)(int)value + 0x698);
                ptr5 = *(int*)((char*)ptr + 8);
                done:
                if (ptr5 != 0) {
                    ptr = (int)((C_00834c60*)ptr5)->FUN_00834c60((unsigned int)0);
                }
            }
        }
    }
    done2:
    return (bool)true;
}
