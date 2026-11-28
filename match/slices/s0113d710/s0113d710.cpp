// 0x0113d710: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0113cea0/s0113cea0.cpp.

extern "C" unsigned char g_016e6307[];
extern "C" unsigned char g_016e7b9c[];
struct C_0112c5f0 { void FUN_0112c5f0(unsigned int); };
struct C_0112c850 { int FUN_0112c850(unsigned int, unsigned int); };
struct C_0113cf20 { void FUN_0113cf20(); };

// @ 0x0113d710
extern "C" int __fastcall FUN_0113d710(char* self, int edx_unused)
{
    int t1001;
    int t1003;
    int t1007;
    int v_l4;
    int t1008;
    int t1012;
    int t1013;
    t1001 = (int)((int)(*(int*)g_016e7b9c));
    t1003 = (int)((int)(self));
    if (t1001 != (int)0) {
        if (t1001 == (int)1) {
            ((C_0113cf20*)((int)(self)))->FUN_0113cf20();
        }
        *(int*)g_016e7b9c = (int)((int)0);
    }
    t1007 = (int)((int)&v_l4);
    *(unsigned char*)g_016e6307 = (unsigned char)((int)0);
    t1008 = (int)(*(int*)((char*)(t1003) + 4));
    v_l4 = (int)((int)0);
    ((C_0112c5f0*)(t1008))->FUN_0112c5f0((unsigned int)(t1007));
    t1012 = (int)(*(int*)((char*)(t1003) + 36));
    if (t1012 != (int)0) {
        t1013 = (int)(*(int*)((char*)(t1003) + 4));
        t1012 = (int)((C_0112c850*)(t1013))->FUN_0112c850((unsigned int)(t1012), (unsigned int)((int)0));
    }
    return (int)(t1012);
}
