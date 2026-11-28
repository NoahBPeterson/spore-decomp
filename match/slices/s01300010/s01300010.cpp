// 0x01300010: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s012f64e0/s012f64e0.cpp.

extern "C" void __cdecl FUN_013c0cc0(...);
extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_01549840[];
extern "C" unsigned char g_01549844[];
extern "C" unsigned char g_01549848[];
extern "C" unsigned char g_01549854[];
extern "C" unsigned char g_01549934[];
extern "C" unsigned char g_01549938[];
extern "C" unsigned char g_01549bb0[];
extern "C" unsigned char g_01549bb1[];
extern "C" unsigned char g_01549bb4[];
extern "C" unsigned char g_01549bb8[];
extern "C" unsigned char g_01549bb9[];
extern "C" unsigned char g_01549bba[];
struct C_008941d0 { void FUN_008941d0(); };
struct C_0089a570 { void FUN_0089a570(); };
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x01300010
extern "C" void __cdecl FUN_01300010(void)
{
    int t1000;
    int t1004;
    float t1008;
    int t1009;
    t1000 = (int)((int)g_01549854);
    ((C_0089a570*)(t1000))->FUN_0089a570();
    t1004 = (int)((int)g_01549938);
    *(unsigned char*)g_01549934 = (unsigned char)((int)1);
    ((C_008941d0*)(t1004))->FUN_008941d0();
    t1008 = (float)((float)(*(float*)g_01485720));
    t1009 = (int)((int)0);
    *(unsigned char*)g_01549bb0 = (unsigned char)((unsigned char)(t1009));
    *(unsigned char*)g_01549bb1 = (unsigned char)((int)1);
    *(float*)g_01549bb4 = (float)(t1008);
    *(unsigned char*)g_01549bb8 = (unsigned char)((unsigned char)(t1009));
    *(unsigned char*)g_01549bb9 = (unsigned char)((unsigned char)(t1009));
    *(unsigned char*)g_01549bba = (unsigned char)((unsigned char)(t1009));
    *(int*)g_01549840 = (int)(t1009);
    *(int*)g_01549844 = (int)(t1009);
    *(int*)g_01549848 = (int)(t1009);
    FUN_011e07ef((unsigned int)((int)&FUN_013c0cc0));
    return;
}
