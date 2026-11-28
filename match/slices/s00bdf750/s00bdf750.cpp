// 0x00bdf750: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00bdee20/s00bdee20.cpp, src/game/SPGonzago/SPCity.cpp.

extern "C" int __cdecl FUN_00921580(...);
struct C_00ac4280 { void FUN_00ac4280(unsigned int); };
struct C_00b534c0 { void FUN_00b534c0(unsigned int, unsigned int); };
struct C_00d018d0 { int FUN_00d018d0(unsigned int, unsigned int); };

// @ 0x00bdf750
extern "C" void __fastcall FUN_00bdf750(char* value, int unused, int obj)
{
    int v_l8[2];
    int ptr;
    int ptr2;
    int value2;
    int ptr3;
    int value3;
    int value4;
    ((C_00ac4280*)obj)->FUN_00ac4280((unsigned int)*(int*)((char*)(int)value + 0x5b4));
    ptr = (int)((C_00d018d0*)obj)->FUN_00d018d0((unsigned int)*(int*)obj, (unsigned int)*(int*)((char*)obj + 4));
    ptr2 = *(int*)((char*)(int)value + 0x5a8);
    value2 = (int)value + 1444;
    if (ptr2 != value2) {
        do {
            ptr3 = *(int*)((char*)obj + 4);
            value3 = *(int*)((char*)ptr2 + 0x10);
            value4 = *(int*)((char*)ptr2 + 0x14);
            *(int*)&v_l8[0] = value3;
            *(int*)&v_l8[1] = value4;
            if ((unsigned int)ptr3 < (unsigned int)*(int*)((char*)obj + 8)) {
                *(int*)((char*)obj + 4) = ptr3 + 8;
                if (ptr3 == 0) goto done;
                *(int*)ptr3 = value3;
                *(int*)((char*)ptr3 + 4) = value4;
                goto done;
            }
            ((C_00b534c0*)obj)->FUN_00b534c0((unsigned int)ptr3, (unsigned int)(int)&v_l8);
            done:
            ptr = (int)FUN_00921580((unsigned int)ptr2);
            ptr2 = ptr;
        } while (ptr2 != value2);
    }
    return;
}
