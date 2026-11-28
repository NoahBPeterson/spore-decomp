// 0x009a3890: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s009a2c90/s009a2c90.cpp.

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013f2150[];
struct C_0099c980 { void FUN_0099c980(); };
struct C_009b3450 { void FUN_009b3450(); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x009a3890
extern "C" int __stdcall FUN_009a3890(int obj)
{
    int ptr3;
    int ptr4;
    int result = (int)FUN_00f473a0((unsigned int)28, (unsigned int)(int)DAT_013f2150, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
    int ptr = result;
    int ptr2 = ptr + 16;
    if (ptr2 != 0) {
        ptr3 = *(int*)obj;
        *(int*)ptr2 = ptr3;
        if (ptr3 != 0) {
            ((C_009b3450*)ptr3)->FUN_009b3450();
        }
        *(int*)((char*)ptr2 + 4) = *(int*)((char*)obj + 4);
        ptr4 = *(int*)((char*)obj + 8);
        *(int*)((char*)ptr2 + 8) = ptr4;
        if (ptr4 != 0) {
            ((C_0099c980*)ptr4)->FUN_0099c980();
        }
        result = ptr;
    }
    return result;
}
