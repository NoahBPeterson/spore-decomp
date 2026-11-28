// 0x006963d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006960f0/s006960f0.cpp, src/game/SPEngine/SPLocaleManager.cpp.

extern "C" unsigned char g_013eb918[];
extern "C" unsigned char g_013f65b4[];
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x006963d0
extern "C" int __fastcall FUN_006963d0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    unsigned char t5;
    int t1013;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 12));
    t1004 = (int)(*(int*)((char*)(t1002) + 20));
    t1005 = (int)(t1004 - t1003);
    t1006 = (int)(t1005 & (int)(-2));
    if (t1006 > (int)2) {
        if (t1003 != (int)0) {
            if (t1003 != (int)*(int*)((char*)(t1002) + 28)) {
                FUN_00f47380((unsigned int)(t1003));
            }
        }
    }
    t5 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_013f65b4);
    *(int*)((char*)(t1002)) = (int)((int)g_013eb918);
    if (t5 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1002));
    }
    t1013 = (int)(t1002);
    return (int)(t1013);
}
