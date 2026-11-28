// 0x0094d270: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/UTFSpore_Win32/_at_00940000.cpp, match/slices/s0094cac0/s0094cac0.cpp.

extern "C" unsigned char DAT_0143f9c4[];
struct C_009221b0 { void FUN_009221b0(unsigned int); };
struct C_00922270 { void FUN_00922270(); };
extern "C" int __cdecl FUN_0094c130(...);
extern "C" int __cdecl FUN_0094c190(...);
extern "C" int __cdecl FUN_0094c1b0(...);
struct C_0094cf60 { void FUN_0094cf60(unsigned int, unsigned int, unsigned int); };
struct C_0094d0e0 { int FUN_0094d0e0(unsigned int); };

// @ 0x0094d270
extern "C" int __fastcall FUN_0094d270(char* value, int unused, int value2)
{
    int result;
    if ((unsigned char)(int)FUN_0094c190((unsigned int)value2) != 0) {
        return (int)FUN_0094c130((unsigned int)value2);
    }
    int ptr = (int)value + 40;
    ((C_009221b0*)ptr)->FUN_009221b0((unsigned int)(int)DAT_0143f9c4);
    int ptr2 = (int)((C_0094d0e0*)(int)value)->FUN_0094d0e0((unsigned int)value2);
    if (ptr2 != 0) {
        result = *(int*)ptr2;
        ((C_00922270*)ptr)->FUN_00922270();
        return result;
    }
    int result2 = (int)FUN_0094c1b0((unsigned int)value2, (unsigned int)*(int*)((char*)(int)value + 4));
    if (result2 != -1) {
        ((C_0094cf60*)(int)value)->FUN_0094cf60((unsigned int)value2, (unsigned int)result2, (unsigned int)0);
    }
    ((C_00922270*)ptr)->FUN_00922270();
    return result2;
}
