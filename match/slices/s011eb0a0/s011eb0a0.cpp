// 0x011eb0a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011eaf70/s011eaf70.cpp.

// @ 0x011eb0a0
extern "C" int __fastcall FUN_011eb0a0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1;
    int t1003;
    int t2;
    int t3;
    int t1004;
    int t1005;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 4));
    t1002 = (int)((int)(self) + (int)8);
    t1 = (int)(t1001 << (int)2);
    t1003 = (int)(t1001 + t1);
    t2 = (int)(t1003 << (int)2);
    t3 = (int)((int)(self) + t2);
    t1004 = (int)(t3 + (int)8);
    if (t1002 != t1004) {
        t1005 = (int)((int)(a4));
        do {
            if ((int)*(int*)((char*)(t1002)) == t1005) goto L11eb0c2;
            t1002 = (int)(t1002 + (int)20);
        } while (t1002 != t1004);
    }
    t1002 = (int)((int)0);
    L11eb0c2:;
    return (int)(t1002);
}
