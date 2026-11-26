// 0x00dd0dc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00dd0230/s00dd0230.cpp.

extern "C" unsigned char g_013f6b3c[];
extern "C" unsigned char g_0147c9f8[];
extern "C" unsigned char g_0147cc78[];
extern "C" unsigned char g_0147cc88[];
struct C_00dd0b50 { void FUN_00dd0b50(); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00dd0dc0
extern "C" int __cdecl FUN_00dd0dc0(void)
{
    int t1004;
    int t1005;
    int t1006;
    int t1010;
    int t1012;
    t1004 = (int)FUN_00f473a0((unsigned int)((int)156), (unsigned int)((int)g_013f6b3c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    t1005 = (int)(t1004);
    if (t1005 != (int)0) {
        t1006 = (int)(t1005);
        ((C_00dd0b50*)(t1006))->FUN_00dd0b50();
        *(int*)((char*)(t1005)) = (int)((int)g_0147c9f8);
        *(int*)((char*)(t1005) + 16) = (int)((int)g_0147cc88);
        *(int*)((char*)(t1005) + 20) = (int)((int)g_0147cc78);
        t1010 = (int)(t1005);
        return (int)(t1010);
    }
    t1012 = (int)((int)0);
    return (int)(t1012);
}
