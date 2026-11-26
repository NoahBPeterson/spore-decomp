// 0x007f5410: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007f5300/s007f5300.cpp.

extern "C" unsigned char g_0105a93d[];
extern "C" unsigned char g_0106f146[];
extern "C" unsigned char g_010edf11[];
struct C_0095f960 { int FUN_0095f960(unsigned int); };

// @ 0x007f5410
extern "C" int __fastcall FUN_007f5410(char* self, int edx_unused, int a4)
{
    int t1000;
    int t6;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)g_0105a93d) {
        if (t1000 != (int)g_0106f146) {
            if (t1000 != (int)g_010edf11) {
                *(int*)&(a4) = (int)(t1000);
                t6 = (int)((C_0095f960*)((int)(self)))->FUN_0095f960((unsigned int)((int)(a4)));
                return (int)(t6);
            }
            if ((int)(self) == (int)0) goto L7f5451;
            t1002 = (int)((int)(self) + (int)528);
            return (int)(t1002);
        }
        t1003 = (int)((int)(self));
        return (int)(t1003);
    }
    if ((int)(self) != (int)0) {
        t1004 = (int)((int)(self) + (int)524);
        return (int)(t1004);
    }
    L7f5451:;
    t1005 = (int)((int)0);
    return (int)(t1005);
}
