// 0x01200a10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s01200010/s01200010.cpp.

extern "C" void __cdecl FUN_01200f80(...);
struct C_011e2300 { int FUN_011e2300(unsigned int); };

// @ 0x01200a10
extern "C" int __cdecl FUN_01200a10(int obj, int obj2)
{
    int value = *(int*)obj;
    *(int*)((char*)obj + 4) = (int)&FUN_01200f80;
    int ptr = *(int*)((char*)obj2 + 0x78);
    *(int*)obj = (int)((C_011e2300*)ptr)->FUN_011e2300((unsigned int)value);
    int value2 = *(int*)((char*)obj + 8);
    int ptr2 = *(int*)((char*)obj2 + 0x78);
    *(int*)((char*)obj + 8) = (int)((C_011e2300*)ptr2)->FUN_011e2300((unsigned int)value2);
    int value3 = *(int*)((char*)obj + 0xc);
    int ptr3 = *(int*)((char*)obj2 + 0x78);
    *(int*)((char*)obj + 0xc) = (int)((C_011e2300*)ptr3)->FUN_011e2300((unsigned int)value3);
    int value4 = *(int*)((char*)obj + 0x10);
    int ptr4 = *(int*)((char*)obj2 + 0x78);
    *(int*)((char*)obj + 0x10) = (int)((C_011e2300*)ptr4)->FUN_011e2300((unsigned int)value4);
    return 1;
}
