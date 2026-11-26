// 0x0113ef00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/cmn/ssysinit.cpp.cpp, match/slices/s0113ec90/s0113ec90.cpp.

extern "C" unsigned char g_016e61a8[];
extern "C" unsigned char g_016e7c1c[];
extern "C" unsigned char g_016e7c68[];
extern "C" unsigned char g_016e7c6c[];
extern "C" unsigned char g_016e7c70[];
extern "C" unsigned char g_016e7c74[];
extern "C" unsigned char g_016e7c78[];
extern "C" unsigned char g_016e7c7c[];
struct C_0112c850 { void FUN_0112c850(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_011330e0(...);
extern "C" void __cdecl FUN_01133450(...);
extern "C" void __cdecl FUN_01133460(...);
extern "C" void __cdecl FUN_01140870(...);
extern "C" void __cdecl FUN_01142690(...);
extern "C" void __cdecl FUN_01156380(...);

// @ 0x0113ef00
extern "C" int __cdecl FUN_0113ef00(void)
{
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    int t1013;
    int t1020;
    int t1033;
    int t1034;
    int t1038;
    int t1039;
    int t1046;
    t1003 = (int)FUN_011330e0();
    if ((unsigned char)(t1003) == (unsigned char)0) {
        t1004 = (int)((int)(-14));
        return (int)(t1004);
    }
    t1005 = (int)((int)(*(int*)g_016e7c68));
    if (t1005 != (int)0) {
        ((void (__cdecl*)(void))(t1005))();
    }
    t1009 = (int)((int)(*(int*)g_016e7c6c));
    if (t1009 != (int)0) {
        ((void (__cdecl*)(void))(t1009))();
    }
    t1013 = (int)((int)(*(int*)g_016e7c74));
    if (t1013 != (int)0) {
        ((void (__cdecl*)(void))(t1013))();
    }
    FUN_01156380();
    t1020 = (int)((int)(*(int*)g_016e7c70));
    if (t1020 != (int)0) {
        ((void (__cdecl*)(int))(t1020))((int)((int)(-1)));
    }
    FUN_01142690();
    FUN_01140870();
    FUN_01133450();
    t1033 = (int)((int)(*(int*)g_016e7c78));
    t1034 = (int)((int)(*(int*)g_016e61a8));
    ((C_0112c850*)(t1034))->FUN_0112c850((unsigned int)(t1033), (unsigned int)((int)0));
    t1038 = (int)((int)(*(int*)g_016e7c7c));
    t1039 = (int)((int)(*(int*)g_016e61a8));
    ((C_0112c850*)(t1039))->FUN_0112c850((unsigned int)(t1038), (unsigned int)((int)0));
    FUN_01133460();
    *(unsigned char*)g_016e7c1c = (unsigned char)((int)0);
    t1046 = (int)((int)0);
    return (int)(t1046);
}
