// 0x005c5e90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPEditorPaletteData.cpp, match/slices/s005c53c0/s005c53c0.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_013f7fc4[];
extern "C" unsigned char g_013f7fd4[];
struct C_005c2230 { void FUN_005c2230(); };
struct C_005c7f10 { int FUN_005c7f10(); };

// @ 0x005c5e90
extern "C" void __fastcall FUN_005c5e90(char* self, int edx_unused)
{
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1016;
    t1003 = (int)((int)(self));
    t1005 = (int)(t1003 + (int)12);
    *(int*)((char*)(t1003)) = (int)((int)g_013f7fd4);
    *(int*)((char*)(t1003) + 8) = (int)((int)g_013f7fc4);
    t1006 = (int)(*(int*)((char*)(t1005) + 4));
    t1007 = (int)(t1006 - (int)*(int*)((char*)(t1005)));
    t1009 = (int)(t1007 >> (int)2);
    t1010 = (int)((int)0);
    if (t1009 > (int)0) {
        do {
            t1011 = (int)(*(int*)((char*)(t1005)));
            t1012 = (int)(*(int*)((char*)(t1011) + (t1010)*4));
            ((C_005c2230*)(t1012))->FUN_005c2230();
            t1010 = (int)(t1010 + (int)1);
        } while (t1010 < t1009);
    }
    t1016 = (int)(t1005);
    ((C_005c7f10*)(t1016))->FUN_005c7f10();
    *(int*)((char*)(t1003) + 8) = (int)((int)g_013eb938);
    *(int*)((char*)(t1003)) = (int)((int)g_013ec458);
    return;
}
