// 0x00e20780: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00e1fb20/s00e1fb20.cpp, src/game/SPGonzago/_at_00e20000.cpp.

extern "C" unsigned char DAT_013ec468[];
extern "C" unsigned char DAT_01480498[];
struct C_00579a90 { int FUN_00579a90(unsigned int); };

// @ 0x00e20780
extern "C" int __fastcall FUN_00e20780(char* value, int unused)
{
    int ptr = (int)value + 68;
    *(int*)((char*)(int)value + 4) = 0;
    *(int*)(int)value = (int)DAT_01480498;
    *(int*)ptr = 0;
    *(int*)((char*)ptr + 4) = 0;
    *(int*)((char*)ptr + 8) = 0;
    ((C_00579a90*)ptr)->FUN_00579a90((unsigned int)(int)DAT_013ec468);
    int ptr2 = (int)value + 8296;
    *(int*)ptr2 = 0;
    *(int*)((char*)ptr2 + 4) = 0;
    *(int*)((char*)ptr2 + 8) = 0;
    ((C_00579a90*)ptr2)->FUN_00579a90((unsigned int)(int)DAT_013ec468);
    int value2 = -1;
    *(int*)((char*)(int)value + 8) = 0;
    *(int*)((char*)(int)value + 0xc) = 0;
    *(int*)((char*)(int)value + 0x38) = 0;
    *(int*)((char*)(int)value + 0x10) = 0;
    *(int*)((char*)(int)value + 0x14) = 0;
    *(int*)((char*)(int)value + 0x18) = 0;
    *(int*)((char*)(int)value + 0x1c) = 0;
    *(int*)((char*)(int)value + 0x24) = 0;
    *(int*)((char*)(int)value + 0x20) = 0;
    *(int*)((char*)(int)value + 0x30) = 0;
    *(int*)((char*)(int)value + 0x28) = 0;
    *(int*)((char*)(int)value + 0x34) = 0;
    *(int*)((char*)(int)value + 0x54) = 0;
    *(int*)((char*)(int)value + 0x58) = 0;
    *(int*)((char*)(int)value + 0x3c) = 0;
    *(int*)((char*)(int)value + 0x5c) = value2;
    *(int*)((char*)(int)value + 0x60) = value2;
    return (int)value;
}
