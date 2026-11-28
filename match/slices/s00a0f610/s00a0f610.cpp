// 0x00a0f610: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPCreatureAnim/SPCreatureAnimManager.cpp, match/slices/s00a0f350/s00a0f350.cpp.

extern "C" void __cdecl FUN_00f62add(...);
extern "C" int DAT_0166c084;
extern "C" int __cdecl FUN_009a37a0(...);
extern "C" void __cdecl FUN_009a4020(...);
struct C_009ab540 { int FUN_009ab540(unsigned int, unsigned int); };
struct C_00a08ba0 { int FUN_00a08ba0(); };
struct C_00a0f080 { int FUN_00a0f080(unsigned int); };

// @ 0x00a0f610
extern "C" bool __fastcall FUN_00a0f610(char* value, int unused, int value2, int obj)
{
    int value3;
    int value4;
    int value5;
    int value6;
    value3 = value2;
    if (value3 != (int)&FUN_00f62add) {
        if (value3 != 36510428) goto done;
        *(int*)((char*)(int)value + 0x78) = *(int*)((char*)obj + 8);
        return (bool)false;
    }
    value3 = *(int*)((char*)obj + 8);
    value4 = *(int*)((char*)obj + 0x18);
    if (value3 != 635371794) {
        if (value3 != 1256942534) {
            if (value3 != -300431699) goto done;
            value5 = (int)FUN_009a37a0((unsigned int)value4);
            value6 = value5;
            if (value6 != 0) {
                FUN_009a4020((unsigned int)value6, (unsigned int)-1);
                value5 = (int)((C_009ab540*)DAT_0166c084)->FUN_009ab540((unsigned int)value6, (unsigned int)-1);
            }
            return (bool)true;
        }
        ((C_00a0f080*)((int)value + -4))->FUN_00a0f080((unsigned int)1);
        return (bool)false;
    }
    value3 = (int)((C_00a08ba0*)(int)value)->FUN_00a08ba0();
    done:
    return (bool)false;
}
