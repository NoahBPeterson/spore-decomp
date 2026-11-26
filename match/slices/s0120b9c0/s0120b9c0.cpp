// 0x0120b9c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0120ae50/s0120ae50.cpp.

extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_014a6e88[];
struct C_0109ae60 { int FUN_0109ae60(); };

// @ 0x0120b9c0
extern "C" void __fastcall FUN_0120b9c0(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1007;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 24));
    *(int*)((char*)(t1002)) = (int)((int)g_014a6e88);
    if (t1003 != (int)0) {
        ((C_0109ae60*)(t1003))->FUN_0109ae60();
        *(int*)((char*)(t1002) + 24) = (int)((int)0);
    }
    t1007 = (int)(*(int*)((char*)(t1002) + 28));
    if (t1007 != (int)0) {
        ((C_0109ae60*)(t1007))->FUN_0109ae60();
        *(int*)((char*)(t1002) + 28) = (int)((int)0);
    }
    *(int*)((char*)(t1002)) = (int)((int)g_013ef094);
    return;
}
