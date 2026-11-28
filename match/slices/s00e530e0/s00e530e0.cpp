// 0x00e530e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00e52d80/s00e52d80.cpp.

extern "C" int DAT_016b3c04;
extern "C" int __cdecl FUN_00e4fd30(...);

// @ 0x00e530e0
extern "C" int __cdecl FUN_00e530e0(void)
{
    int v_l16[4];
    int ptr;
    int cursor;
    int value2;
    int value = (int)FUN_00e4fd30((unsigned int)(int)&v_l16);
    int result = 0;
    int index = 0;
    if (value > 0) {
        ptr = DAT_016b3c04;
        cursor = result + 52;
        do {
            if (*(unsigned char*)((char*)(int)&v_l16 + index) != 0) {
                value2 = *(int*)((char*)cursor + *(int*)((char*)ptr + 0x5190));
                if (value2 != 1) {
                    if (value2 != 2) {
                        ++result;
                    }
                }
            }
            ++index;
            cursor += 4;
        } while (index < value);
    }
    return result;
}
