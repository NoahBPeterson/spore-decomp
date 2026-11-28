// 0x0083db70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Expression.cpp, match/slices/s0083d3d0/s0083d3d0.cpp.

extern "C" unsigned char g_0141b654[];
extern "C" unsigned char g_014f9174[];
extern "C" void __cdecl FUN_0052df30(...);
extern "C" void __cdecl FUN_0083ce90(...);
struct C_0083eb00 { int FUN_0083eb00(unsigned int); };
struct C_011e0912 { int FUN_011e0912(unsigned int, unsigned int); };
extern "C" int __stdcall FUN_011e0912(unsigned int, unsigned int);

// @ 0x0083db70
extern "C" int __fastcall FUN_0083db70(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1008;
    int t1009;
    int v_l16[4];
    int t1013;
    int t1016;
    int t1017;
    int t1018;
    int t1021;
    int t1025;
    int t1026;
    int t1030;
    int t1033;
    int t1034;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    FUN_0083ce90((unsigned int)(t1001));
    t1008 = (int)(*(int*)((char*)(t1001)));
    if ((unsigned char)*(unsigned char*)((char*)(t1008)) != (unsigned char)40) {
        t1009 = (int)((int)&v_l16);
        FUN_0052df30((unsigned int)(t1009), (unsigned int)((int)g_0141b654), (unsigned int)((int)40));
        t1013 = (int)((int)&v_l16);
        t1008 = (int)((C_011e0912*)(t1013))->FUN_011e0912((unsigned int)(t1013), (unsigned int)((int)g_014f9174));
    }
    t1016 = (int)(t1008 + (int)1);
    t1017 = (int)(t1004);
    *(int*)((char*)(t1001)) = (int)(t1016);
    t1018 = (int)((C_0083eb00*)(t1017))->FUN_0083eb00((unsigned int)(t1001));
    t1021 = (int)(t1018);
    FUN_0083ce90((unsigned int)(t1001));
    t1025 = (int)(*(int*)((char*)(t1001)));
    if ((unsigned char)*(unsigned char*)((char*)(t1025)) != (unsigned char)41) {
        t1026 = (int)((int)&v_l16);
        FUN_0052df30((unsigned int)(t1026), (unsigned int)((int)g_0141b654), (unsigned int)((int)41));
        t1030 = (int)((int)&v_l16);
        t1025 = (int)FUN_011e0912((unsigned int)(t1030), (unsigned int)((int)g_014f9174));
    }
    t1033 = (int)(t1025 + (int)1);
    *(int*)((char*)(t1001)) = (int)(t1033);
    t1034 = (int)(t1021);
    return (int)(t1034);
}
