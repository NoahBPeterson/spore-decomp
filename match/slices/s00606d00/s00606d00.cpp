// 0x00606d00: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006068c0/s006068c0.cpp, src/game/SPEditors/SPAuthentication.cpp.

// lifted by il2c_lift + l2c_search (bind@t1003); CI scorer MATCH; corpus status nonmatching/residual
template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00606d00
extern "C" int __fastcall FUN_00606d00(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    t1001 = (int)((int)(self));
    t1002 = (int)((int)(a4));
    if (t1002 <= (int)119542881) {
        if (t1002 != (int)119542881) {
            if (t1002 != (int)(-297840274)) {
                if (t1002 != (int)68123886) goto L606d35;
                return (int)(t1001);
            }
        }
        if (t1001 == (int)0) goto L606d35;
        t1003 = (int)(t1001 + (int)28);
        return (int)(hs_bind(t1003));
    }
    if (t1002 == (int)788569552) goto L606d37;
    L606d35:;
    t1001 = (int)((int)0);
    L606d37:;
    return (int)(t1001);
}
