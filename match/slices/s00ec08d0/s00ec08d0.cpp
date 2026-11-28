// 0x00ec08d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00ebfad0/s00ebfad0.cpp.

extern "C" unsigned char DAT_0145f924[];
extern "C" int DAT_0168d824;
struct C_00c047d0 { int FUN_00c047d0(); };
struct C_00d997e0 { void FUN_00d997e0(); };
struct C_00f30bc0 { int FUN_00f30bc0(); };
struct C_00f30cc0 { int FUN_00f30cc0(unsigned int, float, float); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00ec08d0
extern "C" float __cdecl FUN_00ec08d0(int obj, int unused, int unused2, int unused3, int obj2, int obj3)
{
    int value;
    int value2;
    int ptr;
    int ptr2;
    int value3;
    if ((int)((C_00c047d0*)obj)->FUN_00c047d0() != 5) {
        value = (int)((C_00c047d0*)obj)->FUN_00c047d0();
        if (value != 4) goto done;
    }
    if (obj != 0) {
        value2 = obj + 1448;
    } else {
        value2 = 0;
    }
    ptr = DAT_0168d824;
    if (ptr == 0) {
        ptr2 = (int)FUN_00f473a0((unsigned int)36, (unsigned int)(int)DAT_0145f924, (unsigned int)ptr, (unsigned int)ptr, (unsigned int)ptr, (unsigned int)ptr);
        if (ptr2 != 0) {
            ptr = (int)((C_00f30bc0*)ptr2)->FUN_00f30bc0();
        } else {
            ptr = 0;
        }
        DAT_0168d824 = ptr;
    }
    value = (int)((C_00f30cc0*)ptr)->FUN_00f30cc0((unsigned int)value2, (float)0, (float)0);
    value3 = value;
    if (value3 != 0) {
        if (obj2 != 0) {
            ((C_00d997e0*)obj2)->FUN_00d997e0();
        }
        *(unsigned char*)obj3 = 1;
        *(int*)((char*)obj2 + 4) = value3;
        return (float)1;
    }
    done:
    return (float)0;
}
