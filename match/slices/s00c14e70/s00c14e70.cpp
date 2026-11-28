// 0x00c14e70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c14350/s00c14350.cpp.

struct C_00645ed0 { int FUN_00645ed0(unsigned int, unsigned int); };

// @ 0x00c14e70
extern "C" int __fastcall FUN_00c14e70(char* value, int unused, int value2)
{
    int v_l8[2];
    int value3 = (int)&value2;
    int value4 = (int)&v_l8;
    int ptr = (int)value + 3272;
    ((C_00645ed0*)ptr)->FUN_00645ed0((unsigned int)value4, (unsigned int)value3);
    int value5 = *(int*)((char*)ptr + 8);
    int ptr2 = *(int*)((char*)ptr + 4);
    int ptr3 = *(int*)&v_l8[0];
    if (ptr3 != *(int*)((char*)ptr2 + value5 * 4)) {
        return *(int*)((char*)ptr3 + 4);
    }
    int value6 = (int)&value2;
    int value7 = (int)&v_l8;
    int ptr4 = (int)value + 3432;
    int ptr5 = (int)((C_00645ed0*)ptr4)->FUN_00645ed0((unsigned int)value7, (unsigned int)value6);
    int value8 = *(int*)((char*)ptr5 + 4);
    int ptr6 = *(int*)ptr5;
    int value9 = *(int*)((char*)ptr4 + 8);
    *(int*)&v_l8[1] = value8;
    if (ptr6 != *(int*)((char*)*(int*)((char*)ptr4 + 4) + value9 * 4)) {
        return *(int*)((char*)ptr6 + 4);
    }
    return 0;
}
