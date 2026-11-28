// 0x00c301c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureMissions.cpp, match/slices/s00c2f830/s00c2f830.cpp.

struct C_00c0c1a0 { int FUN_00c0c1a0(); };
struct C_00c2fa50 { int FUN_00c2fa50(); };

// @ 0x00c301c0
extern "C" void __fastcall FUN_00c301c0(char* value, int unused, int obj)
{
    *(int*)((char*)(int)value + 0x80) = *(int*)((char*)obj + 0xb28);
    *(int*)((char*)(int)value + 0x84) = *(int*)((char*)obj + 0xb2c);
    *(int*)((char*)(int)value + 0x88) = *(int*)((char*)obj + 0xb30);
    int ptr = (int)((C_00c0c1a0*)obj)->FUN_00c0c1a0();
    if (ptr != 0) {
        *(int*)((char*)(int)value + 0xac) = *(int*)((char*)ptr + 0x3fc);
        *(int*)((char*)(int)value + 0xb0) = *(int*)((char*)ptr + 0x400);
        *(int*)((char*)(int)value + 0xb4) = *(int*)((char*)ptr + 0x404);
        *(int*)((char*)(int)value + 0xb8) = *(int*)((char*)ptr + 0x408);
        *(int*)((char*)(int)value + 0xbc) = *(int*)((char*)ptr + 0x40c);
        *(int*)((char*)(int)value + 0x94) = *(int*)((char*)ptr + 0x418);
        *(int*)((char*)(int)value + 0x98) = *(int*)((char*)ptr + 0x420);
        *(int*)((char*)(int)value + 0xc0) = *(int*)((char*)ptr + 0x330);
        *(unsigned char*)((char*)(int)value + 0xc4) = *(unsigned char*)((char*)ptr + 0x389);
    }
    ((C_00c2fa50*)(int)value)->FUN_00c2fa50();
    return;
}
