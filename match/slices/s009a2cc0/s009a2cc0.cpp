// 0x009a2cc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s009a2c90/s009a2c90.cpp.

extern "C" int DAT_015504e0;
extern "C" int DAT_0166b260;
struct C_009a1770 { void FUN_009a1770(unsigned int); };
extern "C" double __cdecl FUN_009a1d90(unsigned int, float, unsigned int, unsigned int);
extern "C" int __cdecl FUN_009a80e0(...);

// @ 0x009a2cc0
extern "C" bool __cdecl FUN_009a2cc0(int obj, int value)
{
    int ptr = obj + 200;
    *(unsigned char*)((char*)obj + 0xac) = 0;
    ((C_009a1770*)ptr)->FUN_009a1770((unsigned int)0);
    FUN_009a80e0((unsigned int)obj);
    if (*(int*)obj != 0) {
        *(int*)((char*)obj + 0xc) = value;
        *(int*)((char*)obj + 0x10) = DAT_015504e0;
        ++DAT_015504e0;
        *(int*)((char*)*(int*)obj + 0x12c) = DAT_0166b260;
        ++DAT_0166b260;
        *(double*)((char*)obj + 0xb0) = (float)0;
        *(int*)((char*)obj + 0xc0) += 1;
        *(unsigned char*)((char*)obj + 0xac) = 1;
        *(int*)((char*)obj + 0xc4) = 0;
        FUN_009a1d90(obj, (float)0, 1, 1);
        return (bool)1;
    }
    return (bool)false;
}
