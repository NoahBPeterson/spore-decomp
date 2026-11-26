// 0x008eafd0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct C_008eb910 { int FUN_008eb910(unsigned int, unsigned int); };
struct C_008ec910 { int FUN_008ec910(); };

// @ 0x008eafd0
extern "C" void __fastcall FUN_008eafd0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 56) == (int)(-1)) {
        t1003 = (int)(*(int*)((char*)(t1002) - 184));
        t1006 = (int)((C_008ec910*)(t1003))->FUN_008ec910();
        *(int*)((char*)(t1002) + 56) = (int)(t1006);
    }
    t1007 = (int)((int)(a4));
    t1008 = (int)(*(int*)((char*)(t1002) + 56));
    t1009 = (int)(*(int*)((char*)(t1002) - 184));
    ((C_008eb910*)(t1009))->FUN_008eb910((unsigned int)(t1008), (unsigned int)(t1007));
    return;
}
