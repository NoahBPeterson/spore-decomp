// 0x00d705b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureSleep.cpp, match/slices/s00d70080/s00d70080.cpp.

struct C_00c04590 { int FUN_00c04590(); };

// @ 0x00d705b0
extern "C" float __cdecl FUN_00d705b0(int obj)
{
    int ptr4;
    int value;
    int ptr = (int)((C_00c04590*)obj)->FUN_00c04590();
    int ptr2 = ptr + 356;
    int ptr3 = *(int*)ptr2;
    if (ptr3 != 0) {
        ptr4 = *(int*)((char*)ptr3 + 0xb4c);
        if (*(int*)((char*)ptr4 + 0x1d8) == 47731444) {
            value = *(int*)((char*)ptr3 + 0xb58) & 1024;
            if (value != 0) {
                return (float)1;
            }
        }
    }
    return (float)0;
}
