// 0x0111cf00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s0111c7f0/s0111c7f0.cpp.

// @ 0x0111cf00
extern "C" int __stdcall FUN_0111cf00(int obj, int obj2, int obj3)
{
    int value;
    int value2;
    int value3;
    int result;
    *(int*)((char*)obj3 + 0x34) = *(int*)((char*)obj2 + 0x34);
    value = *(int*)((char*)obj2 + 0x34);
    value2 = *(int*)((char*)obj + 0x24);
    value3 = *(int*)((char*)obj3 + 0x38);
    result = value3 - value + value2;
    if ((unsigned int)result >= 32) {
        if ((unsigned int)value3 <= 2) {
            if ((unsigned int)result < 256) goto done2;
        }
        if ((unsigned int)value3 < 32) {
            if ((unsigned int)*(int*)((char*)obj2 + 0x38) >= 32) goto done;
        }
        if ((unsigned int)value3 < 256) {
            if ((unsigned int)*(int*)((char*)obj2 + 0x38) >= 256) goto done;
        }
        if ((unsigned int)value3 >= 65536) goto done2;
        if ((unsigned int)*(int*)((char*)obj2 + 0x38) < 65536) goto done2;
        done:
        *(int*)((char*)obj3 + 0x34) = value2;
    }
    done2:
    return result;
}
