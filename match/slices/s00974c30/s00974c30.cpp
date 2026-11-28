// 0x00974c30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00973dd0/s00973dd0.cpp, src/game/UTFSpore_Win32/Grid.cpp.

struct C_00614950 { int FUN_00614950(unsigned int); };

// @ 0x00974c30
extern "C" int __cdecl FUN_00974c30(int obj, int obj2)
{
    int ptr;
    int ptr2;
    int value = *(int*)obj;
    if (value == *(int*)obj2) {
        ptr = *(int*)((char*)obj + 0xc);
        if (ptr != 0) {
            ptr2 = *(int*)((char*)obj2 + 0xc);
            if (ptr2 != 0) {
                if (value == 2) {
                    return (int)((C_00614950*)ptr)->FUN_00614950((unsigned int)*(int*)ptr2);
                }
            }
        }
    }
    return 0;
}
