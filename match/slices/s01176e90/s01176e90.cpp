// 0x01176e90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" void __cdecl FUN_01184260(...);
extern "C" void __cdecl FUN_011842c0(...);

// @ 0x01176e90
extern "C" int __cdecl FUN_01176e90(int a4, int a8)
{
    int t1002;
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1013;
    int t1016;
    int t1023;
    int t1028;
    t1002 = (int)((int)(a8));
    t1004 = (int)((int)(a4));
    t1006 = (int)((int)0);
    t1007 = (int)(t1004 + (int)56);
    t1008 = (int)((int)1);
    *(int*)((char*)(t1004)) = (int)(t1002);
    *(int*)((char*)(t1004) + 4) = (int)(t1006);
    *(int*)((char*)(t1004) + 8) = (int)(t1006);
    *(int*)((char*)(t1004) + 12) = (int)(t1006);
    *(int*)((char*)(t1004) + 16) = (int)(t1008);
    *(int*)((char*)(t1004) + 20) = (int)(t1006);
    *(int*)((char*)(t1004) + 24) = (int)(t1006);
    *(int*)((char*)(t1004) + 28) = (int)(t1006);
    *(int*)((char*)(t1004) + 32) = (int)(t1006);
    *(int*)((char*)(t1004) + 40) = (int)(t1006);
    *(int*)((char*)(t1004) + 36) = (int)(t1006);
    *(int*)((char*)(t1004) + 44) = (int)(t1008);
    *(int*)((char*)(t1004) + 48) = (int)(t1006);
    *(int*)((char*)(t1004) + 52) = (int)(t1006);
    FUN_01184260((unsigned int)(t1006), (unsigned int)(t1004), (unsigned int)(t1007));
    t1013 = (int)(*(int*)((char*)(t1002) + 28));
    if (t1013 != t1006) {
        t1016 = (int)((int (__cdecl*)(int))(t1013))((int)(t1004));
        if (t1016 == (int)0) {
            FUN_011842c0((unsigned int)(t1006), (unsigned int)(t1004), (unsigned int)(t1007));
            t1023 = (int)((int)0);
            return (int)(t1023);
        }
    }
    t1028 = (int)((int)1);
    return (int)(t1028);
}
