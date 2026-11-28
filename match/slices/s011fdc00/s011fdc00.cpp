// 0x011fdc00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s011fd3a0/s011fd3a0.cpp.

struct C_011fe180 { void FUN_011fe180(unsigned int); };

// @ 0x011fdc00
extern "C" void __fastcall FUN_011fdc00(char* value, int unused, float x)
{
    if (*(float*)((char*)(int)value + 0x44) > (float)0) {
        if (*(float*)((char*)(int)value + 0x20) + x > *(float*)((char*)(int)value + 0x44)) {
            *(float*)((char*)(int)value + 0x44) = (float)0;
        }
    }
    ((C_011fe180*)(int)value)->FUN_011fe180((unsigned int)*(int*)&x);
    return;
}
