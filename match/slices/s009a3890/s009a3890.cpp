// 0x009a3890: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s009a2c90/s009a2c90.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f2150[];
struct C_0099c980 { void FUN_0099c980(); };
struct C_009b3450 { void FUN_009b3450(); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x009a3890
extern "C" int __stdcall FUN_009a3890(int a4)
{
    int t1003;
    int t1006;
    int t1007;
    int t1009;
    int t1010;
    int t1014;
    int t1015;
    t1003 = (int)FUN_00f473a0((unsigned int)((int)28), (unsigned int)((int)g_013f2150), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    t1006 = (int)(t1003);
    t1007 = (int)(t1006 + (int)16);
    if (t1007 != (int)0) {
        t1009 = (int)((int)(a4));
        t1010 = (int)(*(int*)((char*)(t1009)));
        *(int*)((char*)(t1007)) = (int)(t1010);
        if (t1010 != (int)0) {
            ((C_009b3450*)(t1010))->FUN_009b3450();
        }
        t1014 = (int)(*(int*)((char*)(t1009) + 4));
        *(int*)((char*)(t1007) + 4) = (int)(t1014);
        t1015 = (int)(*(int*)((char*)(t1009) + 8));
        *(int*)((char*)(t1007) + 8) = (int)(t1015);
        if (t1015 != (int)0) {
            ((C_0099c980*)(t1015))->FUN_0099c980();
        }
        t1003 = (int)(t1006);
    }
    return (int)(t1003);
}
