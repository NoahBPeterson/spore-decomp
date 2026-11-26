// 0x007eb060: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPAppTelemetry.cpp, match/slices/s007ea440/s007ea440.cpp.

// @ 0x007eb060
extern "C" int __cdecl FUN_007eb060(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    t1002 = (int)((int)(a12));
    if (t1000 != t1001) {
        t1003 = (int)(t1000 - t1002);
        do {
            if (t1002 != (int)0) {
                t1005 = (int)(*(int*)((char*)(t1003) + t1002));
                *(int*)((char*)(t1002)) = (int)(t1005);
            }
            t1002 = (int)(t1002 + (int)4);
            t1006 = (int)(t1003 + t1002);
        } while (t1006 != t1001);
    }
    return (int)(t1002);
}
