// 0x00a8bf10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a8b940/s00a8b940.cpp.

extern "C" void __cdecl FUN_00a8a8b0(...);
extern "C" void __cdecl FUN_00a8aec0(...);
extern "C" void __cdecl FUN_00a8b420(...);
extern "C" void __cdecl FUN_00a8b940(...);
extern "C" unsigned char g_016781b0[];
extern "C" unsigned char g_016781b8[];
extern "C" unsigned char g_016781bc[];
extern "C" unsigned char g_016781c0[];
extern "C" int __cdecl FUN_011e073e(...);

// @ 0x00a8bf10
extern "C" void __cdecl FUN_00a8bf10(int a4)
{
    if ((unsigned char)(a4) != (unsigned char)0) {
        FUN_011e073e((unsigned int)((int)g_016781b0), (unsigned int)((int)0), (unsigned int)((int)128));
        *(int*)g_016781b0 = (int)((int)&FUN_00a8a8b0);
        *(int*)g_016781b8 = (int)((int)&FUN_00a8aec0);
        *(int*)g_016781bc = (int)((int)&FUN_00a8b420);
        *(int*)g_016781c0 = (int)((int)&FUN_00a8b940);
    }
    return;
}
