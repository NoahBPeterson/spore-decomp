// 0x00e4cfc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00e4c9e0/s00e4c9e0.cpp, src/game/SPGonzago/SPCellData.cpp.

// @ 0x00e4cfc0
extern "C" int __stdcall FUN_00e4cfc0(int obj, int value)
{
    if (obj != 0) {
        if ((unsigned int)value <= 0) {
            return 0;
        }
        *(int*)obj = 1551159691;
        if ((unsigned int)value <= 1) {
            return 1;
        }
        *(int*)((char*)obj + 4) = 75519620;
    }
    return 2;
}
