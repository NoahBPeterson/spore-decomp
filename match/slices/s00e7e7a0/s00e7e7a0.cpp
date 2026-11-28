// 0x00e7e7a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00e7dd90/s00e7dd90.cpp, src/game/SPGonzago/SPCellGame.cpp.

extern "C" unsigned char DAT_016b3c04[];
struct C_00b72230 { int FUN_00b72230(unsigned int); };
struct C_00e31100 { int FUN_00e31100(); };
extern "C" void __cdecl FUN_00e7e6c0(float);

// @ 0x00e7e7a0
extern "C" void __cdecl FUN_00e7e7a0(float x)
{
    int ptr5;
    int value5;
    int ptr6;
    int ptr = *(int*)DAT_016b3c04;
    int ptr2 = ptr + 84;
    int value = (int)((C_00e31100*)ptr2)->FUN_00e31100();
    int ptr3 = *(int*)DAT_016b3c04;
    int value2 = value;
    int value3 = (int)&value2;
    int ptr4 = ptr3 + 84;
    int value4 = (int)((C_00b72230*)ptr4)->FUN_00b72230((unsigned int)value3);
    if (value4 != 0) {
        do {
            FUN_00e7e6c0(x);
            ptr5 = *(int*)DAT_016b3c04;
            value5 = (int)&value2;
            ptr6 = ptr5 + 84;
            value4 = (int)((C_00b72230*)ptr6)->FUN_00b72230((unsigned int)value5);
        } while (value4 != 0);
    }
    return;
}
