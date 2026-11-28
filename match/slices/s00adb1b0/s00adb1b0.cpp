// 0x00adb1b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00adaad0/s00adaad0.cpp.

struct C_00ad91a0 { int FUN_00ad91a0(unsigned int, unsigned int); };

// @ 0x00adb1b0
extern "C" bool __fastcall FUN_00adb1b0(char* value, int unused, int value2, int obj)
{
    int v_l8[2];
    int value3 = (int)&value2;
    int value4 = (int)&v_l8;
    int ptr = (int)value + 144;
    ((C_00ad91a0*)ptr)->FUN_00ad91a0((unsigned int)value4, (unsigned int)value3);
    int value5 = *(int*)((char*)ptr + 8);
    int ptr2 = *(int*)((char*)ptr + 4);
    int ptr3 = *(int*)&v_l8[0];
    if (ptr3 != *(int*)((char*)ptr2 + value5 * 4)) {
        *(int*)obj = *(int*)((char*)ptr3 + 0x10);
        return (bool)true;
    }
    int value6 = (int)&value2;
    int value7 = (int)&v_l8;
    int ptr4 = (int)value + 176;
    int ptr5 = (int)((C_00ad91a0*)ptr4)->FUN_00ad91a0((unsigned int)value7, (unsigned int)value6);
    int ptr6 = *(int*)ptr5;
    int value8 = *(int*)((char*)ptr5 + 4);
    int value9 = *(int*)((char*)ptr4 + 8);
    *(int*)&v_l8[1] = value8;
    if (ptr6 != *(int*)((char*)*(int*)((char*)ptr4 + 4) + value9 * 4)) {
        *(int*)obj = *(int*)((char*)ptr6 + 0x10);
        return (bool)true;
    }
    *(int*)obj = 0;
    return (bool)false;
}
