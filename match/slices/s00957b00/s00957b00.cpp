// 0x00957b00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/UTFSpore_Win32/Image.cpp, match/slices/s009579f0/s009579f0.cpp.

extern "C" void __cdecl FUN_013c1110(...);
extern "C" int DAT_0166b130;
extern "C" unsigned char DAT_0166b140[];
extern "C" int DAT_0166b170;
extern "C" int DAT_0166b174;
extern "C" int DAT_0166b178;
extern "C" unsigned char DAT_0166b188[];
struct C_009222a0 { void FUN_009222a0(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_011e07ef(...);

// @ 0x00957b00
extern "C" int __cdecl FUN_00957b00(void)
{
    int result = DAT_0166b130;
    if (result == 0) {
        if ((*(unsigned char*)DAT_0166b188 & 1) == 0) {
            *(int*)DAT_0166b188 = *(int*)DAT_0166b188 | 1;
            ((C_009222a0*)(int)DAT_0166b140)->FUN_009222a0((unsigned int)0, (unsigned int)1);
            DAT_0166b170 = 0;
            DAT_0166b174 = 0;
            DAT_0166b178 = 0;
            FUN_011e07ef((unsigned int)(int)&FUN_013c1110);
        }
        result = (int)DAT_0166b140;
        DAT_0166b130 = result;
    }
    return result;
}
