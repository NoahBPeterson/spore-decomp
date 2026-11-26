// 0x01192f50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_011b7c70[];
extern "C" unsigned char g_014e6c38[];
extern "C" unsigned char g_016f2124[];
extern "C" int __cdecl FUN_0117db90(...);
extern "C" void __cdecl FUN_0117dd00(...);
extern "C" int __cdecl FUN_01181540(...);
extern "C" int __cdecl FUN_01183410(...);
extern "C" void __cdecl FUN_011835c0(...);
extern "C" void __cdecl FUN_0119f100(...);
extern "C" int __cdecl FUN_011b5540(...);

// @ 0x01192f50
extern "C" void __cdecl FUN_01192f50(void)
{
    int t1015;
    int t1019;
    int t1020;
    int t1023;
    int t1027;
    int t1028;
    FUN_01181540((unsigned int)((int)5), (unsigned int)((int)16), (unsigned int)((int)g_014e6c38), (unsigned int)((int)273));
    if ((int)(*(int*)g_016f2124) == (int)0) {
        FUN_01181540((unsigned int)((int)6), (unsigned int)((int)16), (unsigned int)((int)g_014e6c38), (unsigned int)((int)276));
        FUN_01181540((unsigned int)((int)9), (unsigned int)((int)16), (unsigned int)((int)g_014e6c38), (unsigned int)((int)277));
        if ((int)(*(int*)g_016f2124) == (int)0) {
            FUN_0119f100((unsigned int)((int)3));
            t1015 = (int)FUN_0117db90((unsigned int)((int)g_011b7c70));
            *(int*)g_016f2124 = (int)(t1015);
            if (t1015 != (int)0) {
                t1019 = (int)FUN_01183410((unsigned int)((int)12), (unsigned int)((int)g_014e6c38), (unsigned int)((int)288));
                t1020 = (int)(t1019);
                if (t1020 != (int)0) {
                    t1023 = (int)FUN_011b5540();
                    *(int*)((char*)(t1020) + 8) = (int)(t1023);
                    if (t1023 != (int)0) {
                        if ((int)*(int*)((char*)(t1023)) == (int)0) {
                            FUN_011835c0((unsigned int)(t1020));
                            goto L1193015;
                        }
                    }
                    t1027 = (int)((int)(*(int*)g_016f2124));
                    *(int*)((char*)(t1020)) = (int)((int)1);
                    t1028 = (int)(*(int*)((char*)(t1023) + 4));
                    *(int*)((char*)(t1020) + 4) = (int)(t1028);
                    FUN_0117dd00((unsigned int)(t1027), (unsigned int)(t1020));
                }
                L1193015:;
            }
            FUN_0119f100((unsigned int)((int)2));
        }
        FUN_01181540((unsigned int)((int)10), (unsigned int)((int)16), (unsigned int)((int)g_014e6c38), (unsigned int)((int)308));
        return;
    }
    FUN_01181540((unsigned int)((int)6), (unsigned int)((int)16), (unsigned int)((int)g_014e6c38), (unsigned int)((int)310));
    return;
}
