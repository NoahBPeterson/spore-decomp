// 0x00ba6b40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00ba6750/s00ba6750.cpp.

struct C_005c65e0 { int FUN_005c65e0(); };
extern "C" double __cdecl FUN_010434c0(...);

// @ 0x00ba6b40
extern "C" int __cdecl FUN_00ba6b40(int obj, int value, int value2, float x)
{
    int ptr;
    int value5;
    int ptr2;
    int value6;
    int value7;
    int index = value;
    int value3 = *(int*)((char*)obj + 4) - *(int*)obj;
    int result = index;
    int value4 = value3 >> 2;
    if (index < value4) {
        do {
            ptr = *(int*)((char*)*(int*)obj + index * 4);
            value5 = (int)((C_005c65e0*)ptr)->FUN_005c65e0();
            if (x >= (float)(double)FUN_010434c0((unsigned int)value2, (unsigned int)value5)) {
                if (result != index) {
                    ptr2 = *(int*)obj;
                    value6 = *(int*)((char*)ptr2 + index * 4);
                    value7 = *(int*)((char*)ptr2 + result * 4);
                    *(int*)((char*)ptr2 + result * 4) = value6;
                    *(int*)((char*)*(int*)obj + index * 4) = value7;
                }
                ++result;
            }
            ++index;
        } while (index < value4);
    }
    return result;
}
