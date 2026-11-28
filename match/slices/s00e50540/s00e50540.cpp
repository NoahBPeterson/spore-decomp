// 0x00e50540: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e4f860/s00e4f860.cpp.

extern "C" unsigned char g_01485340[];
extern "C" unsigned char g_0148534c[];
extern "C" int __cdecl FUN_00932e80(...);

// @ 0x00e50540
// @ 0x00e50540
extern "C" bool __cdecl FUN_00e50540(int a4)
{
    int t1002;
    int t1005;
    int t1006;
    bool t1007;
    int t1009;
    int t1012;
    bool t1014;
    t1002 = (int)FUN_00932e80((unsigned int)((int)g_0148534c), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    t1005 = (int)((int)(a4));
    t1006 = (int)(*(int*)((char*)(t1005) + 264));
    if ((int)*(int*)((char*)(t1006)) == t1002) {
        t1007 = true;
        return (bool)(t1007);
    }
    t1009 = (int)FUN_00932e80((unsigned int)((int)g_01485340), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    t1012 = (int)(*(int*)((char*)(t1005) + 264));
    t1014 = ((int)(*(int*)((char*)(t1012))) == (int)(t1009));
    return t1014;
}
