// 0x011223b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01121e10/s01121e10.cpp.

// @ 0x011223b0
extern "C" int __cdecl FUN_011223b0(int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    unsigned char t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    t1000 = (int)((int)(a8));
    t1001 = (int)(*(int*)((char*)(t1000) + 20));
    t1002 = (int)(*(int*)((char*)(t1000) + 16));
    t1003 = (int)(*(int*)((char*)(t1000) + 24));
    t1004 = (int)(*(unsigned short*)((char*)(t1002)));
    t1007 = (int)(*(unsigned short*)((char*)(t1001)));
    t1010 = (int)(*(unsigned short*)((char*)(t1003)));
    t1011 = (int)((int)(a12));
    t1012 = (int)(*(int*)((char*)(t1011) + 16));
    t1013 = (int)(*(unsigned short*)((char*)(t1012)));
    t1014 = (int)(*(int*)((char*)(t1011) + 20));
    t1015 = (int)(*(int*)((char*)(t1011) + 24));
    t1016 = (int)(*(unsigned short*)((char*)(t1014)));
    t1017 = (int)(*(unsigned short*)((char*)(t1015)));
    *(int*)&(a8) = (int)(t1007);
    t1018 = (unsigned char)((int)1);
    if (t1004 == t1013) {
        if (t1007 != t1016) {
            if (t1007 != t1017) goto L1122406;
        }
        t1019 = (int)((int)(a16));
        if ((unsigned char)*(unsigned char*)((char*)(t1019)) != (unsigned char)0) {
            t1018 = (unsigned char)((int)0);
        }
        *(unsigned char*)((char*)(t1019)) = (unsigned char)((int)1);
        t1007 = (int)((int)(a8));
        L1122406:;
        if (t1010 != t1016) {
            if (t1010 != t1017) goto L1122422;
        }
        t1020 = (int)((int)(a20));
        if ((unsigned char)*(unsigned char*)((char*)(t1020)) != (unsigned char)0) {
            t1018 = (unsigned char)((int)0);
        }
        *(unsigned char*)((char*)(t1020)) = (unsigned char)((int)1);
        t1007 = (int)((int)(a8));
    }
    L1122422:;
    if (t1004 == t1016) {
        if (t1007 == t1017) {
            t1021 = (int)((int)(a16));
            if ((unsigned char)*(unsigned char*)((char*)(t1021)) != (unsigned char)0) {
                t1018 = (unsigned char)((int)0);
            }
            *(unsigned char*)((char*)(t1021)) = (unsigned char)((int)1);
        }
        if (t1010 == t1017) {
            t1022 = (int)((int)(a20));
            if ((unsigned char)*(unsigned char*)((char*)(t1022)) != (unsigned char)0) {
                t1018 = (unsigned char)((int)0);
            }
            *(unsigned char*)((char*)(t1022)) = (unsigned char)((int)1);
        }
    }
    if (t1007 == t1013) {
        if (t1010 == t1016) goto L112245e;
        if (t1010 == t1017) goto L112245e;
    }
    if (t1007 != t1016) goto L112246c;
    if (t1010 != t1017) goto L112246c;
    L112245e:;
    t1023 = (int)((int)(a24));
    if ((unsigned char)*(unsigned char*)((char*)(t1023)) != (unsigned char)0) {
        t1018 = (unsigned char)((int)0);
    }
    *(unsigned char*)((char*)(t1023)) = (unsigned char)((int)1);
    L112246c:;
    t1024 = (int)((int)(a4));
    *(unsigned char*)((char*)(t1024)) = (unsigned char)(t1018);
    return (int)(t1024);
}
