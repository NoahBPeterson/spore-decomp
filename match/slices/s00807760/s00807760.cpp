// 0x00807760: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIHelpers.cpp, match/slices/s008068d0/s008068d0.cpp.

extern "C" unsigned char g_008053e0[];
extern "C" unsigned char g_00805400[];
extern "C" unsigned char g_01417940[];
extern "C" unsigned char g_01417958[];
struct C_00926720 { int FUN_00926720(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00807760
extern "C" int __fastcall FUN_00807760(char* self, int edx_unused)
{
    int t1004;
    int v_l8;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int v_l4;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    int t1023;
    t1004 = (int)((int)(self));
    *(int*)((char*)(t1004)) = (int)((int)g_01417958);
    v_l8 = (int)((int)5);
    t1006 = (int)((int)16);
    t1007 = (int)(t1004 + (int)4);
    do {
        t1008 = (int)(t1006 + (int)2499);
        t1011 = (int)(t1008 / t1006);
        t1012 = (int)((int)&v_l8);
        v_l4 = (int)(t1011);
        if (t1011 >= (int)5) {
            t1012 = (int)((int)&v_l4);
        }
        t1015 = (int)FUN_00f473a0((unsigned int)((int)32), (unsigned int)((int)g_01417940), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1015 != (int)0) {
            t1016 = (int)(*(int*)((char*)(t1012)));
            t1017 = (int)(t1015);
            t1020 = (int)((C_00926720*)(t1017))->FUN_00926720((unsigned int)(t1006), (unsigned int)((int)0), (unsigned int)(t1016), (unsigned int)((int)0), (unsigned int)((int)(-1)), (unsigned int)((int)g_008053e0), (unsigned int)((int)g_00805400), (unsigned int)((int)0));
        } else {
            t1020 = (int)((int)0);
        }
        *(int*)((char*)(t1007)) = (int)(t1020);
        t1006 = (int)(t1006 + (int)16);
        t1007 = (int)(t1007 + (int)4);
    } while (t1006 < (int)2544);
    t1023 = (int)(t1004);
    return (int)(t1023);
}
