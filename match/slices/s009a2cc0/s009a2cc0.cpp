// 0x009a2cc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s009a2c90/s009a2c90.cpp.

extern "C" unsigned char g_015504e0[];
extern "C" unsigned char g_0166b260[];
struct C_009a1770 { void FUN_009a1770(unsigned int); };
extern "C" double __cdecl FUN_009a1d90(unsigned int, float, unsigned int, unsigned int);
extern "C" int __cdecl FUN_009a80e0(...);

// @ 0x009a2cc0
extern "C" bool __cdecl FUN_009a2cc0(int a4, int a8)
{
    int t1001;
    int t1002;
    int t1009;
    int t1010;
    int t1012;
    int t1013;
    int t1014;
    unsigned char t1018;
    bool t1021;
    t1001 = (int)((int)(a4));
    t1002 = (int)(t1001 + (int)200);
    *(unsigned char*)((char*)(t1001) + 172) = (unsigned char)((int)0);
    ((C_009a1770*)(t1002))->FUN_009a1770((unsigned int)((int)0));
    FUN_009a80e0((unsigned int)(t1001));
    if ((int)*(int*)((char*)(t1001)) != (int)0) {
        t1009 = (int)((int)(a8));
        *(int*)((char*)(t1001) + 12) = (int)(t1009);
        t1010 = (int)((int)(*(int*)g_015504e0));
        t1012 = (int)((int)1);
        *(int*)((char*)(t1001) + 16) = (int)(t1010);
        *(int*)g_015504e0 = (int)((int)(*(int*)g_015504e0) + t1012);
        t1013 = (int)((int)(*(int*)g_0166b260));
        t1014 = (int)(*(int*)((char*)(t1001)));
        *(int*)((char*)(t1014) + 300) = (int)(t1013);
        *(int*)g_0166b260 = (int)((int)(*(int*)g_0166b260) + t1012);
        *(double*)((char*)(t1001) + 176) = (double)((float)0);
        *(int*)((char*)(t1001) + 192) += t1012;
        *(unsigned char*)((char*)(t1001) + 172) = (unsigned char)((unsigned char)(t1012));
        *(int*)((char*)(t1001) + 196) = (int)((int)0);
        FUN_009a1d90((unsigned int)(t1001), (float)((float)0), (unsigned int)(t1012), (unsigned int)(t1012));
        t1018 = (unsigned char)((unsigned char)(t1012));
        return (bool)(t1018);
    }
    t1021 = false;
    return (bool)(t1021);
}
