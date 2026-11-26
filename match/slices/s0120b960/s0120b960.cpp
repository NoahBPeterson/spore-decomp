// 0x0120b960: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0120ae50/s0120ae50.cpp.

extern "C" unsigned char g_014a6e88[];
struct C_01082590 { void FUN_01082590(); };

// @ 0x0120b960
extern "C" int __fastcall FUN_0120b960(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1000;
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    int t1013;
    t1000 = (int)((int)(a12));
    t1003 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    *(int*)((char*)(t1003) + 16) = (int)(t1000);
    t1005 = (int)((int)(a8));
    *(unsigned short*)((char*)(t1003) + 6) = (unsigned short)((int)1);
    *(int*)((char*)(t1003) + 8) = (int)((int)0);
    *(int*)((char*)(t1003) + 12) = (int)((int)0);
    *(int*)((char*)(t1003) + 20) = (int)((int)0);
    *(int*)((char*)(t1003)) = (int)((int)g_014a6e88);
    *(int*)((char*)(t1003) + 24) = (int)(t1004);
    *(int*)((char*)(t1003) + 28) = (int)(t1005);
    if (t1005 == (int)0) {
        if (t1004 == (int)0) goto L120b9b8;
    } else {
        if (t1004 == (int)0) goto L120b9ac;
    }
    ((C_01082590*)(t1004))->FUN_01082590();
    L120b9ac:;
    t1009 = (int)(*(int*)((char*)(t1003) + 28));
    if (t1009 != (int)0) {
        ((C_01082590*)(t1009))->FUN_01082590();
    }
    L120b9b8:;
    t1013 = (int)(t1003);
    return (int)(t1013);
}
