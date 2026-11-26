// 0x00714ec0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00713e40/s00713e40.cpp, src/game/SPEngine/_at_00710000.cpp.

extern "C" unsigned char g_013eb8a4[];
extern "C" unsigned char g_013ebb38[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00714ec0
extern "C" int __stdcall FUN_00714ec0(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1006;
    int t1007;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1001 = (int)(t1000 + t1000);
        t1002 = (int)(t1001 + t1001);
        t1006 = (int)FUN_00f473a0((unsigned int)(t1002), (unsigned int)((int)g_013eb8a4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    } else {
        t1006 = (int)((int)0);
    }
    t1007 = (int)((int)(a8));
    t1009 = (int)((int)(a12));
    t1010 = (int)(t1006);
    if (t1007 != t1009) {
        t1011 = (int)(t1007 - t1006);
        do {
            if (t1010 != (int)0) {
                t1014 = (int)(*(int*)((char*)(t1011) + t1010));
                *(int*)((char*)(t1010)) = (int)(t1014);
            }
            t1010 = (int)(t1010 + (int)4);
            t1015 = (int)(t1011 + t1010);
        } while (t1015 != t1009);
    }
    return (int)(t1006);
}
