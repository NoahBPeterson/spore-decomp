// 0x00746250: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsModelManager.cpp, match/slices/s00745ac0/s00745ac0.cpp.

struct C_0041d8b0 { int FUN_0041d8b0(unsigned int); };
struct C_00743150 { int FUN_00743150(unsigned int, unsigned int); };

// @ 0x00746250
extern "C" int __stdcall FUN_00746250(int value, int value2, int value3)
{
    int result;
    int ptr;
    int index;
    int cursor;
    int ptr2;
    result = value;
    if (result != 0) {
        ptr = result + -8;
    } else {
        ptr = 0;
    }
    if (value3 < 0) {
        return (int)((C_0041d8b0*)(ptr + 216))->FUN_0041d8b0((unsigned int)value2);
    }
    index = 0;
    cursor = ptr + 156;
    again:
    ptr2 = *(int*)cursor;
    if (ptr2 != 0) {
        result = (int)((C_00743150*)ptr2)->FUN_00743150((unsigned int)value3, (unsigned int)value2);
        ++index;
        cursor += 4;
        if (index < 4) goto again;
    }
    return result;
}
