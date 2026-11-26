// 0x00ece370: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ecda80/s00ecda80.cpp.

struct C_00ecde00 { int FUN_00ecde00(unsigned int); };

// @ 0x00ece370
extern "C" int __fastcall FUN_00ece370(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1002;
    int t1003;
    int t1004;
    int t6;
    int t1005;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)119725667) {
        if (t1000 == (int)788569552) {
            t1002 = (int)((int)(self) + (int)(-8));
            if (t1002 != (int)0) {
                t1003 = (int)(t1002 + (int)108);
                return (int)(t1003);
            }
            t1004 = (int)((int)0);
            return (int)(t1004);
        }
        *(int*)&(a4) = (int)(t1000);
        t6 = (int)((C_00ecde00*)((int)(self)))->FUN_00ecde00((unsigned int)((int)(a4)));
        return (int)(t6);
    }
    t1005 = (int)((int)(self) + (int)(-8));
    return (int)(t1005);
}
