// 0x00a102e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPAudio/_at_00a10000.cpp, match/slices/s00a102e0/s00a102e0.cpp.

struct C_00a0ff50 { int FUN_00a0ff50(unsigned int); };

// @ 0x00a102e0
extern "C" int __fastcall FUN_00a102e0(char* value, int unused, int value2)
{
    int ptr;
    int value3;
    int value4;
    int value5;
    int value6;
    int value7;
    int value8;
    int value9;
    int value10;
    int value11;
    int value12;
    int ptr2;
    int ptr3;
    int value13;
    int value14;
    int value15;
    int value16;
    int value17;
    int value18;
    int value19;
    int value20;
    int value21;
    int ptr4;
    int ptr5;
    int value22;
    int result;
    int value23;
    int value24;
    int value25;
    int value26;
    int value27;
    int value28;
    int ptr6;
    int ptr7;
    ptr = (int)value;
    value3 = 0;
    if (*(int*)((char*)ptr + 0x38) != value3) {
        value4 = *(int*)((char*)ptr + 0x34);
        if (value4 != value3) {
            *(int*)((char*)ptr + 0x2c) = value4;
            *(int*)((char*)ptr + 0x34) = value3;
            *(int*)((char*)ptr + 0x38) = value3;
            *(int*)((char*)ptr + 0x3c) = value3;
        }
    }
    value5 = *(int*)ptr;
    value6 = *(int*)((char*)ptr + 0x2c);
    value7 = value5;
    value8 = value7 - value6;
    value9 = value8 + *(int*)((char*)ptr + 0x44);
    *(int*)((char*)ptr + 0x34) = value6;
    if ((unsigned int)value9 < 4) {
        value10 = *(int*)((char*)ptr + 4);
        value11 = value10 - value5;
        value12 = value11 + value11;
        ptr2 = ptr;
        ((C_00a0ff50*)ptr2)->FUN_00a0ff50((unsigned int)value12);
    }
    ptr3 = *(int*)((char*)ptr + 0x2c);
    value13 = value2;
    *(int*)ptr3 = value13;
    *(int*)((char*)ptr + 0x2c) += 4;
    value14 = *(int*)ptr;
    value15 = *(int*)((char*)ptr + 0x2c);
    value16 = value14;
    value17 = value16 - value15;
    value18 = value17 + *(int*)((char*)ptr + 0x44);
    *(int*)((char*)ptr + 0x38) = value15;
    if ((unsigned int)value18 < 4) {
        value19 = *(int*)((char*)ptr + 4);
        value20 = value19 - value14;
        value21 = value20 + value20;
        ptr4 = ptr;
        ((C_00a0ff50*)ptr4)->FUN_00a0ff50((unsigned int)value21);
    }
    ptr5 = *(int*)((char*)ptr + 0x2c);
    *(int*)ptr5 = value3;
    *(int*)((char*)ptr + 0x2c) += 4;
    value22 = *(int*)ptr;
    result = *(int*)((char*)ptr + 0x2c);
    value23 = value22;
    value24 = value23 - result;
    value25 = value24 + *(int*)((char*)ptr + 0x44);
    *(int*)((char*)ptr + 0x3c) = result;
    if ((unsigned int)value25 < 4) {
        value26 = *(int*)((char*)ptr + 4);
        value27 = value26 - value22;
        value28 = value27 + value27;
        ptr6 = ptr;
        result = (int)((C_00a0ff50*)ptr6)->FUN_00a0ff50((unsigned int)value28);
    }
    ptr7 = *(int*)((char*)ptr + 0x2c);
    *(int*)ptr7 = value3;
    *(int*)((char*)ptr + 0x2c) += 4;
    *(int*)((char*)ptr + 0x48) = value3;
    return result;
}
