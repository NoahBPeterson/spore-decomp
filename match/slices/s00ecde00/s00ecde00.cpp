// 0x00ecde00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ecda80/s00ecda80.cpp.

struct C_005c6a30 { int FUN_005c6a30(unsigned int); };

// @ 0x00ecde00
extern "C" int __fastcall FUN_00ecde00(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1002;
    int t1003;
    int t1004;
    int t9;
    int t1005;
    int t1006;
    int t1007;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)74996285) {
        if (t1000 != (int)119725650) {
            if (t1000 != (int)(-297840274)) {
                if (t1000 != (int)136999144) goto Lecde36;
                t1002 = (int)((int)(self) + (int)(-8));
            } else {
                t1003 = (int)((int)(self) + (int)(-8));
                if (t1003 == (int)0) goto Lecde36;
                t1002 = (int)((int)(self));
            }
            if (t1002 != (int)0) goto Lecde57;
            Lecde36:;
            *(int*)&(a4) = (int)(t1000);
            t1004 = (int)((int)(self) + (int)40);
            t9 = (int)((C_005c6a30*)(t1004))->FUN_005c6a30((unsigned int)((int)(a4)));
            return (int)(t9);
        }
        t1005 = (int)((int)(self) + (int)(-8));
        return (int)(t1005);
    }
    t1006 = (int)((int)(self) + (int)(-8));
    if (t1006 != (int)0) {
        t1007 = (int)((int)(self) + (int)28);
        return (int)(t1007);
    }
    t1002 = (int)((int)0);
    Lecde57:;
    return (int)(t1002);
}
