// 0x00d01820: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00d00ee0/s00d00ee0.cpp.

extern "C" unsigned char DAT_013ebb38[];
extern "C" unsigned char DAT_013f09b4[];
struct C_00d01820 { int FUN_00d01820(unsigned int, unsigned int); };
struct C_00e2b7f0 { int FUN_00e2b7f0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00d01820
extern "C" int __fastcall FUN_00d01820(char* value, int unused, int obj, int value2)
{
    int ptr2;
    int ptr3;
    int value4;
    int result = (int)((C_00e2b7f0*)(int)value)->FUN_00e2b7f0((unsigned int)obj, (unsigned int)value2);
    int value3 = *(int*)obj;
    value2 = result;
    if (value3 != 0) {
        *(int*)result = (int)((C_00d01820*)(int)value)->FUN_00d01820((unsigned int)value3, (unsigned int)result);
    }
    int ptr = *(int*)((char*)obj + 4);
    if (ptr != 0) {
        do {
            ptr2 = (int)FUN_00f473a0((unsigned int)24, (unsigned int)(int)DAT_013f09b4, (unsigned int)0, (unsigned int)0, (unsigned int)(int)DAT_013ebb38, (unsigned int)209);
            ptr3 = ptr2 + 16;
            if (ptr3 != 0) {
                *(int*)ptr3 = *(int*)((char*)ptr + 0x10);
                *(int*)((char*)ptr3 + 4) = *(int*)((char*)ptr + 0x14);
            }
            *(int*)ptr2 = 0;
            *(int*)((char*)ptr2 + 4) = 0;
            *(int*)((char*)ptr2 + 8) = result;
            *(unsigned char*)((char*)ptr2 + 0xc) = *(unsigned char*)((char*)ptr + 0xc);
            *(int*)((char*)result + 4) = ptr2;
            value4 = *(int*)ptr;
            if (value4 != 0) {
                *(int*)ptr2 = (int)((C_00d01820*)(int)value)->FUN_00d01820((unsigned int)value4, (unsigned int)ptr2);
            }
            ptr = *(int*)((char*)ptr + 4);
            result = ptr2;
        } while (ptr != 0);
        return value2;
    }
    return result;
}
