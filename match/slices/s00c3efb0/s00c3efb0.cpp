// 0x00c3efb0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGameplayMarker.cpp, match/slices/s00c3ee20/s00c3ee20.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_0146c388[];
extern "C" unsigned char g_0146c44c[];
extern "C" unsigned char g_0146c460[];
struct C_00b18660 { void FUN_00b18660(); };
struct C_00c89630 { void FUN_00c89630(); };
extern "C" void __cdecl FUN_011e073e(...);

// @ 0x00c3efb0
extern "C" int __fastcall FUN_00c3efb0(char* self, int edx_unused)
{
    int t1003;
    int t1007;
    int t1008;
    int t1012;
    int t1013;
    int t1018;
    t1003 = (int)((int)(self));
    int& t1003_r = t1003;
    ((C_00b18660*)((int)(self)))->FUN_00b18660();
    t1007 = (int)(t1003_r + (int)52);
    t1008 = (int)(t1007);
    ((C_00c89630*)(t1008))->FUN_00c89630();
    t1012 = (int)((int)0);
    *(int*)((char*)(t1003_r) + 264) = (int)(t1012);
    *(int*)((char*)(t1003_r) + 268) = (int)(t1012);
    *(int*)((char*)(t1003_r) + 272) = (int)(t1012);
    *(int*)((char*)(t1003_r)) = (int)((int)g_0146c460);
    *(int*)((char*)(t1003_r) + 4) = (int)((int)g_0146c44c);
    *(int*)((char*)(t1007)) = (int)((int)g_0146c388);
    *(int*)((char*)(t1003_r) + 412) = (int)(t1012);
    *(int*)((char*)(t1003_r) + 416) = (int)(t1012);
    *(int*)((char*)(t1003_r) + 420) = (int)(t1012);
    *(unsigned char*)((char*)(t1003_r) + 452) = (unsigned char)((unsigned char)(t1012));
    t1013 = (int)(t1003_r + (int)276);
    FUN_011e073e((unsigned int)(t1013), (unsigned int)(t1012), (unsigned int)((int)136));
    t1018 = (int)(t1003_r);
    return (int)(t1018);
}
