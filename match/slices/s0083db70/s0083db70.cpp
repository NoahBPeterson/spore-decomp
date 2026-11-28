// 0x0083db70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/UTFSpore_Win32/Expression.cpp, match/slices/s0083d3d0/s0083d3d0.cpp.

extern "C" unsigned char DAT_0141b654[];
extern "C" unsigned char DAT_014f9174[];
extern "C" void __cdecl FUN_0052df30(...);
extern "C" void __cdecl FUN_0083ce90(...);
struct C_0083eb00 { int FUN_0083eb00(unsigned int); };
struct C_011e0912 { int FUN_011e0912(unsigned int, unsigned int); };
extern "C" int __stdcall FUN_011e0912(unsigned int, unsigned int);

// @ 0x0083db70
extern "C" int __fastcall FUN_0083db70(char* value, int unused, int obj)
{
    int v_l16[4];
    int ptr2;
    FUN_0083ce90((unsigned int)obj);
    int ptr = *(int*)obj;
    if (*(unsigned char*)ptr != 40) {
        FUN_0052df30((unsigned int)(int)&v_l16, (unsigned int)(int)DAT_0141b654, (unsigned int)40);
        ptr2 = (int)&v_l16;
        ptr = (int)((C_011e0912*)ptr2)->FUN_011e0912((unsigned int)ptr2, (unsigned int)(int)DAT_014f9174);
    }
    *(int*)obj = ptr + 1;
    int result = (int)((C_0083eb00*)(int)value)->FUN_0083eb00((unsigned int)obj);
    FUN_0083ce90((unsigned int)obj);
    int ptr3 = *(int*)obj;
    if (*(unsigned char*)ptr3 != 41) {
        FUN_0052df30((unsigned int)(int)&v_l16, (unsigned int)(int)DAT_0141b654, (unsigned int)41);
        ptr3 = (int)FUN_011e0912((int)&v_l16, (int)DAT_014f9174);
    }
    *(int*)obj = ptr3 + 1;
    return result;
}
