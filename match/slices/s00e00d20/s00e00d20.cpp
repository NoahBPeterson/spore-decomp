// 0x00e00d20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPUIGlobalUI.cpp, match/slices/s00e00760/s00e00760.cpp.

extern "C" int DAT_015fd918;
extern "C" unsigned char DAT_01654c00[];
extern "C" unsigned char DAT_01654c05[];
struct C_006a25a0 { int FUN_006a25a0(unsigned int); };
struct C_00a98020 { int FUN_00a98020(); };
extern "C" int __cdecl FUN_00b5b800(...);
extern "C" int __cdecl FUN_00e00c40(...);
extern "C" int __cdecl FUN_01015df0(...);

// @ 0x00e00d20
extern "C" bool __cdecl FUN_00e00d20(void)
{
    int value;
    value = (int)FUN_00b5b800();
    if (value != (int)DAT_01654c00) {
        value = (int)FUN_00e00c40();
        if ((unsigned char)value == 0) {
            value = (int)((C_006a25a0*)DAT_015fd918)->FUN_006a25a0((unsigned int)-713458672);
            if ((unsigned char)value == 0) {
                value = (int)FUN_00b5b800();
                if (value == (int)DAT_01654c05) {
                    value = (int)((C_00a98020*)(int)FUN_01015df0())->FUN_00a98020();
                    if ((unsigned char)value != 0) goto done;
                }
            }
            return (bool)true;
        }
    }
    done:
    return (bool)false;
}
