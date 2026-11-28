// 0x007a8790: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s007a7d50/s007a7d50.cpp.

struct C_00890560 { void FUN_00890560(); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x007a8790
extern "C" void __fastcall FUN_007a8790(char* value, int unused)
{
    int ptr;
    if (*(unsigned char*)((char*)(int)value + 0xc) != 0) {
        ptr = *(int*)((char*)(int)value + 0x10);
        *(int*)((char*)ptr + 0xa380) = 0;
        *(int*)((char*)ptr + 0xa37c) = 0;
    }
    FUN_00f47380((unsigned int)*(int*)(int)value);
    FUN_00f47380((unsigned int)*(int*)((char*)(int)value + 4));
    int ptr2 = *(int*)((char*)(int)value + 0x10);
    if (ptr2 != 0) {
        ((C_00890560*)(ptr2 + 40960))->FUN_00890560();
        FUN_00f47380((unsigned int)ptr2);
    }
    int ptr3 = *(int*)((char*)(int)value + 0x14);
    if (ptr3 != 0) {
        ((C_00890560*)ptr3)->FUN_00890560();
        FUN_00f47380((unsigned int)ptr3);
    }
    FUN_00f47380((unsigned int)*(int*)((char*)(int)value + 0x18));
    return;
}
