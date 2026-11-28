// 0x006758a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPAStar.cpp, match/slices/s006755c0/s006755c0.cpp.

extern "C" unsigned char DAT_013eb430[];
extern "C" unsigned char DAT_013ebb38[];
struct C_00675650 { void FUN_00675650(unsigned int); };
struct C_00921440 { void FUN_00921440(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x006758a0
extern "C" int __fastcall FUN_006758a0(char* value, int unused, int obj, int obj2, int unused2)
{
    int v_l8[2];
    int value2;
    int value3;
    unsigned int value4;
    int value5;
    int value6;
    int ptr;
    int ptr2;
    int ptr3;
    int value7;
    int value8;
    int ptr4;
    int value9;
    value2 = *(int*)obj2;
    value3 = *(int*)((char*)(int)value + 8);
    value4 = value2 % (unsigned int)value3;
    value5 = *(int*)((char*)(int)value + 4);
    value6 = value4;
    ptr = value5 + (value6 << 2);
    ptr2 = *(int*)ptr;
    if (ptr2 != 0) {
        do {
            if (value2 == *(int*)ptr2) goto done;
            ptr2 = *(int*)((char*)ptr2 + 4);
        } while (ptr2 != 0);
    }
    ((C_00921440*)((int)value + 16))->FUN_00921440((unsigned int)(int)&v_l8, (unsigned int)value3, (unsigned int)*(int*)((char*)(int)value + 0xc), (unsigned int)1);
    ptr3 = (int)FUN_00f473a0((unsigned int)8, (unsigned int)(int)DAT_013eb430, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
    if (ptr3 != 0) {
        *(int*)ptr3 = *(int*)obj2;
    }
    *(int*)((char*)ptr3 + 4) = 0;
    if ((unsigned char)*(int*)&v_l8[0] != 0) {
        value7 = *(int*)&v_l8[1];
        value6 = value2 % (unsigned int)value7;
        ((C_00675650*)(int)value)->FUN_00675650((unsigned int)value7);
    }
    value8 = *(int*)((char*)(int)value + 4);
    ptr4 = value6 << 2;
    *(int*)((char*)ptr3 + 4) = *(int*)((char*)ptr4 + value8);
    *(int*)((char*)ptr4 + *(int*)((char*)(int)value + 4)) = ptr3;
    *(int*)((char*)(int)value + 0xc) += 1;
    value9 = *(int*)((char*)(int)value + 4) + ptr4;
    *(int*)obj = ptr3;
    *(int*)((char*)obj + 4) = value9;
    *(unsigned char*)((char*)obj + 8) = 1;
    return obj;
    done:
    *(int*)obj = ptr2;
    *(int*)((char*)obj + 4) = ptr;
    *(unsigned char*)((char*)obj + 8) = 0;
    return obj;
}
