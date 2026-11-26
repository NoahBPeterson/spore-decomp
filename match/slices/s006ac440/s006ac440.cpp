// 0x006ac440: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPResource.cpp, match/slices/s006ab3d0/s006ab3d0.cpp.

// @ 0x006ac440
extern "C" int __cdecl FUN_006ac440(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    if ((unsigned int)(t1000) > (unsigned int)0) {
        t1002 = (int)((int)(a12));
        do {
            if (t1001 != (int)0) {
                t1004 = (int)(*(int*)((char*)(t1002)));
                *(int*)((char*)(t1001)) = (int)(t1004);
                t1005 = (int)(*(int*)((char*)(t1002) + 4));
                *(int*)((char*)(t1001) + 4) = (int)(t1005);
            }
            t1000 = (int)(t1000 - (int)1);
            t1001 = (int)(t1001 + (int)8);
        } while ((unsigned int)(t1000) > (unsigned int)0);
    }
    return (int)(t1001);
}
