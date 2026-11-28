// 0x011037e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01102fc0/s01102fc0.cpp.

// @ 0x011037e0
extern "C" int __fastcall FUN_011037e0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    t1001 = (int)((int)(self));
    t1002 = (int)((int)5);
    *(int*)((char*)(t1001) + 16) = (int)(t1002);
    *(int*)((char*)(t1001) + 12) = (int)(t1002);
    t1003 = (int)((int)(a4));
    *(int*)((char*)(t1001)) = (int)((int)1036831949);
    *(int*)((char*)(t1001) + 4) = (int)((int)1000);
    *(int*)((char*)(t1001) + 8) = (int)((int)10);
    switch ((unsigned int)(t1003)) { case 0: goto L110381d; case 1: goto L110380d; default: goto L1103823; }
    goto L110380d;
    goto L110381d;
    goto L1103823;
    L110380d:;
    *(int*)((char*)(t1001)) = (int)((int)1028443341);
    *(int*)((char*)(t1001) + 8) = (int)((int)30);
    return (int)(t1001);
    L110381d:;
    *(int*)((char*)(t1001)) = (int)((int)1045220557);
    L1103823:;
    return (int)(t1001);
}
