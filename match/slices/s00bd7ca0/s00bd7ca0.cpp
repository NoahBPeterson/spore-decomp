// 0x00bd7ca0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bd70b0/s00bd70b0.cpp.

struct C_00ac0320 { int FUN_00ac0320(unsigned int); };
struct C_00b18460 { int FUN_00b18460(unsigned int); };
struct C_00c884f0 { int FUN_00c884f0(unsigned int); };

// @ 0x00bd7ca0
extern "C" int __fastcall FUN_00bd7ca0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    int t1012;
    int t1013;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1002 != (int)(-297840274)) {
        if (t1002 != (int)(-291823054)) {
            t1005 = (int)(t1004 + (int)500);
            t1006 = (int)((C_00ac0320*)(t1005))->FUN_00ac0320((unsigned int)(t1002));
            if (t1006 != (int)0) goto Lbd7ce7;
            t1009 = (int)(t1004);
            t1006 = (int)((C_00b18460*)(t1009))->FUN_00b18460((unsigned int)(t1002));
            if (t1006 != (int)0) goto Lbd7ce7;
            t1012 = (int)(t1004 + (int)288);
            t1013 = (int)((C_00c884f0*)(t1012))->FUN_00c884f0((unsigned int)(t1002));
            return (int)(t1013);
        }
    }
    t1006 = (int)(t1004);
    Lbd7ce7:;
    return (int)(t1006);
}
