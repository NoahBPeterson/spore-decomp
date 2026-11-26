// 0x0086b480: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x0086b480
extern "C" int __cdecl FUN_0086b480(int a4, int a8, int a12, int a16, int a20)
{
    int t1000;
    int t1001;
    unsigned char t3;
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    t1000 = (int)((int)0);
    if ((int)(a4) != t1000) {
        t1001 = (int)((int)(a8));
        if (t1001 != (int)0) {
            t3 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 8) & (unsigned char)16);
            if (t3 != (unsigned char)0) {
                if ((unsigned char)*(unsigned char*)((char*)(t1001) + 25) == (unsigned char)3) {
                    t1002 = (int)((int)(a12));
                    if (t1002 != (int)0) {
                        t1003 = (int)(*(int*)((char*)(t1001) + 76));
                        *(int*)((char*)(t1002)) = (int)(t1003);
                        t1000 = (int)((int)16);
                    }
                    t1004 = (int)((int)(a20));
                    if (t1004 == (int)0) goto L86b4df;
                    t1006 = (int)(t1001 + (int)80);
                    *(int*)((char*)(t1004)) = (int)(t1006);
                    goto L86b4df;
                }
                t1008 = (int)((int)(a20));
                if (t1008 != (int)0) {
                    t1009 = (int)(t1001 + (int)80);
                    *(int*)((char*)(t1008)) = (int)(t1009);
                    t1000 = (int)((int)16);
                }
                t1010 = (int)((int)(a12));
                if (t1010 != (int)0) {
                    *(int*)((char*)(t1010)) = (int)((int)0);
                }
                L86b4df:;
                t1011 = (int)((int)(a16));
                if (t1011 != (int)0) {
                    t1012 = (int)(*(unsigned short*)((char*)(t1001) + 22));
                    *(int*)((char*)(t1011)) = (int)(t1012);
                    t1000 = (int)(t1000 | (int)16);
                }
            }
        }
    }
    return (int)(t1000);
}
