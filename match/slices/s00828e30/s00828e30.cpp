// 0x00828e30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00828c30/s00828c30.cpp, src/game/Spui/_at_00820000.cpp.

struct VObject {
    virtual void Unk_00();
};

extern "C" unsigned char DAT_013f6b3c[];
struct C_00828d40 { int FUN_00828d40(unsigned int, unsigned int); };
struct C_0095bb20 { void FUN_0095bb20(); };
struct C_0095bc10 { int FUN_0095bc10(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00828e30
extern "C" int __cdecl FUN_00828e30(int obj, int value, int obj2)
{
    int ptr2;
    ((C_0095bb20*)obj)->FUN_0095bb20();
    int ptr = (int)FUN_00f473a0((unsigned int)24, (unsigned int)(int)DAT_013f6b3c, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (ptr != 0) {
        ptr2 = (int)((C_00828d40*)ptr)->FUN_00828d40((unsigned int)value, (unsigned int)0);
    } else {
        ptr2 = 0;
    }
    *(int*)obj2 = ptr2;
    ((VObject*)ptr2)->Unk_00();
    int value2 = *(int*)((char*)*(int*)obj2 + 0xc);
    *(int*)((char*)*(int*)obj2 + 0x14) = (int)((C_0095bc10*)obj)->FUN_0095bc10((unsigned int)value2);
    return *(int*)((char*)*(int*)obj2 + 0x14);
}
