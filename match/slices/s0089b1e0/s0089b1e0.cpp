// 0x0089b1e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct C_0089a5d0 { void FUN_0089a5d0(); };

// @ 0x0089b1e0
extern "C" int __fastcall FUN_0089b1e0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    t1002 = (int)((int)(self));
    t1003 = (int)(t1002 + (int)976);
    ((C_0089a5d0*)(t1003))->FUN_0089a5d0();
    t1007 = (int)(*(int*)((char*)(t1002) + 980));
    t1008 = (int)((int)(a8));
    t1009 = (int)(t1007 - (int)44);
    *(int*)((char*)(t1009)) = (int)((int)0);
    t1010 = (int)(*(int*)((char*)(t1002) + 1036));
    *(int*)((char*)(t1009) + 8) = (int)(t1008);
    t1011 = (int)((int)(a4));
    *(int*)((char*)(t1009) + 4) = (int)(t1010);
    t1012 = (int)(*(int*)((char*)(t1002) + 956));
    *(int*)((char*)(t1009) + 12) = (int)(t1012);
    *(int*)((char*)(t1009) + 16) = (int)(t1011);
    *(int*)((char*)(t1002) + 1032) += (int)1;
    t1013 = (int)(*(int*)((char*)(t1009) + 8));
    *(int*)((char*)(t1002) + 1036) += t1013;
    if ((int)*(int*)((char*)(t1002) + 1044) == (int)2) {
        *(int*)((char*)(t1002) + 1044) = (int)((int)0);
    }
    return (int)(t1013);
}
