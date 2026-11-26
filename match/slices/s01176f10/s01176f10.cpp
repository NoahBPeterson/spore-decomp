// 0x01176f10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_014dd6b8[];
extern "C" int __cdecl FUN_011815d0(...);
extern "C" void __cdecl FUN_011835c0(...);
extern "C" void __cdecl FUN_011842c0(...);

// @ 0x01176f10
extern "C" int __cdecl FUN_01176f10(int a4)
{
    int t1001;
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1017;
    int t1018;
    t1001 = (int)((int)(a4));
    if (t1001 == (int)0) {
        t1002 = (int)((int)0);
        return (int)(t1002);
    }
    t1004 = (int)(t1001 + (int)44);
    t1008 = (int)FUN_011815d0((unsigned int)(t1004), (unsigned int)((int)(-1)), (unsigned int)((int)21), (unsigned int)((int)g_014dd6b8), (unsigned int)((int)117));
    if (t1008 <= (int)0) {
        t1009 = (int)(*(int*)((char*)(t1001) + 4));
        if (t1009 != (int)0) {
            t1012 = (int)((int (__cdecl*)(int, int, int, int, int, int))(t1009))((int)(t1001), (int)((int)1), (int)((int)0), (int)((int)0), (int)((int)0), (int)((int)1));
            if (t1012 <= (int)0) goto L1176f80;
        }
        t1013 = (int)(t1001 + (int)56);
        FUN_011842c0((unsigned int)((int)0), (unsigned int)(t1001), (unsigned int)(t1013));
        t1017 = (int)(*(int*)((char*)(t1001)));
        if (t1017 != (int)0) {
            t1018 = (int)(*(int*)((char*)(t1017) + 32));
            if (t1018 != (int)0) {
                ((void (__cdecl*)(int))(t1018))((int)(t1001));
                FUN_011835c0((unsigned int)(t1001));
            }
        }
    }
    t1012 = (int)((int)1);
    L1176f80:;
    return (int)(t1012);
}
