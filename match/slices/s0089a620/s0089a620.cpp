// 0x0089a620: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct C_008996d0 { int FUN_008996d0(unsigned int, unsigned int); };

// @ 0x0089a620
extern "C" int __fastcall FUN_0089a620(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 4));
    if ((unsigned int)(t1001) < (unsigned int)*(int*)((char*)((int)(self)) + 8)) {
        t1002 = (int)(t1001 + (int)16);
        *(int*)((char*)((int)(self)) + 4) = (int)(t1002);
        if (t1001 == (int)0) goto L89a65a;
        t1003 = (int)((int)(a4));
        t1004 = (int)(*(int*)((char*)(t1003)));
        *(int*)((char*)(t1001)) = (int)(t1004);
        t1005 = (int)(*(int*)((char*)(t1003) + 4));
        *(int*)((char*)(t1001) + 4) = (int)(t1005);
        t1006 = (int)(*(int*)((char*)(t1003) + 8));
        *(int*)((char*)(t1001) + 8) = (int)(t1006);
        t1007 = (int)(*(int*)((char*)(t1003) + 12));
        *(int*)((char*)(t1001) + 12) = (int)(t1007);
        return (int)(t1001);
    }
    t1008 = (int)((int)(a4));
    t1001 = (int)((C_008996d0*)((int)(self)))->FUN_008996d0((unsigned int)(t1001), (unsigned int)(t1008));
    L89a65a:;
    return (int)(t1001);
}
