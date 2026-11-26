// 0x00690b50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPJobManager.cpp, match/slices/s006907e0/s006907e0.cpp.

struct C_0068ffb0 { int FUN_0068ffb0(unsigned int); };
struct C_00690930 { int FUN_00690930(unsigned int, unsigned int); };

// @ 0x00690b50
extern "C" void __fastcall FUN_00690b50(char* self, int edx_unused, int a4, int a8)
{
    int t1003;
    int t1004;
    int t1006;
    int t1009;
    int t1010;
    t1003 = (int)((int)(a4));
    t1004 = (int)(*(int*)((char*)(t1003) + 72));
    t1006 = (int)((int)(self));
    if (t1004 == (int)(a8)) {
        t1009 = (int)((C_0068ffb0*)((int)(self)))->FUN_0068ffb0((unsigned int)(t1003));
        if (t1009 < t1004) {
            t1010 = (int)(t1006);
            t1009 = (int)((C_00690930*)(t1010))->FUN_00690930((unsigned int)(t1003), (unsigned int)(t1009));
        }
    }
    return;
}
