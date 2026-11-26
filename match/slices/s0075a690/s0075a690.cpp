// 0x0075a690: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0075a550/s0075a550.cpp, src/game/SPEngine/_at_00750000.cpp.

struct C_011fe600 { int FUN_011fe600(float); };

// @ 0x0075a690
extern "C" void __fastcall FUN_0075a690(char* self, int edx_unused, float a4)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 64));
    t1006 = (int)((int)0);
    if (t1005 > (int)0) {
        t1007 = (int)(t1004);
        do {
            t1008 = (int)(*(int*)((char*)(t1007) + 60));
            t1009 = (int)(t1008 * t1006);
            t1010 = (int)(t1009 + (int)*(int*)((char*)(t1007) + 48));
            ((C_011fe600*)(t1010))->FUN_011fe600((float)((float)(a4)));
            t1006 = (int)(t1006 + (int)1);
        } while (t1006 < t1005);
        *(int*)((char*)(t1007) + 24) = (int)((int)0);
        return;
    }
    *(int*)((char*)(t1004) + 24) = (int)(t1006);
    return;
}
