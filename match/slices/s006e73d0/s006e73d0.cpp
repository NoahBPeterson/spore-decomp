// 0x006e73d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006e7110/s006e7110.cpp, src/game/SPEngine/SPGraphicsEffectsRenderer.cpp.

struct C_006e7270 { int FUN_006e7270(unsigned int, unsigned int); };

// @ 0x006e73d0
extern "C" void __fastcall FUN_006e73d0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)0);
    t1006 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1001)) > (unsigned char)0) {
        t1008 = (int)(t1001 + (int)4);
        do {
            t1009 = (int)((int)(a8));
            t1010 = (int)(*(int*)((char*)(t1008)));
            t1011 = (int)(t1006);
            ((C_006e7270*)(t1011))->FUN_006e7270((unsigned int)(t1010), (unsigned int)(t1009));
            t1015 = (int)(*(unsigned char*)((char*)(t1001)));
            t1004 = (int)(t1004 + (int)1);
            t1008 = (int)(t1008 + (int)4);
        } while (t1004 < t1015);
    }
    return;
}
