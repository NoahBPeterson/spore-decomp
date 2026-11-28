// 0x00e530e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e52d80/s00e52d80.cpp.

extern "C" unsigned char g_016b3c04[];
extern "C" int __cdecl FUN_00e4fd30(...);

// @ 0x00e530e0
extern "C" int __cdecl FUN_00e530e0(void)
{
    int t1000;
    int v_l16[4];
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1010;
    int t1012;
    int t3;
    int t1013;
    int t1014;
    t1000 = (int)((int)&v_l16);
    t1003 = (int)FUN_00e4fd30((unsigned int)(t1000));
    t1006 = (int)(t1003);
    t1007 = (int)((int)0);
    t1008 = (int)((int)0);
    if (t1006 > (int)0) {
        t1010 = (int)((int)(*(int*)g_016b3c04));
        t1012 = (int)(t1007 + (int)52);
        do {
            t3 = (int)((int)&v_l16);
            if ((unsigned char)*(unsigned char*)((char*)(t3) + t1008) != (unsigned char)0) {
                t1013 = (int)(*(int*)((char*)(t1010) + 20880));
                t1014 = (int)(*(int*)((char*)(t1012) + t1013));
                if (t1014 != (int)1) {
                    if (t1014 != (int)2) {
                        t1007 = (int)(t1007 + (int)1);
                    }
                }
            }
            t1008 = (int)(t1008 + (int)1);
            t1012 = (int)(t1012 + (int)4);
        } while (t1008 < t1006);
    }
    return (int)(t1007);
}
