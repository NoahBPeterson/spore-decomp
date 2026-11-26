// 0x00ec4380: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ec40b0/s00ec40b0.cpp.

extern "C" unsigned char g_015abc40[];
extern "C" unsigned char g_015abc4c[];
extern "C" unsigned char g_015abc58[];
extern "C" unsigned char g_015abc64[];
extern "C" unsigned char g_015abc70[];
extern "C" unsigned char g_015abc7c[];
extern "C" int __cdecl FUN_00809db0(...);

// @ 0x00ec4380
extern "C" void __fastcall FUN_00ec4380(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1001;
    t1001 = (int)((int)(self) + (int)16);
    if ((unsigned char)(a4) != (unsigned char)0) {
        if ((unsigned char)(a8) != (unsigned char)0) {
            *(int*)((char*)((int)(self)) + 144) = (int)((int)1);
            if ((unsigned char)(a12) != (unsigned char)0) {
                FUN_00809db0((unsigned int)(t1001), (unsigned int)((int)g_015abc4c));
                return;
            }
            FUN_00809db0((unsigned int)(t1001), (unsigned int)((int)g_015abc40));
            return;
        }
        *(int*)((char*)((int)(self)) + 144) = (int)((int)2);
        if ((unsigned char)(a12) != (unsigned char)0) {
            FUN_00809db0((unsigned int)(t1001), (unsigned int)((int)g_015abc64));
            return;
        }
        FUN_00809db0((unsigned int)(t1001), (unsigned int)((int)g_015abc58));
        return;
    }
    *(int*)((char*)((int)(self)) + 144) = (int)((int)3);
    if ((unsigned char)(a12) != (unsigned char)0) {
        FUN_00809db0((unsigned int)(t1001), (unsigned int)((int)g_015abc7c));
        return;
    }
    FUN_00809db0((unsigned int)(t1001), (unsigned int)((int)g_015abc70));
    return;
}
