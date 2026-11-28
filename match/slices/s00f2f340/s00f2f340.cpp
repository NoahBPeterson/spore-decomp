// 0x00f2f340: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00f2e7d0/s00f2e7d0.cpp.

struct C_00dfce90 { void FUN_00dfce90(); };
extern "C" int __cdecl FUN_00dff2f0(...);

// @ 0x00f2f340
extern "C" int __fastcall FUN_00f2f340(char* value, int unused, int value2, int value3)
{
    int value4 = *(int*)((char*)(int)value + 4);
    int ptr = (int)FUN_00dff2f0((unsigned int)value3, (unsigned int)value4, (unsigned int)value2);
    int value5 = *(int*)((char*)(int)value + 4);
    int cursor = ptr;
    if ((unsigned int)ptr < (unsigned int)value5) {
        do {
            ((C_00dfce90*)(cursor + 8))->FUN_00dfce90();
            cursor += 10216;
        } while ((unsigned int)cursor < (unsigned int)value5);
    }
    *(int*)((char*)(int)value + 4) += (value3 - value2) / -10216 * 10216;
    return value2;
}
