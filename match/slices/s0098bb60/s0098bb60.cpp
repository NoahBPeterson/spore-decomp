// 0x0098bb60: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0098b910/s0098b910.cpp, src/game/UTFSpore_Win32/TextEdit.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f2150[];
struct C_0098b700 { void FUN_0098b700(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x0098bb60
extern "C" int __fastcall FUN_0098bb60(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1012;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    int& t1003_r = t1003;
    t1004 = (int)(*(int*)((char*)(t1003_r) + 20));
    t1006 = (int)(*(int*)((char*)(t1000)));
    if (t1004 == (int)*(int*)((char*)(t1003_r))) {
        t1007 = (int)(t1003_r);
        ((C_0098b700*)(t1007))->FUN_0098b700((unsigned int)((int)1), (unsigned int)((int)0));
    }
    t1012 = (int)FUN_00f473a0((unsigned int)((int)256), (unsigned int)((int)g_013f2150), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    t1014 = (int)(*(int*)((char*)(t1003_r) + 20));
    *(int*)((char*)(t1014) - 4) = (int)(t1012);
    t1015 = (int)(*(int*)((char*)(t1003_r) + 20));
    t1016 = (int)(t1015 - (int)4);
    *(int*)((char*)(t1003_r) + 20) = (int)(t1016);
    t1017 = (int)(*(int*)((char*)(t1016)));
    *(int*)((char*)(t1003_r) + 12) = (int)(t1017);
    t1018 = (int)(t1017 + (int)256);
    *(int*)((char*)(t1003_r) + 16) = (int)(t1018);
    t1019 = (int)(t1018 + (int)(-4));
    *(int*)((char*)(t1003_r) + 8) = (int)(t1019);
    if (t1019 != (int)0) {
        *(int*)((char*)(t1019)) = (int)(t1006);
    }
    return (int)(t1019);
}
