// 0x00623f40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00622f20/s00622f20.cpp.

extern "C" unsigned char g_013fdd3c[];
struct C_00621bf0 { void FUN_00621bf0(unsigned int); };
extern "C" int __cdecl FUN_00621c70(...);
struct C_00623be0 { int FUN_00623be0(); };
extern "C" int __cdecl FUN_009512c0(...);
extern "C" int __cdecl FUN_009512d0(...);

// @ 0x00623f40
extern "C" int __cdecl FUN_00623f40(void)
{
    int t1004;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1015;
    int t1016;
    int t1020;
    t1004 = (int)FUN_009512c0();
    t1007 = (int)FUN_009512d0((unsigned int)((int)43256), (unsigned int)((int)8), (unsigned int)((int)g_013fdd3c), (unsigned int)(t1004));
    if (t1007 != (int)0) {
        t1008 = (int)(t1007);
        t1011 = (int)((C_00623be0*)(t1008))->FUN_00623be0();
        t1012 = (int)(t1011);
    } else {
        t1012 = (int)((int)0);
    }
    t1015 = (int)FUN_00621c70();
    if (t1015 != (int)0) {
        t1016 = (int)(t1015);
        ((C_00621bf0*)(t1016))->FUN_00621bf0((unsigned int)(t1012));
    }
    t1020 = (int)(t1012);
    return (int)(t1020);
}
