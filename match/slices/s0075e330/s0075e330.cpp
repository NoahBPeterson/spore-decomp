// 0x0075e330: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsRenderer.cpp, match/slices/s0075de80/s0075de80.cpp.

extern "C" unsigned char g_0140dca0[];
struct C_009221b0 { void FUN_009221b0(unsigned int); };
struct C_00922270 { void FUN_00922270(); };

// @ 0x0075e330
extern "C" int __fastcall FUN_0075e330(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1005;
    int t1009;
    int t1010;
    int t1018;
    int t1017;
    int t1023;
    t1002 = (int)((int)(self));
    t1004 = (int)(t1002 + (int)40);
    t1005 = (int)(t1004);
    ((C_009221b0*)(t1005))->FUN_009221b0((unsigned int)((int)g_0140dca0));
    t1009 = (int)(*(int*)((char*)(t1002) + 144));
    t1010 = (int)(t1009 - (int)*(int*)((char*)(t1002) + 140));
    t1018 = (int)(t1010 / (int)20);
    t1017 = (int)(t1004);
    ((C_00922270*)(t1017))->FUN_00922270();
    t1023 = (int)(t1018);
    return (int)(t1023);
}
