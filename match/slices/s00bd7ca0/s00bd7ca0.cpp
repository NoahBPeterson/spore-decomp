// 0x00bd7ca0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00bd70b0/s00bd70b0.cpp.

struct C_00ac0320 { int FUN_00ac0320(unsigned int); };
struct C_00b18460 { int FUN_00b18460(unsigned int); };
struct C_00c884f0 { int FUN_00c884f0(unsigned int); };

// @ 0x00bd7ca0
extern "C" int __fastcall FUN_00bd7ca0(char* value, int unused, int value2)
{
    int result;
    if (value2 != -297840274) {
        if (value2 != -291823054) {
            result = (int)((C_00ac0320*)((int)value + 500))->FUN_00ac0320((unsigned int)value2);
            if (result != 0) goto done;
            result = (int)((C_00b18460*)(int)value)->FUN_00b18460((unsigned int)value2);
            if (result != 0) goto done;
            return (int)((C_00c884f0*)((int)value + 288))->FUN_00c884f0((unsigned int)value2);
        }
    }
    result = (int)value;
    done:
    return result;
}
