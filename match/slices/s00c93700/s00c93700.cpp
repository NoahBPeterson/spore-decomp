// 0x00c93700: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPTribe.cpp, match/slices/s00c92a90/s00c92a90.cpp.

struct C_00afbad0 { void FUN_00afbad0(); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00c93700
extern "C" void __stdcall FUN_00c93700(int a4, int a8)
{
    int t1001;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    t1001 = (int)((int)0);
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1001)) {
        t1003 = (int)((int)(a4));
        do {
            t1006 = (int)(*(int*)((char*)(t1003) + (t1001)*4));
            if (t1006 != (int)0) {
                do {
                    t1007 = (int)(t1006);
                    t1006 = (int)(*(int*)((char*)(t1006) + 104));
                    t1008 = (int)(t1007 + (int)4);
                    ((C_00afbad0*)(t1008))->FUN_00afbad0();
                    FUN_00f47380((unsigned int)(t1007));
                } while (t1006 != (int)0);
            }
            *(int*)((char*)(t1003) + (t1001)*4) = (int)((int)0);
            t1001 = (int)(t1001 + (int)1);
        } while ((unsigned int)(t1001) < (unsigned int)((int)(a8)));
    }
    return;
}
