// 0x008773d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_00877350[];
extern "C" unsigned char g_008773b0[];
extern "C" unsigned char g_01423b7c[];
extern "C" unsigned char g_01423bb4[];
extern "C" int __cdecl FUN_0086b300(...);

// @ 0x008773d0
extern "C" void __cdecl FUN_008773d0(int a4, int a8, int a12, int a16)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1002 = (int)((int)(a8));
        *(int*)((char*)(t1001) + 84) = (int)(t1002);
        t1003 = (int)((int)(a12));
        if (t1003 != (int)0) {
            *(int*)((char*)(t1001) + 76) = (int)(t1003);
        } else {
            *(int*)((char*)(t1001) + 76) = (int)((int)g_00877350);
        }
        t1004 = (int)((int)(a16));
        if (t1004 != (int)0) {
            *(int*)((char*)(t1001) + 332) = (int)(t1004);
        } else {
            *(int*)((char*)(t1001) + 332) = (int)((int)g_008773b0);
        }
        if ((int)*(int*)((char*)(t1001) + 80) != (int)0) {
            *(int*)((char*)(t1001) + 80) = (int)((int)0);
            FUN_0086b300((unsigned int)(t1001), (unsigned int)((int)g_01423bb4));
            t1004 = (int)FUN_0086b300((unsigned int)(t1001), (unsigned int)((int)g_01423b7c));
        }
    }
    return;
}
