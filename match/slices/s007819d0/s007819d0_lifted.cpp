// 0x007819d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsShadowWorld.cpp, match/slices/s007819d0/s007819d0.cpp.

extern "C" int __cdecl FUN_00777ae0(...);
struct C_0077f980 { int FUN_0077f980(); };
struct C_00780810 { int FUN_00780810(); };

// @ 0x007819d0
extern "C" void __fastcall FUN_007819d0(char* value, int unused, int value2)
{
    int value3;
    int ptr;
    if (*(int*)((char*)(int)value + 8) == 0) {
        value3 = *(int*)((char*)(int)value + 0x10);
        if (value3 != 0) {
            if (value2 == value3) {
                if (*(unsigned char*)((char*)(int)value + 5) != 0) {
                    if (*(unsigned char*)((char*)(int)value + 4) != 0) {
                        if (*(unsigned char*)((char*)(int)value + 6) != 0) {
                            FUN_00777ae0((unsigned int)522, (unsigned int)0, (unsigned int)0);
                            FUN_00777ae0((unsigned int)523, (unsigned int)0, (unsigned int)0);
                            FUN_00777ae0((unsigned int)547, (unsigned int)((int)value + 60), (unsigned int)1);
                            ptr = (int)value + -8;
                            if (*(unsigned char*)((char*)(int)value + 0x1bc) != 0) {
                                ((C_00780810*)ptr)->FUN_00780810();
                                return;
                            }
                            ((C_0077f980*)ptr)->FUN_0077f980();
                            return;
                        }
                    }
                }
            }
        }
        FUN_00777ae0((unsigned int)547, (unsigned int)0, (unsigned int)0);
    }
    return;
}
