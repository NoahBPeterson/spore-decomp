// 0x009245b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/UTFSpore_Win32/ealog_imp.cpp, match/slices/s009245b0/s009245b0.cpp.

extern "C" unsigned char DAT_0143de68[];
struct C_009244d0 { int FUN_009244d0(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x009245b0
extern "C" int __fastcall FUN_009245b0(char* value, int unused)
{
    int value2;
    int result;
    int ptr = (int)FUN_00f473a0((unsigned int)2648, (unsigned int)(int)DAT_0143de68, (unsigned int)0, (unsigned int)0, (unsigned int)0, (unsigned int)0);
    if (ptr != 0) {
        value2 = *(int*)((char*)(int)value + 8);
        result = (int)((C_009244d0*)ptr)->FUN_009244d0((unsigned int)value2);
    } else {
        result = 0;
    }
    *(unsigned short*)((char*)result + 0x21c) = *(unsigned short*)((char*)(int)value + 0x21c);
    *(int*)((char*)result + 0x220) = *(int*)((char*)(int)value + 0x220);
    return result;
}
