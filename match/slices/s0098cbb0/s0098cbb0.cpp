// 0x0098cbb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/TextEdit.cpp, match/slices/s0098c880/s0098c880.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_014457a8[];
extern "C" unsigned char g_014458a0[];
extern "C" unsigned char g_014459c0[];
struct C_00962740 { void FUN_00962740(); };
struct C_0098b5e0 { void FUN_0098b5e0(); };
struct C_0098c520 { void FUN_0098c520(); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x0098cbb0
// @ 0x0098cbb0
extern "C" void __fastcall FUN_0098cbb0(char* self, int edx_unused)
{
    int t1002;
    int t1008;
    int t1009;
    int t1010;
    int t1016;
    int t1022;
    int t1026;
    int t1030;
    int t1036;
    int t1040;
    t1002 = (int)((int)(self));
    *(int*)((char*)(t1002)) = (int)((int)g_014459c0);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_014458a0);
    *(int*)((char*)(t1002) + 524) = (int)((int)g_014457a8);
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 528) != (unsigned char)0) {
        ((C_0098c520*)((int)(self)))->FUN_0098c520();
    }
    t1008 = (int)(t1002 + (int)1448);
    t1009 = (int)((int)1);
    do {
        t1010 = (int)(*(int*)((char*)(t1008) - 16));
        t1008 = (int)(t1008 - (int)20);
        if (t1010 != (int)0) {
            ((il2c_vc0*)(t1010))->s1();
        }
        t1016 = (int)(*(int*)((char*)(t1008)));
        if (t1016 != (int)0) {
            ((il2c_vc1*)(t1016))->s1();
        }
        t1009 = (int)(t1009 - (int)1);
    } while (t1009 >= (int)0);
    t1022 = (int)(t1002 + (int)1364);
    ((C_0098b5e0*)(t1022))->FUN_0098b5e0();
    t1026 = (int)(t1002 + (int)1320);
    ((C_0098b5e0*)(t1026))->FUN_0098b5e0();
    t1030 = (int)(*(int*)((char*)(t1002) + 1292));
    if (t1030 != (int)0) {
        if ((int)*(int*)((char*)(t1030) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1030));
        }
    }
    t1036 = (int)(*(int*)((char*)(t1002) + 636));
    if (t1036 != (int)0) {
        if ((int)*(int*)((char*)(t1036) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1036));
        }
    }
    *(int*)((char*)(t1002) + 524) = (int)((int)g_013eb938);
    t1040 = (int)(t1002);
    ((C_00962740*)(t1040))->FUN_00962740();
    return;
}
