// 0x00ee7cb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00ee7990/s00ee7990.cpp, src/game/SPEditors/_at_00ee0000.cpp.

extern "C" int __cdecl FUN_00b3d420(...);
struct C_00b8f860 { int FUN_00b8f860(); };
struct C_00b90410 { int FUN_00b90410(unsigned int); };
extern "C" int __cdecl FUN_010212a0(...);

// @ 0x00ee7cb0
extern "C" int __cdecl FUN_00ee7cb0(int value, int obj, int obj2)
{
    int value2;
    int value3;
    int value4;
    int ptr;
    int ptr2;
    int value5;
    int ptr3;
    int value6;
    int index;
    int result;
    int index2;
    int value7;
    int ptr4;
    value2 = value;
    if ((unsigned int)value2 >= 120334374) {
        value = 982246440;
        value3 = value2 + -120334374;
        goto done;
    }
    if ((unsigned int)value2 >= 120334371) {
        value = 43792522;
        value3 = value2 + -120334371;
        goto done;
    }
    value = 1835049420;
    value3 = value2 + -120334368;
    done:
    value4 = value3;
    ptr = (int)FUN_010212a0();
    ptr2 = (int)FUN_00b3d420();
    value5 = *(int*)((char*)ptr + 0xc0) - *(int*)((char*)ptr + 0xbc);
    ptr3 = ptr2;
    value6 = value5 / 12;
    index = 0;
    result = -1;
    if (value6 > 0) {
        index2 = 0;
        do {
            value7 = *(int*)((char*)ptr + 0xbc);
            ptr4 = (int)((C_00b90410*)ptr3)->FUN_00b90410((unsigned int)(value7 + index2));
            if ((int)((C_00b8f860*)ptr4)->FUN_00b8f860() == value) {
                if (*(int*)((char*)*(int*)((char*)ptr + 0xf8) + index * 4) == value4) goto done2;
            }
            ++index;
            index2 += 12;
        } while (index < value6);
        goto done3;
        done2:
        result = index;
        done3:;
    }
    if (obj != 0) {
        *(int*)obj = value;
    }
    if (obj2 != 0) {
        *(int*)obj2 = value4;
    }
    return result;
}
