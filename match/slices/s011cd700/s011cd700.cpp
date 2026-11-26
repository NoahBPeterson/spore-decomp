// 0x011cd700: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_011b7d10[];
extern "C" unsigned char g_011cd6e0[];
extern "C" unsigned char g_011dedb0[];
extern "C" void __cdecl FUN_0117cf90(...);
extern "C" void __cdecl FUN_0117ddb0(...);
extern "C" void __cdecl FUN_0117e030(...);
extern "C" int __cdecl FUN_011835c0(...);
extern "C" void __cdecl FUN_011dedb0(...);

// @ 0x011cd700
extern "C" void __cdecl FUN_011cd700(int a4)
{
    int t1001;
    int t1002;
    int t1009;
    int t1013;
    int t1014;
    int t1015;
    int t1019;
    int t1023;
    int t1027;
    int t1033;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1002 = (int)(*(int*)((char*)(t1001) + 12));
        FUN_0117ddb0((unsigned int)(t1002));
        t1009 = (int)(*(int*)((char*)(t1001) + 16));
        FUN_0117e030((unsigned int)(t1009), (unsigned int)((int)g_011cd6e0));
        t1013 = (int)(*(int*)((char*)(t1001)));
        t1014 = (int)((int)0);
        if ((int)*(int*)((char*)(t1001) + 4) > t1014) {
            do {
                t1015 = (int)(*(int*)((char*)(t1013)));
                if (t1015 != (int)0) {
                    FUN_0117cf90((unsigned int)(t1015));
                }
                t1019 = (int)(*(int*)((char*)(t1013) + 4));
                if (t1019 != (int)0) {
                    FUN_0117e030((unsigned int)(t1019), (unsigned int)((int)g_011dedb0));
                }
                t1023 = (int)(*(int*)((char*)(t1013) + 8));
                if (t1023 != (int)0) {
                    FUN_011dedb0((unsigned int)(t1023));
                }
                t1014 = (int)(t1014 + (int)1);
                t1013 = (int)(t1013 + (int)16);
            } while (t1014 < (int)*(int*)((char*)(t1001) + 4));
        }
        t1027 = (int)(*(int*)((char*)(t1001) + 8));
        if (t1027 != (int)0) {
            FUN_0117e030((unsigned int)(t1027), (unsigned int)((int)g_011b7d10));
        }
        t1033 = (int)(*(int*)((char*)(t1001)));
        FUN_011835c0((unsigned int)(t1033));
        FUN_011835c0((unsigned int)(t1001));
    }
    return;
}
