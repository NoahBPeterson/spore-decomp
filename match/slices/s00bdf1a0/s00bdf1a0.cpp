// 0x00bdf1a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bdee20/s00bdee20.cpp, src/game/SPGonzago/SPCity.cpp.

struct C_00bdd380 { int FUN_00bdd380(unsigned int); };

// @ 0x00bdf1a0
extern "C" void __cdecl FUN_00bdf1a0(int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1005;
    int t1006;
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(a8));
    if ((unsigned int)(t1003) > (unsigned int)0) {
        t1005 = (int)((int)(a12));
        do {
            if (t1001 != (int)0) {
                t1006 = (int)(t1001);
                ((C_00bdd380*)(t1006))->FUN_00bdd380((unsigned int)(t1005));
            }
            t1003 = (int)(t1003 - (int)1);
            t1001 = (int)(t1001 - (int)(-128));
        } while ((unsigned int)(t1003) > (unsigned int)0);
    }
    return;
}
