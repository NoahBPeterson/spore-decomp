// 0x01139d60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s011399e0/s011399e0.cpp, src/game/plugins/reverbmodel1.cpp.cpp.

extern "C" float DAT_01485720;
extern "C" float DAT_014b3dd0;

// @ 0x01139d60
extern "C" int __fastcall FUN_01139d60(char* value, int unused, int obj)
{
    float f = DAT_014b3dd0;
    if (f > *(float*)((char*)(int)value + 0x28)) {
        *(float*)((char*)(int)value + 0x28) = f;
    }
    float f2 = f / *(float*)((char*)(int)value + 0x28);
    float f3 = DAT_01485720;
    float f4 = f3 - f2;
    *(float*)obj = (f3 - *(float*)((char*)(int)value + 0x1ac)) * f4;
    *(float*)((char*)obj + 4) = (f3 - *(float*)((char*)(int)value + 0x1b0)) * f4;
    *(float*)((char*)obj + 8) = (f3 - *(float*)((char*)(int)value + 0x1b4)) * f4;
    *(float*)((char*)obj + 0xc) = (f3 - *(float*)((char*)(int)value + 0x1b8)) * f4;
    *(float*)((char*)obj + 0x10) = (f3 - *(float*)((char*)(int)value + 0x1bc)) * f4;
    *(float*)((char*)obj + 0x14) = (f3 - *(float*)((char*)(int)value + 0x1c0)) * f4;
    return 1;
}
