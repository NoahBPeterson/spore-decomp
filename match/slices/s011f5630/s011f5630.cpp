// 0x011f5630: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011f4e90/s011f4e90.cpp.

extern "C" unsigned char g_0170a720[];
extern "C" unsigned char g_0170a724[];
extern "C" unsigned char g_0170a728[];
extern "C" unsigned char g_0170a72c[];
extern "C" unsigned char g_0170a730[];
extern "C" unsigned char g_0170a734[];
extern "C" unsigned char g_0170a738[];
extern "C" unsigned char g_0170a73c[];
extern "C" unsigned char g_0170a740[];
extern "C" unsigned char g_0170a744[];
extern "C" unsigned char g_0170a748[];
extern "C" unsigned char g_0170a74c[];
extern "C" unsigned char g_0170a754[];
extern "C" unsigned char g_0170a75c[];
struct C_011fd5d0 { void FUN_011fd5d0(); };

// @ 0x011f5630
extern "C" void __cdecl FUN_011f5630(void)
{
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    int t1010;
    t1001 = (int)((int)(*(int*)g_0170a754));
    t1003 = (int)((int)0);
    *(int*)g_0170a720 = (int)(t1003);
    *(int*)g_0170a724 = (int)(t1003);
    *(int*)g_0170a728 = (int)(t1003);
    *(int*)g_0170a72c = (int)(t1003);
    *(int*)g_0170a730 = (int)(t1003);
    *(int*)g_0170a734 = (int)(t1003);
    *(int*)g_0170a738 = (int)(t1003);
    *(int*)g_0170a73c = (int)(t1003);
    *(int*)g_0170a740 = (int)(t1003);
    *(int*)g_0170a744 = (int)(t1003);
    *(int*)g_0170a748 = (int)(t1003);
    *(int*)g_0170a74c = (int)(t1003);
    if (t1001 != t1003) {
        do {
            t1004 = (int)(*(int*)((char*)(t1001)));
            if (t1004 != t1003) {
                t1005 = (int)(*(int*)((char*)(t1004)));
                ((void (__stdcall*)(unsigned int))(*(int*)((char*)(t1005) + 8)))((unsigned int)(t1004));
                *(int*)((char*)(t1001)) = (int)(t1003);
            }
            *(int*)((char*)(t1001) + 8) = (int)(t1003);
            *(int*)((char*)(t1001) + 12) = (int)(t1003);
            t1001 = (int)(*(int*)((char*)(t1001) + 16));
        } while (t1001 != t1003);
    }
    t1010 = (int)((int)g_0170a75c);
    ((C_011fd5d0*)(t1010))->FUN_011fd5d0();
    return;
}
