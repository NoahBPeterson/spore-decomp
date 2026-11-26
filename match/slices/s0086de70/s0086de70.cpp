// 0x0086de70: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// @ 0x0086de70
extern "C" void __cdecl FUN_0086de70(int a4, int a8)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    unsigned char t1009;
    unsigned char t1010;
    unsigned char t1011;
    unsigned char t1012;
    int t1013;
    unsigned char t1014;
    int t1015;
    t1001 = (int)((int)(a4));
    if ((unsigned char)*(unsigned char*)((char*)(t1001) + 9) == (unsigned char)16) {
        t1002 = (int)(*(unsigned char*)((char*)(t1001) + 10));
        t1003 = (int)(t1002 * (int)*(int*)((char*)(t1001)));
        t1004 = (int)((int)(a8));
        t1005 = (int)(t1004);
        if ((unsigned int)(t1003) > (unsigned int)0) {
            t1007 = (int)(t1003);
            do {
                *(unsigned char*)&(t1003) = (unsigned char)(*(unsigned char*)((char*)(t1004)));
                *(unsigned char*)((char*)(t1005)) = (unsigned char)((unsigned char)(t1003));
                t1004 = (int)(t1004 + (int)2);
                t1005 = (int)(t1005 + (int)1);
                t1007 = (int)(t1007 - (int)1);
            } while (t1007 != (int)0);
        }
        t1009 = (unsigned char)(*(unsigned char*)((char*)(t1001) + 10));
        t1010 = (unsigned char)(t1009);
        t1011 = (unsigned char)(t1010 + t1010);
        t1012 = (unsigned char)(t1011 + t1011);
        t1013 = (int)(t1009);
        t1014 = (unsigned char)(t1012 + t1012);
        t1015 = (int)(t1013 * (int)*(int*)((char*)(t1001)));
        *(unsigned char*)((char*)(t1001) + 9) = (unsigned char)((int)8);
        *(unsigned char*)((char*)(t1001) + 11) = (unsigned char)(t1014);
        *(int*)((char*)(t1001) + 4) = (int)(t1015);
    }
    return;
}
