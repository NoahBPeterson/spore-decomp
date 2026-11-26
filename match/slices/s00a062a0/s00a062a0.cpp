// 0x00a062a0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/SPCreatureAnimManager.cpp, match/slices/s00a05c20/s00a05c20.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
struct C_00a05270 { void FUN_00a05270(); };

// @ 0x00a062a0
extern "C" int __fastcall FUN_00a062a0(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1004;
    int t1008;
    int t1010;
    int t1012;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    int& t1003_r = t1003;
    *(int*)((char*)(t1003_r) + 340) = (int)((int)0);
    *(int*)((char*)(t1003_r) + 344) = (int)((int)2);
    t1004 = (int)(*(int*)((char*)(t1003_r) + 348));
    if (t1000 != t1004) {
        if (t1000 != (int)0) {
            *(int*)((char*)(t1000) + 408) += (int)1;
        }
        *(int*)((char*)(t1003_r) + 348) = (int)(t1000);
        if (t1004 != (int)0) {
            ((C_00a05270*)(t1004))->FUN_00a05270();
            t1008 = (int)((int)(a8));
            *(int*)((char*)(t1003_r) + 352) = (int)(t1008);
            return (int)(t1008);
        }
        t1010 = (int)((int)(a8));
        *(int*)((char*)(t1003_r) + 352) = (int)(t1010);
        return (int)(t1000);
    }
    t1012 = (int)((int)(a8));
    *(int*)((char*)(t1003_r) + 352) = (int)(t1012);
    return (int)(t1000);
}
