// 0x00e86880: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00e80000.cpp, match/slices/s00e85dc0/s00e85dc0.cpp.

// @ 0x00e86880
extern "C" int __cdecl FUN_00e86880(int obj, int obj2, float x, int value)
{
    int result;
    int value3;
    int ptr2;
    int value4;
    int ptr = *(int*)((char*)obj + 4);
    int value2 = *(int*)ptr;
    if (value2 == *(int*)((char*)ptr + 0x14)) {
        result = 0;
    } else {
        value3 = *(int*)((char*)ptr + 4);
        if (value2 == value3) {
            ptr2 = *(int*)((char*)ptr + 0x10) * value2 + *(int*)((char*)ptr + 0xc);
            value4 = value2 + 1;
            *(int*)((char*)ptr + 4) = value3 + 1;
        } else {
            ptr2 = *(int*)((char*)ptr + 8);
            *(int*)((char*)ptr + 8) = *(int*)ptr2;
            value4 = value2 + 1;
        }
        *(int*)ptr = value4;
        result = ptr2;
    }
    *(int*)result = *(int*)obj2;
    *(int*)((char*)result + 4) = *(int*)((char*)obj2 + 4);
    *(int*)((char*)result + 8) = *(int*)((char*)obj2 + 8);
    *(float*)((char*)result + 0xc) = x;
    *(int*)((char*)result + 0x14) = 0;
    *(int*)((char*)result + 0x18) = value;
    return result;
}
