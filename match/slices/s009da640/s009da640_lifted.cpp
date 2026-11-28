// 0x009da640: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPCreatureAnim/_at_009d0000.cpp, match/slices/s009da640/s009da640.cpp.

struct C_009d1090 { void FUN_009d1090(unsigned int); };
struct C_009d30b0 { int FUN_009d30b0(); };
struct C_009d84f0 { void FUN_009d84f0(); };
struct C_009da000 { void FUN_009da000(unsigned int); };
struct C_009da5b0 { void FUN_009da5b0(unsigned int); };

// @ 0x009da640
extern "C" void __fastcall FUN_009da640(char* value, int unused, int value2)
{
    int index;
    int count;
    int ptr;
    int value3 = (*(int*)((char*)(int)value + 0x14) - *(int*)((char*)(int)value + 0x10)) / 260;
    if (value3 != 0) {
        index = 0;
        count = value3;
        do {
            ptr = *(int*)((char*)(int)value + 0x10) + index;
            ((C_009da000*)ptr)->FUN_009da000((unsigned int)value2);
            ((C_009da5b0*)ptr)->FUN_009da5b0((unsigned int)value2);
            ((C_009d84f0*)ptr)->FUN_009d84f0();
            ((C_009d1090*)ptr)->FUN_009d1090((unsigned int)((int)value + 36));
            index += 260;
            --count;
        } while (count != 0);
    }
    ((C_009d30b0*)(int)value)->FUN_009d30b0();
    return;
}
