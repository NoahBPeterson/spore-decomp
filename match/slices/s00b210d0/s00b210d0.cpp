// 0x00b210d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/EASymbolUtil.cpp, match/slices/s00b20fb0/s00b20fb0.cpp.

// @ 0x00b210d0
extern "C" int __fastcall FUN_00b210d0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    t1002 = (int)(*(int*)((char*)((int)(self)) + 20));
    t1003 = (int)(*(int*)((char*)(t1002)));
    t1004 = (int)((int)0);
    if (t1003 == (int)0) {
        t1002 = (int)(t1002 + (int)4);
        if ((int)*(int*)((char*)(t1002)) == t1004) {
            do {
                t1002 = (int)(t1002 + (int)4);
            } while ((int)*(int*)((char*)(t1002)) == t1004);
        }
        t1003 = (int)(*(int*)((char*)(t1002)));
    }
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1004)) {
        t1006 = (int)((int)(a4));
        Lb21100:;
        t1009 = (int)(*(int*)((char*)((int)(self)) + 24));
        t1010 = (int)(*(int*)((char*)((int)(self)) + 20));
        if (t1003 != (int)*(int*)((char*)(t1010) + (t1009)*4)) {
            t1011 = (int)(*(int*)((char*)(t1003)));
            *(int*)((char*)(t1006) + (t1004)*4) = (int)(t1011);
            t1003 = (int)(*(int*)((char*)(t1003) + 8));
            t1004 = (int)(t1004 + (int)1);
            if (t1003 == (int)0) {
                do {
                    t1003 = (int)(*(int*)((char*)(t1002) + 4));
                    t1002 = (int)(t1002 + (int)4);
                } while (t1003 == (int)0);
            }
            if ((unsigned int)(t1004) < (unsigned int)((int)(a8))) goto Lb21100;
        }
    }
    return (int)(t1004);
}
