// 0x008edc30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008edc30/s008edc30.cpp, src/game/UTFSpore_Win32/_at_008e0000.cpp.

struct C_008e2810 { int FUN_008e2810(); };
struct C_008e8650 { int FUN_008e8650(); };
struct C_008ecfa0 { int FUN_008ecfa0(unsigned int, unsigned int, unsigned int); };
struct C_008fbe00 { void FUN_008fbe00(unsigned int); };

// @ 0x008edc30
extern "C" void __fastcall FUN_008edc30(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1007;
    int t1008;
    int t1009;
    int v_l1104[276];
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 60) == (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 36));
        t1007 = (int)((C_008e2810*)(t1003))->FUN_008e2810();
        t1008 = (int)(t1007);
        if (t1008 != (int)0) {
            t1009 = (int)((int)&v_l1104);
            ((C_008fbe00*)(t1009))->FUN_008fbe00((unsigned int)(t1002));
            t1013 = (int)((int)&v_l1104);
            t1014 = (int)(t1002);
            *(int*)((char*)(t1002) + 64) = (int)((int)0);
            *(int*)((char*)(t1002) + 616) = (int)((int)0);
            t1017 = (int)((C_008ecfa0*)(t1014))->FUN_008ecfa0((unsigned int)(t1008), (unsigned int)(t1013), (unsigned int)((int)1));
            t1018 = (int)((int)&v_l1104);
            *(int*)((char*)(t1002) + 60) = (int)(t1017);
            t1007 = (int)((C_008e8650*)(t1018))->FUN_008e8650();
        }
    }
    return;
}
