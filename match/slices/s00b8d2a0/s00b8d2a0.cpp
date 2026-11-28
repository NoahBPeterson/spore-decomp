// 0x00b8d2a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPPlanetModel.cpp, match/slices/s00b8d190/s00b8d190.cpp.

struct C_00b8c330 { int FUN_00b8c330(unsigned int, unsigned int, unsigned int); };

// @ 0x00b8d2a0
extern "C" bool __fastcall FUN_00b8d2a0(char* value, int unused, int value2, int obj)
{
    int value3;
    if (value2 != 28653541) {
        if (value2 != 71583981) {
            if (value2 != 73394578) goto done;
            *(unsigned char*)((char*)(int)value + 0x78) = 1;
            return (bool)false;
        }
        *(unsigned char*)((char*)(int)value + 0xea) = 1;
        *(unsigned char*)((char*)(int)value + 0x78) = 1;
        done:
        return (bool)false;
    }
    value3 = 0;
    if (obj != 0) {
        value3 = *(int*)((char*)obj + 8);
    }
    ((C_00b8c330*)(int)value)->FUN_00b8c330((unsigned int)0, (unsigned int)1, (unsigned int)value3);
    return (bool)true;
}
