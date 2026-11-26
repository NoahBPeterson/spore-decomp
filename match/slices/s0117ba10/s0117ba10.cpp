// 0x0117ba10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_0117cf90[];
extern "C" unsigned char g_01194f80[];
extern "C" unsigned char g_014dfee0[];
extern "C" void __cdecl FUN_0117ddb0(...);
extern "C" void __cdecl FUN_0117e030(...);
extern "C" int __cdecl FUN_011815d0(...);
extern "C" void __cdecl FUN_01181d00(...);
extern "C" int __cdecl FUN_011835c0(...);
extern "C" void __cdecl FUN_011842c0(...);
extern "C" void __cdecl FUN_01193d30(...);
extern "C" void __cdecl FUN_01194300(...);
extern "C" void __cdecl FUN_01194b70(...);
extern "C" void __cdecl FUN_011954f0(...);

// @ 0x0117ba10
extern "C" void __cdecl FUN_0117ba10(int a4)
{
    int t1001;
    int t1002;
    int t1006;
    int t1007;
    int t1014;
    int t1018;
    int t1022;
    int t1026;
    int t1030;
    int t1034;
    int t1038;
    int t1042;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1002 = (int)(t1001 + (int)96);
        t1006 = (int)FUN_011815d0((unsigned int)(t1002), (unsigned int)((int)(-1)), (unsigned int)((int)12), (unsigned int)((int)g_014dfee0), (unsigned int)((int)1518));
        if (t1006 <= (int)0) {
            t1007 = (int)(*(int*)((char*)(t1001) + 240));
            if (t1007 != (int)0) {
                FUN_01194300((unsigned int)(t1007));
            }
            if ((int)*(int*)((char*)(t1001) + 16) != (int)0) {
                FUN_01181d00((unsigned int)(t1001), (unsigned int)((int)0));
            }
            t1014 = (int)(t1001 + (int)128);
            FUN_011842c0((unsigned int)((int)2), (unsigned int)(t1001), (unsigned int)(t1014));
            t1018 = (int)(*(int*)((char*)(t1001) + 16));
            if (t1018 != (int)0) {
                FUN_01193d30((unsigned int)(t1018));
            }
            t1022 = (int)(*(int*)((char*)(t1001) + 12));
            if (t1022 != (int)0) {
                FUN_011954f0((unsigned int)(t1022));
            }
            t1026 = (int)(*(int*)((char*)(t1001) + 4));
            if (t1026 != (int)0) {
                FUN_0117ddb0((unsigned int)(t1026));
            }
            t1030 = (int)(*(int*)((char*)(t1001) + 8));
            if (t1030 != (int)0) {
                FUN_0117ddb0((unsigned int)(t1030));
            }
            t1034 = (int)(*(int*)((char*)(t1001) + 176));
            if (t1034 != (int)0) {
                FUN_01194b70((unsigned int)(t1034));
            }
            t1038 = (int)(*(int*)((char*)(t1001) + 160));
            if (t1038 != (int)0) {
                FUN_0117e030((unsigned int)(t1038), (unsigned int)((int)g_01194f80));
            }
            t1042 = (int)(*(int*)((char*)(t1001) + 148));
            if (t1042 != (int)0) {
                FUN_0117e030((unsigned int)(t1042), (unsigned int)((int)g_0117cf90));
            }
            *(int*)((char*)(t1001) + 152) = (int)((int)0);
            t1006 = (int)FUN_011835c0((unsigned int)(t1001));
        }
    }
    return;
}
