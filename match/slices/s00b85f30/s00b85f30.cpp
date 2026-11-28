// 0x00b85f30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00b85380/s00b85380.cpp, src/game/SPGonzago/SPPlanetModel.cpp.

extern "C" void __cdecl FUN_00720250(...);
struct C_00b84e90 { int FUN_00b84e90(unsigned int, unsigned int, unsigned int); };

// @ 0x00b85f30
extern "C" int __fastcall FUN_00b85f30(char* value, int unused, int value2)
{
    int v_l24[6];
    int value3 = *(int*)((char*)(int)value + 4);
    int value4 = *(int*)(int)value;
    int value5 = (value3 - value4) / 24;
    if ((unsigned int)value2 > (unsigned int)value5) {
        return (int)((C_00b84e90*)(int)value)->FUN_00b84e90((unsigned int)value3, (unsigned int)(value2 - value5), (unsigned int)(int)&v_l24);
    }
    int value6 = value4 + ((value2 + (value2 << 1)) << 3);
    FUN_00720250((unsigned int)value3, (unsigned int)value3, (unsigned int)value6);
    int result = (value3 - value6) / -24;
    int value7 = result + (result << 1);
    int value8 = value7 + value7;
    int value9 = value8 + value8;
    *(int*)((char*)(int)value + 4) += value9 + value9;
    return result;
}
