// 0x0113b9d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/plugins/_at_01130000.cpp, match/slices/s0113a8b0/s0113a8b0.cpp.

struct C_0112c850 { int FUN_0112c850(unsigned int, unsigned int); };
struct C_0112dad0 { void FUN_0112dad0(unsigned int); };

// @ 0x0113b9d0
extern "C" int __fastcall FUN_0113b9d0(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1008;
    int t1009;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 361) != (unsigned char)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 4));
        t1004 = (int)(t1002 + (int)48);
        ((C_0112dad0*)(t1003))->FUN_0112dad0((unsigned int)(t1004));
    }
    t1008 = (int)(*(int*)((char*)(t1002) + 72));
    if (t1008 != (int)0) {
        t1009 = (int)(*(int*)((char*)(t1002) + 4));
        t1008 = (int)((C_0112c850*)(t1009))->FUN_0112c850((unsigned int)(t1008), (unsigned int)((int)0));
    }
    return (int)(t1008);
}
