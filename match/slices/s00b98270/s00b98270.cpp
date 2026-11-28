// 0x00b98270: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00b981a0/s00b981a0.cpp, src/game/SPGonzago/_at_00b90000.cpp.

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);
struct C_01011cc0 { void FUN_01011cc0(unsigned int); };

// @ 0x00b98270
extern "C" int __fastcall FUN_00b98270(char* value, int unused, int obj)
{
    int value2;
    int ptr2;
    int value3;
    int value4;
    int value5;
    int ptr = *(int*)((char*)(int)value + 0x1c);
    if (ptr != 0) {
        *(int*)((char*)(int)value + 0x1c) = *(int*)ptr;
    } else {
        value2 = *(int*)((char*)(int)value + 0x2c);
        ptr = (int)FUN_00f473a0((unsigned int)value2, (unsigned int)(int)DAT_013f09b4, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
    }
    if (ptr != 0) {
        *(int*)ptr = *(int*)obj;
        *(int*)((char*)ptr + 4) = *(int*)((char*)obj + 4);
        ptr2 = ptr + 8;
        value3 = ptr2 + 24;
        *(int*)ptr2 = value3;
        *(int*)((char*)ptr2 + 4) = value3;
        value4 = obj + 8;
        value5 = value3 + 32;
        *(int*)((char*)ptr2 + 0x14) = 0;
        *(int*)((char*)ptr2 + 8) = value5;
        ((C_01011cc0*)ptr2)->FUN_01011cc0((unsigned int)value4);
    }
    int result = ptr;
    *(int*)((char*)ptr + 0x40) = 0;
    return result;
}
