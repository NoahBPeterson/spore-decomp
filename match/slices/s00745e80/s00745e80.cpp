// 0x00745e80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsModelManager.cpp, match/slices/s00745ac0/s00745ac0.cpp.

extern "C" int __cdecl FUN_00743f60(...);

// @ 0x00745e80
extern "C" void __cdecl FUN_00745e80(int obj, int value, int value2, int value3, int value4, int value5, int value6)
{
    int value7;
    int count;
    value7 = value3;
    count = value7 + value7 + 2;
    if (count < value2) {
        goto again;
        again:
        if (*(float*)((char*)obj + count * 8 - 4) > *(float*)((char*)obj + count * 8 + 4)) {
            --count;
        }
        *(int*)((char*)obj + value7 * 8) = *(int*)((char*)obj + count * 8);
        *(int*)((char*)obj + value7 * 8 + 4) = *(int*)((char*)obj + count * 8 + 4);
        value7 = count;
        count = count + count + 2;
        if (count < value2) goto again;
    }
    if (count == value2) {
        *(int*)((char*)obj + value7 * 8) = *(int*)((char*)obj + count * 8 - 8);
        *(int*)((char*)obj + value7 * 8 + 4) = *(int*)((char*)obj + count * 8 - 4);
        value7 = count + -1;
    }
    FUN_00743f60((unsigned int)obj, (unsigned int)value, (unsigned int)value7, (unsigned int)value4, (unsigned int)value5, (unsigned int)value6);
    return;
}
