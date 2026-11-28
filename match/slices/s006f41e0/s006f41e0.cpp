// 0x006f41e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/_at_006f0000.cpp, match/slices/s006f3410/s006f3410.cpp.

extern "C" unsigned char DAT_01619530[];
struct C_007c3c20 { void FUN_007c3c20(unsigned int); };
struct C_007c3c50 { void FUN_007c3c50(unsigned int); };
struct C_007c4be0 { void FUN_007c4be0(unsigned int, unsigned int); };
struct C_007c50b0 { void FUN_007c50b0(unsigned int, unsigned int, unsigned int); };

// @ 0x006f41e0
extern "C" int __fastcall FUN_006f41e0(char* value, int unused, int value2)
{
    int index;
    int cursor;
    int ptr;
    index = 0;
    cursor = (int)value + 436;
    goto again;
    again:
    if (*(int*)cursor >= 0) goto done;
    ++index;
    cursor += 4;
    if ((unsigned int)index < 2) goto again;
    again2:
    return 0;
    done:
    if (index < 0) goto again2;
    ptr = *(int*)((char*)*(int*)((char*)(int)value + 0x138) + index * 4);
    if (*(unsigned short*)((char*)ptr + 8) == 65535) {
        return 0;
    }
    ((C_007c50b0*)*(int*)((char*)(int)value + 0x174))->FUN_007c50b0((unsigned int)value2, (unsigned int)0, (unsigned int)0);
    ((C_007c4be0*)*(int*)((char*)(int)value + 0x174))->FUN_007c4be0((unsigned int)(*(int*)((char*)ptr + 0x4c) + ((int)*(unsigned short*)((char*)ptr + 8) << 3)), (unsigned int)1);
    ((C_007c3c20*)*(int*)((char*)(int)value + 0x174))->FUN_007c3c20((unsigned int)(int)DAT_01619530);
    ((C_007c3c50*)*(int*)((char*)(int)value + 0x174))->FUN_007c3c50((unsigned int)7);
    return *(int*)((char*)(int)value + 0x174);
}
