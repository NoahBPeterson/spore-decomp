// 0x00e693f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00e686c0/s00e686c0.cpp.

extern "C" unsigned char DAT_016b3c04[];
struct C_00b72210 { int FUN_00b72210(unsigned int); };
extern "C" void __cdecl FUN_00e69000(unsigned int, unsigned int, float, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

// @ 0x00e693f0
extern "C" int __cdecl FUN_00e693f0(int unused, int obj, int unused2, float x, int obj2)
{
    int ptr;
    int value;
    int ptr2;
    int index;
    int value2;
    int ptr3;
    int ptr4;
    int value3;
    float f;
    int value4;
    int value5;
    int value6;
    int value7;
    int value8;
    int value9;
    int result;
    ptr = obj;
    value = *(int*)ptr;
    ptr2 = obj2;
    *(int*)ptr2 = value;
    index = 1;
    goto again;
    again:
    value2 = *(int*)((char*)ptr2 + index * 4 - 4);
    ptr3 = *(int*)DAT_016b3c04;
    ptr4 = ptr3 + 28;
    value3 = (int)((C_00b72210*)ptr4)->FUN_00b72210((unsigned int)value2);
    f = x;
    value4 = (int)&obj2;
    value5 = (int)&value6;
    value7 = (int)&obj;
    value8 = value3 + 76;
    obj = 0;
    *(float*)&obj2 = f;
    FUN_00e69000(value3, value8, x, value7, value5, value4, ptr2, index);
    value9 = obj;
    if (value9 != 0) {
        *(int*)((char*)ptr2 + index * 4) = value9;
        index = index + 1;
        if (index < 32) goto again;
    }
    result = index;
    return result;
}
