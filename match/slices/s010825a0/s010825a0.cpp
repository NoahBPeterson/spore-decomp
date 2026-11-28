// 0x010825a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Havok/_at_01080000.cpp, match/slices/s01082350/s01082350.cpp.

extern "C" void __cdecl FUN_0107f530(...);

// @ 0x010825a0
// @ 0x010825a0
extern "C" int __fastcall FUN_010825a0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 80));
    t1003 = (int)((int)0);
    t1005 = (int)((int)(a4));
    if (t1001 > (int)0) {
        t1006 = (int)(*(int*)((char*)((int)(self)) + 76));
        do {
            if ((int)*(int*)((char*)(t1006)) == t1005) goto L10825fb;
            t1003 = (int)(t1003 + (int)1);
            t1006 = (int)(t1006 + (int)16);
        } while (t1003 < t1001);
    }
    t1007 = (int)(*(int*)((char*)((int)(self)) + 84));
    t1008 = (int)((int)(self) + (int)76);
    t1009 = (int)(*(int*)((char*)(t1008) + 4));
    t1010 = (int)(t1007 & (int)1073741823);
    if (t1009 == t1010) {
        FUN_0107f530((unsigned int)(t1008), (unsigned int)((int)16));
    }
    t1014 = (int)(*(int*)((char*)(t1008) + 4));
    t1015 = (int)(*(int*)((char*)(t1008)));
    t1016 = (int)(t1014);
    t1017 = (int)(t1016 << (int)4);
    t1003 = (int)(t1017 + t1015);
    t1018 = (int)((int)(a12));
    t1019 = (int)(t1014 + (int)1);
    *(int*)((char*)(t1008) + 4) = (int)(t1019);
    t1020 = (int)((int)(a8));
    *(int*)((char*)(t1003) + 8) = (int)(t1020);
    *(int*)((char*)(t1003) + 12) = (int)(t1018);
    *(int*)((char*)(t1003)) = (int)(t1005);
    L10825fb:;
    return (int)(t1003);
}
