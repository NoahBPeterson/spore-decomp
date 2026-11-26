// 0x0104e2f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolManager.cpp, match/slices/s0104e060/s0104e060.cpp.

// @ 0x0104e2f0
extern "C" bool __fastcall FUN_0104e2f0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    unsigned char t1;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    unsigned char t1007;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 372));
    t1002 = (int)((unsigned int)(t1001) >> (int)5);
    t1 = (unsigned char)((unsigned char)(t1002) & (unsigned char)1);
    if (t1 != (unsigned char)0) {
        t1003 = (int)(*(int*)((char*)((int)(self)) + 124));
        t1004 = (int)((int)(a4));
        *(int*)((char*)(t1004)) = (int)(t1003);
    }
    t1005 = (int)(*(int*)((char*)((int)(self)) + 372));
    t1006 = (int)((unsigned int)(t1005) >> (int)5);
    t1007 = (unsigned char)((unsigned char)(t1006) & (unsigned char)1);
    return (bool)(t1007);
}
