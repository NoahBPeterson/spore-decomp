// 0x00a1a500: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPAudio/AudioResponseCurve.cpp, match/slices/s00a196f0/s00a196f0.cpp.

extern "C" void __cdecl FUN_00951bf0(...);
struct C_00a1a2f0 { int FUN_00a1a2f0(unsigned int, unsigned int, unsigned int); };

// @ 0x00a1a500
extern "C" int __fastcall FUN_00a1a500(char* value, int unused, int value2)
{
    int v_l20[5];
    int value3 = *(int*)((char*)(int)value + 4);
    int value4 = *(int*)(int)value;
    int value5 = (value3 - value4) / 20;
    if ((unsigned int)value2 > (unsigned int)value5) {
        *(int*)&v_l20[0] = 0;
        *(int*)&v_l20[1] = 0;
        *(int*)&v_l20[2] = 0;
        *(int*)&v_l20[3] = 0;
        *(int*)&v_l20[4] = 0;
        return (int)((C_00a1a2f0*)(int)value)->FUN_00a1a2f0((unsigned int)value3, (unsigned int)(value2 - value5), (unsigned int)(int)&v_l20);
    }
    int value6 = value4 + ((value2 + (value2 << 2)) << 2);
    FUN_00951bf0((unsigned int)value3, (unsigned int)value3, (unsigned int)value6);
    int result = (value3 - value6) / -20;
    int value7 = result + (result << 2);
    int value8 = value7 + value7;
    *(int*)((char*)(int)value + 4) += value8 + value8;
    return result;
}
