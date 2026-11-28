// 0x0067f710: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/SPCheatManager.cpp, match/slices/s0067eae0/s0067eae0.cpp.

struct C_00690b80 { void FUN_00690b80(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00921580(...);
extern "C" int __cdecl FUN_0093d5d0(...);

// @ 0x0067f710
extern "C" int __fastcall FUN_0067f710(char* value, int unused, int value2, int obj)
{
    int ptr;
    int result;
    int value3;
    int index;
    int ptr2;
    int value4;
    int ptr3;
    int ptr4;
    ptr = *(int*)((char*)(int)value + 0x14);
    result = 0;
    value3 = (int)value + 16;
    index = result;
    if (ptr != value3) {
        ptr2 = obj;
        do {
            value4 = *(int*)((char*)ptr + 0x10);
            if ((unsigned char)(int)FUN_0093d5d0((unsigned int)value4, (unsigned int)value2, (unsigned int)0) != 0) {
                ptr3 = *(int*)((char*)ptr2 + 4);
                ptr4 = *(int*)((char*)ptr + 0x10);
                obj = ptr4;
                if ((unsigned int)ptr3 < (unsigned int)*(int*)((char*)ptr2 + 8)) {
                    *(int*)((char*)ptr2 + 4) = ptr3 + 4;
                    if (ptr3 == 0) goto done;
                    *(int*)ptr3 = ptr4;
                    goto done;
                }
                ((C_00690b80*)ptr2)->FUN_00690b80((unsigned int)ptr3, (unsigned int)(int)&obj);
                done:
                ++index;
            }
            ptr = (int)FUN_00921580((unsigned int)ptr);
        } while (ptr != value3);
        result = index;
    }
    return result;
}
