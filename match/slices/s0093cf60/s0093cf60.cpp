// 0x0093cf60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s0093c950/s0093c950.cpp, src/game/UTFSpore_Win32/EATextEncoding.cpp.

#include <string.h>
extern "C" void __cdecl FUN_0093c950(...);

// @ 0x0093cf60
extern "C" int __cdecl FUN_0093cf60(int obj, int value, int obj2, int value2)
{
    int value3;
    int ptr;
    int value4;
    int ptr2;
    int ptr3;
    int value5;
    int result;
    int value6;
    value3 = value2;
    ptr = obj2;
    value4 = value;
    if (value3 == -1) {
        ptr2 = ptr;
        value3 = (int)strlen((char*)ptr2);
    }
    ptr3 = obj;
    value5 = (int)&value;
    FUN_0093c950((unsigned int)ptr, (unsigned int)value3, (unsigned int)8, (unsigned int)ptr3, (unsigned int)value5, (unsigned int)16);
    result = value;
    if ((unsigned int)value4 > (unsigned int)result) {
        value6 = 0;
        *(unsigned short*)((char*)ptr3 + result * 2) = (unsigned short)value6;
        result = value;
    }
    return result;
}
