// 0x00e2fda0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00e20000.cpp, match/slices/s00e2f6e0/s00e2f6e0.cpp.

struct VObject {
    virtual void Unk_00();
};
struct VObject2 {
    virtual void Unk_00();
};

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e2fda0
extern "C" int __stdcall FUN_00e2fda0(int obj)
{
    int ptr2;
    int ptr3;
    int result = (int)FUN_00f473a0((unsigned int)24, (unsigned int)(int)DAT_013f09b4, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
    int ptr = result;
    if (ptr != 0) {
        *(int*)ptr = *(int*)obj;
        *(int*)((char*)ptr + 4) = *(int*)((char*)obj + 4);
        ptr2 = *(int*)((char*)obj + 8);
        *(int*)((char*)ptr + 8) = ptr2;
        if (ptr2 != 0) {
            ((VObject*)ptr2)->Unk_00();
        }
        *(unsigned char*)((char*)ptr + 0xc) = *(unsigned char*)((char*)obj + 0xc);
        ptr3 = *(int*)((char*)obj + 0x10);
        *(int*)((char*)ptr + 0x10) = ptr3;
        if (ptr3 != 0) {
            ((VObject2*)ptr3)->Unk_00();
        }
        result = ptr;
    }
    *(int*)((char*)ptr + 0x14) = 0;
    return result;
}
