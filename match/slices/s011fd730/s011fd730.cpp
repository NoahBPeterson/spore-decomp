// 0x011fd730: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011fd3a0/s011fd3a0.cpp.

extern "C" unsigned char g_016f89cc[];
extern "C" unsigned char g_016f89d0[];

// @ 0x011fd730
// @ 0x011fd730
extern "C" int __fastcall FUN_011fd730(char* self, int edx_unused)
{
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 4));
    t1003 = (int)((int)(self) + (int)4);
    if (t1001 == (int)0) {
        t1004 = (int)((int)(*(int*)g_016f89d0));
        t1005 = (int)(*(int*)((char*)(t1004)));
        t1006 = (int)((int)(self) + (int)8);
        t1001 = (int)((int (__stdcall*)(unsigned int, unsigned int, unsigned int))(*(int*)((char*)(t1005) + 424)))((unsigned int)(t1004), (unsigned int)(t1006), (unsigned int)(t1003));
    }
    t1009 = (int)(*(int*)((char*)(t1003)));
    if ((int)(*(int*)g_016f89cc) != t1009) {
        t1010 = (int)((int)(*(int*)g_016f89d0));
        t1011 = (int)(*(int*)((char*)(t1010)));
        t1001 = (int)((int (__stdcall*)(unsigned int, unsigned int))(*(int*)((char*)(t1011) + 428)))((unsigned int)(t1010), (unsigned int)(t1009));
        *(int*)g_016f89cc = (int)(t1009);
    }
    return (int)(t1001);
}
