// 0x00edfce0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00edef10/s00edef10.cpp.

extern "C" unsigned char g_016c7aa4[];
struct C_00f26440 { int FUN_00f26440(unsigned int); };
struct C_00f28c10 { void FUN_00f28c10(unsigned int); };
struct C_00f45970 { void FUN_00f45970(); };
struct C_00f45a80 { int FUN_00f45a80(); };

// @ 0x00edfce0
// @ 0x00edfce0
extern "C" bool __cdecl FUN_00edfce0(int a4, int a8)
{
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    bool t1010;
    int t1011;
    int t1012;
    int t1016;
    int t1017;
    int t1021;
    int t1022;
    bool t1027;
    t1002 = (int)((int)(a8));
    t1003 = (int)(*(int*)((char*)(t1002)));
    t1005 = (int)((int)(a4));
    t1006 = (int)(t1005);
    t1007 = (int)((C_00f26440*)(t1006))->FUN_00f26440((unsigned int)(t1003));
    t1010 = ((int)((unsigned char)(t1007)) == (int)((int)0));
    if (t1010 != (unsigned char)0) {
        t1011 = (int)((int)(*(int*)g_016c7aa4));
        t1012 = (int)(*(int*)((char*)(t1011) + 116));
        ((C_00f45970*)(t1012))->FUN_00f45970();
        t1016 = (int)(*(int*)((char*)(t1002)));
        t1017 = (int)(t1005);
        ((C_00f28c10*)(t1017))->FUN_00f28c10((unsigned int)(t1016));
        t1021 = (int)((int)(*(int*)g_016c7aa4));
        t1022 = (int)(*(int*)((char*)(t1021) + 116));
        t1007 = (int)((C_00f45a80*)(t1022))->FUN_00f45a80();
    }
    t1027 = t1010;
    return t1027;
}
