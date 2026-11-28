// 0x0065bc20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0065af90/s0065af90.cpp, src/game/SPEditors/SPUIAssetWebBrowser.cpp.

extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];
extern "C" void __cdecl FUN_006214c0(...);
struct C_00997730 { bool FUN_00997730(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x0065bc20
// @ 0x0065bc20
extern "C" bool __fastcall FUN_0065bc20(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int v_l16[4];
    int t1006;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1016;
    bool t1017;
    int t1018;
    int t1019;
    int t1020;
    bool t1023;
    bool t1027;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 156) != (int)0) {
        t1003 = (int)((int)(a4));
        t1004 = (int)((int)g_01667bac);
        (*(int*)&v_l16[0]) = (int)(t1004);
        (*(int*)&v_l16[1]) = (int)(t1004);
        t1006 = (int)((int)&v_l16);
        (*(int*)&v_l16[2]) = (int)((int)g_01667bae);
        FUN_006214c0((unsigned int)(t1003), (unsigned int)(t1006));
        t1010 = (int)((*(int*)&v_l16[0]));
        t1011 = (int)(*(int*)((char*)(t1002) + 156));
        t1012 = (int)(t1002 + (int)32);
        t1017 = ((C_00997730*)(t1012))->FUN_00997730((unsigned int)(t1011), (unsigned int)(t1010), (unsigned int)((int)0), (unsigned int)((int)0));
        t1016 = (int)((*(int*)&v_l16[2]));
        t1018 = (int)((*(int*)&v_l16[0]));
        t1019 = (int)(t1016 - t1018);
        t1020 = (int)(t1019 & (int)(-2));
        if (t1020 > (int)2) {
            if (t1018 != (int)0) {
                t1018 = (int)FUN_00f47380((unsigned int)(t1018));
            }
        }
        t1023 = t1017;
        return t1023;
    }
    t1027 = false;
    return (bool)(t1027);
}
