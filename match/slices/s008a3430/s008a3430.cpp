// 0x008a3430: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct C_008a2ee0 { int FUN_008a2ee0(unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_008a3370 { int FUN_008a3370(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x008a3430
extern "C" void __fastcall FUN_008a3430(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int v_l64[16];
    int t1010;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    t1002 = (int)((int)(a8));
    t1004 = (int)((int)(a4));
    t1006 = (int)((int)(self));
    if ((unsigned int)(t1004) < (unsigned int)(t1002)) {
        do {
            t1008 = (int)((int)&a4);
            t1009 = (int)((int)&v_l64);
            t1010 = (int)(t1006);
            t1013 = (int)((C_008a2ee0*)(t1010))->FUN_008a2ee0((unsigned int)(t1004), (unsigned int)(t1002), (unsigned int)(t1009), (unsigned int)(t1008));
            t1014 = (int)((int)(a4));
            t1015 = (int)(t1013);
            t1016 = (int)((int)&v_l64);
            t1017 = (int)(t1006);
            ((C_008a3370*)(t1017))->FUN_008a3370((unsigned int)(t1004), (unsigned int)(t1015), (unsigned int)(t1016), (unsigned int)(t1014));
            t1004 = (int)(t1004 + t1015);
        } while ((unsigned int)(t1004) < (unsigned int)(t1002));
    }
    return;
}
