// 0x00745e00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsModelManager.cpp, match/slices/s00745ac0/s00745ac0.cpp.

extern "C" int __cdecl FUN_00743f00(...);

// @ 0x00745e00
// @ 0x00745e00
extern "C" void __cdecl FUN_00745e00(int a4, int a8, int a12, int a16, int a20, int a24, int a28)
{
    int t1000;
    int t1001;
    int t1003;
    int t1;
    int t1004;
    float t1006;
    int t1007;
    int t1008;
    int t4;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    t1000 = (int)((int)(a16));
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(a12));
    t1 = (int)(t1000 + t1000);
    t1004 = (int)(t1 + (int)2);
    if (t1004 < t1003) {
        goto L745e20;
        L745e20:;
        t1006 = (float)(*(float*)((char*)(t1001) + (t1004)*8 + 4));
        if (t1006 > (float)*(float*)((char*)(t1001) + (t1004)*8 - 4)) {
            t1004 = (int)(t1004 - (int)1);
        }
        t1007 = (int)(*(int*)((char*)(t1001) + (t1004)*8));
        *(int*)((char*)(t1001) + (t1000)*8) = (int)(t1007);
        t1008 = (int)(*(int*)((char*)(t1001) + (t1004)*8 + 4));
        *(int*)((char*)(t1001) + (t1000)*8 + 4) = (int)(t1008);
        t1000 = (int)(t1004);
        t4 = (int)(t1004 + t1004);
        t1004 = (int)(t4 + (int)2);
        if (t1004 < t1003) goto L745e20;
    }
    if (t1004 == t1003) {
        t1010 = (int)(*(int*)((char*)(t1001) + (t1004)*8 - 8));
        *(int*)((char*)(t1001) + (t1000)*8) = (int)(t1010);
        t1011 = (int)(*(int*)((char*)(t1001) + (t1004)*8 - 4));
        *(int*)((char*)(t1001) + (t1000)*8 + 4) = (int)(t1011);
        t1000 = (int)(t1004 + (int)(-1));
    }
    t1012 = (int)((int)(a28));
    t1013 = (int)((int)(a24));
    t1014 = (int)((int)(a20));
    t1015 = (int)((int)(a8));
    FUN_00743f00((unsigned int)(t1001), (unsigned int)(t1015), (unsigned int)(t1000), (unsigned int)(t1014), (unsigned int)(t1013), (unsigned int)(t1012));
    return;
}
