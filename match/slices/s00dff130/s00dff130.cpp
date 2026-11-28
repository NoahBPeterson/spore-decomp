// 0x00dff130: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00dfe460/s00dfe460.cpp.

struct C_00dfb280 { void FUN_00dfb280(unsigned int); };
struct C_00dfeb00 { void FUN_00dfeb00(unsigned int); };

// @ 0x00dff130
extern "C" int __fastcall FUN_00dff130(char* value, int unused, int obj)
{
    ((C_00dfb280*)(int)value)->FUN_00dfb280((unsigned int)obj);
    ((C_00dfb280*)((int)value + 60))->FUN_00dfb280((unsigned int)(obj + 60));
    *(int*)((char*)(int)value + 0x78) = *(int*)((char*)obj + 0x78);
    *(unsigned char*)((char*)(int)value + 0x7c) = *(unsigned char*)((char*)obj + 0x7c);
    *(int*)((char*)(int)value + 0x80) = *(int*)((char*)obj + 0x80);
    int ptr = (int)value + 132;
    int value2 = ptr + 24;
    *(int*)ptr = value2;
    *(int*)((char*)ptr + 4) = value2;
    int value3 = value2 + 1176;
    int value4 = obj + 132;
    *(int*)((char*)ptr + 0x14) = 0;
    *(int*)((char*)ptr + 8) = value3;
    ((C_00dfeb00*)ptr)->FUN_00dfeb00((unsigned int)value4);
    return (int)value;
}
