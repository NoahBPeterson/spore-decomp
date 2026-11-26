// 0x01183410: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011b1520/s011b1520.cpp.

extern "C" unsigned char g_015cd79c[];
extern "C" unsigned char g_015cd7a0[];
extern "C" unsigned char g_015cd7a8[];
extern "C" unsigned char g_016f1c70[];
extern "C" unsigned char g_016f1c84[];

// @ 0x01183410
extern "C" int __cdecl FUN_01183410(int a4, int a8, int a12)
{
    int t1001;
    int t1002;
    int t1003;
    int t1005;
    int t1008;
    int t1010;
    int t1016;
    int t1017;
    int t1018;
    unsigned char t1021;
    int t1024;
    t1001 = (int)((int)(a4));
    t1002 = (int)((int)0);
    if (t1001 <= t1002) {
        t1003 = (int)((int)0);
        return (int)(t1003);
    }
    t1005 = (int)((int)(*(int*)g_016f1c70));
    t1008 = (int)((int)(a12));
    t1010 = (int)((int)(a8));
    *(int*)g_015cd79c = (int)(t1002);
    if (t1005 != t1002) {
        *(int*)g_015cd7a0 = (int)(t1002);
        ((void (__cdecl*)(int, int, int, int, int))(t1005))((int)(t1002), (int)(t1001), (int)(t1010), (int)(t1008), (int)(t1002));
    }
    t1016 = (int)((int (__cdecl*)(...))(*(int*)g_015cd7a8))(t1001, t1010, t1008);
    t1017 = (int)(t1016);
    t1018 = (int)((int)(*(int*)g_016f1c70));
    if (t1018 != (int)0) {
        t1018 = (int)((int (__cdecl*)(int, int, int, int, int))(t1018))((int)(t1017), (int)(t1001), (int)(t1010), (int)(t1008), (int)((int)1));
    }
    if (t1017 != (int)0) {
        if (t1001 > (int)2048) {
            t1021 = (unsigned char)((unsigned char)(*(unsigned char*)g_016f1c84));
            *(unsigned char*)((char*)(t1017)) = (unsigned char)(t1021);
        }
    }
    t1024 = (int)(t1017);
    return (int)(t1024);
}
