// 0x00e2feb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/_at_00e20000.cpp, match/slices/s00e2f6e0/s00e2f6e0.cpp.

extern "C" void __cdecl FUN_00f62def(...);
struct C_00594410 { void FUN_00594410(unsigned int); };
struct C_00e2fcb0 { int FUN_00e2fcb0(unsigned int); };

// @ 0x00e2feb0
extern "C" bool __fastcall FUN_00e2feb0(char* value, int unused, int value2, int obj)
{
    int v_l8[2];
    int value3;
    int value4;
    int ptr;
    int ptr2;
    int value5;
    int ptr3;
    int value6;
    int ptr4;
    int cursor;
    if (value2 == (int)&FUN_00f62def) {
        if (*(int*)((char*)obj + 0x10) == 109705754) {
            value3 = *(int*)((char*)obj + 0x18);
            value4 = (int)&v_l8;
            ptr = (int)value + 28;
            ptr2 = ptr;
            value2 = value3;
            ((C_00594410*)ptr2)->FUN_00594410((unsigned int)value4);
            value5 = *(int*)((char*)ptr + 8);
            ptr3 = *(int*)((char*)ptr + 4);
            value6 = *(int*)((char*)ptr3 + value5 * 4);
            ptr4 = *(int*)&v_l8[0];
            if (ptr4 != value6) {
                cursor = *(int*)&v_l8[1];
                do {
                    if (*(int*)ptr4 == value2) {
                        ptr3 = (int)((C_00e2fcb0*)((int)value + -8))->FUN_00e2fcb0((unsigned int)(ptr4 + 4));
                    }
                    ptr4 = *(int*)((char*)ptr4 + 0x14);
                    if (ptr4 == 0) {
                        goto again;
                        again:
                        ptr4 = *(int*)((char*)cursor + 4);
                        cursor += 4;
                        if (ptr4 == 0) goto again;
                    }
                } while (ptr4 != value6);
                return (bool)true;
            }
            return (bool)true;
        }
    }
    return (bool)true;
}
