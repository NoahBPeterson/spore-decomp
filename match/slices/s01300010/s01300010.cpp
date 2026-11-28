// 0x01300010: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s012f64e0/s012f64e0.cpp.

extern "C" void __cdecl FUN_013c0cc0(...);
extern "C" float DAT_01485720;
extern "C" int DAT_01549840;
extern "C" int DAT_01549844;
extern "C" int DAT_01549848;
extern "C" unsigned char DAT_01549854[];
extern "C" unsigned char DAT_01549934;
extern "C" unsigned char DAT_01549938[];
extern "C" unsigned char DAT_01549bb0;
extern "C" unsigned char DAT_01549bb1;
extern "C" float DAT_01549bb4;
extern "C" unsigned char DAT_01549bb8;
extern "C" unsigned char DAT_01549bb9;
extern "C" unsigned char DAT_01549bba;
struct C_008941d0 { void FUN_008941d0(); };
struct C_0089a570 { void FUN_0089a570(); };
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x01300010
extern "C" void __cdecl FUN_01300010(void)
{
    ((C_0089a570*)(int)DAT_01549854)->FUN_0089a570();
    DAT_01549934 = 1;
    ((C_008941d0*)(int)DAT_01549938)->FUN_008941d0();
    float f = DAT_01485720;
    DAT_01549bb0 = 0;
    DAT_01549bb1 = 1;
    DAT_01549bb4 = f;
    DAT_01549bb8 = 0;
    DAT_01549bb9 = 0;
    DAT_01549bba = 0;
    DAT_01549840 = 0;
    DAT_01549844 = 0;
    DAT_01549848 = 0;
    FUN_011e07ef((unsigned int)(int)&FUN_013c0cc0);
    return;
}
