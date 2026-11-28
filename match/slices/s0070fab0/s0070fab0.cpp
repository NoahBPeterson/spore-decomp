// 0x0070fab0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s0070efa0/s0070efa0.cpp, src/game/SPEngine/SPGraphicsMaterialManager.cpp.

struct C_006fd300 { void FUN_006fd300(); };
extern "C" int __cdecl FUN_0070e390(...);

// @ 0x0070fab0
extern "C" int __fastcall FUN_0070fab0(char* value, int unused, int value2, int value3)
{
    int ptr2;
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_0070e390((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ptr2 = *(int*)cursor;
            if (ptr2 != 0) {
                ((C_006fd300*)ptr2)->FUN_006fd300();
            }
            cursor += 4;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    int value6 = -((value3 - value2) >> 2);
    int value7 = value6 + value6;
    *(int*)((char*)(int)value + 4) += value7 + value7;
    return value2;
}
