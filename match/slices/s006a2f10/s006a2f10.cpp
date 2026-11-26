// 0x006a2f10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006a22a0/s006a22a0.cpp.

struct C_00542b80 { int FUN_00542b80(); };
struct C_006a2d30 { int FUN_006a2d30(unsigned int, unsigned int); };

// @ 0x006a2f10
extern "C" int __fastcall FUN_006a2f10(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1003;
    int t1005;
    int t1007;
    int t1009;
    int t1012;
    int t1013;
    int t1016;
    int t1017;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    if (t1003 != t1000) {
        t1005 = (int)(*(int*)((char*)(t1000) + 24));
        t1007 = (int)(*(int*)((char*)(t1000) + 28));
        if (t1005 != t1007) {
            t1009 = (int)(t1003 + (int)24);
            goto L6a2f30;
            L6a2f30:;
            t1012 = (int)(t1005 + (int)4);
            t1013 = (int)(t1009);
            t1016 = (int)((C_006a2d30*)(t1013))->FUN_006a2d30((unsigned int)(t1005), (unsigned int)(t1012));
            t1017 = (int)(t1016);
            t1000 = (int)((C_00542b80*)(t1017))->FUN_00542b80();
            t1005 = (int)(t1005 + (int)24);
            if (t1005 != t1007) goto L6a2f30;
        }
        *(int*)((char*)(t1003) + 52) += (int)1;
    }
    return (int)(t1000);
}
