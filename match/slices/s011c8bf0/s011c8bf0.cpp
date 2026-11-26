// 0x011c8bf0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x011c8bf0
extern "C" int __cdecl FUN_011c8bf0(int a4)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1001 = (int)(*(int*)((char*)(t1000)));
        t1002 = (int)(t1001 - (int)1);
        if ((unsigned int)(hs_bind(t1002)) <= (unsigned int)1) {
            t1003 = (int)(*(int*)((char*)(t1000) + 12));
            return (int)(t1003);
        }
    }
    t1004 = (int)((int)0);
    return (int)(t1004);
}
