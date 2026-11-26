// 0x0117c3b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_01176f10(...);
extern "C" int __cdecl FUN_011773d0(...);

// @ 0x0117c3b0
extern "C" int __cdecl FUN_0117c3b0(int a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001) + 20));
    if (t1002 != (int)0) {
        t1003 = (int)(*(int*)((char*)(t1001) + 16));
        if (t1002 == t1003) {
            t1006 = (int)FUN_011773d0((unsigned int)(t1003));
            *(int*)((char*)(t1001) + 16) = (int)(t1006);
        }
        t1007 = (int)(*(int*)((char*)(t1001) + 20));
        t1002 = (int)FUN_01176f10((unsigned int)(t1007));
        *(int*)((char*)(t1001) + 20) = (int)((int)0);
    }
    return (int)(t1002);
}
