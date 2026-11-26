// 0x011285f0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01127ee0/s01127ee0.cpp.

// lifted by il2c_lift + l2c_search (ref@t1004); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_014a6ea4[];
struct C_0120b960 { int FUN_0120b960(unsigned int, unsigned int, unsigned int); };

// @ 0x011285f0
extern "C" int __fastcall FUN_011285f0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    unsigned char t1010;
    int t1011;
    t1000 = (int)((int)(a12));
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    int& t1004_r = t1004;
    t1005 = (int)((int)(a8));
    t1006 = (int)(t1004_r);
    ((C_0120b960*)(t1006))->FUN_0120b960((unsigned int)(t1001), (unsigned int)(t1005), (unsigned int)(t1000));
    t1010 = (unsigned char)((int)1);
    *(int*)((char*)(t1004_r)) = (int)((int)g_014a6ea4);
    *(int*)((char*)(t1004_r) + 80) = (int)((int)1065353216);
    *(int*)((char*)(t1004_r) + 84) = (int)((int)1148846080);
    *(int*)((char*)(t1004_r) + 88) = (int)((int)1036831949);
    *(unsigned char*)((char*)(t1004_r) + 92) = (unsigned char)(t1010);
    *(unsigned char*)((char*)(t1004_r) + 93) = (unsigned char)(t1010);
    t1011 = (int)(t1004_r);
    return (int)(t1011);
}
