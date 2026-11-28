// 0x00b60920: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00b60110/s00b60110.cpp.

extern "C" unsigned char DAT_01654c10[];
extern "C" int DAT_016c7aa4;
struct C_0083b9d0 { void FUN_0083b9d0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00b5b800(...);
struct C_00f33b50 { int FUN_00f33b50(unsigned int); };

// @ 0x00b60920
extern "C" int __fastcall FUN_00b60920(char* value, int unused, int value2)
{
    int v_l12[3];
    int ptr;
    int ptr2;
    int result;
    ((C_0083b9d0*)((int)value + 16))->FUN_0083b9d0((unsigned int)value2, (unsigned int)*(int*)((char*)(int)value + 4));
    ptr = DAT_016c7aa4;
    *(int*)&v_l12[1] = 0;
    *(int*)&v_l12[2] = 0;
    *(int*)&v_l12[0] = 0;
    ptr2 = *(int*)((char*)ptr + 0x18);
    result = (int)FUN_00b5b800();
    if (result == (int)DAT_01654c10) {
        result = *(int*)((char*)(int)value + 0x80);
        if (((unsigned char)(int)((unsigned int)result >> 6) & 1) != 0) {
            *(int*)&v_l12[0] = 0;
            goto done;
        }
        if (((unsigned char)result & 1) != 0) {
            *(int*)&v_l12[0] = 695925509;
            goto done;
        }
        if (((unsigned char)(int)((unsigned int)result >> 1) & 1) != 0) {
            *(int*)&v_l12[0] = 932831954;
            goto done;
        }
        if (((unsigned char)(int)((unsigned int)result >> 2) & 1) != 0) {
            *(int*)&v_l12[0] = -354780398;
            goto done;
        }
        if (((unsigned char)(int)((unsigned int)result >> 3) & 1) != 0) {
            *(int*)&v_l12[0] = -707873697;
            goto done;
        }
        if (((unsigned char)(int)((unsigned int)result >> 4) & 1) != 0) {
            *(int*)&v_l12[0] = -1205418159;
            goto done;
        }
        result = (unsigned int)result >> 5;
        if (((unsigned char)result & 1) != 0) {
            *(int*)&v_l12[0] = 533679239;
        }
        done:
        if (ptr2 != 0) {
            result = (int)((C_00f33b50*)ptr2)->FUN_00f33b50((unsigned int)(int)&v_l12);
        }
    }
    return result;
}
