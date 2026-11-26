// 0x007b02f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007af8b0/s007af8b0.cpp, src/game/SPEngine/SPGraphicsTextureUtilities.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_0140fc28[];
extern "C" unsigned char g_0140fc2c[];
struct C_0070f520 { int FUN_0070f520(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x007b02f0
extern "C" void __fastcall FUN_007b02f0(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1011;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1022;
    t1002 = (int)((int)(self));
    t1004 = (int)(t1002 + (int)32);
    *(int*)((char*)(t1002)) = (int)((int)g_0140fc2c);
    *(int*)((char*)(t1002) + 4) = (int)((int)g_0140fc28);
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1006 = (int)(*(int*)((char*)(t1004)));
    t1007 = (int)(t1004);
    ((C_0070f520*)(t1007))->FUN_0070f520((unsigned int)(t1006), (unsigned int)(t1005));
    t1011 = (int)(*(int*)((char*)(t1004)));
    if (t1011 != (int)0) {
        if ((int)*(int*)((char*)(t1011) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1011));
        }
    }
    t1015 = (int)(*(int*)((char*)(t1002) + 16));
    t1016 = (int)(*(int*)((char*)(t1002) + 12));
    t1017 = (int)(t1002 + (int)12);
    t1018 = (int)(t1017);
    ((C_0070f520*)(t1018))->FUN_0070f520((unsigned int)(t1016), (unsigned int)(t1015));
    t1022 = (int)(*(int*)((char*)(t1017)));
    if (t1022 != (int)0) {
        if ((int)*(int*)((char*)(t1022) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1022));
        }
    }
    *(int*)((char*)(t1002) + 4) = (int)((int)g_013ef094);
    *(int*)((char*)(t1002)) = (int)((int)g_013eb938);
    return;
}
