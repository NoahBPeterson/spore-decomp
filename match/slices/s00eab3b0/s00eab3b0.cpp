// 0x00eab3b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPAudioNPCCityMusic.cpp, match/slices/s00eaa9a0/s00eaa9a0.cpp.

extern "C" int __cdecl FUN_00a37290(...);

// @ 0x00eab3b0
extern "C" int __fastcall FUN_00eab3b0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    unsigned char t1005;
    int t1006;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 20));
    if (t1003 != (int)0) {
        t1005 = (unsigned char)((unsigned char)(a4));
        if (t1005 != (unsigned char)*(unsigned char*)((char*)(t1002) + 24)) {
            t1006 = (int)(t1005);
            t1003 = (int)FUN_00a37290((unsigned int)(t1003), (unsigned int)(t1006));
            *(unsigned char*)((char*)(t1002) + 24) = (unsigned char)(t1005);
        }
    }
    return (int)(t1003);
}
