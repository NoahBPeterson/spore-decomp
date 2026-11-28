// 0x0082b7f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/Spui/SPUISerialization.cpp, match/slices/s0082acb0/s0082acb0.cpp.

struct C_00928ba0 { int FUN_00928ba0(unsigned int); };
struct C_00928d40 { int FUN_00928d40(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x0082b7f0
extern "C" int __fastcall FUN_0082b7f0(char* value, int unused, int value2, int value3)
{
    if ((unsigned int)value3 > 8) {
        return (int)((C_00928d40*)((int)value + 4))->FUN_00928d40((unsigned int)value2, (unsigned int)value3, (unsigned int)0, (unsigned int)1);
    }
    int ptr = (int)value + 4;
    int value4 = *(int*)((char*)ptr + 8);
    int value5 = (value2 + 7) & -8;
    if (value4 - value5 - *(int*)((char*)ptr + 0xc) < 0) {
        if ((unsigned char)(int)((C_00928ba0*)ptr)->FUN_00928ba0((unsigned int)value5) == 0) {
            return 0;
        }
    }
    int result = *(int*)((char*)ptr + 0xc);
    int value6 = result + value5;
    *(int*)((char*)ptr + 0xc) = value6;
    *(int*)((char*)ptr + 0x10) = value6;
    return result;
}
