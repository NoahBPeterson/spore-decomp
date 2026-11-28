// 0x01133290: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/cmn/_at_01130000.cpp, match/slices/s01132ad0/s01132ad0.cpp.

extern "C" unsigned char g_016e6268[];

// @ 0x01133290
extern "C" int __cdecl FUN_01133290(void)
{
    int t1000;
    int t1004;
    int t1005;
    int t1006;
    t1000 = (int)((int)(*(int*)g_016e6268));
    if (t1000 != (int)0) {
        do {
            t1004 = (int)(*(int*)((char*)(t1000) + 12));
            t1005 = (int)(*(int*)((char*)(t1000) + 8));
            t1006 = (int)(*(int*)((char*)(t1000)));
            ((void (__cdecl*)(int))(t1005))((int)(t1004));
            t1000 = (int)(t1006);
        } while (t1006 != (int)0);
    }
    return (int)(t1000);
}
