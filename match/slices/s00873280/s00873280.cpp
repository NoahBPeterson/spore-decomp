// 0x00873280: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_0142266c[];
extern "C" void __cdecl FUN_0086b250(...);

// @ 0x00873280
extern "C" int __cdecl FUN_00873280(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1016;
    t1000 = (int)((int)(a8));
    t1001 = (int)(*(unsigned char*)((char*)(t1000) + 1));
    t1002 = (int)(*(unsigned char*)((char*)(t1000) + 2));
    t1004 = (int)(*(unsigned char*)((char*)(t1000)));
    t1005 = (int)(*(unsigned char*)((char*)(t1000) + 3));
    t1006 = (int)(t1004 << (int)8);
    t1007 = (int)(t1006 + t1001);
    t1008 = (int)(t1007 << (int)8);
    t1009 = (int)(t1008 + t1002);
    t1010 = (int)(t1009 << (int)8);
    t1011 = (int)(t1010 + t1005);
    if ((unsigned int)(t1011) > (unsigned int)2147483647) {
        t1012 = (int)((int)(a4));
        FUN_0086b250((unsigned int)(t1012), (unsigned int)((int)g_0142266c));
    }
    t1016 = (int)(t1011);
    return (int)(t1016);
}
