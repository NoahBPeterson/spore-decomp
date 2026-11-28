// 0x0113c9d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s0113baf0/s0113baf0.cpp.

extern "C" float DAT_01485720;
extern "C" unsigned char DAT_014c13b8[];

// @ 0x0113c9d0
extern "C" bool __cdecl FUN_0113c9d0(int obj)
{
    if (obj != 0) {
        *(int*)obj = (int)DAT_014c13b8;
    }
    float f = DAT_01485720;
    int ptr = obj + 40;
    *(int*)((char*)obj + 0xc) = ptr;
    *(unsigned char*)((char*)obj + 0x68) = 0;
    *(unsigned char*)((char*)obj + 0x69) = 0;
    *(float*)((char*)obj + 0x64) = f;
    *(float*)ptr = f;
    return (bool)true;
}
