// 0x00712320: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsMaterialManager.cpp, match/slices/s00711de0/s00711de0.cpp.

struct C_0070f520 { void FUN_0070f520(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x00712320
extern "C" void __stdcall FUN_00712320(int a4, int a8)
{
    int t1001;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1017;
    int t1024;
    t1001 = (int)((int)0);
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1001)) {
        do {
            t1005 = (int)((int)(a4));
            t1006 = (int)(*(int*)((char*)(t1005) + (t1001)*4));
            if (t1006 != (int)0) {
                goto L712340;
                L712340:;
                t1009 = (int)(t1006);
                t1010 = (int)(*(int*)((char*)(t1009) + 40));
                t1011 = (int)(*(int*)((char*)(t1009) + 36));
                t1006 = (int)(*(int*)((char*)(t1006) + 76));
                t1012 = (int)(t1009 + (int)36);
                t1013 = (int)(t1012);
                ((C_0070f520*)(t1013))->FUN_0070f520((unsigned int)(t1011), (unsigned int)(t1010));
                t1017 = (int)(*(int*)((char*)(t1012)));
                if (t1017 != (int)0) {
                    if (t1017 != (int)*(int*)((char*)(t1012) + 16)) {
                        FUN_00f47380((unsigned int)(t1017));
                    }
                }
                FUN_00f47380((unsigned int)(t1009));
                if (t1006 != (int)0) goto L712340;
            }
            t1024 = (int)((int)(a4));
            *(int*)((char*)(t1024) + (t1001)*4) = (int)((int)0);
            t1001 = (int)(t1001 + (int)1);
        } while ((unsigned int)(t1001) < (unsigned int)((int)(a8)));
    }
    return;
}
