// 0x0089e680: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_0089e5e0(...);

// @ 0x0089e680
extern "C" bool __cdecl FUN_0089e680(int a4)
{
    int t1001;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t2;
    int t1009;
    int t1010;
    bool t1011;
    bool t1013;
    t1001 = (int)((int)(a4));
    t1005 = (int)FUN_0089e5e0((unsigned int)(t1001));
    t1006 = (int)((int)1);
    t1007 = (int)(t1005);
    t1008 = (int)(t1006 << (unsigned char)(t1007));
    t2 = (int)(t1008 & (int)7168);
    if (t2 != (int)0) {
        t1005 = (int)((int)2381);
        if ((unsigned short)(t1001) != (unsigned short)(t1005)) {
            t1009 = (int)((int)3642);
            if ((unsigned short)(t1001) != (unsigned short)(t1009)) {
                t1010 = (int)((int)847);
                if ((unsigned short)(t1001) != (unsigned short)(t1010)) {
                    t1011 = true;
                    return (bool)(t1011);
                }
            }
        }
    }
    t1013 = false;
    return (bool)(t1013);
}
