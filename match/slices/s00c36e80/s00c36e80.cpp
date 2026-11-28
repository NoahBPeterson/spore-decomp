// 0x00c36e80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPGameDataUFO.cpp, match/slices/s00c368c0/s00c368c0.cpp.

struct C_00b18460 { int FUN_00b18460(unsigned int); };
struct C_00bfc380 { int FUN_00bfc380(unsigned int); };
struct C_00c41d00 { int FUN_00c41d00(unsigned int); };

// @ 0x00c36e80
extern "C" int __fastcall FUN_00c36e80(char* value, int unused, int value2)
{
    int result;
    if (value2 != -1338788861) {
        result = (int)((C_00b18460*)(int)value)->FUN_00b18460((unsigned int)value2);
        if (result != 0) goto done;
        result = (int)((C_00c41d00*)((int)value + 52))->FUN_00c41d00((unsigned int)value2);
        if (result != 0) goto done;
        return (int)((C_00bfc380*)((int)value + 1288))->FUN_00bfc380((unsigned int)value2);
    }
    result = (int)value;
    done:
    return result;
}
